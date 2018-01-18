$NetBSD$

--- lib/sanitizer_common/sanitizer_common_interceptors.inc.orig	2018-01-17 14:42:51.000000000 +0000
+++ lib/sanitizer_common/sanitizer_common_interceptors.inc
@@ -36,6 +36,7 @@
 //   COMMON_INTERCEPTOR_MEMCPY_IMPL
 //   COMMON_INTERCEPTOR_COPY_STRING
 //   COMMON_INTERCEPTOR_STRNDUP_IMPL
+//   COMMON_INTERCEPTOR_LOCALTIME_AND_FRIEND_SCOPE
 //===----------------------------------------------------------------------===//
 
 #include "interception/interception.h"
@@ -75,6 +76,7 @@
 #define clock_settime __clock_settime50
 #define ctime __ctime50
 #define ctime_r __ctime_r50
+#define devname __devname50
 #define getitimer __getitimer50
 #define getpwent __getpwent50
 #define getpwnam __getpwnam50
@@ -88,6 +90,7 @@
 #define glob __glob30
 #define gmtime __gmtime50
 #define gmtime_r __gmtime_r50
+#define localtime __locatime50
 #define localtime_r __localtime_r50
 #define mktime __mktime50
 #define opendir __opendir30
@@ -107,6 +110,9 @@
 #define times __times13
 #define wait3 __wait350
 #define wait4 __wait450
+extern const unsigned short *_ctype_tab_;
+extern const short *_toupper_tab_;
+extern const short *_tolower_tab_;
 #endif
 
 // Platform-specific options.
@@ -279,6 +285,10 @@ bool PlatformHasDifferentMemcpyAndMemmov
   return new_mem;
 #endif
 
