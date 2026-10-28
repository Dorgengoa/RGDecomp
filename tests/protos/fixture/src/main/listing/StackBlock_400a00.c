#include "types.h"
/* stack-block: retail keeps b (sp+0x10) and r (sp+0x20) in one frame block and
   SweepB_400b20(&b) reads b+0x30 = r.d0 */
typedef struct { f32 x, y, z, w; } V4;
typedef struct { f32 t0; f32 t1; u8 pad8[8]; V4 c0; V4 d0; } Ray;
extern void PutPoint_400b00(V4 *p, s32 v);
extern void PutRay_400b10(V4 *c, V4 *d);
extern s32 SweepB_400b20(V4 *p);

s32 StackBlock_400a00(s32 v)
{
    Ray r;
    V4 b;

    PutPoint_400b00(&b, v);
    PutRay_400b10(&r.c0, &r.d0);
    r.t0 = 1.0f;
    return SweepB_400b20(&b);
}
