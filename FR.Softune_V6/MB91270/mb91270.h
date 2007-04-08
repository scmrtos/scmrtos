/*  FR IO-MAP HEADER FILE      */
/*  =====================      */
/* CREATED BY IO-WIZARD V2.22    */
/* THIS SAMPLE CODE IS PROVIDED AS IS AND IS SUBJECT TO ALTERATIONS. FUJITSU     */
/* MICROELECTRONICS ACCEPTS NO RESPONSIBILITY OR LIABILITY FOR ANY ERRORS OR     */
/* ELIGIBILITY FOR ANY PURPOSES.                                                 */
/*                 (C) Fujitsu Microelectronics Europe GmbH                      */
/*  */
/* ************************************************************************* */
/*                   Fujitsu Microelectronics Europe GmbH                    */
/*                    Am Siebenstein 6-10, 63303 Dreieich                    */
/*                     Tel.: +49 (6103) 690-0, Fax -122                      */
/*                                                                           */
/* THIS SAMPLE CODE IS PROVIDED AS IS AND IS SUBJECT TO ALTERATIONS. FUJITSU */
/* MICROELECTRONICS ACCEPTS NO RESPONSIBILITY OR LIABILITY FOR ANY ERRORS OR */
/* ELIGIBILITY FOR ANY PURPOSES                                              */
/*                 (C) Fujitsu Microelectronics Europe GmbH                  */
/* ************************************************************************* */
/* ---------------------------------------------------------------------- */
/* $Id: MB91270.h,v 1.3 2006/02/16 11:15:56 mherz Exp $ */
/* ---------------------------------------------------------------------- */
/*                      */
/* $Id: MB91270.h,v 1.3 2006/02/16 11:15:56 mherz Exp $ */
/*      - Initial Version */
/*  Id: MB91270.iow,v 1.1 2005/08/08 10:32:08 mherz Exp  */
/*      - Update CAN-register   */

/* ASSEMBLER DEFINITIONS : */

#ifdef  __IO_DEFINE
#define __IO_EXTERN
#else
#define __IO_EXTERN	extern volatile
#endif
#ifdef __IO_DEFINE
#pragma asm
 .GLOBAL _pdr0,     _pdr1,     _pdr2,     _pdr3,     _pdr4,     _pdr5
 .GLOBAL _pdr6,     _pdr7,     _pdr8,     _pdr9,     _pdra,     _pdrb
 .GLOBAL _pdrc,     _pdrd,     _pdre,     _pdrf,     _pdrg,     _eirr0
 .GLOBAL _enir0,    _elvr0,    _dicr,     _hrcl,     _tmrlr0,   _tmr0
 .GLOBAL _tmcsr0,   _tmrlr1,   _tmr1,     _tmcsr1,   _tmrlr2,   _tmr2
 .GLOBAL _tmcsr2,   _scr0,     _smr0,     _ssr0,     _rdr0,     _tdr0
 .GLOBAL _escr0,    _eccr0,    _bgr0,     _bgr10,    _bgr00,    _scr5
 .GLOBAL _smr5,     _ssr5,     _rdr5,     _tdr5,     _escr5,    _eccr5
 .GLOBAL _bgr5,     _bgr15,    _bgr05,    _scr6,     _smr6,     _ssr6
 .GLOBAL _rdr6,     _tdr6,     _escr6,    _eccr6,    _bgr6,     _bgr16
 .GLOBAL _bgr06,    _scr1,     _smr1,     _ssr1,     _rdr1,     _tdr1
 .GLOBAL _escr1,    _eccr1,    _bgr1,     _bgr11,    _bgr01,    _scr2
 .GLOBAL _smr2,     _ssr2,     _rdr2,     _tdr2,     _escr2,    _eccr2
 .GLOBAL _bgr2,     _bgr12,    _bgr02,    _scr3,     _smr3,     _ssr3
 .GLOBAL _rdr3,     _tdr3,     _escr3,    _eccr3,    _bgr3,     _bgr13
 .GLOBAL _bgr03,    _scr4,     _smr4,     _ssr4,     _rdr4,     _tdr4
 .GLOBAL _escr4,    _eccr4,    _bgr4,     _bgr14,    _bgr04,    _eirr1
 .GLOBAL _enir1,    _elvr1,    _tctdt0,   _tcccs0,   _tctdt1,   _tcccs1
 .GLOBAL _tctdt2,   _tcccs2,   _tctdt3,   _tcccs3,   _ipcp1,    _ipcp0
 .GLOBAL _ics01,    _ipcp3,    _ipcp2,    _ics23,    _ipcp5,    _ipcp4
 .GLOBAL _ics45,    _ipcp7,    _ipcp6,    _ics67,    _occp1,    _occp0
 .GLOBAL _occp3,    _occp2,    _ocs23,    _ocs01,    _occp5,    _occp4
 .GLOBAL _occp7,    _occp6,    _ocs67,    _ocs45,    _eirr2,    _enir2
 .GLOBAL _elvr2,    _eirr3,    _enir3,    _elvr3,    _eirr4,    _enir4
 .GLOBAL _elvr4,    _dacr,     _dadr0,    _dadr1,    _dadbl,    _wtdbl
 .GLOBAL _wtcr,     _wtbr,     _wthr,     _wtmr,     _wtsr,     _aderh
 .GLOBAL _aderl,    _adcs1,    _adcs0,    _adcr1,    _adcr0,    _adct1
 .GLOBAL _adct0,    _adsch,    _adech,    _cucr,     _cutd,     _cutr1
 .GLOBAL _cutr2,    _udrc1,    _udrc0,    _udcr1,    _udcr0,    _udcch0
 .GLOBAL _udccl0,   _udcs0,    _udcch1,   _udccl1,   _udcs1,    _udrc3
 .GLOBAL _udrc2,    _udcr3,    _udcr2,    _udcch2,   _udccl2,   _udcs2
 .GLOBAL _udcch3,   _udccl3,   _udcs3,    _ad2erh,   _ad2erl,   _ad2cs1
 .GLOBAL _ad2cs0,   _ad2cr1,   _ad2cr0,   _ad2ct1,   _ad2ct0,   _ad2sch
 .GLOBAL _ad2ech,   _cmpr,     _cmcr,     _cmt1,     _cmt2,     _canpre
 .GLOBAL _eissr,    _prlh0,    _prll0,    _prlh1,    _prll1,    _prlh2
 .GLOBAL _prll2,    _prlh3,    _prll3,    _ppgc0,    _ppgc1,    _ppgc2
 .GLOBAL _ppgc3,    _prlh4,    _prll4,    _prlh5,    _prll5,    _prlh6
 .GLOBAL _prll6,    _prlh7,    _prll7,    _ppgc4,    _ppgc5,    _ppgc6
 .GLOBAL _ppgc7,    _prlh8,    _prll8,    _prlh9,    _prll9,    _prlha
 .GLOBAL _prlla,    _prlhb,    _prllb,    _ppgc8,    _ppgc9,    _ppgca
 .GLOBAL _ppgcb,    _prlhc,    _prllc,    _prlhd,    _prlld,    _prlhe
 .GLOBAL _prlle,    _prlhf,    _prllf,    _ppgcc,    _ppgcd,    _ppgce
 .GLOBAL _ppgcf,    _ppgtrg,   _ppgrevc,  _ppgswap,  _cmclkr,   _dmaca0
 .GLOBAL _dmacb0,   _dmaca1,   _dmacb1,   _dmaca2,   _dmacb2,   _dmaca3
 .GLOBAL _dmacb3,   _dmaca4,   _dmacb4,   _dmacr,    _bsd0,     _bsd1
 .GLOBAL _bsdc,     _bsrr,     _ddr0,     _ddr1,     _ddr2,     _ddr3
 .GLOBAL _ddr4,     _ddr5,     _ddr6,     _ddr7,     _ddr8,     _ddr9
 .GLOBAL _ddra,     _ddrb,     _ddrc,     _ddrd,     _ddre,     _ddrf
 .GLOBAL _ddrg,     _pfr0,     _pfr1,     _pfr2,     _pfr3,     _pfr4
 .GLOBAL _pfr5,     _pfr6,     _pfr7,     _pfr8,     _pfr9,     _pfra
 .GLOBAL _pfrb,     _pfrc,     _pfrd,     _pfre,     _pfrf,     _pfrg
 .GLOBAL _icr00,    _icr01,    _icr02,    _icr03,    _icr04,    _icr05
 .GLOBAL _icr06,    _icr07,    _icr08,    _icr09,    _icr10,    _icr11
 .GLOBAL _icr12,    _icr13,    _icr14,    _icr15,    _icr16,    _icr17
 .GLOBAL _icr18,    _icr19,    _icr20,    _icr21,    _icr22,    _icr23
 .GLOBAL _icr24,    _icr25,    _icr26,    _icr27,    _icr28,    _icr29
 .GLOBAL _icr30,    _icr31,    _icr32,    _icr33,    _icr34,    _icr35
 .GLOBAL _icr36,    _icr37,    _icr38,    _icr39,    _icr40,    _icr41
 .GLOBAL _icr42,    _icr43,    _icr44,    _icr45,    _icr46,    _icr47
 .GLOBAL _rsrr,     _stcr,     _tbcr,     _ctbr,     _clkr,     _wpr
 .GLOBAL _divr0,    _divr1,    _osccr,    _oscr,     _csvcr,    _pper0
 .GLOBAL _pper1,    _pper2,    _pper3,    _pper4,    _pper5,    _pper6
 .GLOBAL _pper7,    _pper8,    _pper9,    _ppera,    _pperb,    _pperc
 .GLOBAL _pperd,    _ppere,    _pperf,    _pperg,    _ppcr0,    _ppcr1
 .GLOBAL _ppcr2,    _ppcr3,    _ppcr4,    _ppcr5,    _ppcr6,    _ppcr7
 .GLOBAL _ppcr8,    _ppcr9,    _ppcra,    _ppcrb,    _ppcrc,    _ppcrd
 .GLOBAL _ppcre,    _ppcrf,    _ppcrg,    _pilr0,    _pilr1,    _pilr2
 .GLOBAL _pilr3,    _pilr4,    _pilr5,    _pilr6,    _pilr7,    _pilr8
 .GLOBAL _pilr9,    _pilra,    _pilrb,    _pilrc,    _pilrd,    _pilre
 .GLOBAL _pilrf,    _pilrg,    _ibcr0,    _ibsr0,    _itbah0,   _itbal0
 .GLOBAL _itmkh0,   _itmkl0,   _ismk0,    _isba0,    _idar0,    _iccr0
 .GLOBAL _ibcr1,    _ibsr1,    _itbah1,   _itbal1,   _itmkh1,   _itmkl1
 .GLOBAL _ismk1,    _isba1,    _idar1,    _iccr1,    _ibcr2,    _ibsr2
 .GLOBAL _itbah2,   _itbal2,   _itmkh2,   _itmkl2,   _ismk2,    _isba2
 .GLOBAL _idar2,    _iccr2,    _hwdcs,    _epfr0,    _epfr1,    _epfr2
 .GLOBAL _epfr3,    _epfr4,    _epfr5,    _epfr6,    _epfr7,    _epfr8
 .GLOBAL _epfr9,    _epfra,    _epfrb,    _epfrc,    _epfrd,    _epfre
 .GLOBAL _epfrf,    _epfrg,    _pidr0,    _pidr1,    _pidr2,    _pidr3
 .GLOBAL _pidr4,    _pidr5,    _pidr6,    _pidr7,    _pidr8,    _pidr9
 .GLOBAL _pidra,    _pidrb,    _pidrc,    _pidrd,    _pidre,    _pidrf
 .GLOBAL _pidrg,    _asr0,     _acr0,     _asr1,     _acr1,     _asr2
 .GLOBAL _acr2,     _asr3,     _acr3,     _awr0,     _awr1,     _awr2
 .GLOBAL _awr3,     _cser,     _tcr,      _modr,     _dmasa0,   _dmada0
 .GLOBAL _dmasa1,   _dmada1,   _dmasa2,   _dmada2,   _dmasa3,   _dmada3
 .GLOBAL _dmasa4,   _dmada4,   _flcr,     _flwc,     _ctrlr0,   _statr0
 .GLOBAL _errcnt0,  _btr0,     _intr0,    _testr0,   _brper0,   _if1creq0
 .GLOBAL _if1cmsk0, _if1msk120, _if1msk20, _if1msk10, _if1arb120, _if1arb20
 .GLOBAL _if1arb10, _if1mctr0, _if1dta120, _if1dta10, _if1dta20, _if1dtb120
 .GLOBAL _if1dtb10, _if1dtb20, _if1dta_swp120, _if1dta_swp20, _if1dta_swp10, _if1dtb_swp120
 .GLOBAL _if1dtb_swp20, _if1dtb_swp10, _if2creq0, _if2cmsk0, _if2msk120, _if2msk20
 .GLOBAL _if2msk10, _if2arb120, _if2arb20, _if2arb10, _if2mctr0, _if2dta120
 .GLOBAL _if2dta10, _if2dta20, _if2dtb120, _if2dtb10, _if2dtb20, _if2dta_swp120
 .GLOBAL _if2dta_swp20, _if2dta_swp10, _if2dtb_swp120, _if2dtb_swp20, _if2dtb_swp10, _treqr120
 .GLOBAL _treqr20,  _treqr10,  _treqr340, _treqr40,  _treqr30,  _newdt120
 .GLOBAL _newdt20,  _newdt10,  _newdt340, _newdt40,  _newdt30,  _intpnd120
 .GLOBAL _intpnd20, _intpnd10, _intpnd340, _intpnd40, _intpnd30, _msgval120
 .GLOBAL _msgval20, _msgval10, _msgval340, _msgval40, _msgval30, _ctrlr1
 .GLOBAL _statr1,   _errcnt1,  _btr1,     _intr1,    _testr1,   _brper1
 .GLOBAL _if1creq1, _if1cmsk1, _if1msk121, _if1msk21, _if1msk11, _if1arb121
 .GLOBAL _if1arb21, _if1arb11, _if1mctr1, _if1dta121, _if1dta11, _if1dta21
 .GLOBAL _if1dtb121, _if1dtb11, _if1dtb21, _if1dta_swp121, _if1dta_swp21, _if1dta_swp11
 .GLOBAL _if1dtb_swp121, _if1dtb_swp21, _if1dtb_swp11, _if2creq1, _if2cmsk1, _if2msk121
 .GLOBAL _if2msk21, _if2msk11, _if2arb121, _if2arb21, _if2arb11, _if2mctr1
 .GLOBAL _if2dta121, _if2dta11, _if2dta21, _if2dtb121, _if2dtb11, _if2dtb21
 .GLOBAL _if2dta_swp121, _if2dta_swp21, _if2dta_swp11, _if2dtb_swp121, _if2dtb_swp21, _if2dtb_swp11
 .GLOBAL _treqr121, _treqr21,  _treqr11,  _treqr341, _treqr41,  _treqr31
 .GLOBAL _newdt121, _newdt21,  _newdt11,  _newdt341, _newdt41,  _newdt31
 .GLOBAL _intpnd121, _intpnd21, _intpnd11, _intpnd341, _intpnd41, _intpnd31
 .GLOBAL _msgval121, _msgval21, _msgval11, _msgval341, _msgval41, _msgval31
 .GLOBAL _ctrlr2,   _statr2,   _errcnt2,  _btr2,     _intr2,    _testr2
 .GLOBAL _brper2,   _if1creq2, _if1cmsk2, _if1msk122, _if1msk22, _if1msk12
 .GLOBAL _if1arb122, _if1arb22, _if1arb12, _if1mctr2, _if1dta122, _if1dta12
 .GLOBAL _if1dta22, _if1dtb122, _if1dtb12, _if1dtb22, _if1dta_swp122, _if1dta_swp22
 .GLOBAL _if1dta_swp12, _if1dtb_swp122, _if1dtb_swp22, _if1dtb_swp12, _if2creq2, _if2cmsk2
 .GLOBAL _if2msk122, _if2msk22, _if2msk12, _if2arb122, _if2arb22, _if2arb12
 .GLOBAL _if2mctr2, _if2dta122, _if2dta12, _if2dta22, _if2dtb122, _if2dtb12
 .GLOBAL _if2dtb22, _if2dta_swp122, _if2dta_swp22, _if2dta_swp12, _if2dtb_swp122, _if2dtb_swp22
 .GLOBAL _if2dtb_swp12, _treqr122, _treqr22,  _treqr12,  _treqr342, _treqr42
 .GLOBAL _treqr32,  _newdt122, _newdt22,  _newdt12,  _newdt342, _newdt42
 .GLOBAL _newdt32,  _intpnd122, _intpnd22, _intpnd12, _intpnd342, _intpnd42
 .GLOBAL _intpnd32, _msgval122, _msgval22, _msgval12, _msgval342, _msgval42
 .GLOBAL _msgval32

_pdr0      .EQU 0x000000
PDR0       .EQU 0x000000 /* Port Data Register */
_pdr1      .EQU 0x000001
PDR1       .EQU 0x000001
_pdr2      .EQU 0x000002
PDR2       .EQU 0x000002
_pdr3      .EQU 0x000003
PDR3       .EQU 0x000003
_pdr4      .EQU 0x000004
PDR4       .EQU 0x000004
_pdr5      .EQU 0x000005
PDR5       .EQU 0x000005
_pdr6      .EQU 0x000006
PDR6       .EQU 0x000006
_pdr7      .EQU 0x000007
PDR7       .EQU 0x000007
_pdr8      .EQU 0x000008
PDR8       .EQU 0x000008
_pdr9      .EQU 0x000009
PDR9       .EQU 0x000009
_pdra      .EQU 0x00000A
PDRA       .EQU 0x00000A
_pdrb      .EQU 0x00000B
PDRB       .EQU 0x00000B
_pdrc      .EQU 0x00000C
PDRC       .EQU 0x00000C
_pdrd      .EQU 0x00000D
PDRD       .EQU 0x00000D
_pdre      .EQU 0x00000E
PDRE       .EQU 0x00000E
_pdrf      .EQU 0x00000F
PDRF       .EQU 0x00000F
_pdrg      .EQU 0x000010
PDRG       .EQU 0x000010
_eirr0     .EQU 0x000040
EIRR0      .EQU 0x000040 /* External Interrupt 0-7 */
_enir0     .EQU 0x000041
ENIR0      .EQU 0x000041
_elvr0     .EQU 0x000042
ELVR0      .EQU 0x000042
_dicr      .EQU 0x000044
DICR       .EQU 0x000044 /* DLYI/I-unit */
_hrcl      .EQU 0x000045
HRCL       .EQU 0x000045
_tmrlr0    .EQU 0x000048
TMRLR0     .EQU 0x000048 /* Reload Timer 0 */
_tmr0      .EQU 0x00004A
TMR0       .EQU 0x00004A
_tmcsr0    .EQU 0x00004E
TMCSR0     .EQU 0x00004E
_tmrlr1    .EQU 0x000050
TMRLR1     .EQU 0x000050 /* Reload Timer 1 */
_tmr1      .EQU 0x000052
TMR1       .EQU 0x000052
_tmcsr1    .EQU 0x000056
TMCSR1     .EQU 0x000056
_tmrlr2    .EQU 0x000058
TMRLR2     .EQU 0x000058 /* Reload Timer 2 */
_tmr2      .EQU 0x00005C
TMR2       .EQU 0x00005C
_tmcsr2    .EQU 0x00005E
TMCSR2     .EQU 0x00005E
_scr0      .EQU 0x000060
SCR0       .EQU 0x000060 /* LIN-UART 0 */
_smr0      .EQU 0x000061
SMR0       .EQU 0x000061
_ssr0      .EQU 0x000062
SSR0       .EQU 0x000062
_rdr0      .EQU 0x000063
RDR0       .EQU 0x000063
_tdr0      .EQU 0x000063
TDR0       .EQU 0x000063
_escr0     .EQU 0x000064
ESCR0      .EQU 0x000064
_eccr0     .EQU 0x000065
ECCR0      .EQU 0x000065
_bgr0      .EQU 0x000066
BGR0       .EQU 0x000066
_bgr10     .EQU 0x000066
BGR10      .EQU 0x000066
_bgr00     .EQU 0x000067
BGR00      .EQU 0x000067
_scr5      .EQU 0x000068
SCR5       .EQU 0x000068 /* LIN-UART 5 */
_smr5      .EQU 0x000069
SMR5       .EQU 0x000069
_ssr5      .EQU 0x00006A
SSR5       .EQU 0x00006A
_rdr5      .EQU 0x00006B
RDR5       .EQU 0x00006B
_tdr5      .EQU 0x00006B
TDR5       .EQU 0x00006B
_escr5     .EQU 0x00006C
ESCR5      .EQU 0x00006C
_eccr5     .EQU 0x00006D
ECCR5      .EQU 0x00006D
_bgr5      .EQU 0x00006E
BGR5       .EQU 0x00006E
_bgr15     .EQU 0x00006E
BGR15      .EQU 0x00006E
_bgr05     .EQU 0x00006F
BGR05      .EQU 0x00006F
_scr6      .EQU 0x000070
SCR6       .EQU 0x000070 /* LIN-UART 6 */
_smr6      .EQU 0x000071
SMR6       .EQU 0x000071
_ssr6      .EQU 0x000072
SSR6       .EQU 0x000072
_rdr6      .EQU 0x000073
RDR6       .EQU 0x000073
_tdr6      .EQU 0x000073
TDR6       .EQU 0x000073
_escr6     .EQU 0x000074
ESCR6      .EQU 0x000074
_eccr6     .EQU 0x000075
ECCR6      .EQU 0x000075
_bgr6      .EQU 0x000076
BGR6       .EQU 0x000076
_bgr16     .EQU 0x000076
BGR16      .EQU 0x000076
_bgr06     .EQU 0x000077
BGR06      .EQU 0x000077
_scr1      .EQU 0x0000B0
SCR1       .EQU 0x0000B0 /* LIN-UART 1 */
_smr1      .EQU 0x0000B1
SMR1       .EQU 0x0000B1
_ssr1      .EQU 0x0000B2
SSR1       .EQU 0x0000B2
_rdr1      .EQU 0x0000B3
RDR1       .EQU 0x0000B3
_tdr1      .EQU 0x0000B3
TDR1       .EQU 0x0000B3
_escr1     .EQU 0x0000B4
ESCR1      .EQU 0x0000B4
_eccr1     .EQU 0x0000B5
ECCR1      .EQU 0x0000B5
_bgr1      .EQU 0x0000B6
BGR1       .EQU 0x0000B6
_bgr11     .EQU 0x0000B6
BGR11      .EQU 0x0000B6
_bgr01     .EQU 0x0000B7
BGR01      .EQU 0x0000B7
_scr2      .EQU 0x0000B8
SCR2       .EQU 0x0000B8 /* LIN-UART 2 */
_smr2      .EQU 0x0000B9
SMR2       .EQU 0x0000B9
_ssr2      .EQU 0x0000BA
SSR2       .EQU 0x0000BA
_rdr2      .EQU 0x0000BB
RDR2       .EQU 0x0000BB
_tdr2      .EQU 0x0000BB
TDR2       .EQU 0x0000BB
_escr2     .EQU 0x0000BC
ESCR2      .EQU 0x0000BC
_eccr2     .EQU 0x0000BD
ECCR2      .EQU 0x0000BD
_bgr2      .EQU 0x0000BE
BGR2       .EQU 0x0000BE
_bgr12     .EQU 0x0000BE
BGR12      .EQU 0x0000BE
_bgr02     .EQU 0x0000BF
BGR02      .EQU 0x0000BF
_scr3      .EQU 0x0000C0
SCR3       .EQU 0x0000C0 /* LIN-UART 3 */
_smr3      .EQU 0x0000C1
SMR3       .EQU 0x0000C1
_ssr3      .EQU 0x0000C2
SSR3       .EQU 0x0000C2
_rdr3      .EQU 0x0000C3
RDR3       .EQU 0x0000C3
_tdr3      .EQU 0x0000C3
TDR3       .EQU 0x0000C3
_escr3     .EQU 0x0000C4
ESCR3      .EQU 0x0000C4
_eccr3     .EQU 0x0000C5
ECCR3      .EQU 0x0000C5
_bgr3      .EQU 0x0000C6
BGR3       .EQU 0x0000C6
_bgr13     .EQU 0x0000C6
BGR13      .EQU 0x0000C6
_bgr03     .EQU 0x0000C7
BGR03      .EQU 0x0000C7
_scr4      .EQU 0x0000C8
SCR4       .EQU 0x0000C8 /* LIN-UART 4 */
_smr4      .EQU 0x0000C9
SMR4       .EQU 0x0000C9
_ssr4      .EQU 0x0000CA
SSR4       .EQU 0x0000CA
_rdr4      .EQU 0x0000CB
RDR4       .EQU 0x0000CB
_tdr4      .EQU 0x0000CB
TDR4       .EQU 0x0000CB
_escr4     .EQU 0x0000CC
ESCR4      .EQU 0x0000CC
_eccr4     .EQU 0x0000CD
ECCR4      .EQU 0x0000CD
_bgr4      .EQU 0x0000CE
BGR4       .EQU 0x0000CE
_bgr14     .EQU 0x0000CE
BGR14      .EQU 0x0000CE
_bgr04     .EQU 0x0000CF
BGR04      .EQU 0x0000CF
_eirr1     .EQU 0x0000D0
EIRR1      .EQU 0x0000D0 /* External Interrupt 8-15 */
_enir1     .EQU 0x0000D1
ENIR1      .EQU 0x0000D1
_elvr1     .EQU 0x0000D2
ELVR1      .EQU 0x0000D2
_tctdt0    .EQU 0x0000D4
TCTDT0     .EQU 0x0000D4 /* Free-Run Timer 0 */
_tcccs0    .EQU 0x0000D7
TCCCS0     .EQU 0x0000D7
_tctdt1    .EQU 0x0000D8
TCTDT1     .EQU 0x0000D8 /* Free-Run Timer 1 */
_tcccs1    .EQU 0x0000DB
TCCCS1     .EQU 0x0000DB
_tctdt2    .EQU 0x0000DC
TCTDT2     .EQU 0x0000DC /* Free-Run Timer 2 */
_tcccs2    .EQU 0x0000DF
TCCCS2     .EQU 0x0000DF
_tctdt3    .EQU 0x0000E0
TCTDT3     .EQU 0x0000E0 /* Free-Run Timer 3 */
_tcccs3    .EQU 0x0000E3
TCCCS3     .EQU 0x0000E3
_ipcp1     .EQU 0x0000E4
IPCP1      .EQU 0x0000E4 /* Input Capture 0-7 */
_ipcp0     .EQU 0x0000E6
IPCP0      .EQU 0x0000E6
_ics01     .EQU 0x0000EB
ICS01      .EQU 0x0000EB
_ipcp3     .EQU 0x0000EC
IPCP3      .EQU 0x0000EC
_ipcp2     .EQU 0x0000EE
IPCP2      .EQU 0x0000EE
_ics23     .EQU 0x0000F3
ICS23      .EQU 0x0000F3
_ipcp5     .EQU 0x0000F4
IPCP5      .EQU 0x0000F4
_ipcp4     .EQU 0x0000F6
IPCP4      .EQU 0x0000F6
_ics45     .EQU 0x0000FB
ICS45      .EQU 0x0000FB
_ipcp7     .EQU 0x0000FC
IPCP7      .EQU 0x0000FC
_ipcp6     .EQU 0x0000FE
IPCP6      .EQU 0x0000FE
_ics67     .EQU 0x000103
ICS67      .EQU 0x000103
_occp1     .EQU 0x000108
OCCP1      .EQU 0x000108 /* Output Compare 0-7 */
_occp0     .EQU 0x00010A
OCCP0      .EQU 0x00010A
_occp3     .EQU 0x00010C
OCCP3      .EQU 0x00010C
_occp2     .EQU 0x00010E
OCCP2      .EQU 0x00010E
_ocs23     .EQU 0x000110
OCS23      .EQU 0x000110
_ocs01     .EQU 0x000112
OCS01      .EQU 0x000112
_occp5     .EQU 0x000114
OCCP5      .EQU 0x000114
_occp4     .EQU 0x000116
OCCP4      .EQU 0x000116
_occp7     .EQU 0x000118
OCCP7      .EQU 0x000118
_occp6     .EQU 0x00011A
OCCP6      .EQU 0x00011A
_ocs67     .EQU 0x00011C
OCS67      .EQU 0x00011C
_ocs45     .EQU 0x00011E
OCS45      .EQU 0x00011E
_eirr2     .EQU 0x000130
EIRR2      .EQU 0x000130 /* External Interrupt 16-23 */
_enir2     .EQU 0x000131
ENIR2      .EQU 0x000131
_elvr2     .EQU 0x000132
ELVR2      .EQU 0x000132
_eirr3     .EQU 0x000134
EIRR3      .EQU 0x000134 /* External Interrupt 24-31 */
_enir3     .EQU 0x000135
ENIR3      .EQU 0x000135
_elvr3     .EQU 0x000136
ELVR3      .EQU 0x000136
_eirr4     .EQU 0x000138
EIRR4      .EQU 0x000138 /* External Interrupt 32-39 */
_enir4     .EQU 0x000139
ENIR4      .EQU 0x000139
_elvr4     .EQU 0x00013A
ELVR4      .EQU 0x00013A
_dacr      .EQU 0x00013D
DACR       .EQU 0x00013D /* DAC */
_dadr0     .EQU 0x00013E
DADR0      .EQU 0x00013E
_dadr1     .EQU 0x000140
DADR1      .EQU 0x000140
_dadbl     .EQU 0x000143
DADBL      .EQU 0x000143
_wtdbl     .EQU 0x000145
WTDBL      .EQU 0x000145 /* Real Time Clock (Watch Timer) */
_wtcr      .EQU 0x000146
WTCR       .EQU 0x000146
_wtbr      .EQU 0x000148
WTBR       .EQU 0x000148
_wthr      .EQU 0x00014C
WTHR       .EQU 0x00014C
_wtmr      .EQU 0x00014D
WTMR       .EQU 0x00014D
_wtsr      .EQU 0x00014E
WTSR       .EQU 0x00014E
_aderh     .EQU 0x000150
ADERH      .EQU 0x000150 /* ADC */
_aderl     .EQU 0x000152
ADERL      .EQU 0x000152
_adcs1     .EQU 0x000154
ADCS1      .EQU 0x000154
_adcs0     .EQU 0x000155
ADCS0      .EQU 0x000155
_adcr1     .EQU 0x000156
ADCR1      .EQU 0x000156
_adcr0     .EQU 0x000157
ADCR0      .EQU 0x000157
_adct1     .EQU 0x000158
ADCT1      .EQU 0x000158
_adct0     .EQU 0x000159
ADCT0      .EQU 0x000159
_adsch     .EQU 0x00015A
ADSCH      .EQU 0x00015A
_adech     .EQU 0x00015B
ADECH      .EQU 0x00015B
_cucr      .EQU 0x00015C
CUCR       .EQU 0x00015C /* Clock Calibration */
_cutd      .EQU 0x00015E
CUTD       .EQU 0x00015E
_cutr1     .EQU 0x000160
CUTR1      .EQU 0x000160
_cutr2     .EQU 0x000162
CUTR2      .EQU 0x000162
_udrc1     .EQU 0x000170
UDRC1      .EQU 0x000170 /* Up/Down Counter 0-1 */
_udrc0     .EQU 0x000171
UDRC0      .EQU 0x000171
_udcr1     .EQU 0x000172
UDCR1      .EQU 0x000172
_udcr0     .EQU 0x000173
UDCR0      .EQU 0x000173
_udcch0    .EQU 0x000174
UDCCH0     .EQU 0x000174
_udccl0    .EQU 0x000175
UDCCL0     .EQU 0x000175
_udcs0     .EQU 0x000177
UDCS0      .EQU 0x000177
_udcch1    .EQU 0x000178
UDCCH1     .EQU 0x000178
_udccl1    .EQU 0x000179
UDCCL1     .EQU 0x000179
_udcs1     .EQU 0x00017B
UDCS1      .EQU 0x00017B
_udrc3     .EQU 0x000180
UDRC3      .EQU 0x000180 /* Up/Down Counter 2-3 */
_udrc2     .EQU 0x000181
UDRC2      .EQU 0x000181
_udcr3     .EQU 0x000182
UDCR3      .EQU 0x000182
_udcr2     .EQU 0x000183
UDCR2      .EQU 0x000183
_udcch2    .EQU 0x000184
UDCCH2     .EQU 0x000184
_udccl2    .EQU 0x000185
UDCCL2     .EQU 0x000185
_udcs2     .EQU 0x000187
UDCS2      .EQU 0x000187
_udcch3    .EQU 0x000188
UDCCH3     .EQU 0x000188
_udccl3    .EQU 0x000189
UDCCL3     .EQU 0x000189
_udcs3     .EQU 0x00018B
UDCS3      .EQU 0x00018B
_ad2erh    .EQU 0x000190
AD2ERH     .EQU 0x000190 /* ADC 2 */
_ad2erl    .EQU 0x000192
AD2ERL     .EQU 0x000192
_ad2cs1    .EQU 0x000194
AD2CS1     .EQU 0x000194
_ad2cs0    .EQU 0x000195
AD2CS0     .EQU 0x000195
_ad2cr1    .EQU 0x000196
AD2CR1     .EQU 0x000196
_ad2cr0    .EQU 0x000197
AD2CR0     .EQU 0x000197
_ad2ct1    .EQU 0x000198
AD2CT1     .EQU 0x000198
_ad2ct0    .EQU 0x000199
AD2CT0     .EQU 0x000199
_ad2sch    .EQU 0x00019A
AD2SCH     .EQU 0x00019A
_ad2ech    .EQU 0x00019B
AD2ECH     .EQU 0x00019B
_cmpr      .EQU 0x0001A0
CMPR       .EQU 0x0001A0 /* Clock Modulator */
_cmcr      .EQU 0x0001A3
CMCR       .EQU 0x0001A3
_cmt1      .EQU 0x0001A4
CMT1       .EQU 0x0001A4
_cmt2      .EQU 0x0001A6
CMT2       .EQU 0x0001A6
_canpre    .EQU 0x0001A8
CANPRE     .EQU 0x0001A8 /* CAN clock control / Ext. Int. Source Sel. */
_eissr     .EQU 0x0001AA
EISSR      .EQU 0x0001AA
_prlh0     .EQU 0x0001B0
PRLH0      .EQU 0x0001B0 /* PPG 0-3 */
_prll0     .EQU 0x0001B1
PRLL0      .EQU 0x0001B1
_prlh1     .EQU 0x0001B2
PRLH1      .EQU 0x0001B2
_prll1     .EQU 0x0001B3
PRLL1      .EQU 0x0001B3
_prlh2     .EQU 0x0001B4
PRLH2      .EQU 0x0001B4
_prll2     .EQU 0x0001B5
PRLL2      .EQU 0x0001B5
_prlh3     .EQU 0x0001B6
PRLH3      .EQU 0x0001B6
_prll3     .EQU 0x0001B7
PRLL3      .EQU 0x0001B7
_ppgc0     .EQU 0x0001B8
PPGC0      .EQU 0x0001B8
_ppgc1     .EQU 0x0001B9
PPGC1      .EQU 0x0001B9
_ppgc2     .EQU 0x0001BA
PPGC2      .EQU 0x0001BA
_ppgc3     .EQU 0x0001BB
PPGC3      .EQU 0x0001BB
_prlh4     .EQU 0x0001C0
PRLH4      .EQU 0x0001C0 /* PPG 4-7 */
_prll4     .EQU 0x0001C1
PRLL4      .EQU 0x0001C1
_prlh5     .EQU 0x0001C2
PRLH5      .EQU 0x0001C2
_prll5     .EQU 0x0001C3
PRLL5      .EQU 0x0001C3
_prlh6     .EQU 0x0001C4
PRLH6      .EQU 0x0001C4
_prll6     .EQU 0x0001C5
PRLL6      .EQU 0x0001C5
_prlh7     .EQU 0x0001C6
PRLH7      .EQU 0x0001C6
_prll7     .EQU 0x0001C7
PRLL7      .EQU 0x0001C7
_ppgc4     .EQU 0x0001C8
PPGC4      .EQU 0x0001C8
_ppgc5     .EQU 0x0001C9
PPGC5      .EQU 0x0001C9
_ppgc6     .EQU 0x0001CA
PPGC6      .EQU 0x0001CA
_ppgc7     .EQU 0x0001CB
PPGC7      .EQU 0x0001CB
_prlh8     .EQU 0x0001D0
PRLH8      .EQU 0x0001D0 /* PPG 8-B */
_prll8     .EQU 0x0001D1
PRLL8      .EQU 0x0001D1
_prlh9     .EQU 0x0001D2
PRLH9      .EQU 0x0001D2
_prll9     .EQU 0x0001D3
PRLL9      .EQU 0x0001D3
_prlha     .EQU 0x0001D4
PRLHA      .EQU 0x0001D4
_prlla     .EQU 0x0001D5
PRLLA      .EQU 0x0001D5
_prlhb     .EQU 0x0001D6
PRLHB      .EQU 0x0001D6
_prllb     .EQU 0x0001D7
PRLLB      .EQU 0x0001D7
_ppgc8     .EQU 0x0001D8
PPGC8      .EQU 0x0001D8
_ppgc9     .EQU 0x0001D9
PPGC9      .EQU 0x0001D9
_ppgca     .EQU 0x0001DA
PPGCA      .EQU 0x0001DA
_ppgcb     .EQU 0x0001DB
PPGCB      .EQU 0x0001DB
_prlhc     .EQU 0x0001E0
PRLHC      .EQU 0x0001E0 /* PPG C-F */
_prllc     .EQU 0x0001E1
PRLLC      .EQU 0x0001E1
_prlhd     .EQU 0x0001E2
PRLHD      .EQU 0x0001E2
_prlld     .EQU 0x0001E3
PRLLD      .EQU 0x0001E3
_prlhe     .EQU 0x0001E4
PRLHE      .EQU 0x0001E4
_prlle     .EQU 0x0001E5
PRLLE      .EQU 0x0001E5
_prlhf     .EQU 0x0001E6
PRLHF      .EQU 0x0001E6
_prllf     .EQU 0x0001E7
PRLLF      .EQU 0x0001E7
_ppgcc     .EQU 0x0001E8
PPGCC      .EQU 0x0001E8
_ppgcd     .EQU 0x0001E9
PPGCD      .EQU 0x0001E9
_ppgce     .EQU 0x0001EA
PPGCE      .EQU 0x0001EA
_ppgcf     .EQU 0x0001EB
PPGCF      .EQU 0x0001EB
_ppgtrg    .EQU 0x0001F0
PPGTRG     .EQU 0x0001F0 /* PPG 0-F Enable / Reverse */
_ppgrevc   .EQU 0x0001F2
PPGREVC    .EQU 0x0001F2
_ppgswap   .EQU 0x0001F4
PPGSWAP    .EQU 0x0001F4 /* PPG 0-F Output Swap */
_cmclkr    .EQU 0x0001F8
CMCLKR     .EQU 0x0001F8 /* Clock Monitor */
_dmaca0    .EQU 0x000200
DMACA0     .EQU 0x000200 /* DMAC */
_dmacb0    .EQU 0x000204
DMACB0     .EQU 0x000204
_dmaca1    .EQU 0x000208
DMACA1     .EQU 0x000208
_dmacb1    .EQU 0x00020C
DMACB1     .EQU 0x00020C
_dmaca2    .EQU 0x000210
DMACA2     .EQU 0x000210
_dmacb2    .EQU 0x000214
DMACB2     .EQU 0x000214
_dmaca3    .EQU 0x000218
DMACA3     .EQU 0x000218
_dmacb3    .EQU 0x00021C
DMACB3     .EQU 0x00021C
_dmaca4    .EQU 0x000220
DMACA4     .EQU 0x000220
_dmacb4    .EQU 0x000224
DMACB4     .EQU 0x000224
_dmacr     .EQU 0x000240
DMACR      .EQU 0x000240
_bsd0      .EQU 0x0003F0
BSD0       .EQU 0x0003F0 /* Bit Search */
_bsd1      .EQU 0x0003F4
BSD1       .EQU 0x0003F4
_bsdc      .EQU 0x0003F8
BSDC       .EQU 0x0003F8
_bsrr      .EQU 0x0003FC
BSRR       .EQU 0x0003FC
_ddr0      .EQU 0x000400
DDR0       .EQU 0x000400 /* Data Direction Register */
_ddr1      .EQU 0x000401
DDR1       .EQU 0x000401
_ddr2      .EQU 0x000402
DDR2       .EQU 0x000402
_ddr3      .EQU 0x000403
DDR3       .EQU 0x000403
_ddr4      .EQU 0x000404
DDR4       .EQU 0x000404
_ddr5      .EQU 0x000405
DDR5       .EQU 0x000405
_ddr6      .EQU 0x000406
DDR6       .EQU 0x000406
_ddr7      .EQU 0x000407
DDR7       .EQU 0x000407
_ddr8      .EQU 0x000408
DDR8       .EQU 0x000408
_ddr9      .EQU 0x000409
DDR9       .EQU 0x000409
_ddra      .EQU 0x00040A
DDRA       .EQU 0x00040A
_ddrb      .EQU 0x00040B
DDRB       .EQU 0x00040B
_ddrc      .EQU 0x00040C
DDRC       .EQU 0x00040C
_ddrd      .EQU 0x00040D
DDRD       .EQU 0x00040D
_ddre      .EQU 0x00040E
DDRE       .EQU 0x00040E
_ddrf      .EQU 0x00040F
DDRF       .EQU 0x00040F
_ddrg      .EQU 0x000410
DDRG       .EQU 0x000410
_pfr0      .EQU 0x000420
PFR0       .EQU 0x000420 /* Port Function Register */
_pfr1      .EQU 0x000421
PFR1       .EQU 0x000421
_pfr2      .EQU 0x000422
PFR2       .EQU 0x000422
_pfr3      .EQU 0x000423
PFR3       .EQU 0x000423
_pfr4      .EQU 0x000424
PFR4       .EQU 0x000424
_pfr5      .EQU 0x000425
PFR5       .EQU 0x000425
_pfr6      .EQU 0x000426
PFR6       .EQU 0x000426
_pfr7      .EQU 0x000427
PFR7       .EQU 0x000427
_pfr8      .EQU 0x000428
PFR8       .EQU 0x000428
_pfr9      .EQU 0x000429
PFR9       .EQU 0x000429
_pfra      .EQU 0x00042A
PFRA       .EQU 0x00042A
_pfrb      .EQU 0x00042B
PFRB       .EQU 0x00042B
_pfrc      .EQU 0x00042C
PFRC       .EQU 0x00042C
_pfrd      .EQU 0x00042D
PFRD       .EQU 0x00042D
_pfre      .EQU 0x00042E
PFRE       .EQU 0x00042E
_pfrf      .EQU 0x00042F
PFRF       .EQU 0x00042F
_pfrg      .EQU 0x000430
PFRG       .EQU 0x000430
_icr00     .EQU 0x000440
ICR00      .EQU 0x000440 /* Interrupt Control Unit */
_icr01     .EQU 0x000441
ICR01      .EQU 0x000441
_icr02     .EQU 0x000442
ICR02      .EQU 0x000442
_icr03     .EQU 0x000443
ICR03      .EQU 0x000443
_icr04     .EQU 0x000444
ICR04      .EQU 0x000444
_icr05     .EQU 0x000445
ICR05      .EQU 0x000445
_icr06     .EQU 0x000446
ICR06      .EQU 0x000446
_icr07     .EQU 0x000447
ICR07      .EQU 0x000447
_icr08     .EQU 0x000448
ICR08      .EQU 0x000448
_icr09     .EQU 0x000449
ICR09      .EQU 0x000449
_icr10     .EQU 0x00044A
ICR10      .EQU 0x00044A
_icr11     .EQU 0x00044B
ICR11      .EQU 0x00044B
_icr12     .EQU 0x00044C
ICR12      .EQU 0x00044C
_icr13     .EQU 0x00044D
ICR13      .EQU 0x00044D
_icr14     .EQU 0x00044E
ICR14      .EQU 0x00044E
_icr15     .EQU 0x00044F
ICR15      .EQU 0x00044F
_icr16     .EQU 0x000450
ICR16      .EQU 0x000450
_icr17     .EQU 0x000451
ICR17      .EQU 0x000451
_icr18     .EQU 0x000452
ICR18      .EQU 0x000452
_icr19     .EQU 0x000453
ICR19      .EQU 0x000453
_icr20     .EQU 0x000454
ICR20      .EQU 0x000454
_icr21     .EQU 0x000455
ICR21      .EQU 0x000455
_icr22     .EQU 0x000456
ICR22      .EQU 0x000456
_icr23     .EQU 0x000457
ICR23      .EQU 0x000457
_icr24     .EQU 0x000458
ICR24      .EQU 0x000458
_icr25     .EQU 0x000459
ICR25      .EQU 0x000459
_icr26     .EQU 0x00045A
ICR26      .EQU 0x00045A
_icr27     .EQU 0x00045B
ICR27      .EQU 0x00045B
_icr28     .EQU 0x00045C
ICR28      .EQU 0x00045C
_icr29     .EQU 0x00045D
ICR29      .EQU 0x00045D
_icr30     .EQU 0x00045E
ICR30      .EQU 0x00045E
_icr31     .EQU 0x00045F
ICR31      .EQU 0x00045F
_icr32     .EQU 0x000460
ICR32      .EQU 0x000460
_icr33     .EQU 0x000461
ICR33      .EQU 0x000461
_icr34     .EQU 0x000462
ICR34      .EQU 0x000462
_icr35     .EQU 0x000463
ICR35      .EQU 0x000463
_icr36     .EQU 0x000464
ICR36      .EQU 0x000464
_icr37     .EQU 0x000465
ICR37      .EQU 0x000465
_icr38     .EQU 0x000466
ICR38      .EQU 0x000466
_icr39     .EQU 0x000467
ICR39      .EQU 0x000467
_icr40     .EQU 0x000468
ICR40      .EQU 0x000468
_icr41     .EQU 0x000469
ICR41      .EQU 0x000469
_icr42     .EQU 0x00046A
ICR42      .EQU 0x00046A
_icr43     .EQU 0x00046B
ICR43      .EQU 0x00046B
_icr44     .EQU 0x00046C
ICR44      .EQU 0x00046C
_icr45     .EQU 0x00046D
ICR45      .EQU 0x00046D
_icr46     .EQU 0x00046E
ICR46      .EQU 0x00046E
_icr47     .EQU 0x00046F
ICR47      .EQU 0x00046F
_rsrr      .EQU 0x000480
RSRR       .EQU 0x000480 /* Clock Control Unit */
_stcr      .EQU 0x000481
STCR       .EQU 0x000481
_tbcr      .EQU 0x000482
TBCR       .EQU 0x000482
_ctbr      .EQU 0x000483
CTBR       .EQU 0x000483
_clkr      .EQU 0x000484
CLKR       .EQU 0x000484
_wpr       .EQU 0x000485
WPR        .EQU 0x000485
_divr0     .EQU 0x000486
DIVR0      .EQU 0x000486
_divr1     .EQU 0x000487
DIVR1      .EQU 0x000487
_osccr     .EQU 0x00048A
OSCCR      .EQU 0x00048A
_oscr      .EQU 0x000490
OSCR       .EQU 0x000490 /* Stb. Wait Timer */
_csvcr     .EQU 0x0004AD
CSVCR      .EQU 0x0004AD /* Clock-Supervisor */
_pper0     .EQU 0x000500
PPER0      .EQU 0x000500 /* Pull-Up/Down Enable Register */
_pper1     .EQU 0x000501
PPER1      .EQU 0x000501
_pper2     .EQU 0x000502
PPER2      .EQU 0x000502
_pper3     .EQU 0x000503
PPER3      .EQU 0x000503
_pper4     .EQU 0x000504
PPER4      .EQU 0x000504
_pper5     .EQU 0x000505
PPER5      .EQU 0x000505
_pper6     .EQU 0x000506
PPER6      .EQU 0x000506
_pper7     .EQU 0x000507
PPER7      .EQU 0x000507
_pper8     .EQU 0x000508
PPER8      .EQU 0x000508
_pper9     .EQU 0x000509
PPER9      .EQU 0x000509
_ppera     .EQU 0x00050A
PPERA      .EQU 0x00050A
_pperb     .EQU 0x00050B
PPERB      .EQU 0x00050B
_pperc     .EQU 0x00050C
PPERC      .EQU 0x00050C
_pperd     .EQU 0x00050D
PPERD      .EQU 0x00050D
_ppere     .EQU 0x00050E
PPERE      .EQU 0x00050E
_pperf     .EQU 0x00050F
PPERF      .EQU 0x00050F
_pperg     .EQU 0x000510
PPERG      .EQU 0x000510
_ppcr0     .EQU 0x000520
PPCR0      .EQU 0x000520 /* Pull-Up/Down  Control Register */
_ppcr1     .EQU 0x000521
PPCR1      .EQU 0x000521
_ppcr2     .EQU 0x000522
PPCR2      .EQU 0x000522
_ppcr3     .EQU 0x000523
PPCR3      .EQU 0x000523
_ppcr4     .EQU 0x000524
PPCR4      .EQU 0x000524
_ppcr5     .EQU 0x000525
PPCR5      .EQU 0x000525
_ppcr6     .EQU 0x000526
PPCR6      .EQU 0x000526
_ppcr7     .EQU 0x000527
PPCR7      .EQU 0x000527
_ppcr8     .EQU 0x000528
PPCR8      .EQU 0x000528
_ppcr9     .EQU 0x000529
PPCR9      .EQU 0x000529
_ppcra     .EQU 0x00052A
PPCRA      .EQU 0x00052A
_ppcrb     .EQU 0x00052B
PPCRB      .EQU 0x00052B
_ppcrc     .EQU 0x00052C
PPCRC      .EQU 0x00052C
_ppcrd     .EQU 0x00052D
PPCRD      .EQU 0x00052D
_ppcre     .EQU 0x00052E
PPCRE      .EQU 0x00052E
_ppcrf     .EQU 0x00052F
PPCRF      .EQU 0x00052F
_ppcrg     .EQU 0x000530
PPCRG      .EQU 0x000530
_pilr0     .EQU 0x000540
PILR0      .EQU 0x000540 /* Port Input Level select Registers */
_pilr1     .EQU 0x000541
PILR1      .EQU 0x000541
_pilr2     .EQU 0x000542
PILR2      .EQU 0x000542
_pilr3     .EQU 0x000543
PILR3      .EQU 0x000543
_pilr4     .EQU 0x000544
PILR4      .EQU 0x000544
_pilr5     .EQU 0x000545
PILR5      .EQU 0x000545
_pilr6     .EQU 0x000546
PILR6      .EQU 0x000546
_pilr7     .EQU 0x000547
PILR7      .EQU 0x000547
_pilr8     .EQU 0x000548
PILR8      .EQU 0x000548
_pilr9     .EQU 0x000549
PILR9      .EQU 0x000549
_pilra     .EQU 0x00054A
PILRA      .EQU 0x00054A
_pilrb     .EQU 0x00054B
PILRB      .EQU 0x00054B
_pilrc     .EQU 0x00054C
PILRC      .EQU 0x00054C
_pilrd     .EQU 0x00054D
PILRD      .EQU 0x00054D
_pilre     .EQU 0x00054E
PILRE      .EQU 0x00054E
_pilrf     .EQU 0x00054F
PILRF      .EQU 0x00054F
_pilrg     .EQU 0x000550
PILRG      .EQU 0x000550
_ibcr0     .EQU 0x000560
IBCR0      .EQU 0x000560 /* I2C 0 */
_ibsr0     .EQU 0x000561
IBSR0      .EQU 0x000561
_itbah0    .EQU 0x000562
ITBAH0     .EQU 0x000562
_itbal0    .EQU 0x000563
ITBAL0     .EQU 0x000563
_itmkh0    .EQU 0x000564
ITMKH0     .EQU 0x000564
_itmkl0    .EQU 0x000565
ITMKL0     .EQU 0x000565
_ismk0     .EQU 0x000566
ISMK0      .EQU 0x000566
_isba0     .EQU 0x000567
ISBA0      .EQU 0x000567
_idar0     .EQU 0x000569
IDAR0      .EQU 0x000569
_iccr0     .EQU 0x00056A
ICCR0      .EQU 0x00056A
_ibcr1     .EQU 0x000570
IBCR1      .EQU 0x000570 /* I2C 1 */
_ibsr1     .EQU 0x000571
IBSR1      .EQU 0x000571
_itbah1    .EQU 0x000572
ITBAH1     .EQU 0x000572
_itbal1    .EQU 0x000573
ITBAL1     .EQU 0x000573
_itmkh1    .EQU 0x000574
ITMKH1     .EQU 0x000574
_itmkl1    .EQU 0x000575
ITMKL1     .EQU 0x000575
_ismk1     .EQU 0x000576
ISMK1      .EQU 0x000576
_isba1     .EQU 0x000577
ISBA1      .EQU 0x000577
_idar1     .EQU 0x000579
IDAR1      .EQU 0x000579
_iccr1     .EQU 0x00057A
ICCR1      .EQU 0x00057A
_ibcr2     .EQU 0x000580
IBCR2      .EQU 0x000580 /* I2C 2 */
_ibsr2     .EQU 0x000581
IBSR2      .EQU 0x000581
_itbah2    .EQU 0x000582
ITBAH2     .EQU 0x000582
_itbal2    .EQU 0x000583
ITBAL2     .EQU 0x000583
_itmkh2    .EQU 0x000584
ITMKH2     .EQU 0x000584
_itmkl2    .EQU 0x000585
ITMKL2     .EQU 0x000585
_ismk2     .EQU 0x000586
ISMK2      .EQU 0x000586
_isba2     .EQU 0x000587
ISBA2      .EQU 0x000587
_idar2     .EQU 0x000589
IDAR2      .EQU 0x000589
_iccr2     .EQU 0x00058A
ICCR2      .EQU 0x00058A
_hwdcs     .EQU 0x0005FD
HWDCS      .EQU 0x0005FD /* Hardware-Watchdog */
_epfr0     .EQU 0x000600
EPFR0      .EQU 0x000600 /* Extra Port Function Register */
_epfr1     .EQU 0x000601
EPFR1      .EQU 0x000601
_epfr2     .EQU 0x000602
EPFR2      .EQU 0x000602
_epfr3     .EQU 0x000603
EPFR3      .EQU 0x000603
_epfr4     .EQU 0x000604
EPFR4      .EQU 0x000604
_epfr5     .EQU 0x000605
EPFR5      .EQU 0x000605
_epfr6     .EQU 0x000606
EPFR6      .EQU 0x000606
_epfr7     .EQU 0x000607
EPFR7      .EQU 0x000607
_epfr8     .EQU 0x000608
EPFR8      .EQU 0x000608
_epfr9     .EQU 0x000609
EPFR9      .EQU 0x000609
_epfra     .EQU 0x00060A
EPFRA      .EQU 0x00060A
_epfrb     .EQU 0x00060B
EPFRB      .EQU 0x00060B
_epfrc     .EQU 0x00060C
EPFRC      .EQU 0x00060C
_epfrd     .EQU 0x00060D
EPFRD      .EQU 0x00060D
_epfre     .EQU 0x00060E
EPFRE      .EQU 0x00060E
_epfrf     .EQU 0x00060F
EPFRF      .EQU 0x00060F
_epfrg     .EQU 0x000610
EPFRG      .EQU 0x000610
_pidr0     .EQU 0x000620
PIDR0      .EQU 0x000620 /* Port Input Direct data Registers */
_pidr1     .EQU 0x000621
PIDR1      .EQU 0x000621
_pidr2     .EQU 0x000622
PIDR2      .EQU 0x000622
_pidr3     .EQU 0x000623
PIDR3      .EQU 0x000623
_pidr4     .EQU 0x000624
PIDR4      .EQU 0x000624
_pidr5     .EQU 0x000625
PIDR5      .EQU 0x000625
_pidr6     .EQU 0x000626
PIDR6      .EQU 0x000626
_pidr7     .EQU 0x000627
PIDR7      .EQU 0x000627
_pidr8     .EQU 0x000628
PIDR8      .EQU 0x000628
_pidr9     .EQU 0x000629
PIDR9      .EQU 0x000629
_pidra     .EQU 0x00062A
PIDRA      .EQU 0x00062A
_pidrb     .EQU 0x00062B
PIDRB      .EQU 0x00062B
_pidrc     .EQU 0x00062C
PIDRC      .EQU 0x00062C
_pidrd     .EQU 0x00062D
PIDRD      .EQU 0x00062D
_pidre     .EQU 0x00062E
PIDRE      .EQU 0x00062E
_pidrf     .EQU 0x00062F
PIDRF      .EQU 0x00062F
_pidrg     .EQU 0x000630
PIDRG      .EQU 0x000630
_asr0      .EQU 0x000640
ASR0       .EQU 0x000640 /* T-Unit */
_acr0      .EQU 0x000642
ACR0       .EQU 0x000642
_asr1      .EQU 0x000644
ASR1       .EQU 0x000644
_acr1      .EQU 0x000646
ACR1       .EQU 0x000646
_asr2      .EQU 0x000648
ASR2       .EQU 0x000648
_acr2      .EQU 0x00064A
ACR2       .EQU 0x00064A
_asr3      .EQU 0x00064C
ASR3       .EQU 0x00064C
_acr3      .EQU 0x00064E
ACR3       .EQU 0x00064E
_awr0      .EQU 0x000660
AWR0       .EQU 0x000660
_awr1      .EQU 0x000662
AWR1       .EQU 0x000662
_awr2      .EQU 0x000664
AWR2       .EQU 0x000664
_awr3      .EQU 0x000666
AWR3       .EQU 0x000666
_cser      .EQU 0x000680
CSER       .EQU 0x000680
_tcr       .EQU 0x000683
TCR        .EQU 0x000683
_modr      .EQU 0x0007FD
MODR       .EQU 0x0007FD /* Mode Register */
_dmasa0    .EQU 0x001000
DMASA0     .EQU 0x001000 /* DMAC */
_dmada0    .EQU 0x001004
DMADA0     .EQU 0x001004
_dmasa1    .EQU 0x001008
DMASA1     .EQU 0x001008
_dmada1    .EQU 0x00100C
DMADA1     .EQU 0x00100C
_dmasa2    .EQU 0x001010
DMASA2     .EQU 0x001010
_dmada2    .EQU 0x001014
DMADA2     .EQU 0x001014
_dmasa3    .EQU 0x001018
DMASA3     .EQU 0x001018
_dmada3    .EQU 0x00101C
DMADA3     .EQU 0x00101C
_dmasa4    .EQU 0x001020
DMASA4     .EQU 0x001020
_dmada4    .EQU 0x001024
DMADA4     .EQU 0x001024
_flcr      .EQU 0x007000
FLCR       .EQU 0x007000 /* Flash I/F */
_flwc      .EQU 0x007004
FLWC       .EQU 0x007004
_ctrlr0    .EQU 0x020000
CTRLR0     .EQU 0x020000 /* CAN 0 Control Register */
_statr0    .EQU 0x020002
STATR0     .EQU 0x020002
_errcnt0   .EQU 0x020004
ERRCNT0    .EQU 0x020004
_btr0  .EQU 0x020006
BTR0   .EQU 0x020006
_intr0     .EQU 0x020008
INTR0      .EQU 0x020008
_testr0    .EQU 0x02000A
TESTR0     .EQU 0x02000A
_brper0    .EQU 0x02000C
BRPER0     .EQU 0x02000C
_if1creq0  .EQU 0x020010
IF1CREQ0   .EQU 0x020010 /* CAN 0 IF 1 */
_if1cmsk0  .EQU 0x020012
IF1CMSK0   .EQU 0x020012
_if1msk120  .EQU 0x020014
IF1MSK120   .EQU 0x020014
_if1msk20  .EQU 0x020014
IF1MSK20   .EQU 0x020014
_if1msk10  .EQU 0x020016
IF1MSK10   .EQU 0x020016
_if1arb120  .EQU 0x020018
IF1ARB120   .EQU 0x020018
_if1arb20  .EQU 0x020018
IF1ARB20   .EQU 0x020018
_if1arb10  .EQU 0x02001A
IF1ARB10   .EQU 0x02001A
_if1mctr0  .EQU 0x02001C
IF1MCTR0   .EQU 0x02001C
_if1dta120  .EQU 0x020020
IF1DTA120   .EQU 0x020020
_if1dta10  .EQU 0x020020
IF1DTA10   .EQU 0x020020
_if1dta20  .EQU 0x020022
IF1DTA20   .EQU 0x020022
_if1dtb120  .EQU 0x020024
IF1DTB120   .EQU 0x020024
_if1dtb10  .EQU 0x020024
IF1DTB10   .EQU 0x020024
_if1dtb20  .EQU 0x020026
IF1DTB20   .EQU 0x020026
_if1dta_swp120  .EQU 0x020030
IF1DTA_SWP120   .EQU 0x020030
_if1dta_swp20  .EQU 0x020030
IF1DTA_SWP20   .EQU 0x020030
_if1dta_swp10  .EQU 0x020032
IF1DTA_SWP10   .EQU 0x020032
_if1dtb_swp120  .EQU 0x020034
IF1DTB_SWP120   .EQU 0x020034
_if1dtb_swp20  .EQU 0x020034
IF1DTB_SWP20   .EQU 0x020034
_if1dtb_swp10  .EQU 0x020036
IF1DTB_SWP10   .EQU 0x020036
_if2creq0  .EQU 0x020040
IF2CREQ0   .EQU 0x020040 /* CAN 0 IF 2 */
_if2cmsk0  .EQU 0x020042
IF2CMSK0   .EQU 0x020042
_if2msk120  .EQU 0x020044
IF2MSK120   .EQU 0x020044
_if2msk20  .EQU 0x020044
IF2MSK20   .EQU 0x020044
_if2msk10  .EQU 0x020046
IF2MSK10   .EQU 0x020046
_if2arb120  .EQU 0x020048
IF2ARB120   .EQU 0x020048
_if2arb20  .EQU 0x020048
IF2ARB20   .EQU 0x020048
_if2arb10  .EQU 0x02004A
IF2ARB10   .EQU 0x02004A
_if2mctr0  .EQU 0x02004C
IF2MCTR0   .EQU 0x02004C
_if2dta120  .EQU 0x020050
IF2DTA120   .EQU 0x020050
_if2dta10  .EQU 0x020050
IF2DTA10   .EQU 0x020050
_if2dta20  .EQU 0x020052
IF2DTA20   .EQU 0x020052
_if2dtb120  .EQU 0x020054
IF2DTB120   .EQU 0x020054
_if2dtb10  .EQU 0x020054
IF2DTB10   .EQU 0x020054
_if2dtb20  .EQU 0x020056
IF2DTB20   .EQU 0x020056
_if2dta_swp120  .EQU 0x020060
IF2DTA_SWP120   .EQU 0x020060
_if2dta_swp20  .EQU 0x020060
IF2DTA_SWP20   .EQU 0x020060
_if2dta_swp10  .EQU 0x020062
IF2DTA_SWP10   .EQU 0x020062
_if2dtb_swp120  .EQU 0x020064
IF2DTB_SWP120   .EQU 0x020064
_if2dtb_swp20  .EQU 0x020064
IF2DTB_SWP20   .EQU 0x020064
_if2dtb_swp10  .EQU 0x020066
IF2DTB_SWP10   .EQU 0x020066
_treqr120  .EQU 0x020080
TREQR120   .EQU 0x020080 /* CAN 0 Status flags */
_treqr20   .EQU 0x020080
TREQR20    .EQU 0x020080
_treqr10   .EQU 0x020082
TREQR10    .EQU 0x020082
_treqr340  .EQU 0x020084
TREQR340   .EQU 0x020084
_treqr40   .EQU 0x020084
TREQR40    .EQU 0x020084
_treqr30   .EQU 0x020086
TREQR30    .EQU 0x020086
_newdt120  .EQU 0x020090
NEWDT120   .EQU 0x020090
_newdt20   .EQU 0x020090
NEWDT20    .EQU 0x020090
_newdt10   .EQU 0x020092
NEWDT10    .EQU 0x020092
_newdt340  .EQU 0x020094
NEWDT340   .EQU 0x020094
_newdt40   .EQU 0x020094
NEWDT40    .EQU 0x020094
_newdt30   .EQU 0x020096
NEWDT30    .EQU 0x020096
_intpnd120  .EQU 0x0200A0
INTPND120   .EQU 0x0200A0
_intpnd20  .EQU 0x0200A0
INTPND20   .EQU 0x0200A0
_intpnd10  .EQU 0x0200A2
INTPND10   .EQU 0x0200A2
_intpnd340  .EQU 0x0200A4
INTPND340   .EQU 0x0200A4
_intpnd40  .EQU 0x0200A4
INTPND40   .EQU 0x0200A4
_intpnd30  .EQU 0x0200A6
INTPND30   .EQU 0x0200A6
_msgval120  .EQU 0x0200B0
MSGVAL120   .EQU 0x0200B0
_msgval20  .EQU 0x0200B0
MSGVAL20   .EQU 0x0200B0
_msgval10  .EQU 0x0200B2
MSGVAL10   .EQU 0x0200B2
_msgval340  .EQU 0x0200B4
MSGVAL340   .EQU 0x0200B4
_msgval40  .EQU 0x0200B4
MSGVAL40   .EQU 0x0200B4
_msgval30  .EQU 0x0200B6
MSGVAL30   .EQU 0x0200B6
_ctrlr1    .EQU 0x020100
CTRLR1     .EQU 0x020100 /* CAN 1 Control Register */
_statr1    .EQU 0x020102
STATR1     .EQU 0x020102
_errcnt1   .EQU 0x020104
ERRCNT1    .EQU 0x020104
_btr1  .EQU 0x020106
BTR1   .EQU 0x020106
_intr1     .EQU 0x020108
INTR1      .EQU 0x020108
_testr1    .EQU 0x02010A
TESTR1     .EQU 0x02010A
_brper1    .EQU 0x02010C
BRPER1     .EQU 0x02010C
_if1creq1  .EQU 0x020110
IF1CREQ1   .EQU 0x020110 /* CAN 1 IF 1 */
_if1cmsk1  .EQU 0x020112
IF1CMSK1   .EQU 0x020112
_if1msk121  .EQU 0x020114
IF1MSK121   .EQU 0x020114
_if1msk21  .EQU 0x020114
IF1MSK21   .EQU 0x020114
_if1msk11  .EQU 0x020116
IF1MSK11   .EQU 0x020116
_if1arb121  .EQU 0x020118
IF1ARB121   .EQU 0x020118
_if1arb21  .EQU 0x020118
IF1ARB21   .EQU 0x020118
_if1arb11  .EQU 0x02011A
IF1ARB11   .EQU 0x02011A
_if1mctr1  .EQU 0x02011C
IF1MCTR1   .EQU 0x02011C
_if1dta121  .EQU 0x020120
IF1DTA121   .EQU 0x020120
_if1dta11  .EQU 0x020120
IF1DTA11   .EQU 0x020120
_if1dta21  .EQU 0x020122
IF1DTA21   .EQU 0x020122
_if1dtb121  .EQU 0x020124
IF1DTB121   .EQU 0x020124
_if1dtb11  .EQU 0x020124
IF1DTB11   .EQU 0x020124
_if1dtb21  .EQU 0x020126
IF1DTB21   .EQU 0x020126
_if1dta_swp121  .EQU 0x020130
IF1DTA_SWP121   .EQU 0x020130
_if1dta_swp21  .EQU 0x020130
IF1DTA_SWP21   .EQU 0x020130
_if1dta_swp11  .EQU 0x020132
IF1DTA_SWP11   .EQU 0x020132
_if1dtb_swp121  .EQU 0x020134
IF1DTB_SWP121   .EQU 0x020134
_if1dtb_swp21  .EQU 0x020134
IF1DTB_SWP21   .EQU 0x020134
_if1dtb_swp11  .EQU 0x020136
IF1DTB_SWP11   .EQU 0x020136
_if2creq1  .EQU 0x020140
IF2CREQ1   .EQU 0x020140 /* CAN 1 IF 2 */
_if2cmsk1  .EQU 0x020142
IF2CMSK1   .EQU 0x020142
_if2msk121  .EQU 0x020144
IF2MSK121   .EQU 0x020144
_if2msk21  .EQU 0x020144
IF2MSK21   .EQU 0x020144
_if2msk11  .EQU 0x020146
IF2MSK11   .EQU 0x020146
_if2arb121  .EQU 0x020148
IF2ARB121   .EQU 0x020148
_if2arb21  .EQU 0x020148
IF2ARB21   .EQU 0x020148
_if2arb11  .EQU 0x02014A
IF2ARB11   .EQU 0x02014A
_if2mctr1  .EQU 0x02014C
IF2MCTR1   .EQU 0x02014C
_if2dta121  .EQU 0x020150
IF2DTA121   .EQU 0x020150
_if2dta11  .EQU 0x020150
IF2DTA11   .EQU 0x020150
_if2dta21  .EQU 0x020152
IF2DTA21   .EQU 0x020152
_if2dtb121  .EQU 0x020154
IF2DTB121   .EQU 0x020154
_if2dtb11  .EQU 0x020154
IF2DTB11   .EQU 0x020154
_if2dtb21  .EQU 0x020156
IF2DTB21   .EQU 0x020156
_if2dta_swp121  .EQU 0x020160
IF2DTA_SWP121   .EQU 0x020160
_if2dta_swp21  .EQU 0x020160
IF2DTA_SWP21   .EQU 0x020160
_if2dta_swp11  .EQU 0x020162
IF2DTA_SWP11   .EQU 0x020162
_if2dtb_swp121  .EQU 0x020164
IF2DTB_SWP121   .EQU 0x020164
_if2dtb_swp21  .EQU 0x020164
IF2DTB_SWP21   .EQU 0x020164
_if2dtb_swp11  .EQU 0x020166
IF2DTB_SWP11   .EQU 0x020166
_treqr121  .EQU 0x020180
TREQR121   .EQU 0x020180 /* CAN 1 Status flags */
_treqr21   .EQU 0x020180
TREQR21    .EQU 0x020180
_treqr11   .EQU 0x020182
TREQR11    .EQU 0x020182
_treqr341  .EQU 0x020184
TREQR341   .EQU 0x020184
_treqr41   .EQU 0x020184
TREQR41    .EQU 0x020184
_treqr31   .EQU 0x020186
TREQR31    .EQU 0x020186
_newdt121  .EQU 0x020190
NEWDT121   .EQU 0x020190
_newdt21   .EQU 0x020190
NEWDT21    .EQU 0x020190
_newdt11   .EQU 0x020192
NEWDT11    .EQU 0x020192
_newdt341  .EQU 0x020194
NEWDT341   .EQU 0x020194
_newdt41   .EQU 0x020194
NEWDT41    .EQU 0x020194
_newdt31   .EQU 0x020196
NEWDT31    .EQU 0x020196
_intpnd121  .EQU 0x0201A0
INTPND121   .EQU 0x0201A0
_intpnd21  .EQU 0x0201A0
INTPND21   .EQU 0x0201A0
_intpnd11  .EQU 0x0201A2
INTPND11   .EQU 0x0201A2
_intpnd341  .EQU 0x0201A4
INTPND341   .EQU 0x0201A4
_intpnd41  .EQU 0x0201A4
INTPND41   .EQU 0x0201A4
_intpnd31  .EQU 0x0201A6
INTPND31   .EQU 0x0201A6
_msgval121  .EQU 0x0201B0
MSGVAL121   .EQU 0x0201B0
_msgval21  .EQU 0x0201B0
MSGVAL21   .EQU 0x0201B0
_msgval11  .EQU 0x0201B2
MSGVAL11   .EQU 0x0201B2
_msgval341  .EQU 0x0201B4
MSGVAL341   .EQU 0x0201B4
_msgval41  .EQU 0x0201B4
MSGVAL41   .EQU 0x0201B4
_msgval31  .EQU 0x0201B6
MSGVAL31   .EQU 0x0201B6
_ctrlr2    .EQU 0x020200
CTRLR2     .EQU 0x020200 /* CAN 2 Control Register */
_statr2    .EQU 0x020202
STATR2     .EQU 0x020202
_errcnt2   .EQU 0x020204
ERRCNT2    .EQU 0x020204
_btr2  .EQU 0x020206
BTR2   .EQU 0x020206
_intr2     .EQU 0x020208
INTR2      .EQU 0x020208
_testr2    .EQU 0x02020A
TESTR2     .EQU 0x02020A
_brper2    .EQU 0x02020C
BRPER2     .EQU 0x02020C
_if1creq2  .EQU 0x020210
IF1CREQ2   .EQU 0x020210 /* CAN 2 IF 1 */
_if1cmsk2  .EQU 0x020212
IF1CMSK2   .EQU 0x020212
_if1msk122  .EQU 0x020214
IF1MSK122   .EQU 0x020214
_if1msk22  .EQU 0x020214
IF1MSK22   .EQU 0x020214
_if1msk12  .EQU 0x020216
IF1MSK12   .EQU 0x020216
_if1arb122  .EQU 0x020218
IF1ARB122   .EQU 0x020218
_if1arb22  .EQU 0x020218
IF1ARB22   .EQU 0x020218
_if1arb12  .EQU 0x02021A
IF1ARB12   .EQU 0x02021A
_if1mctr2  .EQU 0x02021C
IF1MCTR2   .EQU 0x02021C
_if1dta122  .EQU 0x020220
IF1DTA122   .EQU 0x020220
_if1dta12  .EQU 0x020220
IF1DTA12   .EQU 0x020220
_if1dta22  .EQU 0x020222
IF1DTA22   .EQU 0x020222
_if1dtb122  .EQU 0x020224
IF1DTB122   .EQU 0x020224
_if1dtb12  .EQU 0x020224
IF1DTB12   .EQU 0x020224
_if1dtb22  .EQU 0x020226
IF1DTB22   .EQU 0x020226
_if1dta_swp122  .EQU 0x020230
IF1DTA_SWP122   .EQU 0x020230
_if1dta_swp22  .EQU 0x020230
IF1DTA_SWP22   .EQU 0x020230
_if1dta_swp12  .EQU 0x020232
IF1DTA_SWP12   .EQU 0x020232
_if1dtb_swp122  .EQU 0x020234
IF1DTB_SWP122   .EQU 0x020234
_if1dtb_swp22  .EQU 0x020234
IF1DTB_SWP22   .EQU 0x020234
_if1dtb_swp12  .EQU 0x020236
IF1DTB_SWP12   .EQU 0x020236
_if2creq2  .EQU 0x020240
IF2CREQ2   .EQU 0x020240 /* CAN 2 IF 2 */
_if2cmsk2  .EQU 0x020242
IF2CMSK2   .EQU 0x020242
_if2msk122  .EQU 0x020244
IF2MSK122   .EQU 0x020244
_if2msk22  .EQU 0x020244
IF2MSK22   .EQU 0x020244
_if2msk12  .EQU 0x020246
IF2MSK12   .EQU 0x020246
_if2arb122  .EQU 0x020248
IF2ARB122   .EQU 0x020248
_if2arb22  .EQU 0x020248
IF2ARB22   .EQU 0x020248
_if2arb12  .EQU 0x02024A
IF2ARB12   .EQU 0x02024A
_if2mctr2  .EQU 0x02024C
IF2MCTR2   .EQU 0x02024C
_if2dta122  .EQU 0x020250
IF2DTA122   .EQU 0x020250
_if2dta12  .EQU 0x020250
IF2DTA12   .EQU 0x020250
_if2dta22  .EQU 0x020252
IF2DTA22   .EQU 0x020252
_if2dtb122  .EQU 0x020254
IF2DTB122   .EQU 0x020254
_if2dtb12  .EQU 0x020254
IF2DTB12   .EQU 0x020254
_if2dtb22  .EQU 0x020256
IF2DTB22   .EQU 0x020256
_if2dta_swp122  .EQU 0x020260
IF2DTA_SWP122   .EQU 0x020260
_if2dta_swp22  .EQU 0x020260
IF2DTA_SWP22   .EQU 0x020260
_if2dta_swp12  .EQU 0x020262
IF2DTA_SWP12   .EQU 0x020262
_if2dtb_swp122  .EQU 0x020264
IF2DTB_SWP122   .EQU 0x020264
_if2dtb_swp22  .EQU 0x020264
IF2DTB_SWP22   .EQU 0x020264
_if2dtb_swp12  .EQU 0x020266
IF2DTB_SWP12   .EQU 0x020266
_treqr122  .EQU 0x020280
TREQR122   .EQU 0x020280 /* CAN 2 Status flags */
_treqr22   .EQU 0x020280
TREQR22    .EQU 0x020280
_treqr12   .EQU 0x020282
TREQR12    .EQU 0x020282
_treqr342  .EQU 0x020284
TREQR342   .EQU 0x020284
_treqr42   .EQU 0x020284
TREQR42    .EQU 0x020284
_treqr32   .EQU 0x020286
TREQR32    .EQU 0x020286
_newdt122  .EQU 0x020290
NEWDT122   .EQU 0x020290
_newdt22   .EQU 0x020290
NEWDT22    .EQU 0x020290
_newdt12   .EQU 0x020292
NEWDT12    .EQU 0x020292
_newdt342  .EQU 0x020294
NEWDT342   .EQU 0x020294
_newdt42   .EQU 0x020294
NEWDT42    .EQU 0x020294
_newdt32   .EQU 0x020296
NEWDT32    .EQU 0x020296
_intpnd122  .EQU 0x0202A0
INTPND122   .EQU 0x0202A0
_intpnd22  .EQU 0x0202A0
INTPND22   .EQU 0x0202A0
_intpnd12  .EQU 0x0202A2
INTPND12   .EQU 0x0202A2
_intpnd342  .EQU 0x0202A4
INTPND342   .EQU 0x0202A4
_intpnd42  .EQU 0x0202A4
INTPND42   .EQU 0x0202A4
_intpnd32  .EQU 0x0202A6
INTPND32   .EQU 0x0202A6
_msgval122  .EQU 0x0202B0
MSGVAL122   .EQU 0x0202B0
_msgval22  .EQU 0x0202B0
MSGVAL22   .EQU 0x0202B0
_msgval12  .EQU 0x0202B2
MSGVAL12   .EQU 0x0202B2
_msgval342  .EQU 0x0202B4
MSGVAL342   .EQU 0x0202B4
_msgval42  .EQU 0x0202B4
MSGVAL42   .EQU 0x0202B4
_msgval32  .EQU 0x0202B6
MSGVAL32   .EQU 0x0202B6
#pragma endasm
#else

#ifndef _MB91XXX_H
#define _MB91XXX_H

#ifdef  __FASM__ 
#pragma asm
 .IMPORT _pdr0,     _pdr1,     _pdr2,     _pdr3,     _pdr4,     _pdr5
 .IMPORT _pdr6,     _pdr7,     _pdr8,     _pdr9,     _pdra,     _pdrb
 .IMPORT _pdrc,     _pdrd,     _pdre,     _pdrf,     _pdrg,     _eirr0
 .IMPORT _enir0,    _elvr0,    _dicr,     _hrcl,     _tmrlr0,   _tmr0
 .IMPORT _tmcsr0,   _tmrlr1,   _tmr1,     _tmcsr1,   _tmrlr2,   _tmr2
 .IMPORT _tmcsr2,   _scr0,     _smr0,     _ssr0,     _rdr0,     _tdr0
 .IMPORT _escr0,    _eccr0,    _bgr0,     _bgr10,    _bgr00,    _scr5
 .IMPORT _smr5,     _ssr5,     _rdr5,     _tdr5,     _escr5,    _eccr5
 .IMPORT _bgr5,     _bgr15,    _bgr05,    _scr6,     _smr6,     _ssr6
 .IMPORT _rdr6,     _tdr6,     _escr6,    _eccr6,    _bgr6,     _bgr16
 .IMPORT _bgr06,    _scr1,     _smr1,     _ssr1,     _rdr1,     _tdr1
 .IMPORT _escr1,    _eccr1,    _bgr1,     _bgr11,    _bgr01,    _scr2
 .IMPORT _smr2,     _ssr2,     _rdr2,     _tdr2,     _escr2,    _eccr2
 .IMPORT _bgr2,     _bgr12,    _bgr02,    _scr3,     _smr3,     _ssr3
 .IMPORT _rdr3,     _tdr3,     _escr3,    _eccr3,    _bgr3,     _bgr13
 .IMPORT _bgr03,    _scr4,     _smr4,     _ssr4,     _rdr4,     _tdr4
 .IMPORT _escr4,    _eccr4,    _bgr4,     _bgr14,    _bgr04,    _eirr1
 .IMPORT _enir1,    _elvr1,    _tctdt0,   _tcccs0,   _tctdt1,   _tcccs1
 .IMPORT _tctdt2,   _tcccs2,   _tctdt3,   _tcccs3,   _ipcp1,    _ipcp0
 .IMPORT _ics01,    _ipcp3,    _ipcp2,    _ics23,    _ipcp5,    _ipcp4
 .IMPORT _ics45,    _ipcp7,    _ipcp6,    _ics67,    _occp1,    _occp0
 .IMPORT _occp3,    _occp2,    _ocs23,    _ocs01,    _occp5,    _occp4
 .IMPORT _occp7,    _occp6,    _ocs67,    _ocs45,    _eirr2,    _enir2
 .IMPORT _elvr2,    _eirr3,    _enir3,    _elvr3,    _eirr4,    _enir4
 .IMPORT _elvr4,    _dacr,     _dadr0,    _dadr1,    _dadbl,    _wtdbl
 .IMPORT _wtcr,     _wtbr,     _wthr,     _wtmr,     _wtsr,     _aderh
 .IMPORT _aderl,    _adcs1,    _adcs0,    _adcr1,    _adcr0,    _adct1
 .IMPORT _adct0,    _adsch,    _adech,    _cucr,     _cutd,     _cutr1
 .IMPORT _cutr2,    _udrc1,    _udrc0,    _udcr1,    _udcr0,    _udcch0
 .IMPORT _udccl0,   _udcs0,    _udcch1,   _udccl1,   _udcs1,    _udrc3
 .IMPORT _udrc2,    _udcr3,    _udcr2,    _udcch2,   _udccl2,   _udcs2
 .IMPORT _udcch3,   _udccl3,   _udcs3,    _ad2erh,   _ad2erl,   _ad2cs1
 .IMPORT _ad2cs0,   _ad2cr1,   _ad2cr0,   _ad2ct1,   _ad2ct0,   _ad2sch
 .IMPORT _ad2ech,   _cmpr,     _cmcr,     _cmt1,     _cmt2,     _canpre
 .IMPORT _eissr,    _prlh0,    _prll0,    _prlh1,    _prll1,    _prlh2
 .IMPORT _prll2,    _prlh3,    _prll3,    _ppgc0,    _ppgc1,    _ppgc2
 .IMPORT _ppgc3,    _prlh4,    _prll4,    _prlh5,    _prll5,    _prlh6
 .IMPORT _prll6,    _prlh7,    _prll7,    _ppgc4,    _ppgc5,    _ppgc6
 .IMPORT _ppgc7,    _prlh8,    _prll8,    _prlh9,    _prll9,    _prlha
 .IMPORT _prlla,    _prlhb,    _prllb,    _ppgc8,    _ppgc9,    _ppgca
 .IMPORT _ppgcb,    _prlhc,    _prllc,    _prlhd,    _prlld,    _prlhe
 .IMPORT _prlle,    _prlhf,    _prllf,    _ppgcc,    _ppgcd,    _ppgce
 .IMPORT _ppgcf,    _ppgtrg,   _ppgrevc,  _ppgswap,  _cmclkr,   _dmaca0
 .IMPORT _dmacb0,   _dmaca1,   _dmacb1,   _dmaca2,   _dmacb2,   _dmaca3
 .IMPORT _dmacb3,   _dmaca4,   _dmacb4,   _dmacr,    _bsd0,     _bsd1
 .IMPORT _bsdc,     _bsrr,     _ddr0,     _ddr1,     _ddr2,     _ddr3
 .IMPORT _ddr4,     _ddr5,     _ddr6,     _ddr7,     _ddr8,     _ddr9
 .IMPORT _ddra,     _ddrb,     _ddrc,     _ddrd,     _ddre,     _ddrf
 .IMPORT _ddrg,     _pfr0,     _pfr1,     _pfr2,     _pfr3,     _pfr4
 .IMPORT _pfr5,     _pfr6,     _pfr7,     _pfr8,     _pfr9,     _pfra
 .IMPORT _pfrb,     _pfrc,     _pfrd,     _pfre,     _pfrf,     _pfrg
 .IMPORT _icr00,    _icr01,    _icr02,    _icr03,    _icr04,    _icr05
 .IMPORT _icr06,    _icr07,    _icr08,    _icr09,    _icr10,    _icr11
 .IMPORT _icr12,    _icr13,    _icr14,    _icr15,    _icr16,    _icr17
 .IMPORT _icr18,    _icr19,    _icr20,    _icr21,    _icr22,    _icr23
 .IMPORT _icr24,    _icr25,    _icr26,    _icr27,    _icr28,    _icr29
 .IMPORT _icr30,    _icr31,    _icr32,    _icr33,    _icr34,    _icr35
 .IMPORT _icr36,    _icr37,    _icr38,    _icr39,    _icr40,    _icr41
 .IMPORT _icr42,    _icr43,    _icr44,    _icr45,    _icr46,    _icr47
 .IMPORT _rsrr,     _stcr,     _tbcr,     _ctbr,     _clkr,     _wpr
 .IMPORT _divr0,    _divr1,    _osccr,    _oscr,     _csvcr,    _pper0
 .IMPORT _pper1,    _pper2,    _pper3,    _pper4,    _pper5,    _pper6
 .IMPORT _pper7,    _pper8,    _pper9,    _ppera,    _pperb,    _pperc
 .IMPORT _pperd,    _ppere,    _pperf,    _pperg,    _ppcr0,    _ppcr1
 .IMPORT _ppcr2,    _ppcr3,    _ppcr4,    _ppcr5,    _ppcr6,    _ppcr7
 .IMPORT _ppcr8,    _ppcr9,    _ppcra,    _ppcrb,    _ppcrc,    _ppcrd
 .IMPORT _ppcre,    _ppcrf,    _ppcrg,    _pilr0,    _pilr1,    _pilr2
 .IMPORT _pilr3,    _pilr4,    _pilr5,    _pilr6,    _pilr7,    _pilr8
 .IMPORT _pilr9,    _pilra,    _pilrb,    _pilrc,    _pilrd,    _pilre
 .IMPORT _pilrf,    _pilrg,    _ibcr0,    _ibsr0,    _itbah0,   _itbal0
 .IMPORT _itmkh0,   _itmkl0,   _ismk0,    _isba0,    _idar0,    _iccr0
 .IMPORT _ibcr1,    _ibsr1,    _itbah1,   _itbal1,   _itmkh1,   _itmkl1
 .IMPORT _ismk1,    _isba1,    _idar1,    _iccr1,    _ibcr2,    _ibsr2
 .IMPORT _itbah2,   _itbal2,   _itmkh2,   _itmkl2,   _ismk2,    _isba2
 .IMPORT _idar2,    _iccr2,    _hwdcs,    _epfr0,    _epfr1,    _epfr2
 .IMPORT _epfr3,    _epfr4,    _epfr5,    _epfr6,    _epfr7,    _epfr8
 .IMPORT _epfr9,    _epfra,    _epfrb,    _epfrc,    _epfrd,    _epfre
 .IMPORT _epfrf,    _epfrg,    _pidr0,    _pidr1,    _pidr2,    _pidr3
 .IMPORT _pidr4,    _pidr5,    _pidr6,    _pidr7,    _pidr8,    _pidr9
 .IMPORT _pidra,    _pidrb,    _pidrc,    _pidrd,    _pidre,    _pidrf
 .IMPORT _pidrg,    _asr0,     _acr0,     _asr1,     _acr1,     _asr2
 .IMPORT _acr2,     _asr3,     _acr3,     _awr0,     _awr1,     _awr2
 .IMPORT _awr3,     _cser,     _tcr,      _modr,     _dmasa0,   _dmada0
 .IMPORT _dmasa1,   _dmada1,   _dmasa2,   _dmada2,   _dmasa3,   _dmada3
 .IMPORT _dmasa4,   _dmada4,   _flcr,     _flwc,     _ctrlr0,   _statr0
 .IMPORT _errcnt0,  _btr0,     _intr0,    _testr0,   _brper0,   _if1creq0
 .IMPORT _if1cmsk0, _if1msk120, _if1msk20, _if1msk10, _if1arb120, _if1arb20
 .IMPORT _if1arb10, _if1mctr0, _if1dta120, _if1dta10, _if1dta20, _if1dtb120
 .IMPORT _if1dtb10, _if1dtb20, _if1dta_swp120, _if1dta_swp20, _if1dta_swp10, _if1dtb_swp120
 .IMPORT _if1dtb_swp20, _if1dtb_swp10, _if2creq0, _if2cmsk0, _if2msk120, _if2msk20
 .IMPORT _if2msk10, _if2arb120, _if2arb20, _if2arb10, _if2mctr0, _if2dta120
 .IMPORT _if2dta10, _if2dta20, _if2dtb120, _if2dtb10, _if2dtb20, _if2dta_swp120
 .IMPORT _if2dta_swp20, _if2dta_swp10, _if2dtb_swp120, _if2dtb_swp20, _if2dtb_swp10, _treqr120
 .IMPORT _treqr20,  _treqr10,  _treqr340, _treqr40,  _treqr30,  _newdt120
 .IMPORT _newdt20,  _newdt10,  _newdt340, _newdt40,  _newdt30,  _intpnd120
 .IMPORT _intpnd20, _intpnd10, _intpnd340, _intpnd40, _intpnd30, _msgval120
 .IMPORT _msgval20, _msgval10, _msgval340, _msgval40, _msgval30, _ctrlr1
 .IMPORT _statr1,   _errcnt1,  _btr1,     _intr1,    _testr1,   _brper1
 .IMPORT _if1creq1, _if1cmsk1, _if1msk121, _if1msk21, _if1msk11, _if1arb121
 .IMPORT _if1arb21, _if1arb11, _if1mctr1, _if1dta121, _if1dta11, _if1dta21
 .IMPORT _if1dtb121, _if1dtb11, _if1dtb21, _if1dta_swp121, _if1dta_swp21, _if1dta_swp11
 .IMPORT _if1dtb_swp121, _if1dtb_swp21, _if1dtb_swp11, _if2creq1, _if2cmsk1, _if2msk121
 .IMPORT _if2msk21, _if2msk11, _if2arb121, _if2arb21, _if2arb11, _if2mctr1
 .IMPORT _if2dta121, _if2dta11, _if2dta21, _if2dtb121, _if2dtb11, _if2dtb21
 .IMPORT _if2dta_swp121, _if2dta_swp21, _if2dta_swp11, _if2dtb_swp121, _if2dtb_swp21, _if2dtb_swp11
 .IMPORT _treqr121, _treqr21,  _treqr11,  _treqr341, _treqr41,  _treqr31
 .IMPORT _newdt121, _newdt21,  _newdt11,  _newdt341, _newdt41,  _newdt31
 .IMPORT _intpnd121, _intpnd21, _intpnd11, _intpnd341, _intpnd41, _intpnd31
 .IMPORT _msgval121, _msgval21, _msgval11, _msgval341, _msgval41, _msgval31
 .IMPORT _ctrlr2,   _statr2,   _errcnt2,  _btr2,     _intr2,    _testr2
 .IMPORT _brper2,   _if1creq2, _if1cmsk2, _if1msk122, _if1msk22, _if1msk12
 .IMPORT _if1arb122, _if1arb22, _if1arb12, _if1mctr2, _if1dta122, _if1dta12
 .IMPORT _if1dta22, _if1dtb122, _if1dtb12, _if1dtb22, _if1dta_swp122, _if1dta_swp22
 .IMPORT _if1dta_swp12, _if1dtb_swp122, _if1dtb_swp22, _if1dtb_swp12, _if2creq2, _if2cmsk2
 .IMPORT _if2msk122, _if2msk22, _if2msk12, _if2arb122, _if2arb22, _if2arb12
 .IMPORT _if2mctr2, _if2dta122, _if2dta12, _if2dta22, _if2dtb122, _if2dtb12
 .IMPORT _if2dtb22, _if2dta_swp122, _if2dta_swp22, _if2dta_swp12, _if2dtb_swp122, _if2dtb_swp22
 .IMPORT _if2dtb_swp12, _treqr122, _treqr22,  _treqr12,  _treqr342, _treqr42
 .IMPORT _treqr32,  _newdt122, _newdt22,  _newdt12,  _newdt342, _newdt42
 .IMPORT _newdt32,  _intpnd122, _intpnd22, _intpnd12, _intpnd342, _intpnd42
 .IMPORT _intpnd32, _msgval122, _msgval22, _msgval12, _msgval342, _msgval42
 .IMPORT _msgval32
#pragma endasm
#else  /* __FASM__  */ 
/* THIS SAMPLE CODE IS PROVIDED AS IS AND IS SUBJECT TO ALTERATIONS. FUJITSU     */
/* MICROELECTRONICS ACCEPTS NO RESPONSIBILITY OR LIABILITY FOR ANY ERRORS OR     */
/* ELIGIBILITY FOR ANY PURPOSES.                                                 */
/*                 (C) Fujitsu Microelectronics Europe GmbH                      */
/*  */
/* ************************************************************************* */
/*                   Fujitsu Microelectronics Europe GmbH                    */
/*                    Am Siebenstein 6-10, 63303 Dreieich                    */
/*                     Tel.: +49 (6103) 690-0, Fax -122                      */
/*                                                                           */
/* THIS SAMPLE CODE IS PROVIDED AS IS AND IS SUBJECT TO ALTERATIONS. FUJITSU */
/* MICROELECTRONICS ACCEPTS NO RESPONSIBILITY OR LIABILITY FOR ANY ERRORS OR */
/* ELIGIBILITY FOR ANY PURPOSES                                              */
/*                 (C) Fujitsu Microelectronics Europe GmbH                  */
/* ************************************************************************* */
/* ---------------------------------------------------------------------- */
/* $Id: MB91270.h,v 1.3 2006/02/16 11:15:56 mherz Exp $ */
/* ---------------------------------------------------------------------- */
/*                      */
/* $Id: MB91270.h,v 1.3 2006/02/16 11:15:56 mherz Exp $ */
/*      - Initial Version */
/*  Id: MB91270.iow,v 1.1 2005/08/08 10:32:08 mherz Exp  */
/*      - Update CAN-register   */
/* BIT-STRUCTURE-DEFINITIONS */

typedef unsigned char		IO_BYTE;
typedef unsigned short		IO_WORD;
typedef unsigned long		IO_LWORD;
typedef const unsigned short	IO_WORD_READ;

typedef union{   /* Port Data Register */
    IO_BYTE	byte;
    struct{   
    IO_BYTE _P07 :1;
    IO_BYTE _P06 :1;
    IO_BYTE _P05 :1;
    IO_BYTE _P04 :1;
    IO_BYTE _P03 :1;
    IO_BYTE _P02 :1;
    IO_BYTE _P01 :1;
    IO_BYTE _P00 :1;
  }bit;
 }PDR0STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _P17 :1;
    IO_BYTE _P16 :1;
    IO_BYTE _P15 :1;
    IO_BYTE _P14 :1;
    IO_BYTE _P13 :1;
    IO_BYTE _P12 :1;
    IO_BYTE _P11 :1;
    IO_BYTE _P10 :1;
  }bit;
 }PDR1STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _P27 :1;
    IO_BYTE _P26 :1;
    IO_BYTE _P25 :1;
    IO_BYTE _P24 :1;
    IO_BYTE _P23 :1;
    IO_BYTE _P22 :1;
    IO_BYTE _P21 :1;
    IO_BYTE _P20 :1;
  }bit;
 }PDR2STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _P37 :1;
    IO_BYTE _P36 :1;
    IO_BYTE _P35 :1;
    IO_BYTE _P34 :1;
    IO_BYTE _P33 :1;
    IO_BYTE _P32 :1;
    IO_BYTE _P31 :1;
    IO_BYTE _P30 :1;
  }bit;
 }PDR3STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _P47 :1;
    IO_BYTE _P46 :1;
    IO_BYTE _P45 :1;
    IO_BYTE _P44 :1;
    IO_BYTE _P43 :1;
    IO_BYTE _P42 :1;
    IO_BYTE _P41 :1;
    IO_BYTE _P40 :1;
  }bit;
 }PDR4STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _P57 :1;
    IO_BYTE _P56 :1;
    IO_BYTE _P55 :1;
    IO_BYTE _P54 :1;
    IO_BYTE _P53 :1;
    IO_BYTE _P52 :1;
    IO_BYTE _P51 :1;
    IO_BYTE _P50 :1;
  }bit;
 }PDR5STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _P67 :1;
    IO_BYTE _P66 :1;
    IO_BYTE _P65 :1;
    IO_BYTE _P64 :1;
    IO_BYTE _P63 :1;
    IO_BYTE _P62 :1;
    IO_BYTE _P61 :1;
    IO_BYTE _P60 :1;
  }bit;
 }PDR6STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _P77 :1;
    IO_BYTE _P76 :1;
    IO_BYTE _P75 :1;
    IO_BYTE _P74 :1;
    IO_BYTE _P73 :1;
    IO_BYTE _P72 :1;
    IO_BYTE _P71 :1;
    IO_BYTE _P70 :1;
  }bit;
 }PDR7STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _P87 :1;
    IO_BYTE _P86 :1;
    IO_BYTE _P85 :1;
    IO_BYTE _P84 :1;
    IO_BYTE _P83 :1;
    IO_BYTE _P82 :1;
    IO_BYTE _P81 :1;
    IO_BYTE _P80 :1;
  }bit;
 }PDR8STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _P97 :1;
    IO_BYTE _P96 :1;
    IO_BYTE _P95 :1;
    IO_BYTE _P94 :1;
    IO_BYTE _P93 :1;
    IO_BYTE _P92 :1;
    IO_BYTE _P91 :1;
    IO_BYTE _P90 :1;
  }bit;
 }PDR9STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _PA1 :1;
    IO_BYTE _PA0 :1;
  }bit;
 }PDRASTR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _PB5 :1;
    IO_BYTE _PB4 :1;
    IO_BYTE _PB3 :1;
    IO_BYTE _PB2 :1;
    IO_BYTE _PB1 :1;
    IO_BYTE _PB0 :1;
  }bit;
 }PDRBSTR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _PC7 :1;
    IO_BYTE _PC6 :1;
    IO_BYTE _PC5 :1;
    IO_BYTE _PC4 :1;
    IO_BYTE _PC3 :1;
    IO_BYTE _PC2 :1;
    IO_BYTE _PC1 :1;
    IO_BYTE _PC0 :1;
  }bit;
 }PDRCSTR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _PD7 :1;
    IO_BYTE _PD6 :1;
    IO_BYTE _PD5 :1;
    IO_BYTE _PD4 :1;
    IO_BYTE _PD3 :1;
    IO_BYTE _PD2 :1;
    IO_BYTE _PD1 :1;
    IO_BYTE _PD0 :1;
  }bit;
 }PDRDSTR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _PE7 :1;
    IO_BYTE _PE6 :1;
    IO_BYTE _PE5 :1;
    IO_BYTE _PE4 :1;
    IO_BYTE _PE3 :1;
    IO_BYTE _PE2 :1;
    IO_BYTE _PE1 :1;
    IO_BYTE _PE0 :1;
  }bit;
 }PDRESTR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _PF7 :1;
    IO_BYTE _PF6 :1;
    IO_BYTE _PF5 :1;
    IO_BYTE _PF4 :1;
    IO_BYTE _PF3 :1;
    IO_BYTE _PF2 :1;
    IO_BYTE _PF1 :1;
    IO_BYTE _PF0 :1;
  }bit;
 }PDRFSTR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _PG7 :1;
    IO_BYTE _PG6 :1;
    IO_BYTE _PG5 :1;
    IO_BYTE _PG4 :1;
    IO_BYTE _PG3 :1;
    IO_BYTE _PG2 :1;
    IO_BYTE _PG1 :1;
    IO_BYTE _PG0 :1;
  }bit;
 }PDRGSTR;
typedef union{   /* External Interrupt 0-7 */
    IO_BYTE	byte;
    struct{   
    IO_BYTE _ER7 :1;
    IO_BYTE _ER6 :1;
    IO_BYTE _ER5 :1;
    IO_BYTE _ER4 :1;
    IO_BYTE _ER3 :1;
    IO_BYTE _ER2 :1;
    IO_BYTE _ER1 :1;
    IO_BYTE _ER0 :1;
  }bit;
 }EIRR0STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _EN7 :1;
    IO_BYTE _EN6 :1;
    IO_BYTE _EN5 :1;
    IO_BYTE _EN4 :1;
    IO_BYTE _EN3 :1;
    IO_BYTE _EN2 :1;
    IO_BYTE _EN1 :1;
    IO_BYTE _EN0 :1;
  }bit;
 }ENIR0STR;
typedef union{  
    IO_WORD	word;
    struct{   
    IO_WORD _LB7 :1;
    IO_WORD _LA7 :1;
    IO_WORD _LB6 :1;
    IO_WORD _LA6 :1;
    IO_WORD _LB5 :1;
    IO_WORD _LA5 :1;
    IO_WORD _LB4 :1;
    IO_WORD _LA4 :1;
    IO_WORD _LB3 :1;
    IO_WORD _LA3 :1;
    IO_WORD _LB2 :1;
    IO_WORD _LA2 :1;
    IO_WORD _LB1 :1;
    IO_WORD _LA1 :1;
    IO_WORD _LB0 :1;
    IO_WORD _LA0 :1;
  }bit;
 }ELVR0STR;
typedef union{   /* DLYI/I-unit */
    IO_BYTE	byte;
    struct{   
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _DLY1 :1;
  }bit;
 }DICRSTR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _MHALTI :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _LVL4 :1;
    IO_BYTE _LVL3 :1;
    IO_BYTE _LVL2 :1;
    IO_BYTE _LVL1 :1;
  }bit;
  struct{
    IO_BYTE _HALT :1;
  }bitc;
 }HRCLSTR;
typedef union{   /* Reload Timer 0 */
    IO_WORD	word;
    struct{   
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
  }bit;
 }TMRLR0STR;
typedef union{  
    IO_WORD	word;
    struct{   
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD _CSL2 :1;
    IO_WORD _CSL1 :1;
    IO_WORD _CSL0 :1;
    IO_WORD _MOD2 :1;
    IO_WORD _MOD1 :1;
    IO_WORD _MOD0 :1;
    IO_WORD  :1;
    IO_WORD _OULT :1;
    IO_WORD _RELD :1;
    IO_WORD _INTE :1;
    IO_WORD _UF :1;
    IO_WORD _CNTE :1;
    IO_WORD _TRG :1;
  }bit;
  struct{
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD _CSL :3;
    IO_WORD _MOD :3;
  }bitc;
 }TMCSR0STR;
typedef union{  
    IO_WORD	word;
    struct{   
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD _CSL2 :1;
    IO_WORD _CSL1 :1;
    IO_WORD _CSL0 :1;
    IO_WORD _MOD2 :1;
    IO_WORD _MOD1 :1;
    IO_WORD _MOD0 :1;
    IO_WORD  :1;
    IO_WORD _OULT :1;
    IO_WORD _RELD :1;
    IO_WORD _INTE :1;
    IO_WORD _UF :1;
    IO_WORD _CNTE :1;
    IO_WORD _TRG :1;
  }bit;
  struct{
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD _CSL :3;
    IO_WORD _MOD :3;
  }bitc;
 }TMCSR1STR;
typedef union{  
    IO_WORD	word;
    struct{   
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD _CSL2 :1;
    IO_WORD _CSL1 :1;
    IO_WORD _CSL0 :1;
    IO_WORD _MOD2 :1;
    IO_WORD _MOD1 :1;
    IO_WORD _MOD0 :1;
    IO_WORD  :1;
    IO_WORD _OULT :1;
    IO_WORD _RELD :1;
    IO_WORD _INTE :1;
    IO_WORD _UF :1;
    IO_WORD _CNTE :1;
    IO_WORD _TRG :1;
  }bit;
  struct{
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD _CSL :3;
    IO_WORD _MOD :3;
  }bitc;
 }TMCSR2STR;
typedef union{   /* LIN-UART 0 */
    IO_BYTE	byte;
    struct{   
    IO_BYTE _PEN :1;
    IO_BYTE _P :1;
    IO_BYTE _SBL :1;
    IO_BYTE _CL :1;
    IO_BYTE _AD :1;
    IO_BYTE _CRE :1;
    IO_BYTE _RXE :1;
    IO_BYTE _TXE :1;
  }bit;
 }SCR0STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _MD1 :1;
    IO_BYTE _MD0 :1;
    IO_BYTE _OTO :1;
    IO_BYTE _EXT :1;
    IO_BYTE _REST :1;
    IO_BYTE _UPCL :1;
    IO_BYTE _SCKE :1;
    IO_BYTE _SOE :1;
  }bit;
  struct{
    IO_BYTE _MD :2;
  }bitc;
 }SMR0STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _PE :1;
    IO_BYTE _ORE :1;
    IO_BYTE _FRE :1;
    IO_BYTE _RDRF :1;
    IO_BYTE _TDRE :1;
    IO_BYTE _BDS :1;
    IO_BYTE _RIE :1;
    IO_BYTE _TIE :1;
  }bit;
 }SSR0STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _D7 :1;
    IO_BYTE _D6 :1;
    IO_BYTE _D5 :1;
    IO_BYTE _D4 :1;
    IO_BYTE _D3 :1;
    IO_BYTE _D2 :1;
    IO_BYTE _D1 :1;
    IO_BYTE _D0 :1;
  }bit;
 }RDR0STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _D7 :1;
    IO_BYTE _D6 :1;
    IO_BYTE _D5 :1;
    IO_BYTE _D4 :1;
    IO_BYTE _D3 :1;
    IO_BYTE _D2 :1;
    IO_BYTE _D1 :1;
    IO_BYTE _D0 :1;
  }bit;
 }TDR0STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _LBIE :1;
    IO_BYTE _LBD :1;
    IO_BYTE _LBL1 :1;
    IO_BYTE _LBL0 :1;
    IO_BYTE _SOPE :1;
    IO_BYTE _SIOP :1;
    IO_BYTE _CCO :1;
    IO_BYTE _SCES :1;
  }bit;
  struct{
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE _LBL :2;
  }bitc;
 }ESCR0STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE  :1;
    IO_BYTE _LBR :1;
    IO_BYTE _MS :1;
    IO_BYTE _SCDE :1;
    IO_BYTE _SSM :1;
    IO_BYTE _BIE :1;
    IO_BYTE _RBI :1;
    IO_BYTE _TBI :1;
  }bit;
 }ECCR0STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE  :1;
    IO_BYTE _B14 :1;
    IO_BYTE _B13 :1;
    IO_BYTE _B12 :1;
    IO_BYTE _B11 :1;
    IO_BYTE _B10 :1;
    IO_BYTE _B09 :1;
    IO_BYTE _B08 :1;
  }bit;
 }BGR10STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _B07 :1;
    IO_BYTE _B06 :1;
    IO_BYTE _B05 :1;
    IO_BYTE _B04 :1;
    IO_BYTE _B03 :1;
    IO_BYTE _B02 :1;
    IO_BYTE _B01 :1;
    IO_BYTE _B00 :1;
  }bit;
 }BGR00STR;
typedef union{   /* LIN-UART 5 */
    IO_BYTE	byte;
    struct{   
    IO_BYTE _PEN :1;
    IO_BYTE _P :1;
    IO_BYTE _SBL :1;
    IO_BYTE _CL :1;
    IO_BYTE _AD :1;
    IO_BYTE _CRE :1;
    IO_BYTE _RXE :1;
    IO_BYTE _TXE :1;
  }bit;
 }SCR5STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _MD1 :1;
    IO_BYTE _MD0 :1;
    IO_BYTE _OTO :1;
    IO_BYTE _EXT :1;
    IO_BYTE _REST :1;
    IO_BYTE _UPCL :1;
    IO_BYTE _SCKE :1;
    IO_BYTE _SOE :1;
  }bit;
  struct{
    IO_BYTE _MD :2;
  }bitc;
 }SMR5STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _PE :1;
    IO_BYTE _ORE :1;
    IO_BYTE _FRE :1;
    IO_BYTE _RDRF :1;
    IO_BYTE _TDRE :1;
    IO_BYTE _BDS :1;
    IO_BYTE _RIE :1;
    IO_BYTE _TIE :1;
  }bit;
 }SSR5STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _D7 :1;
    IO_BYTE _D6 :1;
    IO_BYTE _D5 :1;
    IO_BYTE _D4 :1;
    IO_BYTE _D3 :1;
    IO_BYTE _D2 :1;
    IO_BYTE _D1 :1;
    IO_BYTE _D0 :1;
  }bit;
 }RDR5STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _D7 :1;
    IO_BYTE _D6 :1;
    IO_BYTE _D5 :1;
    IO_BYTE _D4 :1;
    IO_BYTE _D3 :1;
    IO_BYTE _D2 :1;
    IO_BYTE _D1 :1;
    IO_BYTE _D0 :1;
  }bit;
 }TDR5STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _LBIE :1;
    IO_BYTE _LBD :1;
    IO_BYTE _LBL1 :1;
    IO_BYTE _LBL0 :1;
    IO_BYTE _SOPE :1;
    IO_BYTE _SIOP :1;
    IO_BYTE _CCO :1;
    IO_BYTE _SCES :1;
  }bit;
  struct{
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE _LBL :2;
  }bitc;
 }ESCR5STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE  :1;
    IO_BYTE _LBR :1;
    IO_BYTE _MS :1;
    IO_BYTE _SCDE :1;
    IO_BYTE _SSM :1;
    IO_BYTE _BIE :1;
    IO_BYTE _RBI :1;
    IO_BYTE _TBI :1;
  }bit;
 }ECCR5STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE  :1;
    IO_BYTE _B14 :1;
    IO_BYTE _B13 :1;
    IO_BYTE _B12 :1;
    IO_BYTE _B11 :1;
    IO_BYTE _B10 :1;
    IO_BYTE _B09 :1;
    IO_BYTE _B08 :1;
  }bit;
 }BGR15STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _B07 :1;
    IO_BYTE _B06 :1;
    IO_BYTE _B05 :1;
    IO_BYTE _B04 :1;
    IO_BYTE _B03 :1;
    IO_BYTE _B02 :1;
    IO_BYTE _B01 :1;
    IO_BYTE _B00 :1;
  }bit;
 }BGR05STR;
typedef union{   /* LIN-UART 6 */
    IO_BYTE	byte;
    struct{   
    IO_BYTE _PEN :1;
    IO_BYTE _P :1;
    IO_BYTE _SBL :1;
    IO_BYTE _CL :1;
    IO_BYTE _AD :1;
    IO_BYTE _CRE :1;
    IO_BYTE _RXE :1;
    IO_BYTE _TXE :1;
  }bit;
 }SCR6STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _MD1 :1;
    IO_BYTE _MD0 :1;
    IO_BYTE _OTO :1;
    IO_BYTE _EXT :1;
    IO_BYTE _REST :1;
    IO_BYTE _UPCL :1;
    IO_BYTE _SCKE :1;
    IO_BYTE _SOE :1;
  }bit;
  struct{
    IO_BYTE _MD :2;
  }bitc;
 }SMR6STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _PE :1;
    IO_BYTE _ORE :1;
    IO_BYTE _FRE :1;
    IO_BYTE _RDRF :1;
    IO_BYTE _TDRE :1;
    IO_BYTE _BDS :1;
    IO_BYTE _RIE :1;
    IO_BYTE _TIE :1;
  }bit;
 }SSR6STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _D7 :1;
    IO_BYTE _D6 :1;
    IO_BYTE _D5 :1;
    IO_BYTE _D4 :1;
    IO_BYTE _D3 :1;
    IO_BYTE _D2 :1;
    IO_BYTE _D1 :1;
    IO_BYTE _D0 :1;
  }bit;
 }RDR6STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _D7 :1;
    IO_BYTE _D6 :1;
    IO_BYTE _D5 :1;
    IO_BYTE _D4 :1;
    IO_BYTE _D3 :1;
    IO_BYTE _D2 :1;
    IO_BYTE _D1 :1;
    IO_BYTE _D0 :1;
  }bit;
 }TDR6STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _LBIE :1;
    IO_BYTE _LBD :1;
    IO_BYTE _LBL1 :1;
    IO_BYTE _LBL0 :1;
    IO_BYTE _SOPE :1;
    IO_BYTE _SIOP :1;
    IO_BYTE _CCO :1;
    IO_BYTE _SCES :1;
  }bit;
  struct{
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE _LBL :2;
  }bitc;
 }ESCR6STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE  :1;
    IO_BYTE _LBR :1;
    IO_BYTE _MS :1;
    IO_BYTE _SCDE :1;
    IO_BYTE _SSM :1;
    IO_BYTE _BIE :1;
    IO_BYTE _RBI :1;
    IO_BYTE _TBI :1;
  }bit;
 }ECCR6STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE  :1;
    IO_BYTE _B14 :1;
    IO_BYTE _B13 :1;
    IO_BYTE _B12 :1;
    IO_BYTE _B11 :1;
    IO_BYTE _B10 :1;
    IO_BYTE _B09 :1;
    IO_BYTE _B08 :1;
  }bit;
 }BGR16STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _B07 :1;
    IO_BYTE _B06 :1;
    IO_BYTE _B05 :1;
    IO_BYTE _B04 :1;
    IO_BYTE _B03 :1;
    IO_BYTE _B02 :1;
    IO_BYTE _B01 :1;
    IO_BYTE _B00 :1;
  }bit;
 }BGR06STR;
typedef union{   /* LIN-UART 1 */
    IO_BYTE	byte;
    struct{   
    IO_BYTE _PEN :1;
    IO_BYTE _P :1;
    IO_BYTE _SBL :1;
    IO_BYTE _CL :1;
    IO_BYTE _AD :1;
    IO_BYTE _CRE :1;
    IO_BYTE _RXE :1;
    IO_BYTE _TXE :1;
  }bit;
 }SCR1STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _MD1 :1;
    IO_BYTE _MD0 :1;
    IO_BYTE _OTO :1;
    IO_BYTE _EXT :1;
    IO_BYTE _REST :1;
    IO_BYTE _UPCL :1;
    IO_BYTE _SCKE :1;
    IO_BYTE _SOE :1;
  }bit;
  struct{
    IO_BYTE _MD :2;
  }bitc;
 }SMR1STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _PE :1;
    IO_BYTE _ORE :1;
    IO_BYTE _FRE :1;
    IO_BYTE _RDRF :1;
    IO_BYTE _TDRE :1;
    IO_BYTE _BDS :1;
    IO_BYTE _RIE :1;
    IO_BYTE _TIE :1;
  }bit;
 }SSR1STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _D7 :1;
    IO_BYTE _D6 :1;
    IO_BYTE _D5 :1;
    IO_BYTE _D4 :1;
    IO_BYTE _D3 :1;
    IO_BYTE _D2 :1;
    IO_BYTE _D1 :1;
    IO_BYTE _D0 :1;
  }bit;
 }RDR1STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _D7 :1;
    IO_BYTE _D6 :1;
    IO_BYTE _D5 :1;
    IO_BYTE _D4 :1;
    IO_BYTE _D3 :1;
    IO_BYTE _D2 :1;
    IO_BYTE _D1 :1;
    IO_BYTE _D0 :1;
  }bit;
 }TDR1STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _LBIE :1;
    IO_BYTE _LBD :1;
    IO_BYTE _LBL1 :1;
    IO_BYTE _LBL0 :1;
    IO_BYTE _SOPE :1;
    IO_BYTE _SIOP :1;
    IO_BYTE _CCO :1;
    IO_BYTE _SCES :1;
  }bit;
  struct{
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE _LBL :2;
  }bitc;
 }ESCR1STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE  :1;
    IO_BYTE _LBR :1;
    IO_BYTE _MS :1;
    IO_BYTE _SCDE :1;
    IO_BYTE _SSM :1;
    IO_BYTE _BIE :1;
    IO_BYTE _RBI :1;
    IO_BYTE _TBI :1;
  }bit;
 }ECCR1STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE  :1;
    IO_BYTE _B14 :1;
    IO_BYTE _B13 :1;
    IO_BYTE _B12 :1;
    IO_BYTE _B11 :1;
    IO_BYTE _B10 :1;
    IO_BYTE _B09 :1;
    IO_BYTE _B08 :1;
  }bit;
 }BGR11STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _B07 :1;
    IO_BYTE _B06 :1;
    IO_BYTE _B05 :1;
    IO_BYTE _B04 :1;
    IO_BYTE _B03 :1;
    IO_BYTE _B02 :1;
    IO_BYTE _B01 :1;
    IO_BYTE _B00 :1;
  }bit;
 }BGR01STR;
typedef union{   /* LIN-UART 2 */
    IO_BYTE	byte;
    struct{   
    IO_BYTE _PEN :1;
    IO_BYTE _P :1;
    IO_BYTE _SBL :1;
    IO_BYTE _CL :1;
    IO_BYTE _AD :1;
    IO_BYTE _CRE :1;
    IO_BYTE _RXE :1;
    IO_BYTE _TXE :1;
  }bit;
 }SCR2STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _MD1 :1;
    IO_BYTE _MD0 :1;
    IO_BYTE _OTO :1;
    IO_BYTE _EXT :1;
    IO_BYTE _REST :1;
    IO_BYTE _UPCL :1;
    IO_BYTE _SCKE :1;
    IO_BYTE _SOE :1;
  }bit;
  struct{
    IO_BYTE _MD :2;
  }bitc;
 }SMR2STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _PE :1;
    IO_BYTE _ORE :1;
    IO_BYTE _FRE :1;
    IO_BYTE _RDRF :1;
    IO_BYTE _TDRE :1;
    IO_BYTE _BDS :1;
    IO_BYTE _RIE :1;
    IO_BYTE _TIE :1;
  }bit;
 }SSR2STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _D7 :1;
    IO_BYTE _D6 :1;
    IO_BYTE _D5 :1;
    IO_BYTE _D4 :1;
    IO_BYTE _D3 :1;
    IO_BYTE _D2 :1;
    IO_BYTE _D1 :1;
    IO_BYTE _D0 :1;
  }bit;
 }RDR2STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _D7 :1;
    IO_BYTE _D6 :1;
    IO_BYTE _D5 :1;
    IO_BYTE _D4 :1;
    IO_BYTE _D3 :1;
    IO_BYTE _D2 :1;
    IO_BYTE _D1 :1;
    IO_BYTE _D0 :1;
  }bit;
 }TDR2STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _LBIE :1;
    IO_BYTE _LBD :1;
    IO_BYTE _LBL1 :1;
    IO_BYTE _LBL0 :1;
    IO_BYTE _SOPE :1;
    IO_BYTE _SIOP :1;
    IO_BYTE _CCO :1;
    IO_BYTE _SCES :1;
  }bit;
  struct{
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE _LBL :2;
  }bitc;
 }ESCR2STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE  :1;
    IO_BYTE _LBR :1;
    IO_BYTE _MS :1;
    IO_BYTE _SCDE :1;
    IO_BYTE _SSM :1;
    IO_BYTE _BIE :1;
    IO_BYTE _RBI :1;
    IO_BYTE _TBI :1;
  }bit;
 }ECCR2STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE  :1;
    IO_BYTE _B14 :1;
    IO_BYTE _B13 :1;
    IO_BYTE _B12 :1;
    IO_BYTE _B11 :1;
    IO_BYTE _B10 :1;
    IO_BYTE _B09 :1;
    IO_BYTE _B08 :1;
  }bit;
 }BGR12STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _B07 :1;
    IO_BYTE _B06 :1;
    IO_BYTE _B05 :1;
    IO_BYTE _B04 :1;
    IO_BYTE _B03 :1;
    IO_BYTE _B02 :1;
    IO_BYTE _B01 :1;
    IO_BYTE _B00 :1;
  }bit;
 }BGR02STR;
typedef union{   /* LIN-UART 3 */
    IO_BYTE	byte;
    struct{   
    IO_BYTE _PEN :1;
    IO_BYTE _P :1;
    IO_BYTE _SBL :1;
    IO_BYTE _CL :1;
    IO_BYTE _AD :1;
    IO_BYTE _CRE :1;
    IO_BYTE _RXE :1;
    IO_BYTE _TXE :1;
  }bit;
 }SCR3STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _MD1 :1;
    IO_BYTE _MD0 :1;
    IO_BYTE _OTO :1;
    IO_BYTE _EXT :1;
    IO_BYTE _REST :1;
    IO_BYTE _UPCL :1;
    IO_BYTE _SCKE :1;
    IO_BYTE _SOE :1;
  }bit;
  struct{
    IO_BYTE _MD :2;
  }bitc;
 }SMR3STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _PE :1;
    IO_BYTE _ORE :1;
    IO_BYTE _FRE :1;
    IO_BYTE _RDRF :1;
    IO_BYTE _TDRE :1;
    IO_BYTE _BDS :1;
    IO_BYTE _RIE :1;
    IO_BYTE _TIE :1;
  }bit;
 }SSR3STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _D7 :1;
    IO_BYTE _D6 :1;
    IO_BYTE _D5 :1;
    IO_BYTE _D4 :1;
    IO_BYTE _D3 :1;
    IO_BYTE _D2 :1;
    IO_BYTE _D1 :1;
    IO_BYTE _D0 :1;
  }bit;
 }RDR3STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _D7 :1;
    IO_BYTE _D6 :1;
    IO_BYTE _D5 :1;
    IO_BYTE _D4 :1;
    IO_BYTE _D3 :1;
    IO_BYTE _D2 :1;
    IO_BYTE _D1 :1;
    IO_BYTE _D0 :1;
  }bit;
 }TDR3STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _LBIE :1;
    IO_BYTE _LBD :1;
    IO_BYTE _LBL1 :1;
    IO_BYTE _LBL0 :1;
    IO_BYTE _SOPE :1;
    IO_BYTE _SIOP :1;
    IO_BYTE _CCO :1;
    IO_BYTE _SCES :1;
  }bit;
  struct{
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE _LBL :2;
  }bitc;
 }ESCR3STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE  :1;
    IO_BYTE _LBR :1;
    IO_BYTE _MS :1;
    IO_BYTE _SCDE :1;
    IO_BYTE _SSM :1;
    IO_BYTE _BIE :1;
    IO_BYTE _RBI :1;
    IO_BYTE _TBI :1;
  }bit;
 }ECCR3STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE  :1;
    IO_BYTE _B14 :1;
    IO_BYTE _B13 :1;
    IO_BYTE _B12 :1;
    IO_BYTE _B11 :1;
    IO_BYTE _B10 :1;
    IO_BYTE _B09 :1;
    IO_BYTE _B08 :1;
  }bit;
 }BGR13STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _B07 :1;
    IO_BYTE _B06 :1;
    IO_BYTE _B05 :1;
    IO_BYTE _B04 :1;
    IO_BYTE _B03 :1;
    IO_BYTE _B02 :1;
    IO_BYTE _B01 :1;
    IO_BYTE _B00 :1;
  }bit;
 }BGR03STR;
typedef union{   /* LIN-UART 4 */
    IO_BYTE	byte;
    struct{   
    IO_BYTE _PEN :1;
    IO_BYTE _P :1;
    IO_BYTE _SBL :1;
    IO_BYTE _CL :1;
    IO_BYTE _AD :1;
    IO_BYTE _CRE :1;
    IO_BYTE _RXE :1;
    IO_BYTE _TXE :1;
  }bit;
 }SCR4STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _MD1 :1;
    IO_BYTE _MD0 :1;
    IO_BYTE _OTO :1;
    IO_BYTE _EXT :1;
    IO_BYTE _REST :1;
    IO_BYTE _UPCL :1;
    IO_BYTE _SCKE :1;
    IO_BYTE _SOE :1;
  }bit;
  struct{
    IO_BYTE _MD :2;
  }bitc;
 }SMR4STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _PE :1;
    IO_BYTE _ORE :1;
    IO_BYTE _FRE :1;
    IO_BYTE _RDRF :1;
    IO_BYTE _TDRE :1;
    IO_BYTE _BDS :1;
    IO_BYTE _RIE :1;
    IO_BYTE _TIE :1;
  }bit;
 }SSR4STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _D7 :1;
    IO_BYTE _D6 :1;
    IO_BYTE _D5 :1;
    IO_BYTE _D4 :1;
    IO_BYTE _D3 :1;
    IO_BYTE _D2 :1;
    IO_BYTE _D1 :1;
    IO_BYTE _D0 :1;
  }bit;
 }RDR4STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _D7 :1;
    IO_BYTE _D6 :1;
    IO_BYTE _D5 :1;
    IO_BYTE _D4 :1;
    IO_BYTE _D3 :1;
    IO_BYTE _D2 :1;
    IO_BYTE _D1 :1;
    IO_BYTE _D0 :1;
  }bit;
 }TDR4STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _LBIE :1;
    IO_BYTE _LBD :1;
    IO_BYTE _LBL1 :1;
    IO_BYTE _LBL0 :1;
    IO_BYTE _SOPE :1;
    IO_BYTE _SIOP :1;
    IO_BYTE _CCO :1;
    IO_BYTE _SCES :1;
  }bit;
  struct{
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE _LBL :2;
  }bitc;
 }ESCR4STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE  :1;
    IO_BYTE _LBR :1;
    IO_BYTE _MS :1;
    IO_BYTE _SCDE :1;
    IO_BYTE _SSM :1;
    IO_BYTE _BIE :1;
    IO_BYTE _RBI :1;
    IO_BYTE _TBI :1;
  }bit;
 }ECCR4STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE  :1;
    IO_BYTE _B14 :1;
    IO_BYTE _B13 :1;
    IO_BYTE _B12 :1;
    IO_BYTE _B11 :1;
    IO_BYTE _B10 :1;
    IO_BYTE _B09 :1;
    IO_BYTE _B08 :1;
  }bit;
 }BGR14STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _B07 :1;
    IO_BYTE _B06 :1;
    IO_BYTE _B05 :1;
    IO_BYTE _B04 :1;
    IO_BYTE _B03 :1;
    IO_BYTE _B02 :1;
    IO_BYTE _B01 :1;
    IO_BYTE _B00 :1;
  }bit;
 }BGR04STR;
typedef union{   /* External Interrupt 8-15 */
    IO_BYTE	byte;
    struct{   
    IO_BYTE _ER7 :1;
    IO_BYTE _ER6 :1;
    IO_BYTE _ER5 :1;
    IO_BYTE _ER4 :1;
    IO_BYTE _ER3 :1;
    IO_BYTE _ER2 :1;
    IO_BYTE _ER1 :1;
    IO_BYTE _ER0 :1;
  }bit;
 }EIRR1STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _EN7 :1;
    IO_BYTE _EN6 :1;
    IO_BYTE _EN5 :1;
    IO_BYTE _EN4 :1;
    IO_BYTE _EN3 :1;
    IO_BYTE _EN2 :1;
    IO_BYTE _EN1 :1;
    IO_BYTE _EN0 :1;
  }bit;
 }ENIR1STR;
typedef union{  
    IO_WORD	word;
    struct{   
    IO_WORD _LB7 :1;
    IO_WORD _LA7 :1;
    IO_WORD _LB6 :1;
    IO_WORD _LA6 :1;
    IO_WORD _LB5 :1;
    IO_WORD _LA5 :1;
    IO_WORD _LB4 :1;
    IO_WORD _LA4 :1;
    IO_WORD _LB3 :1;
    IO_WORD _LA3 :1;
    IO_WORD _LB2 :1;
    IO_WORD _LA2 :1;
    IO_WORD _LB1 :1;
    IO_WORD _LA1 :1;
    IO_WORD _LB0 :1;
    IO_WORD _LA0 :1;
  }bit;
 }ELVR1STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _ECLK :1;
    IO_BYTE _IVF :1;
    IO_BYTE _IVFE :1;
    IO_BYTE _STOP :1;
    IO_BYTE _MODE :1;
    IO_BYTE _CLR :1;
    IO_BYTE _CLK1 :1;
    IO_BYTE _CLK0 :1;
  }bit;
  struct{
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE _CLK :2;
  }bitc;
 }TCCCS0STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _ECLK :1;
    IO_BYTE _IVF :1;
    IO_BYTE _IVFE :1;
    IO_BYTE _STOP :1;
    IO_BYTE _MODE :1;
    IO_BYTE _CLR :1;
    IO_BYTE _CLK1 :1;
    IO_BYTE _CLK0 :1;
  }bit;
  struct{
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE _CLK :2;
  }bitc;
 }TCCCS1STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _ECLK :1;
    IO_BYTE _IVF :1;
    IO_BYTE _IVFE :1;
    IO_BYTE _STOP :1;
    IO_BYTE _MODE :1;
    IO_BYTE _CLR :1;
    IO_BYTE _CLK1 :1;
    IO_BYTE _CLK0 :1;
  }bit;
  struct{
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE _CLK :2;
  }bitc;
 }TCCCS2STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _ECLK :1;
    IO_BYTE _IVF :1;
    IO_BYTE _IVFE :1;
    IO_BYTE _STOP :1;
    IO_BYTE _MODE :1;
    IO_BYTE _CLR :1;
    IO_BYTE _CLK1 :1;
    IO_BYTE _CLK0 :1;
  }bit;
  struct{
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE _CLK :2;
  }bitc;
 }TCCCS3STR;
typedef union{   /* Input Capture 0-7 */
    IO_WORD	word;
    struct{   
    IO_WORD _CP15 :1;
    IO_WORD _CP14 :1;
    IO_WORD _CP13 :1;
    IO_WORD _CP12 :1;
    IO_WORD _CP11 :1;
    IO_WORD _CP10 :1;
    IO_WORD _CP09 :1;
    IO_WORD _CP08 :1;
    IO_WORD _CP07 :1;
    IO_WORD _CP06 :1;
    IO_WORD _CP05 :1;
    IO_WORD _CP04 :1;
    IO_WORD _CP03 :1;
    IO_WORD _CP02 :1;
    IO_WORD _CP01 :1;
    IO_WORD _CP00 :1;
  }bit;
 }IPCP1STR;
typedef union{  
    IO_WORD	word;
    struct{   
    IO_WORD _CP15 :1;
    IO_WORD _CP14 :1;
    IO_WORD _CP13 :1;
    IO_WORD _CP12 :1;
    IO_WORD _CP11 :1;
    IO_WORD _CP10 :1;
    IO_WORD _CP09 :1;
    IO_WORD _CP08 :1;
    IO_WORD _CP07 :1;
    IO_WORD _CP06 :1;
    IO_WORD _CP05 :1;
    IO_WORD _CP04 :1;
    IO_WORD _CP03 :1;
    IO_WORD _CP02 :1;
    IO_WORD _CP01 :1;
    IO_WORD _CP00 :1;
  }bit;
 }IPCP0STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _ICP1 :1;
    IO_BYTE _ICP0 :1;
    IO_BYTE _ICE1 :1;
    IO_BYTE _ICE0 :1;
    IO_BYTE _EG11 :1;
    IO_BYTE _EG10 :1;
    IO_BYTE _EG01 :1;
    IO_BYTE _EG00 :1;
  }bit;
  struct{
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE _EG1 :2;
    IO_BYTE _EG0 :2;
  }bitc;
 }ICS01STR;
typedef union{  
    IO_WORD	word;
    struct{   
    IO_WORD _CP15 :1;
    IO_WORD _CP14 :1;
    IO_WORD _CP13 :1;
    IO_WORD _CP12 :1;
    IO_WORD _CP11 :1;
    IO_WORD _CP10 :1;
    IO_WORD _CP09 :1;
    IO_WORD _CP08 :1;
    IO_WORD _CP07 :1;
    IO_WORD _CP06 :1;
    IO_WORD _CP05 :1;
    IO_WORD _CP04 :1;
    IO_WORD _CP03 :1;
    IO_WORD _CP02 :1;
    IO_WORD _CP01 :1;
    IO_WORD _CP00 :1;
  }bit;
 }IPCP3STR;
typedef union{  
    IO_WORD	word;
    struct{   
    IO_WORD _CP15 :1;
    IO_WORD _CP14 :1;
    IO_WORD _CP13 :1;
    IO_WORD _CP12 :1;
    IO_WORD _CP11 :1;
    IO_WORD _CP10 :1;
    IO_WORD _CP09 :1;
    IO_WORD _CP08 :1;
    IO_WORD _CP07 :1;
    IO_WORD _CP06 :1;
    IO_WORD _CP05 :1;
    IO_WORD _CP04 :1;
    IO_WORD _CP03 :1;
    IO_WORD _CP02 :1;
    IO_WORD _CP01 :1;
    IO_WORD _CP00 :1;
  }bit;
 }IPCP2STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _ICP1 :1;
    IO_BYTE _ICP0 :1;
    IO_BYTE _ICE1 :1;
    IO_BYTE _ICE0 :1;
    IO_BYTE _EG11 :1;
    IO_BYTE _EG10 :1;
    IO_BYTE _EG01 :1;
    IO_BYTE _EG00 :1;
  }bit;
  struct{
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE _EG1 :2;
    IO_BYTE _EG0 :2;
  }bitc;
 }ICS23STR;
typedef union{  
    IO_WORD	word;
    struct{   
    IO_WORD _CP15 :1;
    IO_WORD _CP14 :1;
    IO_WORD _CP13 :1;
    IO_WORD _CP12 :1;
    IO_WORD _CP11 :1;
    IO_WORD _CP10 :1;
    IO_WORD _CP09 :1;
    IO_WORD _CP08 :1;
    IO_WORD _CP07 :1;
    IO_WORD _CP06 :1;
    IO_WORD _CP05 :1;
    IO_WORD _CP04 :1;
    IO_WORD _CP03 :1;
    IO_WORD _CP02 :1;
    IO_WORD _CP01 :1;
    IO_WORD _CP00 :1;
  }bit;
 }IPCP5STR;
typedef union{  
    IO_WORD	word;
    struct{   
    IO_WORD _CP15 :1;
    IO_WORD _CP14 :1;
    IO_WORD _CP13 :1;
    IO_WORD _CP12 :1;
    IO_WORD _CP11 :1;
    IO_WORD _CP10 :1;
    IO_WORD _CP09 :1;
    IO_WORD _CP08 :1;
    IO_WORD _CP07 :1;
    IO_WORD _CP06 :1;
    IO_WORD _CP05 :1;
    IO_WORD _CP04 :1;
    IO_WORD _CP03 :1;
    IO_WORD _CP02 :1;
    IO_WORD _CP01 :1;
    IO_WORD _CP00 :1;
  }bit;
 }IPCP4STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _ICP1 :1;
    IO_BYTE _ICP0 :1;
    IO_BYTE _ICE1 :1;
    IO_BYTE _ICE0 :1;
    IO_BYTE _EG11 :1;
    IO_BYTE _EG10 :1;
    IO_BYTE _EG01 :1;
    IO_BYTE _EG00 :1;
  }bit;
  struct{
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE _EG1 :2;
    IO_BYTE _EG0 :2;
  }bitc;
 }ICS45STR;
typedef union{  
    IO_WORD	word;
    struct{   
    IO_WORD _CP15 :1;
    IO_WORD _CP14 :1;
    IO_WORD _CP13 :1;
    IO_WORD _CP12 :1;
    IO_WORD _CP11 :1;
    IO_WORD _CP10 :1;
    IO_WORD _CP09 :1;
    IO_WORD _CP08 :1;
    IO_WORD _CP07 :1;
    IO_WORD _CP06 :1;
    IO_WORD _CP05 :1;
    IO_WORD _CP04 :1;
    IO_WORD _CP03 :1;
    IO_WORD _CP02 :1;
    IO_WORD _CP01 :1;
    IO_WORD _CP00 :1;
  }bit;
 }IPCP7STR;
typedef union{  
    IO_WORD	word;
    struct{   
    IO_WORD _CP15 :1;
    IO_WORD _CP14 :1;
    IO_WORD _CP13 :1;
    IO_WORD _CP12 :1;
    IO_WORD _CP11 :1;
    IO_WORD _CP10 :1;
    IO_WORD _CP09 :1;
    IO_WORD _CP08 :1;
    IO_WORD _CP07 :1;
    IO_WORD _CP06 :1;
    IO_WORD _CP05 :1;
    IO_WORD _CP04 :1;
    IO_WORD _CP03 :1;
    IO_WORD _CP02 :1;
    IO_WORD _CP01 :1;
    IO_WORD _CP00 :1;
  }bit;
 }IPCP6STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _ICP1 :1;
    IO_BYTE _ICP0 :1;
    IO_BYTE _ICE1 :1;
    IO_BYTE _ICE0 :1;
    IO_BYTE _EG11 :1;
    IO_BYTE _EG10 :1;
    IO_BYTE _EG01 :1;
    IO_BYTE _EG00 :1;
  }bit;
  struct{
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE _EG1 :2;
    IO_BYTE _EG0 :2;
  }bitc;
 }ICS67STR;
typedef union{   /* Output Compare 0-7 */
    IO_WORD	word;
    struct{   
    IO_WORD _C15 :1;
    IO_WORD _C14 :1;
    IO_WORD _C13 :1;
    IO_WORD _C12 :1;
    IO_WORD _C11 :1;
    IO_WORD _C10 :1;
    IO_WORD _C09 :1;
    IO_WORD _C08 :1;
    IO_WORD _C07 :1;
    IO_WORD _C06 :1;
    IO_WORD _C05 :1;
    IO_WORD _C04 :1;
    IO_WORD _C03 :1;
    IO_WORD _C02 :1;
    IO_WORD _C01 :1;
    IO_WORD _C00 :1;
  }bit;
 }OCCP1STR;
typedef union{  
    IO_WORD	word;
    struct{   
    IO_WORD _C15 :1;
    IO_WORD _C14 :1;
    IO_WORD _C13 :1;
    IO_WORD _C12 :1;
    IO_WORD _C11 :1;
    IO_WORD _C10 :1;
    IO_WORD _C09 :1;
    IO_WORD _C08 :1;
    IO_WORD _C07 :1;
    IO_WORD _C06 :1;
    IO_WORD _C05 :1;
    IO_WORD _C04 :1;
    IO_WORD _C03 :1;
    IO_WORD _C02 :1;
    IO_WORD _C01 :1;
    IO_WORD _C00 :1;
  }bit;
 }OCCP0STR;
typedef union{  
    IO_WORD	word;
    struct{   
    IO_WORD _C15 :1;
    IO_WORD _C14 :1;
    IO_WORD _C13 :1;
    IO_WORD _C12 :1;
    IO_WORD _C11 :1;
    IO_WORD _C10 :1;
    IO_WORD _C09 :1;
    IO_WORD _C08 :1;
    IO_WORD _C07 :1;
    IO_WORD _C06 :1;
    IO_WORD _C05 :1;
    IO_WORD _C04 :1;
    IO_WORD _C03 :1;
    IO_WORD _C02 :1;
    IO_WORD _C01 :1;
    IO_WORD _C00 :1;
  }bit;
 }OCCP3STR;
typedef union{  
    IO_WORD	word;
    struct{   
    IO_WORD _C15 :1;
    IO_WORD _C14 :1;
    IO_WORD _C13 :1;
    IO_WORD _C12 :1;
    IO_WORD _C11 :1;
    IO_WORD _C10 :1;
    IO_WORD _C09 :1;
    IO_WORD _C08 :1;
    IO_WORD _C07 :1;
    IO_WORD _C06 :1;
    IO_WORD _C05 :1;
    IO_WORD _C04 :1;
    IO_WORD _C03 :1;
    IO_WORD _C02 :1;
    IO_WORD _C01 :1;
    IO_WORD _C00 :1;
  }bit;
 }OCCP2STR;
typedef union{  
    IO_WORD	word;
    struct{   
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD _CMOD :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD _OTD3 :1;
    IO_WORD _OTD2 :1;
    IO_WORD _ICP3 :1;
    IO_WORD _ICP2 :1;
    IO_WORD _ICE3 :1;
    IO_WORD _ICE2 :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD _CST3 :1;
    IO_WORD _CST2 :1;
  }bit;
 }OCS23STR;
typedef union{  
    IO_WORD	word;
    struct{   
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD _CMOD :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD _OTD1 :1;
    IO_WORD _OTD0 :1;
    IO_WORD _ICP1 :1;
    IO_WORD _ICP0 :1;
    IO_WORD _ICE1 :1;
    IO_WORD _ICE0 :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD _CST1 :1;
    IO_WORD _CST0 :1;
  }bit;
 }OCS01STR;
typedef union{  
    IO_WORD	word;
    struct{   
    IO_WORD _C15 :1;
    IO_WORD _C14 :1;
    IO_WORD _C13 :1;
    IO_WORD _C12 :1;
    IO_WORD _C11 :1;
    IO_WORD _C10 :1;
    IO_WORD _C09 :1;
    IO_WORD _C08 :1;
    IO_WORD _C07 :1;
    IO_WORD _C06 :1;
    IO_WORD _C05 :1;
    IO_WORD _C04 :1;
    IO_WORD _C03 :1;
    IO_WORD _C02 :1;
    IO_WORD _C01 :1;
    IO_WORD _C00 :1;
  }bit;
 }OCCP5STR;
typedef union{  
    IO_WORD	word;
    struct{   
    IO_WORD _C15 :1;
    IO_WORD _C14 :1;
    IO_WORD _C13 :1;
    IO_WORD _C12 :1;
    IO_WORD _C11 :1;
    IO_WORD _C10 :1;
    IO_WORD _C09 :1;
    IO_WORD _C08 :1;
    IO_WORD _C07 :1;
    IO_WORD _C06 :1;
    IO_WORD _C05 :1;
    IO_WORD _C04 :1;
    IO_WORD _C03 :1;
    IO_WORD _C02 :1;
    IO_WORD _C01 :1;
    IO_WORD _C00 :1;
  }bit;
 }OCCP4STR;
typedef union{  
    IO_WORD	word;
    struct{   
    IO_WORD _C15 :1;
    IO_WORD _C14 :1;
    IO_WORD _C13 :1;
    IO_WORD _C12 :1;
    IO_WORD _C11 :1;
    IO_WORD _C10 :1;
    IO_WORD _C09 :1;
    IO_WORD _C08 :1;
    IO_WORD _C07 :1;
    IO_WORD _C06 :1;
    IO_WORD _C05 :1;
    IO_WORD _C04 :1;
    IO_WORD _C03 :1;
    IO_WORD _C02 :1;
    IO_WORD _C01 :1;
    IO_WORD _C00 :1;
  }bit;
 }OCCP7STR;
typedef union{  
    IO_WORD	word;
    struct{   
    IO_WORD _C15 :1;
    IO_WORD _C14 :1;
    IO_WORD _C13 :1;
    IO_WORD _C12 :1;
    IO_WORD _C11 :1;
    IO_WORD _C10 :1;
    IO_WORD _C09 :1;
    IO_WORD _C08 :1;
    IO_WORD _C07 :1;
    IO_WORD _C06 :1;
    IO_WORD _C05 :1;
    IO_WORD _C04 :1;
    IO_WORD _C03 :1;
    IO_WORD _C02 :1;
    IO_WORD _C01 :1;
    IO_WORD _C00 :1;
  }bit;
 }OCCP6STR;
typedef union{  
    IO_WORD	word;
    struct{   
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD _CMOD :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD _OTD7 :1;
    IO_WORD _OTD6 :1;
    IO_WORD _ICP7 :1;
    IO_WORD _ICP6 :1;
    IO_WORD _ICE7 :1;
    IO_WORD _ICE6 :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD _CST7 :1;
    IO_WORD _CST6 :1;
  }bit;
 }OCS67STR;
typedef union{  
    IO_WORD	word;
    struct{   
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD _CMOD :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD _OTD5 :1;
    IO_WORD _OTD4 :1;
    IO_WORD _ICP5 :1;
    IO_WORD _ICP4 :1;
    IO_WORD _ICE5 :1;
    IO_WORD _ICE4 :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD _CST5 :1;
    IO_WORD _CST4 :1;
  }bit;
 }OCS45STR;
typedef union{   /* External Interrupt 16-23 */
    IO_BYTE	byte;
    struct{   
    IO_BYTE _ER7 :1;
    IO_BYTE _ER6 :1;
    IO_BYTE _ER5 :1;
    IO_BYTE _ER4 :1;
    IO_BYTE _ER3 :1;
    IO_BYTE _ER2 :1;
    IO_BYTE _ER1 :1;
    IO_BYTE _ER0 :1;
  }bit;
 }EIRR2STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _EN7 :1;
    IO_BYTE _EN6 :1;
    IO_BYTE _EN5 :1;
    IO_BYTE _EN4 :1;
    IO_BYTE _EN3 :1;
    IO_BYTE _EN2 :1;
    IO_BYTE _EN1 :1;
    IO_BYTE _EN0 :1;
  }bit;
 }ENIR2STR;
typedef union{  
    IO_WORD	word;
    struct{   
    IO_WORD _LB7 :1;
    IO_WORD _LA7 :1;
    IO_WORD _LB6 :1;
    IO_WORD _LA6 :1;
    IO_WORD _LB5 :1;
    IO_WORD _LA5 :1;
    IO_WORD _LB4 :1;
    IO_WORD _LA4 :1;
    IO_WORD _LB3 :1;
    IO_WORD _LA3 :1;
    IO_WORD _LB2 :1;
    IO_WORD _LA2 :1;
    IO_WORD _LB1 :1;
    IO_WORD _LA1 :1;
    IO_WORD _LB0 :1;
    IO_WORD _LA0 :1;
  }bit;
 }ELVR2STR;
typedef union{   /* External Interrupt 24-31 */
    IO_BYTE	byte;
    struct{   
    IO_BYTE _ER7 :1;
    IO_BYTE _ER6 :1;
    IO_BYTE _ER5 :1;
    IO_BYTE _ER4 :1;
    IO_BYTE _ER3 :1;
    IO_BYTE _ER2 :1;
    IO_BYTE _ER1 :1;
    IO_BYTE _ER0 :1;
  }bit;
 }EIRR3STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _EN7 :1;
    IO_BYTE _EN6 :1;
    IO_BYTE _EN5 :1;
    IO_BYTE _EN4 :1;
    IO_BYTE _EN3 :1;
    IO_BYTE _EN2 :1;
    IO_BYTE _EN1 :1;
    IO_BYTE _EN0 :1;
  }bit;
 }ENIR3STR;
typedef union{  
    IO_WORD	word;
    struct{   
    IO_WORD _LB7 :1;
    IO_WORD _LA7 :1;
    IO_WORD _LB6 :1;
    IO_WORD _LA6 :1;
    IO_WORD _LB5 :1;
    IO_WORD _LA5 :1;
    IO_WORD _LB4 :1;
    IO_WORD _LA4 :1;
    IO_WORD _LB3 :1;
    IO_WORD _LA3 :1;
    IO_WORD _LB2 :1;
    IO_WORD _LA2 :1;
    IO_WORD _LB1 :1;
    IO_WORD _LA1 :1;
    IO_WORD _LB0 :1;
    IO_WORD _LA0 :1;
  }bit;
 }ELVR3STR;
typedef union{   /* External Interrupt 32-39 */
    IO_BYTE	byte;
    struct{   
    IO_BYTE _ER7 :1;
    IO_BYTE _ER6 :1;
    IO_BYTE _ER5 :1;
    IO_BYTE _ER4 :1;
    IO_BYTE _ER3 :1;
    IO_BYTE _ER2 :1;
    IO_BYTE _ER1 :1;
    IO_BYTE _ER0 :1;
  }bit;
 }EIRR4STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _EN7 :1;
    IO_BYTE _EN6 :1;
    IO_BYTE _EN5 :1;
    IO_BYTE _EN4 :1;
    IO_BYTE _EN3 :1;
    IO_BYTE _EN2 :1;
    IO_BYTE _EN1 :1;
    IO_BYTE _EN0 :1;
  }bit;
 }ENIR4STR;
typedef union{  
    IO_WORD	word;
    struct{   
    IO_WORD _LB7 :1;
    IO_WORD _LA7 :1;
    IO_WORD _LB6 :1;
    IO_WORD _LA6 :1;
    IO_WORD _LB5 :1;
    IO_WORD _LA5 :1;
    IO_WORD _LB4 :1;
    IO_WORD _LA4 :1;
    IO_WORD _LB3 :1;
    IO_WORD _LA3 :1;
    IO_WORD _LB2 :1;
    IO_WORD _LA2 :1;
    IO_WORD _LB1 :1;
    IO_WORD _LA1 :1;
    IO_WORD _LB0 :1;
    IO_WORD _LA0 :1;
  }bit;
 }ELVR4STR;
typedef union{   /* DAC */
    IO_BYTE	byte;
    struct{   
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _MODE :1;
    IO_BYTE _DAE1 :1;
    IO_BYTE _DAE0 :1;
  }bit;
  struct{
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE _DAE :2;
  }bitc;
 }DACRSTR;
typedef union{  
    IO_WORD	word;
    struct{   
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD _DA09 :1;
    IO_WORD _DA08 :1;
    IO_WORD _DA07 :1;
    IO_WORD _DA06 :1;
    IO_WORD _DA05 :1;
    IO_WORD _DA04 :1;
    IO_WORD _DA03 :1;
    IO_WORD _DA02 :1;
    IO_WORD _DA01 :1;
    IO_WORD _DA00 :1;
  }bit;
 }DADR0STR;
typedef union{  
    IO_WORD	word;
    struct{   
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD _DA19 :1;
    IO_WORD _DA18 :1;
    IO_WORD _DA17 :1;
    IO_WORD _DA16 :1;
    IO_WORD _DA15 :1;
    IO_WORD _DA14 :1;
    IO_WORD _DA13 :1;
    IO_WORD _DA12 :1;
    IO_WORD _DA11 :1;
    IO_WORD _DA10 :1;
  }bit;
 }DADR1STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _DBL :1;
  }bit;
 }DADBLSTR;
typedef union{   /* Real Time Clock (Watch Timer) */
    IO_BYTE	byte;
    struct{   
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _WTCK :1;
    IO_BYTE _DBL :1;
  }bit;
 }WTDBLSTR;
typedef union{  
    IO_WORD	word;
    struct{   
    IO_WORD _INTE3 :1;
    IO_WORD _INT3 :1;
    IO_WORD _INTE2 :1;
    IO_WORD _INT2 :1;
    IO_WORD _INTE1 :1;
    IO_WORD _INT1 :1;
    IO_WORD _INTE0 :1;
    IO_WORD _INT0 :1;
    IO_WORD _TST2 :1;
    IO_WORD _TST1 :1;
    IO_WORD _TST0 :1;
    IO_WORD  :1;
    IO_WORD _RUN :1;
    IO_WORD _UPDT :1;
    IO_WORD  :1;
    IO_WORD _ST :1;
  }bit;
 }WTCRSTR;
typedef union{  
    IO_LWORD	lword;
    struct{   
    IO_LWORD  :1;
    IO_LWORD  :1;
    IO_LWORD  :1;
    IO_LWORD  :1;
    IO_LWORD  :1;
    IO_LWORD  :1;
    IO_LWORD  :1;
    IO_LWORD  :1;
    IO_LWORD  :1;
    IO_LWORD  :1;
    IO_LWORD  :1;
    IO_LWORD _D20 :1;
    IO_LWORD _D19 :1;
    IO_LWORD _D18 :1;
    IO_LWORD _D17 :1;
    IO_LWORD _D16 :1;
    IO_LWORD _D15 :1;
    IO_LWORD _D14 :1;
    IO_LWORD _D13 :1;
    IO_LWORD _D12 :1;
    IO_LWORD _D11 :1;
    IO_LWORD _D10 :1;
    IO_LWORD _D9 :1;
    IO_LWORD _D8 :1;
    IO_LWORD _D7 :1;
    IO_LWORD _D6 :1;
    IO_LWORD _D5 :1;
    IO_LWORD _D4 :1;
    IO_LWORD _D3 :1;
    IO_LWORD _D2 :1;
    IO_LWORD _D1 :1;
    IO_LWORD _D0 :1;
  }bit;
 }WTBRSTR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _H4 :1;
    IO_BYTE _H3 :1;
    IO_BYTE _H2 :1;
    IO_BYTE _H1 :1;
    IO_BYTE _H0 :1;
  }bit;
 }WTHRSTR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _M5 :1;
    IO_BYTE _M4 :1;
    IO_BYTE _M3 :1;
    IO_BYTE _M2 :1;
    IO_BYTE _M1 :1;
    IO_BYTE _M0 :1;
  }bit;
 }WTMRSTR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _S5 :1;
    IO_BYTE _S4 :1;
    IO_BYTE _S3 :1;
    IO_BYTE _S2 :1;
    IO_BYTE _S1 :1;
    IO_BYTE _S0 :1;
  }bit;
 }WTSRSTR;
typedef union{   /* ADC */
    IO_WORD	word;
    struct{   
    IO_WORD _ADE31 :1;
    IO_WORD _ADE30 :1;
    IO_WORD _ADE29 :1;
    IO_WORD _ADE28 :1;
    IO_WORD _ADE27 :1;
    IO_WORD _ADE26 :1;
    IO_WORD _ADE25 :1;
    IO_WORD _ADE24 :1;
    IO_WORD _ADE23 :1;
    IO_WORD _ADE22 :1;
    IO_WORD _ADE21 :1;
    IO_WORD _ADE20 :1;
    IO_WORD _ADE19 :1;
    IO_WORD _ADE18 :1;
    IO_WORD _ADE17 :1;
    IO_WORD _ADE16 :1;
  }bit;
 }ADERHSTR;
typedef union{  
    IO_WORD	word;
    struct{   
    IO_WORD _ADE15 :1;
    IO_WORD _ADE14 :1;
    IO_WORD _ADE13 :1;
    IO_WORD _ADE12 :1;
    IO_WORD _ADE11 :1;
    IO_WORD _ADE10 :1;
    IO_WORD _ADE9 :1;
    IO_WORD _ADE8 :1;
    IO_WORD _ADE7 :1;
    IO_WORD _ADE6 :1;
    IO_WORD _ADE5 :1;
    IO_WORD _ADE4 :1;
    IO_WORD _ADE3 :1;
    IO_WORD _ADE2 :1;
    IO_WORD _ADE1 :1;
    IO_WORD _ADE0 :1;
  }bit;
 }ADERLSTR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _BUSY :1;
    IO_BYTE _INT :1;
    IO_BYTE _INTE :1;
    IO_BYTE _PAUS :1;
    IO_BYTE _STS1 :1;
    IO_BYTE _STS0 :1;
    IO_BYTE _STRT :1;
    IO_BYTE  :1;
  }bit;
  struct{
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE _STS :2;
  }bitc;
 }ADCS1STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _MD1 :1;
    IO_BYTE _MD0 :1;
    IO_BYTE _S10 :1;
    IO_BYTE _ACH4 :1;
    IO_BYTE _ACH3 :1;
    IO_BYTE _ACH2 :1;
    IO_BYTE _ACH1 :1;
    IO_BYTE _ACH0 :1;
  }bit;
  struct{
    IO_BYTE _MD :2;
    IO_BYTE :1;
    IO_BYTE _ACH :5;
  }bitc;
 }ADCS0STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _D9 :1;
    IO_BYTE _D8 :1;
  }bit;
 }ADCR1STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _D7 :1;
    IO_BYTE _D6 :1;
    IO_BYTE _D5 :1;
    IO_BYTE _D4 :1;
    IO_BYTE _D3 :1;
    IO_BYTE _D2 :1;
    IO_BYTE _D1 :1;
    IO_BYTE _D0 :1;
  }bit;
 }ADCR0STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _CT5 :1;
    IO_BYTE _CT4 :1;
    IO_BYTE _CT3 :1;
    IO_BYTE _CT2 :1;
    IO_BYTE _CT1 :1;
    IO_BYTE _CT0 :1;
    IO_BYTE _ST9 :1;
    IO_BYTE _ST8 :1;
  }bit;
 }ADCT1STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _ST7 :1;
    IO_BYTE _ST6 :1;
    IO_BYTE _ST5 :1;
    IO_BYTE _ST4 :1;
    IO_BYTE _ST3 :1;
    IO_BYTE _ST2 :1;
    IO_BYTE _ST1 :1;
    IO_BYTE _ST0 :1;
  }bit;
 }ADCT0STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _ANS4 :1;
    IO_BYTE _ANS3 :1;
    IO_BYTE _ANS2 :1;
    IO_BYTE _ANS1 :1;
    IO_BYTE _ASN0 :1;
  }bit;
  struct{
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE _ANS :5;
  }bitc;
 }ADSCHSTR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _ANE4 :1;
    IO_BYTE _ANE3 :1;
    IO_BYTE _ANE2 :1;
    IO_BYTE _ANE1 :1;
    IO_BYTE _ANE0 :1;
  }bit;
  struct{
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE _ANE :5;
  }bitc;
 }ADECHSTR;
typedef union{   /* Clock Calibration */
    IO_WORD	word;
    struct{   
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD _STRT :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD _INT :1;
    IO_WORD _INTEN :1;
  }bit;
 }CUCRSTR;
typedef union{  
    IO_WORD	word;
    struct{   
    IO_WORD _TDD15 :1;
    IO_WORD _TDD14 :1;
    IO_WORD _TDD13 :1;
    IO_WORD _TDD12 :1;
    IO_WORD _TDD11 :1;
    IO_WORD _TDD10 :1;
    IO_WORD _TDD9 :1;
    IO_WORD _TDD8 :1;
    IO_WORD _TDD7 :1;
    IO_WORD _TDD6 :1;
    IO_WORD _TDD5 :1;
    IO_WORD _TDD4 :1;
    IO_WORD _TDD3 :1;
    IO_WORD _TDD2 :1;
    IO_WORD _TDD1 :1;
    IO_WORD _TDD0 :1;
  }bit;
 }CUTDSTR;
typedef union{  
    IO_WORD	word;
    struct{   
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD _TR23 :1;
    IO_WORD _TR22 :1;
    IO_WORD _TR21 :1;
    IO_WORD _TR20 :1;
    IO_WORD _TR19 :1;
    IO_WORD _TR18 :1;
    IO_WORD _TR17 :1;
    IO_WORD _TR16 :1;
  }bit;
 }CUTR1STR;
typedef union{  
    IO_WORD	word;
    struct{   
    IO_WORD _TR15 :1;
    IO_WORD _TR14 :1;
    IO_WORD _TR13 :1;
    IO_WORD _TR12 :1;
    IO_WORD _TR11 :1;
    IO_WORD _TR10 :1;
    IO_WORD _TR9 :1;
    IO_WORD _TR8 :1;
    IO_WORD _TR7 :1;
    IO_WORD _TR6 :1;
    IO_WORD _TR5 :1;
    IO_WORD _TR4 :1;
    IO_WORD _TR3 :1;
    IO_WORD _TR2 :1;
    IO_WORD _TR1 :1;
    IO_WORD _TR0 :1;
  }bit;
 }CUTR2STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _M16E :1;
    IO_BYTE _CDCF :1;
    IO_BYTE _CFIE :1;
    IO_BYTE _CLKS :1;
    IO_BYTE _CMS1 :1;
    IO_BYTE _CMS0 :1;
    IO_BYTE _CES1 :1;
    IO_BYTE _CES0 :1;
  }bit;
  struct{
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE _CMS :2;
    IO_BYTE _CES :2;
  }bitc;
 }UDCCH0STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE  :1;
    IO_BYTE _CTUT :1;
    IO_BYTE _UCRE :1;
    IO_BYTE _RLDE :1;
    IO_BYTE _UDCC :1;
    IO_BYTE _CGSC :1;
    IO_BYTE _CGE1 :1;
    IO_BYTE _CGE0 :1;
  }bit;
  struct{
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE _CGE :2;
  }bitc;
 }UDCCL0STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _CSTR :1;
    IO_BYTE _CITE :1;
    IO_BYTE _UDIE :1;
    IO_BYTE _CMPF :1;
    IO_BYTE _OVFF :1;
    IO_BYTE _UDFF :1;
    IO_BYTE _UDF1 :1;
    IO_BYTE _UDF0 :1;
  }bit;
  struct{
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE _UDF :2;
  }bitc;
 }UDCS0STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _M16E :1;
    IO_BYTE _CDCF :1;
    IO_BYTE _CFIE :1;
    IO_BYTE _CLKS :1;
    IO_BYTE _CMS1 :1;
    IO_BYTE _CMS0 :1;
    IO_BYTE _CES1 :1;
    IO_BYTE _CES0 :1;
  }bit;
  struct{
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE _CMS :2;
    IO_BYTE _CES :2;
  }bitc;
 }UDCCH1STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE  :1;
    IO_BYTE _CTUT :1;
    IO_BYTE _UCRE :1;
    IO_BYTE _RLDE :1;
    IO_BYTE _UDCC :1;
    IO_BYTE _CGSC :1;
    IO_BYTE _CGE1 :1;
    IO_BYTE _CGE0 :1;
  }bit;
  struct{
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE _CGE :2;
  }bitc;
 }UDCCL1STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _CSTR :1;
    IO_BYTE _CITE :1;
    IO_BYTE _UDIE :1;
    IO_BYTE _CMPF :1;
    IO_BYTE _OVFF :1;
    IO_BYTE _UDFF :1;
    IO_BYTE _UDF1 :1;
    IO_BYTE _UDF0 :1;
  }bit;
  struct{
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE _UDF :2;
  }bitc;
 }UDCS1STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _M16E :1;
    IO_BYTE _CDCF :1;
    IO_BYTE _CFIE :1;
    IO_BYTE _CLKS :1;
    IO_BYTE _CMS1 :1;
    IO_BYTE _CMS0 :1;
    IO_BYTE _CES1 :1;
    IO_BYTE _CES0 :1;
  }bit;
  struct{
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE _CMS :2;
    IO_BYTE _CES :2;
  }bitc;
 }UDCCH2STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE  :1;
    IO_BYTE _CTUT :1;
    IO_BYTE _UCRE :1;
    IO_BYTE _RLDE :1;
    IO_BYTE _UDCC :1;
    IO_BYTE _CGSC :1;
    IO_BYTE _CGE1 :1;
    IO_BYTE _CGE0 :1;
  }bit;
  struct{
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE _CGE :2;
  }bitc;
 }UDCCL2STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _CSTR :1;
    IO_BYTE _CITE :1;
    IO_BYTE _UDIE :1;
    IO_BYTE _CMPF :1;
    IO_BYTE _OVFF :1;
    IO_BYTE _UDFF :1;
    IO_BYTE _UDF1 :1;
    IO_BYTE _UDF0 :1;
  }bit;
  struct{
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE _UDF :2;
  }bitc;
 }UDCS2STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _M16E :1;
    IO_BYTE _CDCF :1;
    IO_BYTE _CFIE :1;
    IO_BYTE _CLKS :1;
    IO_BYTE _CMS1 :1;
    IO_BYTE _CMS0 :1;
    IO_BYTE _CES1 :1;
    IO_BYTE _CES0 :1;
  }bit;
  struct{
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE _CMS :2;
    IO_BYTE _CES :2;
  }bitc;
 }UDCCH3STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE  :1;
    IO_BYTE _CTUT :1;
    IO_BYTE _UCRE :1;
    IO_BYTE _RLDE :1;
    IO_BYTE _UDCC :1;
    IO_BYTE _CGSC :1;
    IO_BYTE _CGE1 :1;
    IO_BYTE _CGE0 :1;
  }bit;
  struct{
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE _CGE :2;
  }bitc;
 }UDCCL3STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _CSTR :1;
    IO_BYTE _CITE :1;
    IO_BYTE _UDIE :1;
    IO_BYTE _CMPF :1;
    IO_BYTE _OVFF :1;
    IO_BYTE _UDFF :1;
    IO_BYTE _UDF1 :1;
    IO_BYTE _UDF0 :1;
  }bit;
  struct{
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE _UDF :2;
  }bitc;
 }UDCS3STR;
typedef union{   /* ADC 2 */
    IO_WORD	word;
    struct{   
    IO_WORD _ADE31 :1;
    IO_WORD _ADE30 :1;
    IO_WORD _ADE29 :1;
    IO_WORD _ADE28 :1;
    IO_WORD _ADE27 :1;
    IO_WORD _ADE26 :1;
    IO_WORD _ADE25 :1;
    IO_WORD _ADE24 :1;
    IO_WORD _ADE23 :1;
    IO_WORD _ADE22 :1;
    IO_WORD _ADE21 :1;
    IO_WORD _ADE20 :1;
    IO_WORD _ADE19 :1;
    IO_WORD _ADE18 :1;
    IO_WORD _ADE17 :1;
    IO_WORD _ADE16 :1;
  }bit;
 }AD2ERHSTR;
typedef union{  
    IO_WORD	word;
    struct{   
    IO_WORD _ADE15 :1;
    IO_WORD _ADE14 :1;
    IO_WORD _ADE13 :1;
    IO_WORD _ADE12 :1;
    IO_WORD _ADE11 :1;
    IO_WORD _ADE10 :1;
    IO_WORD _ADE9 :1;
    IO_WORD _ADE8 :1;
    IO_WORD _ADE7 :1;
    IO_WORD _ADE6 :1;
    IO_WORD _ADE5 :1;
    IO_WORD _ADE4 :1;
    IO_WORD _ADE3 :1;
    IO_WORD _ADE2 :1;
    IO_WORD _ADE1 :1;
    IO_WORD _ADE0 :1;
  }bit;
 }AD2ERLSTR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _BUSY :1;
    IO_BYTE _INT :1;
    IO_BYTE _INTE :1;
    IO_BYTE _PAUS :1;
    IO_BYTE _STS1 :1;
    IO_BYTE _STS0 :1;
    IO_BYTE _STRT :1;
    IO_BYTE  :1;
  }bit;
  struct{
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE _STS :2;
  }bitc;
 }AD2CS1STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _MD1 :1;
    IO_BYTE _MD0 :1;
    IO_BYTE _S10 :1;
    IO_BYTE _ACH4 :1;
    IO_BYTE _ACH3 :1;
    IO_BYTE _ACH2 :1;
    IO_BYTE _ACH1 :1;
    IO_BYTE _ACH0 :1;
  }bit;
  struct{
    IO_BYTE _MD :2;
    IO_BYTE :1;
    IO_BYTE _ACH :5;
  }bitc;
 }AD2CS0STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _D9 :1;
    IO_BYTE _D8 :1;
  }bit;
 }AD2CR1STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _D7 :1;
    IO_BYTE _D6 :1;
    IO_BYTE _D5 :1;
    IO_BYTE _D4 :1;
    IO_BYTE _D3 :1;
    IO_BYTE _D2 :1;
    IO_BYTE _D1 :1;
    IO_BYTE _D0 :1;
  }bit;
 }AD2CR0STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _CT5 :1;
    IO_BYTE _CT4 :1;
    IO_BYTE _CT3 :1;
    IO_BYTE _CT2 :1;
    IO_BYTE _CT1 :1;
    IO_BYTE _CT0 :1;
    IO_BYTE _ST9 :1;
    IO_BYTE _ST8 :1;
  }bit;
 }AD2CT1STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _ST7 :1;
    IO_BYTE _ST6 :1;
    IO_BYTE _ST5 :1;
    IO_BYTE _ST4 :1;
    IO_BYTE _ST3 :1;
    IO_BYTE _ST2 :1;
    IO_BYTE _ST1 :1;
    IO_BYTE _ST0 :1;
  }bit;
 }AD2CT0STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _ANS4 :1;
    IO_BYTE _ANS3 :1;
    IO_BYTE _ANS2 :1;
    IO_BYTE _ANS1 :1;
    IO_BYTE _ASN0 :1;
  }bit;
  struct{
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE _ANS :5;
  }bitc;
 }AD2SCHSTR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _ANE4 :1;
    IO_BYTE _ANE3 :1;
    IO_BYTE _ANE2 :1;
    IO_BYTE _ANE1 :1;
    IO_BYTE _ANE0 :1;
  }bit;
  struct{
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE _ANE :5;
  }bitc;
 }AD2ECHSTR;
typedef union{   /* Clock Modulator */
    IO_WORD	word;
    struct{   
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD _MP13 :1;
    IO_WORD _MP12 :1;
    IO_WORD _MP11 :1;
    IO_WORD _MP10 :1;
    IO_WORD _MP9 :1;
    IO_WORD _MP8 :1;
    IO_WORD _MP7 :1;
    IO_WORD _MP6 :1;
    IO_WORD _MP5 :1;
    IO_WORD _MP4 :1;
    IO_WORD _MP3 :1;
    IO_WORD _MP2 :1;
    IO_WORD _MP1 :1;
    IO_WORD _MP0 :1;
  }bit;
 }CMPRSTR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _PHSEL :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _RUN :1;
    IO_BYTE _EN :1;
    IO_BYTE _PDX :1;
  }bit;
 }CMCRSTR;
typedef union{   /* CAN clock control / Ext. Int. Source Sel. */
    IO_BYTE	byte;
    struct{   
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _CANP3 :1;
    IO_BYTE _CANP2 :1;
    IO_BYTE _CANP1 :1;
    IO_BYTE _CANP0 :1;
  }bit;
  struct{
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE _CANP :4;
  }bitc;
 }CANPRESTR;
typedef union{  
    IO_WORD	word;
    struct{   
    IO_WORD _EISS15 :1;
    IO_WORD _EISS14 :1;
    IO_WORD _EISS13 :1;
    IO_WORD _EISS12 :1;
    IO_WORD _EISS11 :1;
    IO_WORD _EISS10 :1;
    IO_WORD _EISS9 :1;
    IO_WORD _EISS8 :1;
    IO_WORD _EISS7 :1;
    IO_WORD _EISS6 :1;
    IO_WORD _EISS5 :1;
    IO_WORD _EISS4 :1;
    IO_WORD _EISS3 :1;
    IO_WORD _EISS2 :1;
    IO_WORD _EISS1 :1;
    IO_WORD _EISS0 :1;
  }bit;
 }EISSRSTR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _PIE :1;
    IO_BYTE _PUF :1;
    IO_BYTE _INTM :1;
    IO_BYTE _PCS1 :1;
    IO_BYTE _PCS0 :1;
    IO_BYTE _MD1 :1;
    IO_BYTE _MD0 :1;
    IO_BYTE  :1;
  }bit;
  struct{
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE _PCS :2;
    IO_BYTE _MD :2;
  }bitc;
 }PPGC0STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _PIE :1;
    IO_BYTE _PUF :1;
    IO_BYTE _INTM :1;
    IO_BYTE _PCS1 :1;
    IO_BYTE _PCS0 :1;
    IO_BYTE _MD1 :1;
    IO_BYTE _MD0 :1;
    IO_BYTE  :1;
  }bit;
  struct{
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE _PCS :2;
    IO_BYTE _MD :2;
  }bitc;
 }PPGC1STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _PIE :1;
    IO_BYTE _PUF :1;
    IO_BYTE _INTM :1;
    IO_BYTE _PCS1 :1;
    IO_BYTE _PCS0 :1;
    IO_BYTE _MD1 :1;
    IO_BYTE _MD0 :1;
    IO_BYTE  :1;
  }bit;
  struct{
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE _PCS :2;
    IO_BYTE _MD :2;
  }bitc;
 }PPGC2STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _PIE :1;
    IO_BYTE _PUF :1;
    IO_BYTE _INTM :1;
    IO_BYTE _PCS1 :1;
    IO_BYTE _PCS0 :1;
    IO_BYTE _MD1 :1;
    IO_BYTE _MD0 :1;
    IO_BYTE  :1;
  }bit;
  struct{
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE _PCS :2;
    IO_BYTE _MD :2;
  }bitc;
 }PPGC3STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _PIE :1;
    IO_BYTE _PUF :1;
    IO_BYTE _INTM :1;
    IO_BYTE _PCS1 :1;
    IO_BYTE _PCS0 :1;
    IO_BYTE _MD1 :1;
    IO_BYTE _MD0 :1;
    IO_BYTE  :1;
  }bit;
  struct{
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE _PCS :2;
    IO_BYTE _MD :2;
  }bitc;
 }PPGC4STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _PIE :1;
    IO_BYTE _PUF :1;
    IO_BYTE _INTM :1;
    IO_BYTE _PCS1 :1;
    IO_BYTE _PCS0 :1;
    IO_BYTE _MD1 :1;
    IO_BYTE _MD0 :1;
    IO_BYTE  :1;
  }bit;
  struct{
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE _PCS :2;
    IO_BYTE _MD :2;
  }bitc;
 }PPGC5STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _PIE :1;
    IO_BYTE _PUF :1;
    IO_BYTE _INTM :1;
    IO_BYTE _PCS1 :1;
    IO_BYTE _PCS0 :1;
    IO_BYTE _MD1 :1;
    IO_BYTE _MD0 :1;
    IO_BYTE  :1;
  }bit;
  struct{
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE _PCS :2;
    IO_BYTE _MD :2;
  }bitc;
 }PPGC6STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _PIE :1;
    IO_BYTE _PUF :1;
    IO_BYTE _INTM :1;
    IO_BYTE _PCS1 :1;
    IO_BYTE _PCS0 :1;
    IO_BYTE _MD1 :1;
    IO_BYTE _MD0 :1;
    IO_BYTE  :1;
  }bit;
  struct{
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE _PCS :2;
    IO_BYTE _MD :2;
  }bitc;
 }PPGC7STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _PIE :1;
    IO_BYTE _PUF :1;
    IO_BYTE _INTM :1;
    IO_BYTE _PCS1 :1;
    IO_BYTE _PCS0 :1;
    IO_BYTE _MD1 :1;
    IO_BYTE _MD0 :1;
    IO_BYTE  :1;
  }bit;
  struct{
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE _PCS :2;
    IO_BYTE _MD :2;
  }bitc;
 }PPGC8STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _PIE :1;
    IO_BYTE _PUF :1;
    IO_BYTE _INTM :1;
    IO_BYTE _PCS1 :1;
    IO_BYTE _PCS0 :1;
    IO_BYTE _MD1 :1;
    IO_BYTE _MD0 :1;
    IO_BYTE  :1;
  }bit;
  struct{
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE _PCS :2;
    IO_BYTE _MD :2;
  }bitc;
 }PPGC9STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _PIE :1;
    IO_BYTE _PUF :1;
    IO_BYTE _INTM :1;
    IO_BYTE _PCS1 :1;
    IO_BYTE _PCS0 :1;
    IO_BYTE _MD1 :1;
    IO_BYTE _MD0 :1;
    IO_BYTE  :1;
  }bit;
  struct{
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE _PCS :2;
    IO_BYTE _MD :2;
  }bitc;
 }PPGCASTR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _PIE :1;
    IO_BYTE _PUF :1;
    IO_BYTE _INTM :1;
    IO_BYTE _PCS1 :1;
    IO_BYTE _PCS0 :1;
    IO_BYTE _MD1 :1;
    IO_BYTE _MD0 :1;
    IO_BYTE  :1;
  }bit;
  struct{
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE _PCS :2;
    IO_BYTE _MD :2;
  }bitc;
 }PPGCBSTR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _PIE :1;
    IO_BYTE _PUF :1;
    IO_BYTE _INTM :1;
    IO_BYTE _PCS1 :1;
    IO_BYTE _PCS0 :1;
    IO_BYTE _MD1 :1;
    IO_BYTE _MD0 :1;
    IO_BYTE  :1;
  }bit;
  struct{
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE _PCS :2;
    IO_BYTE _MD :2;
  }bitc;
 }PPGCCSTR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _PIE :1;
    IO_BYTE _PUF :1;
    IO_BYTE _INTM :1;
    IO_BYTE _PCS1 :1;
    IO_BYTE _PCS0 :1;
    IO_BYTE _MD1 :1;
    IO_BYTE _MD0 :1;
    IO_BYTE  :1;
  }bit;
  struct{
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE _PCS :2;
    IO_BYTE _MD :2;
  }bitc;
 }PPGCDSTR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _PIE :1;
    IO_BYTE _PUF :1;
    IO_BYTE _INTM :1;
    IO_BYTE _PCS1 :1;
    IO_BYTE _PCS0 :1;
    IO_BYTE _MD1 :1;
    IO_BYTE _MD0 :1;
    IO_BYTE  :1;
  }bit;
  struct{
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE _PCS :2;
    IO_BYTE _MD :2;
  }bitc;
 }PPGCESTR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _PIE :1;
    IO_BYTE _PUF :1;
    IO_BYTE _INTM :1;
    IO_BYTE _PCS1 :1;
    IO_BYTE _PCS0 :1;
    IO_BYTE _MD1 :1;
    IO_BYTE _MD0 :1;
    IO_BYTE  :1;
  }bit;
  struct{
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE _PCS :2;
    IO_BYTE _MD :2;
  }bitc;
 }PPGCFSTR;
typedef union{   /* PPG 0-F Enable / Reverse */
    IO_WORD	word;
    struct{   
    IO_WORD _PEN15 :1;
    IO_WORD _PEN14 :1;
    IO_WORD _PEN13 :1;
    IO_WORD _PEN12 :1;
    IO_WORD _PEN11 :1;
    IO_WORD _PEN10 :1;
    IO_WORD _PEN09 :1;
    IO_WORD _PEN08 :1;
    IO_WORD _PEN07 :1;
    IO_WORD _PEN06 :1;
    IO_WORD _PEN05 :1;
    IO_WORD _PEN04 :1;
    IO_WORD _PEN03 :1;
    IO_WORD _PEN02 :1;
    IO_WORD _PEN01 :1;
    IO_WORD _PEN00 :1;
  }bit;
 }PPGTRGSTR;
typedef union{  
    IO_WORD	word;
    struct{   
    IO_WORD _REV15 :1;
    IO_WORD _REV14 :1;
    IO_WORD _REV13 :1;
    IO_WORD _REV12 :1;
    IO_WORD _REV11 :1;
    IO_WORD _REV10 :1;
    IO_WORD _REV09 :1;
    IO_WORD _REV08 :1;
    IO_WORD _REV07 :1;
    IO_WORD _REV06 :1;
    IO_WORD _REV05 :1;
    IO_WORD _REV04 :1;
    IO_WORD _REV03 :1;
    IO_WORD _REV02 :1;
    IO_WORD _REV01 :1;
    IO_WORD _REV00 :1;
  }bit;
 }PPGREVCSTR;
typedef union{   /* Clock Monitor */
    IO_BYTE	byte;
    struct{   
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _CKEN :1;
    IO_BYTE _FRQ2 :1;
    IO_BYTE _FRQ1 :1;
    IO_BYTE _FRQ0 :1;
  }bit;
  struct{
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE _FRQ :3;
  }bitc;
 }CMCLKRSTR;
typedef union{   /* DMAC */
    IO_LWORD	lword;
    struct{   
    IO_LWORD _DENB :1;
    IO_LWORD _PAUS :1;
    IO_LWORD _STRG :1;
    IO_LWORD _IS4 :1;
    IO_LWORD _IS3 :1;
    IO_LWORD _IS2 :1;
    IO_LWORD _IS1 :1;
    IO_LWORD _IS0 :1;
    IO_LWORD _DDN03 :1;
    IO_LWORD _DDN02 :1;
    IO_LWORD _DDN01 :1;
    IO_LWORD _DDN00 :1;
    IO_LWORD _BLK3 :1;
    IO_LWORD _BLK2 :1;
    IO_LWORD _BLK1 :1;
    IO_LWORD _BLK0 :1;
    IO_LWORD _DTCF :1;
    IO_LWORD _DTCE :1;
    IO_LWORD _DTCD :1;
    IO_LWORD _DTCC :1;
    IO_LWORD _DTCB :1;
    IO_LWORD _DTCA :1;
    IO_LWORD _DTC9 :1;
    IO_LWORD _DTC8 :1;
    IO_LWORD _DTC7 :1;
    IO_LWORD _DTC6 :1;
    IO_LWORD _DTC5 :1;
    IO_LWORD _DTC4 :1;
    IO_LWORD _DTC3 :1;
    IO_LWORD _DTC2 :1;
    IO_LWORD _DTC1 :1;
    IO_LWORD _DTC0 :1;
  }bit;
  struct{
    IO_LWORD :1;
    IO_LWORD :1;
    IO_LWORD :1;
    IO_LWORD _IS :5;
    IO_LWORD _DDN0 :4;
    IO_LWORD _BLK :4;
    IO_LWORD _DTC :16;
  }bitc;
 }DMACA0STR;
typedef union{  
    IO_LWORD	lword;
    struct{   
    IO_LWORD _TYPE1 :1;
    IO_LWORD _TYPE0 :1;
    IO_LWORD _MOD1 :1;
    IO_LWORD _MOD0 :1;
    IO_LWORD _WS1 :1;
    IO_LWORD _WS0 :1;
    IO_LWORD _SADM :1;
    IO_LWORD _DADM :1;
    IO_LWORD _DTCR :1;
    IO_LWORD _SADR :1;
    IO_LWORD _DADR :1;
    IO_LWORD _ERIE :1;
    IO_LWORD _EDIE :1;
    IO_LWORD _DSS2 :1;
    IO_LWORD _DSS1 :1;
    IO_LWORD _DSS0 :1;
    IO_LWORD _SASZ7 :1;
    IO_LWORD _SASZ6 :1;
    IO_LWORD _SASZ5 :1;
    IO_LWORD _SASZ4 :1;
    IO_LWORD _SASZ3 :1;
    IO_LWORD _SASZ2 :1;
    IO_LWORD _SASZ1 :1;
    IO_LWORD _SASZ0 :1;
    IO_LWORD _DASZ7 :1;
    IO_LWORD _DASZ6 :1;
    IO_LWORD _DASZ5 :1;
    IO_LWORD _DASZ4 :1;
    IO_LWORD _DASZ3 :1;
    IO_LWORD _DASZ2 :1;
    IO_LWORD _DASZ1 :1;
    IO_LWORD _DASZ0 :1;
  }bit;
  struct{
    IO_LWORD _TYPE :2;
    IO_LWORD _MOD :2;
    IO_LWORD _WS :2;
    IO_LWORD :1;
    IO_LWORD :1;
    IO_LWORD :1;
    IO_LWORD :1;
    IO_LWORD :1;
    IO_LWORD :1;
    IO_LWORD :1;
    IO_LWORD _DSS :3;
    IO_LWORD _SASZ :8;
    IO_LWORD _DASZ :8;
  }bitc;
 }DMACB0STR;
typedef union{  
    IO_LWORD	lword;
    struct{   
    IO_LWORD _DENB :1;
    IO_LWORD _PAUS :1;
    IO_LWORD _STRG :1;
    IO_LWORD _IS4 :1;
    IO_LWORD _IS3 :1;
    IO_LWORD _IS2 :1;
    IO_LWORD _IS1 :1;
    IO_LWORD _IS0 :1;
    IO_LWORD _DDN13 :1;
    IO_LWORD _DDN12 :1;
    IO_LWORD _DDN11 :1;
    IO_LWORD _DDN10 :1;
    IO_LWORD _BLK3 :1;
    IO_LWORD _BLK2 :1;
    IO_LWORD _BLK1 :1;
    IO_LWORD _BLK0 :1;
    IO_LWORD _DTCF :1;
    IO_LWORD _DTCE :1;
    IO_LWORD _DTCD :1;
    IO_LWORD _DTCC :1;
    IO_LWORD _DTCB :1;
    IO_LWORD _DTCA :1;
    IO_LWORD _DTC9 :1;
    IO_LWORD _DTC8 :1;
    IO_LWORD _DTC7 :1;
    IO_LWORD _DTC6 :1;
    IO_LWORD _DTC5 :1;
    IO_LWORD _DTC4 :1;
    IO_LWORD _DTC3 :1;
    IO_LWORD _DTC2 :1;
    IO_LWORD _DTC1 :1;
    IO_LWORD _DTC0 :1;
  }bit;
  struct{
    IO_LWORD :1;
    IO_LWORD :1;
    IO_LWORD :1;
    IO_LWORD _IS :5;
    IO_LWORD _DDN1 :4;
    IO_LWORD _BLK :4;
    IO_LWORD _DTC :16;
  }bitc;
 }DMACA1STR;
typedef union{  
    IO_LWORD	lword;
    struct{   
    IO_LWORD _TYPE1 :1;
    IO_LWORD _TYPE0 :1;
    IO_LWORD _MD1 :1;
    IO_LWORD _MD0 :1;
    IO_LWORD _WS1 :1;
    IO_LWORD _WS0 :1;
    IO_LWORD _SADM :1;
    IO_LWORD _DADM :1;
    IO_LWORD _DTCR :1;
    IO_LWORD _SADR :1;
    IO_LWORD _DADR :1;
    IO_LWORD _ERIE :1;
    IO_LWORD _EDIE :1;
    IO_LWORD _DSS2 :1;
    IO_LWORD _DSS1 :1;
    IO_LWORD _DSS0 :1;
    IO_LWORD _SASZ7 :1;
    IO_LWORD _SASZ6 :1;
    IO_LWORD _SASZ5 :1;
    IO_LWORD _SASZ4 :1;
    IO_LWORD _SASZ3 :1;
    IO_LWORD _SASZ2 :1;
    IO_LWORD _SASZ1 :1;
    IO_LWORD _SASZ0 :1;
    IO_LWORD _DASZ7 :1;
    IO_LWORD _DASZ6 :1;
    IO_LWORD _DASZ5 :1;
    IO_LWORD _DASZ4 :1;
    IO_LWORD _DASZ3 :1;
    IO_LWORD _DASZ2 :1;
    IO_LWORD _DASZ1 :1;
    IO_LWORD _DASZ0 :1;
  }bit;
  struct{
    IO_LWORD _TYPE :2;
    IO_LWORD _MD :2;
    IO_LWORD _WS :2;
    IO_LWORD :1;
    IO_LWORD :1;
    IO_LWORD :1;
    IO_LWORD :1;
    IO_LWORD :1;
    IO_LWORD :1;
    IO_LWORD :1;
    IO_LWORD _DSS :3;
    IO_LWORD _SASZ :8;
    IO_LWORD _DASZ :8;
  }bitc;
 }DMACB1STR;
typedef union{  
    IO_LWORD	lword;
    struct{   
    IO_LWORD _DENB :1;
    IO_LWORD _PAUS :1;
    IO_LWORD _STRG :1;
    IO_LWORD _IS4 :1;
    IO_LWORD _IS3 :1;
    IO_LWORD _IS2 :1;
    IO_LWORD _IS1 :1;
    IO_LWORD _IS0 :1;
    IO_LWORD _DDN23 :1;
    IO_LWORD _DDN22 :1;
    IO_LWORD _DDN21 :1;
    IO_LWORD _DDN20 :1;
    IO_LWORD _BLK3 :1;
    IO_LWORD _BLK2 :1;
    IO_LWORD _BLK1 :1;
    IO_LWORD _BLK0 :1;
    IO_LWORD _DTCF :1;
    IO_LWORD _DTCE :1;
    IO_LWORD _DTCD :1;
    IO_LWORD _DTCC :1;
    IO_LWORD _DTCB :1;
    IO_LWORD _DTCA :1;
    IO_LWORD _DTC9 :1;
    IO_LWORD _DTC8 :1;
    IO_LWORD _DTC7 :1;
    IO_LWORD _DTC6 :1;
    IO_LWORD _DTC5 :1;
    IO_LWORD _DTC4 :1;
    IO_LWORD _DTC3 :1;
    IO_LWORD _DTC2 :1;
    IO_LWORD _DTC1 :1;
    IO_LWORD _DTC0 :1;
  }bit;
  struct{
    IO_LWORD :1;
    IO_LWORD :1;
    IO_LWORD :1;
    IO_LWORD _IS :5;
    IO_LWORD _DDN2 :4;
    IO_LWORD _BLK :4;
    IO_LWORD _DTC :16;
  }bitc;
 }DMACA2STR;
typedef union{  
    IO_LWORD	lword;
    struct{   
    IO_LWORD _TYPE1 :1;
    IO_LWORD _TYPE0 :1;
    IO_LWORD _MD1 :1;
    IO_LWORD _MD0 :1;
    IO_LWORD _WS1 :1;
    IO_LWORD _WS0 :1;
    IO_LWORD _SADM :1;
    IO_LWORD _DADM :1;
    IO_LWORD _DTCR :1;
    IO_LWORD _SADR :1;
    IO_LWORD _DADR :1;
    IO_LWORD _ERIE :1;
    IO_LWORD _EDIE :1;
    IO_LWORD _DSS2 :1;
    IO_LWORD _DSS1 :1;
    IO_LWORD _DSS0 :1;
    IO_LWORD _SASZ7 :1;
    IO_LWORD _SASZ6 :1;
    IO_LWORD _SASZ5 :1;
    IO_LWORD _SASZ4 :1;
    IO_LWORD _SASZ3 :1;
    IO_LWORD _SASZ2 :1;
    IO_LWORD _SASZ1 :1;
    IO_LWORD _SASZ0 :1;
    IO_LWORD _DASZ7 :1;
    IO_LWORD _DASZ6 :1;
    IO_LWORD _DASZ5 :1;
    IO_LWORD _DASZ4 :1;
    IO_LWORD _DASZ3 :1;
    IO_LWORD _DASZ2 :1;
    IO_LWORD _DASZ1 :1;
    IO_LWORD _DASZ0 :1;
  }bit;
  struct{
    IO_LWORD _TYPE :2;
    IO_LWORD _MD :2;
    IO_LWORD _WS :2;
    IO_LWORD :1;
    IO_LWORD :1;
    IO_LWORD :1;
    IO_LWORD :1;
    IO_LWORD :1;
    IO_LWORD :1;
    IO_LWORD :1;
    IO_LWORD _DSS :3;
    IO_LWORD _SASZ :8;
    IO_LWORD _DASZ :8;
  }bitc;
 }DMACB2STR;
typedef union{  
    IO_LWORD	lword;
    struct{   
    IO_LWORD _DENB :1;
    IO_LWORD _PAUS :1;
    IO_LWORD _STRG :1;
    IO_LWORD _IS4 :1;
    IO_LWORD _IS3 :1;
    IO_LWORD _IS2 :1;
    IO_LWORD _IS1 :1;
    IO_LWORD _IS0 :1;
    IO_LWORD _DDN33 :1;
    IO_LWORD _DDN32 :1;
    IO_LWORD _DDN31 :1;
    IO_LWORD _DDN30 :1;
    IO_LWORD _BLK3 :1;
    IO_LWORD _BLK2 :1;
    IO_LWORD _BLK1 :1;
    IO_LWORD _BLK0 :1;
    IO_LWORD _DTCF :1;
    IO_LWORD _DTCE :1;
    IO_LWORD _DTCD :1;
    IO_LWORD _DTCC :1;
    IO_LWORD _DTCB :1;
    IO_LWORD _DTCA :1;
    IO_LWORD _DTC9 :1;
    IO_LWORD _DTC8 :1;
    IO_LWORD _DTC7 :1;
    IO_LWORD _DTC6 :1;
    IO_LWORD _DTC5 :1;
    IO_LWORD _DTC4 :1;
    IO_LWORD _DTC3 :1;
    IO_LWORD _DTC2 :1;
    IO_LWORD _DTC1 :1;
    IO_LWORD _DTC0 :1;
  }bit;
  struct{
    IO_LWORD :1;
    IO_LWORD :1;
    IO_LWORD :1;
    IO_LWORD _IS :5;
    IO_LWORD _DDN3 :4;
    IO_LWORD _BLK :4;
    IO_LWORD _DTC :16;
  }bitc;
 }DMACA3STR;
typedef union{  
    IO_LWORD	lword;
    struct{   
    IO_LWORD _TYPE1 :1;
    IO_LWORD _TYPE0 :1;
    IO_LWORD _MD1 :1;
    IO_LWORD _MD0 :1;
    IO_LWORD _WS1 :1;
    IO_LWORD _WS0 :1;
    IO_LWORD _SADM :1;
    IO_LWORD _DADM :1;
    IO_LWORD _DTCR :1;
    IO_LWORD _SADR :1;
    IO_LWORD _DADR :1;
    IO_LWORD _ERIE :1;
    IO_LWORD _EDIE :1;
    IO_LWORD _DSS2 :1;
    IO_LWORD _DSS1 :1;
    IO_LWORD _DSS0 :1;
    IO_LWORD _SASZ7 :1;
    IO_LWORD _SASZ6 :1;
    IO_LWORD _SASZ5 :1;
    IO_LWORD _SASZ4 :1;
    IO_LWORD _SASZ3 :1;
    IO_LWORD _SASZ2 :1;
    IO_LWORD _SASZ1 :1;
    IO_LWORD _SASZ0 :1;
    IO_LWORD _DASZ7 :1;
    IO_LWORD _DASZ6 :1;
    IO_LWORD _DASZ5 :1;
    IO_LWORD _DASZ4 :1;
    IO_LWORD _DASZ3 :1;
    IO_LWORD _DASZ2 :1;
    IO_LWORD _DASZ1 :1;
    IO_LWORD _DASZ0 :1;
  }bit;
  struct{
    IO_LWORD _TYPE :2;
    IO_LWORD _MD :2;
    IO_LWORD _WS :2;
    IO_LWORD :1;
    IO_LWORD :1;
    IO_LWORD :1;
    IO_LWORD :1;
    IO_LWORD :1;
    IO_LWORD :1;
    IO_LWORD :1;
    IO_LWORD _DSS :3;
    IO_LWORD _SASZ :8;
    IO_LWORD _DASZ :8;
  }bitc;
 }DMACB3STR;
typedef union{  
    IO_LWORD	lword;
    struct{   
    IO_LWORD _DENB :1;
    IO_LWORD _PAUS :1;
    IO_LWORD _STRG :1;
    IO_LWORD _IS4 :1;
    IO_LWORD _IS3 :1;
    IO_LWORD _IS2 :1;
    IO_LWORD _IS1 :1;
    IO_LWORD _IS0 :1;
    IO_LWORD _DDN43 :1;
    IO_LWORD _DDN42 :1;
    IO_LWORD _DDN41 :1;
    IO_LWORD _DDN40 :1;
    IO_LWORD _BLK3 :1;
    IO_LWORD _BLK2 :1;
    IO_LWORD _BLK1 :1;
    IO_LWORD _BLK0 :1;
    IO_LWORD _DTCF :1;
    IO_LWORD _DTCE :1;
    IO_LWORD _DTCD :1;
    IO_LWORD _DTCC :1;
    IO_LWORD _DTCB :1;
    IO_LWORD _DTCA :1;
    IO_LWORD _DTC9 :1;
    IO_LWORD _DTC8 :1;
    IO_LWORD _DTC7 :1;
    IO_LWORD _DTC6 :1;
    IO_LWORD _DTC5 :1;
    IO_LWORD _DTC4 :1;
    IO_LWORD _DTC3 :1;
    IO_LWORD _DTC2 :1;
    IO_LWORD _DTC1 :1;
    IO_LWORD _DTC0 :1;
  }bit;
  struct{
    IO_LWORD :1;
    IO_LWORD :1;
    IO_LWORD :1;
    IO_LWORD _IS :5;
    IO_LWORD _DDN4 :4;
    IO_LWORD _BLK :4;
    IO_LWORD _DTC :16;
  }bitc;
 }DMACA4STR;
typedef union{  
    IO_LWORD	lword;
    struct{   
    IO_LWORD _TYPE1 :1;
    IO_LWORD _TYPE0 :1;
    IO_LWORD _MD1 :1;
    IO_LWORD _MD0 :1;
    IO_LWORD _WS1 :1;
    IO_LWORD _WS0 :1;
    IO_LWORD _SADM :1;
    IO_LWORD _DADM :1;
    IO_LWORD _DTCR :1;
    IO_LWORD _SADR :1;
    IO_LWORD _DADR :1;
    IO_LWORD _ERIE :1;
    IO_LWORD _EDIE :1;
    IO_LWORD _DSS2 :1;
    IO_LWORD _DSS1 :1;
    IO_LWORD _DSS0 :1;
    IO_LWORD _SASZ7 :1;
    IO_LWORD _SASZ6 :1;
    IO_LWORD _SASZ5 :1;
    IO_LWORD _SASZ4 :1;
    IO_LWORD _SASZ3 :1;
    IO_LWORD _SASZ2 :1;
    IO_LWORD _SASZ1 :1;
    IO_LWORD _SASZ0 :1;
    IO_LWORD _DASZ7 :1;
    IO_LWORD _DASZ6 :1;
    IO_LWORD _DASZ5 :1;
    IO_LWORD _DASZ4 :1;
    IO_LWORD _DASZ3 :1;
    IO_LWORD _DASZ2 :1;
    IO_LWORD _DASZ1 :1;
    IO_LWORD _DASZ0 :1;
  }bit;
  struct{
    IO_LWORD _TYPE :2;
    IO_LWORD _MD :2;
    IO_LWORD _WS :2;
    IO_LWORD :1;
    IO_LWORD :1;
    IO_LWORD :1;
    IO_LWORD :1;
    IO_LWORD :1;
    IO_LWORD :1;
    IO_LWORD :1;
    IO_LWORD _DSS :3;
    IO_LWORD _SASZ :8;
    IO_LWORD _DASZ :8;
  }bitc;
 }DMACB4STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _DMAE :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _PM01 :1;
    IO_BYTE _DMAH3 :1;
    IO_BYTE _DMAH2 :1;
    IO_BYTE _DMAH1 :1;
    IO_BYTE _DMAH0 :1;
  }bit;
  struct{
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE _DMAH :4;
  }bitc;
 }DMACRSTR;
typedef union{   /* Data Direction Register */
    IO_BYTE	byte;
    struct{   
    IO_BYTE _D07 :1;
    IO_BYTE _D06 :1;
    IO_BYTE _D05 :1;
    IO_BYTE _D04 :1;
    IO_BYTE _D03 :1;
    IO_BYTE _D02 :1;
    IO_BYTE _D01 :1;
    IO_BYTE _D00 :1;
  }bit;
 }DDR0STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _D17 :1;
    IO_BYTE _D16 :1;
    IO_BYTE _D15 :1;
    IO_BYTE _D14 :1;
    IO_BYTE _D13 :1;
    IO_BYTE _D12 :1;
    IO_BYTE _D11 :1;
    IO_BYTE _D10 :1;
  }bit;
 }DDR1STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _D27 :1;
    IO_BYTE _D26 :1;
    IO_BYTE _D25 :1;
    IO_BYTE _D24 :1;
    IO_BYTE _D23 :1;
    IO_BYTE _D22 :1;
    IO_BYTE _D21 :1;
    IO_BYTE _D20 :1;
  }bit;
 }DDR2STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _D37 :1;
    IO_BYTE _D36 :1;
    IO_BYTE _D35 :1;
    IO_BYTE _D34 :1;
    IO_BYTE _D33 :1;
    IO_BYTE _D32 :1;
    IO_BYTE _D31 :1;
    IO_BYTE _D30 :1;
  }bit;
 }DDR3STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _D47 :1;
    IO_BYTE _D46 :1;
    IO_BYTE _D45 :1;
    IO_BYTE _D44 :1;
    IO_BYTE _D43 :1;
    IO_BYTE _D42 :1;
    IO_BYTE _D41 :1;
    IO_BYTE _D40 :1;
  }bit;
 }DDR4STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _D57 :1;
    IO_BYTE _D56 :1;
    IO_BYTE _D55 :1;
    IO_BYTE _D54 :1;
    IO_BYTE _D53 :1;
    IO_BYTE _D52 :1;
    IO_BYTE _D51 :1;
    IO_BYTE _D50 :1;
  }bit;
 }DDR5STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _D67 :1;
    IO_BYTE _D66 :1;
    IO_BYTE _D65 :1;
    IO_BYTE _D64 :1;
    IO_BYTE _D63 :1;
    IO_BYTE _D62 :1;
    IO_BYTE _D61 :1;
    IO_BYTE _D60 :1;
  }bit;
 }DDR6STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _D77 :1;
    IO_BYTE _D76 :1;
    IO_BYTE _D75 :1;
    IO_BYTE _D74 :1;
    IO_BYTE _D73 :1;
    IO_BYTE _D72 :1;
    IO_BYTE _D71 :1;
    IO_BYTE _D70 :1;
  }bit;
 }DDR7STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _D87 :1;
    IO_BYTE _D86 :1;
    IO_BYTE _D85 :1;
    IO_BYTE _D84 :1;
    IO_BYTE _D83 :1;
    IO_BYTE _D82 :1;
    IO_BYTE _D81 :1;
    IO_BYTE _D80 :1;
  }bit;
 }DDR8STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _D97 :1;
    IO_BYTE _D96 :1;
    IO_BYTE _D95 :1;
    IO_BYTE _D94 :1;
    IO_BYTE _D93 :1;
    IO_BYTE _D92 :1;
    IO_BYTE _D91 :1;
    IO_BYTE _D90 :1;
  }bit;
 }DDR9STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _DA1 :1;
    IO_BYTE _DA0 :1;
  }bit;
 }DDRASTR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _DB5 :1;
    IO_BYTE _DB4 :1;
    IO_BYTE _DB3 :1;
    IO_BYTE _DB2 :1;
    IO_BYTE _DB1 :1;
    IO_BYTE _DB0 :1;
  }bit;
 }DDRBSTR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _DC7 :1;
    IO_BYTE _DC6 :1;
    IO_BYTE _DC5 :1;
    IO_BYTE _DC4 :1;
    IO_BYTE _DC3 :1;
    IO_BYTE _DC2 :1;
    IO_BYTE _DC1 :1;
    IO_BYTE _DC0 :1;
  }bit;
 }DDRCSTR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _DD7 :1;
    IO_BYTE _DD6 :1;
    IO_BYTE _DD5 :1;
    IO_BYTE _DD4 :1;
    IO_BYTE _DD3 :1;
    IO_BYTE _DD2 :1;
    IO_BYTE _DD1 :1;
    IO_BYTE _DD0 :1;
  }bit;
 }DDRDSTR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _DE7 :1;
    IO_BYTE _DE6 :1;
    IO_BYTE _DE5 :1;
    IO_BYTE _DE4 :1;
    IO_BYTE _DE3 :1;
    IO_BYTE _DE2 :1;
    IO_BYTE _DE1 :1;
    IO_BYTE _DE0 :1;
  }bit;
 }DDRESTR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _DF7 :1;
    IO_BYTE _DF6 :1;
    IO_BYTE _DF5 :1;
    IO_BYTE _DF4 :1;
    IO_BYTE _DF3 :1;
    IO_BYTE _DF2 :1;
    IO_BYTE _DF1 :1;
    IO_BYTE _DF0 :1;
  }bit;
 }DDRFSTR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _DG7 :1;
    IO_BYTE _DG6 :1;
    IO_BYTE _DG5 :1;
    IO_BYTE _DG4 :1;
    IO_BYTE _DG3 :1;
    IO_BYTE _DG2 :1;
    IO_BYTE _DG1 :1;
    IO_BYTE _DG0 :1;
  }bit;
 }DDRGSTR;
typedef union{   /* Port Function Register */
    IO_BYTE	byte;
    struct{   
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _F05 :1;
    IO_BYTE _F04 :1;
    IO_BYTE  :1;
    IO_BYTE _F02 :1;
    IO_BYTE _F01 :1;
    IO_BYTE  :1;
  }bit;
 }PFR0STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _F17 :1;
    IO_BYTE _F06 :1;
    IO_BYTE  :1;
    IO_BYTE _F04 :1;
    IO_BYTE _F03 :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
  }bit;
 }PFR1STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _F27 :1;
    IO_BYTE _F06 :1;
    IO_BYTE _F05 :1;
    IO_BYTE _F04 :1;
    IO_BYTE _F03 :1;
    IO_BYTE _F02 :1;
    IO_BYTE _F01 :1;
    IO_BYTE _F00 :1;
  }bit;
 }PFR2STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _F07 :1;
    IO_BYTE _F06 :1;
    IO_BYTE _F05 :1;
    IO_BYTE _F04 :1;
    IO_BYTE _F03 :1;
    IO_BYTE  :1;
    IO_BYTE _F01 :1;
    IO_BYTE _F00 :1;
  }bit;
 }PFR3STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _F07 :1;
    IO_BYTE _F06 :1;
    IO_BYTE _F05 :1;
    IO_BYTE _F04 :1;
    IO_BYTE _F03 :1;
    IO_BYTE _F02 :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
  }bit;
 }PFR4STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _F02 :1;
    IO_BYTE _F01 :1;
    IO_BYTE  :1;
  }bit;
 }PFR5STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _F07 :1;
    IO_BYTE _F06 :1;
    IO_BYTE _F05 :1;
    IO_BYTE _F04 :1;
    IO_BYTE _F03 :1;
    IO_BYTE _F02 :1;
    IO_BYTE _F01 :1;
    IO_BYTE _F00 :1;
  }bit;
 }PFR6STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _F07 :1;
    IO_BYTE _F06 :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
  }bit;
 }PFR7STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _F07 :1;
    IO_BYTE _F06 :1;
    IO_BYTE  :1;
    IO_BYTE _F04 :1;
    IO_BYTE _F03 :1;
    IO_BYTE  :1;
    IO_BYTE _F01 :1;
    IO_BYTE  :1;
  }bit;
 }PFR8STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _F07 :1;
    IO_BYTE _F06 :1;
    IO_BYTE _F05 :1;
    IO_BYTE _F04 :1;
    IO_BYTE _F03 :1;
    IO_BYTE _F02 :1;
    IO_BYTE _F01 :1;
    IO_BYTE _F00 :1;
  }bit;
 }PFR9STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _F01 :1;
    IO_BYTE _F00 :1;
  }bit;
 }PFRASTR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _F05 :1;
    IO_BYTE _F04 :1;
    IO_BYTE _F03 :1;
    IO_BYTE _F02 :1;
    IO_BYTE _F01 :1;
    IO_BYTE _F00 :1;
  }bit;
 }PFRBSTR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _F07 :1;
    IO_BYTE _F06 :1;
    IO_BYTE _F05 :1;
    IO_BYTE _F04 :1;
    IO_BYTE _F03 :1;
    IO_BYTE _F02 :1;
    IO_BYTE _F01 :1;
    IO_BYTE _F00 :1;
  }bit;
 }PFRCSTR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _F07 :1;
    IO_BYTE _F06 :1;
    IO_BYTE _F05 :1;
    IO_BYTE _F04 :1;
    IO_BYTE _F03 :1;
    IO_BYTE _F02 :1;
    IO_BYTE _F01 :1;
    IO_BYTE _F00 :1;
  }bit;
 }PFRDSTR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
  }bit;
 }PFRESTR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
  }bit;
 }PFRFSTR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
  }bit;
 }PFRGSTR;
typedef union{   /* Interrupt Control Unit */
    IO_BYTE	byte;
    struct{   
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _ICR4 :1;
    IO_BYTE _ICR3 :1;
    IO_BYTE _ICR2 :1;
    IO_BYTE _ICR1 :1;
    IO_BYTE _ICR0 :1;
  }bit;
 }ICR00STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _ICR4 :1;
    IO_BYTE _ICR3 :1;
    IO_BYTE _ICR2 :1;
    IO_BYTE _ICR1 :1;
    IO_BYTE _ICR0 :1;
  }bit;
 }ICR01STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _ICR4 :1;
    IO_BYTE _ICR3 :1;
    IO_BYTE _ICR2 :1;
    IO_BYTE _ICR1 :1;
    IO_BYTE _ICR0 :1;
  }bit;
 }ICR02STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _ICR4 :1;
    IO_BYTE _ICR3 :1;
    IO_BYTE _ICR2 :1;
    IO_BYTE _ICR1 :1;
    IO_BYTE _ICR0 :1;
  }bit;
 }ICR03STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _ICR4 :1;
    IO_BYTE _ICR3 :1;
    IO_BYTE _ICR2 :1;
    IO_BYTE _ICR1 :1;
    IO_BYTE _ICR0 :1;
  }bit;
 }ICR04STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _ICR4 :1;
    IO_BYTE _ICR3 :1;
    IO_BYTE _ICR2 :1;
    IO_BYTE _ICR1 :1;
    IO_BYTE _ICR0 :1;
  }bit;
 }ICR05STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _ICR4 :1;
    IO_BYTE _ICR3 :1;
    IO_BYTE _ICR2 :1;
    IO_BYTE _ICR1 :1;
    IO_BYTE _ICR0 :1;
  }bit;
 }ICR06STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _ICR4 :1;
    IO_BYTE _ICR3 :1;
    IO_BYTE _ICR2 :1;
    IO_BYTE _ICR1 :1;
    IO_BYTE _ICR0 :1;
  }bit;
 }ICR07STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _ICR4 :1;
    IO_BYTE _ICR3 :1;
    IO_BYTE _ICR2 :1;
    IO_BYTE _ICR1 :1;
    IO_BYTE _ICR0 :1;
  }bit;
 }ICR08STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _ICR4 :1;
    IO_BYTE _ICR3 :1;
    IO_BYTE _ICR2 :1;
    IO_BYTE _ICR1 :1;
    IO_BYTE _ICR0 :1;
  }bit;
 }ICR09STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _ICR4 :1;
    IO_BYTE _ICR3 :1;
    IO_BYTE _ICR2 :1;
    IO_BYTE _ICR1 :1;
    IO_BYTE _ICR0 :1;
  }bit;
 }ICR10STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _ICR4 :1;
    IO_BYTE _ICR3 :1;
    IO_BYTE _ICR2 :1;
    IO_BYTE _ICR1 :1;
    IO_BYTE _ICR0 :1;
  }bit;
 }ICR11STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _ICR4 :1;
    IO_BYTE _ICR3 :1;
    IO_BYTE _ICR2 :1;
    IO_BYTE _ICR1 :1;
    IO_BYTE _ICR0 :1;
  }bit;
 }ICR12STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _ICR4 :1;
    IO_BYTE _ICR3 :1;
    IO_BYTE _ICR2 :1;
    IO_BYTE _ICR1 :1;
    IO_BYTE _ICR0 :1;
  }bit;
 }ICR13STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _ICR4 :1;
    IO_BYTE _ICR3 :1;
    IO_BYTE _ICR2 :1;
    IO_BYTE _ICR1 :1;
    IO_BYTE _ICR0 :1;
  }bit;
 }ICR14STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _ICR4 :1;
    IO_BYTE _ICR3 :1;
    IO_BYTE _ICR2 :1;
    IO_BYTE _ICR1 :1;
    IO_BYTE _ICR0 :1;
  }bit;
 }ICR15STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _ICR4 :1;
    IO_BYTE _ICR3 :1;
    IO_BYTE _ICR2 :1;
    IO_BYTE _ICR1 :1;
    IO_BYTE _ICR0 :1;
  }bit;
 }ICR16STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _ICR4 :1;
    IO_BYTE _ICR3 :1;
    IO_BYTE _ICR2 :1;
    IO_BYTE _ICR1 :1;
    IO_BYTE _ICR0 :1;
  }bit;
 }ICR17STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _ICR4 :1;
    IO_BYTE _ICR3 :1;
    IO_BYTE _ICR2 :1;
    IO_BYTE _ICR1 :1;
    IO_BYTE _ICR0 :1;
  }bit;
 }ICR18STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _ICR4 :1;
    IO_BYTE _ICR3 :1;
    IO_BYTE _ICR2 :1;
    IO_BYTE _ICR1 :1;
    IO_BYTE _ICR0 :1;
  }bit;
 }ICR19STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _ICR4 :1;
    IO_BYTE _ICR3 :1;
    IO_BYTE _ICR2 :1;
    IO_BYTE _ICR1 :1;
    IO_BYTE _ICR0 :1;
  }bit;
 }ICR20STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _ICR4 :1;
    IO_BYTE _ICR3 :1;
    IO_BYTE _ICR2 :1;
    IO_BYTE _ICR1 :1;
    IO_BYTE _ICR0 :1;
  }bit;
 }ICR21STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _ICR4 :1;
    IO_BYTE _ICR3 :1;
    IO_BYTE _ICR2 :1;
    IO_BYTE _ICR1 :1;
    IO_BYTE _ICR0 :1;
  }bit;
 }ICR22STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _ICR4 :1;
    IO_BYTE _ICR3 :1;
    IO_BYTE _ICR2 :1;
    IO_BYTE _ICR1 :1;
    IO_BYTE _ICR0 :1;
  }bit;
 }ICR23STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _ICR4 :1;
    IO_BYTE _ICR3 :1;
    IO_BYTE _ICR2 :1;
    IO_BYTE _ICR1 :1;
    IO_BYTE _ICR0 :1;
  }bit;
 }ICR24STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _ICR4 :1;
    IO_BYTE _ICR3 :1;
    IO_BYTE _ICR2 :1;
    IO_BYTE _ICR1 :1;
    IO_BYTE _ICR0 :1;
  }bit;
 }ICR25STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _ICR4 :1;
    IO_BYTE _ICR3 :1;
    IO_BYTE _ICR2 :1;
    IO_BYTE _ICR1 :1;
    IO_BYTE _ICR0 :1;
  }bit;
 }ICR26STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _ICR4 :1;
    IO_BYTE _ICR3 :1;
    IO_BYTE _ICR2 :1;
    IO_BYTE _ICR1 :1;
    IO_BYTE _ICR0 :1;
  }bit;
 }ICR27STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _ICR4 :1;
    IO_BYTE _ICR3 :1;
    IO_BYTE _ICR2 :1;
    IO_BYTE _ICR1 :1;
    IO_BYTE _ICR0 :1;
  }bit;
 }ICR28STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _ICR4 :1;
    IO_BYTE _ICR3 :1;
    IO_BYTE _ICR2 :1;
    IO_BYTE _ICR1 :1;
    IO_BYTE _ICR0 :1;
  }bit;
 }ICR29STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _ICR4 :1;
    IO_BYTE _ICR3 :1;
    IO_BYTE _ICR2 :1;
    IO_BYTE _ICR1 :1;
    IO_BYTE _ICR0 :1;
  }bit;
 }ICR30STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _ICR4 :1;
    IO_BYTE _ICR3 :1;
    IO_BYTE _ICR2 :1;
    IO_BYTE _ICR1 :1;
    IO_BYTE _ICR0 :1;
  }bit;
 }ICR31STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _ICR4 :1;
    IO_BYTE _ICR3 :1;
    IO_BYTE _ICR2 :1;
    IO_BYTE _ICR1 :1;
    IO_BYTE _ICR0 :1;
  }bit;
 }ICR32STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _ICR4 :1;
    IO_BYTE _ICR3 :1;
    IO_BYTE _ICR2 :1;
    IO_BYTE _ICR1 :1;
    IO_BYTE _ICR0 :1;
  }bit;
 }ICR33STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _ICR4 :1;
    IO_BYTE _ICR3 :1;
    IO_BYTE _ICR2 :1;
    IO_BYTE _ICR1 :1;
    IO_BYTE _ICR0 :1;
  }bit;
 }ICR34STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _ICR4 :1;
    IO_BYTE _ICR3 :1;
    IO_BYTE _ICR2 :1;
    IO_BYTE _ICR1 :1;
    IO_BYTE _ICR0 :1;
  }bit;
 }ICR35STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _ICR4 :1;
    IO_BYTE _ICR3 :1;
    IO_BYTE _ICR2 :1;
    IO_BYTE _ICR1 :1;
    IO_BYTE _ICR0 :1;
  }bit;
 }ICR36STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _ICR4 :1;
    IO_BYTE _ICR3 :1;
    IO_BYTE _ICR2 :1;
    IO_BYTE _ICR1 :1;
    IO_BYTE _ICR0 :1;
  }bit;
 }ICR37STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _ICR4 :1;
    IO_BYTE _ICR3 :1;
    IO_BYTE _ICR2 :1;
    IO_BYTE _ICR1 :1;
    IO_BYTE _ICR0 :1;
  }bit;
 }ICR38STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _ICR4 :1;
    IO_BYTE _ICR3 :1;
    IO_BYTE _ICR2 :1;
    IO_BYTE _ICR1 :1;
    IO_BYTE _ICR0 :1;
  }bit;
 }ICR39STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _ICR4 :1;
    IO_BYTE _ICR3 :1;
    IO_BYTE _ICR2 :1;
    IO_BYTE _ICR1 :1;
    IO_BYTE _ICR0 :1;
  }bit;
 }ICR40STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _ICR4 :1;
    IO_BYTE _ICR3 :1;
    IO_BYTE _ICR2 :1;
    IO_BYTE _ICR1 :1;
    IO_BYTE _ICR0 :1;
  }bit;
 }ICR41STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _ICR4 :1;
    IO_BYTE _ICR3 :1;
    IO_BYTE _ICR2 :1;
    IO_BYTE _ICR1 :1;
    IO_BYTE _ICR0 :1;
  }bit;
 }ICR42STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _ICR4 :1;
    IO_BYTE _ICR3 :1;
    IO_BYTE _ICR2 :1;
    IO_BYTE _ICR1 :1;
    IO_BYTE _ICR0 :1;
  }bit;
 }ICR43STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _ICR4 :1;
    IO_BYTE _ICR3 :1;
    IO_BYTE _ICR2 :1;
    IO_BYTE _ICR1 :1;
    IO_BYTE _ICR0 :1;
  }bit;
 }ICR44STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _ICR4 :1;
    IO_BYTE _ICR3 :1;
    IO_BYTE _ICR2 :1;
    IO_BYTE _ICR1 :1;
    IO_BYTE _ICR0 :1;
  }bit;
 }ICR45STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _ICR4 :1;
    IO_BYTE _ICR3 :1;
    IO_BYTE _ICR2 :1;
    IO_BYTE _ICR1 :1;
    IO_BYTE _ICR0 :1;
  }bit;
 }ICR46STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _ICR4 :1;
    IO_BYTE _ICR3 :1;
    IO_BYTE _ICR2 :1;
    IO_BYTE _ICR1 :1;
    IO_BYTE _ICR0 :1;
  }bit;
 }ICR47STR;
typedef union{   /* Clock Control Unit */
    IO_BYTE	byte;
    struct{   
    IO_BYTE _INIT :1;
    IO_BYTE  :1;
    IO_BYTE _WDOG :1;
    IO_BYTE  :1;
    IO_BYTE _SRST :1;
    IO_BYTE  :1;
    IO_BYTE _WT1 :1;
    IO_BYTE _WT0 :1;
  }bit;
  struct{
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE _WT :2;
  }bitc;
 }RSRRSTR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _STOP :1;
    IO_BYTE _SLEEP :1;
    IO_BYTE _HIZ :1;
    IO_BYTE _SRST :1;
    IO_BYTE _OS1 :1;
    IO_BYTE _OS0 :1;
    IO_BYTE _OSCD2 :1;
    IO_BYTE _OSCD1 :1;
  }bit;
  struct{
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE _OS :2;
    IO_BYTE _OSCD :2;
  }bitc;
 }STCRSTR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _TBIF :1;
    IO_BYTE _TBIE :1;
    IO_BYTE _TBC2 :1;
    IO_BYTE _TBC1 :1;
    IO_BYTE _TBC0 :1;
    IO_BYTE  :1;
    IO_BYTE _SYNCR :1;
    IO_BYTE _SYNCS :1;
  }bit;
  struct{
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE _TBC :3;
  }bitc;
 }TBCRSTR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _D7 :1;
    IO_BYTE _D6 :1;
    IO_BYTE _D5 :1;
    IO_BYTE _D4 :1;
    IO_BYTE _D3 :1;
    IO_BYTE _D2 :1;
    IO_BYTE _D1 :1;
    IO_BYTE _D0 :1;
  }bit;
 }CTBRSTR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE  :1;
    IO_BYTE _PLL1S2 :1;
    IO_BYTE _PLL1S1 :1;
    IO_BYTE _PLL1S0 :1;
    IO_BYTE _PLL2EN :1;
    IO_BYTE _PLL1EN :1;
    IO_BYTE _CLKS1 :1;
    IO_BYTE _CLKS0 :1;
  }bit;
  struct{
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE _CLKS :2;
  }bitc;
 }CLKRSTR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _D7 :1;
    IO_BYTE _D6 :1;
    IO_BYTE _D5 :1;
    IO_BYTE _D4 :1;
    IO_BYTE _D3 :1;
    IO_BYTE _D2 :1;
    IO_BYTE _D1 :1;
    IO_BYTE _D0 :1;
  }bit;
 }WPRSTR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _B3 :1;
    IO_BYTE _B2 :1;
    IO_BYTE _B1 :1;
    IO_BYTE _B0 :1;
    IO_BYTE _P3 :1;
    IO_BYTE _P2 :1;
    IO_BYTE _P1 :1;
    IO_BYTE _P0 :1;
  }bit;
  struct{
    IO_BYTE _B :4;
    IO_BYTE _P :4;
  }bitc;
 }DIVR0STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _T3 :1;
    IO_BYTE _T2 :1;
    IO_BYTE _T1 :1;
    IO_BYTE _T0 :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
  }bit;
  struct{
    IO_BYTE _T :4;
  }bitc;
 }DIVR1STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _OSCDS1 :1;
  }bit;
 }OSCCRSTR;
typedef union{   /* Stb. Wait Timer */
    IO_BYTE	byte;
    struct{   
    IO_BYTE _WIF :1;
    IO_BYTE _WIE :1;
    IO_BYTE _WEN :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _WS1 :1;
    IO_BYTE _WS0 :1;
    IO_BYTE _WCL :1;
  }bit;
  struct{
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE _WS :2;
  }bitc;
 }OSCRSTR;
typedef union{   /* Clock-Supervisor */
    IO_BYTE	byte;
    struct{   
    IO_BYTE  :1;
    IO_BYTE _MM :1;
    IO_BYTE _SM :1;
    IO_BYTE _RCE :1;
    IO_BYTE _MSVE :1;
    IO_BYTE _SSVE :1;
    IO_BYTE _SRST :1;
    IO_BYTE  :1;
  }bit;
 }CSVCRSTR;
typedef union{   /* Pull-Up/Down Enable Register */
    IO_BYTE	byte;
    struct{   
    IO_BYTE _P07 :1;
    IO_BYTE _P06 :1;
    IO_BYTE _P05 :1;
    IO_BYTE _P04 :1;
    IO_BYTE _P03 :1;
    IO_BYTE _P02 :1;
    IO_BYTE _P01 :1;
    IO_BYTE _P00 :1;
  }bit;
 }PPER0STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _P17 :1;
    IO_BYTE _P16 :1;
    IO_BYTE _P15 :1;
    IO_BYTE _P14 :1;
    IO_BYTE _P13 :1;
    IO_BYTE _P12 :1;
    IO_BYTE _P11 :1;
    IO_BYTE _P10 :1;
  }bit;
 }PPER1STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _P27 :1;
    IO_BYTE _P26 :1;
    IO_BYTE _P25 :1;
    IO_BYTE _P24 :1;
    IO_BYTE _P23 :1;
    IO_BYTE _P22 :1;
    IO_BYTE _P21 :1;
    IO_BYTE _P20 :1;
  }bit;
 }PPER2STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _P37 :1;
    IO_BYTE _P36 :1;
    IO_BYTE _P35 :1;
    IO_BYTE _P34 :1;
    IO_BYTE _P33 :1;
    IO_BYTE _P32 :1;
    IO_BYTE _P31 :1;
    IO_BYTE _P30 :1;
  }bit;
 }PPER3STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _P43 :1;
    IO_BYTE _P42 :1;
    IO_BYTE _P41 :1;
    IO_BYTE _P40 :1;
  }bit;
 }PPER4STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _P55 :1;
    IO_BYTE _P54 :1;
    IO_BYTE _P53 :1;
    IO_BYTE _P52 :1;
    IO_BYTE _P51 :1;
    IO_BYTE _P50 :1;
  }bit;
 }PPER5STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _P67 :1;
    IO_BYTE _P66 :1;
    IO_BYTE _P65 :1;
    IO_BYTE _P64 :1;
    IO_BYTE _P63 :1;
    IO_BYTE _P62 :1;
    IO_BYTE _P61 :1;
    IO_BYTE _P60 :1;
  }bit;
 }PPER6STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _P75 :1;
    IO_BYTE _P74 :1;
    IO_BYTE _P73 :1;
    IO_BYTE _P72 :1;
    IO_BYTE _P71 :1;
    IO_BYTE _P70 :1;
  }bit;
 }PPER7STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _P87 :1;
    IO_BYTE _P86 :1;
    IO_BYTE _P85 :1;
    IO_BYTE _P84 :1;
    IO_BYTE _P83 :1;
    IO_BYTE _P82 :1;
    IO_BYTE _P81 :1;
    IO_BYTE _P80 :1;
  }bit;
 }PPER8STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _P97 :1;
    IO_BYTE _P96 :1;
    IO_BYTE _P95 :1;
    IO_BYTE _P94 :1;
    IO_BYTE _P93 :1;
    IO_BYTE _P92 :1;
    IO_BYTE _P91 :1;
    IO_BYTE _P90 :1;
  }bit;
 }PPER9STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _PA1 :1;
    IO_BYTE _PA0 :1;
  }bit;
 }PPERASTR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _PB5 :1;
    IO_BYTE _PB4 :1;
    IO_BYTE _PB3 :1;
    IO_BYTE _PB2 :1;
    IO_BYTE _PB1 :1;
    IO_BYTE _PB0 :1;
  }bit;
 }PPERBSTR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _PC7 :1;
    IO_BYTE _PC6 :1;
    IO_BYTE _PC5 :1;
    IO_BYTE _PC4 :1;
    IO_BYTE _PC3 :1;
    IO_BYTE _PC2 :1;
    IO_BYTE _PC1 :1;
    IO_BYTE _PC0 :1;
  }bit;
 }PPERCSTR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _PD7 :1;
    IO_BYTE _PD6 :1;
    IO_BYTE _PD5 :1;
    IO_BYTE _PD4 :1;
    IO_BYTE _PD3 :1;
    IO_BYTE _PD2 :1;
    IO_BYTE _PD1 :1;
    IO_BYTE _PD0 :1;
  }bit;
 }PPERDSTR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _PE7 :1;
    IO_BYTE _PE6 :1;
    IO_BYTE _PE5 :1;
    IO_BYTE _PE4 :1;
    IO_BYTE _PE3 :1;
    IO_BYTE _PE2 :1;
    IO_BYTE _PE1 :1;
    IO_BYTE _PE0 :1;
  }bit;
 }PPERESTR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _PF7 :1;
    IO_BYTE _PF6 :1;
    IO_BYTE _PF5 :1;
    IO_BYTE _PF4 :1;
    IO_BYTE _PF3 :1;
    IO_BYTE _PF2 :1;
    IO_BYTE _PF1 :1;
    IO_BYTE _PF0 :1;
  }bit;
 }PPERFSTR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _PG7 :1;
    IO_BYTE _PG6 :1;
    IO_BYTE _PG5 :1;
    IO_BYTE _PG4 :1;
    IO_BYTE _PG3 :1;
    IO_BYTE _PG2 :1;
    IO_BYTE _PG1 :1;
    IO_BYTE _PG0 :1;
  }bit;
 }PPERGSTR;
typedef union{   /* Pull-Up/Down  Control Register */
    IO_BYTE	byte;
    struct{   
    IO_BYTE _P07 :1;
    IO_BYTE _P06 :1;
    IO_BYTE _P05 :1;
    IO_BYTE _P04 :1;
    IO_BYTE _P03 :1;
    IO_BYTE _P02 :1;
    IO_BYTE _P01 :1;
    IO_BYTE _P00 :1;
  }bit;
 }PPCR0STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _P17 :1;
    IO_BYTE _P16 :1;
    IO_BYTE _P15 :1;
    IO_BYTE _P14 :1;
    IO_BYTE _P13 :1;
    IO_BYTE _P12 :1;
    IO_BYTE _P11 :1;
    IO_BYTE _P10 :1;
  }bit;
 }PPCR1STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _P27 :1;
    IO_BYTE _P26 :1;
    IO_BYTE _P25 :1;
    IO_BYTE _P24 :1;
    IO_BYTE _P23 :1;
    IO_BYTE _P22 :1;
    IO_BYTE _P21 :1;
    IO_BYTE _P20 :1;
  }bit;
 }PPCR2STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _P37 :1;
    IO_BYTE _P36 :1;
    IO_BYTE _P35 :1;
    IO_BYTE _P34 :1;
    IO_BYTE _P33 :1;
    IO_BYTE _P32 :1;
    IO_BYTE _P31 :1;
    IO_BYTE _P30 :1;
  }bit;
 }PPCR3STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _P43 :1;
    IO_BYTE _P42 :1;
    IO_BYTE _P41 :1;
    IO_BYTE _P40 :1;
  }bit;
 }PPCR4STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _P55 :1;
    IO_BYTE _P54 :1;
    IO_BYTE _P53 :1;
    IO_BYTE _P52 :1;
    IO_BYTE _P51 :1;
    IO_BYTE _P50 :1;
  }bit;
 }PPCR5STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _P67 :1;
    IO_BYTE _P66 :1;
    IO_BYTE _P65 :1;
    IO_BYTE _P64 :1;
    IO_BYTE _P63 :1;
    IO_BYTE _P62 :1;
    IO_BYTE _P61 :1;
    IO_BYTE _P60 :1;
  }bit;
 }PPCR6STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _P75 :1;
    IO_BYTE _P74 :1;
    IO_BYTE _P73 :1;
    IO_BYTE _P72 :1;
    IO_BYTE _P71 :1;
    IO_BYTE _P70 :1;
  }bit;
 }PPCR7STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _P87 :1;
    IO_BYTE _P86 :1;
    IO_BYTE _P85 :1;
    IO_BYTE _P84 :1;
    IO_BYTE _P83 :1;
    IO_BYTE _P82 :1;
    IO_BYTE _P81 :1;
    IO_BYTE _P80 :1;
  }bit;
 }PPCR8STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _P97 :1;
    IO_BYTE _P96 :1;
    IO_BYTE _P95 :1;
    IO_BYTE _P94 :1;
    IO_BYTE _P93 :1;
    IO_BYTE _P92 :1;
    IO_BYTE _P91 :1;
    IO_BYTE _P90 :1;
  }bit;
 }PPCR9STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _PA1 :1;
    IO_BYTE _PA0 :1;
  }bit;
 }PPCRASTR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _PB5 :1;
    IO_BYTE _PB4 :1;
    IO_BYTE _PB3 :1;
    IO_BYTE _PB2 :1;
    IO_BYTE _PB1 :1;
    IO_BYTE _PB0 :1;
  }bit;
 }PPCRBSTR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _PC7 :1;
    IO_BYTE _PC6 :1;
    IO_BYTE _PC5 :1;
    IO_BYTE _PC4 :1;
    IO_BYTE _PC3 :1;
    IO_BYTE _PC2 :1;
    IO_BYTE _PC1 :1;
    IO_BYTE _PC0 :1;
  }bit;
 }PPCRCSTR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _PD7 :1;
    IO_BYTE _PD6 :1;
    IO_BYTE _PD5 :1;
    IO_BYTE _PD4 :1;
    IO_BYTE _PD3 :1;
    IO_BYTE _PD2 :1;
    IO_BYTE _PD1 :1;
    IO_BYTE _PD0 :1;
  }bit;
 }PPCRDSTR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _PE7 :1;
    IO_BYTE _PE6 :1;
    IO_BYTE _PE5 :1;
    IO_BYTE _PE4 :1;
    IO_BYTE _PE3 :1;
    IO_BYTE _PE2 :1;
    IO_BYTE _PE1 :1;
    IO_BYTE _PE0 :1;
  }bit;
 }PPCRESTR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _PF7 :1;
    IO_BYTE _PF6 :1;
    IO_BYTE _PF5 :1;
    IO_BYTE _PF4 :1;
    IO_BYTE _PF3 :1;
    IO_BYTE _PF2 :1;
    IO_BYTE _PF1 :1;
    IO_BYTE _PF0 :1;
  }bit;
 }PPCRFSTR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _PG7 :1;
    IO_BYTE _PG6 :1;
    IO_BYTE _PG5 :1;
    IO_BYTE _PG4 :1;
    IO_BYTE _PG3 :1;
    IO_BYTE _PG2 :1;
    IO_BYTE _PG1 :1;
    IO_BYTE _PG0 :1;
  }bit;
 }PPCRGSTR;
typedef union{   /* Port Input Level select Registers */
    IO_BYTE	byte;
    struct{   
    IO_BYTE _P07 :1;
    IO_BYTE _P06 :1;
    IO_BYTE _P05 :1;
    IO_BYTE _P04 :1;
    IO_BYTE _P03 :1;
    IO_BYTE _P02 :1;
    IO_BYTE _P01 :1;
    IO_BYTE _P00 :1;
  }bit;
 }PILR0STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _P17 :1;
    IO_BYTE _P16 :1;
    IO_BYTE _P15 :1;
    IO_BYTE _P14 :1;
    IO_BYTE _P13 :1;
    IO_BYTE _P12 :1;
    IO_BYTE _P11 :1;
    IO_BYTE _P10 :1;
  }bit;
 }PILR1STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _P27 :1;
    IO_BYTE _P26 :1;
    IO_BYTE _P25 :1;
    IO_BYTE _P24 :1;
    IO_BYTE _P23 :1;
    IO_BYTE _P22 :1;
    IO_BYTE _P21 :1;
    IO_BYTE _P20 :1;
  }bit;
 }PILR2STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _P37 :1;
    IO_BYTE _P36 :1;
    IO_BYTE _P35 :1;
    IO_BYTE _P34 :1;
    IO_BYTE _P33 :1;
    IO_BYTE _P32 :1;
    IO_BYTE _P31 :1;
    IO_BYTE _P30 :1;
  }bit;
 }PILR3STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _P47 :1;
    IO_BYTE _P46 :1;
    IO_BYTE _P45 :1;
    IO_BYTE _P44 :1;
    IO_BYTE _P43 :1;
    IO_BYTE _P42 :1;
    IO_BYTE _P41 :1;
    IO_BYTE _P40 :1;
  }bit;
 }PILR4STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _P57 :1;
    IO_BYTE _P56 :1;
    IO_BYTE _P55 :1;
    IO_BYTE _P54 :1;
    IO_BYTE _P53 :1;
    IO_BYTE _P52 :1;
    IO_BYTE _P51 :1;
    IO_BYTE _P50 :1;
  }bit;
 }PILR5STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _P67 :1;
    IO_BYTE _P66 :1;
    IO_BYTE _P65 :1;
    IO_BYTE _P64 :1;
    IO_BYTE _P63 :1;
    IO_BYTE _P62 :1;
    IO_BYTE _P61 :1;
    IO_BYTE _P60 :1;
  }bit;
 }PILR6STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _P77 :1;
    IO_BYTE _P76 :1;
    IO_BYTE _P75 :1;
    IO_BYTE _P74 :1;
    IO_BYTE _P73 :1;
    IO_BYTE _P72 :1;
    IO_BYTE _P71 :1;
    IO_BYTE _P70 :1;
  }bit;
 }PILR7STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _P87 :1;
    IO_BYTE _P86 :1;
    IO_BYTE _P85 :1;
    IO_BYTE _P84 :1;
    IO_BYTE _P83 :1;
    IO_BYTE _P82 :1;
    IO_BYTE _P81 :1;
    IO_BYTE _P80 :1;
  }bit;
 }PILR8STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _P97 :1;
    IO_BYTE _P96 :1;
    IO_BYTE _P95 :1;
    IO_BYTE _P94 :1;
    IO_BYTE _P93 :1;
    IO_BYTE _P92 :1;
    IO_BYTE _P91 :1;
    IO_BYTE _P90 :1;
  }bit;
 }PILR9STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _PA1 :1;
    IO_BYTE _PA0 :1;
  }bit;
 }PILRASTR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _PB5 :1;
    IO_BYTE _PB4 :1;
    IO_BYTE _PB3 :1;
    IO_BYTE _PB2 :1;
    IO_BYTE _PB1 :1;
    IO_BYTE _PB0 :1;
  }bit;
 }PILRBSTR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _PC7 :1;
    IO_BYTE _PC6 :1;
    IO_BYTE _PC5 :1;
    IO_BYTE _PC4 :1;
    IO_BYTE _PC3 :1;
    IO_BYTE _PC2 :1;
    IO_BYTE _PC1 :1;
    IO_BYTE _PC0 :1;
  }bit;
 }PILRCSTR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _PD7 :1;
    IO_BYTE _PD6 :1;
    IO_BYTE _PD5 :1;
    IO_BYTE _PD4 :1;
    IO_BYTE _PD3 :1;
    IO_BYTE _PD2 :1;
    IO_BYTE _PD1 :1;
    IO_BYTE _PD0 :1;
  }bit;
 }PILRDSTR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _PE7 :1;
    IO_BYTE _PE6 :1;
    IO_BYTE _PE5 :1;
    IO_BYTE _PE4 :1;
    IO_BYTE _PE3 :1;
    IO_BYTE _PE2 :1;
    IO_BYTE _PE1 :1;
    IO_BYTE _PE0 :1;
  }bit;
 }PILRESTR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _PF7 :1;
    IO_BYTE _PF6 :1;
    IO_BYTE _PF5 :1;
    IO_BYTE _PF4 :1;
    IO_BYTE _PF3 :1;
    IO_BYTE _PF2 :1;
    IO_BYTE _PF1 :1;
    IO_BYTE _PF0 :1;
  }bit;
 }PILRFSTR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _PG7 :1;
    IO_BYTE _PG6 :1;
    IO_BYTE _PG5 :1;
    IO_BYTE _PG4 :1;
    IO_BYTE _PG3 :1;
    IO_BYTE _PG2 :1;
    IO_BYTE _PG1 :1;
    IO_BYTE _PG0 :1;
  }bit;
 }PILRGSTR;
typedef union{   /* I2C 0 */
    IO_BYTE	byte;
    struct{   
    IO_BYTE _BER :1;
    IO_BYTE _BEIE :1;
    IO_BYTE _SCC :1;
    IO_BYTE _MSS :1;
    IO_BYTE _ACK :1;
    IO_BYTE _GCAA :1;
    IO_BYTE _INTE :1;
    IO_BYTE _INT :1;
  }bit;
 }IBCR0STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _BB :1;
    IO_BYTE _RSC :1;
    IO_BYTE _AL :1;
    IO_BYTE _LRB :1;
    IO_BYTE _TRX :1;
    IO_BYTE _AAS :1;
    IO_BYTE _GCA :1;
    IO_BYTE _ADT :1;
  }bit;
 }IBSR0STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _TA9 :1;
    IO_BYTE _TA8 :1;
  }bit;
 }ITBAH0STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _TA7 :1;
    IO_BYTE _TA6 :1;
    IO_BYTE _TA5 :1;
    IO_BYTE _TA4 :1;
    IO_BYTE _TA3 :1;
    IO_BYTE _TA2 :1;
    IO_BYTE _TA1 :1;
    IO_BYTE _TA0 :1;
  }bit;
 }ITBAL0STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _ENTB :1;
    IO_BYTE _RAL :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _TM9 :1;
    IO_BYTE _TM8 :1;
  }bit;
 }ITMKH0STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _TM7 :1;
    IO_BYTE _TM6 :1;
    IO_BYTE _TM5 :1;
    IO_BYTE _TM4 :1;
    IO_BYTE _TM3 :1;
    IO_BYTE _TM2 :1;
    IO_BYTE _TM1 :1;
    IO_BYTE _TM0 :1;
  }bit;
 }ITMKL0STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _ENSB :1;
    IO_BYTE _SM6 :1;
    IO_BYTE _SM5 :1;
    IO_BYTE _SM4 :1;
    IO_BYTE _SM3 :1;
    IO_BYTE _SM2 :1;
    IO_BYTE _SM1 :1;
    IO_BYTE _SM0 :1;
  }bit;
 }ISMK0STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE  :1;
    IO_BYTE _SA6 :1;
    IO_BYTE _SA5 :1;
    IO_BYTE _SA4 :1;
    IO_BYTE _SA3 :1;
    IO_BYTE _SA2 :1;
    IO_BYTE _SA1 :1;
    IO_BYTE _SA0 :1;
  }bit;
 }ISBA0STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _D7 :1;
    IO_BYTE _D6 :1;
    IO_BYTE _D5 :1;
    IO_BYTE _D4 :1;
    IO_BYTE _D3 :1;
    IO_BYTE _D2 :1;
    IO_BYTE _D1 :1;
    IO_BYTE _D0 :1;
  }bit;
 }IDAR0STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE  :1;
    IO_BYTE _NSF :1;
    IO_BYTE _EN :1;
    IO_BYTE _CS4 :1;
    IO_BYTE _CS3 :1;
    IO_BYTE _CS2 :1;
    IO_BYTE _CS1 :1;
    IO_BYTE _CS0 :1;
  }bit;
  struct{
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE _CS :5;
  }bitc;
 }ICCR0STR;
typedef union{   /* I2C 1 */
    IO_BYTE	byte;
    struct{   
    IO_BYTE _BER :1;
    IO_BYTE _BEIE :1;
    IO_BYTE _SCC :1;
    IO_BYTE _MSS :1;
    IO_BYTE _ACK :1;
    IO_BYTE _GCAA :1;
    IO_BYTE _INTE :1;
    IO_BYTE _INT :1;
  }bit;
 }IBCR1STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _BB :1;
    IO_BYTE _RSC :1;
    IO_BYTE _AL :1;
    IO_BYTE _LRB :1;
    IO_BYTE _TRX :1;
    IO_BYTE _AAS :1;
    IO_BYTE _GCA :1;
    IO_BYTE _ADT :1;
  }bit;
 }IBSR1STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _TA9 :1;
    IO_BYTE _TA8 :1;
  }bit;
 }ITBAH1STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _TA7 :1;
    IO_BYTE _TA6 :1;
    IO_BYTE _TA5 :1;
    IO_BYTE _TA4 :1;
    IO_BYTE _TA3 :1;
    IO_BYTE _TA2 :1;
    IO_BYTE _TA1 :1;
    IO_BYTE _TA0 :1;
  }bit;
 }ITBAL1STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _ENTB :1;
    IO_BYTE _RAL :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _TM9 :1;
    IO_BYTE _TM8 :1;
  }bit;
 }ITMKH1STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _TM7 :1;
    IO_BYTE _TM6 :1;
    IO_BYTE _TM5 :1;
    IO_BYTE _TM4 :1;
    IO_BYTE _TM3 :1;
    IO_BYTE _TM2 :1;
    IO_BYTE _TM1 :1;
    IO_BYTE _TM0 :1;
  }bit;
 }ITMKL1STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _ENSB :1;
    IO_BYTE _SM6 :1;
    IO_BYTE _SM5 :1;
    IO_BYTE _SM4 :1;
    IO_BYTE _SM3 :1;
    IO_BYTE _SM2 :1;
    IO_BYTE _SM1 :1;
    IO_BYTE _SM0 :1;
  }bit;
 }ISMK1STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE  :1;
    IO_BYTE _SA6 :1;
    IO_BYTE _SA5 :1;
    IO_BYTE _SA4 :1;
    IO_BYTE _SA3 :1;
    IO_BYTE _SA2 :1;
    IO_BYTE _SA1 :1;
    IO_BYTE _SA0 :1;
  }bit;
 }ISBA1STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _D7 :1;
    IO_BYTE _D6 :1;
    IO_BYTE _D5 :1;
    IO_BYTE _D4 :1;
    IO_BYTE _D3 :1;
    IO_BYTE _D2 :1;
    IO_BYTE _D1 :1;
    IO_BYTE _D0 :1;
  }bit;
 }IDAR1STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE  :1;
    IO_BYTE _NSF :1;
    IO_BYTE _EN :1;
    IO_BYTE _CS4 :1;
    IO_BYTE _CS3 :1;
    IO_BYTE _CS2 :1;
    IO_BYTE _CS1 :1;
    IO_BYTE _CS0 :1;
  }bit;
  struct{
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE _CS :5;
  }bitc;
 }ICCR1STR;
typedef union{   /* I2C 2 */
    IO_BYTE	byte;
    struct{   
    IO_BYTE _BER :1;
    IO_BYTE _BEIE :1;
    IO_BYTE _SCC :1;
    IO_BYTE _MSS :1;
    IO_BYTE _ACK :1;
    IO_BYTE _GCAA :1;
    IO_BYTE _INTE :1;
    IO_BYTE _INT :1;
  }bit;
 }IBCR2STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _BB :1;
    IO_BYTE _RSC :1;
    IO_BYTE _AL :1;
    IO_BYTE _LRB :1;
    IO_BYTE _TRX :1;
    IO_BYTE _AAS :1;
    IO_BYTE _GCA :1;
    IO_BYTE _ADT :1;
  }bit;
 }IBSR2STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _TA9 :1;
    IO_BYTE _TA8 :1;
  }bit;
 }ITBAH2STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _TA7 :1;
    IO_BYTE _TA6 :1;
    IO_BYTE _TA5 :1;
    IO_BYTE _TA4 :1;
    IO_BYTE _TA3 :1;
    IO_BYTE _TA2 :1;
    IO_BYTE _TA1 :1;
    IO_BYTE _TA0 :1;
  }bit;
 }ITBAL2STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _ENTB :1;
    IO_BYTE _RAL :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _TM9 :1;
    IO_BYTE _TM8 :1;
  }bit;
 }ITMKH2STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _TM7 :1;
    IO_BYTE _TM6 :1;
    IO_BYTE _TM5 :1;
    IO_BYTE _TM4 :1;
    IO_BYTE _TM3 :1;
    IO_BYTE _TM2 :1;
    IO_BYTE _TM1 :1;
    IO_BYTE _TM0 :1;
  }bit;
 }ITMKL2STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _ENSB :1;
    IO_BYTE _SM6 :1;
    IO_BYTE _SM5 :1;
    IO_BYTE _SM4 :1;
    IO_BYTE _SM3 :1;
    IO_BYTE _SM2 :1;
    IO_BYTE _SM1 :1;
    IO_BYTE _SM0 :1;
  }bit;
 }ISMK2STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE  :1;
    IO_BYTE _SA6 :1;
    IO_BYTE _SA5 :1;
    IO_BYTE _SA4 :1;
    IO_BYTE _SA3 :1;
    IO_BYTE _SA2 :1;
    IO_BYTE _SA1 :1;
    IO_BYTE _SA0 :1;
  }bit;
 }ISBA2STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _D7 :1;
    IO_BYTE _D6 :1;
    IO_BYTE _D5 :1;
    IO_BYTE _D4 :1;
    IO_BYTE _D3 :1;
    IO_BYTE _D2 :1;
    IO_BYTE _D1 :1;
    IO_BYTE _D0 :1;
  }bit;
 }IDAR2STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE  :1;
    IO_BYTE _NSF :1;
    IO_BYTE _EN :1;
    IO_BYTE _CS4 :1;
    IO_BYTE _CS3 :1;
    IO_BYTE _CS2 :1;
    IO_BYTE _CS1 :1;
    IO_BYTE _CS0 :1;
  }bit;
  struct{
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE _CS :5;
  }bitc;
 }ICCR2STR;
typedef union{   /* Hardware-Watchdog */
    IO_BYTE	byte;
    struct{   
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _CL :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _CPUF :1;
  }bit;
 }HWDCSSTR;
typedef union{   /* Extra Port Function Register */
    IO_BYTE	byte;
    struct{   
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
  }bit;
 }EPFR0STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _F11 :1;
    IO_BYTE  :1;
  }bit;
 }EPFR1STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _F27 :1;
    IO_BYTE _F26 :1;
    IO_BYTE _F25 :1;
    IO_BYTE _F24 :1;
    IO_BYTE _F23 :1;
    IO_BYTE _F22 :1;
    IO_BYTE _F21 :1;
    IO_BYTE _F20 :1;
  }bit;
 }EPFR2STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _F37 :1;
    IO_BYTE _F36 :1;
    IO_BYTE _F35 :1;
    IO_BYTE _F34 :1;
    IO_BYTE _F33 :1;
    IO_BYTE _F32 :1;
    IO_BYTE _F31 :1;
    IO_BYTE _F30 :1;
  }bit;
 }EPFR3STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _F43 :1;
    IO_BYTE _F42 :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
  }bit;
 }EPFR4STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _F83 :1;
    IO_BYTE  :1;
    IO_BYTE _F81 :1;
    IO_BYTE  :1;
  }bit;
 }EPFR8STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _F93 :1;
    IO_BYTE _F92 :1;
    IO_BYTE _F91 :1;
    IO_BYTE _F90 :1;
  }bit;
 }EPFR9STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _FB5 :1;
    IO_BYTE _FB4 :1;
    IO_BYTE _FB3 :1;
    IO_BYTE _FB2 :1;
    IO_BYTE _FB1 :1;
    IO_BYTE _FB0 :1;
  }bit;
 }EPFRBSTR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _FE7 :1;
    IO_BYTE _FE6 :1;
    IO_BYTE _FE5 :1;
    IO_BYTE _FE4 :1;
    IO_BYTE _FE3 :1;
    IO_BYTE _FE2 :1;
    IO_BYTE _FE1 :1;
    IO_BYTE _FE0 :1;
  }bit;
 }EPFRESTR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _FF7 :1;
    IO_BYTE _FF6 :1;
    IO_BYTE _FF5 :1;
    IO_BYTE _FF4 :1;
    IO_BYTE _FF3 :1;
    IO_BYTE _FF2 :1;
    IO_BYTE _FF1 :1;
    IO_BYTE _FF0 :1;
  }bit;
 }EPFRFSTR;
typedef union{   /* Port Input Direct data Registers */
    IO_BYTE	byte;
    struct{   
    IO_BYTE _D07 :1;
    IO_BYTE _D06 :1;
    IO_BYTE _D05 :1;
    IO_BYTE _D04 :1;
    IO_BYTE _D03 :1;
    IO_BYTE _D02 :1;
    IO_BYTE _D01 :1;
    IO_BYTE _D00 :1;
  }bit;
 }PIDR0STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _D17 :1;
    IO_BYTE _D16 :1;
    IO_BYTE _D15 :1;
    IO_BYTE _D14 :1;
    IO_BYTE _D13 :1;
    IO_BYTE _D12 :1;
    IO_BYTE _D11 :1;
    IO_BYTE _D10 :1;
  }bit;
 }PIDR1STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _D27 :1;
    IO_BYTE _D26 :1;
    IO_BYTE _D25 :1;
    IO_BYTE _D24 :1;
    IO_BYTE _D23 :1;
    IO_BYTE _D22 :1;
    IO_BYTE _D21 :1;
    IO_BYTE _D20 :1;
  }bit;
 }PIDR2STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _D37 :1;
    IO_BYTE _D36 :1;
    IO_BYTE _D35 :1;
    IO_BYTE _D34 :1;
    IO_BYTE _D33 :1;
    IO_BYTE _D32 :1;
    IO_BYTE _D31 :1;
    IO_BYTE _D30 :1;
  }bit;
 }PIDR3STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _D47 :1;
    IO_BYTE _D46 :1;
    IO_BYTE _D45 :1;
    IO_BYTE _D44 :1;
    IO_BYTE _D43 :1;
    IO_BYTE _D42 :1;
    IO_BYTE _D41 :1;
    IO_BYTE _D40 :1;
  }bit;
 }PIDR4STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _D57 :1;
    IO_BYTE _D56 :1;
    IO_BYTE _D55 :1;
    IO_BYTE _D54 :1;
    IO_BYTE _D53 :1;
    IO_BYTE _D52 :1;
    IO_BYTE _D51 :1;
    IO_BYTE _D50 :1;
  }bit;
 }PIDR5STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _D67 :1;
    IO_BYTE _D66 :1;
    IO_BYTE _D65 :1;
    IO_BYTE _D64 :1;
    IO_BYTE _D63 :1;
    IO_BYTE _D62 :1;
    IO_BYTE _D61 :1;
    IO_BYTE _D60 :1;
  }bit;
 }PIDR6STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _D77 :1;
    IO_BYTE _D76 :1;
    IO_BYTE _D75 :1;
    IO_BYTE _D74 :1;
    IO_BYTE _D73 :1;
    IO_BYTE _D72 :1;
    IO_BYTE _D71 :1;
    IO_BYTE _D70 :1;
  }bit;
 }PIDR7STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _D87 :1;
    IO_BYTE _D86 :1;
    IO_BYTE _D85 :1;
    IO_BYTE _D84 :1;
    IO_BYTE _D83 :1;
    IO_BYTE _D82 :1;
    IO_BYTE _D81 :1;
    IO_BYTE _D80 :1;
  }bit;
 }PIDR8STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _D97 :1;
    IO_BYTE _D96 :1;
    IO_BYTE _D95 :1;
    IO_BYTE _D94 :1;
    IO_BYTE _D93 :1;
    IO_BYTE _D92 :1;
    IO_BYTE _D91 :1;
    IO_BYTE _D90 :1;
  }bit;
 }PIDR9STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _DA1 :1;
    IO_BYTE _DA0 :1;
  }bit;
 }PIDRASTR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _DB5 :1;
    IO_BYTE _DB4 :1;
    IO_BYTE _DB3 :1;
    IO_BYTE _DB2 :1;
    IO_BYTE _DB1 :1;
    IO_BYTE _DB0 :1;
  }bit;
 }PIDRBSTR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _DC7 :1;
    IO_BYTE _DC6 :1;
    IO_BYTE _DC5 :1;
    IO_BYTE _DC4 :1;
    IO_BYTE _DC3 :1;
    IO_BYTE _DC2 :1;
    IO_BYTE _DC1 :1;
    IO_BYTE _DC0 :1;
  }bit;
 }PIDRCSTR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _DD7 :1;
    IO_BYTE _DD6 :1;
    IO_BYTE _DD5 :1;
    IO_BYTE _DD4 :1;
    IO_BYTE _DD3 :1;
    IO_BYTE _DD2 :1;
    IO_BYTE _DD1 :1;
    IO_BYTE _DD0 :1;
  }bit;
 }PIDRDSTR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _DE7 :1;
    IO_BYTE _DE6 :1;
    IO_BYTE _DE5 :1;
    IO_BYTE _DE4 :1;
    IO_BYTE _DE3 :1;
    IO_BYTE _DE2 :1;
    IO_BYTE _DE1 :1;
    IO_BYTE _DE0 :1;
  }bit;
 }PIDRESTR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _DF7 :1;
    IO_BYTE _DF6 :1;
    IO_BYTE _DF5 :1;
    IO_BYTE _DF4 :1;
    IO_BYTE _DF3 :1;
    IO_BYTE _DF2 :1;
    IO_BYTE _DF1 :1;
    IO_BYTE _DF0 :1;
  }bit;
 }PIDRFSTR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE _DG7 :1;
    IO_BYTE _DG6 :1;
    IO_BYTE _DG5 :1;
    IO_BYTE _DG4 :1;
    IO_BYTE _DG3 :1;
    IO_BYTE _DG2 :1;
    IO_BYTE _DG1 :1;
    IO_BYTE _DG0 :1;
  }bit;
 }PIDRGSTR;
typedef union{   /* T-Unit */
    IO_WORD	word;
    struct{   
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD _A23 :1;
    IO_WORD _A22 :1;
    IO_WORD _A21 :1;
    IO_WORD _A20 :1;
    IO_WORD _A19 :1;
    IO_WORD _A18 :1;
    IO_WORD _A17 :1;
    IO_WORD _A16 :1;
  }bit;
 }ASR0STR;
typedef union{  
    IO_WORD	word;
    struct{   
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD _ASZ1 :1;
    IO_WORD _ASZ0 :1;
    IO_WORD  :1;
    IO_WORD _DBW0 :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD _WREN :1;
    IO_WORD  :1;
    IO_WORD _TYP3 :1;
    IO_WORD _TYP2 :1;
    IO_WORD _TYP1 :1;
    IO_WORD _TYP0 :1;
  }bit;
  struct{
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD _ASZ :2;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD _TYP :4;
  }bitc;
 }ACR0STR;
typedef union{  
    IO_WORD	word;
    struct{   
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD _A23 :1;
    IO_WORD _A22 :1;
    IO_WORD _A21 :1;
    IO_WORD _A20 :1;
    IO_WORD _A19 :1;
    IO_WORD _A18 :1;
    IO_WORD _A17 :1;
    IO_WORD _A16 :1;
  }bit;
 }ASR1STR;
typedef union{  
    IO_WORD	word;
    struct{   
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD _ASZ1 :1;
    IO_WORD _ASZ0 :1;
    IO_WORD  :1;
    IO_WORD _DBW0 :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD _WREN :1;
    IO_WORD  :1;
    IO_WORD _TYP3 :1;
    IO_WORD _TYP2 :1;
    IO_WORD _TYP1 :1;
    IO_WORD _TYP0 :1;
  }bit;
  struct{
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD _ASZ :2;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD _TYP :4;
  }bitc;
 }ACR1STR;
typedef union{  
    IO_WORD	word;
    struct{   
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD _A23 :1;
    IO_WORD _A22 :1;
    IO_WORD _A21 :1;
    IO_WORD _A20 :1;
    IO_WORD _A19 :1;
    IO_WORD _A18 :1;
    IO_WORD _A17 :1;
    IO_WORD _A16 :1;
  }bit;
 }ASR2STR;
typedef union{  
    IO_WORD	word;
    struct{   
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD _ASZ1 :1;
    IO_WORD _ASZ0 :1;
    IO_WORD  :1;
    IO_WORD _DBW0 :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD _WREN :1;
    IO_WORD  :1;
    IO_WORD _TYP3 :1;
    IO_WORD _TYP2 :1;
    IO_WORD _TYP1 :1;
    IO_WORD _TYP0 :1;
  }bit;
  struct{
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD _ASZ :2;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD _TYP :4;
  }bitc;
 }ACR2STR;
typedef union{  
    IO_WORD	word;
    struct{   
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD _A23 :1;
    IO_WORD _A22 :1;
    IO_WORD _A21 :1;
    IO_WORD _A20 :1;
    IO_WORD _A19 :1;
    IO_WORD _A18 :1;
    IO_WORD _A17 :1;
    IO_WORD _A16 :1;
  }bit;
 }ASR3STR;
typedef union{  
    IO_WORD	word;
    struct{   
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD _ASZ1 :1;
    IO_WORD _ASZ0 :1;
    IO_WORD  :1;
    IO_WORD _DBW0 :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD _WREN :1;
    IO_WORD  :1;
    IO_WORD _TYP3 :1;
    IO_WORD _TYP2 :1;
    IO_WORD _TYP1 :1;
    IO_WORD _TYP0 :1;
  }bit;
  struct{
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD _ASZ :2;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD _TYP :4;
  }bitc;
 }ACR3STR;
typedef union{  
    IO_WORD	word;
    struct{   
    IO_WORD  :1;
    IO_WORD _W14 :1;
    IO_WORD _W13 :1;
    IO_WORD _W12 :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD _W06 :1;
    IO_WORD  :1;
    IO_WORD _W04 :1;
    IO_WORD  :1;
    IO_WORD _W02 :1;
    IO_WORD _W01 :1;
    IO_WORD _W00 :1;
  }bit;
 }AWR0STR;
typedef union{  
    IO_WORD	word;
    struct{   
    IO_WORD  :1;
    IO_WORD _W14 :1;
    IO_WORD _W13 :1;
    IO_WORD _W12 :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD _W06 :1;
    IO_WORD  :1;
    IO_WORD _W04 :1;
    IO_WORD  :1;
    IO_WORD _W02 :1;
    IO_WORD _W01 :1;
    IO_WORD _W00 :1;
  }bit;
 }AWR1STR;
typedef union{  
    IO_WORD	word;
    struct{   
    IO_WORD  :1;
    IO_WORD _W14 :1;
    IO_WORD _W13 :1;
    IO_WORD _W12 :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD _W06 :1;
    IO_WORD  :1;
    IO_WORD _W04 :1;
    IO_WORD  :1;
    IO_WORD _W02 :1;
    IO_WORD _W01 :1;
    IO_WORD _W00 :1;
  }bit;
 }AWR2STR;
typedef union{  
    IO_WORD	word;
    struct{   
    IO_WORD  :1;
    IO_WORD _W14 :1;
    IO_WORD _W13 :1;
    IO_WORD _W12 :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD _W06 :1;
    IO_WORD  :1;
    IO_WORD _W04 :1;
    IO_WORD  :1;
    IO_WORD _W02 :1;
    IO_WORD _W01 :1;
    IO_WORD _W00 :1;
  }bit;
 }AWR3STR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _CSE3 :1;
    IO_BYTE _CSE2 :1;
    IO_BYTE _CSE1 :1;
    IO_BYTE _CSE0 :1;
  }bit;
 }CSERSTR;
typedef union{   /* Mode Register */
    IO_BYTE	byte;
    struct{   
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _ROMA :1;
    IO_BYTE _WTH1 :1;
    IO_BYTE _WTH0 :1;
  }bit;
  struct{
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE _WTH :2;
  }bitc;
 }MODRSTR;
typedef union{   /* Flash I/F */
    IO_BYTE	byte;
    struct{   
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _RDY :1;
    IO_BYTE  :1;
    IO_BYTE _WE :1;
    IO_BYTE  :1;
  }bit;
 }FLCRSTR;
typedef union{  
    IO_BYTE	byte;
    struct{   
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _FAC1 :1;
    IO_BYTE _FAC0 :1;
    IO_BYTE  :1;
    IO_BYTE _WTC2 :1;
    IO_BYTE _WTC1 :1;
    IO_BYTE _WTC0 :1;
  }bit;
  struct{
    IO_BYTE :1;
    IO_BYTE :1;
    IO_BYTE _FAC :2;
    IO_BYTE :1;
    IO_BYTE _WTC :3;
  }bitc;
 }FLWCSTR;
typedef union{   /* CAN 0 Control Register */
    IO_WORD	word;
    struct{   
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD _Test :1;
    IO_WORD _CCE :1;
    IO_WORD _DAR :1;
    IO_WORD  :1;
    IO_WORD _EIE :1;
    IO_WORD _SIE :1;
    IO_WORD _IE :1;
    IO_WORD _Init :1;
  }bit;
 }CTRLR0STR;
typedef union{  
    IO_WORD	word;
    struct{   
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD _BOff :1;
    IO_WORD _EWarn :1;
    IO_WORD _EPass :1;
    IO_WORD _RxOK :1;
    IO_WORD _TxOK :1;
    IO_WORD _LEC2 :1;
    IO_WORD _LEC1 :1;
    IO_WORD _LEC0 :1;
  }bit;
  struct{
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD _LEC :3;
  }bitc;
 }STATR0STR;
typedef union{  
    IO_WORD	word;
    struct{   
    IO_WORD _RP :1;
    IO_WORD _REC6 :1;
    IO_WORD _REC5 :1;
    IO_WORD _REC4 :1;
    IO_WORD _REC3 :1;
    IO_WORD _REC2 :1;
    IO_WORD _REC1 :1;
    IO_WORD _REC0 :1;
    IO_WORD _TEC7 :1;
    IO_WORD _TEC6 :1;
    IO_WORD _TEC5 :1;
    IO_WORD _TEC4 :1;
    IO_WORD _TEC3 :1;
    IO_WORD _TEC2 :1;
    IO_WORD _TEC1 :1;
    IO_WORD _TEC0 :1;
  }bit;
  struct{
    IO_WORD :1;
    IO_WORD _REC :7;
    IO_WORD _TEC :8;
  }bitc;
 }ERRCNT0STR;
typedef union{  
    IO_WORD	word;
    struct{   
    IO_WORD  :1;
    IO_WORD _Tseg22 :1;
    IO_WORD _Tseg21 :1;
    IO_WORD _Tseg20 :1;
    IO_WORD _Tseg13 :1;
    IO_WORD _Tseg12 :1;
    IO_WORD _Tseg11 :1;
    IO_WORD _Tseg10 :1;
    IO_WORD _SJW1 :1;
    IO_WORD _SJW0 :1;
    IO_WORD _BRP5 :1;
    IO_WORD _BRP4 :1;
    IO_WORD _BRP3 :1;
    IO_WORD _BRP2 :1;
    IO_WORD _BRP1 :1;
    IO_WORD _BRP0 :1;
  }bit;
  struct{
    IO_WORD :1;
    IO_WORD _Tseg2 :3;
    IO_WORD _Tseg1 :4;
    IO_WORD _SJW :2;
    IO_WORD _BRP :6;
  }bitc;
 }BTR0STR;
typedef union{  
    IO_WORD	word;
    struct{   
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD _Rx :1;
    IO_WORD _Tx1 :1;
    IO_WORD _Tx0 :1;
    IO_WORD _LBack :1;
    IO_WORD _Silent :1;
    IO_WORD _Basic :1;
    IO_WORD  :1;
    IO_WORD  :1;
  }bit;
  struct{
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD _Tx :2;
  }bitc;
 }TESTR0STR;
typedef union{  
    IO_WORD	word;
    struct{   
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
  }bit;
 }BRPER0STR;
typedef union{   /* CAN 0 IF 1 */
    IO_WORD	word;
    struct{   
    IO_WORD _Busy :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD _MN5 :1;
    IO_WORD _MN4 :1;
    IO_WORD _MN3 :1;
    IO_WORD _MN2 :1;
    IO_WORD _MN1 :1;
    IO_WORD _MN0 :1;
  }bit;
  struct{
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD _MN :6;
  }bitc;
 }IF1CREQ0STR;
typedef union{  
    IO_WORD	word;
    struct{   
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD _WR :1;
    IO_WORD _Mask :1;
    IO_WORD _Arb :1;
    IO_WORD _Control :1;
    IO_WORD _CIP :1;
    IO_WORD _TxReq :1;
    IO_WORD _DataA :1;
    IO_WORD _DataB :1;
  }bit;
 }IF1CMSK0STR;
typedef union{  
    IO_WORD	word;
    struct{   
    IO_WORD _MXtd :1;
    IO_WORD _MDir :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
  }bit;
 }IF1MSK20STR;
typedef union{  
    IO_WORD	word;
    struct{   
    IO_WORD _MsgVal :1;
    IO_WORD _Xtd :1;
    IO_WORD _DIR :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
  }bit;
 }IF1ARB20STR;
typedef union{  
    IO_WORD	word;
    struct{   
    IO_WORD _NewDat :1;
    IO_WORD _MsgLst :1;
    IO_WORD _IntPnd :1;
    IO_WORD _UMask :1;
    IO_WORD _TxIE :1;
    IO_WORD _RxIE :1;
    IO_WORD _RmtEn :1;
    IO_WORD _TxRqst :1;
    IO_WORD _EoB :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD _DLC3 :1;
    IO_WORD _DLC2 :1;
    IO_WORD _DLC1 :1;
    IO_WORD _DLC0 :1;
  }bit;
  struct{
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD _DLC :4;
  }bitc;
 }IF1MCTR0STR;
typedef union{   /* CAN 0 IF 2 */
    IO_WORD	word;
    struct{   
    IO_WORD _Busy :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD _MN5 :1;
    IO_WORD _MN4 :1;
    IO_WORD _MN3 :1;
    IO_WORD _MN2 :1;
    IO_WORD _MN1 :1;
    IO_WORD _MN0 :1;
  }bit;
  struct{
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD _MN :6;
  }bitc;
 }IF2CREQ0STR;
typedef union{  
    IO_WORD	word;
    struct{   
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD _WR :1;
    IO_WORD _Mask :1;
    IO_WORD _Arb :1;
    IO_WORD _Control :1;
    IO_WORD _CIP :1;
    IO_WORD _TxReq :1;
    IO_WORD _DataA :1;
    IO_WORD _DataB :1;
  }bit;
 }IF2CMSK0STR;
typedef union{  
    IO_WORD	word;
    struct{   
    IO_WORD _MXtd :1;
    IO_WORD _MDir :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
  }bit;
 }IF2MSK20STR;
typedef union{  
    IO_WORD	word;
    struct{   
    IO_WORD _MsgVal :1;
    IO_WORD _Xtd :1;
    IO_WORD _DIR :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
  }bit;
 }IF2ARB20STR;
typedef union{  
    IO_WORD	word;
    struct{   
    IO_WORD _NewDat :1;
    IO_WORD _MsgLst :1;
    IO_WORD _IntPnd :1;
    IO_WORD _UMask :1;
    IO_WORD _TxIE :1;
    IO_WORD _RxIE :1;
    IO_WORD _RmtEn :1;
    IO_WORD _TxRqst :1;
    IO_WORD _EoB :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD _DLC3 :1;
    IO_WORD _DLC2 :1;
    IO_WORD _DLC1 :1;
    IO_WORD _DLC0 :1;
  }bit;
  struct{
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD _DLC :4;
  }bitc;
 }IF2MCTR0STR;
typedef union{   /* CAN 1 Control Register */
    IO_WORD	word;
    struct{   
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD _Test :1;
    IO_WORD _CCE :1;
    IO_WORD _DAR :1;
    IO_WORD  :1;
    IO_WORD _EIE :1;
    IO_WORD _SIE :1;
    IO_WORD _IE :1;
    IO_WORD _Init :1;
  }bit;
 }CTRLR1STR;
typedef union{  
    IO_WORD	word;
    struct{   
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD _BOff :1;
    IO_WORD _EWarn :1;
    IO_WORD _EPass :1;
    IO_WORD _RxOK :1;
    IO_WORD _TxOK :1;
    IO_WORD _LEC2 :1;
    IO_WORD _LEC1 :1;
    IO_WORD _LEC0 :1;
  }bit;
  struct{
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD _LEC :3;
  }bitc;
 }STATR1STR;
typedef union{  
    IO_WORD	word;
    struct{   
    IO_WORD _RP :1;
    IO_WORD _REC6 :1;
    IO_WORD _REC5 :1;
    IO_WORD _REC4 :1;
    IO_WORD _REC3 :1;
    IO_WORD _REC2 :1;
    IO_WORD _REC1 :1;
    IO_WORD _REC0 :1;
    IO_WORD _TEC7 :1;
    IO_WORD _TEC6 :1;
    IO_WORD _TEC5 :1;
    IO_WORD _TEC4 :1;
    IO_WORD _TEC3 :1;
    IO_WORD _TEC2 :1;
    IO_WORD _TEC1 :1;
    IO_WORD _TEC0 :1;
  }bit;
  struct{
    IO_WORD :1;
    IO_WORD _REC :7;
    IO_WORD _TEC :8;
  }bitc;
 }ERRCNT1STR;
typedef union{  
    IO_WORD	word;
    struct{   
    IO_WORD  :1;
    IO_WORD _Tseg22 :1;
    IO_WORD _Tseg21 :1;
    IO_WORD _Tseg20 :1;
    IO_WORD _Tseg13 :1;
    IO_WORD _Tseg12 :1;
    IO_WORD _Tseg11 :1;
    IO_WORD _Tseg10 :1;
    IO_WORD _SJW1 :1;
    IO_WORD _SJW0 :1;
    IO_WORD _BRP5 :1;
    IO_WORD _BRP4 :1;
    IO_WORD _BRP3 :1;
    IO_WORD _BRP2 :1;
    IO_WORD _BRP1 :1;
    IO_WORD _BRP0 :1;
  }bit;
  struct{
    IO_WORD :1;
    IO_WORD _Tseg2 :3;
    IO_WORD _Tseg1 :4;
    IO_WORD _SJW :2;
    IO_WORD _BRP :6;
  }bitc;
 }BTR1STR;
typedef union{  
    IO_WORD	word;
    struct{   
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD _Rx :1;
    IO_WORD _Tx1 :1;
    IO_WORD _Tx0 :1;
    IO_WORD _LBack :1;
    IO_WORD _Silent :1;
    IO_WORD _Basic :1;
    IO_WORD  :1;
    IO_WORD  :1;
  }bit;
  struct{
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD _Tx :2;
  }bitc;
 }TESTR1STR;
typedef union{  
    IO_WORD	word;
    struct{   
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
  }bit;
 }BRPER1STR;
typedef union{   /* CAN 1 IF 1 */
    IO_WORD	word;
    struct{   
    IO_WORD _Busy :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD _MN5 :1;
    IO_WORD _MN4 :1;
    IO_WORD _MN3 :1;
    IO_WORD _MN2 :1;
    IO_WORD _MN1 :1;
    IO_WORD _MN0 :1;
  }bit;
  struct{
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD _MN :6;
  }bitc;
 }IF1CREQ1STR;
typedef union{  
    IO_WORD	word;
    struct{   
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD _WR :1;
    IO_WORD _Mask :1;
    IO_WORD _Arb :1;
    IO_WORD _Control :1;
    IO_WORD _CIP :1;
    IO_WORD _TxReq :1;
    IO_WORD _DataA :1;
    IO_WORD _DataB :1;
  }bit;
 }IF1CMSK1STR;
typedef union{  
    IO_WORD	word;
    struct{   
    IO_WORD _MXtd :1;
    IO_WORD _MDir :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
  }bit;
 }IF1MSK21STR;
typedef union{  
    IO_WORD	word;
    struct{   
    IO_WORD _MsgVal :1;
    IO_WORD _Xtd :1;
    IO_WORD _DIR :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
  }bit;
 }IF1ARB21STR;
typedef union{  
    IO_WORD	word;
    struct{   
    IO_WORD _NewDat :1;
    IO_WORD _MsgLst :1;
    IO_WORD _IntPnd :1;
    IO_WORD _UMask :1;
    IO_WORD _TxIE :1;
    IO_WORD _RxIE :1;
    IO_WORD _RmtEn :1;
    IO_WORD _TxRqst :1;
    IO_WORD _EoB :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD _DLC3 :1;
    IO_WORD _DLC2 :1;
    IO_WORD _DLC1 :1;
    IO_WORD _DLC0 :1;
  }bit;
  struct{
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD _DLC :4;
  }bitc;
 }IF1MCTR1STR;
typedef union{   /* CAN 1 IF 2 */
    IO_WORD	word;
    struct{   
    IO_WORD _Busy :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD _MN5 :1;
    IO_WORD _MN4 :1;
    IO_WORD _MN3 :1;
    IO_WORD _MN2 :1;
    IO_WORD _MN1 :1;
    IO_WORD _MN0 :1;
  }bit;
  struct{
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD _MN :6;
  }bitc;
 }IF2CREQ1STR;
typedef union{  
    IO_WORD	word;
    struct{   
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD _WR :1;
    IO_WORD _Mask :1;
    IO_WORD _Arb :1;
    IO_WORD _Control :1;
    IO_WORD _CIP :1;
    IO_WORD _TxReq :1;
    IO_WORD _DataA :1;
    IO_WORD _DataB :1;
  }bit;
 }IF2CMSK1STR;
typedef union{  
    IO_WORD	word;
    struct{   
    IO_WORD _MXtd :1;
    IO_WORD _MDir :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
  }bit;
 }IF2MSK21STR;
typedef union{  
    IO_WORD	word;
    struct{   
    IO_WORD _MsgVal :1;
    IO_WORD _Xtd :1;
    IO_WORD _DIR :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
  }bit;
 }IF2ARB21STR;
typedef union{  
    IO_WORD	word;
    struct{   
    IO_WORD _NewDat :1;
    IO_WORD _MsgLst :1;
    IO_WORD _IntPnd :1;
    IO_WORD _UMask :1;
    IO_WORD _TxIE :1;
    IO_WORD _RxIE :1;
    IO_WORD _RmtEn :1;
    IO_WORD _TxRqst :1;
    IO_WORD _EoB :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD _DLC3 :1;
    IO_WORD _DLC2 :1;
    IO_WORD _DLC1 :1;
    IO_WORD _DLC0 :1;
  }bit;
  struct{
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD _DLC :4;
  }bitc;
 }IF2MCTR1STR;
typedef union{   /* CAN 2 Control Register */
    IO_WORD	word;
    struct{   
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD _Test :1;
    IO_WORD _CCE :1;
    IO_WORD _DAR :1;
    IO_WORD  :1;
    IO_WORD _EIE :1;
    IO_WORD _SIE :1;
    IO_WORD _IE :1;
    IO_WORD _Init :1;
  }bit;
 }CTRLR2STR;
typedef union{  
    IO_WORD	word;
    struct{   
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD _BOff :1;
    IO_WORD _EWarn :1;
    IO_WORD _EPass :1;
    IO_WORD _RxOK :1;
    IO_WORD _TxOK :1;
    IO_WORD _LEC2 :1;
    IO_WORD _LEC1 :1;
    IO_WORD _LEC0 :1;
  }bit;
  struct{
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD _LEC :3;
  }bitc;
 }STATR2STR;
typedef union{  
    IO_WORD	word;
    struct{   
    IO_WORD _RP :1;
    IO_WORD _REC6 :1;
    IO_WORD _REC5 :1;
    IO_WORD _REC4 :1;
    IO_WORD _REC3 :1;
    IO_WORD _REC2 :1;
    IO_WORD _REC1 :1;
    IO_WORD _REC0 :1;
    IO_WORD _TEC7 :1;
    IO_WORD _TEC6 :1;
    IO_WORD _TEC5 :1;
    IO_WORD _TEC4 :1;
    IO_WORD _TEC3 :1;
    IO_WORD _TEC2 :1;
    IO_WORD _TEC1 :1;
    IO_WORD _TEC0 :1;
  }bit;
  struct{
    IO_WORD :1;
    IO_WORD _REC :7;
    IO_WORD _TEC :8;
  }bitc;
 }ERRCNT2STR;
typedef union{  
    IO_WORD	word;
    struct{   
    IO_WORD  :1;
    IO_WORD _Tseg22 :1;
    IO_WORD _Tseg21 :1;
    IO_WORD _Tseg20 :1;
    IO_WORD _Tseg13 :1;
    IO_WORD _Tseg12 :1;
    IO_WORD _Tseg11 :1;
    IO_WORD _Tseg10 :1;
    IO_WORD _SJW1 :1;
    IO_WORD _SJW0 :1;
    IO_WORD _BRP5 :1;
    IO_WORD _BRP4 :1;
    IO_WORD _BRP3 :1;
    IO_WORD _BRP2 :1;
    IO_WORD _BRP1 :1;
    IO_WORD _BRP0 :1;
  }bit;
  struct{
    IO_WORD :1;
    IO_WORD _Tseg2 :3;
    IO_WORD _Tseg1 :4;
    IO_WORD _SJW :2;
    IO_WORD _BRP :6;
  }bitc;
 }BTR2STR;
typedef union{  
    IO_WORD	word;
    struct{   
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD _Rx :1;
    IO_WORD _Tx1 :1;
    IO_WORD _Tx0 :1;
    IO_WORD _LBack :1;
    IO_WORD _Silent :1;
    IO_WORD _Basic :1;
    IO_WORD  :1;
    IO_WORD  :1;
  }bit;
  struct{
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD _Tx :2;
  }bitc;
 }TESTR2STR;
typedef union{  
    IO_WORD	word;
    struct{   
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
  }bit;
 }BRPER2STR;
typedef union{   /* CAN 2 IF 1 */
    IO_WORD	word;
    struct{   
    IO_WORD _Busy :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD _MN5 :1;
    IO_WORD _MN4 :1;
    IO_WORD _MN3 :1;
    IO_WORD _MN2 :1;
    IO_WORD _MN1 :1;
    IO_WORD _MN0 :1;
  }bit;
  struct{
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD _MN :6;
  }bitc;
 }IF1CREQ2STR;
typedef union{  
    IO_WORD	word;
    struct{   
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD _WR :1;
    IO_WORD _Mask :1;
    IO_WORD _Arb :1;
    IO_WORD _Control :1;
    IO_WORD _CIP :1;
    IO_WORD _TxReq :1;
    IO_WORD _DataA :1;
    IO_WORD _DataB :1;
  }bit;
 }IF1CMSK2STR;
typedef union{  
    IO_WORD	word;
    struct{   
    IO_WORD _MXtd :1;
    IO_WORD _MDir :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
  }bit;
 }IF1MSK22STR;
typedef union{  
    IO_WORD	word;
    struct{   
    IO_WORD _MsgVal :1;
    IO_WORD _Xtd :1;
    IO_WORD _DIR :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
  }bit;
 }IF1ARB22STR;
typedef union{  
    IO_WORD	word;
    struct{   
    IO_WORD _NewDat :1;
    IO_WORD _MsgLst :1;
    IO_WORD _IntPnd :1;
    IO_WORD _UMask :1;
    IO_WORD _TxIE :1;
    IO_WORD _RxIE :1;
    IO_WORD _RmtEn :1;
    IO_WORD _TxRqst :1;
    IO_WORD _EoB :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD _DLC3 :1;
    IO_WORD _DLC2 :1;
    IO_WORD _DLC1 :1;
    IO_WORD _DLC0 :1;
  }bit;
  struct{
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD _DLC :4;
  }bitc;
 }IF1MCTR2STR;
typedef union{   /* CAN 2 IF 2 */
    IO_WORD	word;
    struct{   
    IO_WORD _Busy :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD _MN5 :1;
    IO_WORD _MN4 :1;
    IO_WORD _MN3 :1;
    IO_WORD _MN2 :1;
    IO_WORD _MN1 :1;
    IO_WORD _MN0 :1;
  }bit;
  struct{
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD _MN :6;
  }bitc;
 }IF2CREQ2STR;
typedef union{  
    IO_WORD	word;
    struct{   
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD _WR :1;
    IO_WORD _Mask :1;
    IO_WORD _Arb :1;
    IO_WORD _Control :1;
    IO_WORD _CIP :1;
    IO_WORD _TxReq :1;
    IO_WORD _DataA :1;
    IO_WORD _DataB :1;
  }bit;
 }IF2CMSK2STR;
typedef union{  
    IO_WORD	word;
    struct{   
    IO_WORD _MXtd :1;
    IO_WORD _MDir :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
  }bit;
 }IF2MSK22STR;
typedef union{  
    IO_WORD	word;
    struct{   
    IO_WORD _MsgVal :1;
    IO_WORD _Xtd :1;
    IO_WORD _DIR :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
  }bit;
 }IF2ARB22STR;
typedef union{  
    IO_WORD	word;
    struct{   
    IO_WORD _NewDat :1;
    IO_WORD _MsgLst :1;
    IO_WORD _IntPnd :1;
    IO_WORD _UMask :1;
    IO_WORD _TxIE :1;
    IO_WORD _RxIE :1;
    IO_WORD _RmtEn :1;
    IO_WORD _TxRqst :1;
    IO_WORD _EoB :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD  :1;
    IO_WORD _DLC3 :1;
    IO_WORD _DLC2 :1;
    IO_WORD _DLC1 :1;
    IO_WORD _DLC0 :1;
  }bit;
  struct{
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD :1;
    IO_WORD _DLC :4;
  }bitc;
 }IF2MCTR2STR;

/* C-DECLARATIONS */

__IO_EXTERN __io PDR0STR pdr0;   /* Port Data Register */
#define PDR0 pdr0.byte
#define PDR0_P07 pdr0.bit._P07
#define PDR0_P06 pdr0.bit._P06
#define PDR0_P05 pdr0.bit._P05
#define PDR0_P04 pdr0.bit._P04
#define PDR0_P03 pdr0.bit._P03
#define PDR0_P02 pdr0.bit._P02
#define PDR0_P01 pdr0.bit._P01
#define PDR0_P00 pdr0.bit._P00
__IO_EXTERN __io PDR1STR pdr1;  
#define PDR1 pdr1.byte
#define PDR1_P17 pdr1.bit._P17
#define PDR1_P16 pdr1.bit._P16
#define PDR1_P15 pdr1.bit._P15
#define PDR1_P14 pdr1.bit._P14
#define PDR1_P13 pdr1.bit._P13
#define PDR1_P12 pdr1.bit._P12
#define PDR1_P11 pdr1.bit._P11
#define PDR1_P10 pdr1.bit._P10
__IO_EXTERN __io PDR2STR pdr2;  
#define PDR2 pdr2.byte
#define PDR2_P27 pdr2.bit._P27
#define PDR2_P26 pdr2.bit._P26
#define PDR2_P25 pdr2.bit._P25
#define PDR2_P24 pdr2.bit._P24
#define PDR2_P23 pdr2.bit._P23
#define PDR2_P22 pdr2.bit._P22
#define PDR2_P21 pdr2.bit._P21
#define PDR2_P20 pdr2.bit._P20
__IO_EXTERN __io PDR3STR pdr3;  
#define PDR3 pdr3.byte
#define PDR3_P37 pdr3.bit._P37
#define PDR3_P36 pdr3.bit._P36
#define PDR3_P35 pdr3.bit._P35
#define PDR3_P34 pdr3.bit._P34
#define PDR3_P33 pdr3.bit._P33
#define PDR3_P32 pdr3.bit._P32
#define PDR3_P31 pdr3.bit._P31
#define PDR3_P30 pdr3.bit._P30
__IO_EXTERN __io PDR4STR pdr4;  
#define PDR4 pdr4.byte
#define PDR4_P47 pdr4.bit._P47
#define PDR4_P46 pdr4.bit._P46
#define PDR4_P45 pdr4.bit._P45
#define PDR4_P44 pdr4.bit._P44
#define PDR4_P43 pdr4.bit._P43
#define PDR4_P42 pdr4.bit._P42
#define PDR4_P41 pdr4.bit._P41
#define PDR4_P40 pdr4.bit._P40
__IO_EXTERN __io PDR5STR pdr5;  
#define PDR5 pdr5.byte
#define PDR5_P57 pdr5.bit._P57
#define PDR5_P56 pdr5.bit._P56
#define PDR5_P55 pdr5.bit._P55
#define PDR5_P54 pdr5.bit._P54
#define PDR5_P53 pdr5.bit._P53
#define PDR5_P52 pdr5.bit._P52
#define PDR5_P51 pdr5.bit._P51
#define PDR5_P50 pdr5.bit._P50
__IO_EXTERN __io PDR6STR pdr6;  
#define PDR6 pdr6.byte
#define PDR6_P67 pdr6.bit._P67
#define PDR6_P66 pdr6.bit._P66
#define PDR6_P65 pdr6.bit._P65
#define PDR6_P64 pdr6.bit._P64
#define PDR6_P63 pdr6.bit._P63
#define PDR6_P62 pdr6.bit._P62
#define PDR6_P61 pdr6.bit._P61
#define PDR6_P60 pdr6.bit._P60
__IO_EXTERN __io PDR7STR pdr7;  
#define PDR7 pdr7.byte
#define PDR7_P77 pdr7.bit._P77
#define PDR7_P76 pdr7.bit._P76
#define PDR7_P75 pdr7.bit._P75
#define PDR7_P74 pdr7.bit._P74
#define PDR7_P73 pdr7.bit._P73
#define PDR7_P72 pdr7.bit._P72
#define PDR7_P71 pdr7.bit._P71
#define PDR7_P70 pdr7.bit._P70
__IO_EXTERN __io PDR8STR pdr8;  
#define PDR8 pdr8.byte
#define PDR8_P87 pdr8.bit._P87
#define PDR8_P86 pdr8.bit._P86
#define PDR8_P85 pdr8.bit._P85
#define PDR8_P84 pdr8.bit._P84
#define PDR8_P83 pdr8.bit._P83
#define PDR8_P82 pdr8.bit._P82
#define PDR8_P81 pdr8.bit._P81
#define PDR8_P80 pdr8.bit._P80
__IO_EXTERN __io PDR9STR pdr9;  
#define PDR9 pdr9.byte
#define PDR9_P97 pdr9.bit._P97
#define PDR9_P96 pdr9.bit._P96
#define PDR9_P95 pdr9.bit._P95
#define PDR9_P94 pdr9.bit._P94
#define PDR9_P93 pdr9.bit._P93
#define PDR9_P92 pdr9.bit._P92
#define PDR9_P91 pdr9.bit._P91
#define PDR9_P90 pdr9.bit._P90
__IO_EXTERN __io PDRASTR pdra;  
#define PDRA pdra.byte
#define PDRA_PA1 pdra.bit._PA1
#define PDRA_PA0 pdra.bit._PA0
__IO_EXTERN __io PDRBSTR pdrb;  
#define PDRB pdrb.byte
#define PDRB_PB5 pdrb.bit._PB5
#define PDRB_PB4 pdrb.bit._PB4
#define PDRB_PB3 pdrb.bit._PB3
#define PDRB_PB2 pdrb.bit._PB2
#define PDRB_PB1 pdrb.bit._PB1
#define PDRB_PB0 pdrb.bit._PB0
__IO_EXTERN __io PDRCSTR pdrc;  
#define PDRC pdrc.byte
#define PDRC_PC7 pdrc.bit._PC7
#define PDRC_PC6 pdrc.bit._PC6
#define PDRC_PC5 pdrc.bit._PC5
#define PDRC_PC4 pdrc.bit._PC4
#define PDRC_PC3 pdrc.bit._PC3
#define PDRC_PC2 pdrc.bit._PC2
#define PDRC_PC1 pdrc.bit._PC1
#define PDRC_PC0 pdrc.bit._PC0
__IO_EXTERN __io PDRDSTR pdrd;  
#define PDRD pdrd.byte
#define PDRD_PD7 pdrd.bit._PD7
#define PDRD_PD6 pdrd.bit._PD6
#define PDRD_PD5 pdrd.bit._PD5
#define PDRD_PD4 pdrd.bit._PD4
#define PDRD_PD3 pdrd.bit._PD3
#define PDRD_PD2 pdrd.bit._PD2
#define PDRD_PD1 pdrd.bit._PD1
#define PDRD_PD0 pdrd.bit._PD0
__IO_EXTERN __io PDRESTR pdre;  
#define PDRE pdre.byte
#define PDRE_PE7 pdre.bit._PE7
#define PDRE_PE6 pdre.bit._PE6
#define PDRE_PE5 pdre.bit._PE5
#define PDRE_PE4 pdre.bit._PE4
#define PDRE_PE3 pdre.bit._PE3
#define PDRE_PE2 pdre.bit._PE2
#define PDRE_PE1 pdre.bit._PE1
#define PDRE_PE0 pdre.bit._PE0
__IO_EXTERN __io PDRFSTR pdrf;  
#define PDRF pdrf.byte
#define PDRF_PF7 pdrf.bit._PF7
#define PDRF_PF6 pdrf.bit._PF6
#define PDRF_PF5 pdrf.bit._PF5
#define PDRF_PF4 pdrf.bit._PF4
#define PDRF_PF3 pdrf.bit._PF3
#define PDRF_PF2 pdrf.bit._PF2
#define PDRF_PF1 pdrf.bit._PF1
#define PDRF_PF0 pdrf.bit._PF0
__IO_EXTERN __io PDRGSTR pdrg;  
#define PDRG pdrg.byte
#define PDRG_PG7 pdrg.bit._PG7
#define PDRG_PG6 pdrg.bit._PG6
#define PDRG_PG5 pdrg.bit._PG5
#define PDRG_PG4 pdrg.bit._PG4
#define PDRG_PG3 pdrg.bit._PG3
#define PDRG_PG2 pdrg.bit._PG2
#define PDRG_PG1 pdrg.bit._PG1
#define PDRG_PG0 pdrg.bit._PG0
__IO_EXTERN __io EIRR0STR eirr0;   /* External Interrupt 0-7 */
#define EIRR0 eirr0.byte
#define EIRR0_ER7 eirr0.bit._ER7
#define EIRR0_ER6 eirr0.bit._ER6
#define EIRR0_ER5 eirr0.bit._ER5
#define EIRR0_ER4 eirr0.bit._ER4
#define EIRR0_ER3 eirr0.bit._ER3
#define EIRR0_ER2 eirr0.bit._ER2
#define EIRR0_ER1 eirr0.bit._ER1
#define EIRR0_ER0 eirr0.bit._ER0
__IO_EXTERN __io ENIR0STR enir0;  
#define ENIR0 enir0.byte
#define ENIR0_EN7 enir0.bit._EN7
#define ENIR0_EN6 enir0.bit._EN6
#define ENIR0_EN5 enir0.bit._EN5
#define ENIR0_EN4 enir0.bit._EN4
#define ENIR0_EN3 enir0.bit._EN3
#define ENIR0_EN2 enir0.bit._EN2
#define ENIR0_EN1 enir0.bit._EN1
#define ENIR0_EN0 enir0.bit._EN0
__IO_EXTERN __io ELVR0STR elvr0;  
#define ELVR0 elvr0.word
#define ELVR0_LB7 elvr0.bit._LB7
#define ELVR0_LA7 elvr0.bit._LA7
#define ELVR0_LB6 elvr0.bit._LB6
#define ELVR0_LA6 elvr0.bit._LA6
#define ELVR0_LB5 elvr0.bit._LB5
#define ELVR0_LA5 elvr0.bit._LA5
#define ELVR0_LB4 elvr0.bit._LB4
#define ELVR0_LA4 elvr0.bit._LA4
#define ELVR0_LB3 elvr0.bit._LB3
#define ELVR0_LA3 elvr0.bit._LA3
#define ELVR0_LB2 elvr0.bit._LB2
#define ELVR0_LA2 elvr0.bit._LA2
#define ELVR0_LB1 elvr0.bit._LB1
#define ELVR0_LA1 elvr0.bit._LA1
#define ELVR0_LB0 elvr0.bit._LB0
#define ELVR0_LA0 elvr0.bit._LA0
__IO_EXTERN __io DICRSTR dicr;   /* DLYI/I-unit */
#define DICR dicr.byte
#define DICR_DLY1 dicr.bit._DLY1
__IO_EXTERN __io HRCLSTR hrcl;  
#define HRCL hrcl.byte
#define HRCL_MHALTI hrcl.bit._MHALTI
#define HRCL_LVL4 hrcl.bit._LVL4
#define HRCL_LVL3 hrcl.bit._LVL3
#define HRCL_LVL2 hrcl.bit._LVL2
#define HRCL_LVL1 hrcl.bit._LVL1
__IO_EXTERN __io TMRLR0STR tmrlr0;   /* Reload Timer 0 */
#define TMRLR0 tmrlr0.word
__IO_EXTERN __io IO_WORD tmr0;  
#define TMR0 tmr0
__IO_EXTERN __io TMCSR0STR tmcsr0;  
#define TMCSR0 tmcsr0.word
#define TMCSR0_CSL2 tmcsr0.bit._CSL2
#define TMCSR0_CSL1 tmcsr0.bit._CSL1
#define TMCSR0_CSL0 tmcsr0.bit._CSL0
#define TMCSR0_MOD2 tmcsr0.bit._MOD2
#define TMCSR0_MOD1 tmcsr0.bit._MOD1
#define TMCSR0_MOD0 tmcsr0.bit._MOD0
#define TMCSR0_OULT tmcsr0.bit._OULT
#define TMCSR0_RELD tmcsr0.bit._RELD
#define TMCSR0_INTE tmcsr0.bit._INTE
#define TMCSR0_UF tmcsr0.bit._UF
#define TMCSR0_CNTE tmcsr0.bit._CNTE
#define TMCSR0_TRG tmcsr0.bit._TRG
#define TMCSR0_CSL tmcsr0.bitc._CSL
#define TMCSR0_MOD tmcsr0.bitc._MOD
__IO_EXTERN __io IO_WORD tmrlr1;   /* Reload Timer 1 */
#define TMRLR1 tmrlr1
__IO_EXTERN __io IO_WORD tmr1;  
#define TMR1 tmr1
__IO_EXTERN __io TMCSR1STR tmcsr1;  
#define TMCSR1 tmcsr1.word
#define TMCSR1_CSL2 tmcsr1.bit._CSL2
#define TMCSR1_CSL1 tmcsr1.bit._CSL1
#define TMCSR1_CSL0 tmcsr1.bit._CSL0
#define TMCSR1_MOD2 tmcsr1.bit._MOD2
#define TMCSR1_MOD1 tmcsr1.bit._MOD1
#define TMCSR1_MOD0 tmcsr1.bit._MOD0
#define TMCSR1_OULT tmcsr1.bit._OULT
#define TMCSR1_RELD tmcsr1.bit._RELD
#define TMCSR1_INTE tmcsr1.bit._INTE
#define TMCSR1_UF tmcsr1.bit._UF
#define TMCSR1_CNTE tmcsr1.bit._CNTE
#define TMCSR1_TRG tmcsr1.bit._TRG
#define TMCSR1_CSL tmcsr1.bitc._CSL
#define TMCSR1_MOD tmcsr1.bitc._MOD
__IO_EXTERN __io IO_WORD tmrlr2;   /* Reload Timer 2 */
#define TMRLR2 tmrlr2
__IO_EXTERN __io IO_WORD tmr2;  
#define TMR2 tmr2
__IO_EXTERN __io TMCSR2STR tmcsr2;  
#define TMCSR2 tmcsr2.word
#define TMCSR2_CSL2 tmcsr2.bit._CSL2
#define TMCSR2_CSL1 tmcsr2.bit._CSL1
#define TMCSR2_CSL0 tmcsr2.bit._CSL0
#define TMCSR2_MOD2 tmcsr2.bit._MOD2
#define TMCSR2_MOD1 tmcsr2.bit._MOD1
#define TMCSR2_MOD0 tmcsr2.bit._MOD0
#define TMCSR2_OULT tmcsr2.bit._OULT
#define TMCSR2_RELD tmcsr2.bit._RELD
#define TMCSR2_INTE tmcsr2.bit._INTE
#define TMCSR2_UF tmcsr2.bit._UF
#define TMCSR2_CNTE tmcsr2.bit._CNTE
#define TMCSR2_TRG tmcsr2.bit._TRG
#define TMCSR2_CSL tmcsr2.bitc._CSL
#define TMCSR2_MOD tmcsr2.bitc._MOD
__IO_EXTERN __io SCR0STR scr0;   /* LIN-UART 0 */
#define SCR0 scr0.byte
#define SCR0_PEN scr0.bit._PEN
#define SCR0_P scr0.bit._P
#define SCR0_SBL scr0.bit._SBL
#define SCR0_CL scr0.bit._CL
#define SCR0_AD scr0.bit._AD
#define SCR0_CRE scr0.bit._CRE
#define SCR0_RXE scr0.bit._RXE
#define SCR0_TXE scr0.bit._TXE
__IO_EXTERN __io SMR0STR smr0;  
#define SMR0 smr0.byte
#define SMR0_MD1 smr0.bit._MD1
#define SMR0_MD0 smr0.bit._MD0
#define SMR0_OTO smr0.bit._OTO
#define SMR0_EXT smr0.bit._EXT
#define SMR0_REST smr0.bit._REST
#define SMR0_UPCL smr0.bit._UPCL
#define SMR0_SCKE smr0.bit._SCKE
#define SMR0_SOE smr0.bit._SOE
#define SMR0_MD smr0.bitc._MD
__IO_EXTERN __io SSR0STR ssr0;  
#define SSR0 ssr0.byte
#define SSR0_PE ssr0.bit._PE
#define SSR0_ORE ssr0.bit._ORE
#define SSR0_FRE ssr0.bit._FRE
#define SSR0_RDRF ssr0.bit._RDRF
#define SSR0_TDRE ssr0.bit._TDRE
#define SSR0_BDS ssr0.bit._BDS
#define SSR0_RIE ssr0.bit._RIE
#define SSR0_TIE ssr0.bit._TIE
__IO_EXTERN __io RDR0STR rdr0;  
#define RDR0 rdr0.byte
#define RDR0_D7 rdr0.bit._D7
#define RDR0_D6 rdr0.bit._D6
#define RDR0_D5 rdr0.bit._D5
#define RDR0_D4 rdr0.bit._D4
#define RDR0_D3 rdr0.bit._D3
#define RDR0_D2 rdr0.bit._D2
#define RDR0_D1 rdr0.bit._D1
#define RDR0_D0 rdr0.bit._D0
__IO_EXTERN __io TDR0STR tdr0;  
#define TDR0 tdr0.byte
#define TDR0_D7 tdr0.bit._D7
#define TDR0_D6 tdr0.bit._D6
#define TDR0_D5 tdr0.bit._D5
#define TDR0_D4 tdr0.bit._D4
#define TDR0_D3 tdr0.bit._D3
#define TDR0_D2 tdr0.bit._D2
#define TDR0_D1 tdr0.bit._D1
#define TDR0_D0 tdr0.bit._D0
__IO_EXTERN __io ESCR0STR escr0;  
#define ESCR0 escr0.byte
#define ESCR0_LBIE escr0.bit._LBIE
#define ESCR0_LBD escr0.bit._LBD
#define ESCR0_LBL1 escr0.bit._LBL1
#define ESCR0_LBL0 escr0.bit._LBL0
#define ESCR0_SOPE escr0.bit._SOPE
#define ESCR0_SIOP escr0.bit._SIOP
#define ESCR0_CCO escr0.bit._CCO
#define ESCR0_SCES escr0.bit._SCES
#define ESCR0_LBL escr0.bitc._LBL
__IO_EXTERN __io ECCR0STR eccr0;  
#define ECCR0 eccr0.byte
#define ECCR0_LBR eccr0.bit._LBR
#define ECCR0_MS eccr0.bit._MS
#define ECCR0_SCDE eccr0.bit._SCDE
#define ECCR0_SSM eccr0.bit._SSM
#define ECCR0_BIE eccr0.bit._BIE
#define ECCR0_RBI eccr0.bit._RBI
#define ECCR0_TBI eccr0.bit._TBI
__IO_EXTERN __io IO_WORD bgr0;  
#define BGR0 bgr0
__IO_EXTERN __io BGR10STR bgr10;  
#define BGR10 bgr10.byte
#define BGR10_B14 bgr10.bit._B14
#define BGR10_B13 bgr10.bit._B13
#define BGR10_B12 bgr10.bit._B12
#define BGR10_B11 bgr10.bit._B11
#define BGR10_B10 bgr10.bit._B10
#define BGR10_B09 bgr10.bit._B09
#define BGR10_B08 bgr10.bit._B08
__IO_EXTERN __io BGR00STR bgr00;  
#define BGR00 bgr00.byte
#define BGR00_B07 bgr00.bit._B07
#define BGR00_B06 bgr00.bit._B06
#define BGR00_B05 bgr00.bit._B05
#define BGR00_B04 bgr00.bit._B04
#define BGR00_B03 bgr00.bit._B03
#define BGR00_B02 bgr00.bit._B02
#define BGR00_B01 bgr00.bit._B01
#define BGR00_B00 bgr00.bit._B00
__IO_EXTERN __io SCR5STR scr5;   /* LIN-UART 5 */
#define SCR5 scr5.byte
#define SCR5_PEN scr5.bit._PEN
#define SCR5_P scr5.bit._P
#define SCR5_SBL scr5.bit._SBL
#define SCR5_CL scr5.bit._CL
#define SCR5_AD scr5.bit._AD
#define SCR5_CRE scr5.bit._CRE
#define SCR5_RXE scr5.bit._RXE
#define SCR5_TXE scr5.bit._TXE
__IO_EXTERN __io SMR5STR smr5;  
#define SMR5 smr5.byte
#define SMR5_MD1 smr5.bit._MD1
#define SMR5_MD0 smr5.bit._MD0
#define SMR5_OTO smr5.bit._OTO
#define SMR5_EXT smr5.bit._EXT
#define SMR5_REST smr5.bit._REST
#define SMR5_UPCL smr5.bit._UPCL
#define SMR5_SCKE smr5.bit._SCKE
#define SMR5_SOE smr5.bit._SOE
#define SMR5_MD smr5.bitc._MD
__IO_EXTERN __io SSR5STR ssr5;  
#define SSR5 ssr5.byte
#define SSR5_PE ssr5.bit._PE
#define SSR5_ORE ssr5.bit._ORE
#define SSR5_FRE ssr5.bit._FRE
#define SSR5_RDRF ssr5.bit._RDRF
#define SSR5_TDRE ssr5.bit._TDRE
#define SSR5_BDS ssr5.bit._BDS
#define SSR5_RIE ssr5.bit._RIE
#define SSR5_TIE ssr5.bit._TIE
__IO_EXTERN __io RDR5STR rdr5;  
#define RDR5 rdr5.byte
#define RDR5_D7 rdr5.bit._D7
#define RDR5_D6 rdr5.bit._D6
#define RDR5_D5 rdr5.bit._D5
#define RDR5_D4 rdr5.bit._D4
#define RDR5_D3 rdr5.bit._D3
#define RDR5_D2 rdr5.bit._D2
#define RDR5_D1 rdr5.bit._D1
#define RDR5_D0 rdr5.bit._D0
__IO_EXTERN __io TDR5STR tdr5;  
#define TDR5 tdr5.byte
#define TDR5_D7 tdr5.bit._D7
#define TDR5_D6 tdr5.bit._D6
#define TDR5_D5 tdr5.bit._D5
#define TDR5_D4 tdr5.bit._D4
#define TDR5_D3 tdr5.bit._D3
#define TDR5_D2 tdr5.bit._D2
#define TDR5_D1 tdr5.bit._D1
#define TDR5_D0 tdr5.bit._D0
__IO_EXTERN __io ESCR5STR escr5;  
#define ESCR5 escr5.byte
#define ESCR5_LBIE escr5.bit._LBIE
#define ESCR5_LBD escr5.bit._LBD
#define ESCR5_LBL1 escr5.bit._LBL1
#define ESCR5_LBL0 escr5.bit._LBL0
#define ESCR5_SOPE escr5.bit._SOPE
#define ESCR5_SIOP escr5.bit._SIOP
#define ESCR5_CCO escr5.bit._CCO
#define ESCR5_SCES escr5.bit._SCES
#define ESCR5_LBL escr5.bitc._LBL
__IO_EXTERN __io ECCR5STR eccr5;  
#define ECCR5 eccr5.byte
#define ECCR5_LBR eccr5.bit._LBR
#define ECCR5_MS eccr5.bit._MS
#define ECCR5_SCDE eccr5.bit._SCDE
#define ECCR5_SSM eccr5.bit._SSM
#define ECCR5_BIE eccr5.bit._BIE
#define ECCR5_RBI eccr5.bit._RBI
#define ECCR5_TBI eccr5.bit._TBI
__IO_EXTERN __io IO_WORD bgr5;  
#define BGR5 bgr5
__IO_EXTERN __io BGR15STR bgr15;  
#define BGR15 bgr15.byte
#define BGR15_B14 bgr15.bit._B14
#define BGR15_B13 bgr15.bit._B13
#define BGR15_B12 bgr15.bit._B12
#define BGR15_B11 bgr15.bit._B11
#define BGR15_B10 bgr15.bit._B10
#define BGR15_B09 bgr15.bit._B09
#define BGR15_B08 bgr15.bit._B08
__IO_EXTERN __io BGR05STR bgr05;  
#define BGR05 bgr05.byte
#define BGR05_B07 bgr05.bit._B07
#define BGR05_B06 bgr05.bit._B06
#define BGR05_B05 bgr05.bit._B05
#define BGR05_B04 bgr05.bit._B04
#define BGR05_B03 bgr05.bit._B03
#define BGR05_B02 bgr05.bit._B02
#define BGR05_B01 bgr05.bit._B01
#define BGR05_B00 bgr05.bit._B00
__IO_EXTERN __io SCR6STR scr6;   /* LIN-UART 6 */
#define SCR6 scr6.byte
#define SCR6_PEN scr6.bit._PEN
#define SCR6_P scr6.bit._P
#define SCR6_SBL scr6.bit._SBL
#define SCR6_CL scr6.bit._CL
#define SCR6_AD scr6.bit._AD
#define SCR6_CRE scr6.bit._CRE
#define SCR6_RXE scr6.bit._RXE
#define SCR6_TXE scr6.bit._TXE
__IO_EXTERN __io SMR6STR smr6;  
#define SMR6 smr6.byte
#define SMR6_MD1 smr6.bit._MD1
#define SMR6_MD0 smr6.bit._MD0
#define SMR6_OTO smr6.bit._OTO
#define SMR6_EXT smr6.bit._EXT
#define SMR6_REST smr6.bit._REST
#define SMR6_UPCL smr6.bit._UPCL
#define SMR6_SCKE smr6.bit._SCKE
#define SMR6_SOE smr6.bit._SOE
#define SMR6_MD smr6.bitc._MD
__IO_EXTERN __io SSR6STR ssr6;  
#define SSR6 ssr6.byte
#define SSR6_PE ssr6.bit._PE
#define SSR6_ORE ssr6.bit._ORE
#define SSR6_FRE ssr6.bit._FRE
#define SSR6_RDRF ssr6.bit._RDRF
#define SSR6_TDRE ssr6.bit._TDRE
#define SSR6_BDS ssr6.bit._BDS
#define SSR6_RIE ssr6.bit._RIE
#define SSR6_TIE ssr6.bit._TIE
__IO_EXTERN __io RDR6STR rdr6;  
#define RDR6 rdr6.byte
#define RDR6_D7 rdr6.bit._D7
#define RDR6_D6 rdr6.bit._D6
#define RDR6_D5 rdr6.bit._D5
#define RDR6_D4 rdr6.bit._D4
#define RDR6_D3 rdr6.bit._D3
#define RDR6_D2 rdr6.bit._D2
#define RDR6_D1 rdr6.bit._D1
#define RDR6_D0 rdr6.bit._D0
__IO_EXTERN __io TDR6STR tdr6;  
#define TDR6 tdr6.byte
#define TDR6_D7 tdr6.bit._D7
#define TDR6_D6 tdr6.bit._D6
#define TDR6_D5 tdr6.bit._D5
#define TDR6_D4 tdr6.bit._D4
#define TDR6_D3 tdr6.bit._D3
#define TDR6_D2 tdr6.bit._D2
#define TDR6_D1 tdr6.bit._D1
#define TDR6_D0 tdr6.bit._D0
__IO_EXTERN __io ESCR6STR escr6;  
#define ESCR6 escr6.byte
#define ESCR6_LBIE escr6.bit._LBIE
#define ESCR6_LBD escr6.bit._LBD
#define ESCR6_LBL1 escr6.bit._LBL1
#define ESCR6_LBL0 escr6.bit._LBL0
#define ESCR6_SOPE escr6.bit._SOPE
#define ESCR6_SIOP escr6.bit._SIOP
#define ESCR6_CCO escr6.bit._CCO
#define ESCR6_SCES escr6.bit._SCES
#define ESCR6_LBL escr6.bitc._LBL
__IO_EXTERN __io ECCR6STR eccr6;  
#define ECCR6 eccr6.byte
#define ECCR6_LBR eccr6.bit._LBR
#define ECCR6_MS eccr6.bit._MS
#define ECCR6_SCDE eccr6.bit._SCDE
#define ECCR6_SSM eccr6.bit._SSM
#define ECCR6_BIE eccr6.bit._BIE
#define ECCR6_RBI eccr6.bit._RBI
#define ECCR6_TBI eccr6.bit._TBI
__IO_EXTERN __io IO_WORD bgr6;  
#define BGR6 bgr6
__IO_EXTERN __io BGR16STR bgr16;  
#define BGR16 bgr16.byte
#define BGR16_B14 bgr16.bit._B14
#define BGR16_B13 bgr16.bit._B13
#define BGR16_B12 bgr16.bit._B12
#define BGR16_B11 bgr16.bit._B11
#define BGR16_B10 bgr16.bit._B10
#define BGR16_B09 bgr16.bit._B09
#define BGR16_B08 bgr16.bit._B08
__IO_EXTERN __io BGR06STR bgr06;  
#define BGR06 bgr06.byte
#define BGR06_B07 bgr06.bit._B07
#define BGR06_B06 bgr06.bit._B06
#define BGR06_B05 bgr06.bit._B05
#define BGR06_B04 bgr06.bit._B04
#define BGR06_B03 bgr06.bit._B03
#define BGR06_B02 bgr06.bit._B02
#define BGR06_B01 bgr06.bit._B01
#define BGR06_B00 bgr06.bit._B00
__IO_EXTERN __io SCR1STR scr1;   /* LIN-UART 1 */
#define SCR1 scr1.byte
#define SCR1_PEN scr1.bit._PEN
#define SCR1_P scr1.bit._P
#define SCR1_SBL scr1.bit._SBL
#define SCR1_CL scr1.bit._CL
#define SCR1_AD scr1.bit._AD
#define SCR1_CRE scr1.bit._CRE
#define SCR1_RXE scr1.bit._RXE
#define SCR1_TXE scr1.bit._TXE
__IO_EXTERN __io SMR1STR smr1;  
#define SMR1 smr1.byte
#define SMR1_MD1 smr1.bit._MD1
#define SMR1_MD0 smr1.bit._MD0
#define SMR1_OTO smr1.bit._OTO
#define SMR1_EXT smr1.bit._EXT
#define SMR1_REST smr1.bit._REST
#define SMR1_UPCL smr1.bit._UPCL
#define SMR1_SCKE smr1.bit._SCKE
#define SMR1_SOE smr1.bit._SOE
#define SMR1_MD smr1.bitc._MD
__IO_EXTERN __io SSR1STR ssr1;  
#define SSR1 ssr1.byte
#define SSR1_PE ssr1.bit._PE
#define SSR1_ORE ssr1.bit._ORE
#define SSR1_FRE ssr1.bit._FRE
#define SSR1_RDRF ssr1.bit._RDRF
#define SSR1_TDRE ssr1.bit._TDRE
#define SSR1_BDS ssr1.bit._BDS
#define SSR1_RIE ssr1.bit._RIE
#define SSR1_TIE ssr1.bit._TIE
__IO_EXTERN __io RDR1STR rdr1;  
#define RDR1 rdr1.byte
#define RDR1_D7 rdr1.bit._D7
#define RDR1_D6 rdr1.bit._D6
#define RDR1_D5 rdr1.bit._D5
#define RDR1_D4 rdr1.bit._D4
#define RDR1_D3 rdr1.bit._D3
#define RDR1_D2 rdr1.bit._D2
#define RDR1_D1 rdr1.bit._D1
#define RDR1_D0 rdr1.bit._D0
__IO_EXTERN __io TDR1STR tdr1;  
#define TDR1 tdr1.byte
#define TDR1_D7 tdr1.bit._D7
#define TDR1_D6 tdr1.bit._D6
#define TDR1_D5 tdr1.bit._D5
#define TDR1_D4 tdr1.bit._D4
#define TDR1_D3 tdr1.bit._D3
#define TDR1_D2 tdr1.bit._D2
#define TDR1_D1 tdr1.bit._D1
#define TDR1_D0 tdr1.bit._D0
__IO_EXTERN __io ESCR1STR escr1;  
#define ESCR1 escr1.byte
#define ESCR1_LBIE escr1.bit._LBIE
#define ESCR1_LBD escr1.bit._LBD
#define ESCR1_LBL1 escr1.bit._LBL1
#define ESCR1_LBL0 escr1.bit._LBL0
#define ESCR1_SOPE escr1.bit._SOPE
#define ESCR1_SIOP escr1.bit._SIOP
#define ESCR1_CCO escr1.bit._CCO
#define ESCR1_SCES escr1.bit._SCES
#define ESCR1_LBL escr1.bitc._LBL
__IO_EXTERN __io ECCR1STR eccr1;  
#define ECCR1 eccr1.byte
#define ECCR1_LBR eccr1.bit._LBR
#define ECCR1_MS eccr1.bit._MS
#define ECCR1_SCDE eccr1.bit._SCDE
#define ECCR1_SSM eccr1.bit._SSM
#define ECCR1_BIE eccr1.bit._BIE
#define ECCR1_RBI eccr1.bit._RBI
#define ECCR1_TBI eccr1.bit._TBI
__IO_EXTERN __io IO_WORD bgr1;  
#define BGR1 bgr1
__IO_EXTERN __io BGR11STR bgr11;  
#define BGR11 bgr11.byte
#define BGR11_B14 bgr11.bit._B14
#define BGR11_B13 bgr11.bit._B13
#define BGR11_B12 bgr11.bit._B12
#define BGR11_B11 bgr11.bit._B11
#define BGR11_B10 bgr11.bit._B10
#define BGR11_B09 bgr11.bit._B09
#define BGR11_B08 bgr11.bit._B08
__IO_EXTERN __io BGR01STR bgr01;  
#define BGR01 bgr01.byte
#define BGR01_B07 bgr01.bit._B07
#define BGR01_B06 bgr01.bit._B06
#define BGR01_B05 bgr01.bit._B05
#define BGR01_B04 bgr01.bit._B04
#define BGR01_B03 bgr01.bit._B03
#define BGR01_B02 bgr01.bit._B02
#define BGR01_B01 bgr01.bit._B01
#define BGR01_B00 bgr01.bit._B00
__IO_EXTERN __io SCR2STR scr2;   /* LIN-UART 2 */
#define SCR2 scr2.byte
#define SCR2_PEN scr2.bit._PEN
#define SCR2_P scr2.bit._P
#define SCR2_SBL scr2.bit._SBL
#define SCR2_CL scr2.bit._CL
#define SCR2_AD scr2.bit._AD
#define SCR2_CRE scr2.bit._CRE
#define SCR2_RXE scr2.bit._RXE
#define SCR2_TXE scr2.bit._TXE
__IO_EXTERN __io SMR2STR smr2;  
#define SMR2 smr2.byte
#define SMR2_MD1 smr2.bit._MD1
#define SMR2_MD0 smr2.bit._MD0
#define SMR2_OTO smr2.bit._OTO
#define SMR2_EXT smr2.bit._EXT
#define SMR2_REST smr2.bit._REST
#define SMR2_UPCL smr2.bit._UPCL
#define SMR2_SCKE smr2.bit._SCKE
#define SMR2_SOE smr2.bit._SOE
#define SMR2_MD smr2.bitc._MD
__IO_EXTERN __io SSR2STR ssr2;  
#define SSR2 ssr2.byte
#define SSR2_PE ssr2.bit._PE
#define SSR2_ORE ssr2.bit._ORE
#define SSR2_FRE ssr2.bit._FRE
#define SSR2_RDRF ssr2.bit._RDRF
#define SSR2_TDRE ssr2.bit._TDRE
#define SSR2_BDS ssr2.bit._BDS
#define SSR2_RIE ssr2.bit._RIE
#define SSR2_TIE ssr2.bit._TIE
__IO_EXTERN __io RDR2STR rdr2;  
#define RDR2 rdr2.byte
#define RDR2_D7 rdr2.bit._D7
#define RDR2_D6 rdr2.bit._D6
#define RDR2_D5 rdr2.bit._D5
#define RDR2_D4 rdr2.bit._D4
#define RDR2_D3 rdr2.bit._D3
#define RDR2_D2 rdr2.bit._D2
#define RDR2_D1 rdr2.bit._D1
#define RDR2_D0 rdr2.bit._D0
__IO_EXTERN __io TDR2STR tdr2;  
#define TDR2 tdr2.byte
#define TDR2_D7 tdr2.bit._D7
#define TDR2_D6 tdr2.bit._D6
#define TDR2_D5 tdr2.bit._D5
#define TDR2_D4 tdr2.bit._D4
#define TDR2_D3 tdr2.bit._D3
#define TDR2_D2 tdr2.bit._D2
#define TDR2_D1 tdr2.bit._D1
#define TDR2_D0 tdr2.bit._D0
__IO_EXTERN __io ESCR2STR escr2;  
#define ESCR2 escr2.byte
#define ESCR2_LBIE escr2.bit._LBIE
#define ESCR2_LBD escr2.bit._LBD
#define ESCR2_LBL1 escr2.bit._LBL1
#define ESCR2_LBL0 escr2.bit._LBL0
#define ESCR2_SOPE escr2.bit._SOPE
#define ESCR2_SIOP escr2.bit._SIOP
#define ESCR2_CCO escr2.bit._CCO
#define ESCR2_SCES escr2.bit._SCES
#define ESCR2_LBL escr2.bitc._LBL
__IO_EXTERN __io ECCR2STR eccr2;  
#define ECCR2 eccr2.byte
#define ECCR2_LBR eccr2.bit._LBR
#define ECCR2_MS eccr2.bit._MS
#define ECCR2_SCDE eccr2.bit._SCDE
#define ECCR2_SSM eccr2.bit._SSM
#define ECCR2_BIE eccr2.bit._BIE
#define ECCR2_RBI eccr2.bit._RBI
#define ECCR2_TBI eccr2.bit._TBI
__IO_EXTERN __io IO_WORD bgr2;  
#define BGR2 bgr2
__IO_EXTERN __io BGR12STR bgr12;  
#define BGR12 bgr12.byte
#define BGR12_B14 bgr12.bit._B14
#define BGR12_B13 bgr12.bit._B13
#define BGR12_B12 bgr12.bit._B12
#define BGR12_B11 bgr12.bit._B11
#define BGR12_B10 bgr12.bit._B10
#define BGR12_B09 bgr12.bit._B09
#define BGR12_B08 bgr12.bit._B08
__IO_EXTERN __io BGR02STR bgr02;  
#define BGR02 bgr02.byte
#define BGR02_B07 bgr02.bit._B07
#define BGR02_B06 bgr02.bit._B06
#define BGR02_B05 bgr02.bit._B05
#define BGR02_B04 bgr02.bit._B04
#define BGR02_B03 bgr02.bit._B03
#define BGR02_B02 bgr02.bit._B02
#define BGR02_B01 bgr02.bit._B01
#define BGR02_B00 bgr02.bit._B00
__IO_EXTERN __io SCR3STR scr3;   /* LIN-UART 3 */
#define SCR3 scr3.byte
#define SCR3_PEN scr3.bit._PEN
#define SCR3_P scr3.bit._P
#define SCR3_SBL scr3.bit._SBL
#define SCR3_CL scr3.bit._CL
#define SCR3_AD scr3.bit._AD
#define SCR3_CRE scr3.bit._CRE
#define SCR3_RXE scr3.bit._RXE
#define SCR3_TXE scr3.bit._TXE
__IO_EXTERN __io SMR3STR smr3;  
#define SMR3 smr3.byte
#define SMR3_MD1 smr3.bit._MD1
#define SMR3_MD0 smr3.bit._MD0
#define SMR3_OTO smr3.bit._OTO
#define SMR3_EXT smr3.bit._EXT
#define SMR3_REST smr3.bit._REST
#define SMR3_UPCL smr3.bit._UPCL
#define SMR3_SCKE smr3.bit._SCKE
#define SMR3_SOE smr3.bit._SOE
#define SMR3_MD smr3.bitc._MD
__IO_EXTERN __io SSR3STR ssr3;  
#define SSR3 ssr3.byte
#define SSR3_PE ssr3.bit._PE
#define SSR3_ORE ssr3.bit._ORE
#define SSR3_FRE ssr3.bit._FRE
#define SSR3_RDRF ssr3.bit._RDRF
#define SSR3_TDRE ssr3.bit._TDRE
#define SSR3_BDS ssr3.bit._BDS
#define SSR3_RIE ssr3.bit._RIE
#define SSR3_TIE ssr3.bit._TIE
__IO_EXTERN __io RDR3STR rdr3;  
#define RDR3 rdr3.byte
#define RDR3_D7 rdr3.bit._D7
#define RDR3_D6 rdr3.bit._D6
#define RDR3_D5 rdr3.bit._D5
#define RDR3_D4 rdr3.bit._D4
#define RDR3_D3 rdr3.bit._D3
#define RDR3_D2 rdr3.bit._D2
#define RDR3_D1 rdr3.bit._D1
#define RDR3_D0 rdr3.bit._D0
__IO_EXTERN __io TDR3STR tdr3;  
#define TDR3 tdr3.byte
#define TDR3_D7 tdr3.bit._D7
#define TDR3_D6 tdr3.bit._D6
#define TDR3_D5 tdr3.bit._D5
#define TDR3_D4 tdr3.bit._D4
#define TDR3_D3 tdr3.bit._D3
#define TDR3_D2 tdr3.bit._D2
#define TDR3_D1 tdr3.bit._D1
#define TDR3_D0 tdr3.bit._D0
__IO_EXTERN __io ESCR3STR escr3;  
#define ESCR3 escr3.byte
#define ESCR3_LBIE escr3.bit._LBIE
#define ESCR3_LBD escr3.bit._LBD
#define ESCR3_LBL1 escr3.bit._LBL1
#define ESCR3_LBL0 escr3.bit._LBL0
#define ESCR3_SOPE escr3.bit._SOPE
#define ESCR3_SIOP escr3.bit._SIOP
#define ESCR3_CCO escr3.bit._CCO
#define ESCR3_SCES escr3.bit._SCES
#define ESCR3_LBL escr3.bitc._LBL
__IO_EXTERN __io ECCR3STR eccr3;  
#define ECCR3 eccr3.byte
#define ECCR3_LBR eccr3.bit._LBR
#define ECCR3_MS eccr3.bit._MS
#define ECCR3_SCDE eccr3.bit._SCDE
#define ECCR3_SSM eccr3.bit._SSM
#define ECCR3_BIE eccr3.bit._BIE
#define ECCR3_RBI eccr3.bit._RBI
#define ECCR3_TBI eccr3.bit._TBI
__IO_EXTERN __io IO_WORD bgr3;  
#define BGR3 bgr3
__IO_EXTERN __io BGR13STR bgr13;  
#define BGR13 bgr13.byte
#define BGR13_B14 bgr13.bit._B14
#define BGR13_B13 bgr13.bit._B13
#define BGR13_B12 bgr13.bit._B12
#define BGR13_B11 bgr13.bit._B11
#define BGR13_B10 bgr13.bit._B10
#define BGR13_B09 bgr13.bit._B09
#define BGR13_B08 bgr13.bit._B08
__IO_EXTERN __io BGR03STR bgr03;  
#define BGR03 bgr03.byte
#define BGR03_B07 bgr03.bit._B07
#define BGR03_B06 bgr03.bit._B06
#define BGR03_B05 bgr03.bit._B05
#define BGR03_B04 bgr03.bit._B04
#define BGR03_B03 bgr03.bit._B03
#define BGR03_B02 bgr03.bit._B02
#define BGR03_B01 bgr03.bit._B01
#define BGR03_B00 bgr03.bit._B00
__IO_EXTERN __io SCR4STR scr4;   /* LIN-UART 4 */
#define SCR4 scr4.byte
#define SCR4_PEN scr4.bit._PEN
#define SCR4_P scr4.bit._P
#define SCR4_SBL scr4.bit._SBL
#define SCR4_CL scr4.bit._CL
#define SCR4_AD scr4.bit._AD
#define SCR4_CRE scr4.bit._CRE
#define SCR4_RXE scr4.bit._RXE
#define SCR4_TXE scr4.bit._TXE
__IO_EXTERN __io SMR4STR smr4;  
#define SMR4 smr4.byte
#define SMR4_MD1 smr4.bit._MD1
#define SMR4_MD0 smr4.bit._MD0
#define SMR4_OTO smr4.bit._OTO
#define SMR4_EXT smr4.bit._EXT
#define SMR4_REST smr4.bit._REST
#define SMR4_UPCL smr4.bit._UPCL
#define SMR4_SCKE smr4.bit._SCKE
#define SMR4_SOE smr4.bit._SOE
#define SMR4_MD smr4.bitc._MD
__IO_EXTERN __io SSR4STR ssr4;  
#define SSR4 ssr4.byte
#define SSR4_PE ssr4.bit._PE
#define SSR4_ORE ssr4.bit._ORE
#define SSR4_FRE ssr4.bit._FRE
#define SSR4_RDRF ssr4.bit._RDRF
#define SSR4_TDRE ssr4.bit._TDRE
#define SSR4_BDS ssr4.bit._BDS
#define SSR4_RIE ssr4.bit._RIE
#define SSR4_TIE ssr4.bit._TIE
__IO_EXTERN __io RDR4STR rdr4;  
#define RDR4 rdr4.byte
#define RDR4_D7 rdr4.bit._D7
#define RDR4_D6 rdr4.bit._D6
#define RDR4_D5 rdr4.bit._D5
#define RDR4_D4 rdr4.bit._D4
#define RDR4_D3 rdr4.bit._D3
#define RDR4_D2 rdr4.bit._D2
#define RDR4_D1 rdr4.bit._D1
#define RDR4_D0 rdr4.bit._D0
__IO_EXTERN __io TDR4STR tdr4;  
#define TDR4 tdr4.byte
#define TDR4_D7 tdr4.bit._D7
#define TDR4_D6 tdr4.bit._D6
#define TDR4_D5 tdr4.bit._D5
#define TDR4_D4 tdr4.bit._D4
#define TDR4_D3 tdr4.bit._D3
#define TDR4_D2 tdr4.bit._D2
#define TDR4_D1 tdr4.bit._D1
#define TDR4_D0 tdr4.bit._D0
__IO_EXTERN __io ESCR4STR escr4;  
#define ESCR4 escr4.byte
#define ESCR4_LBIE escr4.bit._LBIE
#define ESCR4_LBD escr4.bit._LBD
#define ESCR4_LBL1 escr4.bit._LBL1
#define ESCR4_LBL0 escr4.bit._LBL0
#define ESCR4_SOPE escr4.bit._SOPE
#define ESCR4_SIOP escr4.bit._SIOP
#define ESCR4_CCO escr4.bit._CCO
#define ESCR4_SCES escr4.bit._SCES
#define ESCR4_LBL escr4.bitc._LBL
__IO_EXTERN __io ECCR4STR eccr4;  
#define ECCR4 eccr4.byte
#define ECCR4_LBR eccr4.bit._LBR
#define ECCR4_MS eccr4.bit._MS
#define ECCR4_SCDE eccr4.bit._SCDE
#define ECCR4_SSM eccr4.bit._SSM
#define ECCR4_BIE eccr4.bit._BIE
#define ECCR4_RBI eccr4.bit._RBI
#define ECCR4_TBI eccr4.bit._TBI
__IO_EXTERN __io IO_WORD bgr4;  
#define BGR4 bgr4
__IO_EXTERN __io BGR14STR bgr14;  
#define BGR14 bgr14.byte
#define BGR14_B14 bgr14.bit._B14
#define BGR14_B13 bgr14.bit._B13
#define BGR14_B12 bgr14.bit._B12
#define BGR14_B11 bgr14.bit._B11
#define BGR14_B10 bgr14.bit._B10
#define BGR14_B09 bgr14.bit._B09
#define BGR14_B08 bgr14.bit._B08
__IO_EXTERN __io BGR04STR bgr04;  
#define BGR04 bgr04.byte
#define BGR04_B07 bgr04.bit._B07
#define BGR04_B06 bgr04.bit._B06
#define BGR04_B05 bgr04.bit._B05
#define BGR04_B04 bgr04.bit._B04
#define BGR04_B03 bgr04.bit._B03
#define BGR04_B02 bgr04.bit._B02
#define BGR04_B01 bgr04.bit._B01
#define BGR04_B00 bgr04.bit._B00
__IO_EXTERN __io EIRR1STR eirr1;   /* External Interrupt 8-15 */
#define EIRR1 eirr1.byte
#define EIRR1_ER7 eirr1.bit._ER7
#define EIRR1_ER6 eirr1.bit._ER6
#define EIRR1_ER5 eirr1.bit._ER5
#define EIRR1_ER4 eirr1.bit._ER4
#define EIRR1_ER3 eirr1.bit._ER3
#define EIRR1_ER2 eirr1.bit._ER2
#define EIRR1_ER1 eirr1.bit._ER1
#define EIRR1_ER0 eirr1.bit._ER0
__IO_EXTERN __io ENIR1STR enir1;  
#define ENIR1 enir1.byte
#define ENIR1_EN7 enir1.bit._EN7
#define ENIR1_EN6 enir1.bit._EN6
#define ENIR1_EN5 enir1.bit._EN5
#define ENIR1_EN4 enir1.bit._EN4
#define ENIR1_EN3 enir1.bit._EN3
#define ENIR1_EN2 enir1.bit._EN2
#define ENIR1_EN1 enir1.bit._EN1
#define ENIR1_EN0 enir1.bit._EN0
__IO_EXTERN __io ELVR1STR elvr1;  
#define ELVR1 elvr1.word
#define ELVR1_LB7 elvr1.bit._LB7
#define ELVR1_LA7 elvr1.bit._LA7
#define ELVR1_LB6 elvr1.bit._LB6
#define ELVR1_LA6 elvr1.bit._LA6
#define ELVR1_LB5 elvr1.bit._LB5
#define ELVR1_LA5 elvr1.bit._LA5
#define ELVR1_LB4 elvr1.bit._LB4
#define ELVR1_LA4 elvr1.bit._LA4
#define ELVR1_LB3 elvr1.bit._LB3
#define ELVR1_LA3 elvr1.bit._LA3
#define ELVR1_LB2 elvr1.bit._LB2
#define ELVR1_LA2 elvr1.bit._LA2
#define ELVR1_LB1 elvr1.bit._LB1
#define ELVR1_LA1 elvr1.bit._LA1
#define ELVR1_LB0 elvr1.bit._LB0
#define ELVR1_LA0 elvr1.bit._LA0
__IO_EXTERN __io IO_WORD tctdt0;   /* Free-Run Timer 0 */
#define TCTDT0 tctdt0
__IO_EXTERN __io TCCCS0STR tcccs0;  
#define TCCCS0 tcccs0.byte
#define TCCCS0_ECLK tcccs0.bit._ECLK
#define TCCCS0_IVF tcccs0.bit._IVF
#define TCCCS0_IVFE tcccs0.bit._IVFE
#define TCCCS0_STOP tcccs0.bit._STOP
#define TCCCS0_MODE tcccs0.bit._MODE
#define TCCCS0_CLR tcccs0.bit._CLR
#define TCCCS0_CLK1 tcccs0.bit._CLK1
#define TCCCS0_CLK0 tcccs0.bit._CLK0
#define TCCCS0_CLK tcccs0.bitc._CLK
__IO_EXTERN __io IO_WORD tctdt1;   /* Free-Run Timer 1 */
#define TCTDT1 tctdt1
__IO_EXTERN __io TCCCS1STR tcccs1;  
#define TCCCS1 tcccs1.byte
#define TCCCS1_ECLK tcccs1.bit._ECLK
#define TCCCS1_IVF tcccs1.bit._IVF
#define TCCCS1_IVFE tcccs1.bit._IVFE
#define TCCCS1_STOP tcccs1.bit._STOP
#define TCCCS1_MODE tcccs1.bit._MODE
#define TCCCS1_CLR tcccs1.bit._CLR
#define TCCCS1_CLK1 tcccs1.bit._CLK1
#define TCCCS1_CLK0 tcccs1.bit._CLK0
#define TCCCS1_CLK tcccs1.bitc._CLK
__IO_EXTERN __io IO_WORD tctdt2;   /* Free-Run Timer 2 */
#define TCTDT2 tctdt2
__IO_EXTERN __io TCCCS2STR tcccs2;  
#define TCCCS2 tcccs2.byte
#define TCCCS2_ECLK tcccs2.bit._ECLK
#define TCCCS2_IVF tcccs2.bit._IVF
#define TCCCS2_IVFE tcccs2.bit._IVFE
#define TCCCS2_STOP tcccs2.bit._STOP
#define TCCCS2_MODE tcccs2.bit._MODE
#define TCCCS2_CLR tcccs2.bit._CLR
#define TCCCS2_CLK1 tcccs2.bit._CLK1
#define TCCCS2_CLK0 tcccs2.bit._CLK0
#define TCCCS2_CLK tcccs2.bitc._CLK
__IO_EXTERN __io IO_WORD tctdt3;   /* Free-Run Timer 3 */
#define TCTDT3 tctdt3
__IO_EXTERN __io TCCCS3STR tcccs3;  
#define TCCCS3 tcccs3.byte
#define TCCCS3_ECLK tcccs3.bit._ECLK
#define TCCCS3_IVF tcccs3.bit._IVF
#define TCCCS3_IVFE tcccs3.bit._IVFE
#define TCCCS3_STOP tcccs3.bit._STOP
#define TCCCS3_MODE tcccs3.bit._MODE
#define TCCCS3_CLR tcccs3.bit._CLR
#define TCCCS3_CLK1 tcccs3.bit._CLK1
#define TCCCS3_CLK0 tcccs3.bit._CLK0
#define TCCCS3_CLK tcccs3.bitc._CLK
__IO_EXTERN __io IPCP1STR ipcp1;   /* Input Capture 0-7 */
#define IPCP1 ipcp1.word
#define IPCP1_CP15 ipcp1.bit._CP15
#define IPCP1_CP14 ipcp1.bit._CP14
#define IPCP1_CP13 ipcp1.bit._CP13
#define IPCP1_CP12 ipcp1.bit._CP12
#define IPCP1_CP11 ipcp1.bit._CP11
#define IPCP1_CP10 ipcp1.bit._CP10
#define IPCP1_CP09 ipcp1.bit._CP09
#define IPCP1_CP08 ipcp1.bit._CP08
#define IPCP1_CP07 ipcp1.bit._CP07
#define IPCP1_CP06 ipcp1.bit._CP06
#define IPCP1_CP05 ipcp1.bit._CP05
#define IPCP1_CP04 ipcp1.bit._CP04
#define IPCP1_CP03 ipcp1.bit._CP03
#define IPCP1_CP02 ipcp1.bit._CP02
#define IPCP1_CP01 ipcp1.bit._CP01
#define IPCP1_CP00 ipcp1.bit._CP00
__IO_EXTERN __io IPCP0STR ipcp0;  
#define IPCP0 ipcp0.word
#define IPCP0_CP15 ipcp0.bit._CP15
#define IPCP0_CP14 ipcp0.bit._CP14
#define IPCP0_CP13 ipcp0.bit._CP13
#define IPCP0_CP12 ipcp0.bit._CP12
#define IPCP0_CP11 ipcp0.bit._CP11
#define IPCP0_CP10 ipcp0.bit._CP10
#define IPCP0_CP09 ipcp0.bit._CP09
#define IPCP0_CP08 ipcp0.bit._CP08
#define IPCP0_CP07 ipcp0.bit._CP07
#define IPCP0_CP06 ipcp0.bit._CP06
#define IPCP0_CP05 ipcp0.bit._CP05
#define IPCP0_CP04 ipcp0.bit._CP04
#define IPCP0_CP03 ipcp0.bit._CP03
#define IPCP0_CP02 ipcp0.bit._CP02
#define IPCP0_CP01 ipcp0.bit._CP01
#define IPCP0_CP00 ipcp0.bit._CP00
__IO_EXTERN __io ICS01STR ics01;  
#define ICS01 ics01.byte
#define ICS01_ICP1 ics01.bit._ICP1
#define ICS01_ICP0 ics01.bit._ICP0
#define ICS01_ICE1 ics01.bit._ICE1
#define ICS01_ICE0 ics01.bit._ICE0
#define ICS01_EG11 ics01.bit._EG11
#define ICS01_EG10 ics01.bit._EG10
#define ICS01_EG01 ics01.bit._EG01
#define ICS01_EG00 ics01.bit._EG00
#define ICS01_EG1 ics01.bitc._EG1
#define ICS01_EG0 ics01.bitc._EG0
__IO_EXTERN __io IPCP3STR ipcp3;  
#define IPCP3 ipcp3.word
#define IPCP3_CP15 ipcp3.bit._CP15
#define IPCP3_CP14 ipcp3.bit._CP14
#define IPCP3_CP13 ipcp3.bit._CP13
#define IPCP3_CP12 ipcp3.bit._CP12
#define IPCP3_CP11 ipcp3.bit._CP11
#define IPCP3_CP10 ipcp3.bit._CP10
#define IPCP3_CP09 ipcp3.bit._CP09
#define IPCP3_CP08 ipcp3.bit._CP08
#define IPCP3_CP07 ipcp3.bit._CP07
#define IPCP3_CP06 ipcp3.bit._CP06
#define IPCP3_CP05 ipcp3.bit._CP05
#define IPCP3_CP04 ipcp3.bit._CP04
#define IPCP3_CP03 ipcp3.bit._CP03
#define IPCP3_CP02 ipcp3.bit._CP02
#define IPCP3_CP01 ipcp3.bit._CP01
#define IPCP3_CP00 ipcp3.bit._CP00
__IO_EXTERN __io IPCP2STR ipcp2;  
#define IPCP2 ipcp2.word
#define IPCP2_CP15 ipcp2.bit._CP15
#define IPCP2_CP14 ipcp2.bit._CP14
#define IPCP2_CP13 ipcp2.bit._CP13
#define IPCP2_CP12 ipcp2.bit._CP12
#define IPCP2_CP11 ipcp2.bit._CP11
#define IPCP2_CP10 ipcp2.bit._CP10
#define IPCP2_CP09 ipcp2.bit._CP09
#define IPCP2_CP08 ipcp2.bit._CP08
#define IPCP2_CP07 ipcp2.bit._CP07
#define IPCP2_CP06 ipcp2.bit._CP06
#define IPCP2_CP05 ipcp2.bit._CP05
#define IPCP2_CP04 ipcp2.bit._CP04
#define IPCP2_CP03 ipcp2.bit._CP03
#define IPCP2_CP02 ipcp2.bit._CP02
#define IPCP2_CP01 ipcp2.bit._CP01
#define IPCP2_CP00 ipcp2.bit._CP00
__IO_EXTERN __io ICS23STR ics23;  
#define ICS23 ics23.byte
#define ICS23_ICP1 ics23.bit._ICP1
#define ICS23_ICP0 ics23.bit._ICP0
#define ICS23_ICE1 ics23.bit._ICE1
#define ICS23_ICE0 ics23.bit._ICE0
#define ICS23_EG11 ics23.bit._EG11
#define ICS23_EG10 ics23.bit._EG10
#define ICS23_EG01 ics23.bit._EG01
#define ICS23_EG00 ics23.bit._EG00
#define ICS23_EG1 ics23.bitc._EG1
#define ICS23_EG0 ics23.bitc._EG0
__IO_EXTERN __io IPCP5STR ipcp5;  
#define IPCP5 ipcp5.word
#define IPCP5_CP15 ipcp5.bit._CP15
#define IPCP5_CP14 ipcp5.bit._CP14
#define IPCP5_CP13 ipcp5.bit._CP13
#define IPCP5_CP12 ipcp5.bit._CP12
#define IPCP5_CP11 ipcp5.bit._CP11
#define IPCP5_CP10 ipcp5.bit._CP10
#define IPCP5_CP09 ipcp5.bit._CP09
#define IPCP5_CP08 ipcp5.bit._CP08
#define IPCP5_CP07 ipcp5.bit._CP07
#define IPCP5_CP06 ipcp5.bit._CP06
#define IPCP5_CP05 ipcp5.bit._CP05
#define IPCP5_CP04 ipcp5.bit._CP04
#define IPCP5_CP03 ipcp5.bit._CP03
#define IPCP5_CP02 ipcp5.bit._CP02
#define IPCP5_CP01 ipcp5.bit._CP01
#define IPCP5_CP00 ipcp5.bit._CP00
__IO_EXTERN __io IPCP4STR ipcp4;  
#define IPCP4 ipcp4.word
#define IPCP4_CP15 ipcp4.bit._CP15
#define IPCP4_CP14 ipcp4.bit._CP14
#define IPCP4_CP13 ipcp4.bit._CP13
#define IPCP4_CP12 ipcp4.bit._CP12
#define IPCP4_CP11 ipcp4.bit._CP11
#define IPCP4_CP10 ipcp4.bit._CP10
#define IPCP4_CP09 ipcp4.bit._CP09
#define IPCP4_CP08 ipcp4.bit._CP08
#define IPCP4_CP07 ipcp4.bit._CP07
#define IPCP4_CP06 ipcp4.bit._CP06
#define IPCP4_CP05 ipcp4.bit._CP05
#define IPCP4_CP04 ipcp4.bit._CP04
#define IPCP4_CP03 ipcp4.bit._CP03
#define IPCP4_CP02 ipcp4.bit._CP02
#define IPCP4_CP01 ipcp4.bit._CP01
#define IPCP4_CP00 ipcp4.bit._CP00
__IO_EXTERN __io ICS45STR ics45;  
#define ICS45 ics45.byte
#define ICS45_ICP1 ics45.bit._ICP1
#define ICS45_ICP0 ics45.bit._ICP0
#define ICS45_ICE1 ics45.bit._ICE1
#define ICS45_ICE0 ics45.bit._ICE0
#define ICS45_EG11 ics45.bit._EG11
#define ICS45_EG10 ics45.bit._EG10
#define ICS45_EG01 ics45.bit._EG01
#define ICS45_EG00 ics45.bit._EG00
#define ICS45_EG1 ics45.bitc._EG1
#define ICS45_EG0 ics45.bitc._EG0
__IO_EXTERN __io IPCP7STR ipcp7;  
#define IPCP7 ipcp7.word
#define IPCP7_CP15 ipcp7.bit._CP15
#define IPCP7_CP14 ipcp7.bit._CP14
#define IPCP7_CP13 ipcp7.bit._CP13
#define IPCP7_CP12 ipcp7.bit._CP12
#define IPCP7_CP11 ipcp7.bit._CP11
#define IPCP7_CP10 ipcp7.bit._CP10
#define IPCP7_CP09 ipcp7.bit._CP09
#define IPCP7_CP08 ipcp7.bit._CP08
#define IPCP7_CP07 ipcp7.bit._CP07
#define IPCP7_CP06 ipcp7.bit._CP06
#define IPCP7_CP05 ipcp7.bit._CP05
#define IPCP7_CP04 ipcp7.bit._CP04
#define IPCP7_CP03 ipcp7.bit._CP03
#define IPCP7_CP02 ipcp7.bit._CP02
#define IPCP7_CP01 ipcp7.bit._CP01
#define IPCP7_CP00 ipcp7.bit._CP00
__IO_EXTERN __io IPCP6STR ipcp6;  
#define IPCP6 ipcp6.word
#define IPCP6_CP15 ipcp6.bit._CP15
#define IPCP6_CP14 ipcp6.bit._CP14
#define IPCP6_CP13 ipcp6.bit._CP13
#define IPCP6_CP12 ipcp6.bit._CP12
#define IPCP6_CP11 ipcp6.bit._CP11
#define IPCP6_CP10 ipcp6.bit._CP10
#define IPCP6_CP09 ipcp6.bit._CP09
#define IPCP6_CP08 ipcp6.bit._CP08
#define IPCP6_CP07 ipcp6.bit._CP07
#define IPCP6_CP06 ipcp6.bit._CP06
#define IPCP6_CP05 ipcp6.bit._CP05
#define IPCP6_CP04 ipcp6.bit._CP04
#define IPCP6_CP03 ipcp6.bit._CP03
#define IPCP6_CP02 ipcp6.bit._CP02
#define IPCP6_CP01 ipcp6.bit._CP01
#define IPCP6_CP00 ipcp6.bit._CP00
__IO_EXTERN ICS67STR ics67;  
#define ICS67 ics67.byte
#define ICS67_ICP1 ics67.bit._ICP1
#define ICS67_ICP0 ics67.bit._ICP0
#define ICS67_ICE1 ics67.bit._ICE1
#define ICS67_ICE0 ics67.bit._ICE0
#define ICS67_EG11 ics67.bit._EG11
#define ICS67_EG10 ics67.bit._EG10
#define ICS67_EG01 ics67.bit._EG01
#define ICS67_EG00 ics67.bit._EG00
#define ICS67_EG1 ics67.bitc._EG1
#define ICS67_EG0 ics67.bitc._EG0
__IO_EXTERN OCCP1STR occp1;   /* Output Compare 0-7 */
#define OCCP1 occp1.word
#define OCCP1_C15 occp1.bit._C15
#define OCCP1_C14 occp1.bit._C14
#define OCCP1_C13 occp1.bit._C13
#define OCCP1_C12 occp1.bit._C12
#define OCCP1_C11 occp1.bit._C11
#define OCCP1_C10 occp1.bit._C10
#define OCCP1_C09 occp1.bit._C09
#define OCCP1_C08 occp1.bit._C08
#define OCCP1_C07 occp1.bit._C07
#define OCCP1_C06 occp1.bit._C06
#define OCCP1_C05 occp1.bit._C05
#define OCCP1_C04 occp1.bit._C04
#define OCCP1_C03 occp1.bit._C03
#define OCCP1_C02 occp1.bit._C02
#define OCCP1_C01 occp1.bit._C01
#define OCCP1_C00 occp1.bit._C00
__IO_EXTERN OCCP0STR occp0;  
#define OCCP0 occp0.word
#define OCCP0_C15 occp0.bit._C15
#define OCCP0_C14 occp0.bit._C14
#define OCCP0_C13 occp0.bit._C13
#define OCCP0_C12 occp0.bit._C12
#define OCCP0_C11 occp0.bit._C11
#define OCCP0_C10 occp0.bit._C10
#define OCCP0_C09 occp0.bit._C09
#define OCCP0_C08 occp0.bit._C08
#define OCCP0_C07 occp0.bit._C07
#define OCCP0_C06 occp0.bit._C06
#define OCCP0_C05 occp0.bit._C05
#define OCCP0_C04 occp0.bit._C04
#define OCCP0_C03 occp0.bit._C03
#define OCCP0_C02 occp0.bit._C02
#define OCCP0_C01 occp0.bit._C01
#define OCCP0_C00 occp0.bit._C00
__IO_EXTERN OCCP3STR occp3;  
#define OCCP3 occp3.word
#define OCCP3_C15 occp3.bit._C15
#define OCCP3_C14 occp3.bit._C14
#define OCCP3_C13 occp3.bit._C13
#define OCCP3_C12 occp3.bit._C12
#define OCCP3_C11 occp3.bit._C11
#define OCCP3_C10 occp3.bit._C10
#define OCCP3_C09 occp3.bit._C09
#define OCCP3_C08 occp3.bit._C08
#define OCCP3_C07 occp3.bit._C07
#define OCCP3_C06 occp3.bit._C06
#define OCCP3_C05 occp3.bit._C05
#define OCCP3_C04 occp3.bit._C04
#define OCCP3_C03 occp3.bit._C03
#define OCCP3_C02 occp3.bit._C02
#define OCCP3_C01 occp3.bit._C01
#define OCCP3_C00 occp3.bit._C00
__IO_EXTERN OCCP2STR occp2;  
#define OCCP2 occp2.word
#define OCCP2_C15 occp2.bit._C15
#define OCCP2_C14 occp2.bit._C14
#define OCCP2_C13 occp2.bit._C13
#define OCCP2_C12 occp2.bit._C12
#define OCCP2_C11 occp2.bit._C11
#define OCCP2_C10 occp2.bit._C10
#define OCCP2_C09 occp2.bit._C09
#define OCCP2_C08 occp2.bit._C08
#define OCCP2_C07 occp2.bit._C07
#define OCCP2_C06 occp2.bit._C06
#define OCCP2_C05 occp2.bit._C05
#define OCCP2_C04 occp2.bit._C04
#define OCCP2_C03 occp2.bit._C03
#define OCCP2_C02 occp2.bit._C02
#define OCCP2_C01 occp2.bit._C01
#define OCCP2_C00 occp2.bit._C00
__IO_EXTERN OCS23STR ocs23;  
#define OCS23 ocs23.word
#define OCS23_CMOD ocs23.bit._CMOD
#define OCS23_OTD3 ocs23.bit._OTD3
#define OCS23_OTD2 ocs23.bit._OTD2
#define OCS23_ICP3 ocs23.bit._ICP3
#define OCS23_ICP2 ocs23.bit._ICP2
#define OCS23_ICE3 ocs23.bit._ICE3
#define OCS23_ICE2 ocs23.bit._ICE2
#define OCS23_CST3 ocs23.bit._CST3
#define OCS23_CST2 ocs23.bit._CST2
__IO_EXTERN OCS01STR ocs01;  
#define OCS01 ocs01.word
#define OCS01_CMOD ocs01.bit._CMOD
#define OCS01_OTD1 ocs01.bit._OTD1
#define OCS01_OTD0 ocs01.bit._OTD0
#define OCS01_ICP1 ocs01.bit._ICP1
#define OCS01_ICP0 ocs01.bit._ICP0
#define OCS01_ICE1 ocs01.bit._ICE1
#define OCS01_ICE0 ocs01.bit._ICE0
#define OCS01_CST1 ocs01.bit._CST1
#define OCS01_CST0 ocs01.bit._CST0
__IO_EXTERN OCCP5STR occp5;  
#define OCCP5 occp5.word
#define OCCP5_C15 occp5.bit._C15
#define OCCP5_C14 occp5.bit._C14
#define OCCP5_C13 occp5.bit._C13
#define OCCP5_C12 occp5.bit._C12
#define OCCP5_C11 occp5.bit._C11
#define OCCP5_C10 occp5.bit._C10
#define OCCP5_C09 occp5.bit._C09
#define OCCP5_C08 occp5.bit._C08
#define OCCP5_C07 occp5.bit._C07
#define OCCP5_C06 occp5.bit._C06
#define OCCP5_C05 occp5.bit._C05
#define OCCP5_C04 occp5.bit._C04
#define OCCP5_C03 occp5.bit._C03
#define OCCP5_C02 occp5.bit._C02
#define OCCP5_C01 occp5.bit._C01
#define OCCP5_C00 occp5.bit._C00
__IO_EXTERN OCCP4STR occp4;  
#define OCCP4 occp4.word
#define OCCP4_C15 occp4.bit._C15
#define OCCP4_C14 occp4.bit._C14
#define OCCP4_C13 occp4.bit._C13
#define OCCP4_C12 occp4.bit._C12
#define OCCP4_C11 occp4.bit._C11
#define OCCP4_C10 occp4.bit._C10
#define OCCP4_C09 occp4.bit._C09
#define OCCP4_C08 occp4.bit._C08
#define OCCP4_C07 occp4.bit._C07
#define OCCP4_C06 occp4.bit._C06
#define OCCP4_C05 occp4.bit._C05
#define OCCP4_C04 occp4.bit._C04
#define OCCP4_C03 occp4.bit._C03
#define OCCP4_C02 occp4.bit._C02
#define OCCP4_C01 occp4.bit._C01
#define OCCP4_C00 occp4.bit._C00
__IO_EXTERN OCCP7STR occp7;  
#define OCCP7 occp7.word
#define OCCP7_C15 occp7.bit._C15
#define OCCP7_C14 occp7.bit._C14
#define OCCP7_C13 occp7.bit._C13
#define OCCP7_C12 occp7.bit._C12
#define OCCP7_C11 occp7.bit._C11
#define OCCP7_C10 occp7.bit._C10
#define OCCP7_C09 occp7.bit._C09
#define OCCP7_C08 occp7.bit._C08
#define OCCP7_C07 occp7.bit._C07
#define OCCP7_C06 occp7.bit._C06
#define OCCP7_C05 occp7.bit._C05
#define OCCP7_C04 occp7.bit._C04
#define OCCP7_C03 occp7.bit._C03
#define OCCP7_C02 occp7.bit._C02
#define OCCP7_C01 occp7.bit._C01
#define OCCP7_C00 occp7.bit._C00
__IO_EXTERN OCCP6STR occp6;  
#define OCCP6 occp6.word
#define OCCP6_C15 occp6.bit._C15
#define OCCP6_C14 occp6.bit._C14
#define OCCP6_C13 occp6.bit._C13
#define OCCP6_C12 occp6.bit._C12
#define OCCP6_C11 occp6.bit._C11
#define OCCP6_C10 occp6.bit._C10
#define OCCP6_C09 occp6.bit._C09
#define OCCP6_C08 occp6.bit._C08
#define OCCP6_C07 occp6.bit._C07
#define OCCP6_C06 occp6.bit._C06
#define OCCP6_C05 occp6.bit._C05
#define OCCP6_C04 occp6.bit._C04
#define OCCP6_C03 occp6.bit._C03
#define OCCP6_C02 occp6.bit._C02
#define OCCP6_C01 occp6.bit._C01
#define OCCP6_C00 occp6.bit._C00
__IO_EXTERN OCS67STR ocs67;  
#define OCS67 ocs67.word
#define OCS67_CMOD ocs67.bit._CMOD
#define OCS67_OTD7 ocs67.bit._OTD7
#define OCS67_OTD6 ocs67.bit._OTD6
#define OCS67_ICP7 ocs67.bit._ICP7
#define OCS67_ICP6 ocs67.bit._ICP6
#define OCS67_ICE7 ocs67.bit._ICE7
#define OCS67_ICE6 ocs67.bit._ICE6
#define OCS67_CST7 ocs67.bit._CST7
#define OCS67_CST6 ocs67.bit._CST6
__IO_EXTERN OCS45STR ocs45;  
#define OCS45 ocs45.word
#define OCS45_CMOD ocs45.bit._CMOD
#define OCS45_OTD5 ocs45.bit._OTD5
#define OCS45_OTD4 ocs45.bit._OTD4
#define OCS45_ICP5 ocs45.bit._ICP5
#define OCS45_ICP4 ocs45.bit._ICP4
#define OCS45_ICE5 ocs45.bit._ICE5
#define OCS45_ICE4 ocs45.bit._ICE4
#define OCS45_CST5 ocs45.bit._CST5
#define OCS45_CST4 ocs45.bit._CST4
__IO_EXTERN EIRR2STR eirr2;   /* External Interrupt 16-23 */
#define EIRR2 eirr2.byte
#define EIRR2_ER7 eirr2.bit._ER7
#define EIRR2_ER6 eirr2.bit._ER6
#define EIRR2_ER5 eirr2.bit._ER5
#define EIRR2_ER4 eirr2.bit._ER4
#define EIRR2_ER3 eirr2.bit._ER3
#define EIRR2_ER2 eirr2.bit._ER2
#define EIRR2_ER1 eirr2.bit._ER1
#define EIRR2_ER0 eirr2.bit._ER0
__IO_EXTERN ENIR2STR enir2;  
#define ENIR2 enir2.byte
#define ENIR2_EN7 enir2.bit._EN7
#define ENIR2_EN6 enir2.bit._EN6
#define ENIR2_EN5 enir2.bit._EN5
#define ENIR2_EN4 enir2.bit._EN4
#define ENIR2_EN3 enir2.bit._EN3
#define ENIR2_EN2 enir2.bit._EN2
#define ENIR2_EN1 enir2.bit._EN1
#define ENIR2_EN0 enir2.bit._EN0
__IO_EXTERN ELVR2STR elvr2;  
#define ELVR2 elvr2.word
#define ELVR2_LB7 elvr2.bit._LB7
#define ELVR2_LA7 elvr2.bit._LA7
#define ELVR2_LB6 elvr2.bit._LB6
#define ELVR2_LA6 elvr2.bit._LA6
#define ELVR2_LB5 elvr2.bit._LB5
#define ELVR2_LA5 elvr2.bit._LA5
#define ELVR2_LB4 elvr2.bit._LB4
#define ELVR2_LA4 elvr2.bit._LA4
#define ELVR2_LB3 elvr2.bit._LB3
#define ELVR2_LA3 elvr2.bit._LA3
#define ELVR2_LB2 elvr2.bit._LB2
#define ELVR2_LA2 elvr2.bit._LA2
#define ELVR2_LB1 elvr2.bit._LB1
#define ELVR2_LA1 elvr2.bit._LA1
#define ELVR2_LB0 elvr2.bit._LB0
#define ELVR2_LA0 elvr2.bit._LA0
__IO_EXTERN EIRR3STR eirr3;   /* External Interrupt 24-31 */
#define EIRR3 eirr3.byte
#define EIRR3_ER7 eirr3.bit._ER7
#define EIRR3_ER6 eirr3.bit._ER6
#define EIRR3_ER5 eirr3.bit._ER5
#define EIRR3_ER4 eirr3.bit._ER4
#define EIRR3_ER3 eirr3.bit._ER3
#define EIRR3_ER2 eirr3.bit._ER2
#define EIRR3_ER1 eirr3.bit._ER1
#define EIRR3_ER0 eirr3.bit._ER0
__IO_EXTERN ENIR3STR enir3;  
#define ENIR3 enir3.byte
#define ENIR3_EN7 enir3.bit._EN7
#define ENIR3_EN6 enir3.bit._EN6
#define ENIR3_EN5 enir3.bit._EN5
#define ENIR3_EN4 enir3.bit._EN4
#define ENIR3_EN3 enir3.bit._EN3
#define ENIR3_EN2 enir3.bit._EN2
#define ENIR3_EN1 enir3.bit._EN1
#define ENIR3_EN0 enir3.bit._EN0
__IO_EXTERN ELVR3STR elvr3;  
#define ELVR3 elvr3.word
#define ELVR3_LB7 elvr3.bit._LB7
#define ELVR3_LA7 elvr3.bit._LA7
#define ELVR3_LB6 elvr3.bit._LB6
#define ELVR3_LA6 elvr3.bit._LA6
#define ELVR3_LB5 elvr3.bit._LB5
#define ELVR3_LA5 elvr3.bit._LA5
#define ELVR3_LB4 elvr3.bit._LB4
#define ELVR3_LA4 elvr3.bit._LA4
#define ELVR3_LB3 elvr3.bit._LB3
#define ELVR3_LA3 elvr3.bit._LA3
#define ELVR3_LB2 elvr3.bit._LB2
#define ELVR3_LA2 elvr3.bit._LA2
#define ELVR3_LB1 elvr3.bit._LB1
#define ELVR3_LA1 elvr3.bit._LA1
#define ELVR3_LB0 elvr3.bit._LB0
#define ELVR3_LA0 elvr3.bit._LA0
__IO_EXTERN EIRR4STR eirr4;   /* External Interrupt 32-39 */
#define EIRR4 eirr4.byte
#define EIRR4_ER7 eirr4.bit._ER7
#define EIRR4_ER6 eirr4.bit._ER6
#define EIRR4_ER5 eirr4.bit._ER5
#define EIRR4_ER4 eirr4.bit._ER4
#define EIRR4_ER3 eirr4.bit._ER3
#define EIRR4_ER2 eirr4.bit._ER2
#define EIRR4_ER1 eirr4.bit._ER1
#define EIRR4_ER0 eirr4.bit._ER0
__IO_EXTERN ENIR4STR enir4;  
#define ENIR4 enir4.byte
#define ENIR4_EN7 enir4.bit._EN7
#define ENIR4_EN6 enir4.bit._EN6
#define ENIR4_EN5 enir4.bit._EN5
#define ENIR4_EN4 enir4.bit._EN4
#define ENIR4_EN3 enir4.bit._EN3
#define ENIR4_EN2 enir4.bit._EN2
#define ENIR4_EN1 enir4.bit._EN1
#define ENIR4_EN0 enir4.bit._EN0
__IO_EXTERN ELVR4STR elvr4;  
#define ELVR4 elvr4.word
#define ELVR4_LB7 elvr4.bit._LB7
#define ELVR4_LA7 elvr4.bit._LA7
#define ELVR4_LB6 elvr4.bit._LB6
#define ELVR4_LA6 elvr4.bit._LA6
#define ELVR4_LB5 elvr4.bit._LB5
#define ELVR4_LA5 elvr4.bit._LA5
#define ELVR4_LB4 elvr4.bit._LB4
#define ELVR4_LA4 elvr4.bit._LA4
#define ELVR4_LB3 elvr4.bit._LB3
#define ELVR4_LA3 elvr4.bit._LA3
#define ELVR4_LB2 elvr4.bit._LB2
#define ELVR4_LA2 elvr4.bit._LA2
#define ELVR4_LB1 elvr4.bit._LB1
#define ELVR4_LA1 elvr4.bit._LA1
#define ELVR4_LB0 elvr4.bit._LB0
#define ELVR4_LA0 elvr4.bit._LA0
__IO_EXTERN DACRSTR dacr;   /* DAC */
#define DACR dacr.byte
#define DACR_MODE dacr.bit._MODE
#define DACR_DAE1 dacr.bit._DAE1
#define DACR_DAE0 dacr.bit._DAE0
#define DACR_DAE dacr.bitc._DAE
__IO_EXTERN DADR0STR dadr0;  
#define DADR0 dadr0.word
#define DADR0_DA09 dadr0.bit._DA09
#define DADR0_DA08 dadr0.bit._DA08
#define DADR0_DA07 dadr0.bit._DA07
#define DADR0_DA06 dadr0.bit._DA06
#define DADR0_DA05 dadr0.bit._DA05
#define DADR0_DA04 dadr0.bit._DA04
#define DADR0_DA03 dadr0.bit._DA03
#define DADR0_DA02 dadr0.bit._DA02
#define DADR0_DA01 dadr0.bit._DA01
#define DADR0_DA00 dadr0.bit._DA00
__IO_EXTERN DADR1STR dadr1;  
#define DADR1 dadr1.word
#define DADR1_DA19 dadr1.bit._DA19
#define DADR1_DA18 dadr1.bit._DA18
#define DADR1_DA17 dadr1.bit._DA17
#define DADR1_DA16 dadr1.bit._DA16
#define DADR1_DA15 dadr1.bit._DA15
#define DADR1_DA14 dadr1.bit._DA14
#define DADR1_DA13 dadr1.bit._DA13
#define DADR1_DA12 dadr1.bit._DA12
#define DADR1_DA11 dadr1.bit._DA11
#define DADR1_DA10 dadr1.bit._DA10
__IO_EXTERN DADBLSTR dadbl;  
#define DADBL dadbl.byte
#define DADBL_DBL dadbl.bit._DBL
__IO_EXTERN WTDBLSTR wtdbl;   /* Real Time Clock (Watch Timer) */
#define WTDBL wtdbl.byte
#define WTDBL_WTCK wtdbl.bit._WTCK
#define WTDBL_DBL wtdbl.bit._DBL
__IO_EXTERN WTCRSTR wtcr;  
#define WTCR wtcr.word
#define WTCR_INTE3 wtcr.bit._INTE3
#define WTCR_INT3 wtcr.bit._INT3
#define WTCR_INTE2 wtcr.bit._INTE2
#define WTCR_INT2 wtcr.bit._INT2
#define WTCR_INTE1 wtcr.bit._INTE1
#define WTCR_INT1 wtcr.bit._INT1
#define WTCR_INTE0 wtcr.bit._INTE0
#define WTCR_INT0 wtcr.bit._INT0
#define WTCR_TST2 wtcr.bit._TST2
#define WTCR_TST1 wtcr.bit._TST1
#define WTCR_TST0 wtcr.bit._TST0
#define WTCR_RUN wtcr.bit._RUN
#define WTCR_UPDT wtcr.bit._UPDT
#define WTCR_ST wtcr.bit._ST
__IO_EXTERN WTBRSTR wtbr;  
#define WTBR wtbr.lword
#define WTBR_D20 wtbr.bit._D20
#define WTBR_D19 wtbr.bit._D19
#define WTBR_D18 wtbr.bit._D18
#define WTBR_D17 wtbr.bit._D17
#define WTBR_D16 wtbr.bit._D16
#define WTBR_D15 wtbr.bit._D15
#define WTBR_D14 wtbr.bit._D14
#define WTBR_D13 wtbr.bit._D13
#define WTBR_D12 wtbr.bit._D12
#define WTBR_D11 wtbr.bit._D11
#define WTBR_D10 wtbr.bit._D10
#define WTBR_D9 wtbr.bit._D9
#define WTBR_D8 wtbr.bit._D8
#define WTBR_D7 wtbr.bit._D7
#define WTBR_D6 wtbr.bit._D6
#define WTBR_D5 wtbr.bit._D5
#define WTBR_D4 wtbr.bit._D4
#define WTBR_D3 wtbr.bit._D3
#define WTBR_D2 wtbr.bit._D2
#define WTBR_D1 wtbr.bit._D1
#define WTBR_D0 wtbr.bit._D0
__IO_EXTERN WTHRSTR wthr;  
#define WTHR wthr.byte
#define WTHR_H4 wthr.bit._H4
#define WTHR_H3 wthr.bit._H3
#define WTHR_H2 wthr.bit._H2
#define WTHR_H1 wthr.bit._H1
#define WTHR_H0 wthr.bit._H0
__IO_EXTERN WTMRSTR wtmr;  
#define WTMR wtmr.byte
#define WTMR_M5 wtmr.bit._M5
#define WTMR_M4 wtmr.bit._M4
#define WTMR_M3 wtmr.bit._M3
#define WTMR_M2 wtmr.bit._M2
#define WTMR_M1 wtmr.bit._M1
#define WTMR_M0 wtmr.bit._M0
__IO_EXTERN WTSRSTR wtsr;  
#define WTSR wtsr.byte
#define WTSR_S5 wtsr.bit._S5
#define WTSR_S4 wtsr.bit._S4
#define WTSR_S3 wtsr.bit._S3
#define WTSR_S2 wtsr.bit._S2
#define WTSR_S1 wtsr.bit._S1
#define WTSR_S0 wtsr.bit._S0
__IO_EXTERN ADERHSTR aderh;   /* ADC */
#define ADERH aderh.word
#define ADERH_ADE31 aderh.bit._ADE31
#define ADERH_ADE30 aderh.bit._ADE30
#define ADERH_ADE29 aderh.bit._ADE29
#define ADERH_ADE28 aderh.bit._ADE28
#define ADERH_ADE27 aderh.bit._ADE27
#define ADERH_ADE26 aderh.bit._ADE26
#define ADERH_ADE25 aderh.bit._ADE25
#define ADERH_ADE24 aderh.bit._ADE24
#define ADERH_ADE23 aderh.bit._ADE23
#define ADERH_ADE22 aderh.bit._ADE22
#define ADERH_ADE21 aderh.bit._ADE21
#define ADERH_ADE20 aderh.bit._ADE20
#define ADERH_ADE19 aderh.bit._ADE19
#define ADERH_ADE18 aderh.bit._ADE18
#define ADERH_ADE17 aderh.bit._ADE17
#define ADERH_ADE16 aderh.bit._ADE16
__IO_EXTERN ADERLSTR aderl;  
#define ADERL aderl.word
#define ADERL_ADE15 aderl.bit._ADE15
#define ADERL_ADE14 aderl.bit._ADE14
#define ADERL_ADE13 aderl.bit._ADE13
#define ADERL_ADE12 aderl.bit._ADE12
#define ADERL_ADE11 aderl.bit._ADE11
#define ADERL_ADE10 aderl.bit._ADE10
#define ADERL_ADE9 aderl.bit._ADE9
#define ADERL_ADE8 aderl.bit._ADE8
#define ADERL_ADE7 aderl.bit._ADE7
#define ADERL_ADE6 aderl.bit._ADE6
#define ADERL_ADE5 aderl.bit._ADE5
#define ADERL_ADE4 aderl.bit._ADE4
#define ADERL_ADE3 aderl.bit._ADE3
#define ADERL_ADE2 aderl.bit._ADE2
#define ADERL_ADE1 aderl.bit._ADE1
#define ADERL_ADE0 aderl.bit._ADE0
__IO_EXTERN ADCS1STR adcs1;  
#define ADCS1 adcs1.byte
#define ADCS1_BUSY adcs1.bit._BUSY
#define ADCS1_INT adcs1.bit._INT
#define ADCS1_INTE adcs1.bit._INTE
#define ADCS1_PAUS adcs1.bit._PAUS
#define ADCS1_STS1 adcs1.bit._STS1
#define ADCS1_STS0 adcs1.bit._STS0
#define ADCS1_STRT adcs1.bit._STRT
#define ADCS1_STS adcs1.bitc._STS
__IO_EXTERN ADCS0STR adcs0;  
#define ADCS0 adcs0.byte
#define ADCS0_MD1 adcs0.bit._MD1
#define ADCS0_MD0 adcs0.bit._MD0
#define ADCS0_S10 adcs0.bit._S10
#define ADCS0_ACH4 adcs0.bit._ACH4
#define ADCS0_ACH3 adcs0.bit._ACH3
#define ADCS0_ACH2 adcs0.bit._ACH2
#define ADCS0_ACH1 adcs0.bit._ACH1
#define ADCS0_ACH0 adcs0.bit._ACH0
#define ADCS0_MD adcs0.bitc._MD
#define ADCS0_ACH adcs0.bitc._ACH
__IO_EXTERN ADCR1STR adcr1;  
#define ADCR1 adcr1.byte
#define ADCR1_D9 adcr1.bit._D9
#define ADCR1_D8 adcr1.bit._D8
__IO_EXTERN ADCR0STR adcr0;  
#define ADCR0 adcr0.byte
#define ADCR0_D7 adcr0.bit._D7
#define ADCR0_D6 adcr0.bit._D6
#define ADCR0_D5 adcr0.bit._D5
#define ADCR0_D4 adcr0.bit._D4
#define ADCR0_D3 adcr0.bit._D3
#define ADCR0_D2 adcr0.bit._D2
#define ADCR0_D1 adcr0.bit._D1
#define ADCR0_D0 adcr0.bit._D0
__IO_EXTERN ADCT1STR adct1;  
#define ADCT1 adct1.byte
#define ADCT1_CT5 adct1.bit._CT5
#define ADCT1_CT4 adct1.bit._CT4
#define ADCT1_CT3 adct1.bit._CT3
#define ADCT1_CT2 adct1.bit._CT2
#define ADCT1_CT1 adct1.bit._CT1
#define ADCT1_CT0 adct1.bit._CT0
#define ADCT1_ST9 adct1.bit._ST9
#define ADCT1_ST8 adct1.bit._ST8
__IO_EXTERN ADCT0STR adct0;  
#define ADCT0 adct0.byte
#define ADCT0_ST7 adct0.bit._ST7
#define ADCT0_ST6 adct0.bit._ST6
#define ADCT0_ST5 adct0.bit._ST5
#define ADCT0_ST4 adct0.bit._ST4
#define ADCT0_ST3 adct0.bit._ST3
#define ADCT0_ST2 adct0.bit._ST2
#define ADCT0_ST1 adct0.bit._ST1
#define ADCT0_ST0 adct0.bit._ST0
__IO_EXTERN ADSCHSTR adsch;  
#define ADSCH adsch.byte
#define ADSCH_ANS4 adsch.bit._ANS4
#define ADSCH_ANS3 adsch.bit._ANS3
#define ADSCH_ANS2 adsch.bit._ANS2
#define ADSCH_ANS1 adsch.bit._ANS1
#define ADSCH_ASN0 adsch.bit._ASN0
#define ADSCH_ANS adsch.bitc._ANS
__IO_EXTERN ADECHSTR adech;  
#define ADECH adech.byte
#define ADECH_ANE4 adech.bit._ANE4
#define ADECH_ANE3 adech.bit._ANE3
#define ADECH_ANE2 adech.bit._ANE2
#define ADECH_ANE1 adech.bit._ANE1
#define ADECH_ANE0 adech.bit._ANE0
#define ADECH_ANE adech.bitc._ANE
__IO_EXTERN CUCRSTR cucr;   /* Clock Calibration */
#define CUCR cucr.word
#define CUCR_STRT cucr.bit._STRT
#define CUCR_INT cucr.bit._INT
#define CUCR_INTEN cucr.bit._INTEN
__IO_EXTERN CUTDSTR cutd;  
#define CUTD cutd.word
#define CUTD_TDD15 cutd.bit._TDD15
#define CUTD_TDD14 cutd.bit._TDD14
#define CUTD_TDD13 cutd.bit._TDD13
#define CUTD_TDD12 cutd.bit._TDD12
#define CUTD_TDD11 cutd.bit._TDD11
#define CUTD_TDD10 cutd.bit._TDD10
#define CUTD_TDD9 cutd.bit._TDD9
#define CUTD_TDD8 cutd.bit._TDD8
#define CUTD_TDD7 cutd.bit._TDD7
#define CUTD_TDD6 cutd.bit._TDD6
#define CUTD_TDD5 cutd.bit._TDD5
#define CUTD_TDD4 cutd.bit._TDD4
#define CUTD_TDD3 cutd.bit._TDD3
#define CUTD_TDD2 cutd.bit._TDD2
#define CUTD_TDD1 cutd.bit._TDD1
#define CUTD_TDD0 cutd.bit._TDD0
__IO_EXTERN CUTR1STR cutr1;  
#define CUTR1 cutr1.word
#define CUTR1_TR23 cutr1.bit._TR23
#define CUTR1_TR22 cutr1.bit._TR22
#define CUTR1_TR21 cutr1.bit._TR21
#define CUTR1_TR20 cutr1.bit._TR20
#define CUTR1_TR19 cutr1.bit._TR19
#define CUTR1_TR18 cutr1.bit._TR18
#define CUTR1_TR17 cutr1.bit._TR17
#define CUTR1_TR16 cutr1.bit._TR16
__IO_EXTERN CUTR2STR cutr2;  
#define CUTR2 cutr2.word
#define CUTR2_TR15 cutr2.bit._TR15
#define CUTR2_TR14 cutr2.bit._TR14
#define CUTR2_TR13 cutr2.bit._TR13
#define CUTR2_TR12 cutr2.bit._TR12
#define CUTR2_TR11 cutr2.bit._TR11
#define CUTR2_TR10 cutr2.bit._TR10
#define CUTR2_TR9 cutr2.bit._TR9
#define CUTR2_TR8 cutr2.bit._TR8
#define CUTR2_TR7 cutr2.bit._TR7
#define CUTR2_TR6 cutr2.bit._TR6
#define CUTR2_TR5 cutr2.bit._TR5
#define CUTR2_TR4 cutr2.bit._TR4
#define CUTR2_TR3 cutr2.bit._TR3
#define CUTR2_TR2 cutr2.bit._TR2
#define CUTR2_TR1 cutr2.bit._TR1
#define CUTR2_TR0 cutr2.bit._TR0
__IO_EXTERN IO_BYTE udrc1;   /* Up/Down Counter 0-1 */
#define UDRC1 udrc1
__IO_EXTERN IO_BYTE udrc0;  
#define UDRC0 udrc0
__IO_EXTERN IO_BYTE udcr1;  
#define UDCR1 udcr1
__IO_EXTERN IO_BYTE udcr0;  
#define UDCR0 udcr0
__IO_EXTERN UDCCH0STR udcch0;  
#define UDCCH0 udcch0.byte
#define UDCCH0_M16E udcch0.bit._M16E
#define UDCCH0_CDCF udcch0.bit._CDCF
#define UDCCH0_CFIE udcch0.bit._CFIE
#define UDCCH0_CLKS udcch0.bit._CLKS
#define UDCCH0_CMS1 udcch0.bit._CMS1
#define UDCCH0_CMS0 udcch0.bit._CMS0
#define UDCCH0_CES1 udcch0.bit._CES1
#define UDCCH0_CES0 udcch0.bit._CES0
#define UDCCH0_CMS udcch0.bitc._CMS
#define UDCCH0_CES udcch0.bitc._CES
__IO_EXTERN UDCCL0STR udccl0;  
#define UDCCL0 udccl0.byte
#define UDCCL0_CTUT udccl0.bit._CTUT
#define UDCCL0_UCRE udccl0.bit._UCRE
#define UDCCL0_RLDE udccl0.bit._RLDE
#define UDCCL0_UDCC udccl0.bit._UDCC
#define UDCCL0_CGSC udccl0.bit._CGSC
#define UDCCL0_CGE1 udccl0.bit._CGE1
#define UDCCL0_CGE0 udccl0.bit._CGE0
#define UDCCL0_CGE udccl0.bitc._CGE
__IO_EXTERN UDCS0STR udcs0;  
#define UDCS0 udcs0.byte
#define UDCS0_CSTR udcs0.bit._CSTR
#define UDCS0_CITE udcs0.bit._CITE
#define UDCS0_UDIE udcs0.bit._UDIE
#define UDCS0_CMPF udcs0.bit._CMPF
#define UDCS0_OVFF udcs0.bit._OVFF
#define UDCS0_UDFF udcs0.bit._UDFF
#define UDCS0_UDF1 udcs0.bit._UDF1
#define UDCS0_UDF0 udcs0.bit._UDF0
#define UDCS0_UDF udcs0.bitc._UDF
__IO_EXTERN UDCCH1STR udcch1;  
#define UDCCH1 udcch1.byte
#define UDCCH1_M16E udcch1.bit._M16E
#define UDCCH1_CDCF udcch1.bit._CDCF
#define UDCCH1_CFIE udcch1.bit._CFIE
#define UDCCH1_CLKS udcch1.bit._CLKS
#define UDCCH1_CMS1 udcch1.bit._CMS1
#define UDCCH1_CMS0 udcch1.bit._CMS0
#define UDCCH1_CES1 udcch1.bit._CES1
#define UDCCH1_CES0 udcch1.bit._CES0
#define UDCCH1_CMS udcch1.bitc._CMS
#define UDCCH1_CES udcch1.bitc._CES
__IO_EXTERN UDCCL1STR udccl1;  
#define UDCCL1 udccl1.byte
#define UDCCL1_CTUT udccl1.bit._CTUT
#define UDCCL1_UCRE udccl1.bit._UCRE
#define UDCCL1_RLDE udccl1.bit._RLDE
#define UDCCL1_UDCC udccl1.bit._UDCC
#define UDCCL1_CGSC udccl1.bit._CGSC
#define UDCCL1_CGE1 udccl1.bit._CGE1
#define UDCCL1_CGE0 udccl1.bit._CGE0
#define UDCCL1_CGE udccl1.bitc._CGE
__IO_EXTERN UDCS1STR udcs1;  
#define UDCS1 udcs1.byte
#define UDCS1_CSTR udcs1.bit._CSTR
#define UDCS1_CITE udcs1.bit._CITE
#define UDCS1_UDIE udcs1.bit._UDIE
#define UDCS1_CMPF udcs1.bit._CMPF
#define UDCS1_OVFF udcs1.bit._OVFF
#define UDCS1_UDFF udcs1.bit._UDFF
#define UDCS1_UDF1 udcs1.bit._UDF1
#define UDCS1_UDF0 udcs1.bit._UDF0
#define UDCS1_UDF udcs1.bitc._UDF
__IO_EXTERN IO_BYTE udrc3;   /* Up/Down Counter 2-3 */
#define UDRC3 udrc3
__IO_EXTERN IO_BYTE udrc2;  
#define UDRC2 udrc2
__IO_EXTERN IO_BYTE udcr3;  
#define UDCR3 udcr3
__IO_EXTERN IO_BYTE udcr2;  
#define UDCR2 udcr2
__IO_EXTERN UDCCH2STR udcch2;  
#define UDCCH2 udcch2.byte
#define UDCCH2_M16E udcch2.bit._M16E
#define UDCCH2_CDCF udcch2.bit._CDCF
#define UDCCH2_CFIE udcch2.bit._CFIE
#define UDCCH2_CLKS udcch2.bit._CLKS
#define UDCCH2_CMS1 udcch2.bit._CMS1
#define UDCCH2_CMS0 udcch2.bit._CMS0
#define UDCCH2_CES1 udcch2.bit._CES1
#define UDCCH2_CES0 udcch2.bit._CES0
#define UDCCH2_CMS udcch2.bitc._CMS
#define UDCCH2_CES udcch2.bitc._CES
__IO_EXTERN UDCCL2STR udccl2;  
#define UDCCL2 udccl2.byte
#define UDCCL2_CTUT udccl2.bit._CTUT
#define UDCCL2_UCRE udccl2.bit._UCRE
#define UDCCL2_RLDE udccl2.bit._RLDE
#define UDCCL2_UDCC udccl2.bit._UDCC
#define UDCCL2_CGSC udccl2.bit._CGSC
#define UDCCL2_CGE1 udccl2.bit._CGE1
#define UDCCL2_CGE0 udccl2.bit._CGE0
#define UDCCL2_CGE udccl2.bitc._CGE
__IO_EXTERN UDCS2STR udcs2;  
#define UDCS2 udcs2.byte
#define UDCS2_CSTR udcs2.bit._CSTR
#define UDCS2_CITE udcs2.bit._CITE
#define UDCS2_UDIE udcs2.bit._UDIE
#define UDCS2_CMPF udcs2.bit._CMPF
#define UDCS2_OVFF udcs2.bit._OVFF
#define UDCS2_UDFF udcs2.bit._UDFF
#define UDCS2_UDF1 udcs2.bit._UDF1
#define UDCS2_UDF0 udcs2.bit._UDF0
#define UDCS2_UDF udcs2.bitc._UDF
__IO_EXTERN UDCCH3STR udcch3;  
#define UDCCH3 udcch3.byte
#define UDCCH3_M16E udcch3.bit._M16E
#define UDCCH3_CDCF udcch3.bit._CDCF
#define UDCCH3_CFIE udcch3.bit._CFIE
#define UDCCH3_CLKS udcch3.bit._CLKS
#define UDCCH3_CMS1 udcch3.bit._CMS1
#define UDCCH3_CMS0 udcch3.bit._CMS0
#define UDCCH3_CES1 udcch3.bit._CES1
#define UDCCH3_CES0 udcch3.bit._CES0
#define UDCCH3_CMS udcch3.bitc._CMS
#define UDCCH3_CES udcch3.bitc._CES
__IO_EXTERN UDCCL3STR udccl3;  
#define UDCCL3 udccl3.byte
#define UDCCL3_CTUT udccl3.bit._CTUT
#define UDCCL3_UCRE udccl3.bit._UCRE
#define UDCCL3_RLDE udccl3.bit._RLDE
#define UDCCL3_UDCC udccl3.bit._UDCC
#define UDCCL3_CGSC udccl3.bit._CGSC
#define UDCCL3_CGE1 udccl3.bit._CGE1
#define UDCCL3_CGE0 udccl3.bit._CGE0
#define UDCCL3_CGE udccl3.bitc._CGE
__IO_EXTERN UDCS3STR udcs3;  
#define UDCS3 udcs3.byte
#define UDCS3_CSTR udcs3.bit._CSTR
#define UDCS3_CITE udcs3.bit._CITE
#define UDCS3_UDIE udcs3.bit._UDIE
#define UDCS3_CMPF udcs3.bit._CMPF
#define UDCS3_OVFF udcs3.bit._OVFF
#define UDCS3_UDFF udcs3.bit._UDFF
#define UDCS3_UDF1 udcs3.bit._UDF1
#define UDCS3_UDF0 udcs3.bit._UDF0
#define UDCS3_UDF udcs3.bitc._UDF
__IO_EXTERN AD2ERHSTR ad2erh;   /* ADC 2 */
#define AD2ERH ad2erh.word
#define AD2ERH_ADE31 ad2erh.bit._ADE31
#define AD2ERH_ADE30 ad2erh.bit._ADE30
#define AD2ERH_ADE29 ad2erh.bit._ADE29
#define AD2ERH_ADE28 ad2erh.bit._ADE28
#define AD2ERH_ADE27 ad2erh.bit._ADE27
#define AD2ERH_ADE26 ad2erh.bit._ADE26
#define AD2ERH_ADE25 ad2erh.bit._ADE25
#define AD2ERH_ADE24 ad2erh.bit._ADE24
#define AD2ERH_ADE23 ad2erh.bit._ADE23
#define AD2ERH_ADE22 ad2erh.bit._ADE22
#define AD2ERH_ADE21 ad2erh.bit._ADE21
#define AD2ERH_ADE20 ad2erh.bit._ADE20
#define AD2ERH_ADE19 ad2erh.bit._ADE19
#define AD2ERH_ADE18 ad2erh.bit._ADE18
#define AD2ERH_ADE17 ad2erh.bit._ADE17
#define AD2ERH_ADE16 ad2erh.bit._ADE16
__IO_EXTERN AD2ERLSTR ad2erl;  
#define AD2ERL ad2erl.word
#define AD2ERL_ADE15 ad2erl.bit._ADE15
#define AD2ERL_ADE14 ad2erl.bit._ADE14
#define AD2ERL_ADE13 ad2erl.bit._ADE13
#define AD2ERL_ADE12 ad2erl.bit._ADE12
#define AD2ERL_ADE11 ad2erl.bit._ADE11
#define AD2ERL_ADE10 ad2erl.bit._ADE10
#define AD2ERL_ADE9 ad2erl.bit._ADE9
#define AD2ERL_ADE8 ad2erl.bit._ADE8
#define AD2ERL_ADE7 ad2erl.bit._ADE7
#define AD2ERL_ADE6 ad2erl.bit._ADE6
#define AD2ERL_ADE5 ad2erl.bit._ADE5
#define AD2ERL_ADE4 ad2erl.bit._ADE4
#define AD2ERL_ADE3 ad2erl.bit._ADE3
#define AD2ERL_ADE2 ad2erl.bit._ADE2
#define AD2ERL_ADE1 ad2erl.bit._ADE1
#define AD2ERL_ADE0 ad2erl.bit._ADE0
__IO_EXTERN AD2CS1STR ad2cs1;  
#define AD2CS1 ad2cs1.byte
#define AD2CS1_BUSY ad2cs1.bit._BUSY
#define AD2CS1_INT ad2cs1.bit._INT
#define AD2CS1_INTE ad2cs1.bit._INTE
#define AD2CS1_PAUS ad2cs1.bit._PAUS
#define AD2CS1_STS1 ad2cs1.bit._STS1
#define AD2CS1_STS0 ad2cs1.bit._STS0
#define AD2CS1_STRT ad2cs1.bit._STRT
#define AD2CS1_STS ad2cs1.bitc._STS
__IO_EXTERN AD2CS0STR ad2cs0;  
#define AD2CS0 ad2cs0.byte
#define AD2CS0_MD1 ad2cs0.bit._MD1
#define AD2CS0_MD0 ad2cs0.bit._MD0
#define AD2CS0_S10 ad2cs0.bit._S10
#define AD2CS0_ACH4 ad2cs0.bit._ACH4
#define AD2CS0_ACH3 ad2cs0.bit._ACH3
#define AD2CS0_ACH2 ad2cs0.bit._ACH2
#define AD2CS0_ACH1 ad2cs0.bit._ACH1
#define AD2CS0_ACH0 ad2cs0.bit._ACH0
#define AD2CS0_MD ad2cs0.bitc._MD
#define AD2CS0_ACH ad2cs0.bitc._ACH
__IO_EXTERN AD2CR1STR ad2cr1;  
#define AD2CR1 ad2cr1.byte
#define AD2CR1_D9 ad2cr1.bit._D9
#define AD2CR1_D8 ad2cr1.bit._D8
__IO_EXTERN AD2CR0STR ad2cr0;  
#define AD2CR0 ad2cr0.byte
#define AD2CR0_D7 ad2cr0.bit._D7
#define AD2CR0_D6 ad2cr0.bit._D6
#define AD2CR0_D5 ad2cr0.bit._D5
#define AD2CR0_D4 ad2cr0.bit._D4
#define AD2CR0_D3 ad2cr0.bit._D3
#define AD2CR0_D2 ad2cr0.bit._D2
#define AD2CR0_D1 ad2cr0.bit._D1
#define AD2CR0_D0 ad2cr0.bit._D0
__IO_EXTERN AD2CT1STR ad2ct1;  
#define AD2CT1 ad2ct1.byte
#define AD2CT1_CT5 ad2ct1.bit._CT5
#define AD2CT1_CT4 ad2ct1.bit._CT4
#define AD2CT1_CT3 ad2ct1.bit._CT3
#define AD2CT1_CT2 ad2ct1.bit._CT2
#define AD2CT1_CT1 ad2ct1.bit._CT1
#define AD2CT1_CT0 ad2ct1.bit._CT0
#define AD2CT1_ST9 ad2ct1.bit._ST9
#define AD2CT1_ST8 ad2ct1.bit._ST8
__IO_EXTERN AD2CT0STR ad2ct0;  
#define AD2CT0 ad2ct0.byte
#define AD2CT0_ST7 ad2ct0.bit._ST7
#define AD2CT0_ST6 ad2ct0.bit._ST6
#define AD2CT0_ST5 ad2ct0.bit._ST5
#define AD2CT0_ST4 ad2ct0.bit._ST4
#define AD2CT0_ST3 ad2ct0.bit._ST3
#define AD2CT0_ST2 ad2ct0.bit._ST2
#define AD2CT0_ST1 ad2ct0.bit._ST1
#define AD2CT0_ST0 ad2ct0.bit._ST0
__IO_EXTERN AD2SCHSTR ad2sch;  
#define AD2SCH ad2sch.byte
#define AD2SCH_ANS4 ad2sch.bit._ANS4
#define AD2SCH_ANS3 ad2sch.bit._ANS3
#define AD2SCH_ANS2 ad2sch.bit._ANS2
#define AD2SCH_ANS1 ad2sch.bit._ANS1
#define AD2SCH_ASN0 ad2sch.bit._ASN0
#define AD2SCH_ANS ad2sch.bitc._ANS
__IO_EXTERN AD2ECHSTR ad2ech;  
#define AD2ECH ad2ech.byte
#define AD2ECH_ANE4 ad2ech.bit._ANE4
#define AD2ECH_ANE3 ad2ech.bit._ANE3
#define AD2ECH_ANE2 ad2ech.bit._ANE2
#define AD2ECH_ANE1 ad2ech.bit._ANE1
#define AD2ECH_ANE0 ad2ech.bit._ANE0
#define AD2ECH_ANE ad2ech.bitc._ANE
__IO_EXTERN CMPRSTR cmpr;   /* Clock Modulator */
#define CMPR cmpr.word
#define CMPR_MP13 cmpr.bit._MP13
#define CMPR_MP12 cmpr.bit._MP12
#define CMPR_MP11 cmpr.bit._MP11
#define CMPR_MP10 cmpr.bit._MP10
#define CMPR_MP9 cmpr.bit._MP9
#define CMPR_MP8 cmpr.bit._MP8
#define CMPR_MP7 cmpr.bit._MP7
#define CMPR_MP6 cmpr.bit._MP6
#define CMPR_MP5 cmpr.bit._MP5
#define CMPR_MP4 cmpr.bit._MP4
#define CMPR_MP3 cmpr.bit._MP3
#define CMPR_MP2 cmpr.bit._MP2
#define CMPR_MP1 cmpr.bit._MP1
#define CMPR_MP0 cmpr.bit._MP0
__IO_EXTERN CMCRSTR cmcr;  
#define CMCR cmcr.byte
#define CMCR_PHSEL cmcr.bit._PHSEL
#define CMCR_RUN cmcr.bit._RUN
#define CMCR_EN cmcr.bit._EN
#define CMCR_PDX cmcr.bit._PDX
__IO_EXTERN IO_WORD cmt1;  
#define CMT1 cmt1
__IO_EXTERN IO_WORD cmt2;  
#define CMT2 cmt2
__IO_EXTERN CANPRESTR canpre;   /* CAN clock control / Ext. Int. Source Sel. */
#define CANPRE canpre.byte
#define CANPRE_CANP3 canpre.bit._CANP3
#define CANPRE_CANP2 canpre.bit._CANP2
#define CANPRE_CANP1 canpre.bit._CANP1
#define CANPRE_CANP0 canpre.bit._CANP0
#define CANPRE_CANP canpre.bitc._CANP
__IO_EXTERN EISSRSTR eissr;  
#define EISSR eissr.word
#define EISSR_EISS15 eissr.bit._EISS15
#define EISSR_EISS14 eissr.bit._EISS14
#define EISSR_EISS13 eissr.bit._EISS13
#define EISSR_EISS12 eissr.bit._EISS12
#define EISSR_EISS11 eissr.bit._EISS11
#define EISSR_EISS10 eissr.bit._EISS10
#define EISSR_EISS9 eissr.bit._EISS9
#define EISSR_EISS8 eissr.bit._EISS8
#define EISSR_EISS7 eissr.bit._EISS7
#define EISSR_EISS6 eissr.bit._EISS6
#define EISSR_EISS5 eissr.bit._EISS5
#define EISSR_EISS4 eissr.bit._EISS4
#define EISSR_EISS3 eissr.bit._EISS3
#define EISSR_EISS2 eissr.bit._EISS2
#define EISSR_EISS1 eissr.bit._EISS1
#define EISSR_EISS0 eissr.bit._EISS0
__IO_EXTERN IO_BYTE prlh0;   /* PPG 0-3 */
#define PRLH0 prlh0
__IO_EXTERN IO_BYTE prll0;  
#define PRLL0 prll0
__IO_EXTERN IO_BYTE prlh1;  
#define PRLH1 prlh1
__IO_EXTERN IO_BYTE prll1;  
#define PRLL1 prll1
__IO_EXTERN IO_BYTE prlh2;  
#define PRLH2 prlh2
__IO_EXTERN IO_BYTE prll2;  
#define PRLL2 prll2
__IO_EXTERN IO_BYTE prlh3;  
#define PRLH3 prlh3
__IO_EXTERN IO_BYTE prll3;  
#define PRLL3 prll3
__IO_EXTERN PPGC0STR ppgc0;  
#define PPGC0 ppgc0.byte
#define PPGC0_PIE ppgc0.bit._PIE
#define PPGC0_PUF ppgc0.bit._PUF
#define PPGC0_INTM ppgc0.bit._INTM
#define PPGC0_PCS1 ppgc0.bit._PCS1
#define PPGC0_PCS0 ppgc0.bit._PCS0
#define PPGC0_MD1 ppgc0.bit._MD1
#define PPGC0_MD0 ppgc0.bit._MD0
#define PPGC0_PCS ppgc0.bitc._PCS
#define PPGC0_MD ppgc0.bitc._MD
__IO_EXTERN PPGC1STR ppgc1;  
#define PPGC1 ppgc1.byte
#define PPGC1_PIE ppgc1.bit._PIE
#define PPGC1_PUF ppgc1.bit._PUF
#define PPGC1_INTM ppgc1.bit._INTM
#define PPGC1_PCS1 ppgc1.bit._PCS1
#define PPGC1_PCS0 ppgc1.bit._PCS0
#define PPGC1_MD1 ppgc1.bit._MD1
#define PPGC1_MD0 ppgc1.bit._MD0
#define PPGC1_PCS ppgc1.bitc._PCS
#define PPGC1_MD ppgc1.bitc._MD
__IO_EXTERN PPGC2STR ppgc2;  
#define PPGC2 ppgc2.byte
#define PPGC2_PIE ppgc2.bit._PIE
#define PPGC2_PUF ppgc2.bit._PUF
#define PPGC2_INTM ppgc2.bit._INTM
#define PPGC2_PCS1 ppgc2.bit._PCS1
#define PPGC2_PCS0 ppgc2.bit._PCS0
#define PPGC2_MD1 ppgc2.bit._MD1
#define PPGC2_MD0 ppgc2.bit._MD0
#define PPGC2_PCS ppgc2.bitc._PCS
#define PPGC2_MD ppgc2.bitc._MD
__IO_EXTERN PPGC3STR ppgc3;  
#define PPGC3 ppgc3.byte
#define PPGC3_PIE ppgc3.bit._PIE
#define PPGC3_PUF ppgc3.bit._PUF
#define PPGC3_INTM ppgc3.bit._INTM
#define PPGC3_PCS1 ppgc3.bit._PCS1
#define PPGC3_PCS0 ppgc3.bit._PCS0
#define PPGC3_MD1 ppgc3.bit._MD1
#define PPGC3_MD0 ppgc3.bit._MD0
#define PPGC3_PCS ppgc3.bitc._PCS
#define PPGC3_MD ppgc3.bitc._MD
__IO_EXTERN IO_BYTE prlh4;   /* PPG 4-7 */
#define PRLH4 prlh4
__IO_EXTERN IO_BYTE prll4;  
#define PRLL4 prll4
__IO_EXTERN IO_BYTE prlh5;  
#define PRLH5 prlh5
__IO_EXTERN IO_BYTE prll5;  
#define PRLL5 prll5
__IO_EXTERN IO_BYTE prlh6;  
#define PRLH6 prlh6
__IO_EXTERN IO_BYTE prll6;  
#define PRLL6 prll6
__IO_EXTERN IO_BYTE prlh7;  
#define PRLH7 prlh7
__IO_EXTERN IO_BYTE prll7;  
#define PRLL7 prll7
__IO_EXTERN PPGC4STR ppgc4;  
#define PPGC4 ppgc4.byte
#define PPGC4_PIE ppgc4.bit._PIE
#define PPGC4_PUF ppgc4.bit._PUF
#define PPGC4_INTM ppgc4.bit._INTM
#define PPGC4_PCS1 ppgc4.bit._PCS1
#define PPGC4_PCS0 ppgc4.bit._PCS0
#define PPGC4_MD1 ppgc4.bit._MD1
#define PPGC4_MD0 ppgc4.bit._MD0
#define PPGC4_PCS ppgc4.bitc._PCS
#define PPGC4_MD ppgc4.bitc._MD
__IO_EXTERN PPGC5STR ppgc5;  
#define PPGC5 ppgc5.byte
#define PPGC5_PIE ppgc5.bit._PIE
#define PPGC5_PUF ppgc5.bit._PUF
#define PPGC5_INTM ppgc5.bit._INTM
#define PPGC5_PCS1 ppgc5.bit._PCS1
#define PPGC5_PCS0 ppgc5.bit._PCS0
#define PPGC5_MD1 ppgc5.bit._MD1
#define PPGC5_MD0 ppgc5.bit._MD0
#define PPGC5_PCS ppgc5.bitc._PCS
#define PPGC5_MD ppgc5.bitc._MD
__IO_EXTERN PPGC6STR ppgc6;  
#define PPGC6 ppgc6.byte
#define PPGC6_PIE ppgc6.bit._PIE
#define PPGC6_PUF ppgc6.bit._PUF
#define PPGC6_INTM ppgc6.bit._INTM
#define PPGC6_PCS1 ppgc6.bit._PCS1
#define PPGC6_PCS0 ppgc6.bit._PCS0
#define PPGC6_MD1 ppgc6.bit._MD1
#define PPGC6_MD0 ppgc6.bit._MD0
#define PPGC6_PCS ppgc6.bitc._PCS
#define PPGC6_MD ppgc6.bitc._MD
__IO_EXTERN PPGC7STR ppgc7;  
#define PPGC7 ppgc7.byte
#define PPGC7_PIE ppgc7.bit._PIE
#define PPGC7_PUF ppgc7.bit._PUF
#define PPGC7_INTM ppgc7.bit._INTM
#define PPGC7_PCS1 ppgc7.bit._PCS1
#define PPGC7_PCS0 ppgc7.bit._PCS0
#define PPGC7_MD1 ppgc7.bit._MD1
#define PPGC7_MD0 ppgc7.bit._MD0
#define PPGC7_PCS ppgc7.bitc._PCS
#define PPGC7_MD ppgc7.bitc._MD
__IO_EXTERN IO_BYTE prlh8;   /* PPG 8-B */
#define PRLH8 prlh8
__IO_EXTERN IO_BYTE prll8;  
#define PRLL8 prll8
__IO_EXTERN IO_BYTE prlh9;  
#define PRLH9 prlh9
__IO_EXTERN IO_BYTE prll9;  
#define PRLL9 prll9
__IO_EXTERN IO_BYTE prlha;  
#define PRLHA prlha
__IO_EXTERN IO_BYTE prlla;  
#define PRLLA prlla
__IO_EXTERN IO_BYTE prlhb;  
#define PRLHB prlhb
__IO_EXTERN IO_BYTE prllb;  
#define PRLLB prllb
__IO_EXTERN PPGC8STR ppgc8;  
#define PPGC8 ppgc8.byte
#define PPGC8_PIE ppgc8.bit._PIE
#define PPGC8_PUF ppgc8.bit._PUF
#define PPGC8_INTM ppgc8.bit._INTM
#define PPGC8_PCS1 ppgc8.bit._PCS1
#define PPGC8_PCS0 ppgc8.bit._PCS0
#define PPGC8_MD1 ppgc8.bit._MD1
#define PPGC8_MD0 ppgc8.bit._MD0
#define PPGC8_PCS ppgc8.bitc._PCS
#define PPGC8_MD ppgc8.bitc._MD
__IO_EXTERN PPGC9STR ppgc9;  
#define PPGC9 ppgc9.byte
#define PPGC9_PIE ppgc9.bit._PIE
#define PPGC9_PUF ppgc9.bit._PUF
#define PPGC9_INTM ppgc9.bit._INTM
#define PPGC9_PCS1 ppgc9.bit._PCS1
#define PPGC9_PCS0 ppgc9.bit._PCS0
#define PPGC9_MD1 ppgc9.bit._MD1
#define PPGC9_MD0 ppgc9.bit._MD0
#define PPGC9_PCS ppgc9.bitc._PCS
#define PPGC9_MD ppgc9.bitc._MD
__IO_EXTERN PPGCASTR ppgca;  
#define PPGCA ppgca.byte
#define PPGCA_PIE ppgca.bit._PIE
#define PPGCA_PUF ppgca.bit._PUF
#define PPGCA_INTM ppgca.bit._INTM
#define PPGCA_PCS1 ppgca.bit._PCS1
#define PPGCA_PCS0 ppgca.bit._PCS0
#define PPGCA_MD1 ppgca.bit._MD1
#define PPGCA_MD0 ppgca.bit._MD0
#define PPGCA_PCS ppgca.bitc._PCS
#define PPGCA_MD ppgca.bitc._MD
__IO_EXTERN PPGCBSTR ppgcb;  
#define PPGCB ppgcb.byte
#define PPGCB_PIE ppgcb.bit._PIE
#define PPGCB_PUF ppgcb.bit._PUF
#define PPGCB_INTM ppgcb.bit._INTM
#define PPGCB_PCS1 ppgcb.bit._PCS1
#define PPGCB_PCS0 ppgcb.bit._PCS0
#define PPGCB_MD1 ppgcb.bit._MD1
#define PPGCB_MD0 ppgcb.bit._MD0
#define PPGCB_PCS ppgcb.bitc._PCS
#define PPGCB_MD ppgcb.bitc._MD
__IO_EXTERN IO_BYTE prlhc;   /* PPG C-F */
#define PRLHC prlhc
__IO_EXTERN IO_BYTE prllc;  
#define PRLLC prllc
__IO_EXTERN IO_BYTE prlhd;  
#define PRLHD prlhd
__IO_EXTERN IO_BYTE prlld;  
#define PRLLD prlld
__IO_EXTERN IO_BYTE prlhe;  
#define PRLHE prlhe
__IO_EXTERN IO_BYTE prlle;  
#define PRLLE prlle
__IO_EXTERN IO_BYTE prlhf;  
#define PRLHF prlhf
__IO_EXTERN IO_BYTE prllf;  
#define PRLLF prllf
__IO_EXTERN PPGCCSTR ppgcc;  
#define PPGCC ppgcc.byte
#define PPGCC_PIE ppgcc.bit._PIE
#define PPGCC_PUF ppgcc.bit._PUF
#define PPGCC_INTM ppgcc.bit._INTM
#define PPGCC_PCS1 ppgcc.bit._PCS1
#define PPGCC_PCS0 ppgcc.bit._PCS0
#define PPGCC_MD1 ppgcc.bit._MD1
#define PPGCC_MD0 ppgcc.bit._MD0
#define PPGCC_PCS ppgcc.bitc._PCS
#define PPGCC_MD ppgcc.bitc._MD
__IO_EXTERN PPGCDSTR ppgcd;  
#define PPGCD ppgcd.byte
#define PPGCD_PIE ppgcd.bit._PIE
#define PPGCD_PUF ppgcd.bit._PUF
#define PPGCD_INTM ppgcd.bit._INTM
#define PPGCD_PCS1 ppgcd.bit._PCS1
#define PPGCD_PCS0 ppgcd.bit._PCS0
#define PPGCD_MD1 ppgcd.bit._MD1
#define PPGCD_MD0 ppgcd.bit._MD0
#define PPGCD_PCS ppgcd.bitc._PCS
#define PPGCD_MD ppgcd.bitc._MD
__IO_EXTERN PPGCESTR ppgce;  
#define PPGCE ppgce.byte
#define PPGCE_PIE ppgce.bit._PIE
#define PPGCE_PUF ppgce.bit._PUF
#define PPGCE_INTM ppgce.bit._INTM
#define PPGCE_PCS1 ppgce.bit._PCS1
#define PPGCE_PCS0 ppgce.bit._PCS0
#define PPGCE_MD1 ppgce.bit._MD1
#define PPGCE_MD0 ppgce.bit._MD0
#define PPGCE_PCS ppgce.bitc._PCS
#define PPGCE_MD ppgce.bitc._MD
__IO_EXTERN PPGCFSTR ppgcf;  
#define PPGCF ppgcf.byte
#define PPGCF_PIE ppgcf.bit._PIE
#define PPGCF_PUF ppgcf.bit._PUF
#define PPGCF_INTM ppgcf.bit._INTM
#define PPGCF_PCS1 ppgcf.bit._PCS1
#define PPGCF_PCS0 ppgcf.bit._PCS0
#define PPGCF_MD1 ppgcf.bit._MD1
#define PPGCF_MD0 ppgcf.bit._MD0
#define PPGCF_PCS ppgcf.bitc._PCS
#define PPGCF_MD ppgcf.bitc._MD
__IO_EXTERN PPGTRGSTR ppgtrg;   /* PPG 0-F Enable / Reverse */
#define PPGTRG ppgtrg.word
#define PPGTRG_PEN15 ppgtrg.bit._PEN15
#define PPGTRG_PEN14 ppgtrg.bit._PEN14
#define PPGTRG_PEN13 ppgtrg.bit._PEN13
#define PPGTRG_PEN12 ppgtrg.bit._PEN12
#define PPGTRG_PEN11 ppgtrg.bit._PEN11
#define PPGTRG_PEN10 ppgtrg.bit._PEN10
#define PPGTRG_PEN09 ppgtrg.bit._PEN09
#define PPGTRG_PEN08 ppgtrg.bit._PEN08
#define PPGTRG_PEN07 ppgtrg.bit._PEN07
#define PPGTRG_PEN06 ppgtrg.bit._PEN06
#define PPGTRG_PEN05 ppgtrg.bit._PEN05
#define PPGTRG_PEN04 ppgtrg.bit._PEN04
#define PPGTRG_PEN03 ppgtrg.bit._PEN03
#define PPGTRG_PEN02 ppgtrg.bit._PEN02
#define PPGTRG_PEN01 ppgtrg.bit._PEN01
#define PPGTRG_PEN00 ppgtrg.bit._PEN00
__IO_EXTERN PPGREVCSTR ppgrevc;  
#define PPGREVC ppgrevc.word
#define PPGREVC_REV15 ppgrevc.bit._REV15
#define PPGREVC_REV14 ppgrevc.bit._REV14
#define PPGREVC_REV13 ppgrevc.bit._REV13
#define PPGREVC_REV12 ppgrevc.bit._REV12
#define PPGREVC_REV11 ppgrevc.bit._REV11
#define PPGREVC_REV10 ppgrevc.bit._REV10
#define PPGREVC_REV09 ppgrevc.bit._REV09
#define PPGREVC_REV08 ppgrevc.bit._REV08
#define PPGREVC_REV07 ppgrevc.bit._REV07
#define PPGREVC_REV06 ppgrevc.bit._REV06
#define PPGREVC_REV05 ppgrevc.bit._REV05
#define PPGREVC_REV04 ppgrevc.bit._REV04
#define PPGREVC_REV03 ppgrevc.bit._REV03
#define PPGREVC_REV02 ppgrevc.bit._REV02
#define PPGREVC_REV01 ppgrevc.bit._REV01
#define PPGREVC_REV00 ppgrevc.bit._REV00
__IO_EXTERN IO_BYTE ppgswap;   /* PPG 0-F Output Swap */
#define PPGSWAP ppgswap
__IO_EXTERN CMCLKRSTR cmclkr;   /* Clock Monitor */
#define CMCLKR cmclkr.byte
#define CMCLKR_CKEN cmclkr.bit._CKEN
#define CMCLKR_FRQ2 cmclkr.bit._FRQ2
#define CMCLKR_FRQ1 cmclkr.bit._FRQ1
#define CMCLKR_FRQ0 cmclkr.bit._FRQ0
#define CMCLKR_FRQ cmclkr.bitc._FRQ
__IO_EXTERN DMACA0STR dmaca0;   /* DMAC */
#define DMACA0 dmaca0.lword
#define DMACA0_DENB dmaca0.bit._DENB
#define DMACA0_PAUS dmaca0.bit._PAUS
#define DMACA0_STRG dmaca0.bit._STRG
#define DMACA0_IS4 dmaca0.bit._IS4
#define DMACA0_IS3 dmaca0.bit._IS3
#define DMACA0_IS2 dmaca0.bit._IS2
#define DMACA0_IS1 dmaca0.bit._IS1
#define DMACA0_IS0 dmaca0.bit._IS0
#define DMACA0_DDN03 dmaca0.bit._DDN03
#define DMACA0_DDN02 dmaca0.bit._DDN02
#define DMACA0_DDN01 dmaca0.bit._DDN01
#define DMACA0_DDN00 dmaca0.bit._DDN00
#define DMACA0_BLK3 dmaca0.bit._BLK3
#define DMACA0_BLK2 dmaca0.bit._BLK2
#define DMACA0_BLK1 dmaca0.bit._BLK1
#define DMACA0_BLK0 dmaca0.bit._BLK0
#define DMACA0_DTCF dmaca0.bit._DTCF
#define DMACA0_DTCE dmaca0.bit._DTCE
#define DMACA0_DTCD dmaca0.bit._DTCD
#define DMACA0_DTCC dmaca0.bit._DTCC
#define DMACA0_DTCB dmaca0.bit._DTCB
#define DMACA0_DTCA dmaca0.bit._DTCA
#define DMACA0_DTC9 dmaca0.bit._DTC9
#define DMACA0_DTC8 dmaca0.bit._DTC8
#define DMACA0_DTC7 dmaca0.bit._DTC7
#define DMACA0_DTC6 dmaca0.bit._DTC6
#define DMACA0_DTC5 dmaca0.bit._DTC5
#define DMACA0_DTC4 dmaca0.bit._DTC4
#define DMACA0_DTC3 dmaca0.bit._DTC3
#define DMACA0_DTC2 dmaca0.bit._DTC2
#define DMACA0_DTC1 dmaca0.bit._DTC1
#define DMACA0_DTC0 dmaca0.bit._DTC0
#define DMACA0_IS dmaca0.bitc._IS
#define DMACA0_DDN0 dmaca0.bitc._DDN0
#define DMACA0_BLK dmaca0.bitc._BLK
#define DMACA0_DTC dmaca0.bitc._DTC
__IO_EXTERN DMACB0STR dmacb0;  
#define DMACB0 dmacb0.lword
#define DMACB0_TYPE1 dmacb0.bit._TYPE1
#define DMACB0_TYPE0 dmacb0.bit._TYPE0
#define DMACB0_MOD1 dmacb0.bit._MOD1
#define DMACB0_MOD0 dmacb0.bit._MOD0
#define DMACB0_WS1 dmacb0.bit._WS1
#define DMACB0_WS0 dmacb0.bit._WS0
#define DMACB0_SADM dmacb0.bit._SADM
#define DMACB0_DADM dmacb0.bit._DADM
#define DMACB0_DTCR dmacb0.bit._DTCR
#define DMACB0_SADR dmacb0.bit._SADR
#define DMACB0_DADR dmacb0.bit._DADR
#define DMACB0_ERIE dmacb0.bit._ERIE
#define DMACB0_EDIE dmacb0.bit._EDIE
#define DMACB0_DSS2 dmacb0.bit._DSS2
#define DMACB0_DSS1 dmacb0.bit._DSS1
#define DMACB0_DSS0 dmacb0.bit._DSS0
#define DMACB0_SASZ7 dmacb0.bit._SASZ7
#define DMACB0_SASZ6 dmacb0.bit._SASZ6
#define DMACB0_SASZ5 dmacb0.bit._SASZ5
#define DMACB0_SASZ4 dmacb0.bit._SASZ4
#define DMACB0_SASZ3 dmacb0.bit._SASZ3
#define DMACB0_SASZ2 dmacb0.bit._SASZ2
#define DMACB0_SASZ1 dmacb0.bit._SASZ1
#define DMACB0_SASZ0 dmacb0.bit._SASZ0
#define DMACB0_DASZ7 dmacb0.bit._DASZ7
#define DMACB0_DASZ6 dmacb0.bit._DASZ6
#define DMACB0_DASZ5 dmacb0.bit._DASZ5
#define DMACB0_DASZ4 dmacb0.bit._DASZ4
#define DMACB0_DASZ3 dmacb0.bit._DASZ3
#define DMACB0_DASZ2 dmacb0.bit._DASZ2
#define DMACB0_DASZ1 dmacb0.bit._DASZ1
#define DMACB0_DASZ0 dmacb0.bit._DASZ0
#define DMACB0_TYPE dmacb0.bitc._TYPE
#define DMACB0_MOD dmacb0.bitc._MOD
#define DMACB0_WS dmacb0.bitc._WS
#define DMACB0_DSS dmacb0.bitc._DSS
#define DMACB0_SASZ dmacb0.bitc._SASZ
#define DMACB0_DASZ dmacb0.bitc._DASZ
__IO_EXTERN DMACA1STR dmaca1;  
#define DMACA1 dmaca1.lword
#define DMACA1_DENB dmaca1.bit._DENB
#define DMACA1_PAUS dmaca1.bit._PAUS
#define DMACA1_STRG dmaca1.bit._STRG
#define DMACA1_IS4 dmaca1.bit._IS4
#define DMACA1_IS3 dmaca1.bit._IS3
#define DMACA1_IS2 dmaca1.bit._IS2
#define DMACA1_IS1 dmaca1.bit._IS1
#define DMACA1_IS0 dmaca1.bit._IS0
#define DMACA1_DDN13 dmaca1.bit._DDN13
#define DMACA1_DDN12 dmaca1.bit._DDN12
#define DMACA1_DDN11 dmaca1.bit._DDN11
#define DMACA1_DDN10 dmaca1.bit._DDN10
#define DMACA1_BLK3 dmaca1.bit._BLK3
#define DMACA1_BLK2 dmaca1.bit._BLK2
#define DMACA1_BLK1 dmaca1.bit._BLK1
#define DMACA1_BLK0 dmaca1.bit._BLK0
#define DMACA1_DTCF dmaca1.bit._DTCF
#define DMACA1_DTCE dmaca1.bit._DTCE
#define DMACA1_DTCD dmaca1.bit._DTCD
#define DMACA1_DTCC dmaca1.bit._DTCC
#define DMACA1_DTCB dmaca1.bit._DTCB
#define DMACA1_DTCA dmaca1.bit._DTCA
#define DMACA1_DTC9 dmaca1.bit._DTC9
#define DMACA1_DTC8 dmaca1.bit._DTC8
#define DMACA1_DTC7 dmaca1.bit._DTC7
#define DMACA1_DTC6 dmaca1.bit._DTC6
#define DMACA1_DTC5 dmaca1.bit._DTC5
#define DMACA1_DTC4 dmaca1.bit._DTC4
#define DMACA1_DTC3 dmaca1.bit._DTC3
#define DMACA1_DTC2 dmaca1.bit._DTC2
#define DMACA1_DTC1 dmaca1.bit._DTC1
#define DMACA1_DTC0 dmaca1.bit._DTC0
#define DMACA1_IS dmaca1.bitc._IS
#define DMACA1_DDN1 dmaca1.bitc._DDN1
#define DMACA1_BLK dmaca1.bitc._BLK
#define DMACA1_DTC dmaca1.bitc._DTC
__IO_EXTERN DMACB1STR dmacb1;  
#define DMACB1 dmacb1.lword
#define DMACB1_TYPE1 dmacb1.bit._TYPE1
#define DMACB1_TYPE0 dmacb1.bit._TYPE0
#define DMACB1_MD1 dmacb1.bit._MD1
#define DMACB1_MD0 dmacb1.bit._MD0
#define DMACB1_WS1 dmacb1.bit._WS1
#define DMACB1_WS0 dmacb1.bit._WS0
#define DMACB1_SADM dmacb1.bit._SADM
#define DMACB1_DADM dmacb1.bit._DADM
#define DMACB1_DTCR dmacb1.bit._DTCR
#define DMACB1_SADR dmacb1.bit._SADR
#define DMACB1_DADR dmacb1.bit._DADR
#define DMACB1_ERIE dmacb1.bit._ERIE
#define DMACB1_EDIE dmacb1.bit._EDIE
#define DMACB1_DSS2 dmacb1.bit._DSS2
#define DMACB1_DSS1 dmacb1.bit._DSS1
#define DMACB1_DSS0 dmacb1.bit._DSS0
#define DMACB1_SASZ7 dmacb1.bit._SASZ7
#define DMACB1_SASZ6 dmacb1.bit._SASZ6
#define DMACB1_SASZ5 dmacb1.bit._SASZ5
#define DMACB1_SASZ4 dmacb1.bit._SASZ4
#define DMACB1_SASZ3 dmacb1.bit._SASZ3
#define DMACB1_SASZ2 dmacb1.bit._SASZ2
#define DMACB1_SASZ1 dmacb1.bit._SASZ1
#define DMACB1_SASZ0 dmacb1.bit._SASZ0
#define DMACB1_DASZ7 dmacb1.bit._DASZ7
#define DMACB1_DASZ6 dmacb1.bit._DASZ6
#define DMACB1_DASZ5 dmacb1.bit._DASZ5
#define DMACB1_DASZ4 dmacb1.bit._DASZ4
#define DMACB1_DASZ3 dmacb1.bit._DASZ3
#define DMACB1_DASZ2 dmacb1.bit._DASZ2
#define DMACB1_DASZ1 dmacb1.bit._DASZ1
#define DMACB1_DASZ0 dmacb1.bit._DASZ0
#define DMACB1_TYPE dmacb1.bitc._TYPE
#define DMACB1_MD dmacb1.bitc._MD
#define DMACB1_WS dmacb1.bitc._WS
#define DMACB1_DSS dmacb1.bitc._DSS
#define DMACB1_SASZ dmacb1.bitc._SASZ
#define DMACB1_DASZ dmacb1.bitc._DASZ
__IO_EXTERN DMACA2STR dmaca2;  
#define DMACA2 dmaca2.lword
#define DMACA2_DENB dmaca2.bit._DENB
#define DMACA2_PAUS dmaca2.bit._PAUS
#define DMACA2_STRG dmaca2.bit._STRG
#define DMACA2_IS4 dmaca2.bit._IS4
#define DMACA2_IS3 dmaca2.bit._IS3
#define DMACA2_IS2 dmaca2.bit._IS2
#define DMACA2_IS1 dmaca2.bit._IS1
#define DMACA2_IS0 dmaca2.bit._IS0
#define DMACA2_DDN23 dmaca2.bit._DDN23
#define DMACA2_DDN22 dmaca2.bit._DDN22
#define DMACA2_DDN21 dmaca2.bit._DDN21
#define DMACA2_DDN20 dmaca2.bit._DDN20
#define DMACA2_BLK3 dmaca2.bit._BLK3
#define DMACA2_BLK2 dmaca2.bit._BLK2
#define DMACA2_BLK1 dmaca2.bit._BLK1
#define DMACA2_BLK0 dmaca2.bit._BLK0
#define DMACA2_DTCF dmaca2.bit._DTCF
#define DMACA2_DTCE dmaca2.bit._DTCE
#define DMACA2_DTCD dmaca2.bit._DTCD
#define DMACA2_DTCC dmaca2.bit._DTCC
#define DMACA2_DTCB dmaca2.bit._DTCB
#define DMACA2_DTCA dmaca2.bit._DTCA
#define DMACA2_DTC9 dmaca2.bit._DTC9
#define DMACA2_DTC8 dmaca2.bit._DTC8
#define DMACA2_DTC7 dmaca2.bit._DTC7
#define DMACA2_DTC6 dmaca2.bit._DTC6
#define DMACA2_DTC5 dmaca2.bit._DTC5
#define DMACA2_DTC4 dmaca2.bit._DTC4
#define DMACA2_DTC3 dmaca2.bit._DTC3
#define DMACA2_DTC2 dmaca2.bit._DTC2
#define DMACA2_DTC1 dmaca2.bit._DTC1
#define DMACA2_DTC0 dmaca2.bit._DTC0
#define DMACA2_IS dmaca2.bitc._IS
#define DMACA2_DDN2 dmaca2.bitc._DDN2
#define DMACA2_BLK dmaca2.bitc._BLK
#define DMACA2_DTC dmaca2.bitc._DTC
__IO_EXTERN DMACB2STR dmacb2;  
#define DMACB2 dmacb2.lword
#define DMACB2_TYPE1 dmacb2.bit._TYPE1
#define DMACB2_TYPE0 dmacb2.bit._TYPE0
#define DMACB2_MD1 dmacb2.bit._MD1
#define DMACB2_MD0 dmacb2.bit._MD0
#define DMACB2_WS1 dmacb2.bit._WS1
#define DMACB2_WS0 dmacb2.bit._WS0
#define DMACB2_SADM dmacb2.bit._SADM
#define DMACB2_DADM dmacb2.bit._DADM
#define DMACB2_DTCR dmacb2.bit._DTCR
#define DMACB2_SADR dmacb2.bit._SADR
#define DMACB2_DADR dmacb2.bit._DADR
#define DMACB2_ERIE dmacb2.bit._ERIE
#define DMACB2_EDIE dmacb2.bit._EDIE
#define DMACB2_DSS2 dmacb2.bit._DSS2
#define DMACB2_DSS1 dmacb2.bit._DSS1
#define DMACB2_DSS0 dmacb2.bit._DSS0
#define DMACB2_SASZ7 dmacb2.bit._SASZ7
#define DMACB2_SASZ6 dmacb2.bit._SASZ6
#define DMACB2_SASZ5 dmacb2.bit._SASZ5
#define DMACB2_SASZ4 dmacb2.bit._SASZ4
#define DMACB2_SASZ3 dmacb2.bit._SASZ3
#define DMACB2_SASZ2 dmacb2.bit._SASZ2
#define DMACB2_SASZ1 dmacb2.bit._SASZ1
#define DMACB2_SASZ0 dmacb2.bit._SASZ0
#define DMACB2_DASZ7 dmacb2.bit._DASZ7
#define DMACB2_DASZ6 dmacb2.bit._DASZ6
#define DMACB2_DASZ5 dmacb2.bit._DASZ5
#define DMACB2_DASZ4 dmacb2.bit._DASZ4
#define DMACB2_DASZ3 dmacb2.bit._DASZ3
#define DMACB2_DASZ2 dmacb2.bit._DASZ2
#define DMACB2_DASZ1 dmacb2.bit._DASZ1
#define DMACB2_DASZ0 dmacb2.bit._DASZ0
#define DMACB2_TYPE dmacb2.bitc._TYPE
#define DMACB2_MD dmacb2.bitc._MD
#define DMACB2_WS dmacb2.bitc._WS
#define DMACB2_DSS dmacb2.bitc._DSS
#define DMACB2_SASZ dmacb2.bitc._SASZ
#define DMACB2_DASZ dmacb2.bitc._DASZ
__IO_EXTERN DMACA3STR dmaca3;  
#define DMACA3 dmaca3.lword
#define DMACA3_DENB dmaca3.bit._DENB
#define DMACA3_PAUS dmaca3.bit._PAUS
#define DMACA3_STRG dmaca3.bit._STRG
#define DMACA3_IS4 dmaca3.bit._IS4
#define DMACA3_IS3 dmaca3.bit._IS3
#define DMACA3_IS2 dmaca3.bit._IS2
#define DMACA3_IS1 dmaca3.bit._IS1
#define DMACA3_IS0 dmaca3.bit._IS0
#define DMACA3_DDN33 dmaca3.bit._DDN33
#define DMACA3_DDN32 dmaca3.bit._DDN32
#define DMACA3_DDN31 dmaca3.bit._DDN31
#define DMACA3_DDN30 dmaca3.bit._DDN30
#define DMACA3_BLK3 dmaca3.bit._BLK3
#define DMACA3_BLK2 dmaca3.bit._BLK2
#define DMACA3_BLK1 dmaca3.bit._BLK1
#define DMACA3_BLK0 dmaca3.bit._BLK0
#define DMACA3_DTCF dmaca3.bit._DTCF
#define DMACA3_DTCE dmaca3.bit._DTCE
#define DMACA3_DTCD dmaca3.bit._DTCD
#define DMACA3_DTCC dmaca3.bit._DTCC
#define DMACA3_DTCB dmaca3.bit._DTCB
#define DMACA3_DTCA dmaca3.bit._DTCA
#define DMACA3_DTC9 dmaca3.bit._DTC9
#define DMACA3_DTC8 dmaca3.bit._DTC8
#define DMACA3_DTC7 dmaca3.bit._DTC7
#define DMACA3_DTC6 dmaca3.bit._DTC6
#define DMACA3_DTC5 dmaca3.bit._DTC5
#define DMACA3_DTC4 dmaca3.bit._DTC4
#define DMACA3_DTC3 dmaca3.bit._DTC3
#define DMACA3_DTC2 dmaca3.bit._DTC2
#define DMACA3_DTC1 dmaca3.bit._DTC1
#define DMACA3_DTC0 dmaca3.bit._DTC0
#define DMACA3_IS dmaca3.bitc._IS
#define DMACA3_DDN3 dmaca3.bitc._DDN3
#define DMACA3_BLK dmaca3.bitc._BLK
#define DMACA3_DTC dmaca3.bitc._DTC
__IO_EXTERN DMACB3STR dmacb3;  
#define DMACB3 dmacb3.lword
#define DMACB3_TYPE1 dmacb3.bit._TYPE1
#define DMACB3_TYPE0 dmacb3.bit._TYPE0
#define DMACB3_MD1 dmacb3.bit._MD1
#define DMACB3_MD0 dmacb3.bit._MD0
#define DMACB3_WS1 dmacb3.bit._WS1
#define DMACB3_WS0 dmacb3.bit._WS0
#define DMACB3_SADM dmacb3.bit._SADM
#define DMACB3_DADM dmacb3.bit._DADM
#define DMACB3_DTCR dmacb3.bit._DTCR
#define DMACB3_SADR dmacb3.bit._SADR
#define DMACB3_DADR dmacb3.bit._DADR
#define DMACB3_ERIE dmacb3.bit._ERIE
#define DMACB3_EDIE dmacb3.bit._EDIE
#define DMACB3_DSS2 dmacb3.bit._DSS2
#define DMACB3_DSS1 dmacb3.bit._DSS1
#define DMACB3_DSS0 dmacb3.bit._DSS0
#define DMACB3_SASZ7 dmacb3.bit._SASZ7
#define DMACB3_SASZ6 dmacb3.bit._SASZ6
#define DMACB3_SASZ5 dmacb3.bit._SASZ5
#define DMACB3_SASZ4 dmacb3.bit._SASZ4
#define DMACB3_SASZ3 dmacb3.bit._SASZ3
#define DMACB3_SASZ2 dmacb3.bit._SASZ2
#define DMACB3_SASZ1 dmacb3.bit._SASZ1
#define DMACB3_SASZ0 dmacb3.bit._SASZ0
#define DMACB3_DASZ7 dmacb3.bit._DASZ7
#define DMACB3_DASZ6 dmacb3.bit._DASZ6
#define DMACB3_DASZ5 dmacb3.bit._DASZ5
#define DMACB3_DASZ4 dmacb3.bit._DASZ4
#define DMACB3_DASZ3 dmacb3.bit._DASZ3
#define DMACB3_DASZ2 dmacb3.bit._DASZ2
#define DMACB3_DASZ1 dmacb3.bit._DASZ1
#define DMACB3_DASZ0 dmacb3.bit._DASZ0
#define DMACB3_TYPE dmacb3.bitc._TYPE
#define DMACB3_MD dmacb3.bitc._MD
#define DMACB3_WS dmacb3.bitc._WS
#define DMACB3_DSS dmacb3.bitc._DSS
#define DMACB3_SASZ dmacb3.bitc._SASZ
#define DMACB3_DASZ dmacb3.bitc._DASZ
__IO_EXTERN DMACA4STR dmaca4;  
#define DMACA4 dmaca4.lword
#define DMACA4_DENB dmaca4.bit._DENB
#define DMACA4_PAUS dmaca4.bit._PAUS
#define DMACA4_STRG dmaca4.bit._STRG
#define DMACA4_IS4 dmaca4.bit._IS4
#define DMACA4_IS3 dmaca4.bit._IS3
#define DMACA4_IS2 dmaca4.bit._IS2
#define DMACA4_IS1 dmaca4.bit._IS1
#define DMACA4_IS0 dmaca4.bit._IS0
#define DMACA4_DDN43 dmaca4.bit._DDN43
#define DMACA4_DDN42 dmaca4.bit._DDN42
#define DMACA4_DDN41 dmaca4.bit._DDN41
#define DMACA4_DDN40 dmaca4.bit._DDN40
#define DMACA4_BLK3 dmaca4.bit._BLK3
#define DMACA4_BLK2 dmaca4.bit._BLK2
#define DMACA4_BLK1 dmaca4.bit._BLK1
#define DMACA4_BLK0 dmaca4.bit._BLK0
#define DMACA4_DTCF dmaca4.bit._DTCF
#define DMACA4_DTCE dmaca4.bit._DTCE
#define DMACA4_DTCD dmaca4.bit._DTCD
#define DMACA4_DTCC dmaca4.bit._DTCC
#define DMACA4_DTCB dmaca4.bit._DTCB
#define DMACA4_DTCA dmaca4.bit._DTCA
#define DMACA4_DTC9 dmaca4.bit._DTC9
#define DMACA4_DTC8 dmaca4.bit._DTC8
#define DMACA4_DTC7 dmaca4.bit._DTC7
#define DMACA4_DTC6 dmaca4.bit._DTC6
#define DMACA4_DTC5 dmaca4.bit._DTC5
#define DMACA4_DTC4 dmaca4.bit._DTC4
#define DMACA4_DTC3 dmaca4.bit._DTC3
#define DMACA4_DTC2 dmaca4.bit._DTC2
#define DMACA4_DTC1 dmaca4.bit._DTC1
#define DMACA4_DTC0 dmaca4.bit._DTC0
#define DMACA4_IS dmaca4.bitc._IS
#define DMACA4_DDN4 dmaca4.bitc._DDN4
#define DMACA4_BLK dmaca4.bitc._BLK
#define DMACA4_DTC dmaca4.bitc._DTC
__IO_EXTERN DMACB4STR dmacb4;  
#define DMACB4 dmacb4.lword
#define DMACB4_TYPE1 dmacb4.bit._TYPE1
#define DMACB4_TYPE0 dmacb4.bit._TYPE0
#define DMACB4_MD1 dmacb4.bit._MD1
#define DMACB4_MD0 dmacb4.bit._MD0
#define DMACB4_WS1 dmacb4.bit._WS1
#define DMACB4_WS0 dmacb4.bit._WS0
#define DMACB4_SADM dmacb4.bit._SADM
#define DMACB4_DADM dmacb4.bit._DADM
#define DMACB4_DTCR dmacb4.bit._DTCR
#define DMACB4_SADR dmacb4.bit._SADR
#define DMACB4_DADR dmacb4.bit._DADR
#define DMACB4_ERIE dmacb4.bit._ERIE
#define DMACB4_EDIE dmacb4.bit._EDIE
#define DMACB4_DSS2 dmacb4.bit._DSS2
#define DMACB4_DSS1 dmacb4.bit._DSS1
#define DMACB4_DSS0 dmacb4.bit._DSS0
#define DMACB4_SASZ7 dmacb4.bit._SASZ7
#define DMACB4_SASZ6 dmacb4.bit._SASZ6
#define DMACB4_SASZ5 dmacb4.bit._SASZ5
#define DMACB4_SASZ4 dmacb4.bit._SASZ4
#define DMACB4_SASZ3 dmacb4.bit._SASZ3
#define DMACB4_SASZ2 dmacb4.bit._SASZ2
#define DMACB4_SASZ1 dmacb4.bit._SASZ1
#define DMACB4_SASZ0 dmacb4.bit._SASZ0
#define DMACB4_DASZ7 dmacb4.bit._DASZ7
#define DMACB4_DASZ6 dmacb4.bit._DASZ6
#define DMACB4_DASZ5 dmacb4.bit._DASZ5
#define DMACB4_DASZ4 dmacb4.bit._DASZ4
#define DMACB4_DASZ3 dmacb4.bit._DASZ3
#define DMACB4_DASZ2 dmacb4.bit._DASZ2
#define DMACB4_DASZ1 dmacb4.bit._DASZ1
#define DMACB4_DASZ0 dmacb4.bit._DASZ0
#define DMACB4_TYPE dmacb4.bitc._TYPE
#define DMACB4_MD dmacb4.bitc._MD
#define DMACB4_WS dmacb4.bitc._WS
#define DMACB4_DSS dmacb4.bitc._DSS
#define DMACB4_SASZ dmacb4.bitc._SASZ
#define DMACB4_DASZ dmacb4.bitc._DASZ
__IO_EXTERN DMACRSTR dmacr;  
#define DMACR dmacr.byte
#define DMACR_DMAE dmacr.bit._DMAE
#define DMACR_PM01 dmacr.bit._PM01
#define DMACR_DMAH3 dmacr.bit._DMAH3
#define DMACR_DMAH2 dmacr.bit._DMAH2
#define DMACR_DMAH1 dmacr.bit._DMAH1
#define DMACR_DMAH0 dmacr.bit._DMAH0
#define DMACR_DMAH dmacr.bitc._DMAH
__IO_EXTERN IO_LWORD bsd0;   /* Bit Search */
#define BSD0 bsd0
__IO_EXTERN IO_LWORD bsd1;  
#define BSD1 bsd1
__IO_EXTERN IO_LWORD bsdc;  
#define BSDC bsdc
__IO_EXTERN IO_LWORD bsrr;  
#define BSRR bsrr
__IO_EXTERN DDR0STR ddr0;   /* Data Direction Register */
#define DDR0 ddr0.byte
#define DDR0_D07 ddr0.bit._D07
#define DDR0_D06 ddr0.bit._D06
#define DDR0_D05 ddr0.bit._D05
#define DDR0_D04 ddr0.bit._D04
#define DDR0_D03 ddr0.bit._D03
#define DDR0_D02 ddr0.bit._D02
#define DDR0_D01 ddr0.bit._D01
#define DDR0_D00 ddr0.bit._D00
__IO_EXTERN DDR1STR ddr1;  
#define DDR1 ddr1.byte
#define DDR1_D17 ddr1.bit._D17
#define DDR1_D16 ddr1.bit._D16
#define DDR1_D15 ddr1.bit._D15
#define DDR1_D14 ddr1.bit._D14
#define DDR1_D13 ddr1.bit._D13
#define DDR1_D12 ddr1.bit._D12
#define DDR1_D11 ddr1.bit._D11
#define DDR1_D10 ddr1.bit._D10
__IO_EXTERN DDR2STR ddr2;  
#define DDR2 ddr2.byte
#define DDR2_D27 ddr2.bit._D27
#define DDR2_D26 ddr2.bit._D26
#define DDR2_D25 ddr2.bit._D25
#define DDR2_D24 ddr2.bit._D24
#define DDR2_D23 ddr2.bit._D23
#define DDR2_D22 ddr2.bit._D22
#define DDR2_D21 ddr2.bit._D21
#define DDR2_D20 ddr2.bit._D20
__IO_EXTERN DDR3STR ddr3;  
#define DDR3 ddr3.byte
#define DDR3_D37 ddr3.bit._D37
#define DDR3_D36 ddr3.bit._D36
#define DDR3_D35 ddr3.bit._D35
#define DDR3_D34 ddr3.bit._D34
#define DDR3_D33 ddr3.bit._D33
#define DDR3_D32 ddr3.bit._D32
#define DDR3_D31 ddr3.bit._D31
#define DDR3_D30 ddr3.bit._D30
__IO_EXTERN DDR4STR ddr4;  
#define DDR4 ddr4.byte
#define DDR4_D47 ddr4.bit._D47
#define DDR4_D46 ddr4.bit._D46
#define DDR4_D45 ddr4.bit._D45
#define DDR4_D44 ddr4.bit._D44
#define DDR4_D43 ddr4.bit._D43
#define DDR4_D42 ddr4.bit._D42
#define DDR4_D41 ddr4.bit._D41
#define DDR4_D40 ddr4.bit._D40
__IO_EXTERN DDR5STR ddr5;  
#define DDR5 ddr5.byte
#define DDR5_D57 ddr5.bit._D57
#define DDR5_D56 ddr5.bit._D56
#define DDR5_D55 ddr5.bit._D55
#define DDR5_D54 ddr5.bit._D54
#define DDR5_D53 ddr5.bit._D53
#define DDR5_D52 ddr5.bit._D52
#define DDR5_D51 ddr5.bit._D51
#define DDR5_D50 ddr5.bit._D50
__IO_EXTERN DDR6STR ddr6;  
#define DDR6 ddr6.byte
#define DDR6_D67 ddr6.bit._D67
#define DDR6_D66 ddr6.bit._D66
#define DDR6_D65 ddr6.bit._D65
#define DDR6_D64 ddr6.bit._D64
#define DDR6_D63 ddr6.bit._D63
#define DDR6_D62 ddr6.bit._D62
#define DDR6_D61 ddr6.bit._D61
#define DDR6_D60 ddr6.bit._D60
__IO_EXTERN DDR7STR ddr7;  
#define DDR7 ddr7.byte
#define DDR7_D77 ddr7.bit._D77
#define DDR7_D76 ddr7.bit._D76
#define DDR7_D75 ddr7.bit._D75
#define DDR7_D74 ddr7.bit._D74
#define DDR7_D73 ddr7.bit._D73
#define DDR7_D72 ddr7.bit._D72
#define DDR7_D71 ddr7.bit._D71
#define DDR7_D70 ddr7.bit._D70
__IO_EXTERN DDR8STR ddr8;  
#define DDR8 ddr8.byte
#define DDR8_D87 ddr8.bit._D87
#define DDR8_D86 ddr8.bit._D86
#define DDR8_D85 ddr8.bit._D85
#define DDR8_D84 ddr8.bit._D84
#define DDR8_D83 ddr8.bit._D83
#define DDR8_D82 ddr8.bit._D82
#define DDR8_D81 ddr8.bit._D81
#define DDR8_D80 ddr8.bit._D80
__IO_EXTERN DDR9STR ddr9;  
#define DDR9 ddr9.byte
#define DDR9_D97 ddr9.bit._D97
#define DDR9_D96 ddr9.bit._D96
#define DDR9_D95 ddr9.bit._D95
#define DDR9_D94 ddr9.bit._D94
#define DDR9_D93 ddr9.bit._D93
#define DDR9_D92 ddr9.bit._D92
#define DDR9_D91 ddr9.bit._D91
#define DDR9_D90 ddr9.bit._D90
__IO_EXTERN DDRASTR ddra;  
#define DDRA ddra.byte
#define DDRA_DA1 ddra.bit._DA1
#define DDRA_DA0 ddra.bit._DA0
__IO_EXTERN DDRBSTR ddrb;  
#define DDRB ddrb.byte
#define DDRB_DB5 ddrb.bit._DB5
#define DDRB_DB4 ddrb.bit._DB4
#define DDRB_DB3 ddrb.bit._DB3
#define DDRB_DB2 ddrb.bit._DB2
#define DDRB_DB1 ddrb.bit._DB1
#define DDRB_DB0 ddrb.bit._DB0
__IO_EXTERN DDRCSTR ddrc;  
#define DDRC ddrc.byte
#define DDRC_DC7 ddrc.bit._DC7
#define DDRC_DC6 ddrc.bit._DC6
#define DDRC_DC5 ddrc.bit._DC5
#define DDRC_DC4 ddrc.bit._DC4
#define DDRC_DC3 ddrc.bit._DC3
#define DDRC_DC2 ddrc.bit._DC2
#define DDRC_DC1 ddrc.bit._DC1
#define DDRC_DC0 ddrc.bit._DC0
__IO_EXTERN DDRDSTR ddrd;  
#define DDRD ddrd.byte
#define DDRD_DD7 ddrd.bit._DD7
#define DDRD_DD6 ddrd.bit._DD6
#define DDRD_DD5 ddrd.bit._DD5
#define DDRD_DD4 ddrd.bit._DD4
#define DDRD_DD3 ddrd.bit._DD3
#define DDRD_DD2 ddrd.bit._DD2
#define DDRD_DD1 ddrd.bit._DD1
#define DDRD_DD0 ddrd.bit._DD0
__IO_EXTERN DDRESTR ddre;  
#define DDRE ddre.byte
#define DDRE_DE7 ddre.bit._DE7
#define DDRE_DE6 ddre.bit._DE6
#define DDRE_DE5 ddre.bit._DE5
#define DDRE_DE4 ddre.bit._DE4
#define DDRE_DE3 ddre.bit._DE3
#define DDRE_DE2 ddre.bit._DE2
#define DDRE_DE1 ddre.bit._DE1
#define DDRE_DE0 ddre.bit._DE0
__IO_EXTERN DDRFSTR ddrf;  
#define DDRF ddrf.byte
#define DDRF_DF7 ddrf.bit._DF7
#define DDRF_DF6 ddrf.bit._DF6
#define DDRF_DF5 ddrf.bit._DF5
#define DDRF_DF4 ddrf.bit._DF4
#define DDRF_DF3 ddrf.bit._DF3
#define DDRF_DF2 ddrf.bit._DF2
#define DDRF_DF1 ddrf.bit._DF1
#define DDRF_DF0 ddrf.bit._DF0
__IO_EXTERN DDRGSTR ddrg;  
#define DDRG ddrg.byte
#define DDRG_DG7 ddrg.bit._DG7
#define DDRG_DG6 ddrg.bit._DG6
#define DDRG_DG5 ddrg.bit._DG5
#define DDRG_DG4 ddrg.bit._DG4
#define DDRG_DG3 ddrg.bit._DG3
#define DDRG_DG2 ddrg.bit._DG2
#define DDRG_DG1 ddrg.bit._DG1
#define DDRG_DG0 ddrg.bit._DG0
__IO_EXTERN PFR0STR pfr0;   /* Port Function Register */
#define PFR0 pfr0.byte
#define PFR0_F05 pfr0.bit._F05
#define PFR0_F04 pfr0.bit._F04
#define PFR0_F02 pfr0.bit._F02
#define PFR0_F01 pfr0.bit._F01
__IO_EXTERN PFR1STR pfr1;  
#define PFR1 pfr1.byte
#define PFR1_F17 pfr1.bit._F17
#define PFR1_F06 pfr1.bit._F06
#define PFR1_F04 pfr1.bit._F04
#define PFR1_F03 pfr1.bit._F03
__IO_EXTERN PFR2STR pfr2;  
#define PFR2 pfr2.byte
#define PFR2_F27 pfr2.bit._F27
#define PFR2_F06 pfr2.bit._F06
#define PFR2_F05 pfr2.bit._F05
#define PFR2_F04 pfr2.bit._F04
#define PFR2_F03 pfr2.bit._F03
#define PFR2_F02 pfr2.bit._F02
#define PFR2_F01 pfr2.bit._F01
#define PFR2_F00 pfr2.bit._F00
__IO_EXTERN PFR3STR pfr3;  
#define PFR3 pfr3.byte
#define PFR3_F07 pfr3.bit._F07
#define PFR3_F06 pfr3.bit._F06
#define PFR3_F05 pfr3.bit._F05
#define PFR3_F04 pfr3.bit._F04
#define PFR3_F03 pfr3.bit._F03
#define PFR3_F01 pfr3.bit._F01
#define PFR3_F00 pfr3.bit._F00
__IO_EXTERN PFR4STR pfr4;  
#define PFR4 pfr4.byte
#define PFR4_F07 pfr4.bit._F07
#define PFR4_F06 pfr4.bit._F06
#define PFR4_F05 pfr4.bit._F05
#define PFR4_F04 pfr4.bit._F04
#define PFR4_F03 pfr4.bit._F03
#define PFR4_F02 pfr4.bit._F02
__IO_EXTERN PFR5STR pfr5;  
#define PFR5 pfr5.byte
#define PFR5_F02 pfr5.bit._F02
#define PFR5_F01 pfr5.bit._F01
__IO_EXTERN PFR6STR pfr6;  
#define PFR6 pfr6.byte
#define PFR6_F07 pfr6.bit._F07
#define PFR6_F06 pfr6.bit._F06
#define PFR6_F05 pfr6.bit._F05
#define PFR6_F04 pfr6.bit._F04
#define PFR6_F03 pfr6.bit._F03
#define PFR6_F02 pfr6.bit._F02
#define PFR6_F01 pfr6.bit._F01
#define PFR6_F00 pfr6.bit._F00
__IO_EXTERN PFR7STR pfr7;  
#define PFR7 pfr7.byte
#define PFR7_F07 pfr7.bit._F07
#define PFR7_F06 pfr7.bit._F06
__IO_EXTERN PFR8STR pfr8;  
#define PFR8 pfr8.byte
#define PFR8_F07 pfr8.bit._F07
#define PFR8_F06 pfr8.bit._F06
#define PFR8_F04 pfr8.bit._F04
#define PFR8_F03 pfr8.bit._F03
#define PFR8_F01 pfr8.bit._F01
__IO_EXTERN PFR9STR pfr9;  
#define PFR9 pfr9.byte
#define PFR9_F07 pfr9.bit._F07
#define PFR9_F06 pfr9.bit._F06
#define PFR9_F05 pfr9.bit._F05
#define PFR9_F04 pfr9.bit._F04
#define PFR9_F03 pfr9.bit._F03
#define PFR9_F02 pfr9.bit._F02
#define PFR9_F01 pfr9.bit._F01
#define PFR9_F00 pfr9.bit._F00
__IO_EXTERN PFRASTR pfra;  
#define PFRA pfra.byte
#define PFRA_F01 pfra.bit._F01
#define PFRA_F00 pfra.bit._F00
__IO_EXTERN PFRBSTR pfrb;  
#define PFRB pfrb.byte
#define PFRB_F05 pfrb.bit._F05
#define PFRB_F04 pfrb.bit._F04
#define PFRB_F03 pfrb.bit._F03
#define PFRB_F02 pfrb.bit._F02
#define PFRB_F01 pfrb.bit._F01
#define PFRB_F00 pfrb.bit._F00
__IO_EXTERN PFRCSTR pfrc;  
#define PFRC pfrc.byte
#define PFRC_F07 pfrc.bit._F07
#define PFRC_F06 pfrc.bit._F06
#define PFRC_F05 pfrc.bit._F05
#define PFRC_F04 pfrc.bit._F04
#define PFRC_F03 pfrc.bit._F03
#define PFRC_F02 pfrc.bit._F02
#define PFRC_F01 pfrc.bit._F01
#define PFRC_F00 pfrc.bit._F00
__IO_EXTERN PFRDSTR pfrd;  
#define PFRD pfrd.byte
#define PFRD_F07 pfrd.bit._F07
#define PFRD_F06 pfrd.bit._F06
#define PFRD_F05 pfrd.bit._F05
#define PFRD_F04 pfrd.bit._F04
#define PFRD_F03 pfrd.bit._F03
#define PFRD_F02 pfrd.bit._F02
#define PFRD_F01 pfrd.bit._F01
#define PFRD_F00 pfrd.bit._F00
__IO_EXTERN PFRESTR pfre;  
#define PFRE pfre.byte
__IO_EXTERN PFRFSTR pfrf;  
#define PFRF pfrf.byte
__IO_EXTERN PFRGSTR pfrg;  
#define PFRG pfrg.byte
__IO_EXTERN ICR00STR icr00;   /* Interrupt Control Unit */
#define ICR00 icr00.byte
#define ICR00_ICR4 icr00.bit._ICR4
#define ICR00_ICR3 icr00.bit._ICR3
#define ICR00_ICR2 icr00.bit._ICR2
#define ICR00_ICR1 icr00.bit._ICR1
#define ICR00_ICR0 icr00.bit._ICR0
__IO_EXTERN ICR01STR icr01;  
#define ICR01 icr01.byte
#define ICR01_ICR4 icr01.bit._ICR4
#define ICR01_ICR3 icr01.bit._ICR3
#define ICR01_ICR2 icr01.bit._ICR2
#define ICR01_ICR1 icr01.bit._ICR1
#define ICR01_ICR0 icr01.bit._ICR0
__IO_EXTERN ICR02STR icr02;  
#define ICR02 icr02.byte
#define ICR02_ICR4 icr02.bit._ICR4
#define ICR02_ICR3 icr02.bit._ICR3
#define ICR02_ICR2 icr02.bit._ICR2
#define ICR02_ICR1 icr02.bit._ICR1
#define ICR02_ICR0 icr02.bit._ICR0
__IO_EXTERN ICR03STR icr03;  
#define ICR03 icr03.byte
#define ICR03_ICR4 icr03.bit._ICR4
#define ICR03_ICR3 icr03.bit._ICR3
#define ICR03_ICR2 icr03.bit._ICR2
#define ICR03_ICR1 icr03.bit._ICR1
#define ICR03_ICR0 icr03.bit._ICR0
__IO_EXTERN ICR04STR icr04;  
#define ICR04 icr04.byte
#define ICR04_ICR4 icr04.bit._ICR4
#define ICR04_ICR3 icr04.bit._ICR3
#define ICR04_ICR2 icr04.bit._ICR2
#define ICR04_ICR1 icr04.bit._ICR1
#define ICR04_ICR0 icr04.bit._ICR0
__IO_EXTERN ICR05STR icr05;  
#define ICR05 icr05.byte
#define ICR05_ICR4 icr05.bit._ICR4
#define ICR05_ICR3 icr05.bit._ICR3
#define ICR05_ICR2 icr05.bit._ICR2
#define ICR05_ICR1 icr05.bit._ICR1
#define ICR05_ICR0 icr05.bit._ICR0
__IO_EXTERN ICR06STR icr06;  
#define ICR06 icr06.byte
#define ICR06_ICR4 icr06.bit._ICR4
#define ICR06_ICR3 icr06.bit._ICR3
#define ICR06_ICR2 icr06.bit._ICR2
#define ICR06_ICR1 icr06.bit._ICR1
#define ICR06_ICR0 icr06.bit._ICR0
__IO_EXTERN ICR07STR icr07;  
#define ICR07 icr07.byte
#define ICR07_ICR4 icr07.bit._ICR4
#define ICR07_ICR3 icr07.bit._ICR3
#define ICR07_ICR2 icr07.bit._ICR2
#define ICR07_ICR1 icr07.bit._ICR1
#define ICR07_ICR0 icr07.bit._ICR0
__IO_EXTERN ICR08STR icr08;  
#define ICR08 icr08.byte
#define ICR08_ICR4 icr08.bit._ICR4
#define ICR08_ICR3 icr08.bit._ICR3
#define ICR08_ICR2 icr08.bit._ICR2
#define ICR08_ICR1 icr08.bit._ICR1
#define ICR08_ICR0 icr08.bit._ICR0
__IO_EXTERN ICR09STR icr09;  
#define ICR09 icr09.byte
#define ICR09_ICR4 icr09.bit._ICR4
#define ICR09_ICR3 icr09.bit._ICR3
#define ICR09_ICR2 icr09.bit._ICR2
#define ICR09_ICR1 icr09.bit._ICR1
#define ICR09_ICR0 icr09.bit._ICR0
__IO_EXTERN ICR10STR icr10;  
#define ICR10 icr10.byte
#define ICR10_ICR4 icr10.bit._ICR4
#define ICR10_ICR3 icr10.bit._ICR3
#define ICR10_ICR2 icr10.bit._ICR2
#define ICR10_ICR1 icr10.bit._ICR1
#define ICR10_ICR0 icr10.bit._ICR0
__IO_EXTERN ICR11STR icr11;  
#define ICR11 icr11.byte
#define ICR11_ICR4 icr11.bit._ICR4
#define ICR11_ICR3 icr11.bit._ICR3
#define ICR11_ICR2 icr11.bit._ICR2
#define ICR11_ICR1 icr11.bit._ICR1
#define ICR11_ICR0 icr11.bit._ICR0
__IO_EXTERN ICR12STR icr12;  
#define ICR12 icr12.byte
#define ICR12_ICR4 icr12.bit._ICR4
#define ICR12_ICR3 icr12.bit._ICR3
#define ICR12_ICR2 icr12.bit._ICR2
#define ICR12_ICR1 icr12.bit._ICR1
#define ICR12_ICR0 icr12.bit._ICR0
__IO_EXTERN ICR13STR icr13;  
#define ICR13 icr13.byte
#define ICR13_ICR4 icr13.bit._ICR4
#define ICR13_ICR3 icr13.bit._ICR3
#define ICR13_ICR2 icr13.bit._ICR2
#define ICR13_ICR1 icr13.bit._ICR1
#define ICR13_ICR0 icr13.bit._ICR0
__IO_EXTERN ICR14STR icr14;  
#define ICR14 icr14.byte
#define ICR14_ICR4 icr14.bit._ICR4
#define ICR14_ICR3 icr14.bit._ICR3
#define ICR14_ICR2 icr14.bit._ICR2
#define ICR14_ICR1 icr14.bit._ICR1
#define ICR14_ICR0 icr14.bit._ICR0
__IO_EXTERN ICR15STR icr15;  
#define ICR15 icr15.byte
#define ICR15_ICR4 icr15.bit._ICR4
#define ICR15_ICR3 icr15.bit._ICR3
#define ICR15_ICR2 icr15.bit._ICR2
#define ICR15_ICR1 icr15.bit._ICR1
#define ICR15_ICR0 icr15.bit._ICR0
__IO_EXTERN ICR16STR icr16;  
#define ICR16 icr16.byte
#define ICR16_ICR4 icr16.bit._ICR4
#define ICR16_ICR3 icr16.bit._ICR3
#define ICR16_ICR2 icr16.bit._ICR2
#define ICR16_ICR1 icr16.bit._ICR1
#define ICR16_ICR0 icr16.bit._ICR0
__IO_EXTERN ICR17STR icr17;  
#define ICR17 icr17.byte
#define ICR17_ICR4 icr17.bit._ICR4
#define ICR17_ICR3 icr17.bit._ICR3
#define ICR17_ICR2 icr17.bit._ICR2
#define ICR17_ICR1 icr17.bit._ICR1
#define ICR17_ICR0 icr17.bit._ICR0
__IO_EXTERN ICR18STR icr18;  
#define ICR18 icr18.byte
#define ICR18_ICR4 icr18.bit._ICR4
#define ICR18_ICR3 icr18.bit._ICR3
#define ICR18_ICR2 icr18.bit._ICR2
#define ICR18_ICR1 icr18.bit._ICR1
#define ICR18_ICR0 icr18.bit._ICR0
__IO_EXTERN ICR19STR icr19;  
#define ICR19 icr19.byte
#define ICR19_ICR4 icr19.bit._ICR4
#define ICR19_ICR3 icr19.bit._ICR3
#define ICR19_ICR2 icr19.bit._ICR2
#define ICR19_ICR1 icr19.bit._ICR1
#define ICR19_ICR0 icr19.bit._ICR0
__IO_EXTERN ICR20STR icr20;  
#define ICR20 icr20.byte
#define ICR20_ICR4 icr20.bit._ICR4
#define ICR20_ICR3 icr20.bit._ICR3
#define ICR20_ICR2 icr20.bit._ICR2
#define ICR20_ICR1 icr20.bit._ICR1
#define ICR20_ICR0 icr20.bit._ICR0
__IO_EXTERN ICR21STR icr21;  
#define ICR21 icr21.byte
#define ICR21_ICR4 icr21.bit._ICR4
#define ICR21_ICR3 icr21.bit._ICR3
#define ICR21_ICR2 icr21.bit._ICR2
#define ICR21_ICR1 icr21.bit._ICR1
#define ICR21_ICR0 icr21.bit._ICR0
__IO_EXTERN ICR22STR icr22;  
#define ICR22 icr22.byte
#define ICR22_ICR4 icr22.bit._ICR4
#define ICR22_ICR3 icr22.bit._ICR3
#define ICR22_ICR2 icr22.bit._ICR2
#define ICR22_ICR1 icr22.bit._ICR1
#define ICR22_ICR0 icr22.bit._ICR0
__IO_EXTERN ICR23STR icr23;  
#define ICR23 icr23.byte
#define ICR23_ICR4 icr23.bit._ICR4
#define ICR23_ICR3 icr23.bit._ICR3
#define ICR23_ICR2 icr23.bit._ICR2
#define ICR23_ICR1 icr23.bit._ICR1
#define ICR23_ICR0 icr23.bit._ICR0
__IO_EXTERN ICR24STR icr24;  
#define ICR24 icr24.byte
#define ICR24_ICR4 icr24.bit._ICR4
#define ICR24_ICR3 icr24.bit._ICR3
#define ICR24_ICR2 icr24.bit._ICR2
#define ICR24_ICR1 icr24.bit._ICR1
#define ICR24_ICR0 icr24.bit._ICR0
__IO_EXTERN ICR25STR icr25;  
#define ICR25 icr25.byte
#define ICR25_ICR4 icr25.bit._ICR4
#define ICR25_ICR3 icr25.bit._ICR3
#define ICR25_ICR2 icr25.bit._ICR2
#define ICR25_ICR1 icr25.bit._ICR1
#define ICR25_ICR0 icr25.bit._ICR0
__IO_EXTERN ICR26STR icr26;  
#define ICR26 icr26.byte
#define ICR26_ICR4 icr26.bit._ICR4
#define ICR26_ICR3 icr26.bit._ICR3
#define ICR26_ICR2 icr26.bit._ICR2
#define ICR26_ICR1 icr26.bit._ICR1
#define ICR26_ICR0 icr26.bit._ICR0
__IO_EXTERN ICR27STR icr27;  
#define ICR27 icr27.byte
#define ICR27_ICR4 icr27.bit._ICR4
#define ICR27_ICR3 icr27.bit._ICR3
#define ICR27_ICR2 icr27.bit._ICR2
#define ICR27_ICR1 icr27.bit._ICR1
#define ICR27_ICR0 icr27.bit._ICR0
__IO_EXTERN ICR28STR icr28;  
#define ICR28 icr28.byte
#define ICR28_ICR4 icr28.bit._ICR4
#define ICR28_ICR3 icr28.bit._ICR3
#define ICR28_ICR2 icr28.bit._ICR2
#define ICR28_ICR1 icr28.bit._ICR1
#define ICR28_ICR0 icr28.bit._ICR0
__IO_EXTERN ICR29STR icr29;  
#define ICR29 icr29.byte
#define ICR29_ICR4 icr29.bit._ICR4
#define ICR29_ICR3 icr29.bit._ICR3
#define ICR29_ICR2 icr29.bit._ICR2
#define ICR29_ICR1 icr29.bit._ICR1
#define ICR29_ICR0 icr29.bit._ICR0
__IO_EXTERN ICR30STR icr30;  
#define ICR30 icr30.byte
#define ICR30_ICR4 icr30.bit._ICR4
#define ICR30_ICR3 icr30.bit._ICR3
#define ICR30_ICR2 icr30.bit._ICR2
#define ICR30_ICR1 icr30.bit._ICR1
#define ICR30_ICR0 icr30.bit._ICR0
__IO_EXTERN ICR31STR icr31;  
#define ICR31 icr31.byte
#define ICR31_ICR4 icr31.bit._ICR4
#define ICR31_ICR3 icr31.bit._ICR3
#define ICR31_ICR2 icr31.bit._ICR2
#define ICR31_ICR1 icr31.bit._ICR1
#define ICR31_ICR0 icr31.bit._ICR0
__IO_EXTERN ICR32STR icr32;  
#define ICR32 icr32.byte
#define ICR32_ICR4 icr32.bit._ICR4
#define ICR32_ICR3 icr32.bit._ICR3
#define ICR32_ICR2 icr32.bit._ICR2
#define ICR32_ICR1 icr32.bit._ICR1
#define ICR32_ICR0 icr32.bit._ICR0
__IO_EXTERN ICR33STR icr33;  
#define ICR33 icr33.byte
#define ICR33_ICR4 icr33.bit._ICR4
#define ICR33_ICR3 icr33.bit._ICR3
#define ICR33_ICR2 icr33.bit._ICR2
#define ICR33_ICR1 icr33.bit._ICR1
#define ICR33_ICR0 icr33.bit._ICR0
__IO_EXTERN ICR34STR icr34;  
#define ICR34 icr34.byte
#define ICR34_ICR4 icr34.bit._ICR4
#define ICR34_ICR3 icr34.bit._ICR3
#define ICR34_ICR2 icr34.bit._ICR2
#define ICR34_ICR1 icr34.bit._ICR1
#define ICR34_ICR0 icr34.bit._ICR0
__IO_EXTERN ICR35STR icr35;  
#define ICR35 icr35.byte
#define ICR35_ICR4 icr35.bit._ICR4
#define ICR35_ICR3 icr35.bit._ICR3
#define ICR35_ICR2 icr35.bit._ICR2
#define ICR35_ICR1 icr35.bit._ICR1
#define ICR35_ICR0 icr35.bit._ICR0
__IO_EXTERN ICR36STR icr36;  
#define ICR36 icr36.byte
#define ICR36_ICR4 icr36.bit._ICR4
#define ICR36_ICR3 icr36.bit._ICR3
#define ICR36_ICR2 icr36.bit._ICR2
#define ICR36_ICR1 icr36.bit._ICR1
#define ICR36_ICR0 icr36.bit._ICR0
__IO_EXTERN ICR37STR icr37;  
#define ICR37 icr37.byte
#define ICR37_ICR4 icr37.bit._ICR4
#define ICR37_ICR3 icr37.bit._ICR3
#define ICR37_ICR2 icr37.bit._ICR2
#define ICR37_ICR1 icr37.bit._ICR1
#define ICR37_ICR0 icr37.bit._ICR0
__IO_EXTERN ICR38STR icr38;  
#define ICR38 icr38.byte
#define ICR38_ICR4 icr38.bit._ICR4
#define ICR38_ICR3 icr38.bit._ICR3
#define ICR38_ICR2 icr38.bit._ICR2
#define ICR38_ICR1 icr38.bit._ICR1
#define ICR38_ICR0 icr38.bit._ICR0
__IO_EXTERN ICR39STR icr39;  
#define ICR39 icr39.byte
#define ICR39_ICR4 icr39.bit._ICR4
#define ICR39_ICR3 icr39.bit._ICR3
#define ICR39_ICR2 icr39.bit._ICR2
#define ICR39_ICR1 icr39.bit._ICR1
#define ICR39_ICR0 icr39.bit._ICR0
__IO_EXTERN ICR40STR icr40;  
#define ICR40 icr40.byte
#define ICR40_ICR4 icr40.bit._ICR4
#define ICR40_ICR3 icr40.bit._ICR3
#define ICR40_ICR2 icr40.bit._ICR2
#define ICR40_ICR1 icr40.bit._ICR1
#define ICR40_ICR0 icr40.bit._ICR0
__IO_EXTERN ICR41STR icr41;  
#define ICR41 icr41.byte
#define ICR41_ICR4 icr41.bit._ICR4
#define ICR41_ICR3 icr41.bit._ICR3
#define ICR41_ICR2 icr41.bit._ICR2
#define ICR41_ICR1 icr41.bit._ICR1
#define ICR41_ICR0 icr41.bit._ICR0
__IO_EXTERN ICR42STR icr42;  
#define ICR42 icr42.byte
#define ICR42_ICR4 icr42.bit._ICR4
#define ICR42_ICR3 icr42.bit._ICR3
#define ICR42_ICR2 icr42.bit._ICR2
#define ICR42_ICR1 icr42.bit._ICR1
#define ICR42_ICR0 icr42.bit._ICR0
__IO_EXTERN ICR43STR icr43;  
#define ICR43 icr43.byte
#define ICR43_ICR4 icr43.bit._ICR4
#define ICR43_ICR3 icr43.bit._ICR3
#define ICR43_ICR2 icr43.bit._ICR2
#define ICR43_ICR1 icr43.bit._ICR1
#define ICR43_ICR0 icr43.bit._ICR0
__IO_EXTERN ICR44STR icr44;  
#define ICR44 icr44.byte
#define ICR44_ICR4 icr44.bit._ICR4
#define ICR44_ICR3 icr44.bit._ICR3
#define ICR44_ICR2 icr44.bit._ICR2
#define ICR44_ICR1 icr44.bit._ICR1
#define ICR44_ICR0 icr44.bit._ICR0
__IO_EXTERN ICR45STR icr45;  
#define ICR45 icr45.byte
#define ICR45_ICR4 icr45.bit._ICR4
#define ICR45_ICR3 icr45.bit._ICR3
#define ICR45_ICR2 icr45.bit._ICR2
#define ICR45_ICR1 icr45.bit._ICR1
#define ICR45_ICR0 icr45.bit._ICR0
__IO_EXTERN ICR46STR icr46;  
#define ICR46 icr46.byte
#define ICR46_ICR4 icr46.bit._ICR4
#define ICR46_ICR3 icr46.bit._ICR3
#define ICR46_ICR2 icr46.bit._ICR2
#define ICR46_ICR1 icr46.bit._ICR1
#define ICR46_ICR0 icr46.bit._ICR0
__IO_EXTERN ICR47STR icr47;  
#define ICR47 icr47.byte
#define ICR47_ICR4 icr47.bit._ICR4
#define ICR47_ICR3 icr47.bit._ICR3
#define ICR47_ICR2 icr47.bit._ICR2
#define ICR47_ICR1 icr47.bit._ICR1
#define ICR47_ICR0 icr47.bit._ICR0
__IO_EXTERN RSRRSTR rsrr;   /* Clock Control Unit */
#define RSRR rsrr.byte
#define RSRR_INIT rsrr.bit._INIT
#define RSRR_WDOG rsrr.bit._WDOG
#define RSRR_SRST rsrr.bit._SRST
#define RSRR_WT1 rsrr.bit._WT1
#define RSRR_WT0 rsrr.bit._WT0
#define RSRR_WT rsrr.bitc._WT
__IO_EXTERN STCRSTR stcr;  
#define STCR stcr.byte
#define STCR_STOP stcr.bit._STOP
#define STCR_SLEEP stcr.bit._SLEEP
#define STCR_HIZ stcr.bit._HIZ
#define STCR_SRST stcr.bit._SRST
#define STCR_OS1 stcr.bit._OS1
#define STCR_OS0 stcr.bit._OS0
#define STCR_OSCD2 stcr.bit._OSCD2
#define STCR_OSCD1 stcr.bit._OSCD1
#define STCR_OS stcr.bitc._OS
#define STCR_OSCD stcr.bitc._OSCD
__IO_EXTERN TBCRSTR tbcr;  
#define TBCR tbcr.byte
#define TBCR_TBIF tbcr.bit._TBIF
#define TBCR_TBIE tbcr.bit._TBIE
#define TBCR_TBC2 tbcr.bit._TBC2
#define TBCR_TBC1 tbcr.bit._TBC1
#define TBCR_TBC0 tbcr.bit._TBC0
#define TBCR_SYNCR tbcr.bit._SYNCR
#define TBCR_SYNCS tbcr.bit._SYNCS
#define TBCR_TBC tbcr.bitc._TBC
__IO_EXTERN CTBRSTR ctbr;  
#define CTBR ctbr.byte
#define CTBR_D7 ctbr.bit._D7
#define CTBR_D6 ctbr.bit._D6
#define CTBR_D5 ctbr.bit._D5
#define CTBR_D4 ctbr.bit._D4
#define CTBR_D3 ctbr.bit._D3
#define CTBR_D2 ctbr.bit._D2
#define CTBR_D1 ctbr.bit._D1
#define CTBR_D0 ctbr.bit._D0
__IO_EXTERN CLKRSTR clkr;  
#define CLKR clkr.byte
#define CLKR_PLL1S2 clkr.bit._PLL1S2
#define CLKR_PLL1S1 clkr.bit._PLL1S1
#define CLKR_PLL1S0 clkr.bit._PLL1S0
#define CLKR_PLL2EN clkr.bit._PLL2EN
#define CLKR_PLL1EN clkr.bit._PLL1EN
#define CLKR_CLKS1 clkr.bit._CLKS1
#define CLKR_CLKS0 clkr.bit._CLKS0
#define CLKR_CLKS clkr.bitc._CLKS
__IO_EXTERN WPRSTR wpr;  
#define WPR wpr.byte
#define WPR_D7 wpr.bit._D7
#define WPR_D6 wpr.bit._D6
#define WPR_D5 wpr.bit._D5
#define WPR_D4 wpr.bit._D4
#define WPR_D3 wpr.bit._D3
#define WPR_D2 wpr.bit._D2
#define WPR_D1 wpr.bit._D1
#define WPR_D0 wpr.bit._D0
__IO_EXTERN DIVR0STR divr0;  
#define DIVR0 divr0.byte
#define DIVR0_B3 divr0.bit._B3
#define DIVR0_B2 divr0.bit._B2
#define DIVR0_B1 divr0.bit._B1
#define DIVR0_B0 divr0.bit._B0
#define DIVR0_P3 divr0.bit._P3
#define DIVR0_P2 divr0.bit._P2
#define DIVR0_P1 divr0.bit._P1
#define DIVR0_P0 divr0.bit._P0
#define DIVR0_B divr0.bitc._B
#define DIVR0_P divr0.bitc._P
__IO_EXTERN DIVR1STR divr1;  
#define DIVR1 divr1.byte
#define DIVR1_T3 divr1.bit._T3
#define DIVR1_T2 divr1.bit._T2
#define DIVR1_T1 divr1.bit._T1
#define DIVR1_T0 divr1.bit._T0
#define DIVR1_T divr1.bitc._T
__IO_EXTERN OSCCRSTR osccr;  
#define OSCCR osccr.byte
#define OSCCR_OSCDS1 osccr.bit._OSCDS1
__IO_EXTERN OSCRSTR oscr;   /* Stb. Wait Timer */
#define OSCR oscr.byte
#define OSCR_WIF oscr.bit._WIF
#define OSCR_WIE oscr.bit._WIE
#define OSCR_WEN oscr.bit._WEN
#define OSCR_WS1 oscr.bit._WS1
#define OSCR_WS0 oscr.bit._WS0
#define OSCR_WCL oscr.bit._WCL
#define OSCR_WS oscr.bitc._WS
__IO_EXTERN CSVCRSTR csvcr;   /* Clock-Supervisor */
#define CSVCR csvcr.byte
#define CSVCR_MM csvcr.bit._MM
#define CSVCR_SM csvcr.bit._SM
#define CSVCR_RCE csvcr.bit._RCE
#define CSVCR_MSVE csvcr.bit._MSVE
#define CSVCR_SSVE csvcr.bit._SSVE
#define CSVCR_SRST csvcr.bit._SRST
__IO_EXTERN PPER0STR pper0;   /* Pull-Up/Down Enable Register */
#define PPER0 pper0.byte
#define PPER0_P07 pper0.bit._P07
#define PPER0_P06 pper0.bit._P06
#define PPER0_P05 pper0.bit._P05
#define PPER0_P04 pper0.bit._P04
#define PPER0_P03 pper0.bit._P03
#define PPER0_P02 pper0.bit._P02
#define PPER0_P01 pper0.bit._P01
#define PPER0_P00 pper0.bit._P00
__IO_EXTERN PPER1STR pper1;  
#define PPER1 pper1.byte
#define PPER1_P17 pper1.bit._P17
#define PPER1_P16 pper1.bit._P16
#define PPER1_P15 pper1.bit._P15
#define PPER1_P14 pper1.bit._P14
#define PPER1_P13 pper1.bit._P13
#define PPER1_P12 pper1.bit._P12
#define PPER1_P11 pper1.bit._P11
#define PPER1_P10 pper1.bit._P10
__IO_EXTERN PPER2STR pper2;  
#define PPER2 pper2.byte
#define PPER2_P27 pper2.bit._P27
#define PPER2_P26 pper2.bit._P26
#define PPER2_P25 pper2.bit._P25
#define PPER2_P24 pper2.bit._P24
#define PPER2_P23 pper2.bit._P23
#define PPER2_P22 pper2.bit._P22
#define PPER2_P21 pper2.bit._P21
#define PPER2_P20 pper2.bit._P20
__IO_EXTERN PPER3STR pper3;  
#define PPER3 pper3.byte
#define PPER3_P37 pper3.bit._P37
#define PPER3_P36 pper3.bit._P36
#define PPER3_P35 pper3.bit._P35
#define PPER3_P34 pper3.bit._P34
#define PPER3_P33 pper3.bit._P33
#define PPER3_P32 pper3.bit._P32
#define PPER3_P31 pper3.bit._P31
#define PPER3_P30 pper3.bit._P30
__IO_EXTERN PPER4STR pper4;  
#define PPER4 pper4.byte
#define PPER4_P43 pper4.bit._P43
#define PPER4_P42 pper4.bit._P42
#define PPER4_P41 pper4.bit._P41
#define PPER4_P40 pper4.bit._P40
__IO_EXTERN PPER5STR pper5;  
#define PPER5 pper5.byte
#define PPER5_P55 pper5.bit._P55
#define PPER5_P54 pper5.bit._P54
#define PPER5_P53 pper5.bit._P53
#define PPER5_P52 pper5.bit._P52
#define PPER5_P51 pper5.bit._P51
#define PPER5_P50 pper5.bit._P50
__IO_EXTERN PPER6STR pper6;  
#define PPER6 pper6.byte
#define PPER6_P67 pper6.bit._P67
#define PPER6_P66 pper6.bit._P66
#define PPER6_P65 pper6.bit._P65
#define PPER6_P64 pper6.bit._P64
#define PPER6_P63 pper6.bit._P63
#define PPER6_P62 pper6.bit._P62
#define PPER6_P61 pper6.bit._P61
#define PPER6_P60 pper6.bit._P60
__IO_EXTERN PPER7STR pper7;  
#define PPER7 pper7.byte
#define PPER7_P75 pper7.bit._P75
#define PPER7_P74 pper7.bit._P74
#define PPER7_P73 pper7.bit._P73
#define PPER7_P72 pper7.bit._P72
#define PPER7_P71 pper7.bit._P71
#define PPER7_P70 pper7.bit._P70
__IO_EXTERN PPER8STR pper8;  
#define PPER8 pper8.byte
#define PPER8_P87 pper8.bit._P87
#define PPER8_P86 pper8.bit._P86
#define PPER8_P85 pper8.bit._P85
#define PPER8_P84 pper8.bit._P84
#define PPER8_P83 pper8.bit._P83
#define PPER8_P82 pper8.bit._P82
#define PPER8_P81 pper8.bit._P81
#define PPER8_P80 pper8.bit._P80
__IO_EXTERN PPER9STR pper9;  
#define PPER9 pper9.byte
#define PPER9_P97 pper9.bit._P97
#define PPER9_P96 pper9.bit._P96
#define PPER9_P95 pper9.bit._P95
#define PPER9_P94 pper9.bit._P94
#define PPER9_P93 pper9.bit._P93
#define PPER9_P92 pper9.bit._P92
#define PPER9_P91 pper9.bit._P91
#define PPER9_P90 pper9.bit._P90
__IO_EXTERN PPERASTR ppera;  
#define PPERA ppera.byte
#define PPERA_PA1 ppera.bit._PA1
#define PPERA_PA0 ppera.bit._PA0
__IO_EXTERN PPERBSTR pperb;  
#define PPERB pperb.byte
#define PPERB_PB5 pperb.bit._PB5
#define PPERB_PB4 pperb.bit._PB4
#define PPERB_PB3 pperb.bit._PB3
#define PPERB_PB2 pperb.bit._PB2
#define PPERB_PB1 pperb.bit._PB1
#define PPERB_PB0 pperb.bit._PB0
__IO_EXTERN PPERCSTR pperc;  
#define PPERC pperc.byte
#define PPERC_PC7 pperc.bit._PC7
#define PPERC_PC6 pperc.bit._PC6
#define PPERC_PC5 pperc.bit._PC5
#define PPERC_PC4 pperc.bit._PC4
#define PPERC_PC3 pperc.bit._PC3
#define PPERC_PC2 pperc.bit._PC2
#define PPERC_PC1 pperc.bit._PC1
#define PPERC_PC0 pperc.bit._PC0
__IO_EXTERN PPERDSTR pperd;  
#define PPERD pperd.byte
#define PPERD_PD7 pperd.bit._PD7
#define PPERD_PD6 pperd.bit._PD6
#define PPERD_PD5 pperd.bit._PD5
#define PPERD_PD4 pperd.bit._PD4
#define PPERD_PD3 pperd.bit._PD3
#define PPERD_PD2 pperd.bit._PD2
#define PPERD_PD1 pperd.bit._PD1
#define PPERD_PD0 pperd.bit._PD0
__IO_EXTERN PPERESTR ppere;  
#define PPERE ppere.byte
#define PPERE_PE7 ppere.bit._PE7
#define PPERE_PE6 ppere.bit._PE6
#define PPERE_PE5 ppere.bit._PE5
#define PPERE_PE4 ppere.bit._PE4
#define PPERE_PE3 ppere.bit._PE3
#define PPERE_PE2 ppere.bit._PE2
#define PPERE_PE1 ppere.bit._PE1
#define PPERE_PE0 ppere.bit._PE0
__IO_EXTERN PPERFSTR pperf;  
#define PPERF pperf.byte
#define PPERF_PF7 pperf.bit._PF7
#define PPERF_PF6 pperf.bit._PF6
#define PPERF_PF5 pperf.bit._PF5
#define PPERF_PF4 pperf.bit._PF4
#define PPERF_PF3 pperf.bit._PF3
#define PPERF_PF2 pperf.bit._PF2
#define PPERF_PF1 pperf.bit._PF1
#define PPERF_PF0 pperf.bit._PF0
__IO_EXTERN PPERGSTR pperg;  
#define PPERG pperg.byte
#define PPERG_PG7 pperg.bit._PG7
#define PPERG_PG6 pperg.bit._PG6
#define PPERG_PG5 pperg.bit._PG5
#define PPERG_PG4 pperg.bit._PG4
#define PPERG_PG3 pperg.bit._PG3
#define PPERG_PG2 pperg.bit._PG2
#define PPERG_PG1 pperg.bit._PG1
#define PPERG_PG0 pperg.bit._PG0
__IO_EXTERN PPCR0STR ppcr0;   /* Pull-Up/Down  Control Register */
#define PPCR0 ppcr0.byte
#define PPCR0_P07 ppcr0.bit._P07
#define PPCR0_P06 ppcr0.bit._P06
#define PPCR0_P05 ppcr0.bit._P05
#define PPCR0_P04 ppcr0.bit._P04
#define PPCR0_P03 ppcr0.bit._P03
#define PPCR0_P02 ppcr0.bit._P02
#define PPCR0_P01 ppcr0.bit._P01
#define PPCR0_P00 ppcr0.bit._P00
__IO_EXTERN PPCR1STR ppcr1;  
#define PPCR1 ppcr1.byte
#define PPCR1_P17 ppcr1.bit._P17
#define PPCR1_P16 ppcr1.bit._P16
#define PPCR1_P15 ppcr1.bit._P15
#define PPCR1_P14 ppcr1.bit._P14
#define PPCR1_P13 ppcr1.bit._P13
#define PPCR1_P12 ppcr1.bit._P12
#define PPCR1_P11 ppcr1.bit._P11
#define PPCR1_P10 ppcr1.bit._P10
__IO_EXTERN PPCR2STR ppcr2;  
#define PPCR2 ppcr2.byte
#define PPCR2_P27 ppcr2.bit._P27
#define PPCR2_P26 ppcr2.bit._P26
#define PPCR2_P25 ppcr2.bit._P25
#define PPCR2_P24 ppcr2.bit._P24
#define PPCR2_P23 ppcr2.bit._P23
#define PPCR2_P22 ppcr2.bit._P22
#define PPCR2_P21 ppcr2.bit._P21
#define PPCR2_P20 ppcr2.bit._P20
__IO_EXTERN PPCR3STR ppcr3;  
#define PPCR3 ppcr3.byte
#define PPCR3_P37 ppcr3.bit._P37
#define PPCR3_P36 ppcr3.bit._P36
#define PPCR3_P35 ppcr3.bit._P35
#define PPCR3_P34 ppcr3.bit._P34
#define PPCR3_P33 ppcr3.bit._P33
#define PPCR3_P32 ppcr3.bit._P32
#define PPCR3_P31 ppcr3.bit._P31
#define PPCR3_P30 ppcr3.bit._P30
__IO_EXTERN PPCR4STR ppcr4;  
#define PPCR4 ppcr4.byte
#define PPCR4_P43 ppcr4.bit._P43
#define PPCR4_P42 ppcr4.bit._P42
#define PPCR4_P41 ppcr4.bit._P41
#define PPCR4_P40 ppcr4.bit._P40
__IO_EXTERN PPCR5STR ppcr5;  
#define PPCR5 ppcr5.byte
#define PPCR5_P55 ppcr5.bit._P55
#define PPCR5_P54 ppcr5.bit._P54
#define PPCR5_P53 ppcr5.bit._P53
#define PPCR5_P52 ppcr5.bit._P52
#define PPCR5_P51 ppcr5.bit._P51
#define PPCR5_P50 ppcr5.bit._P50
__IO_EXTERN PPCR6STR ppcr6;  
#define PPCR6 ppcr6.byte
#define PPCR6_P67 ppcr6.bit._P67
#define PPCR6_P66 ppcr6.bit._P66
#define PPCR6_P65 ppcr6.bit._P65
#define PPCR6_P64 ppcr6.bit._P64
#define PPCR6_P63 ppcr6.bit._P63
#define PPCR6_P62 ppcr6.bit._P62
#define PPCR6_P61 ppcr6.bit._P61
#define PPCR6_P60 ppcr6.bit._P60
__IO_EXTERN PPCR7STR ppcr7;  
#define PPCR7 ppcr7.byte
#define PPCR7_P75 ppcr7.bit._P75
#define PPCR7_P74 ppcr7.bit._P74
#define PPCR7_P73 ppcr7.bit._P73
#define PPCR7_P72 ppcr7.bit._P72
#define PPCR7_P71 ppcr7.bit._P71
#define PPCR7_P70 ppcr7.bit._P70
__IO_EXTERN PPCR8STR ppcr8;  
#define PPCR8 ppcr8.byte
#define PPCR8_P87 ppcr8.bit._P87
#define PPCR8_P86 ppcr8.bit._P86
#define PPCR8_P85 ppcr8.bit._P85
#define PPCR8_P84 ppcr8.bit._P84
#define PPCR8_P83 ppcr8.bit._P83
#define PPCR8_P82 ppcr8.bit._P82
#define PPCR8_P81 ppcr8.bit._P81
#define PPCR8_P80 ppcr8.bit._P80
__IO_EXTERN PPCR9STR ppcr9;  
#define PPCR9 ppcr9.byte
#define PPCR9_P97 ppcr9.bit._P97
#define PPCR9_P96 ppcr9.bit._P96
#define PPCR9_P95 ppcr9.bit._P95
#define PPCR9_P94 ppcr9.bit._P94
#define PPCR9_P93 ppcr9.bit._P93
#define PPCR9_P92 ppcr9.bit._P92
#define PPCR9_P91 ppcr9.bit._P91
#define PPCR9_P90 ppcr9.bit._P90
__IO_EXTERN PPCRASTR ppcra;  
#define PPCRA ppcra.byte
#define PPCRA_PA1 ppcra.bit._PA1
#define PPCRA_PA0 ppcra.bit._PA0
__IO_EXTERN PPCRBSTR ppcrb;  
#define PPCRB ppcrb.byte
#define PPCRB_PB5 ppcrb.bit._PB5
#define PPCRB_PB4 ppcrb.bit._PB4
#define PPCRB_PB3 ppcrb.bit._PB3
#define PPCRB_PB2 ppcrb.bit._PB2
#define PPCRB_PB1 ppcrb.bit._PB1
#define PPCRB_PB0 ppcrb.bit._PB0
__IO_EXTERN PPCRCSTR ppcrc;  
#define PPCRC ppcrc.byte
#define PPCRC_PC7 ppcrc.bit._PC7
#define PPCRC_PC6 ppcrc.bit._PC6
#define PPCRC_PC5 ppcrc.bit._PC5
#define PPCRC_PC4 ppcrc.bit._PC4
#define PPCRC_PC3 ppcrc.bit._PC3
#define PPCRC_PC2 ppcrc.bit._PC2
#define PPCRC_PC1 ppcrc.bit._PC1
#define PPCRC_PC0 ppcrc.bit._PC0
__IO_EXTERN PPCRDSTR ppcrd;  
#define PPCRD ppcrd.byte
#define PPCRD_PD7 ppcrd.bit._PD7
#define PPCRD_PD6 ppcrd.bit._PD6
#define PPCRD_PD5 ppcrd.bit._PD5
#define PPCRD_PD4 ppcrd.bit._PD4
#define PPCRD_PD3 ppcrd.bit._PD3
#define PPCRD_PD2 ppcrd.bit._PD2
#define PPCRD_PD1 ppcrd.bit._PD1
#define PPCRD_PD0 ppcrd.bit._PD0
__IO_EXTERN PPCRESTR ppcre;  
#define PPCRE ppcre.byte
#define PPCRE_PE7 ppcre.bit._PE7
#define PPCRE_PE6 ppcre.bit._PE6
#define PPCRE_PE5 ppcre.bit._PE5
#define PPCRE_PE4 ppcre.bit._PE4
#define PPCRE_PE3 ppcre.bit._PE3
#define PPCRE_PE2 ppcre.bit._PE2
#define PPCRE_PE1 ppcre.bit._PE1
#define PPCRE_PE0 ppcre.bit._PE0
__IO_EXTERN PPCRFSTR ppcrf;  
#define PPCRF ppcrf.byte
#define PPCRF_PF7 ppcrf.bit._PF7
#define PPCRF_PF6 ppcrf.bit._PF6
#define PPCRF_PF5 ppcrf.bit._PF5
#define PPCRF_PF4 ppcrf.bit._PF4
#define PPCRF_PF3 ppcrf.bit._PF3
#define PPCRF_PF2 ppcrf.bit._PF2
#define PPCRF_PF1 ppcrf.bit._PF1
#define PPCRF_PF0 ppcrf.bit._PF0
__IO_EXTERN PPCRGSTR ppcrg;  
#define PPCRG ppcrg.byte
#define PPCRG_PG7 ppcrg.bit._PG7
#define PPCRG_PG6 ppcrg.bit._PG6
#define PPCRG_PG5 ppcrg.bit._PG5
#define PPCRG_PG4 ppcrg.bit._PG4
#define PPCRG_PG3 ppcrg.bit._PG3
#define PPCRG_PG2 ppcrg.bit._PG2
#define PPCRG_PG1 ppcrg.bit._PG1
#define PPCRG_PG0 ppcrg.bit._PG0
__IO_EXTERN PILR0STR pilr0;   /* Port Input Level select Registers */
#define PILR0 pilr0.byte
#define PILR0_P07 pilr0.bit._P07
#define PILR0_P06 pilr0.bit._P06
#define PILR0_P05 pilr0.bit._P05
#define PILR0_P04 pilr0.bit._P04
#define PILR0_P03 pilr0.bit._P03
#define PILR0_P02 pilr0.bit._P02
#define PILR0_P01 pilr0.bit._P01
#define PILR0_P00 pilr0.bit._P00
__IO_EXTERN PILR1STR pilr1;  
#define PILR1 pilr1.byte
#define PILR1_P17 pilr1.bit._P17
#define PILR1_P16 pilr1.bit._P16
#define PILR1_P15 pilr1.bit._P15
#define PILR1_P14 pilr1.bit._P14
#define PILR1_P13 pilr1.bit._P13
#define PILR1_P12 pilr1.bit._P12
#define PILR1_P11 pilr1.bit._P11
#define PILR1_P10 pilr1.bit._P10
__IO_EXTERN PILR2STR pilr2;  
#define PILR2 pilr2.byte
#define PILR2_P27 pilr2.bit._P27
#define PILR2_P26 pilr2.bit._P26
#define PILR2_P25 pilr2.bit._P25
#define PILR2_P24 pilr2.bit._P24
#define PILR2_P23 pilr2.bit._P23
#define PILR2_P22 pilr2.bit._P22
#define PILR2_P21 pilr2.bit._P21
#define PILR2_P20 pilr2.bit._P20
__IO_EXTERN PILR3STR pilr3;  
#define PILR3 pilr3.byte
#define PILR3_P37 pilr3.bit._P37
#define PILR3_P36 pilr3.bit._P36
#define PILR3_P35 pilr3.bit._P35
#define PILR3_P34 pilr3.bit._P34
#define PILR3_P33 pilr3.bit._P33
#define PILR3_P32 pilr3.bit._P32
#define PILR3_P31 pilr3.bit._P31
#define PILR3_P30 pilr3.bit._P30
__IO_EXTERN PILR4STR pilr4;  
#define PILR4 pilr4.byte
#define PILR4_P47 pilr4.bit._P47
#define PILR4_P46 pilr4.bit._P46
#define PILR4_P45 pilr4.bit._P45
#define PILR4_P44 pilr4.bit._P44
#define PILR4_P43 pilr4.bit._P43
#define PILR4_P42 pilr4.bit._P42
#define PILR4_P41 pilr4.bit._P41
#define PILR4_P40 pilr4.bit._P40
__IO_EXTERN PILR5STR pilr5;  
#define PILR5 pilr5.byte
#define PILR5_P57 pilr5.bit._P57
#define PILR5_P56 pilr5.bit._P56
#define PILR5_P55 pilr5.bit._P55
#define PILR5_P54 pilr5.bit._P54
#define PILR5_P53 pilr5.bit._P53
#define PILR5_P52 pilr5.bit._P52
#define PILR5_P51 pilr5.bit._P51
#define PILR5_P50 pilr5.bit._P50
__IO_EXTERN PILR6STR pilr6;  
#define PILR6 pilr6.byte
#define PILR6_P67 pilr6.bit._P67
#define PILR6_P66 pilr6.bit._P66
#define PILR6_P65 pilr6.bit._P65
#define PILR6_P64 pilr6.bit._P64
#define PILR6_P63 pilr6.bit._P63
#define PILR6_P62 pilr6.bit._P62
#define PILR6_P61 pilr6.bit._P61
#define PILR6_P60 pilr6.bit._P60
__IO_EXTERN PILR7STR pilr7;  
#define PILR7 pilr7.byte
#define PILR7_P77 pilr7.bit._P77
#define PILR7_P76 pilr7.bit._P76
#define PILR7_P75 pilr7.bit._P75
#define PILR7_P74 pilr7.bit._P74
#define PILR7_P73 pilr7.bit._P73
#define PILR7_P72 pilr7.bit._P72
#define PILR7_P71 pilr7.bit._P71
#define PILR7_P70 pilr7.bit._P70
__IO_EXTERN PILR8STR pilr8;  
#define PILR8 pilr8.byte
#define PILR8_P87 pilr8.bit._P87
#define PILR8_P86 pilr8.bit._P86
#define PILR8_P85 pilr8.bit._P85
#define PILR8_P84 pilr8.bit._P84
#define PILR8_P83 pilr8.bit._P83
#define PILR8_P82 pilr8.bit._P82
#define PILR8_P81 pilr8.bit._P81
#define PILR8_P80 pilr8.bit._P80
__IO_EXTERN PILR9STR pilr9;  
#define PILR9 pilr9.byte
#define PILR9_P97 pilr9.bit._P97
#define PILR9_P96 pilr9.bit._P96
#define PILR9_P95 pilr9.bit._P95
#define PILR9_P94 pilr9.bit._P94
#define PILR9_P93 pilr9.bit._P93
#define PILR9_P92 pilr9.bit._P92
#define PILR9_P91 pilr9.bit._P91
#define PILR9_P90 pilr9.bit._P90
__IO_EXTERN PILRASTR pilra;  
#define PILRA pilra.byte
#define PILRA_PA1 pilra.bit._PA1
#define PILRA_PA0 pilra.bit._PA0
__IO_EXTERN PILRBSTR pilrb;  
#define PILRB pilrb.byte
#define PILRB_PB5 pilrb.bit._PB5
#define PILRB_PB4 pilrb.bit._PB4
#define PILRB_PB3 pilrb.bit._PB3
#define PILRB_PB2 pilrb.bit._PB2
#define PILRB_PB1 pilrb.bit._PB1
#define PILRB_PB0 pilrb.bit._PB0
__IO_EXTERN PILRCSTR pilrc;  
#define PILRC pilrc.byte
#define PILRC_PC7 pilrc.bit._PC7
#define PILRC_PC6 pilrc.bit._PC6
#define PILRC_PC5 pilrc.bit._PC5
#define PILRC_PC4 pilrc.bit._PC4
#define PILRC_PC3 pilrc.bit._PC3
#define PILRC_PC2 pilrc.bit._PC2
#define PILRC_PC1 pilrc.bit._PC1
#define PILRC_PC0 pilrc.bit._PC0
__IO_EXTERN PILRDSTR pilrd;  
#define PILRD pilrd.byte
#define PILRD_PD7 pilrd.bit._PD7
#define PILRD_PD6 pilrd.bit._PD6
#define PILRD_PD5 pilrd.bit._PD5
#define PILRD_PD4 pilrd.bit._PD4
#define PILRD_PD3 pilrd.bit._PD3
#define PILRD_PD2 pilrd.bit._PD2
#define PILRD_PD1 pilrd.bit._PD1
#define PILRD_PD0 pilrd.bit._PD0
__IO_EXTERN PILRESTR pilre;  
#define PILRE pilre.byte
#define PILRE_PE7 pilre.bit._PE7
#define PILRE_PE6 pilre.bit._PE6
#define PILRE_PE5 pilre.bit._PE5
#define PILRE_PE4 pilre.bit._PE4
#define PILRE_PE3 pilre.bit._PE3
#define PILRE_PE2 pilre.bit._PE2
#define PILRE_PE1 pilre.bit._PE1
#define PILRE_PE0 pilre.bit._PE0
__IO_EXTERN PILRFSTR pilrf;  
#define PILRF pilrf.byte
#define PILRF_PF7 pilrf.bit._PF7
#define PILRF_PF6 pilrf.bit._PF6
#define PILRF_PF5 pilrf.bit._PF5
#define PILRF_PF4 pilrf.bit._PF4
#define PILRF_PF3 pilrf.bit._PF3
#define PILRF_PF2 pilrf.bit._PF2
#define PILRF_PF1 pilrf.bit._PF1
#define PILRF_PF0 pilrf.bit._PF0
__IO_EXTERN PILRGSTR pilrg;  
#define PILRG pilrg.byte
#define PILRG_PG7 pilrg.bit._PG7
#define PILRG_PG6 pilrg.bit._PG6
#define PILRG_PG5 pilrg.bit._PG5
#define PILRG_PG4 pilrg.bit._PG4
#define PILRG_PG3 pilrg.bit._PG3
#define PILRG_PG2 pilrg.bit._PG2
#define PILRG_PG1 pilrg.bit._PG1
#define PILRG_PG0 pilrg.bit._PG0
__IO_EXTERN IBCR0STR ibcr0;   /* I2C 0 */
#define IBCR0 ibcr0.byte
#define IBCR0_BER ibcr0.bit._BER
#define IBCR0_BEIE ibcr0.bit._BEIE
#define IBCR0_SCC ibcr0.bit._SCC
#define IBCR0_MSS ibcr0.bit._MSS
#define IBCR0_ACK ibcr0.bit._ACK
#define IBCR0_GCAA ibcr0.bit._GCAA
#define IBCR0_INTE ibcr0.bit._INTE
#define IBCR0_INT ibcr0.bit._INT
__IO_EXTERN IBSR0STR ibsr0;  
#define IBSR0 ibsr0.byte
#define IBSR0_BB ibsr0.bit._BB
#define IBSR0_RSC ibsr0.bit._RSC
#define IBSR0_AL ibsr0.bit._AL
#define IBSR0_LRB ibsr0.bit._LRB
#define IBSR0_TRX ibsr0.bit._TRX
#define IBSR0_AAS ibsr0.bit._AAS
#define IBSR0_GCA ibsr0.bit._GCA
#define IBSR0_ADT ibsr0.bit._ADT
__IO_EXTERN ITBAH0STR itbah0;  
#define ITBAH0 itbah0.byte
#define ITBAH0_TA9 itbah0.bit._TA9
#define ITBAH0_TA8 itbah0.bit._TA8
__IO_EXTERN ITBAL0STR itbal0;  
#define ITBAL0 itbal0.byte
#define ITBAL0_TA7 itbal0.bit._TA7
#define ITBAL0_TA6 itbal0.bit._TA6
#define ITBAL0_TA5 itbal0.bit._TA5
#define ITBAL0_TA4 itbal0.bit._TA4
#define ITBAL0_TA3 itbal0.bit._TA3
#define ITBAL0_TA2 itbal0.bit._TA2
#define ITBAL0_TA1 itbal0.bit._TA1
#define ITBAL0_TA0 itbal0.bit._TA0
__IO_EXTERN ITMKH0STR itmkh0;  
#define ITMKH0 itmkh0.byte
#define ITMKH0_ENTB itmkh0.bit._ENTB
#define ITMKH0_RAL itmkh0.bit._RAL
#define ITMKH0_TM9 itmkh0.bit._TM9
#define ITMKH0_TM8 itmkh0.bit._TM8
__IO_EXTERN ITMKL0STR itmkl0;  
#define ITMKL0 itmkl0.byte
#define ITMKL0_TM7 itmkl0.bit._TM7
#define ITMKL0_TM6 itmkl0.bit._TM6
#define ITMKL0_TM5 itmkl0.bit._TM5
#define ITMKL0_TM4 itmkl0.bit._TM4
#define ITMKL0_TM3 itmkl0.bit._TM3
#define ITMKL0_TM2 itmkl0.bit._TM2
#define ITMKL0_TM1 itmkl0.bit._TM1
#define ITMKL0_TM0 itmkl0.bit._TM0
__IO_EXTERN ISMK0STR ismk0;  
#define ISMK0 ismk0.byte
#define ISMK0_ENSB ismk0.bit._ENSB
#define ISMK0_SM6 ismk0.bit._SM6
#define ISMK0_SM5 ismk0.bit._SM5
#define ISMK0_SM4 ismk0.bit._SM4
#define ISMK0_SM3 ismk0.bit._SM3
#define ISMK0_SM2 ismk0.bit._SM2
#define ISMK0_SM1 ismk0.bit._SM1
#define ISMK0_SM0 ismk0.bit._SM0
__IO_EXTERN ISBA0STR isba0;  
#define ISBA0 isba0.byte
#define ISBA0_SA6 isba0.bit._SA6
#define ISBA0_SA5 isba0.bit._SA5
#define ISBA0_SA4 isba0.bit._SA4
#define ISBA0_SA3 isba0.bit._SA3
#define ISBA0_SA2 isba0.bit._SA2
#define ISBA0_SA1 isba0.bit._SA1
#define ISBA0_SA0 isba0.bit._SA0
__IO_EXTERN IDAR0STR idar0;  
#define IDAR0 idar0.byte
#define IDAR0_D7 idar0.bit._D7
#define IDAR0_D6 idar0.bit._D6
#define IDAR0_D5 idar0.bit._D5
#define IDAR0_D4 idar0.bit._D4
#define IDAR0_D3 idar0.bit._D3
#define IDAR0_D2 idar0.bit._D2
#define IDAR0_D1 idar0.bit._D1
#define IDAR0_D0 idar0.bit._D0
__IO_EXTERN ICCR0STR iccr0;  
#define ICCR0 iccr0.byte
#define ICCR0_NSF iccr0.bit._NSF
#define ICCR0_EN iccr0.bit._EN
#define ICCR0_CS4 iccr0.bit._CS4
#define ICCR0_CS3 iccr0.bit._CS3
#define ICCR0_CS2 iccr0.bit._CS2
#define ICCR0_CS1 iccr0.bit._CS1
#define ICCR0_CS0 iccr0.bit._CS0
#define ICCR0_CS iccr0.bitc._CS
__IO_EXTERN IBCR1STR ibcr1;   /* I2C 1 */
#define IBCR1 ibcr1.byte
#define IBCR1_BER ibcr1.bit._BER
#define IBCR1_BEIE ibcr1.bit._BEIE
#define IBCR1_SCC ibcr1.bit._SCC
#define IBCR1_MSS ibcr1.bit._MSS
#define IBCR1_ACK ibcr1.bit._ACK
#define IBCR1_GCAA ibcr1.bit._GCAA
#define IBCR1_INTE ibcr1.bit._INTE
#define IBCR1_INT ibcr1.bit._INT
__IO_EXTERN IBSR1STR ibsr1;  
#define IBSR1 ibsr1.byte
#define IBSR1_BB ibsr1.bit._BB
#define IBSR1_RSC ibsr1.bit._RSC
#define IBSR1_AL ibsr1.bit._AL
#define IBSR1_LRB ibsr1.bit._LRB
#define IBSR1_TRX ibsr1.bit._TRX
#define IBSR1_AAS ibsr1.bit._AAS
#define IBSR1_GCA ibsr1.bit._GCA
#define IBSR1_ADT ibsr1.bit._ADT
__IO_EXTERN ITBAH1STR itbah1;  
#define ITBAH1 itbah1.byte
#define ITBAH1_TA9 itbah1.bit._TA9
#define ITBAH1_TA8 itbah1.bit._TA8
__IO_EXTERN ITBAL1STR itbal1;  
#define ITBAL1 itbal1.byte
#define ITBAL1_TA7 itbal1.bit._TA7
#define ITBAL1_TA6 itbal1.bit._TA6
#define ITBAL1_TA5 itbal1.bit._TA5
#define ITBAL1_TA4 itbal1.bit._TA4
#define ITBAL1_TA3 itbal1.bit._TA3
#define ITBAL1_TA2 itbal1.bit._TA2
#define ITBAL1_TA1 itbal1.bit._TA1
#define ITBAL1_TA0 itbal1.bit._TA0
__IO_EXTERN ITMKH1STR itmkh1;  
#define ITMKH1 itmkh1.byte
#define ITMKH1_ENTB itmkh1.bit._ENTB
#define ITMKH1_RAL itmkh1.bit._RAL
#define ITMKH1_TM9 itmkh1.bit._TM9
#define ITMKH1_TM8 itmkh1.bit._TM8
__IO_EXTERN ITMKL1STR itmkl1;  
#define ITMKL1 itmkl1.byte
#define ITMKL1_TM7 itmkl1.bit._TM7
#define ITMKL1_TM6 itmkl1.bit._TM6
#define ITMKL1_TM5 itmkl1.bit._TM5
#define ITMKL1_TM4 itmkl1.bit._TM4
#define ITMKL1_TM3 itmkl1.bit._TM3
#define ITMKL1_TM2 itmkl1.bit._TM2
#define ITMKL1_TM1 itmkl1.bit._TM1
#define ITMKL1_TM0 itmkl1.bit._TM0
__IO_EXTERN ISMK1STR ismk1;  
#define ISMK1 ismk1.byte
#define ISMK1_ENSB ismk1.bit._ENSB
#define ISMK1_SM6 ismk1.bit._SM6
#define ISMK1_SM5 ismk1.bit._SM5
#define ISMK1_SM4 ismk1.bit._SM4
#define ISMK1_SM3 ismk1.bit._SM3
#define ISMK1_SM2 ismk1.bit._SM2
#define ISMK1_SM1 ismk1.bit._SM1
#define ISMK1_SM0 ismk1.bit._SM0
__IO_EXTERN ISBA1STR isba1;  
#define ISBA1 isba1.byte
#define ISBA1_SA6 isba1.bit._SA6
#define ISBA1_SA5 isba1.bit._SA5
#define ISBA1_SA4 isba1.bit._SA4
#define ISBA1_SA3 isba1.bit._SA3
#define ISBA1_SA2 isba1.bit._SA2
#define ISBA1_SA1 isba1.bit._SA1
#define ISBA1_SA0 isba1.bit._SA0
__IO_EXTERN IDAR1STR idar1;  
#define IDAR1 idar1.byte
#define IDAR1_D7 idar1.bit._D7
#define IDAR1_D6 idar1.bit._D6
#define IDAR1_D5 idar1.bit._D5
#define IDAR1_D4 idar1.bit._D4
#define IDAR1_D3 idar1.bit._D3
#define IDAR1_D2 idar1.bit._D2
#define IDAR1_D1 idar1.bit._D1
#define IDAR1_D0 idar1.bit._D0
__IO_EXTERN ICCR1STR iccr1;  
#define ICCR1 iccr1.byte
#define ICCR1_NSF iccr1.bit._NSF
#define ICCR1_EN iccr1.bit._EN
#define ICCR1_CS4 iccr1.bit._CS4
#define ICCR1_CS3 iccr1.bit._CS3
#define ICCR1_CS2 iccr1.bit._CS2
#define ICCR1_CS1 iccr1.bit._CS1
#define ICCR1_CS0 iccr1.bit._CS0
#define ICCR1_CS iccr1.bitc._CS
__IO_EXTERN IBCR2STR ibcr2;   /* I2C 2 */
#define IBCR2 ibcr2.byte
#define IBCR2_BER ibcr2.bit._BER
#define IBCR2_BEIE ibcr2.bit._BEIE
#define IBCR2_SCC ibcr2.bit._SCC
#define IBCR2_MSS ibcr2.bit._MSS
#define IBCR2_ACK ibcr2.bit._ACK
#define IBCR2_GCAA ibcr2.bit._GCAA
#define IBCR2_INTE ibcr2.bit._INTE
#define IBCR2_INT ibcr2.bit._INT
__IO_EXTERN IBSR2STR ibsr2;  
#define IBSR2 ibsr2.byte
#define IBSR2_BB ibsr2.bit._BB
#define IBSR2_RSC ibsr2.bit._RSC
#define IBSR2_AL ibsr2.bit._AL
#define IBSR2_LRB ibsr2.bit._LRB
#define IBSR2_TRX ibsr2.bit._TRX
#define IBSR2_AAS ibsr2.bit._AAS
#define IBSR2_GCA ibsr2.bit._GCA
#define IBSR2_ADT ibsr2.bit._ADT
__IO_EXTERN ITBAH2STR itbah2;  
#define ITBAH2 itbah2.byte
#define ITBAH2_TA9 itbah2.bit._TA9
#define ITBAH2_TA8 itbah2.bit._TA8
__IO_EXTERN ITBAL2STR itbal2;  
#define ITBAL2 itbal2.byte
#define ITBAL2_TA7 itbal2.bit._TA7
#define ITBAL2_TA6 itbal2.bit._TA6
#define ITBAL2_TA5 itbal2.bit._TA5
#define ITBAL2_TA4 itbal2.bit._TA4
#define ITBAL2_TA3 itbal2.bit._TA3
#define ITBAL2_TA2 itbal2.bit._TA2
#define ITBAL2_TA1 itbal2.bit._TA1
#define ITBAL2_TA0 itbal2.bit._TA0
__IO_EXTERN ITMKH2STR itmkh2;  
#define ITMKH2 itmkh2.byte
#define ITMKH2_ENTB itmkh2.bit._ENTB
#define ITMKH2_RAL itmkh2.bit._RAL
#define ITMKH2_TM9 itmkh2.bit._TM9
#define ITMKH2_TM8 itmkh2.bit._TM8
__IO_EXTERN ITMKL2STR itmkl2;  
#define ITMKL2 itmkl2.byte
#define ITMKL2_TM7 itmkl2.bit._TM7
#define ITMKL2_TM6 itmkl2.bit._TM6
#define ITMKL2_TM5 itmkl2.bit._TM5
#define ITMKL2_TM4 itmkl2.bit._TM4
#define ITMKL2_TM3 itmkl2.bit._TM3
#define ITMKL2_TM2 itmkl2.bit._TM2
#define ITMKL2_TM1 itmkl2.bit._TM1
#define ITMKL2_TM0 itmkl2.bit._TM0
__IO_EXTERN ISMK2STR ismk2;  
#define ISMK2 ismk2.byte
#define ISMK2_ENSB ismk2.bit._ENSB
#define ISMK2_SM6 ismk2.bit._SM6
#define ISMK2_SM5 ismk2.bit._SM5
#define ISMK2_SM4 ismk2.bit._SM4
#define ISMK2_SM3 ismk2.bit._SM3
#define ISMK2_SM2 ismk2.bit._SM2
#define ISMK2_SM1 ismk2.bit._SM1
#define ISMK2_SM0 ismk2.bit._SM0
__IO_EXTERN ISBA2STR isba2;  
#define ISBA2 isba2.byte
#define ISBA2_SA6 isba2.bit._SA6
#define ISBA2_SA5 isba2.bit._SA5
#define ISBA2_SA4 isba2.bit._SA4
#define ISBA2_SA3 isba2.bit._SA3
#define ISBA2_SA2 isba2.bit._SA2
#define ISBA2_SA1 isba2.bit._SA1
#define ISBA2_SA0 isba2.bit._SA0
__IO_EXTERN IDAR2STR idar2;  
#define IDAR2 idar2.byte
#define IDAR2_D7 idar2.bit._D7
#define IDAR2_D6 idar2.bit._D6
#define IDAR2_D5 idar2.bit._D5
#define IDAR2_D4 idar2.bit._D4
#define IDAR2_D3 idar2.bit._D3
#define IDAR2_D2 idar2.bit._D2
#define IDAR2_D1 idar2.bit._D1
#define IDAR2_D0 idar2.bit._D0
__IO_EXTERN ICCR2STR iccr2;  
#define ICCR2 iccr2.byte
#define ICCR2_NSF iccr2.bit._NSF
#define ICCR2_EN iccr2.bit._EN
#define ICCR2_CS4 iccr2.bit._CS4
#define ICCR2_CS3 iccr2.bit._CS3
#define ICCR2_CS2 iccr2.bit._CS2
#define ICCR2_CS1 iccr2.bit._CS1
#define ICCR2_CS0 iccr2.bit._CS0
#define ICCR2_CS iccr2.bitc._CS
__IO_EXTERN HWDCSSTR hwdcs;   /* Hardware-Watchdog */
#define HWDCS hwdcs.byte
#define HWDCS_CL hwdcs.bit._CL
#define HWDCS_CPUF hwdcs.bit._CPUF
__IO_EXTERN EPFR0STR epfr0;   /* Extra Port Function Register */
#define EPFR0 epfr0.byte
__IO_EXTERN EPFR1STR epfr1;  
#define EPFR1 epfr1.byte
#define EPFR1_F11 epfr1.bit._F11
__IO_EXTERN EPFR2STR epfr2;  
#define EPFR2 epfr2.byte
#define EPFR2_F27 epfr2.bit._F27
#define EPFR2_F26 epfr2.bit._F26
#define EPFR2_F25 epfr2.bit._F25
#define EPFR2_F24 epfr2.bit._F24
#define EPFR2_F23 epfr2.bit._F23
#define EPFR2_F22 epfr2.bit._F22
#define EPFR2_F21 epfr2.bit._F21
#define EPFR2_F20 epfr2.bit._F20
__IO_EXTERN EPFR3STR epfr3;  
#define EPFR3 epfr3.byte
#define EPFR3_F37 epfr3.bit._F37
#define EPFR3_F36 epfr3.bit._F36
#define EPFR3_F35 epfr3.bit._F35
#define EPFR3_F34 epfr3.bit._F34
#define EPFR3_F33 epfr3.bit._F33
#define EPFR3_F32 epfr3.bit._F32
#define EPFR3_F31 epfr3.bit._F31
#define EPFR3_F30 epfr3.bit._F30
__IO_EXTERN EPFR4STR epfr4;  
#define EPFR4 epfr4.byte
#define EPFR4_F43 epfr4.bit._F43
#define EPFR4_F42 epfr4.bit._F42
__IO_EXTERN IO_BYTE epfr5;  
#define EPFR5 epfr5
__IO_EXTERN IO_BYTE epfr6;  
#define EPFR6 epfr6
__IO_EXTERN IO_BYTE epfr7;  
#define EPFR7 epfr7
__IO_EXTERN EPFR8STR epfr8;  
#define EPFR8 epfr8.byte
#define EPFR8_F83 epfr8.bit._F83
#define EPFR8_F81 epfr8.bit._F81
__IO_EXTERN EPFR9STR epfr9;  
#define EPFR9 epfr9.byte
#define EPFR9_F93 epfr9.bit._F93
#define EPFR9_F92 epfr9.bit._F92
#define EPFR9_F91 epfr9.bit._F91
#define EPFR9_F90 epfr9.bit._F90
__IO_EXTERN IO_BYTE epfra;  
#define EPFRA epfra
__IO_EXTERN EPFRBSTR epfrb;  
#define EPFRB epfrb.byte
#define EPFRB_FB5 epfrb.bit._FB5
#define EPFRB_FB4 epfrb.bit._FB4
#define EPFRB_FB3 epfrb.bit._FB3
#define EPFRB_FB2 epfrb.bit._FB2
#define EPFRB_FB1 epfrb.bit._FB1
#define EPFRB_FB0 epfrb.bit._FB0
__IO_EXTERN IO_BYTE epfrc;  
#define EPFRC epfrc
__IO_EXTERN IO_BYTE epfrd;  
#define EPFRD epfrd
__IO_EXTERN EPFRESTR epfre;  
#define EPFRE epfre.byte
#define EPFRE_FE7 epfre.bit._FE7
#define EPFRE_FE6 epfre.bit._FE6
#define EPFRE_FE5 epfre.bit._FE5
#define EPFRE_FE4 epfre.bit._FE4
#define EPFRE_FE3 epfre.bit._FE3
#define EPFRE_FE2 epfre.bit._FE2
#define EPFRE_FE1 epfre.bit._FE1
#define EPFRE_FE0 epfre.bit._FE0
__IO_EXTERN EPFRFSTR epfrf;  
#define EPFRF epfrf.byte
#define EPFRF_FF7 epfrf.bit._FF7
#define EPFRF_FF6 epfrf.bit._FF6
#define EPFRF_FF5 epfrf.bit._FF5
#define EPFRF_FF4 epfrf.bit._FF4
#define EPFRF_FF3 epfrf.bit._FF3
#define EPFRF_FF2 epfrf.bit._FF2
#define EPFRF_FF1 epfrf.bit._FF1
#define EPFRF_FF0 epfrf.bit._FF0
__IO_EXTERN IO_BYTE epfrg;  
#define EPFRG epfrg
__IO_EXTERN PIDR0STR pidr0;   /* Port Input Direct data Registers */
#define PIDR0 pidr0.byte
#define PIDR0_D07 pidr0.bit._D07
#define PIDR0_D06 pidr0.bit._D06
#define PIDR0_D05 pidr0.bit._D05
#define PIDR0_D04 pidr0.bit._D04
#define PIDR0_D03 pidr0.bit._D03
#define PIDR0_D02 pidr0.bit._D02
#define PIDR0_D01 pidr0.bit._D01
#define PIDR0_D00 pidr0.bit._D00
__IO_EXTERN PIDR1STR pidr1;  
#define PIDR1 pidr1.byte
#define PIDR1_D17 pidr1.bit._D17
#define PIDR1_D16 pidr1.bit._D16
#define PIDR1_D15 pidr1.bit._D15
#define PIDR1_D14 pidr1.bit._D14
#define PIDR1_D13 pidr1.bit._D13
#define PIDR1_D12 pidr1.bit._D12
#define PIDR1_D11 pidr1.bit._D11
#define PIDR1_D10 pidr1.bit._D10
__IO_EXTERN PIDR2STR pidr2;  
#define PIDR2 pidr2.byte
#define PIDR2_D27 pidr2.bit._D27
#define PIDR2_D26 pidr2.bit._D26
#define PIDR2_D25 pidr2.bit._D25
#define PIDR2_D24 pidr2.bit._D24
#define PIDR2_D23 pidr2.bit._D23
#define PIDR2_D22 pidr2.bit._D22
#define PIDR2_D21 pidr2.bit._D21
#define PIDR2_D20 pidr2.bit._D20
__IO_EXTERN PIDR3STR pidr3;  
#define PIDR3 pidr3.byte
#define PIDR3_D37 pidr3.bit._D37
#define PIDR3_D36 pidr3.bit._D36
#define PIDR3_D35 pidr3.bit._D35
#define PIDR3_D34 pidr3.bit._D34
#define PIDR3_D33 pidr3.bit._D33
#define PIDR3_D32 pidr3.bit._D32
#define PIDR3_D31 pidr3.bit._D31
#define PIDR3_D30 pidr3.bit._D30
__IO_EXTERN PIDR4STR pidr4;  
#define PIDR4 pidr4.byte
#define PIDR4_D47 pidr4.bit._D47
#define PIDR4_D46 pidr4.bit._D46
#define PIDR4_D45 pidr4.bit._D45
#define PIDR4_D44 pidr4.bit._D44
#define PIDR4_D43 pidr4.bit._D43
#define PIDR4_D42 pidr4.bit._D42
#define PIDR4_D41 pidr4.bit._D41
#define PIDR4_D40 pidr4.bit._D40
__IO_EXTERN PIDR5STR pidr5;  
#define PIDR5 pidr5.byte
#define PIDR5_D57 pidr5.bit._D57
#define PIDR5_D56 pidr5.bit._D56
#define PIDR5_D55 pidr5.bit._D55
#define PIDR5_D54 pidr5.bit._D54
#define PIDR5_D53 pidr5.bit._D53
#define PIDR5_D52 pidr5.bit._D52
#define PIDR5_D51 pidr5.bit._D51
#define PIDR5_D50 pidr5.bit._D50
__IO_EXTERN PIDR6STR pidr6;  
#define PIDR6 pidr6.byte
#define PIDR6_D67 pidr6.bit._D67
#define PIDR6_D66 pidr6.bit._D66
#define PIDR6_D65 pidr6.bit._D65
#define PIDR6_D64 pidr6.bit._D64
#define PIDR6_D63 pidr6.bit._D63
#define PIDR6_D62 pidr6.bit._D62
#define PIDR6_D61 pidr6.bit._D61
#define PIDR6_D60 pidr6.bit._D60
__IO_EXTERN PIDR7STR pidr7;  
#define PIDR7 pidr7.byte
#define PIDR7_D77 pidr7.bit._D77
#define PIDR7_D76 pidr7.bit._D76
#define PIDR7_D75 pidr7.bit._D75
#define PIDR7_D74 pidr7.bit._D74
#define PIDR7_D73 pidr7.bit._D73
#define PIDR7_D72 pidr7.bit._D72
#define PIDR7_D71 pidr7.bit._D71
#define PIDR7_D70 pidr7.bit._D70
__IO_EXTERN PIDR8STR pidr8;  
#define PIDR8 pidr8.byte
#define PIDR8_D87 pidr8.bit._D87
#define PIDR8_D86 pidr8.bit._D86
#define PIDR8_D85 pidr8.bit._D85
#define PIDR8_D84 pidr8.bit._D84
#define PIDR8_D83 pidr8.bit._D83
#define PIDR8_D82 pidr8.bit._D82
#define PIDR8_D81 pidr8.bit._D81
#define PIDR8_D80 pidr8.bit._D80
__IO_EXTERN PIDR9STR pidr9;  
#define PIDR9 pidr9.byte
#define PIDR9_D97 pidr9.bit._D97
#define PIDR9_D96 pidr9.bit._D96
#define PIDR9_D95 pidr9.bit._D95
#define PIDR9_D94 pidr9.bit._D94
#define PIDR9_D93 pidr9.bit._D93
#define PIDR9_D92 pidr9.bit._D92
#define PIDR9_D91 pidr9.bit._D91
#define PIDR9_D90 pidr9.bit._D90
__IO_EXTERN PIDRASTR pidra;  
#define PIDRA pidra.byte
#define PIDRA_DA1 pidra.bit._DA1
#define PIDRA_DA0 pidra.bit._DA0
__IO_EXTERN PIDRBSTR pidrb;  
#define PIDRB pidrb.byte
#define PIDRB_DB5 pidrb.bit._DB5
#define PIDRB_DB4 pidrb.bit._DB4
#define PIDRB_DB3 pidrb.bit._DB3
#define PIDRB_DB2 pidrb.bit._DB2
#define PIDRB_DB1 pidrb.bit._DB1
#define PIDRB_DB0 pidrb.bit._DB0
__IO_EXTERN PIDRCSTR pidrc;  
#define PIDRC pidrc.byte
#define PIDRC_DC7 pidrc.bit._DC7
#define PIDRC_DC6 pidrc.bit._DC6
#define PIDRC_DC5 pidrc.bit._DC5
#define PIDRC_DC4 pidrc.bit._DC4
#define PIDRC_DC3 pidrc.bit._DC3
#define PIDRC_DC2 pidrc.bit._DC2
#define PIDRC_DC1 pidrc.bit._DC1
#define PIDRC_DC0 pidrc.bit._DC0
__IO_EXTERN PIDRDSTR pidrd;  
#define PIDRD pidrd.byte
#define PIDRD_DD7 pidrd.bit._DD7
#define PIDRD_DD6 pidrd.bit._DD6
#define PIDRD_DD5 pidrd.bit._DD5
#define PIDRD_DD4 pidrd.bit._DD4
#define PIDRD_DD3 pidrd.bit._DD3
#define PIDRD_DD2 pidrd.bit._DD2
#define PIDRD_DD1 pidrd.bit._DD1
#define PIDRD_DD0 pidrd.bit._DD0
__IO_EXTERN PIDRESTR pidre;  
#define PIDRE pidre.byte
#define PIDRE_DE7 pidre.bit._DE7
#define PIDRE_DE6 pidre.bit._DE6
#define PIDRE_DE5 pidre.bit._DE5
#define PIDRE_DE4 pidre.bit._DE4
#define PIDRE_DE3 pidre.bit._DE3
#define PIDRE_DE2 pidre.bit._DE2
#define PIDRE_DE1 pidre.bit._DE1
#define PIDRE_DE0 pidre.bit._DE0
__IO_EXTERN PIDRFSTR pidrf;  
#define PIDRF pidrf.byte
#define PIDRF_DF7 pidrf.bit._DF7
#define PIDRF_DF6 pidrf.bit._DF6
#define PIDRF_DF5 pidrf.bit._DF5
#define PIDRF_DF4 pidrf.bit._DF4
#define PIDRF_DF3 pidrf.bit._DF3
#define PIDRF_DF2 pidrf.bit._DF2
#define PIDRF_DF1 pidrf.bit._DF1
#define PIDRF_DF0 pidrf.bit._DF0
__IO_EXTERN PIDRGSTR pidrg;  
#define PIDRG pidrg.byte
#define PIDRG_DG7 pidrg.bit._DG7
#define PIDRG_DG6 pidrg.bit._DG6
#define PIDRG_DG5 pidrg.bit._DG5
#define PIDRG_DG4 pidrg.bit._DG4
#define PIDRG_DG3 pidrg.bit._DG3
#define PIDRG_DG2 pidrg.bit._DG2
#define PIDRG_DG1 pidrg.bit._DG1
#define PIDRG_DG0 pidrg.bit._DG0
__IO_EXTERN ASR0STR asr0;   /* T-Unit */
#define ASR0 asr0.word
#define ASR0_A23 asr0.bit._A23
#define ASR0_A22 asr0.bit._A22
#define ASR0_A21 asr0.bit._A21
#define ASR0_A20 asr0.bit._A20
#define ASR0_A19 asr0.bit._A19
#define ASR0_A18 asr0.bit._A18
#define ASR0_A17 asr0.bit._A17
#define ASR0_A16 asr0.bit._A16
__IO_EXTERN ACR0STR acr0;  
#define ACR0 acr0.word
#define ACR0_ASZ1 acr0.bit._ASZ1
#define ACR0_ASZ0 acr0.bit._ASZ0
#define ACR0_DBW0 acr0.bit._DBW0
#define ACR0_WREN acr0.bit._WREN
#define ACR0_TYP3 acr0.bit._TYP3
#define ACR0_TYP2 acr0.bit._TYP2
#define ACR0_TYP1 acr0.bit._TYP1
#define ACR0_TYP0 acr0.bit._TYP0
#define ACR0_ASZ acr0.bitc._ASZ
#define ACR0_TYP acr0.bitc._TYP
__IO_EXTERN ASR1STR asr1;  
#define ASR1 asr1.word
#define ASR1_A23 asr1.bit._A23
#define ASR1_A22 asr1.bit._A22
#define ASR1_A21 asr1.bit._A21
#define ASR1_A20 asr1.bit._A20
#define ASR1_A19 asr1.bit._A19
#define ASR1_A18 asr1.bit._A18
#define ASR1_A17 asr1.bit._A17
#define ASR1_A16 asr1.bit._A16
__IO_EXTERN ACR1STR acr1;  
#define ACR1 acr1.word
#define ACR1_ASZ1 acr1.bit._ASZ1
#define ACR1_ASZ0 acr1.bit._ASZ0
#define ACR1_DBW0 acr1.bit._DBW0
#define ACR1_WREN acr1.bit._WREN
#define ACR1_TYP3 acr1.bit._TYP3
#define ACR1_TYP2 acr1.bit._TYP2
#define ACR1_TYP1 acr1.bit._TYP1
#define ACR1_TYP0 acr1.bit._TYP0
#define ACR1_ASZ acr1.bitc._ASZ
#define ACR1_TYP acr1.bitc._TYP
__IO_EXTERN ASR2STR asr2;  
#define ASR2 asr2.word
#define ASR2_A23 asr2.bit._A23
#define ASR2_A22 asr2.bit._A22
#define ASR2_A21 asr2.bit._A21
#define ASR2_A20 asr2.bit._A20
#define ASR2_A19 asr2.bit._A19
#define ASR2_A18 asr2.bit._A18
#define ASR2_A17 asr2.bit._A17
#define ASR2_A16 asr2.bit._A16
__IO_EXTERN ACR2STR acr2;  
#define ACR2 acr2.word
#define ACR2_ASZ1 acr2.bit._ASZ1
#define ACR2_ASZ0 acr2.bit._ASZ0
#define ACR2_DBW0 acr2.bit._DBW0
#define ACR2_WREN acr2.bit._WREN
#define ACR2_TYP3 acr2.bit._TYP3
#define ACR2_TYP2 acr2.bit._TYP2
#define ACR2_TYP1 acr2.bit._TYP1
#define ACR2_TYP0 acr2.bit._TYP0
#define ACR2_ASZ acr2.bitc._ASZ
#define ACR2_TYP acr2.bitc._TYP
__IO_EXTERN ASR3STR asr3;  
#define ASR3 asr3.word
#define ASR3_A23 asr3.bit._A23
#define ASR3_A22 asr3.bit._A22
#define ASR3_A21 asr3.bit._A21
#define ASR3_A20 asr3.bit._A20
#define ASR3_A19 asr3.bit._A19
#define ASR3_A18 asr3.bit._A18
#define ASR3_A17 asr3.bit._A17
#define ASR3_A16 asr3.bit._A16
__IO_EXTERN ACR3STR acr3;  
#define ACR3 acr3.word
#define ACR3_ASZ1 acr3.bit._ASZ1
#define ACR3_ASZ0 acr3.bit._ASZ0
#define ACR3_DBW0 acr3.bit._DBW0
#define ACR3_WREN acr3.bit._WREN
#define ACR3_TYP3 acr3.bit._TYP3
#define ACR3_TYP2 acr3.bit._TYP2
#define ACR3_TYP1 acr3.bit._TYP1
#define ACR3_TYP0 acr3.bit._TYP0
#define ACR3_ASZ acr3.bitc._ASZ
#define ACR3_TYP acr3.bitc._TYP
__IO_EXTERN AWR0STR awr0;  
#define AWR0 awr0.word
#define AWR0_W14 awr0.bit._W14
#define AWR0_W13 awr0.bit._W13
#define AWR0_W12 awr0.bit._W12
#define AWR0_W06 awr0.bit._W06
#define AWR0_W04 awr0.bit._W04
#define AWR0_W02 awr0.bit._W02
#define AWR0_W01 awr0.bit._W01
#define AWR0_W00 awr0.bit._W00
__IO_EXTERN AWR1STR awr1;  
#define AWR1 awr1.word
#define AWR1_W14 awr1.bit._W14
#define AWR1_W13 awr1.bit._W13
#define AWR1_W12 awr1.bit._W12
#define AWR1_W06 awr1.bit._W06
#define AWR1_W04 awr1.bit._W04
#define AWR1_W02 awr1.bit._W02
#define AWR1_W01 awr1.bit._W01
#define AWR1_W00 awr1.bit._W00
__IO_EXTERN AWR2STR awr2;  
#define AWR2 awr2.word
#define AWR2_W14 awr2.bit._W14
#define AWR2_W13 awr2.bit._W13
#define AWR2_W12 awr2.bit._W12
#define AWR2_W06 awr2.bit._W06
#define AWR2_W04 awr2.bit._W04
#define AWR2_W02 awr2.bit._W02
#define AWR2_W01 awr2.bit._W01
#define AWR2_W00 awr2.bit._W00
__IO_EXTERN AWR3STR awr3;  
#define AWR3 awr3.word
#define AWR3_W14 awr3.bit._W14
#define AWR3_W13 awr3.bit._W13
#define AWR3_W12 awr3.bit._W12
#define AWR3_W06 awr3.bit._W06
#define AWR3_W04 awr3.bit._W04
#define AWR3_W02 awr3.bit._W02
#define AWR3_W01 awr3.bit._W01
#define AWR3_W00 awr3.bit._W00
__IO_EXTERN CSERSTR cser;  
#define CSER cser.byte
#define CSER_CSE3 cser.bit._CSE3
#define CSER_CSE2 cser.bit._CSE2
#define CSER_CSE1 cser.bit._CSE1
#define CSER_CSE0 cser.bit._CSE0
__IO_EXTERN IO_BYTE tcr;  
#define TCR tcr
__IO_EXTERN MODRSTR modr;   /* Mode Register */
#define MODR modr.byte
#define MODR_ROMA modr.bit._ROMA
#define MODR_WTH1 modr.bit._WTH1
#define MODR_WTH0 modr.bit._WTH0
#define MODR_WTH modr.bitc._WTH
__IO_EXTERN IO_LWORD dmasa0;   /* DMAC */
#define DMASA0 dmasa0
__IO_EXTERN IO_LWORD dmada0;  
#define DMADA0 dmada0
__IO_EXTERN IO_LWORD dmasa1;  
#define DMASA1 dmasa1
__IO_EXTERN IO_LWORD dmada1;  
#define DMADA1 dmada1
__IO_EXTERN IO_LWORD dmasa2;  
#define DMASA2 dmasa2
__IO_EXTERN IO_LWORD dmada2;  
#define DMADA2 dmada2
__IO_EXTERN IO_LWORD dmasa3;  
#define DMASA3 dmasa3
__IO_EXTERN IO_LWORD dmada3;  
#define DMADA3 dmada3
__IO_EXTERN IO_LWORD dmasa4;  
#define DMASA4 dmasa4
__IO_EXTERN IO_LWORD dmada4;  
#define DMADA4 dmada4
__IO_EXTERN FLCRSTR flcr;   /* Flash I/F */
#define FLCR flcr.byte
#define FLCR_RDY flcr.bit._RDY
#define FLCR_WE flcr.bit._WE
__IO_EXTERN FLWCSTR flwc;  
#define FLWC flwc.byte
#define FLWC_FAC1 flwc.bit._FAC1
#define FLWC_FAC0 flwc.bit._FAC0
#define FLWC_WTC2 flwc.bit._WTC2
#define FLWC_WTC1 flwc.bit._WTC1
#define FLWC_WTC0 flwc.bit._WTC0
#define FLWC_FAC flwc.bitc._FAC
#define FLWC_WTC flwc.bitc._WTC
__IO_EXTERN CTRLR0STR ctrlr0;   /* CAN 0 Control Register */
#define CTRLR0 ctrlr0.word
#define CTRLR0_Test ctrlr0.bit._Test
#define CTRLR0_CCE ctrlr0.bit._CCE
#define CTRLR0_DAR ctrlr0.bit._DAR
#define CTRLR0_EIE ctrlr0.bit._EIE
#define CTRLR0_SIE ctrlr0.bit._SIE
#define CTRLR0_IE ctrlr0.bit._IE
#define CTRLR0_Init ctrlr0.bit._Init
__IO_EXTERN STATR0STR statr0;  
#define STATR0 statr0.word
#define STATR0_BOff statr0.bit._BOff
#define STATR0_EWarn statr0.bit._EWarn
#define STATR0_EPass statr0.bit._EPass
#define STATR0_RxOK statr0.bit._RxOK
#define STATR0_TxOK statr0.bit._TxOK
#define STATR0_LEC2 statr0.bit._LEC2
#define STATR0_LEC1 statr0.bit._LEC1
#define STATR0_LEC0 statr0.bit._LEC0
#define STATR0_LEC statr0.bitc._LEC
__IO_EXTERN ERRCNT0STR errcnt0;  
#define ERRCNT0 errcnt0.word
#define ERRCNT0_RP errcnt0.bit._RP
#define ERRCNT0_REC6 errcnt0.bit._REC6
#define ERRCNT0_REC5 errcnt0.bit._REC5
#define ERRCNT0_REC4 errcnt0.bit._REC4
#define ERRCNT0_REC3 errcnt0.bit._REC3
#define ERRCNT0_REC2 errcnt0.bit._REC2
#define ERRCNT0_REC1 errcnt0.bit._REC1
#define ERRCNT0_REC0 errcnt0.bit._REC0
#define ERRCNT0_TEC7 errcnt0.bit._TEC7
#define ERRCNT0_TEC6 errcnt0.bit._TEC6
#define ERRCNT0_TEC5 errcnt0.bit._TEC5
#define ERRCNT0_TEC4 errcnt0.bit._TEC4
#define ERRCNT0_TEC3 errcnt0.bit._TEC3
#define ERRCNT0_TEC2 errcnt0.bit._TEC2
#define ERRCNT0_TEC1 errcnt0.bit._TEC1
#define ERRCNT0_TEC0 errcnt0.bit._TEC0
#define ERRCNT0_REC errcnt0.bitc._REC
#define ERRCNT0_TEC errcnt0.bitc._TEC
__IO_EXTERN BTR0STR btr0;  
#define BTR0 btr0.word
#define BTR0_Tseg22 btr0.bit._Tseg22
#define BTR0_Tseg21 btr0.bit._Tseg21
#define BTR0_Tseg20 btr0.bit._Tseg20
#define BTR0_Tseg13 btr0.bit._Tseg13
#define BTR0_Tseg12 btr0.bit._Tseg12
#define BTR0_Tseg11 btr0.bit._Tseg11
#define BTR0_Tseg10 btr0.bit._Tseg10
#define BTR0_SJW1 btr0.bit._SJW1
#define BTR0_SJW0 btr0.bit._SJW0
#define BTR0_BRP5 btr0.bit._BRP5
#define BTR0_BRP4 btr0.bit._BRP4
#define BTR0_BRP3 btr0.bit._BRP3
#define BTR0_BRP2 btr0.bit._BRP2
#define BTR0_BRP1 btr0.bit._BRP1
#define BTR0_BRP0 btr0.bit._BRP0
#define BTR0_Tseg2 btr0.bitc._Tseg2
#define BTR0_Tseg1 btr0.bitc._Tseg1
#define BTR0_SJW btr0.bitc._SJW
#define BTR0_BRP btr0.bitc._BRP
__IO_EXTERN IO_WORD intr0;  
#define INTR0 intr0
__IO_EXTERN TESTR0STR testr0;  
#define TESTR0 testr0.word
#define TESTR0_Rx testr0.bit._Rx
#define TESTR0_Tx1 testr0.bit._Tx1
#define TESTR0_Tx0 testr0.bit._Tx0
#define TESTR0_LBack testr0.bit._LBack
#define TESTR0_Silent testr0.bit._Silent
#define TESTR0_Basic testr0.bit._Basic
#define TESTR0_Tx testr0.bitc._Tx
__IO_EXTERN BRPER0STR brper0;  
#define BRPER0 brper0.word
__IO_EXTERN IF1CREQ0STR if1creq0;   /* CAN 0 IF 1 */
#define IF1CREQ0 if1creq0.word
#define IF1CREQ0_Busy if1creq0.bit._Busy
#define IF1CREQ0_MN5 if1creq0.bit._MN5
#define IF1CREQ0_MN4 if1creq0.bit._MN4
#define IF1CREQ0_MN3 if1creq0.bit._MN3
#define IF1CREQ0_MN2 if1creq0.bit._MN2
#define IF1CREQ0_MN1 if1creq0.bit._MN1
#define IF1CREQ0_MN0 if1creq0.bit._MN0
#define IF1CREQ0_MN if1creq0.bitc._MN
__IO_EXTERN IF1CMSK0STR if1cmsk0;  
#define IF1CMSK0 if1cmsk0.word
#define IF1CMSK0_WR if1cmsk0.bit._WR
#define IF1CMSK0_Mask if1cmsk0.bit._Mask
#define IF1CMSK0_Arb if1cmsk0.bit._Arb
#define IF1CMSK0_Control if1cmsk0.bit._Control
#define IF1CMSK0_CIP if1cmsk0.bit._CIP
#define IF1CMSK0_TxReq if1cmsk0.bit._TxReq
#define IF1CMSK0_DataA if1cmsk0.bit._DataA
#define IF1CMSK0_DataB if1cmsk0.bit._DataB
__IO_EXTERN IO_LWORD if1msk120;  
#define IF1MSK120 if1msk120
__IO_EXTERN IF1MSK20STR if1msk20;  
#define IF1MSK20 if1msk20.word
#define IF1MSK20_MXtd if1msk20.bit._MXtd
#define IF1MSK20_MDir if1msk20.bit._MDir
__IO_EXTERN IO_WORD if1msk10;  
#define IF1MSK10 if1msk10
__IO_EXTERN IO_LWORD if1arb120;  
#define IF1ARB120 if1arb120
__IO_EXTERN IF1ARB20STR if1arb20;  
#define IF1ARB20 if1arb20.word
#define IF1ARB20_MsgVal if1arb20.bit._MsgVal
#define IF1ARB20_Xtd if1arb20.bit._Xtd
#define IF1ARB20_DIR if1arb20.bit._DIR
__IO_EXTERN IO_WORD if1arb10;  
#define IF1ARB10 if1arb10
__IO_EXTERN IF1MCTR0STR if1mctr0;  
#define IF1MCTR0 if1mctr0.word
#define IF1MCTR0_NewDat if1mctr0.bit._NewDat
#define IF1MCTR0_MsgLst if1mctr0.bit._MsgLst
#define IF1MCTR0_IntPnd if1mctr0.bit._IntPnd
#define IF1MCTR0_UMask if1mctr0.bit._UMask
#define IF1MCTR0_TxIE if1mctr0.bit._TxIE
#define IF1MCTR0_RxIE if1mctr0.bit._RxIE
#define IF1MCTR0_RmtEn if1mctr0.bit._RmtEn
#define IF1MCTR0_TxRqst if1mctr0.bit._TxRqst
#define IF1MCTR0_EoB if1mctr0.bit._EoB
#define IF1MCTR0_DLC3 if1mctr0.bit._DLC3
#define IF1MCTR0_DLC2 if1mctr0.bit._DLC2
#define IF1MCTR0_DLC1 if1mctr0.bit._DLC1
#define IF1MCTR0_DLC0 if1mctr0.bit._DLC0
#define IF1MCTR0_DLC if1mctr0.bitc._DLC
__IO_EXTERN IO_LWORD if1dta120;  
#define IF1DTA120 if1dta120
__IO_EXTERN IO_WORD if1dta10;  
#define IF1DTA10 if1dta10
__IO_EXTERN IO_WORD if1dta20;  
#define IF1DTA20 if1dta20
__IO_EXTERN IO_LWORD if1dtb120;  
#define IF1DTB120 if1dtb120
__IO_EXTERN IO_WORD if1dtb10;  
#define IF1DTB10 if1dtb10
__IO_EXTERN IO_WORD if1dtb20;  
#define IF1DTB20 if1dtb20
__IO_EXTERN IO_LWORD if1dta_swp120;  
#define IF1DTA_SWP120 if1dta_swp120
__IO_EXTERN IO_WORD if1dta_swp20;  
#define IF1DTA_SWP20 if1dta_swp20
__IO_EXTERN IO_WORD if1dta_swp10;  
#define IF1DTA_SWP10 if1dta_swp10
__IO_EXTERN IO_LWORD if1dtb_swp120;  
#define IF1DTB_SWP120 if1dtb_swp120
__IO_EXTERN IO_WORD if1dtb_swp20;  
#define IF1DTB_SWP20 if1dtb_swp20
__IO_EXTERN IO_WORD if1dtb_swp10;  
#define IF1DTB_SWP10 if1dtb_swp10
__IO_EXTERN IF2CREQ0STR if2creq0;   /* CAN 0 IF 2 */
#define IF2CREQ0 if2creq0.word
#define IF2CREQ0_Busy if2creq0.bit._Busy
#define IF2CREQ0_MN5 if2creq0.bit._MN5
#define IF2CREQ0_MN4 if2creq0.bit._MN4
#define IF2CREQ0_MN3 if2creq0.bit._MN3
#define IF2CREQ0_MN2 if2creq0.bit._MN2
#define IF2CREQ0_MN1 if2creq0.bit._MN1
#define IF2CREQ0_MN0 if2creq0.bit._MN0
#define IF2CREQ0_MN if2creq0.bitc._MN
__IO_EXTERN IF2CMSK0STR if2cmsk0;  
#define IF2CMSK0 if2cmsk0.word
#define IF2CMSK0_WR if2cmsk0.bit._WR
#define IF2CMSK0_Mask if2cmsk0.bit._Mask
#define IF2CMSK0_Arb if2cmsk0.bit._Arb
#define IF2CMSK0_Control if2cmsk0.bit._Control
#define IF2CMSK0_CIP if2cmsk0.bit._CIP
#define IF2CMSK0_TxReq if2cmsk0.bit._TxReq
#define IF2CMSK0_DataA if2cmsk0.bit._DataA
#define IF2CMSK0_DataB if2cmsk0.bit._DataB
__IO_EXTERN IO_LWORD if2msk120;  
#define IF2MSK120 if2msk120
__IO_EXTERN IF2MSK20STR if2msk20;  
#define IF2MSK20 if2msk20.word
#define IF2MSK20_MXtd if2msk20.bit._MXtd
#define IF2MSK20_MDir if2msk20.bit._MDir
__IO_EXTERN IO_WORD if2msk10;  
#define IF2MSK10 if2msk10
__IO_EXTERN IO_LWORD if2arb120;  
#define IF2ARB120 if2arb120
__IO_EXTERN IF2ARB20STR if2arb20;  
#define IF2ARB20 if2arb20.word
#define IF2ARB20_MsgVal if2arb20.bit._MsgVal
#define IF2ARB20_Xtd if2arb20.bit._Xtd
#define IF2ARB20_DIR if2arb20.bit._DIR
__IO_EXTERN IO_WORD if2arb10;  
#define IF2ARB10 if2arb10
__IO_EXTERN IF2MCTR0STR if2mctr0;  
#define IF2MCTR0 if2mctr0.word
#define IF2MCTR0_NewDat if2mctr0.bit._NewDat
#define IF2MCTR0_MsgLst if2mctr0.bit._MsgLst
#define IF2MCTR0_IntPnd if2mctr0.bit._IntPnd
#define IF2MCTR0_UMask if2mctr0.bit._UMask
#define IF2MCTR0_TxIE if2mctr0.bit._TxIE
#define IF2MCTR0_RxIE if2mctr0.bit._RxIE
#define IF2MCTR0_RmtEn if2mctr0.bit._RmtEn
#define IF2MCTR0_TxRqst if2mctr0.bit._TxRqst
#define IF2MCTR0_EoB if2mctr0.bit._EoB
#define IF2MCTR0_DLC3 if2mctr0.bit._DLC3
#define IF2MCTR0_DLC2 if2mctr0.bit._DLC2
#define IF2MCTR0_DLC1 if2mctr0.bit._DLC1
#define IF2MCTR0_DLC0 if2mctr0.bit._DLC0
#define IF2MCTR0_DLC if2mctr0.bitc._DLC
__IO_EXTERN IO_LWORD if2dta120;  
#define IF2DTA120 if2dta120
__IO_EXTERN IO_WORD if2dta10;  
#define IF2DTA10 if2dta10
__IO_EXTERN IO_WORD if2dta20;  
#define IF2DTA20 if2dta20
__IO_EXTERN IO_LWORD if2dtb120;  
#define IF2DTB120 if2dtb120
__IO_EXTERN IO_WORD if2dtb10;  
#define IF2DTB10 if2dtb10
__IO_EXTERN IO_WORD if2dtb20;  
#define IF2DTB20 if2dtb20
__IO_EXTERN IO_LWORD if2dta_swp120;  
#define IF2DTA_SWP120 if2dta_swp120
__IO_EXTERN IO_WORD if2dta_swp20;  
#define IF2DTA_SWP20 if2dta_swp20
__IO_EXTERN IO_WORD if2dta_swp10;  
#define IF2DTA_SWP10 if2dta_swp10
__IO_EXTERN IO_LWORD if2dtb_swp120;  
#define IF2DTB_SWP120 if2dtb_swp120
__IO_EXTERN IO_WORD if2dtb_swp20;  
#define IF2DTB_SWP20 if2dtb_swp20
__IO_EXTERN IO_WORD if2dtb_swp10;  
#define IF2DTB_SWP10 if2dtb_swp10
__IO_EXTERN IO_LWORD treqr120;   /* CAN 0 Status flags */
#define TREQR120 treqr120
__IO_EXTERN IO_WORD treqr20;  
#define TREQR20 treqr20
__IO_EXTERN IO_WORD treqr10;  
#define TREQR10 treqr10
__IO_EXTERN IO_LWORD treqr340;  
#define TREQR340 treqr340
__IO_EXTERN IO_WORD treqr40;  
#define TREQR40 treqr40
__IO_EXTERN IO_WORD treqr30;  
#define TREQR30 treqr30
__IO_EXTERN IO_LWORD newdt120;  
#define NEWDT120 newdt120
__IO_EXTERN IO_WORD newdt20;  
#define NEWDT20 newdt20
__IO_EXTERN IO_WORD newdt10;  
#define NEWDT10 newdt10
__IO_EXTERN IO_LWORD newdt340;  
#define NEWDT340 newdt340
__IO_EXTERN IO_WORD newdt40;  
#define NEWDT40 newdt40
__IO_EXTERN IO_WORD newdt30;  
#define NEWDT30 newdt30
__IO_EXTERN IO_LWORD intpnd120;  
#define INTPND120 intpnd120
__IO_EXTERN IO_WORD intpnd20;  
#define INTPND20 intpnd20
__IO_EXTERN IO_WORD intpnd10;  
#define INTPND10 intpnd10
__IO_EXTERN IO_LWORD intpnd340;  
#define INTPND340 intpnd340
__IO_EXTERN IO_WORD intpnd40;  
#define INTPND40 intpnd40
__IO_EXTERN IO_WORD intpnd30;  
#define INTPND30 intpnd30
__IO_EXTERN IO_LWORD msgval120;  
#define MSGVAL120 msgval120
__IO_EXTERN IO_WORD msgval20;  
#define MSGVAL20 msgval20
__IO_EXTERN IO_WORD msgval10;  
#define MSGVAL10 msgval10
__IO_EXTERN IO_LWORD msgval340;  
#define MSGVAL340 msgval340
__IO_EXTERN IO_WORD msgval40;  
#define MSGVAL40 msgval40
__IO_EXTERN IO_WORD msgval30;  
#define MSGVAL30 msgval30
__IO_EXTERN CTRLR1STR ctrlr1;   /* CAN 1 Control Register */
#define CTRLR1 ctrlr1.word
#define CTRLR1_Test ctrlr1.bit._Test
#define CTRLR1_CCE ctrlr1.bit._CCE
#define CTRLR1_DAR ctrlr1.bit._DAR
#define CTRLR1_EIE ctrlr1.bit._EIE
#define CTRLR1_SIE ctrlr1.bit._SIE
#define CTRLR1_IE ctrlr1.bit._IE
#define CTRLR1_Init ctrlr1.bit._Init
__IO_EXTERN STATR1STR statr1;  
#define STATR1 statr1.word
#define STATR1_BOff statr1.bit._BOff
#define STATR1_EWarn statr1.bit._EWarn
#define STATR1_EPass statr1.bit._EPass
#define STATR1_RxOK statr1.bit._RxOK
#define STATR1_TxOK statr1.bit._TxOK
#define STATR1_LEC2 statr1.bit._LEC2
#define STATR1_LEC1 statr1.bit._LEC1
#define STATR1_LEC0 statr1.bit._LEC0
#define STATR1_LEC statr1.bitc._LEC
__IO_EXTERN ERRCNT1STR errcnt1;  
#define ERRCNT1 errcnt1.word
#define ERRCNT1_RP errcnt1.bit._RP
#define ERRCNT1_REC6 errcnt1.bit._REC6
#define ERRCNT1_REC5 errcnt1.bit._REC5
#define ERRCNT1_REC4 errcnt1.bit._REC4
#define ERRCNT1_REC3 errcnt1.bit._REC3
#define ERRCNT1_REC2 errcnt1.bit._REC2
#define ERRCNT1_REC1 errcnt1.bit._REC1
#define ERRCNT1_REC0 errcnt1.bit._REC0
#define ERRCNT1_TEC7 errcnt1.bit._TEC7
#define ERRCNT1_TEC6 errcnt1.bit._TEC6
#define ERRCNT1_TEC5 errcnt1.bit._TEC5
#define ERRCNT1_TEC4 errcnt1.bit._TEC4
#define ERRCNT1_TEC3 errcnt1.bit._TEC3
#define ERRCNT1_TEC2 errcnt1.bit._TEC2
#define ERRCNT1_TEC1 errcnt1.bit._TEC1
#define ERRCNT1_TEC0 errcnt1.bit._TEC0
#define ERRCNT1_REC errcnt1.bitc._REC
#define ERRCNT1_TEC errcnt1.bitc._TEC
__IO_EXTERN BTR1STR btr1;  
#define BTR1 btr1.word
#define BTR1_Tseg22 btr1.bit._Tseg22
#define BTR1_Tseg21 btr1.bit._Tseg21
#define BTR1_Tseg20 btr1.bit._Tseg20
#define BTR1_Tseg13 btr1.bit._Tseg13
#define BTR1_Tseg12 btr1.bit._Tseg12
#define BTR1_Tseg11 btr1.bit._Tseg11
#define BTR1_Tseg10 btr1.bit._Tseg10
#define BTR1_SJW1 btr1.bit._SJW1
#define BTR1_SJW0 btr1.bit._SJW0
#define BTR1_BRP5 btr1.bit._BRP5
#define BTR1_BRP4 btr1.bit._BRP4
#define BTR1_BRP3 btr1.bit._BRP3
#define BTR1_BRP2 btr1.bit._BRP2
#define BTR1_BRP1 btr1.bit._BRP1
#define BTR1_BRP0 btr1.bit._BRP0
#define BTR1_Tseg2 btr1.bitc._Tseg2
#define BTR1_Tseg1 btr1.bitc._Tseg1
#define BTR1_SJW btr1.bitc._SJW
#define BTR1_BRP btr1.bitc._BRP
__IO_EXTERN IO_WORD intr1;  
#define INTR1 intr1
__IO_EXTERN TESTR1STR testr1;  
#define TESTR1 testr1.word
#define TESTR1_Rx testr1.bit._Rx
#define TESTR1_Tx1 testr1.bit._Tx1
#define TESTR1_Tx0 testr1.bit._Tx0
#define TESTR1_LBack testr1.bit._LBack
#define TESTR1_Silent testr1.bit._Silent
#define TESTR1_Basic testr1.bit._Basic
#define TESTR1_Tx testr1.bitc._Tx
__IO_EXTERN BRPER1STR brper1;  
#define BRPER1 brper1.word
__IO_EXTERN IF1CREQ1STR if1creq1;   /* CAN 1 IF 1 */
#define IF1CREQ1 if1creq1.word
#define IF1CREQ1_Busy if1creq1.bit._Busy
#define IF1CREQ1_MN5 if1creq1.bit._MN5
#define IF1CREQ1_MN4 if1creq1.bit._MN4
#define IF1CREQ1_MN3 if1creq1.bit._MN3
#define IF1CREQ1_MN2 if1creq1.bit._MN2
#define IF1CREQ1_MN1 if1creq1.bit._MN1
#define IF1CREQ1_MN0 if1creq1.bit._MN0
#define IF1CREQ1_MN if1creq1.bitc._MN
__IO_EXTERN IF1CMSK1STR if1cmsk1;  
#define IF1CMSK1 if1cmsk1.word
#define IF1CMSK1_WR if1cmsk1.bit._WR
#define IF1CMSK1_Mask if1cmsk1.bit._Mask
#define IF1CMSK1_Arb if1cmsk1.bit._Arb
#define IF1CMSK1_Control if1cmsk1.bit._Control
#define IF1CMSK1_CIP if1cmsk1.bit._CIP
#define IF1CMSK1_TxReq if1cmsk1.bit._TxReq
#define IF1CMSK1_DataA if1cmsk1.bit._DataA
#define IF1CMSK1_DataB if1cmsk1.bit._DataB
__IO_EXTERN IO_LWORD if1msk121;  
#define IF1MSK121 if1msk121
__IO_EXTERN IF1MSK21STR if1msk21;  
#define IF1MSK21 if1msk21.word
#define IF1MSK21_MXtd if1msk21.bit._MXtd
#define IF1MSK21_MDir if1msk21.bit._MDir
__IO_EXTERN IO_WORD if1msk11;  
#define IF1MSK11 if1msk11
__IO_EXTERN IO_LWORD if1arb121;  
#define IF1ARB121 if1arb121
__IO_EXTERN IF1ARB21STR if1arb21;  
#define IF1ARB21 if1arb21.word
#define IF1ARB21_MsgVal if1arb21.bit._MsgVal
#define IF1ARB21_Xtd if1arb21.bit._Xtd
#define IF1ARB21_DIR if1arb21.bit._DIR
__IO_EXTERN IO_WORD if1arb11;  
#define IF1ARB11 if1arb11
__IO_EXTERN IF1MCTR1STR if1mctr1;  
#define IF1MCTR1 if1mctr1.word
#define IF1MCTR1_NewDat if1mctr1.bit._NewDat
#define IF1MCTR1_MsgLst if1mctr1.bit._MsgLst
#define IF1MCTR1_IntPnd if1mctr1.bit._IntPnd
#define IF1MCTR1_UMask if1mctr1.bit._UMask
#define IF1MCTR1_TxIE if1mctr1.bit._TxIE
#define IF1MCTR1_RxIE if1mctr1.bit._RxIE
#define IF1MCTR1_RmtEn if1mctr1.bit._RmtEn
#define IF1MCTR1_TxRqst if1mctr1.bit._TxRqst
#define IF1MCTR1_EoB if1mctr1.bit._EoB
#define IF1MCTR1_DLC3 if1mctr1.bit._DLC3
#define IF1MCTR1_DLC2 if1mctr1.bit._DLC2
#define IF1MCTR1_DLC1 if1mctr1.bit._DLC1
#define IF1MCTR1_DLC0 if1mctr1.bit._DLC0
#define IF1MCTR1_DLC if1mctr1.bitc._DLC
__IO_EXTERN IO_LWORD if1dta121;  
#define IF1DTA121 if1dta121
__IO_EXTERN IO_WORD if1dta11;  
#define IF1DTA11 if1dta11
__IO_EXTERN IO_WORD if1dta21;  
#define IF1DTA21 if1dta21
__IO_EXTERN IO_LWORD if1dtb121;  
#define IF1DTB121 if1dtb121
__IO_EXTERN IO_WORD if1dtb11;  
#define IF1DTB11 if1dtb11
__IO_EXTERN IO_WORD if1dtb21;  
#define IF1DTB21 if1dtb21
__IO_EXTERN IO_LWORD if1dta_swp121;  
#define IF1DTA_SWP121 if1dta_swp121
__IO_EXTERN IO_WORD if1dta_swp21;  
#define IF1DTA_SWP21 if1dta_swp21
__IO_EXTERN IO_WORD if1dta_swp11;  
#define IF1DTA_SWP11 if1dta_swp11
__IO_EXTERN IO_LWORD if1dtb_swp121;  
#define IF1DTB_SWP121 if1dtb_swp121
__IO_EXTERN IO_WORD if1dtb_swp21;  
#define IF1DTB_SWP21 if1dtb_swp21
__IO_EXTERN IO_WORD if1dtb_swp11;  
#define IF1DTB_SWP11 if1dtb_swp11
__IO_EXTERN IF2CREQ1STR if2creq1;   /* CAN 1 IF 2 */
#define IF2CREQ1 if2creq1.word
#define IF2CREQ1_Busy if2creq1.bit._Busy
#define IF2CREQ1_MN5 if2creq1.bit._MN5
#define IF2CREQ1_MN4 if2creq1.bit._MN4
#define IF2CREQ1_MN3 if2creq1.bit._MN3
#define IF2CREQ1_MN2 if2creq1.bit._MN2
#define IF2CREQ1_MN1 if2creq1.bit._MN1
#define IF2CREQ1_MN0 if2creq1.bit._MN0
#define IF2CREQ1_MN if2creq1.bitc._MN
__IO_EXTERN IF2CMSK1STR if2cmsk1;  
#define IF2CMSK1 if2cmsk1.word
#define IF2CMSK1_WR if2cmsk1.bit._WR
#define IF2CMSK1_Mask if2cmsk1.bit._Mask
#define IF2CMSK1_Arb if2cmsk1.bit._Arb
#define IF2CMSK1_Control if2cmsk1.bit._Control
#define IF2CMSK1_CIP if2cmsk1.bit._CIP
#define IF2CMSK1_TxReq if2cmsk1.bit._TxReq
#define IF2CMSK1_DataA if2cmsk1.bit._DataA
#define IF2CMSK1_DataB if2cmsk1.bit._DataB
__IO_EXTERN IO_LWORD if2msk121;  
#define IF2MSK121 if2msk121
__IO_EXTERN IF2MSK21STR if2msk21;  
#define IF2MSK21 if2msk21.word
#define IF2MSK21_MXtd if2msk21.bit._MXtd
#define IF2MSK21_MDir if2msk21.bit._MDir
__IO_EXTERN IO_WORD if2msk11;  
#define IF2MSK11 if2msk11
__IO_EXTERN IO_LWORD if2arb121;  
#define IF2ARB121 if2arb121
__IO_EXTERN IF2ARB21STR if2arb21;  
#define IF2ARB21 if2arb21.word
#define IF2ARB21_MsgVal if2arb21.bit._MsgVal
#define IF2ARB21_Xtd if2arb21.bit._Xtd
#define IF2ARB21_DIR if2arb21.bit._DIR
__IO_EXTERN IO_WORD if2arb11;  
#define IF2ARB11 if2arb11
__IO_EXTERN IF2MCTR1STR if2mctr1;  
#define IF2MCTR1 if2mctr1.word
#define IF2MCTR1_NewDat if2mctr1.bit._NewDat
#define IF2MCTR1_MsgLst if2mctr1.bit._MsgLst
#define IF2MCTR1_IntPnd if2mctr1.bit._IntPnd
#define IF2MCTR1_UMask if2mctr1.bit._UMask
#define IF2MCTR1_TxIE if2mctr1.bit._TxIE
#define IF2MCTR1_RxIE if2mctr1.bit._RxIE
#define IF2MCTR1_RmtEn if2mctr1.bit._RmtEn
#define IF2MCTR1_TxRqst if2mctr1.bit._TxRqst
#define IF2MCTR1_EoB if2mctr1.bit._EoB
#define IF2MCTR1_DLC3 if2mctr1.bit._DLC3
#define IF2MCTR1_DLC2 if2mctr1.bit._DLC2
#define IF2MCTR1_DLC1 if2mctr1.bit._DLC1
#define IF2MCTR1_DLC0 if2mctr1.bit._DLC0
#define IF2MCTR1_DLC if2mctr1.bitc._DLC
__IO_EXTERN IO_LWORD if2dta121;  
#define IF2DTA121 if2dta121
__IO_EXTERN IO_WORD if2dta11;  
#define IF2DTA11 if2dta11
__IO_EXTERN IO_WORD if2dta21;  
#define IF2DTA21 if2dta21
__IO_EXTERN IO_LWORD if2dtb121;  
#define IF2DTB121 if2dtb121
__IO_EXTERN IO_WORD if2dtb11;  
#define IF2DTB11 if2dtb11
__IO_EXTERN IO_WORD if2dtb21;  
#define IF2DTB21 if2dtb21
__IO_EXTERN IO_LWORD if2dta_swp121;  
#define IF2DTA_SWP121 if2dta_swp121
__IO_EXTERN IO_WORD if2dta_swp21;  
#define IF2DTA_SWP21 if2dta_swp21
__IO_EXTERN IO_WORD if2dta_swp11;  
#define IF2DTA_SWP11 if2dta_swp11
__IO_EXTERN IO_LWORD if2dtb_swp121;  
#define IF2DTB_SWP121 if2dtb_swp121
__IO_EXTERN IO_WORD if2dtb_swp21;  
#define IF2DTB_SWP21 if2dtb_swp21
__IO_EXTERN IO_WORD if2dtb_swp11;  
#define IF2DTB_SWP11 if2dtb_swp11
__IO_EXTERN IO_LWORD treqr121;   /* CAN 1 Status flags */
#define TREQR121 treqr121
__IO_EXTERN IO_WORD treqr21;  
#define TREQR21 treqr21
__IO_EXTERN IO_WORD treqr11;  
#define TREQR11 treqr11
__IO_EXTERN IO_LWORD treqr341;  
#define TREQR341 treqr341
__IO_EXTERN IO_WORD treqr41;  
#define TREQR41 treqr41
__IO_EXTERN IO_WORD treqr31;  
#define TREQR31 treqr31
__IO_EXTERN IO_LWORD newdt121;  
#define NEWDT121 newdt121
__IO_EXTERN IO_WORD newdt21;  
#define NEWDT21 newdt21
__IO_EXTERN IO_WORD newdt11;  
#define NEWDT11 newdt11
__IO_EXTERN IO_LWORD newdt341;  
#define NEWDT341 newdt341
__IO_EXTERN IO_WORD newdt41;  
#define NEWDT41 newdt41
__IO_EXTERN IO_WORD newdt31;  
#define NEWDT31 newdt31
__IO_EXTERN IO_LWORD intpnd121;  
#define INTPND121 intpnd121
__IO_EXTERN IO_WORD intpnd21;  
#define INTPND21 intpnd21
__IO_EXTERN IO_WORD intpnd11;  
#define INTPND11 intpnd11
__IO_EXTERN IO_LWORD intpnd341;  
#define INTPND341 intpnd341
__IO_EXTERN IO_WORD intpnd41;  
#define INTPND41 intpnd41
__IO_EXTERN IO_WORD intpnd31;  
#define INTPND31 intpnd31
__IO_EXTERN IO_LWORD msgval121;  
#define MSGVAL121 msgval121
__IO_EXTERN IO_WORD msgval21;  
#define MSGVAL21 msgval21
__IO_EXTERN IO_WORD msgval11;  
#define MSGVAL11 msgval11
__IO_EXTERN IO_LWORD msgval341;  
#define MSGVAL341 msgval341
__IO_EXTERN IO_WORD msgval41;  
#define MSGVAL41 msgval41
__IO_EXTERN IO_WORD msgval31;  
#define MSGVAL31 msgval31
__IO_EXTERN CTRLR2STR ctrlr2;   /* CAN 2 Control Register */
#define CTRLR2 ctrlr2.word
#define CTRLR2_Test ctrlr2.bit._Test
#define CTRLR2_CCE ctrlr2.bit._CCE
#define CTRLR2_DAR ctrlr2.bit._DAR
#define CTRLR2_EIE ctrlr2.bit._EIE
#define CTRLR2_SIE ctrlr2.bit._SIE
#define CTRLR2_IE ctrlr2.bit._IE
#define CTRLR2_Init ctrlr2.bit._Init
__IO_EXTERN STATR2STR statr2;  
#define STATR2 statr2.word
#define STATR2_BOff statr2.bit._BOff
#define STATR2_EWarn statr2.bit._EWarn
#define STATR2_EPass statr2.bit._EPass
#define STATR2_RxOK statr2.bit._RxOK
#define STATR2_TxOK statr2.bit._TxOK
#define STATR2_LEC2 statr2.bit._LEC2
#define STATR2_LEC1 statr2.bit._LEC1
#define STATR2_LEC0 statr2.bit._LEC0
#define STATR2_LEC statr2.bitc._LEC
__IO_EXTERN ERRCNT2STR errcnt2;  
#define ERRCNT2 errcnt2.word
#define ERRCNT2_RP errcnt2.bit._RP
#define ERRCNT2_REC6 errcnt2.bit._REC6
#define ERRCNT2_REC5 errcnt2.bit._REC5
#define ERRCNT2_REC4 errcnt2.bit._REC4
#define ERRCNT2_REC3 errcnt2.bit._REC3
#define ERRCNT2_REC2 errcnt2.bit._REC2
#define ERRCNT2_REC1 errcnt2.bit._REC1
#define ERRCNT2_REC0 errcnt2.bit._REC0
#define ERRCNT2_TEC7 errcnt2.bit._TEC7
#define ERRCNT2_TEC6 errcnt2.bit._TEC6
#define ERRCNT2_TEC5 errcnt2.bit._TEC5
#define ERRCNT2_TEC4 errcnt2.bit._TEC4
#define ERRCNT2_TEC3 errcnt2.bit._TEC3
#define ERRCNT2_TEC2 errcnt2.bit._TEC2
#define ERRCNT2_TEC1 errcnt2.bit._TEC1
#define ERRCNT2_TEC0 errcnt2.bit._TEC0
#define ERRCNT2_REC errcnt2.bitc._REC
#define ERRCNT2_TEC errcnt2.bitc._TEC
__IO_EXTERN BTR2STR btr2;  
#define BTR2 btr2.word
#define BTR2_Tseg22 btr2.bit._Tseg22
#define BTR2_Tseg21 btr2.bit._Tseg21
#define BTR2_Tseg20 btr2.bit._Tseg20
#define BTR2_Tseg13 btr2.bit._Tseg13
#define BTR2_Tseg12 btr2.bit._Tseg12
#define BTR2_Tseg11 btr2.bit._Tseg11
#define BTR2_Tseg10 btr2.bit._Tseg10
#define BTR2_SJW1 btr2.bit._SJW1
#define BTR2_SJW0 btr2.bit._SJW0
#define BTR2_BRP5 btr2.bit._BRP5
#define BTR2_BRP4 btr2.bit._BRP4
#define BTR2_BRP3 btr2.bit._BRP3
#define BTR2_BRP2 btr2.bit._BRP2
#define BTR2_BRP1 btr2.bit._BRP1
#define BTR2_BRP0 btr2.bit._BRP0
#define BTR2_Tseg2 btr2.bitc._Tseg2
#define BTR2_Tseg1 btr2.bitc._Tseg1
#define BTR2_SJW btr2.bitc._SJW
#define BTR2_BRP btr2.bitc._BRP
__IO_EXTERN IO_WORD intr2;  
#define INTR2 intr2
__IO_EXTERN TESTR2STR testr2;  
#define TESTR2 testr2.word
#define TESTR2_Rx testr2.bit._Rx
#define TESTR2_Tx1 testr2.bit._Tx1
#define TESTR2_Tx0 testr2.bit._Tx0
#define TESTR2_LBack testr2.bit._LBack
#define TESTR2_Silent testr2.bit._Silent
#define TESTR2_Basic testr2.bit._Basic
#define TESTR2_Tx testr2.bitc._Tx
__IO_EXTERN BRPER2STR brper2;  
#define BRPER2 brper2.word
__IO_EXTERN IF1CREQ2STR if1creq2;   /* CAN 2 IF 1 */
#define IF1CREQ2 if1creq2.word
#define IF1CREQ2_Busy if1creq2.bit._Busy
#define IF1CREQ2_MN5 if1creq2.bit._MN5
#define IF1CREQ2_MN4 if1creq2.bit._MN4
#define IF1CREQ2_MN3 if1creq2.bit._MN3
#define IF1CREQ2_MN2 if1creq2.bit._MN2
#define IF1CREQ2_MN1 if1creq2.bit._MN1
#define IF1CREQ2_MN0 if1creq2.bit._MN0
#define IF1CREQ2_MN if1creq2.bitc._MN
__IO_EXTERN IF1CMSK2STR if1cmsk2;  
#define IF1CMSK2 if1cmsk2.word
#define IF1CMSK2_WR if1cmsk2.bit._WR
#define IF1CMSK2_Mask if1cmsk2.bit._Mask
#define IF1CMSK2_Arb if1cmsk2.bit._Arb
#define IF1CMSK2_Control if1cmsk2.bit._Control
#define IF1CMSK2_CIP if1cmsk2.bit._CIP
#define IF1CMSK2_TxReq if1cmsk2.bit._TxReq
#define IF1CMSK2_DataA if1cmsk2.bit._DataA
#define IF1CMSK2_DataB if1cmsk2.bit._DataB
__IO_EXTERN IO_LWORD if1msk122;  
#define IF1MSK122 if1msk122
__IO_EXTERN IF1MSK22STR if1msk22;  
#define IF1MSK22 if1msk22.word
#define IF1MSK22_MXtd if1msk22.bit._MXtd
#define IF1MSK22_MDir if1msk22.bit._MDir
__IO_EXTERN IO_WORD if1msk12;  
#define IF1MSK12 if1msk12
__IO_EXTERN IO_LWORD if1arb122;  
#define IF1ARB122 if1arb122
__IO_EXTERN IF1ARB22STR if1arb22;  
#define IF1ARB22 if1arb22.word
#define IF1ARB22_MsgVal if1arb22.bit._MsgVal
#define IF1ARB22_Xtd if1arb22.bit._Xtd
#define IF1ARB22_DIR if1arb22.bit._DIR
__IO_EXTERN IO_WORD if1arb12;  
#define IF1ARB12 if1arb12
__IO_EXTERN IF1MCTR2STR if1mctr2;  
#define IF1MCTR2 if1mctr2.word
#define IF1MCTR2_NewDat if1mctr2.bit._NewDat
#define IF1MCTR2_MsgLst if1mctr2.bit._MsgLst
#define IF1MCTR2_IntPnd if1mctr2.bit._IntPnd
#define IF1MCTR2_UMask if1mctr2.bit._UMask
#define IF1MCTR2_TxIE if1mctr2.bit._TxIE
#define IF1MCTR2_RxIE if1mctr2.bit._RxIE
#define IF1MCTR2_RmtEn if1mctr2.bit._RmtEn
#define IF1MCTR2_TxRqst if1mctr2.bit._TxRqst
#define IF1MCTR2_EoB if1mctr2.bit._EoB
#define IF1MCTR2_DLC3 if1mctr2.bit._DLC3
#define IF1MCTR2_DLC2 if1mctr2.bit._DLC2
#define IF1MCTR2_DLC1 if1mctr2.bit._DLC1
#define IF1MCTR2_DLC0 if1mctr2.bit._DLC0
#define IF1MCTR2_DLC if1mctr2.bitc._DLC
__IO_EXTERN IO_LWORD if1dta122;  
#define IF1DTA122 if1dta122
__IO_EXTERN IO_WORD if1dta12;  
#define IF1DTA12 if1dta12
__IO_EXTERN IO_WORD if1dta22;  
#define IF1DTA22 if1dta22
__IO_EXTERN IO_LWORD if1dtb122;  
#define IF1DTB122 if1dtb122
__IO_EXTERN IO_WORD if1dtb12;  
#define IF1DTB12 if1dtb12
__IO_EXTERN IO_WORD if1dtb22;  
#define IF1DTB22 if1dtb22
__IO_EXTERN IO_LWORD if1dta_swp122;  
#define IF1DTA_SWP122 if1dta_swp122
__IO_EXTERN IO_WORD if1dta_swp22;  
#define IF1DTA_SWP22 if1dta_swp22
__IO_EXTERN IO_WORD if1dta_swp12;  
#define IF1DTA_SWP12 if1dta_swp12
__IO_EXTERN IO_LWORD if1dtb_swp122;  
#define IF1DTB_SWP122 if1dtb_swp122
__IO_EXTERN IO_WORD if1dtb_swp22;  
#define IF1DTB_SWP22 if1dtb_swp22
__IO_EXTERN IO_WORD if1dtb_swp12;  
#define IF1DTB_SWP12 if1dtb_swp12
__IO_EXTERN IF2CREQ2STR if2creq2;   /* CAN 2 IF 2 */
#define IF2CREQ2 if2creq2.word
#define IF2CREQ2_Busy if2creq2.bit._Busy
#define IF2CREQ2_MN5 if2creq2.bit._MN5
#define IF2CREQ2_MN4 if2creq2.bit._MN4
#define IF2CREQ2_MN3 if2creq2.bit._MN3
#define IF2CREQ2_MN2 if2creq2.bit._MN2
#define IF2CREQ2_MN1 if2creq2.bit._MN1
#define IF2CREQ2_MN0 if2creq2.bit._MN0
#define IF2CREQ2_MN if2creq2.bitc._MN
__IO_EXTERN IF2CMSK2STR if2cmsk2;  
#define IF2CMSK2 if2cmsk2.word
#define IF2CMSK2_WR if2cmsk2.bit._WR
#define IF2CMSK2_Mask if2cmsk2.bit._Mask
#define IF2CMSK2_Arb if2cmsk2.bit._Arb
#define IF2CMSK2_Control if2cmsk2.bit._Control
#define IF2CMSK2_CIP if2cmsk2.bit._CIP
#define IF2CMSK2_TxReq if2cmsk2.bit._TxReq
#define IF2CMSK2_DataA if2cmsk2.bit._DataA
#define IF2CMSK2_DataB if2cmsk2.bit._DataB
__IO_EXTERN IO_LWORD if2msk122;  
#define IF2MSK122 if2msk122
__IO_EXTERN IF2MSK22STR if2msk22;  
#define IF2MSK22 if2msk22.word
#define IF2MSK22_MXtd if2msk22.bit._MXtd
#define IF2MSK22_MDir if2msk22.bit._MDir
__IO_EXTERN IO_WORD if2msk12;  
#define IF2MSK12 if2msk12
__IO_EXTERN IO_LWORD if2arb122;  
#define IF2ARB122 if2arb122
__IO_EXTERN IF2ARB22STR if2arb22;  
#define IF2ARB22 if2arb22.word
#define IF2ARB22_MsgVal if2arb22.bit._MsgVal
#define IF2ARB22_Xtd if2arb22.bit._Xtd
#define IF2ARB22_DIR if2arb22.bit._DIR
__IO_EXTERN IO_WORD if2arb12;  
#define IF2ARB12 if2arb12
__IO_EXTERN IF2MCTR2STR if2mctr2;  
#define IF2MCTR2 if2mctr2.word
#define IF2MCTR2_NewDat if2mctr2.bit._NewDat
#define IF2MCTR2_MsgLst if2mctr2.bit._MsgLst
#define IF2MCTR2_IntPnd if2mctr2.bit._IntPnd
#define IF2MCTR2_UMask if2mctr2.bit._UMask
#define IF2MCTR2_TxIE if2mctr2.bit._TxIE
#define IF2MCTR2_RxIE if2mctr2.bit._RxIE
#define IF2MCTR2_RmtEn if2mctr2.bit._RmtEn
#define IF2MCTR2_TxRqst if2mctr2.bit._TxRqst
#define IF2MCTR2_EoB if2mctr2.bit._EoB
#define IF2MCTR2_DLC3 if2mctr2.bit._DLC3
#define IF2MCTR2_DLC2 if2mctr2.bit._DLC2
#define IF2MCTR2_DLC1 if2mctr2.bit._DLC1
#define IF2MCTR2_DLC0 if2mctr2.bit._DLC0
#define IF2MCTR2_DLC if2mctr2.bitc._DLC
__IO_EXTERN IO_LWORD if2dta122;  
#define IF2DTA122 if2dta122
__IO_EXTERN IO_WORD if2dta12;  
#define IF2DTA12 if2dta12
__IO_EXTERN IO_WORD if2dta22;  
#define IF2DTA22 if2dta22
__IO_EXTERN IO_LWORD if2dtb122;  
#define IF2DTB122 if2dtb122
__IO_EXTERN IO_WORD if2dtb12;  
#define IF2DTB12 if2dtb12
__IO_EXTERN IO_WORD if2dtb22;  
#define IF2DTB22 if2dtb22
__IO_EXTERN IO_LWORD if2dta_swp122;  
#define IF2DTA_SWP122 if2dta_swp122
__IO_EXTERN IO_WORD if2dta_swp22;  
#define IF2DTA_SWP22 if2dta_swp22
__IO_EXTERN IO_WORD if2dta_swp12;  
#define IF2DTA_SWP12 if2dta_swp12
__IO_EXTERN IO_LWORD if2dtb_swp122;  
#define IF2DTB_SWP122 if2dtb_swp122
__IO_EXTERN IO_WORD if2dtb_swp22;  
#define IF2DTB_SWP22 if2dtb_swp22
__IO_EXTERN IO_WORD if2dtb_swp12;  
#define IF2DTB_SWP12 if2dtb_swp12
__IO_EXTERN IO_LWORD treqr122;   /* CAN 2 Status flags */
#define TREQR122 treqr122
__IO_EXTERN IO_WORD treqr22;  
#define TREQR22 treqr22
__IO_EXTERN IO_WORD treqr12;  
#define TREQR12 treqr12
__IO_EXTERN IO_LWORD treqr342;  
#define TREQR342 treqr342
__IO_EXTERN IO_WORD treqr42;  
#define TREQR42 treqr42
__IO_EXTERN IO_WORD treqr32;  
#define TREQR32 treqr32
__IO_EXTERN IO_LWORD newdt122;  
#define NEWDT122 newdt122
__IO_EXTERN IO_WORD newdt22;  
#define NEWDT22 newdt22
__IO_EXTERN IO_WORD newdt12;  
#define NEWDT12 newdt12
__IO_EXTERN IO_LWORD newdt342;  
#define NEWDT342 newdt342
__IO_EXTERN IO_WORD newdt42;  
#define NEWDT42 newdt42
__IO_EXTERN IO_WORD newdt32;  
#define NEWDT32 newdt32
__IO_EXTERN IO_LWORD intpnd122;  
#define INTPND122 intpnd122
__IO_EXTERN IO_WORD intpnd22;  
#define INTPND22 intpnd22
__IO_EXTERN IO_WORD intpnd12;  
#define INTPND12 intpnd12
__IO_EXTERN IO_LWORD intpnd342;  
#define INTPND342 intpnd342
__IO_EXTERN IO_WORD intpnd42;  
#define INTPND42 intpnd42
__IO_EXTERN IO_WORD intpnd32;  
#define INTPND32 intpnd32
__IO_EXTERN IO_LWORD msgval122;  
#define MSGVAL122 msgval122
__IO_EXTERN IO_WORD msgval22;  
#define MSGVAL22 msgval22
__IO_EXTERN IO_WORD msgval12;  
#define MSGVAL12 msgval12
__IO_EXTERN IO_LWORD msgval342;  
#define MSGVAL342 msgval342
__IO_EXTERN IO_WORD msgval42;  
#define MSGVAL42 msgval42
__IO_EXTERN IO_WORD msgval32;  
#define MSGVAL32 msgval32
#endif                   /* __FASM__    */
#endif                   /* __MB91XXX_H */
#endif                   /* __IO_DEFINE */
