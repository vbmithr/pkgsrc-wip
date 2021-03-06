$NetBSD$

--- extensions/browser/api/web_request/form_data_parser.cc.orig	2017-02-02 02:02:54.000000000 +0000
+++ extensions/browser/api/web_request/form_data_parser.cc
@@ -15,7 +15,11 @@
 #include "base/values.h"
 #include "net/base/escape.h"
 #include "net/url_request/url_request.h"
+#if defined(OS_BSD)
+#include <re2/re2.h>
+#else
 #include "third_party/re2/src/re2/re2.h"
+#endif
 
 using base::DictionaryValue;
 using base::ListValue;
