#pragma warn_illpragma on
#pragma opt_optimizecontrolflow off
#include "types.h"

extern void sceDmaSend_10a040(s32, s32);
extern void sceDmaSync_10a2e0(s32, s32, s32);
extern void DrawCtxVif1HandlerStop_15dc40(void);
extern s32 VoBufGetWriteTag_1d48c0(void *);
extern void *VoBufGetNextTag_1d4900(void *);
extern void *VoBufGetTag_1d4940(void *);
extern s32 sceDmaGetChan(s32);
extern u8 D_004B3330[0x400];

void MovieFrameResend_1d4be0(void)
{
u8 *var_17;
u64 temp_4;
s32 temp_16;
var_17 = (u8 *)VoBufGetTag_1d4940(&(*(u8 *)D_004B3330));
    if (var_17 == NULL) {
        var_17 = (u8 *)VoBufGetNextTag_1d4900(&(*(u8 *)D_004B3330));
    }
    if(var_17==(u8*)VoBufGetWriteTag_1d48c0(D_004B3330))return;
    DrawCtxVif1HandlerStop_15dc40();temp_16=sceDmaGetChan(2);
    temp_4=*(s32*)var_17;
    if(temp_4==3 || temp_4==2){sceDmaSend_10a040(temp_16,*(s32*)(var_17+0x40));sceDmaSync_10a2e0(temp_16,0,0);}
}
