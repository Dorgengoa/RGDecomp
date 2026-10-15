#include "types.h"

typedef unsigned __int128 u128;

typedef union V228 {
    u128 q;
    struct {
        f32 x;
        f32 y;
        f32 z;
        f32 w;
    } v;
} V228;

typedef struct S228 {
    u8    pad000[0x80];
    s32   f80;
    u8    pad084[0xFC];
    V228  f180;
    u8    pad190[0x10];
    V228  f1A0;
} S228;

void ProjectileSetPos_228e50(S228 *p, f32 x, f32 y, f32 z)
{
    p->f180.v.x = x;
    p->f180.v.y = y;
    p->f180.v.z = z;
    p->f180.v.w = 1.0f;
    if ((p->f80 & 0x80000000) != 0) {
        p->f1A0.q = p->f180.q;
    }
}
