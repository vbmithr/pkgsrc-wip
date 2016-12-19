$NetBSD$

--- source/Plugins/Platform/NetBSD/PlatformNetBSD.h.orig	2016-12-17 10:29:30.000000000 +0000
+++ source/Plugins/Platform/NetBSD/PlatformNetBSD.h
@@ -14,109 +14,73 @@
 // C++ Includes
 // Other libraries and framework includes
 // Project includes
-#include "lldb/Target/Platform.h"
+#include "Plugins/Platform/POSIX/PlatformPOSIX.h"
 
 namespace lldb_private {
 namespace platform_netbsd {
 
-class PlatformNetBSD : public Platform {
+class PlatformNetBSD : public PlatformPOSIX {
 public:
   PlatformNetBSD(bool is_host);
 
-  ~PlatformNetBSD() override = default;
+  ~PlatformNetBSD() override;
 
-  //------------------------------------------------------------
-  // Class functions
-  //------------------------------------------------------------
-  static lldb::PlatformSP CreateInstance(bool force, const ArchSpec *arch);
+  static void DebuggerInitialize(Debugger &debugger);
 
   static void Initialize();
 
   static void Terminate();
 
-  static ConstString GetPluginNameStatic(bool is_host);
-
-  static const char *GetDescriptionStatic(bool is_host);
-
   //------------------------------------------------------------
   // lldb_private::PluginInterface functions
   //------------------------------------------------------------
-  ConstString GetPluginName() override { return GetPluginNameStatic(IsHost()); }
+  static lldb::PlatformSP CreateInstance(bool force, const ArchSpec *arch);
 
-  uint32_t GetPluginVersion() override { return 1; }
+  static ConstString GetPluginNameStatic(bool is_host);
 
-  const char *GetDescription() override {
-    return GetDescriptionStatic(IsHost());
-  }
+  static const char *GetPluginDescriptionStatic(bool is_host);
+
+  ConstString GetPluginName() override;
+
+  uint32_t GetPluginVersion() override { return 1; }
 
   //------------------------------------------------------------
   // lldb_private::Platform functions
   //------------------------------------------------------------
-  bool GetModuleSpec(const FileSpec &module_file_spec, const ArchSpec &arch,
-                     ModuleSpec &module_spec) override;
-
-  Error RunShellCommand(const char *command, const FileSpec &working_dir,
-                        int *status_ptr, int *signo_ptr,
-                        std::string *command_output,
-                        uint32_t timeout_sec) override;
-
   Error ResolveExecutable(const ModuleSpec &module_spec,
                           lldb::ModuleSP &module_sp,
                           const FileSpecList *module_search_paths_ptr) override;
 
-  bool GetRemoteOSVersion() override;
-
-  bool GetRemoteOSBuildString(std::string &s) override;
-
-  bool GetRemoteOSKernelDescription(std::string &s) override;
-
-  // Remote Platform subclasses need to override this function
-  ArchSpec GetRemoteSystemArchitecture() override;
-
-  bool IsConnected() const override;
-
-  Error ConnectRemote(Args &args) override;
-
-  Error DisconnectRemote() override;
-
-  const char *GetHostname() override;
+  const char *GetDescription() override {
+    return GetPluginDescriptionStatic(IsHost());
+  }
 
-  const char *GetUserName(uint32_t uid) override;
+  void GetStatus(Stream &strm) override;
 
-  const char *GetGroupName(uint32_t gid) override;
+  Error GetFileWithUUID(const FileSpec &platform_file, const UUID *uuid,
+                        FileSpec &local_file) override;
 
   bool GetProcessInfo(lldb::pid_t pid, ProcessInstanceInfo &proc_info) override;
 
   uint32_t FindProcesses(const ProcessInstanceInfoMatch &match_info,
                          ProcessInstanceInfoList &process_infos) override;
 
-  Error LaunchProcess(ProcessLaunchInfo &launch_info) override;
-
-  lldb::ProcessSP Attach(ProcessAttachInfo &attach_info, Debugger &debugger,
-                         Target *target, Error &error) override;
-
-  // NetBSD processes can not be launched by spawning and attaching.
-  bool CanDebugProcess() override { return false; }
-
-  // Only on PlatformMacOSX:
-  Error GetFileWithUUID(const FileSpec &platform_file, const UUID *uuid,
-                        FileSpec &local_file) override;
+  bool GetSupportedArchitectureAtIndex(uint32_t idx, ArchSpec &arch) override;
 
-  Error GetSharedModule(const ModuleSpec &module_spec, Process *process,
-                        lldb::ModuleSP &module_sp,
-                        const FileSpecList *module_search_paths_ptr,
-                        lldb::ModuleSP *old_module_sp_ptr,
-                        bool *did_create_ptr) override;
+  int32_t GetResumeCountForLaunchInfo(ProcessLaunchInfo &launch_info) override;
 
-  bool GetSupportedArchitectureAtIndex(uint32_t idx, ArchSpec &arch) override;
+  bool CanDebugProcess() override;
 
-  void GetStatus(Stream &strm) override;
+  lldb::ProcessSP DebugProcess(ProcessLaunchInfo &launch_info,
+                               Debugger &debugger, Target *target,
+                               Error &error) override;
 
   void CalculateTrapHandlerSymbolNames() override;
 
-protected:
-  lldb::PlatformSP m_remote_platform_sp; // Allow multiple ways to connect to a
-                                         // remote netbsd OS
+  uint64_t ConvertMmapFlagsToPlatform(const ArchSpec &arch,
+                                      unsigned flags) override;
+
+  ConstString GetFullNameForDylib(ConstString basename) override;
 
 private:
   DISALLOW_COPY_AND_ASSIGN(PlatformNetBSD);
