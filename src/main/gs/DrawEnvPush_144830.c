#include "types.h"

#pragma divbyzerocheck on

typedef struct F2_144830 { f32 a, b; } F2_144830;
typedef struct F4_144830 { f32 a, b, c, d; } F4_144830;
typedef struct W10_144830 { s32 b[10]; } W10_144830;
typedef struct D2_144830 { s64 b[2]; } D2_144830;
typedef struct D16_144830 { s64 b[16]; } D16_144830;
typedef struct D12_144830 { s64 b[12]; } D12_144830;

typedef struct T144830 {
    s32 m00;
    s32 m04;
    s32 m08;
    s32 m0C;
    s32 m10;
    s32 m14;
    s32 m18;
    s32 m1C;
    s32 m20;
    s32 m24;
    s32 m28;
    s32 m2C;
    s32 m30;
    s32 m34;
    s32 m38;
    F2_144830 m3C;
    W10_144830 m44;
    u8 pad6C[4];
    D2_144830 m70;
    D16_144830 m80;
    D12_144830 m100;
    F4_144830 m160;
    s32 m170;
    s32 m174;
    s32 m178;
    s32 m17C;
    s32 m180;
    s32 m184;
    s32 m188;
    u8 pad18C[4];
} T144830;

typedef struct P144830 {
    u8 pad00[0x270];
    T144830 *cur;
    u8 pad274[0xC];
    T144830 arr[8];
} P144830;

void DrawEnvPush_144830(P144830 *p)
{
    T144830 *d;
    T144830 *s;
    T144830 *n;

    s = p->cur;
    if (s - p->arr < 7) {
        d = *(T144830 *volatile *)&p->cur;
        n = d + 1;
        p->cur = n;
        n->m00 = s->m00;
        n->m04 = s->m04;
        n->m08 = s->m08;
        n->m0C = s->m0C;
        n->m10 = s->m10;
        n->m14 = s->m14;
        n->m18 = s->m18;
        n->m1C = s->m1C;
        n->m20 = s->m20;
        n->m24 = s->m24;
        n->m28 = s->m28;
        n->m2C = s->m2C;
        n->m30 = s->m30;
        n->m34 = s->m34;
        n->m38 = s->m38;
        n->m3C = s->m3C;
        n->m44 = s->m44;
        n->m70 = s->m70;
        n->m80 = s->m80;
        n->m100 = s->m100;
        n->m160 = s->m160;
        n->m170 = s->m170;
        n->m174 = s->m174;
        n->m178 = s->m178;
        n->m17C = s->m17C;
        n->m180 = s->m180;
        n->m184 = s->m184;
        n->m188 = s->m188;
    }
}
