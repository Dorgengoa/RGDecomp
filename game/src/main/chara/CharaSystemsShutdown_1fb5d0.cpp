/* rgp:protos */
#line 1
#include "types.h"

struct C17300 {
    u8 pad000[0x4394];
    VC_VPTR_MEMBER;
    s32 v1() { return VCM0(s32, 0xC); }
};

extern "C" s32 GetCurrentScene_1f5be0(void);
extern "C" void CharaResReleaseAllNpc_1f1070(void *, s32);
extern "C" void CharaResReleaseAllMon_1f1060(void *, s32);
extern "C" void CharaResReleaseHeapData_1f0f70(void *);
extern "C" void CharaResReleaseHeapDataThunk_1f0f70(void *);
extern "C" void CharaDataMgrInit_1edf40(void *);
extern "C" void CharaResMgrInit_1f2ed0(void *);
extern "C" void ActionMgrReset_234860(void *);
extern "C" void InsectCageMgrShutdown_39b1b0(void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern "C" u8 D_004B69C0[];
extern "C" u8 D_004B7960[];
extern "C" u8 D_004B8680[];
extern "C" u8 D_004B8700[];

extern "C" s32 CharaSystemsShutdown_1fb5d0(void)
{ s32 rgp_v0;
    s32 r0;

    r0 = GetCurrentScene_1f5be0();
    CharaResReleaseAllNpc_1f1070(D_004B7960, r0);
    CharaResReleaseAllMon_1f1060(D_004B7960, r0);
    CharaResReleaseHeapData_1f0f70(D_004B7960);
    CharaResReleaseHeapDataThunk_1f0f70(D_004B7960);
    CharaDataMgrInit_1edf40(D_004B69C0);
    CharaResMgrInit_1f2ed0(D_004B7960);
    ActionMgrReset_234860(D_004B8680);
    InsectCageMgrShutdown_39b1b0(D_004B8700);
    rgp_v0 = ((struct C17300 *)r0)->v1();
return rgp_v0; }
