#include "types.h"

typedef struct Vec3 { f32 x, y, z; } Vec3;

extern f32 Cosf_128d30(f32);
extern f32 Sinf_128fd0(f32);
extern void ScriptSetRefFloat_26a1c0(s64 *, f32);
extern void ScriptSetRefInt_26a1e0(s64 *, u8);
extern s32 ScriptGetInt_26a2a0(void);
extern s32 CharaGetEvObjContactXform_2d08c0(s32, Vec3 *, Vec3 *);

s32 EvCmdCharaGetEvObjContactXform_25a420(s64 *arg0, s32 arg1)
{
    Vec3 sp40;
    Vec3 sp30;
    s32 k;

    arg0++;
    k = CharaGetEvObjContactXform_2d08c0(ScriptGetInt_26a2a0(), &sp40, &sp30);
    ScriptSetRefInt_26a1e0(arg0++, k);
    ScriptSetRefFloat_26a1c0(arg0++, sp40.x);
    ScriptSetRefFloat_26a1c0(arg0++, sp40.y);
    ScriptSetRefFloat_26a1c0(arg0++, sp40.z);
    ScriptSetRefFloat_26a1c0(arg0++, sp30.x);
    ScriptSetRefFloat_26a1c0(arg0++, sp30.y);
    ScriptSetRefFloat_26a1c0(arg0++, sp30.z);
    if (arg1 >= 9) {
        ScriptSetRefFloat_26a1c0(arg0++, Sinf_128fd0(sp30.y));
        ScriptSetRefFloat_26a1c0(arg0++, 0.0f);
        ScriptSetRefFloat_26a1c0(arg0, Cosf_128d30(sp30.y));
    }
    return 1;
}
