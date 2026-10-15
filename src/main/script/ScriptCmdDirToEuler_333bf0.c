#include "types.h"

typedef struct { f32 x, y, z, w; } V4;
typedef struct { V4 a; V4 b; } V8;

extern const V4 D_0047F4A0 __attribute__((section(".sdata")));
extern void MatGetEulerRot_1cb160(V4 *, V4 *);
extern void VecLinearCombine_1cb8b0(V4 *, V4 *, V4 *, f32, f32);
extern void VecCross_1cb9f0(V4 *, V4 *, V8 *);
extern void ScriptSlotStoreFloatRef_3347d0(s32, f32);
extern f32 ScriptSlotGetFloat_334890(s32);
extern f32 Cosf_128d30(f32);
extern f32 Sinf_128fd0(f32);

s32 ScriptCmdDirToEuler_333bf0(s32 arg0, s32 arg1)
{
    V8 p;
    V4 s80;
    V4 s70;
    V4 s60;
    V4 s50;
    V4 s40;
    f32 ang;
    f32 sn;
    f32 cs;

    if (arg1 != 6 && arg1 != 7) {
        return 0;
    }
    p.a.x = ScriptSlotGetFloat_334890(arg0 + 0x18);
    p.a.y = ScriptSlotGetFloat_334890(arg0 + 0x20);
    p.a.z = ScriptSlotGetFloat_334890(arg0 + 0x28);
    p.b.w = 1.0f;
    p.a.w = 0.0f;
    p.b.x = 0.0f;
    p.b.y = 0.0f;
    p.b.z = 0.0f;
    *(V4 *)&s60 = D_0047F4A0;
    ang = 0.0f;
    if (arg1 == 7) {
        ang = ScriptSlotGetFloat_334890(arg0 + 0x30);
    }
    VecCross_1cb9f0(&s50, &s60, &p);
    VecCross_1cb9f0(&s60, (V4 *)&p, (V8 *)&s50);
    sn = Sinf_128fd0(ang);
    cs = Cosf_128d30(ang);
    VecLinearCombine_1cb8b0(&s70, &s50, &s60, cs, sn);
    VecLinearCombine_1cb8b0(&s80, &s50, &s60, -sn, cs);
    MatGetEulerRot_1cb160(&s40, &s70);
    ScriptSlotStoreFloatRef_3347d0(arg0, s40.x);
    ScriptSlotStoreFloatRef_3347d0(arg0 + 8, s40.y);
    ScriptSlotStoreFloatRef_3347d0(arg0 + 0x10, s40.z);
    return 1;
}
