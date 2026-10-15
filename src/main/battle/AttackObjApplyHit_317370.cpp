#include "types.h"

struct V16 {
    f32 x, y, z, w;
} __attribute__((aligned(16)));

struct Vec4 {
    f32 x, y, z, w;
};

struct P {
    Vec4 v;      /* +0x00 */
    s16  a;      /* +0x10 */
    s16  b;
    s16  c;
    s16  d;
    s16  e;
    s16  f;
    s16  g;      /* +0x1C */
    u8   pad1E[0xA];
};

struct Q {
    void *self;  /* +0x00 */
    P    *p;     /* +0x04 */
};

struct A {
    s32  m00;
    u8   pad04[4];
    s32  m08;
    s32  m0C;
    s32  m10;
    u8   pad14[0xC];
    V16  m20;
    u8   pad30[4];
    s32  m34;
    s32  m38;
};

class Obj {
    u8  pad000[0x80];
public:
    s32 m80;               /* +0x80 */
    u8  pad84[0x8E - 0x84];
    s16 m8E;               /* +0x8E */
    u8  pad90[0xB0 - 0x90];
    /* +0x08 */ virtual void s08();
    /* +0x0C */ virtual void s0C();
    /* +0x10 */ virtual void s10();
    /* +0x14 */ virtual void s14();
    /* +0x18 */ virtual void s18();
    /* +0x1C */ virtual void s1C();
    /* +0x20 */ virtual void s20();
    /* +0x24 */ virtual void s24();
    /* +0x28 */ virtual void s28();
    /* +0x2C */ virtual void s2C();
    /* +0x30 */ virtual s32 f30(s32 v);
    /* +0x34 */ virtual void s34();
    /* +0x38 */ virtual void s38();
    /* +0x3C */ virtual void s3C();
    /* +0x40 */ virtual void s40();
    /* +0x44 */ virtual void s44();
    /* +0x48 */ virtual void s48();
    /* +0x4C */ virtual s32 f4C(Obj *o);
    /* +0xB0 is the vptr */
    u8  padb4[0xB8 - 0xB4];
    s16 mB8;               /* +0xB8 */
    u8  padba[0x170 - 0xBA];
    V16 m170;              /* +0x170 */
};

extern "C" void VecCopy_1cbe30(P *p, V16 *v);
extern "C" s32  BattleApplyHit_2ef930(Q *q);

extern "C" s32 AttackObjApplyHit_317370(Obj *self, A *a)
{
    P p;
    Q q;

    if (self->f30(a->m08) == 0) {
        return 0;
    }
    if (self->f4C(self) == 0) {
        return 0;
    }
    self->m8E = a->m34;
    p.v.x = 0.0f;
    p.v.y = 0.0f;
    p.v.z = 0.0f;
    p.v.w = 1.0f;
    p.a = -1;
    p.b = -1;
    p.c = -1;
    p.d = -1;
    p.e = -1;
    p.f = -1;
    p.g = -1;
    VecCopy_1cbe30(&p, &a->m20);
    p.a = a->m00;
    p.b = a->m08;
    p.c = a->m10;
    p.d = a->m0C;
    p.e = a->m38;
    p.f = self->mB8;
    p.g = a->m34;
    q.self = self;
    q.p = &p;
    if (BattleApplyHit_2ef930(&q) == 0) {
        return 0;
    }
    *(__int128 *)&self->m170 = *(__int128 *)&a->m20;
    self->m80 |= 2;
    self->mB8++;
    return 1;
}
