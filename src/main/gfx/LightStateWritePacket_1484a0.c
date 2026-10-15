#include "types.h"
#include "vec.h"

typedef struct {
    u128 q0;
    u128 q10;
    u128 m20[4];
    u128 q60[4];
    u128 qA0;
    u128 qB0;
    u128 qC0;
    u128 qD0;
    u128 qE0[1];
} Src;

typedef struct {
    s32 x0;
    u8 pad4[0x10];
    s32 x14;
} Part;

typedef struct {
    u8 pad0[0xF20];
    Part *part;
    u8 padF24[0x36B4 - 0xF24];
    Src *src;
    s32 x36B8;
} Obj;

typedef struct {
    u128 a;
    u128 b;
    f32 pad[3];
} Light;

extern void FogColRegWrite_156c00(s32, u128 *);
extern void FogCalcCoefs_156c40(s32, u128 *);
extern void sceVu0TransposeMatrix(u128 *, u128 *);

s32 LightStateWritePacket_1484a0(Obj *o, u32 pkt)
{
    u128 *p;
    Part *part;
    Src *s;
    u8 *e;
    u32 *tag;
    u128 *start;
    s32 i;
    s32 n;
    u32 *hdr;
    u128 m[4];
    u128 c;
    s32 h;

    part = o->part;
    if (part == 0) {
        return 0;
    }
    if (&part->x14 == 0) {
        return 0;
    }
    s = o->src;
    if (s == 0) {
        return 0;
    }
    p = (u128 *)pkt;
    start = p;
    hdr = (u32 *)p;
    tag = (u32 *)p + 3;
    p[0] = 0;
    ((u32 *)pkt)[2] = 0x01000101;
    sceVu0TransposeMatrix(m, s->m20);
    p[1] = m[0];
    p[2] = m[1];
    p[3] = m[2];
    p[4] = s->q60[0];
    p[5] = s->q60[1];
    p[6] = s->q60[2];
    p[7] = s->q60[3];
    p[8] = s->q10;
    p[9] = s->qA0;
    p[10] = s->qB0;
    h = o->x36B8;
    if (part->x0 != 0 && h != 0) {
        FogCalcCoefs_156c40(h, &c);
        p[11] = c;
        FogColRegWrite_156c00(h, &p[12]);
    } else {
        p[11] = 0;
        ((f32 *)&p[11])[1] = 255.0f;
        ((f32 *)&p[11])[2] = 255.0f;
        p[12] = 0;
    }
    p[13] = s->qC0;
    p[14] = s->qD0;
    p += 15;
    i = 0;
    do {
        f32 w;
        e = (u8 *)s + i * 0x30 + 0xE0;
        w = *(f32 *)(e + 0x20);
        if (!(w <= 0.0f)) {
            *(f32 *)(e + 0xC) = 1.0f / w;
            p[0] = ((u128 *)e)[0];
            p[1] = ((u128 *)e)[1];
        } else {
            *(s32 *)(e + 0xC) = 0x3F800000;
            p[0] = 0;
            p[1] = 0;
        }
        p += 2;
        i++;
    } while (i < 4);
    n = ((u8 *)p - (u8 *)start) / 4 / 4;
    {
        s32 q = n - 1;
        *tag = (q << 16) | 0x6C00001E;
        *hdr = q | 0x60000000;
    }
    return n;
}
