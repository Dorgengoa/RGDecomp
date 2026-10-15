#include "types.h"

typedef struct VN { s32 m00; f32 m04; } VN;
typedef struct E8 { s32 a; VN *b; } E8;

extern f32 TaggedGetFloat_26a280(E8 *);
extern void ScriptArgsToVec4_26a220(f32 *, E8 *);
extern void sceVu0DivVector(f32 *, f32 *, f32);
extern void ScriptSetRefFloat_26a1c0(E8 *, f32);

s32 EvCmdVecDiv_25dbe0(E8 *p0, s32 p1)
{
    f32 w[4];
    f32 v[4];
    f32 f;

    switch (p1) {
    case 4:
        v[0] = p0[0].b->m04;
        v[1] = p0[1].b->m04;
        v[2] = p0[2].b->m04;
        v[3] = 1.0f;
        f = TaggedGetFloat_26a280(p0 + 3);
        break;
    case 7:
        ScriptArgsToVec4_26a220(v, p0 + 3);
        f = TaggedGetFloat_26a280(p0 + 6);
        break;
    default:
        return 0;
    }
    if (f == 0.0f) {
        return 0;
    }
    sceVu0DivVector(w, v, f);
    ScriptSetRefFloat_26a1c0(p0++, w[0]);
    ScriptSetRefFloat_26a1c0(p0++, w[1]);
    ScriptSetRefFloat_26a1c0(p0, w[2]);
    return 1;
}
