/* rgp:protos */
#define RGP_SELF_EventSysGameInitMaybe_27adc0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma peephole off

/*rgp*/                        /* extern */
/*rgp*/                                /* extern */
/*rgp*/                           /* extern */
/*rgp*/                                 /* extern */
/*rgp*/                                /* extern */
/*rgp*/                                 /* extern */
/*rgp*/                                /* extern */
/*rgp*/                                   /* extern */
/*rgp*/                                /* extern */
/*rgp*/                   /* extern */
/*rgp*/                                 /* extern */
/*rgp*/                                /* extern */
/*rgp*/                                   /* extern */
/*rgp*/                                  /* extern */
extern s8 D_0047E9A8;
extern u8 *D_0047E9AC;
extern s8 D_00482070;
extern s8 D_00482178;
extern s8 D_0048217C;
extern s8 D_00482184;
extern s8 D_00482188;
extern u8 D_004D77B0[0x400];
extern u8 D_004D7810[0x400];
extern u8 D_004D7830[0x400];

void EventSysGameInitMaybe_27adc0(u8 *arg0, s32 arg1) {
    s32 temp_16;

    temp_16 = GetCurrentScene_1f5be0();
    EventSysAllocBuffers_26b650(arg1);
    EventSysSetScene_250b50(temp_16);
    MemStackInit_14d810((unsigned char *)(&(*(s32 *)D_004D77B0)), MemStackAllocAligned64_14da10(arg1, 0x280), 0x280);
    MemStackReset_14d830((u8 *)&(*(s32 *)D_004D77B0));
    MesMgrInit_277b30(((s32)GetMesMgr_277e90()), arg1, (*(s32 *)((u8 *)arg0 + 0x28)) + ((*(s32 *)((u8 *)arg0 + 0x2C)) * 0x10), (long long)(0x338));
    D_0047E9A8 = 1;
    D_0048217C = 0;
    LetterboxReset_278390((u8 *)&(*(s32 *)D_004D7810));
    D_00482178 = 0;
    EventGlobalObjInit_257930();
    SetFieldControlActive_27bd30(0);
    AbilityReqReset_27a610();
    D_00482184 = 0;
    D_00482188 = 0;
    D_0047E9AC = (u8 *)&(*(s32 *)D_004D7830);
    ObjRecFlagsSnapshotStackInit_1d7650(((s32)GetObjRecFlagsSnapshotStack_1d7640()));
    D_00482070 = 0;
}
