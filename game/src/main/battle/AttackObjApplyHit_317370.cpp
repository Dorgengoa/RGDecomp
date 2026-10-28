/* rgp:protos */
#line 1
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
    /* +0x08 */ VC_VPTR_MEMBER;
    /* +0x0C */ 
    /* +0x10 */ 
    /* +0x14 */ 
    /* +0x18 */ 
    /* +0x1C */ 
    /* +0x20 */ 
    /* +0x24 */ 
    /* +0x28 */ 
    /* +0x2C */ 
    /* +0x30 */ s32 f30(s32 v, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(s32, (void *, s32, int, int), 0x30, v, rgp_fwd2, rgp_fwd3); }
    /* +0x34 */ 
    /* +0x38 */ 
    /* +0x3C */ 
    /* +0x40 */ 
    /* +0x44 */ 
    /* +0x48 */ 
    /* +0x4C */ s32 f4C(Obj *o) { return VCM(s32, (void *, Obj *), 0x4C, o); }
    /* +0xB0 is the vptr */
    u8  padb4[0xB8 - 0xB4];
    s16 mB8;               /* +0xB8 */
    u8  padba[0x170 - 0xBA];
    V16 m170;              /* +0x170 */
};

extern "C" void VecCopy_1cbe30(P *p, V16 *v);
extern "C" s32  BattleApplyHit_2ef930(Q *q);

extern "C" s32 AttackObjApplyHit_317370(Obj *self, A *a, int rgp_a2, int rgp_a3)
{
    P p __attribute__((aligned(16)));
    Q q __attribute__((aligned(16)));

    if (self->f30(a->m08, (int)(long)(rgp_a2), (int)(long)(rgp_a3)) == 0) {
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
    *(rg_s128 *)&self->m170 = *(rg_s128 *)&a->m20;
    self->m80 |= 2;
    self->mB8++;
    return 1;
}
