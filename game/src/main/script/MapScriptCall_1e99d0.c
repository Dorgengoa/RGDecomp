/* rgp:protos */
#define RGP_SELF_MapScriptCall_1e99d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Obj180C {
    u8 pad28[0x28];
    s32 unk28;
    u32 unk2C;
    u8 pad30[4];
    s32 unk34;
} Obj180C;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 MapScriptCall_1e99d0(s32 arg0, s32 arg1) {
    u8 spB0[0x60] __attribute__((aligned(16)));
    u8 sp50[0x60] __attribute__((aligned(16)));
    s32 k;
    s32 h;
    Obj180C *o;
    s32 a;
    s32 b;

    o = *(Obj180C **)(((u8 *)GetCurrentScene_1f5be0()) + 0x180C);
    h = ((s32)MemStackHeapAlloc_14db10(o, 2, 0, 0x40));
    if (h == 0) {
        MemStackReturnToOwnerMaybe_14dad0(o);
        return -1;
    }
    ScriptVmCtor_176be0(spB0);
    MemStackCtor_14e030(sp50);
    MemStackClear_14dff0(sp50);
    k = o->unk2C;
    a = o->unk34 - k;
    b = o->unk28 + k * 0x10;
    MemStackInit_14d810(sp50, b, a);
    MemStackReturnToOwnerMaybe_14dad0(o);
    MemStackHeapFree_14dcb0(o, h);
    a = MemStackAllocQw_14d950(sp50, 0x40);
    b = MemStackAllocQw_14d950(sp50, 0x180);
    ScriptVmInit_176af0(spB0, MapAreaGetSeqScript_1dcec0(arg0), a, 0x80, b, 0x200);
    MapScriptCmdTableBuild_1e9af0(spB0);
    return ScriptVmRunEntry_176940(spB0, arg1);
}
