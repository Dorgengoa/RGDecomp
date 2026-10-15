#include "types.h"

typedef struct { s16 a, b, c; } E6;

typedef struct T230760 {
    f32 f00[6];
    s32 f18[6];
    f32 f30[6];
    f32 f48[3];
    s32 f54;
    s32 f58;
    s32 f5C;
    s16 f60;
    s16 f62;
    E6  e[4];
} T230760;

extern void ClearU32Bytes_302f20(E6 *);

void CharaEffEntryInit_230760(T230760 *o)
{
    s32 i;

    o->f54 = 0;
    o->f58 = 0;
    o->f60 = 0;
    o->f62 = 2000;
    o->e[0].c = -1;
    ClearU32Bytes_302f20(&o->e[0]);
    o->e[1].c = -1;
    ClearU32Bytes_302f20(&o->e[1]);
    o->e[2].c = -1;
    ClearU32Bytes_302f20(&o->e[2]);
    o->e[3].c = -1;
    ClearU32Bytes_302f20(&o->e[3]);
    o->f5C = 0;
    for (i = 0; i < 6; i++) {
        o->f18[i] = 0;
    }
    for (i = 0; i < 6; i++) {
        o->f00[i] = 0.0f;
    }
    o->f30[0] = 0.0f;
    o->f30[1] = 0.0f;
    o->f30[2] = 0.0f;
    o->f30[3] = 0.0f;
    o->f30[4] = 0.0f;
    o->f30[5] = 0.0f;
    o->f48[0] = 1.0f;
    o->f48[1] = 1.0f;
    o->f48[2] = 1.0f;
}
