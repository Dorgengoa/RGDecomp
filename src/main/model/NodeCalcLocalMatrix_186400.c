#include "types.h"

typedef struct { f32 x, y, z, w; } V4;

extern void MtxLoad3x4_186ec0(void *out, void *p);
extern void MatFromSRTVu0_13bc90(void *out, V4 *a, V4 *b, V4 *c);

typedef struct {
    u8 pad00[0x0C];
    f32 m0C;
    f32 m10;
    f32 m14;
    f32 m18;
    f32 m1C;
    f32 m20;
    f32 m24;
    f32 m28;
    f32 m2C;
    s16 m30;
} Obj_186400;

void NodeCalcLocalMatrix_186400(Obj_186400 *p, void *out)
{
    V4 c;
    V4 b;
    V4 a;

    if (p->m30 != 0) {
        MtxLoad3x4_186ec0(out, p);
    } else {
        c.x = p->m18;
        c.y = p->m1C;
        c.z = p->m20;
        b.x = p->m0C;
        b.y = p->m10;
        b.z = p->m14;
        a.x = p->m24;
        a.y = p->m28;
        a.z = p->m2C;
        MatFromSRTVu0_13bc90(out, &c, &b, &a);
    }
}
