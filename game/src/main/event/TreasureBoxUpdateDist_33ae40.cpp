#include "types.h"
#include "vec.h"
#pragma opt_propagation off

typedef struct Obj {
    Vec4 pos;
    Vec4 rot;
    u8 pad20[6];
    s16 m26;
    u8 pad28[4];
    s16 m2C;
    u8 pad2E[0x6C - 0x2E];
    f32 dist;
    bool f0 : 1;
    bool f1 : 1;
    bool f2 : 1;
    bool f3 : 1;
    bool f4 : 1;
} Obj;

extern "C" f32 D_0047F620;
extern "C" f32 D_0047F624;
extern "C" f32 D_0047F628;
extern "C" f32 D_0047F62C;

extern "C" {
f32 VecDistance_13d3d0(Vec4 *a, Vec4 *b);
void MatFromRotPos_1caf90(Mtx4 *m, Vec4 *rot, Vec4 *pos);
void MatMulPoint_1cb8e0(Vec4 *d, Mtx4 *m, Vec4 *v);
s32 TreasureBoxIsOpened_33a240(Obj *o);
}

extern "C" f32 TreasureBoxUpdateDist_33ae40(Obj *o, Vec4 *target)
{
    Mtx4 m __attribute__((aligned(16)));
    Vec4 c __attribute__((aligned(16)));
    Vec4 v __attribute__((aligned(16)));
    bool was;

    was = o->f0;
    o->dist = VecDistance_13d3d0(&o->pos, target);
    o->f0 = false;
    o->f1 = false;
    o->f2 = false;
    o->f3 = false;
    o->f4 = false;
    if (!(o->dist < 0.0f)) {
        if (o->dist <= 1000.0f) {
            o->f0 = true;
            if (o->dist <= 600.0f) {
                if (TreasureBoxIsOpened_33a240(o) == 0) {
                    o->f1 = true;
                }
            }
            if (o->dist <= 400.0f) {
                o->f2 = true;
            }
            if (o->dist <= 200.0f) {
                o->f3 = true;
            }
            if (o->dist <= 40.0f) {
                MatFromRotPos_1caf90(&m, &o->rot, &o->pos);
                c.x = D_0047F620;
                c.y = D_0047F624;
                c.z = D_0047F628;
                c.w = D_0047F62C;
                { Vec4 *p = &c; MatMulPoint_1cb8e0(&v, &m, p); }
                if (VecDistance_13d3d0(&v, target) <= 30.0f) {
                    o->f4 = true;
                }
            }
            if (!was) {
                o->m26 = (o->m26 & ~0x18) | 8;
                o->m2C = (s32)(15.0f - (f32)o->m2C);
            }
        } else if (was) {
            o->m26 = (o->m26 & ~0x18) | 0x10;
            o->m2C = (s32)(15.0f - (f32)o->m2C);
        }
    }
    return o->dist;
}
