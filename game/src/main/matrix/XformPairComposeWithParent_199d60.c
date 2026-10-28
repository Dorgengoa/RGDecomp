/* rgp:protos */
#define RGP_SELF_XformPairComposeWithParent_199d60 1
#define RGP_SELF_func_00199D70 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#include "vec.h"

typedef Mtx4 M34;

typedef struct Obj {
    u8 pad0[0x10];
    Vec4 a10;
    Vec4 a20;
    Vec4 a30;
    Vec4 a40;
    u8 pad50[0x10];
    Vec4 b60;
    Vec4 b70;
    Vec4 b80;
    Vec4 b90;
    u8 padA0[0x48];
    u8 xE8;
    u8 padE9[3];
    s32 xEC;
    u8 xF0;
    u8 xF1;
    u8 padF2[0xE];
    u8 m100[0x40];
} Obj;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void func_00199D70(Obj *self, u8 *out, u8 *out2);

void XformPairComposeWithParent_199d60(Obj *self, u8 *out)
{
    func_00199D70(self, out, out + 0x40);
}

void func_00199D70(Obj *self, u8 *out, u8 *out2)
{
    M34 m __attribute__((aligned(16)));
    Vec4 v70 __attribute__((aligned(16)));
    Vec4 v60 __attribute__((aligned(16)));
    Vec4 v50 __attribute__((aligned(16)));
    f32 sx;
    f32 sy;
    f32 sz;

    VecAdd_13be20(&v70, &self->a10, &self->b60);
    VecAdd_13be20(&v60, &self->a20, &self->b70);
    VecMul_13bd40(&v50, &self->a30, &self->b80);
    MatFromSRTVu0_13bc90(out, &v50, &v60, &v70);
    VecMul_13bd40(out2, &self->a40, &self->b90);
    if (self->xEC != 0) {
        FrameCalcWorldMatrix_148ff0(self->xEC, &m);
        if (self->xF0 != 0 && self->xF1 != 0) {
            VEC4_ZERO(m.r[0]);
            VEC4_ZERO(m.r[1]);
            VEC4_ZERO(m.r[2]);
            m.r[2].z = 1.0f;
            m.r[1].y = 1.0f;
            m.r[0].x = 1.0f;
        } else if (self->xF0 != 0) {
            VecNormalize_13bd90(&m.r[0], &m.r[0]);
            VecNormalize_13bd90(&m.r[1], &m.r[1]);
            VecNormalize_13bd90(&m.r[2], &m.r[2]);
        } else if (self->xF1 != 0) {
            sx = VecLength_13d4a0(&m.r[0]);
            sy = VecLength_13d4a0(&m.r[1]);
            sz = VecLength_13d4a0(&m.r[2]);
            VEC4_ZERO(m.r[0]);
            VEC4_ZERO(m.r[1]);
            m.r[0].x = sx;
            VEC4_ZERO(m.r[2]);
            m.r[1].y = sy;
            m.r[2].z = sz;
        }
        MtxMul_13d240(out, &m, out);
    }
    if (self->xE8 != 0) {
        MtxMul_13d240(out, self->m100, out);
    }
}
