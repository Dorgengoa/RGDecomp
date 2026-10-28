/* rgp:protos */
#include "port/game_protos.h"
#line 1
/* rg:datareloc */
/* Generated: do not edit. */
#include "types.h"
extern void MpegMcLumaAvgHalfHV_10ed80(void);
extern void MpegMcLumaAvgHalfH_10ebd8(void);
extern void MpegMcLumaAvgHalfV_10ea10(void);
extern void MpegMcLumaAvg_10e8c0(void);
extern void MpegMcLumaCopy_10e2c8(void);
extern void MpegMcLumaHalfHV_10e6c8(void);
extern void MpegMcLumaHalfH_10e560(void);
extern void MpegMcLumaHalfV_10e3d8(void);
u32 D_00445F90[8] __attribute__((section(".data$rg00445F90"), aligned(16))) = {
    (u32)&MpegMcLumaCopy_10e2c8, (u32)&MpegMcLumaHalfV_10e3d8, (u32)&MpegMcLumaHalfH_10e560, (u32)&MpegMcLumaHalfHV_10e6c8, (u32)&MpegMcLumaAvg_10e8c0, (u32)&MpegMcLumaAvgHalfV_10ea10, (u32)&MpegMcLumaAvgHalfH_10ebd8, (u32)&MpegMcLumaAvgHalfHV_10ed80
};
typedef char data2c_sizecheck_00445F90[(sizeof(D_00445F90) == 32) ? 1 : -1];
