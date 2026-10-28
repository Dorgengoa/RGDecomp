/* rgp:protos */
#define RGP_SELF_ScriptCmdDirToEuler_333bf0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct { f32 x, y, z, w; } V4;
typedef struct { V4 a; V4 b; } V8;

extern V4 D_0047F4A0 __attribute__((section(".sdata")));
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 ScriptCmdDirToEuler_333bf0(s32 arg0, s32 arg1)
{
    __attribute__((aligned(16))) unsigned char rgp_blk1[sizeof(union { char m0[0x20 + sizeof(V8)]; char m1[0x0 + sizeof(V4)]; char m2[0x10 + sizeof(V4)]; char m3[0x30]; char m4[0x10]; char m5[0x20]; char m6[0x40]; })]; typedef char rgp_blk1_chk0[(0x0) + sizeof(V4) <= (0x10) && (0x0) >= 0 ? 1 : -1]; typedef char rgp_blk1_chk1[(0x10) + sizeof(V4) <= (0x20) && (0x10) >= 0 ? 1 : -1];
    
    
    V4 s60 __attribute__((aligned(16)));
    V4 s50 __attribute__((aligned(16)));
    V4 s40 __attribute__((aligned(16)));
    f32 ang;
    f32 sn;
    f32 cs;

    if (arg1 != 6 && arg1 != 7) {
        return 0;
    }
    (*(V8 *)(rgp_blk1 + 0x20)).a.x = ScriptSlotGetFloat_334890(arg0 + 0x18);
    (*(V8 *)(rgp_blk1 + 0x20)).a.y = ScriptSlotGetFloat_334890(arg0 + 0x20);
    (*(V8 *)(rgp_blk1 + 0x20)).a.z = ScriptSlotGetFloat_334890(arg0 + 0x28);
    (*(V8 *)(rgp_blk1 + 0x20)).b.w = 1.0f;
    (*(V8 *)(rgp_blk1 + 0x20)).a.w = 0.0f;
    (*(V8 *)(rgp_blk1 + 0x20)).b.x = 0.0f;
    (*(V8 *)(rgp_blk1 + 0x20)).b.y = 0.0f;
    (*(V8 *)(rgp_blk1 + 0x20)).b.z = 0.0f;
    *(V4 *)&s60 = D_0047F4A0;
    ang = 0.0f;
    if (arg1 == 7) {
        ang = ScriptSlotGetFloat_334890(arg0 + 0x30);
    }
    VecCross_1cb9f0(&s50, &s60, &(*(V8 *)(rgp_blk1 + 0x20)));
    VecCross_1cb9f0(&s60, (V4 *)&(*(V8 *)(rgp_blk1 + 0x20)), (V8 *)&s50);
    sn = Sinf_128fd0(ang);
    cs = Cosf_128d30(ang);
    VecLinearCombine_1cb8b0(&(*(V4 *)(rgp_blk1 + 0x0)), &s50, &s60, cs, sn);
    VecLinearCombine_1cb8b0(&(*(V4 *)(rgp_blk1 + 0x10)), &s50, &s60, -sn, cs);
    MatGetEulerRot_1cb160(&s40, &(*(V4 *)(rgp_blk1 + 0x0)));
    ScriptSlotStoreFloatRef_3347d0(arg0, s40.x);
    ScriptSlotStoreFloatRef_3347d0(arg0 + 8, s40.y);
    ScriptSlotStoreFloatRef_3347d0(arg0 + 0x10, s40.z);
    return 1;
}
