Samples set does not require STM8S_StdPeriph_Driver\src source files so sources excluded from library directory.

STM8S_StdPeriph_Driver\src\stm8s.h was patched:

=========== cut here ===================
--- stm8s.h.original	2011-03-03 17:42:32.000000000 +0200
+++ stm8s.h	2011-11-05 17:17:37.804895194 +0200
@@ -26,6 +26,10 @@
 /** @addtogroup STM8S_StdPeriph_Driver
   * @{
   */
+
+#ifdef __cplusplus
+  extern "C" {
+#endif
   
 /* Uncomment the line below according to the target STM8S or STM8A device used in your
    application. */
@@ -171,6 +175,8 @@
 
 /* Includes ------------------------------------------------------------------*/
 
+#include <stdint.h>
+
 /* Exported types and constants ----------------------------------------------*/
 
 /** @addtogroup Exported_types
@@ -186,16 +192,6 @@
 #define     __O     volatile         /*!< defines 'write only' permissions    */
 #define     __IO    volatile         /*!< defines 'read / write' permissions  */
 
-/*!< Signed integer types  */
-typedef   signed char     int8_t;
-typedef   signed short    int16_t;
-typedef   signed long     int32_t;
-
-/*!< Unsigned integer types  */
-typedef unsigned char     uint8_t;
-typedef unsigned short    uint16_t;
-typedef unsigned long     uint32_t;
-
 /*!< STM8 Standard Peripheral Library old types (maintained for legacy purpose) */
 
 typedef int32_t  s32;
@@ -207,7 +203,12 @@
 typedef uint8_t  u8;
 
 
-typedef enum {FALSE = 0, TRUE = !FALSE} bool;
+#ifndef __cplusplus
+  typedef enum {FALSE = 0, TRUE = !FALSE} bool;
+#else
+  #define FALSE false
+  #define TRUE true
+#endif
 
 typedef enum {RESET = 0, SET = !RESET} FlagStatus, ITStatus, BitStatus, BitAction;
 
@@ -2692,6 +2693,12 @@
 
 /* Exported functions ------------------------------------------------------- */
 
+
+/*--------------------------------------------------------------------------- */
+#ifdef __cplusplus
+  }
+#endif
+
 #endif /* __STM8S_H */
 
 /**

