#include "types.h"

struct Vec4 { f32 x; f32 y; f32 z; f32 w; };
struct T39B290 { u8 pad000[0x18]; void *f18; };

extern f32 D_0047FF90;
extern f32 D_0047FF94;
extern f32 D_0047FF98;
extern f32 D_0047FF9C;
extern void ModelSetPos_151110(void *q, struct Vec4 *v);

void InsectCageSlotSetPos_39b290(struct T39B290 *p, f32 x, f32 y, f32 z)
{
    struct Vec4 v;
    void *q;

    q = p->f18;
    if (q != 0) {
        v.x = D_0047FF90;
        v.y = D_0047FF94;
        v.z = D_0047FF98;
        v.w = D_0047FF9C;
        v.x = x;
        v.y = y;
        v.z = z;
        ModelSetPos_151110(q, &v);
    }
}
