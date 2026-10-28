/* rgp:protos */
#define RGP_SELF_EvCmdVecAdd_25de90 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct V25D {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} V25D;

typedef struct F25D {
    u8  pad000[0x4];
    f32 m4;
} F25D;

typedef struct A25D {
    u8 pad000[0x8];
} A25D;

typedef struct P25D {
    u8    pad000[0x4];
    F25D *m4;
    u8    pad008[0x4];
    F25D *mC;
    u8    pad010[0x4];
    F25D *m14;
    u8    m18[0x18];
    u8    m30[0x10];
} P25D;

/*rgp*/
/*rgp*/
/*rgp*/

s32 EvCmdVecAdd_25de90(A25D *p, s32 mode)
{
    P25D *o;
    V25D v40 __attribute__((aligned(16)));
    V25D v30 __attribute__((aligned(16)));
    V25D v20 __attribute__((aligned(16)));

    o = (P25D *)p;
    switch (mode) {
    case 6:
        v30.x = o->m4->m4;
        v30.y = o->mC->m4;
        v30.z = o->m14->m4;
        v30.w = 1.0f;
        ScriptArgsToVec4_26a220(&v20, o->m18);
        break;
    case 9:
        ScriptArgsToVec4_26a220(&v30, o->m18);
        ScriptArgsToVec4_26a220(&v20, o->m30);
        break;
    default:
        return 0;
    }
    VecAdd_13be20(&v40, &v30, &v20);
    ScriptSetRefFloat_26a1c0(p++, v40.x);
    ScriptSetRefFloat_26a1c0(p++, v40.y);
    ScriptSetRefFloat_26a1c0(p++, v40.z);
    return 1;
}
