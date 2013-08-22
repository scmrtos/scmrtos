/*
** ADSP-BF609 CPLB table definitions for coreA generated on Aug 21, 2013 at 14:27:38.
*/
/*
** Copyright (C) 2000-2012 Analog Devices Inc., All Rights Reserved.
**
** This file is generated automatically based upon the options selected
** in the System Configuration utility. Changes to the CPLB configuration
** should be made by modifying the appropriate options rather than editing
** this file. To access the System Configuration utility, double-click the
** system.svc file from a navigation view.
**
** Custom additions can be inserted within the user-modifiable sections,
** these are bounded by comments that start with "$VDSG". Only changes
** placed within these sections are preserved when this file is re-generated.
**
** Product      : CrossCore Embedded Studio 1.0.1.0
** Tool Version : 6.0.2.28
*/

#include <sys/platform.h>
#include <cplbtab.h>

#ifdef _MISRA_RULES
#pragma diag(push)
#pragma diag(suppress:misra_rule_2_2)
#pragma diag(suppress:misra_rule_8_10)
#pragma diag(suppress:misra_rule_10_1_a)
#endif /* _MISRA_RULES */

#define CACHE_MEM_MODE (CPLB_DNOCACHE)

#define NOCACHE_READONLY (CPLB_READONLY_ACCESS)

#pragma section("cplb_data")
#pragma file_attr("DualCoreMem=CoreA")

cplb_entry dcplbs_table[] = {


   /*
   ** L1 data memory must be covered by a locked CPLB as it will contain
   ** the tables used in interrupt and exceptions handling support.
   ** For L1 Data A & B, set the write-through bit to avoid 1st write exceptions.
   */

   {0xFF800000, (ENUM_DCPLB_DATA_16KB | CPLB_DNOCACHE | BITM_DCPLB_DATA_LOCK | BITM_DCPLB_DATA_WT)}, 
   {0xFF804000, (ENUM_DCPLB_DATA_16KB | CPLB_DNOCACHE | BITM_DCPLB_DATA_LOCK | BITM_DCPLB_DATA_WT)}, 
   {0xFF900000, (ENUM_DCPLB_DATA_16KB | CPLB_DNOCACHE | BITM_DCPLB_DATA_LOCK | BITM_DCPLB_DATA_WT)}, 
   {0xFF904000, (ENUM_DCPLB_DATA_16KB | CPLB_DNOCACHE | BITM_DCPLB_DATA_LOCK | BITM_DCPLB_DATA_WT)}, 

   /*
   ** 256K L2 SRAM is split as follows:
   **
   **   ICC private area             - (0xC8080000-0xC808041F) 1056B
   **   Shareable, owned by 0        - (0xC8080420-0xC808820F) 32240B
   **   Shareable, owned by 1        - (0xC8088210-0xC808FFFF) 32240B
   **   Core 0                       - (0xC8090000-0xC80A7FFF) 96KB
   **   Core 1                       - (0xC80A8000-0xC80BFFFF) 96KB
   */

   {0xC8080000, (ENUM_DCPLB_DATA_64KB | CPLB_DNOCACHE)}, 
   {0xC8090000, (ENUM_DCPLB_DATA_64KB | CACHE_MEM_MODE)}, 
   {0xC80A0000, (ENUM_DCPLB_DATA_16KB | CACHE_MEM_MODE)}, 
   {0xC80A4000, (ENUM_DCPLB_DATA_16KB | CACHE_MEM_MODE)}, 
   {0xC80A8000, (ENUM_DCPLB_DATA_16KB | CPLB_READONLY_ACCESS)}, 
   {0xC80AC000, (ENUM_DCPLB_DATA_16KB | CPLB_READONLY_ACCESS)}, 
   {0xC80B0000, (ENUM_DCPLB_DATA_64KB | CPLB_READONLY_ACCESS)}, 

     /* Async Memory */
   {0xBC000000, (ENUM_DCPLB_DATA_64MB | CACHE_MEM_MODE)}, 
   {0xB8000000, (ENUM_DCPLB_DATA_64MB | CACHE_MEM_MODE)}, 
   {0xB4000000, (ENUM_DCPLB_DATA_64MB | CACHE_MEM_MODE)}, 
   {0xB0000000, (ENUM_DCPLB_DATA_64MB | CACHE_MEM_MODE)}, 

     /* L2 ROM */
   {0xC8000000, (ENUM_DCPLB_DATA_16KB | CPLB_DNOCACHE)}, 
   {0xC8004000, (ENUM_DCPLB_DATA_16KB | CPLB_DNOCACHE)}, 

   /* end of section - termination */
   {0xffffffff, 0}, 
}; /* dcplbs_table */

#pragma section("cplb_data")
#pragma file_attr("DualCoreMem=CoreA")

cplb_entry icplbs_table[] = {


     /* L1 Code SRAM */
   {0xFFA00000, (ENUM_ICPLB_DATA_64KB | CPLB_I_PAGE_MGMT)}, 

     /* L1 Code cache */
   {0xFFA10000, (ENUM_ICPLB_DATA_16KB | CPLB_I_PAGE_MGMT)}, 

     /* L2 ROM */
   {0xC8000000, (ENUM_ICPLB_DATA_16KB | CPLB_I_PAGE_MGMT)}, 
   {0xC8004000, (ENUM_ICPLB_DATA_16KB | CPLB_I_PAGE_MGMT)}, 

     /* L2 SRAM */
   {0xC8080000, (ENUM_ICPLB_DATA_64KB | CPLB_IDOCACHE)}, 
   {0xC8090000, (ENUM_ICPLB_DATA_64KB | CPLB_IDOCACHE)}, 
   {0xC80A0000, (ENUM_ICPLB_DATA_64KB | CPLB_IDOCACHE)}, 
   {0xC80B0000, (ENUM_ICPLB_DATA_64KB | CPLB_IDOCACHE)}, 

     /* Async Memory */
   {0xBC000000, (ENUM_ICPLB_DATA_64MB | CPLB_IDOCACHE)}, 
   {0xB8000000, (ENUM_ICPLB_DATA_64MB | CPLB_IDOCACHE)}, 
   {0xB4000000, (ENUM_ICPLB_DATA_64MB | CPLB_IDOCACHE)}, 
   {0xB0000000, (ENUM_ICPLB_DATA_64MB | CPLB_IDOCACHE)}, 

   /* end of section - termination */
   {0xffffffff, 0}, 
}; /* icplbs_table */


#ifdef _MISRA_RULES
#pragma diag(pop)
#endif /* _MISRA_RULES */

