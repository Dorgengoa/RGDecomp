#include "types.h"
#include "vec.h"

#define ZERO16(d) { u8 *p_ = (u8 *)(d); u32 n_ = 0x10; if (p_ != 0) while (n_) { *p_ = 0; n_--; p_++; } }

typedef struct Dst { Vec4 m0; Vec4 m10; } Dst;
typedef struct Src { u8 type; u8 pad1[0xF]; Vec4 m10; Vec4 m20; } Src;

extern void VecAdd_13be20(Vec4 *, const Vec4 *, const Vec4 *);
extern void VecSub_13be40(Vec4 *, const Vec4 *, const Vec4 *);
extern void VecMaxMin_13df70(void *, void *, void *, void *);
extern void VecSubInPlace_13e050(void *, void *);
extern void VecAddInPlace_13e070(void *, void *);
extern f32 D_0045B080[];

void HitShapeCalcBounds_315140(Dst *d, Src *s)
{
    switch (s->type) {
    case 1: {
        Vec4 t;
        ZERO16(&t);
        t.z = t.y = t.x = s->m10.w;
        VecAdd_13be20(&d->m0, &s->m10, &t);
        VecSub_13be40(&d->m10, &s->m10, &t);
        break;
    }
    case 2: {
        Vec4 t;
        ZERO16(&t);
        t.z = t.y = t.x = s->m10.w;
        VecMaxMin_13df70(d, &d->m10, &s->m10, &s->m20);
        VecAddInPlace_13e070(d, &t);
        VecSubInPlace_13e050(&d->m10, &t);
        break;
    }
    case 3: {
        Vec4 t;
        ZERO16(&t);
        t.z = t.y = t.x = s->m10.w;
        VecMaxMin_13df70(d, &d->m10, &s->m10, &s->m20);
        VecAddInPlace_13e070(d, &t);
        VecSubInPlace_13e050(&d->m10, &t);
        break;
    }
    case 4: {
        Vec4 t;
        ZERO16(&t);
        t.z = t.x = s->m10.w;
        VecAdd_13be20(&d->m0, &s->m10, &t);
        VecSub_13be40(&d->m10, &s->m10, &t);
        d->m10.y = d->m10.y - 100.0f * D_0045B080[0];
        break;
    }
    }
}
