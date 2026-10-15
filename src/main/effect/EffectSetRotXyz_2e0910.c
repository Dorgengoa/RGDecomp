#include "types.h"

typedef struct Vec4 { f32 x; f32 y; f32 z; f32 w; } Vec4;

extern f32 D_0047EF00;
extern f32 D_0047EF04;
extern f32 D_0047EF08;
extern f32 D_0047EF0C;
extern void EffectSetRot_2e09f0(void *a, void *b, Vec4 *v);

void EffectSetRotXyz_2e0910(void *a, void *b, f32 x, f32 y, f32 z)
{
    Vec4 v;

    v.x = D_0047EF00;
    v.y = D_0047EF04;
    v.z = D_0047EF08;
    v.w = D_0047EF0C;
    v.x = x;
    v.y = y;
    v.z = z;
    EffectSetRot_2e09f0(a, b, &v);
}