+#ifndef COMMON_INTERCEPTOR_LOCALTIME_AND_FRIEND_SCOPE
+#define COMMON_INTERCEPTOR_LOCALTIME_AND_FRIEND_SCOPE
+#endif
+
 struct FileMetadata {
   // For open_memstream().
   char **addr;
@@ -1229,6 +1239,7 @@ static void unpoison_tm(void *ctx, __san
 INTERCEPTOR(__sanitizer_tm *, localtime, unsigned long *timep) {
   void *ctx;
   COMMON_INTERCEPTOR_ENTER(ctx, localtime, timep);
+  COMMON_INTERCEPTOR_LOCALTIME_AND_FRIEND_SCOPE;
   __sanitizer_tm *res = REAL(localtime)(timep);
   if (res) {
     COMMON_INTERCEPTOR_READ_RANGE(ctx, timep, sizeof(*timep));
@@ -1239,6 +1250,7 @@ INTERCEPTOR(__sanitizer_tm *, localtime,
 INTERCEPTOR(__sanitizer_tm *, localtime_r, unsigned long *timep, void *result) {
   void *ctx;
   COMMON_INTERCEPTOR_ENTER(ctx, localtime_r, timep, result);
+  COMMON_INTERCEPTOR_LOCALTIME_AND_FRIEND_SCOPE;
   __sanitizer_tm *res = REAL(localtime_r)(timep, result);
   if (res) {
     COMMON_INTERCEPTOR_READ_RANGE(ctx, timep, sizeof(*timep));
@@ -1249,6 +1261,7 @@ INTERCEPTOR(__sanitizer_tm *, localtime_
 INTERCEPTOR(__sanitizer_tm *, gmtime, unsigned long *timep) {
   void *ctx;
   COMMON_INTERCEPTOR_ENTER(ctx, gmtime, timep);
+  COMMON_INTERCEPTOR_LOCALTIME_AND_FRIEND_SCOPE;
   __sanitizer_tm *res = REAL(gmtime)(timep);
   if (res) {
     COMMON_INTERCEPTOR_READ_RANGE(ctx, timep, sizeof(*timep));
@@ -1259,6 +1272,7 @@ INTERCEPTOR(__sanitizer_tm *, gmtime, un
 INTERCEPTOR(__sanitizer_tm *, gmtime_r, unsigned long *timep, void *result) {
   void *ctx;
   COMMON_INTERCEPTOR_ENTER(ctx, gmtime_r, timep, result);
+  COMMON_INTERCEPTOR_LOCALTIME_AND_FRIEND_SCOPE;
   __sanitizer_tm *res = REAL(gmtime_r)(timep, result);
   if (res) {
     COMMON_INTERCEPTOR_READ_RANGE(ctx, timep, sizeof(*timep));
@@ -1269,6 +1283,7 @@ INTERCEPTOR(__sanitizer_tm *, gmtime_r, 
 INTERCEPTOR(char *, ctime, unsigned long *timep) {
   void *ctx;
   COMMON_INTERCEPTOR_ENTER(ctx, ctime, timep);
+  COMMON_INTERCEPTOR_LOCALTIME_AND_FRIEND_SCOPE;
   // FIXME: under ASan the call below may write to freed memory and corrupt
   // its metadata. See
   // https://github.com/google/sanitizers/issues/321.
@@ -1282,6 +1297,7 @@ INTERCEPTOR(char *, ctime, unsigned long
 INTERCEPTOR(char *, ctime_r, unsigned long *timep, char *result) {
   void *ctx;
   COMMON_INTERCEPTOR_ENTER(ctx, ctime_r, timep, result);
+  COMMON_INTERCEPTOR_LOCALTIME_AND_FRIEND_SCOPE;
   // FIXME: under ASan the call below may write to freed memory and corrupt
   // its metadata. See
   // https://github.com/google/sanitizers/issues/321.
@@ -1295,6 +1311,7 @@ INTERCEPTOR(char *, ctime_r, unsigned lo
 INTERCEPTOR(char *, asctime, __sanitizer_tm *tm) {
   void *ctx;
   COMMON_INTERCEPTOR_ENTER(ctx, asctime, tm);
+  COMMON_INTERCEPTOR_LOCALTIME_AND_FRIEND_SCOPE;
   // FIXME: under ASan the call below may write to freed memory and corrupt
   // its metadata. See
   // https://github.com/google/sanitizers/issues/321.
@@ -1308,6 +1325,7 @@ INTERCEPTOR(char *, asctime, __sanitizer
 INTERCEPTOR(char *, asctime_r, __sanitizer_tm *tm, char *result) {
   void *ctx;
   COMMON_INTERCEPTOR_ENTER(ctx, asctime_r, tm, result);
+  COMMON_INTERCEPTOR_LOCALTIME_AND_FRIEND_SCOPE;
   // FIXME: under ASan the call below may write to freed memory and corrupt
   // its metadata. See
   // https://github.com/google/sanitizers/issues/321.
@@ -1321,6 +1339,7 @@ INTERCEPTOR(char *, asctime_r, __sanitiz
 INTERCEPTOR(long, mktime, __sanitizer_tm *tm) {
   void *ctx;
   COMMON_INTERCEPTOR_ENTER(ctx, mktime, tm);
+  COMMON_INTERCEPTOR_LOCALTIME_AND_FRIEND_SCOPE;
   COMMON_INTERCEPTOR_READ_RANGE(ctx, &tm->tm_sec, sizeof(tm->tm_sec));
   COMMON_INTERCEPTOR_READ_RANGE(ctx, &tm->tm_min, sizeof(tm->tm_min));
   COMMON_INTERCEPTOR_READ_RANGE(ctx, &tm->tm_hour, sizeof(tm->tm_hour));
@@ -1703,6 +1722,7 @@ FORMAT_INTERCEPTOR_IMPL(__isoc99_snprint
 
 #if SANITIZER_INTERCEPT_IOCTL
 #include "sanitizer_common_interceptors_ioctl.inc"
+#include "sanitizer_netbsd_interceptors_ioctl.inc"
 INTERCEPTOR(int, ioctl, int d, unsigned long request, ...) {
   // We need a frame pointer, because we call into ioctl_common_[pre|post] which
   // can trigger a report and we need to be able to unwind through this
@@ -2776,6 +2796,30 @@ INTERCEPTOR(int, accept4, int fd, void *
 #define INIT_ACCEPT4
 #endif
 
+#if SANITIZER_INTERCEPT_PACCEPT
+INTERCEPTOR(int, paccept, int fd, void *addr, unsigned *addrlen,
+            __sanitizer_sigset_t *set, int f) {
+  void *ctx;
+  COMMON_INTERCEPTOR_ENTER(ctx, paccept, fd, addr, addrlen, set, f);
+  unsigned addrlen0 = 0;
+  if (addrlen) {
+    COMMON_INTERCEPTOR_READ_RANGE(ctx, addrlen, sizeof(*addrlen));
+    addrlen0 = *addrlen;
+  }
+  if (set) COMMON_INTERCEPTOR_READ_RANGE(ctx, set, sizeof(*set));
+  int fd2 = REAL(paccept)(fd, addr, addrlen, set, f);
+  if (fd2 >= 0) {
+    if (fd >= 0) COMMON_INTERCEPTOR_FD_SOCKET_ACCEPT(ctx, fd, fd2);
+    if (addr && addrlen)
+      COMMON_INTERCEPTOR_WRITE_RANGE(ctx, addr, Min(*addrlen, addrlen0));
+  }
+  return fd2;
+}
+#define INIT_PACCEPT COMMON_INTERCEPT_FUNCTION(paccept);
+#else
+#define INIT_PACCEPT
+#endif
+
 #if SANITIZER_INTERCEPT_MODF
 INTERCEPTOR(double, modf, double x, double *iptr) {
   void *ctx;
@@ -3164,7 +3208,14 @@ INTERCEPTOR(char *, setlocale, int categ
   if (locale)
     COMMON_INTERCEPTOR_READ_RANGE(ctx, locale, REAL(strlen)(locale) + 1);
   char *res = REAL(setlocale)(category, locale);
-  if (res) COMMON_INTERCEPTOR_WRITE_RANGE(ctx, res, REAL(strlen)(res) + 1);
+  if (res) {
+    COMMON_INTERCEPTOR_WRITE_RANGE(ctx, res, REAL(strlen)(res) + 1);
+#if SANITIZER_NETBSD
+    COMMON_INTERCEPTOR_WRITE_RANGE(ctx, _ctype_tab_, 257 * sizeof(short));
+    COMMON_INTERCEPTOR_WRITE_RANGE(ctx, _toupper_tab_, 257 * sizeof(short));
+    COMMON_INTERCEPTOR_WRITE_RANGE(ctx, _tolower_tab_, 257 * sizeof(short));
+#endif
+  }
   return res;
 }
 
@@ -6476,6 +6527,620 @@ INTERCEPTOR(int, acct, const char *file)
 #define INIT_ACCT
 #endif
 
+#if SANITIZER_INTERCEPT_KVM
+INTERCEPTOR(int, kvm_close, struct __sanitizer_kvm *kd) {
+  void *ctx;
+  COMMON_INTERCEPTOR_ENTER(ctx, kvm_close, kd);
+  if (kd)
+    COMMON_INTERCEPTOR_READ_RANGE(ctx, kd, sizeof(struct __sanitizer_kvm));
+  return REAL(kvm_close)(kd);
+}
+
+INTERCEPTOR(int, kvm_dump_header, struct __sanitizer_kvm *kd,
+            bool (*write_buf)(void*, void*, uptr), void *cookie, int dumpsize) {
+  void *ctx;
+  COMMON_INTERCEPTOR_ENTER(ctx, kvm_dump_header, kd, write_buf, cookie,
+                           dumpsize);
+  if (kd)
+    COMMON_INTERCEPTOR_READ_RANGE(ctx, kd, sizeof(struct __sanitizer_kvm));
+  return REAL(kvm_dump_header)(kd, write_buf, cookie, dumpsize);
+}
+
+INTERCEPTOR(int, kvm_dump_inval, struct __sanitizer_kvm *kd) {
+  void *ctx;
+  COMMON_INTERCEPTOR_ENTER(ctx, kvm_dump_inval, kd);
+  if (kd)
+    COMMON_INTERCEPTOR_READ_RANGE(ctx, kd, sizeof(struct __sanitizer_kvm));
+  return REAL(kvm_dump_inval)(kd);
+}
+
+INTERCEPTOR(int, kvm_dump_mkheader, struct __sanitizer_kvm *kd,
+            OFF_T dump_off) {
+  void *ctx;
+  COMMON_INTERCEPTOR_ENTER(ctx, kvm_dump_mkheader, kd, dump_off);
+  if (kd)
+    COMMON_INTERCEPTOR_READ_RANGE(ctx, kd, sizeof(struct __sanitizer_kvm));
+  return REAL(kvm_dump_mkheader)(kd, dump_off);
+}
+
+INTERCEPTOR(int, kvm_dump_wrtheader, struct __sanitizer_kvm *kd,
+            __sanitizer_FILE *fp, int dumpsize) {
+  void *ctx;
+  COMMON_INTERCEPTOR_ENTER(ctx, kvm_dump_wrtheader, kd, fp, dumpsize);
+  if (kd)
+    COMMON_INTERCEPTOR_READ_RANGE(ctx, kd, sizeof(struct __sanitizer_kvm));
+  return REAL(kvm_dump_wrtheader)(kd, fp, dumpsize);
+}
+
+INTERCEPTOR(char **, kvm_getargv, struct __sanitizer_kvm *kd, void *kp,
+            int nchr) {
+  void *ctx;
+  COMMON_INTERCEPTOR_ENTER(ctx, kvm_getargv, kd, kp, nchr);
+  if (kd)
+    COMMON_INTERCEPTOR_READ_RANGE(ctx, kd, sizeof(struct __sanitizer_kvm));
+  if (kp)
+    COMMON_INTERCEPTOR_READ_RANGE(ctx, kp, struct_kinfo_proc_sz);
+  return REAL(kvm_getargv)(kd, kp, nchr);
+}
+
+INTERCEPTOR(char **, kvm_getargv2, struct __sanitizer_kvm *kd, void *kp,
+            int nchr) {
+  void *ctx;
+  char **argv;
+  COMMON_INTERCEPTOR_ENTER(ctx, kvm_getargv2, kd, kp, nchr);
+  if (kd)
+    COMMON_INTERCEPTOR_READ_RANGE(ctx, kd, sizeof(struct __sanitizer_kvm));
+  if (kp)
+    COMMON_INTERCEPTOR_READ_RANGE(ctx, kp, struct_kinfo_proc2_sz);
+  argv = REAL(kvm_getargv2)(kd, kp, nchr);
+  if (argv) {
+    char **p = argv;
+    while (*p) {
+      COMMON_INTERCEPTOR_WRITE_RANGE(ctx, p, sizeof(char **));
+      COMMON_INTERCEPTOR_WRITE_RANGE(ctx, *p, REAL(strlen)(*p) + 1);
+      p++;
+    }
+    COMMON_INTERCEPTOR_WRITE_RANGE(ctx, p, sizeof(char **));
+  }
+  return argv;
+}
+
+INTERCEPTOR(char **, kvm_getenvv, struct __sanitizer_kvm *kd, void *kp,
+            int nchr) {
+  void *ctx;
+  char **argv;
+  COMMON_INTERCEPTOR_ENTER(ctx, kvm_getenvv, kd, kp, nchr);
+  if (kd)
+    COMMON_INTERCEPTOR_READ_RANGE(ctx, kd, sizeof(struct __sanitizer_kvm));
+  if (kp)
+    COMMON_INTERCEPTOR_READ_RANGE(ctx, kp, struct_kinfo_proc_sz);
+  argv = REAL(kvm_getenvv)(kd, kp, nchr);
+  if (argv) {
+    char **p = argv;
+    while (*p) {
+      COMMON_INTERCEPTOR_WRITE_RANGE(ctx, p, sizeof(char **));
+      COMMON_INTERCEPTOR_WRITE_RANGE(ctx, *p, REAL(strlen)(*p) + 1);
+      p++;
+    }
+    COMMON_INTERCEPTOR_WRITE_RANGE(ctx, p, sizeof(char **));
+  }
+  return argv;
+}
+
+INTERCEPTOR(char **, kvm_getenvv2, struct __sanitizer_kvm *kd, void *kp,
+            int nchr) {
+  void *ctx;
+  char **argv;
+  COMMON_INTERCEPTOR_ENTER(ctx, kvm_getenvv2, kd, kp, nchr);
+  if (kd)
+    COMMON_INTERCEPTOR_READ_RANGE(ctx, kd, sizeof(struct __sanitizer_kvm));
+  if (kp)
+    COMMON_INTERCEPTOR_READ_RANGE(ctx, kp, struct_kinfo_proc2_sz);
+  argv = REAL(kvm_getenvv2)(kd, kp, nchr);
+  if (argv) {
+    char **p = argv;
+    while (*p) {
+      COMMON_INTERCEPTOR_WRITE_RANGE(ctx, p, sizeof(char **));
+      COMMON_INTERCEPTOR_WRITE_RANGE(ctx, *p, REAL(strlen)(*p) + 1);
+      p++;
+    }
+    COMMON_INTERCEPTOR_WRITE_RANGE(ctx, p, sizeof(char **));
+  }
+  return argv;
+}
+
+INTERCEPTOR(char *, kvm_geterr, struct __sanitizer_kvm *kd) {
+  void *ctx;
+  COMMON_INTERCEPTOR_ENTER(ctx, kvm_geterr, kd);
+  if (kd)
+    COMMON_INTERCEPTOR_READ_RANGE(ctx, kd, sizeof(struct __sanitizer_kvm));
+  return REAL(kvm_geterr)(kd);
+}
+
+INTERCEPTOR(int, kvm_getloadavg, struct __sanitizer_kvm *kd, double loadavg[],
+            int nelem) {
+  void *ctx;
+  COMMON_INTERCEPTOR_ENTER(ctx, kvm_getloadavg, kd, loadavg, nelem);
+  if (kd)
+    COMMON_INTERCEPTOR_READ_RANGE(ctx, kd, sizeof(struct __sanitizer_kvm));
+  return REAL(kvm_getloadavg)(kd, loadavg, nelem);
+}
+
+INTERCEPTOR(char *, kvm_getfiles, struct __sanitizer_kvm *kd, int op, int arg,
+            int *cnt) {
+  void *ctx;
+  COMMON_INTERCEPTOR_ENTER(ctx, kvm_getfiles, kd, op, arg, cnt);
+  if (kd)
+    COMMON_INTERCEPTOR_READ_RANGE(ctx, kd, sizeof(struct __sanitizer_kvm));
+  return REAL(kvm_getfiles)(kd, op, arg, cnt);
+}
+
+INTERCEPTOR(char *, kvm_getkernelname, struct __sanitizer_kvm *kd) {
+  void *ctx;
+  char *name;
+  COMMON_INTERCEPTOR_ENTER(ctx, kvm_getkernelname, kd);
+  name = REAL(kvm_getkernelname)(kd);
+  if (name)
+    COMMON_INTERCEPTOR_WRITE_RANGE(ctx, name, REAL(strlen)(name) + 1);
+  return name;
+}
+
+INTERCEPTOR(void *, kvm_getlwps, struct __sanitizer_kvm *kd, int pid,
+            unsigned long paddr, uptr esize, int *cnt) {
+  void *ctx;
+  void *res;
+  COMMON_INTERCEPTOR_ENTER(ctx, kvm_getlwps, kd, pid, paddr, esize, cnt);
+  if (kd)
+    COMMON_INTERCEPTOR_READ_RANGE(ctx, kd, sizeof(struct __sanitizer_kvm));
+  res = REAL(kvm_getlwps)(kd, pid, paddr, esize, cnt);
+  if (res) {
+    COMMON_INTERCEPTOR_WRITE_RANGE(ctx, cnt, sizeof(int));
+    COMMON_INTERCEPTOR_WRITE_RANGE(ctx, res, esize * (*cnt));
+  }
+  return res;
+}
+
+INTERCEPTOR(void *, kvm_getproc2, struct __sanitizer_kvm *kd, int op, int arg,
+            uptr esize, int *cnt) {
+  void *ctx;
+  void *res;
+  COMMON_INTERCEPTOR_ENTER(ctx, kvm_getproc2, kd, op, arg, esize, cnt);
+  if (kd)
+    COMMON_INTERCEPTOR_READ_RANGE(ctx, kd, sizeof(struct __sanitizer_kvm));
+  res = REAL(kvm_getproc2)(kd, op, arg, esize, cnt);
+  if (res) {
+    COMMON_INTERCEPTOR_WRITE_RANGE(ctx, cnt, sizeof(int));
+    COMMON_INTERCEPTOR_WRITE_RANGE(ctx, res, esize * (*cnt));
+  }
+  return res;
+}
+
+INTERCEPTOR(void *, kvm_getprocs, struct __sanitizer_kvm *kd, int op, int arg,
+            int *cnt) {
+  void *ctx;
+  COMMON_INTERCEPTOR_ENTER(ctx, kvm_getprocs, kd, op, arg, cnt);
+  if (kd)
+    COMMON_INTERCEPTOR_READ_RANGE(ctx, kd, sizeof(struct __sanitizer_kvm));
+  return REAL(kvm_getprocs)(kd, op, arg, cnt);
+}
+
+INTERCEPTOR(int, kvm_nlist, struct __sanitizer_kvm *kd, void *nl) {
+  void *ctx;
+  COMMON_INTERCEPTOR_ENTER(ctx, kvm_nlist, kd, nl);
+  if (kd)
+    COMMON_INTERCEPTOR_READ_RANGE(ctx, kd, sizeof(struct __sanitizer_kvm));
+  return REAL(kvm_nlist)(kd, nl);
+}
+
+INTERCEPTOR(struct __sanitizer_kvm *, kvm_open, char *uf, char *mf, char *sf,
+            int flag, char *program) {
+  void *ctx;
+  struct __sanitizer_kvm *kd;
+  COMMON_INTERCEPTOR_ENTER(ctx, kvm_open, uf, mf, sf, flag, program);
+  if (uf)
+    COMMON_INTERCEPTOR_READ_RANGE(ctx, uf, REAL(strlen)(uf) + 1);
+  if (mf)
+    COMMON_INTERCEPTOR_READ_RANGE(ctx, mf, REAL(strlen)(mf) + 1);
+  if (sf)
+    COMMON_INTERCEPTOR_READ_RANGE(ctx, sf, REAL(strlen)(sf) + 1);
+  kd = REAL(kvm_open)(uf, mf, sf, flag, program);
+  if (kd)
+    COMMON_INTERCEPTOR_WRITE_RANGE(ctx, kd, sizeof(struct __sanitizer_kvm));
+  return kd;
+}
+
+INTERCEPTOR(struct __sanitizer_kvm *, kvm_openfiles, char *uf, char *mf,
+            char *sf, int flag, char *program) {
+  void *ctx;
+  struct __sanitizer_kvm *kd;
+  COMMON_INTERCEPTOR_ENTER(ctx, kvm_openfiles, uf, mf, sf, flag, program);
+  if (uf)
+    COMMON_INTERCEPTOR_READ_RANGE(ctx, uf, REAL(strlen)(uf) + 1);
+  if (mf)
+    COMMON_INTERCEPTOR_READ_RANGE(ctx, mf, REAL(strlen)(mf) + 1);
+  if (sf)
+    COMMON_INTERCEPTOR_READ_RANGE(ctx, sf, REAL(strlen)(sf) + 1);
+  kd = REAL(kvm_openfiles)(uf, mf, sf, flag, program);
+  if (kd)
+    COMMON_INTERCEPTOR_WRITE_RANGE(ctx, kd, sizeof(struct __sanitizer_kvm));
+  return kd;
+}
+
+INTERCEPTOR(uptr, kvm_read, struct __sanitizer_kvm *kd, unsigned long kva,
+            void *buf, uptr len) {
+  void *ctx;
+  uptr res;
+  COMMON_INTERCEPTOR_ENTER(ctx, kvm_read, kd, kva, buf, len);
+  res = REAL(kvm_read)(kd, kva, buf, len);
+  if (res)
+    COMMON_INTERCEPTOR_WRITE_RANGE(ctx, buf, res);
+  return res;
+}
+
+INTERCEPTOR(uptr, kvm_uread, struct __sanitizer_kvm *kd, unsigned long uva,
+            void *buf, uptr len) {
+  void *ctx;
+  uptr res;
+  COMMON_INTERCEPTOR_ENTER(ctx, kvm_uread, kd, uva, buf, len);
+  res = REAL(kvm_uread)(kd, uva, buf, len);
+  if (res)
+    COMMON_INTERCEPTOR_WRITE_RANGE(ctx, buf, res);
+  return res;
+}
+
+INTERCEPTOR(uptr, kvm_write, struct __sanitizer_kvm *kd, unsigned long kva,
+            void *buf, uptr len) {
+  void *ctx;
+  uptr res;
+  COMMON_INTERCEPTOR_ENTER(ctx, kvm_write, kd, kva, buf, len);
+  res = REAL(kvm_uread)(kd, kva, buf, len);
+  if (res)
+    COMMON_INTERCEPTOR_READ_RANGE(ctx, buf, res);
+  return res;
+}
+
+#define INIT_KVM \
+  COMMON_INTERCEPT_FUNCTION(kvm_close); \
+  COMMON_INTERCEPT_FUNCTION(kvm_dump_header); \
+  COMMON_INTERCEPT_FUNCTION(kvm_dump_inval); \
+  COMMON_INTERCEPT_FUNCTION(kvm_dump_mkheader); \
+  COMMON_INTERCEPT_FUNCTION(kvm_dump_wrtheader); \
+  COMMON_INTERCEPT_FUNCTION(kvm_getargv); \
+  COMMON_INTERCEPT_FUNCTION(kvm_getargv2); \
+  COMMON_INTERCEPT_FUNCTION(kvm_getenvv); \
+  COMMON_INTERCEPT_FUNCTION(kvm_getenvv2); \
+  COMMON_INTERCEPT_FUNCTION(kvm_geterr); \
+  COMMON_INTERCEPT_FUNCTION(kvm_getfiles); \
+  COMMON_INTERCEPT_FUNCTION(kvm_getkernelname); \
+  COMMON_INTERCEPT_FUNCTION(kvm_getloadavg); \
+  COMMON_INTERCEPT_FUNCTION(kvm_getlwps); \
+  COMMON_INTERCEPT_FUNCTION(kvm_getproc2); \
+  COMMON_INTERCEPT_FUNCTION(kvm_getprocs); \
+  COMMON_INTERCEPT_FUNCTION(kvm_nlist); \
+  COMMON_INTERCEPT_FUNCTION(kvm_open); \
+  COMMON_INTERCEPT_FUNCTION(kvm_openfiles); \
+  COMMON_INTERCEPT_FUNCTION(kvm_read); \
+  COMMON_INTERCEPT_FUNCTION(kvm_uread); \
+  COMMON_INTERCEPT_FUNCTION(kvm_write)
+#else
+#define INIT_KVM
+#endif
+
+#if SANITIZER_INTERCEPT_DEVNAME
+INTERCEPTOR(char *, devname, u64 dev, u32 type) {
+  void *ctx;
+  char *name;
+  COMMON_INTERCEPTOR_ENTER(ctx, devname, dev, type);
+  name = REAL(devname)(dev, type);
+  if (name)
+    COMMON_INTERCEPTOR_WRITE_RANGE(ctx, name, REAL(strlen)(name) + 1);
+  return name;
+}
+
+INTERCEPTOR(int, devname_r, u64 dev, u32 type, const char *path, uptr len) {
+  void *ctx;
+  int res;
+  COMMON_INTERCEPTOR_ENTER(ctx, devname_r, dev, type, path, len);
+  res = REAL(devname_r)(dev, type, path, len);
+  if (!res)
+    COMMON_INTERCEPTOR_WRITE_RANGE(ctx, path, REAL(strlen)(path) + 1);
+  return res;
+}
+
+#define INIT_DEVNAME \
+  COMMON_INTERCEPT_FUNCTION(devname); \
+  COMMON_INTERCEPT_FUNCTION(devname_r)
+#else
+#define INIT_DEVNAME
+#endif
+
+#if SANITIZER_INTERCEPT_SYSCTL
+INTERCEPTOR(int, sysctl, int *name, unsigned int namelen, void *oldp,
+            uptr *oldlenp, void *newp, uptr newlen) {
+  void *ctx;
+  int res;
+  COMMON_INTERCEPTOR_ENTER(ctx, sysctl, name, namelen, oldp, oldlenp, newp,
+                           newlen);
+  if (name) {
+    COMMON_INTERCEPTOR_READ_RANGE(ctx, name, namelen * sizeof(*name));
+  }
+  if (newp) {
+    COMMON_INTERCEPTOR_READ_RANGE(ctx, newp, newlen);
+  }
+  res = REAL(sysctl)(name, namelen, oldp, oldlenp, newp, newlen);
+  if (!res)
+    COMMON_INTERCEPTOR_WRITE_RANGE(ctx, oldp, *oldlenp);
+  return res;
+}
+
+INTERCEPTOR(int, sysctlbyname, char *sname, void *oldp, uptr *oldlenp,
+            void *newp, uptr newlen) {
+  void *ctx;
+  int res;
+  COMMON_INTERCEPTOR_ENTER(ctx, sysctlbyname, sname, oldp, oldlenp, newp,
+                           newlen);
+  if (sname) {
+    COMMON_INTERCEPTOR_READ_RANGE(ctx, sname, REAL(strlen)(sname) + 1);
+  }
+  res = REAL(sysctlbyname)(sname, oldp, oldlenp, newp, newlen);
+  if (!res)
+    COMMON_INTERCEPTOR_WRITE_RANGE(ctx, oldp, *oldlenp);
+  return res;
+}
+
+#define INIT_SYSCTL \
+  COMMON_INTERCEPT_FUNCTION(sysctl); \
+  COMMON_INTERCEPT_FUNCTION(sysctlbyname)
+#else
+#define INIT_SYSCTL
+#endif
+
+#if SANITIZER_INTERCEPT_STRLCPY
+INTERCEPTOR(uptr, strlcpy, char *dst, char *src, uptr size) {
+  void *ctx;
+  uptr res;
+  COMMON_INTERCEPTOR_ENTER(ctx, strlcpy, dst, src, size);
+  if (src) {
+    uptr len = REAL(strnlen)(src, size);
+    COMMON_INTERCEPTOR_READ_RANGE(ctx, src, len >= size ? size : len + 1);
+  }
+  res = REAL(strlcpy)(dst, src, size);
+  COMMON_INTERCEPTOR_WRITE_RANGE(ctx, dst, REAL(strlen)(dst) + 1);
+  return res;
+}
+
+INTERCEPTOR(uptr, strlcat, char *dst, char *src, uptr size) {
+  void *ctx;
+  uptr res;
+  COMMON_INTERCEPTOR_ENTER(ctx, strlcat, dst, src, size);
+  if (src) {
+    uptr len = REAL(strnlen)(src, size);
+    COMMON_INTERCEPTOR_READ_RANGE(ctx, src, len >= size ? size : len + 1);
+  }
+  res = REAL(strlcat)(dst, src, size);
+  COMMON_INTERCEPTOR_WRITE_RANGE(ctx, dst, REAL(strlen)(dst) + 1);
+  return res;
+}
+#define INIT_STRLCPY \
+  COMMON_INTERCEPT_FUNCTION(strlcpy); \
+  COMMON_INTERCEPT_FUNCTION(strlcat)
+#else
+#define INIT_STRLCPY
+#endif
+
+#if SANITIZER_INTERCEPT_GETGROUPLIST
+INTERCEPTOR(int, getgrouplist, const char *name, u32 basegid, u32 *groups,
+            int *ngroups) {
+  void *ctx;
+  int res;
+  COMMON_INTERCEPTOR_ENTER(ctx, getgrouplist, name, basegid, groups, ngroups);
+  if (name)
+    COMMON_INTERCEPTOR_READ_RANGE(ctx, name, REAL(strlen)(name) + 1);
+  if (ngroups)
+    COMMON_INTERCEPTOR_READ_RANGE(ctx, ngroups, sizeof(*ngroups));
+  res = REAL(getgrouplist)(name, basegid, groups, ngroups);
+  if (!res && groups && ngroups) {
+    COMMON_INTERCEPTOR_WRITE_RANGE(ctx, groups, sizeof(*groups) * (*ngroups));
+    COMMON_INTERCEPTOR_WRITE_RANGE(ctx, ngroups, sizeof(*ngroups));
+  }
+  return res;
+}
+
+INTERCEPTOR(int, getgroupmembership, char *name, u32 basegid, u32 *groups,
+            int maxgrp, int *ngroups) {
+  void *ctx;
+  int res;
+  COMMON_INTERCEPTOR_ENTER(ctx, getgroupmembership, name, basegid, groups,
+                           maxgrp, ngroups);
+  if (name)
+    COMMON_INTERCEPTOR_READ_RANGE(ctx, name, REAL(strlen)(name) + 1);
+  res = REAL(getgroupmembership)(name, basegid, groups, maxgrp, ngroups);
+  if (!res && groups && ngroups) {
+    COMMON_INTERCEPTOR_WRITE_RANGE(ctx, groups, sizeof(*groups) * (*ngroups));
+    COMMON_INTERCEPTOR_WRITE_RANGE(ctx, ngroups, sizeof(*ngroups));
+  }
+  return res;
+}
+
+#define INIT_GETGROUPLIST \
+  COMMON_INTERCEPT_FUNCTION(getgrouplist); \
+  COMMON_INTERCEPT_FUNCTION(getgroupmembership)
+#else
+#define INIT_GETGROUPLIST
+#endif
+
+#if SANITIZER_INTERCEPT_ACCESS
+INTERCEPTOR(int, access, const char *path, int mode) {
+  void *ctx;
+  COMMON_INTERCEPTOR_ENTER(ctx, access, path, mode);
+  if (path)
+    COMMON_INTERCEPTOR_READ_RANGE(ctx, path, REAL(strlen)(path) + 1);
+  return REAL(access)(path, mode);
+}
+#define INIT_ACCESS COMMON_INTERCEPT_FUNCTION(access)
+#else
+#define INIT_ACCESS
+#endif
+
+#if SANITIZER_INTERCEPT_FACCESSAT
+INTERCEPTOR(int, faccessat, int fd, const char *path, int mode, int flags) {
+  void *ctx;
+  COMMON_INTERCEPTOR_ENTER(ctx, faccessat, fd, path, mode, flags);
+  if (path)
+    COMMON_INTERCEPTOR_READ_RANGE(ctx, path, REAL(strlen)(path) + 1);
+  return REAL(faccessat)(fd, path, mode, flags);
+}
+#define INIT_FACCESSAT COMMON_INTERCEPT_FUNCTION(faccessat)
+#else
+#define INIT_FACCESSAT
+#endif
+
+#if SANITIZER_INTERCEPT_ATOF
+INTERCEPTOR(double, atof, char *nptr) {
+  void *ctx;
+  COMMON_INTERCEPTOR_ENTER(ctx, atof, nptr);
+  if (nptr) {
+    COMMON_INTERCEPTOR_READ_RANGE(ctx, nptr, REAL(strlen)(nptr) + 1);
+  }
+  return REAL(atof)(nptr); // strtof // todo atoi atol
+}
+#define INIT_ATOF COMMON_INTERCEPT_FUNCTION(atof)
+#else
+#define INIT_ATOF
+#endif
+
+#if SANITIZER_INTERCEPT_USER_FROM_UID
+INTERCEPTOR(const char *, user_from_uid, u32 uid, int nouser) {
+  void *ctx;
+  const char *user;
+  COMMON_INTERCEPTOR_ENTER(ctx, user_from_uid, uid, nouser);
+  user = REAL(user_from_uid)(uid, nouser);
+  if (user)
+    COMMON_INTERCEPTOR_WRITE_RANGE(ctx, user, REAL(strlen)(user) + 1);
+  return user;
+}
+#define INIT_USER_FROM_UID COMMON_INTERCEPT_FUNCTION(user_from_uid)
+#else
+#define INIT_USER_FROM_UID
+#endif
+
+#if SANITIZER_INTERCEPT_UID_FROM_USER
+INTERCEPTOR(int, uid_from_user, const char *name, u32 *uid) {
+  void *ctx;
+  int res;
+  COMMON_INTERCEPTOR_ENTER(ctx, uid_from_user, name, uid);
+  if (name)
+    COMMON_INTERCEPTOR_READ_RANGE(ctx, name, REAL(strlen)(name) + 1);
+  res = REAL(uid_from_user)(name, uid);
+  if (res != -1 && uid)
+    COMMON_INTERCEPTOR_WRITE_RANGE(ctx, uid, sizeof(*uid));
+  return res;
+}
+#define INIT_UID_FROM_USER COMMON_INTERCEPT_FUNCTION(uid_from_user)
+#else
+#define INIT_UID_FROM_USER
+#endif
+
+#if SANITIZER_INTERCEPT_GROUP_FROM_GID
+INTERCEPTOR(const char *, group_from_gid, u32 gid, int nogroup) {
+  void *ctx;
+  const char *group;
+  COMMON_INTERCEPTOR_ENTER(ctx, group_from_gid, gid, nogroup);
+  group = REAL(group_from_gid)(gid, nogroup);
+  if (group) {
+    COMMON_INTERCEPTOR_WRITE_RANGE(ctx, group, REAL(strlen)(group) + 1);
+  }
+  return group;
+}
+#define INIT_GROUP_FROM_GID COMMON_INTERCEPT_FUNCTION(group_from_gid)
+#else
+#define INIT_GROUP_FROM_GID
+#endif
+
+#if SANITIZER_INTERCEPT_GID_FROM_GROUP
+INTERCEPTOR(int, gid_from_group, const char *group, u32 *gid) {
+  void *ctx;
+  int res;
+  COMMON_INTERCEPTOR_ENTER(ctx, gid_from_group, group, gid);
+  if (group)
+    COMMON_INTERCEPTOR_READ_RANGE(ctx, group, REAL(strlen)(group) + 1);
+  res = REAL(gid_from_group)(group, gid);
+  if (res != -1 && gid)
+    COMMON_INTERCEPTOR_WRITE_RANGE(ctx, gid, sizeof(*gid));
+  return res;
+}
+#define INIT_GID_FROM_USER COMMON_INTERCEPT_FUNCTION(gid_from_group)
+#else
+#define INIT_GID_FROM_USER
+#endif
+
+#if SANITIZER_INTERCEPT_GETTTYENT
+INTERCEPTOR(struct __sanitizer_ttyent *, getttyent, void) {
+  void *ctx;
+  struct __sanitizer_ttyent *ttyent;
+  COMMON_INTERCEPTOR_ENTER(ctx, getttyent);
+  ttyent = REAL(getttyent)();
+  if (ttyent) {
+    COMMON_INTERCEPTOR_WRITE_RANGE(ctx, ttyent, struct_ttyent_sz);
+  }
+  return ttyent;
+}
+INTERCEPTOR(struct __sanitizer_ttyent *, getttynam, char *name) {
+  void *ctx;
+  struct __sanitizer_ttyent *ttyent;
+  COMMON_INTERCEPTOR_ENTER(ctx, getttynam, name);
+  if (name)
+    COMMON_INTERCEPTOR_READ_RANGE(ctx, name, REAL(strlen)(name) + 1);
+  ttyent = REAL(getttynam)(name);
+  if (ttyent) {
+    COMMON_INTERCEPTOR_WRITE_RANGE(ctx, ttyent, struct_ttyent_sz);
+  }
+  return ttyent;
+}
+INTERCEPTOR(int, setttyent) {
+  void *ctx;
+  COMMON_INTERCEPTOR_ENTER(ctx, setttyent);
+  return REAL(setttyent)();
+}
+INTERCEPTOR(int, setttyentpath, char *path) {
+  void *ctx;
+  COMMON_INTERCEPTOR_ENTER(ctx, setttyentpath, path);
+  if (path)
+    COMMON_INTERCEPTOR_READ_RANGE(ctx, path, REAL(strlen)(path) + 1);
+  return REAL(setttyentpath)(path);
+}
+INTERCEPTOR(int, endttyent) {
+  void *ctx;
+  COMMON_INTERCEPTOR_ENTER(ctx, endttyent);
+  return REAL(endttyent)();
+}
+#define INIT_GETTTYENT \
+  COMMON_INTERCEPT_FUNCTION(getttyent); \
+  COMMON_INTERCEPT_FUNCTION(getttynam); \
+  COMMON_INTERCEPT_FUNCTION(setttyent); \
+  COMMON_INTERCEPT_FUNCTION(setttyentpath); \
+  COMMON_INTERCEPT_FUNCTION(endttyent)
+#else
+#define INIT_GETTTYENT
+#endif
+
+#if SANITIZER_INTERCEPT_FGETLN
+INTERCEPTOR(char *, fgetln, __sanitizer_FILE *stream, SIZE_T *len) {
+  void *ctx;
+  char *str;
+  COMMON_INTERCEPTOR_ENTER(ctx, fgetln, stream, len);
+  str = REAL(fgetln)(stream, len);
+  if (str && len) {
+    COMMON_INTERCEPTOR_WRITE_RANGE(ctx, len, sizeof(*len));
+    COMMON_INTERCEPTOR_WRITE_RANGE(ctx, str, *len);
+  }
+  return str;
+}
+#define INIT_FGETLN COMMON_INTERCEPT_FUNCTION(fgetln)
+#else
+#define INIT_FGETLN
+#endif
+
 static void InitializeCommonInterceptors() {
   static u64 metadata_mem[sizeof(MetadataHashMap) / sizeof(u64) + 1];
   interceptor_metadata_map = new((void *)&metadata_mem) MetadataHashMap();
@@ -6555,6 +7220,7 @@ static void InitializeCommonInterceptors
   INIT_GETSOCKOPT;
   INIT_ACCEPT;
   INIT_ACCEPT4;
+  INIT_PACCEPT;
   INIT_MODF;
   INIT_RECVMSG;
   INIT_SENDMSG;
@@ -6688,6 +7354,21 @@ static void InitializeCommonInterceptors
   INIT_WCSLEN;
   INIT_WCSCAT;
   INIT_ACCT;
+  INIT_KVM;
+  INIT_DEVNAME;
+  INIT_SYSCTL;
+  INIT_STRLCPY;
+  INIT_GETGROUPLIST;
+  INIT_ACCESS;
+  INIT_FACCESSAT;
+  INIT_ATOF;
+  INIT_USER_FROM_UID;
+  INIT_UID_FROM_USER;
+  INIT_GROUP_FROM_GID;
+  INIT_GID_FROM_USER;
+  INIT_GETTTYENT;
+  INIT_FGETLN;
+  INIT_GETGROUPLIST;
 
 #if SANITIZER_NETBSD
   COMMON_INTERCEPT_FUNCTION(__libc_mutex_lock);