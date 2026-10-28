/* rgp:protos */
#define RGP_SELF_FuncDataRecVolumeContainsPointMaybe_187080 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#include "vec.h"

typedef struct Obj {
    u8 pad0[0x60];
    s32 flags;      /* 0x60 */
    s32 n;          /* 0x64 */
} Obj;

typedef struct Out {
    s32 mode;       /* 0x00 */
    s32 n;          /* 0x04 */
    u8 pad8[8];
    Mtx4 m;         /* 0x10 */
} Out;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 FuncDataRecVolumeContainsPointMaybe_187080(Obj *o, Vec4 *pos, s32 mode, Out *out, f32 *dist)
{
    Mtx4 m __attribute__((aligned(16)));
    Mtx4 inv __attribute__((aligned(16)));
    Vec4 q __attribute__((aligned(16)));
    Vec4 s __attribute__((aligned(16)));
    Vec4 d __attribute__((aligned(16)));
    s32 flags;
    s32 a;

    if (FuncDataRecIsActiveAt_192170(o, 0) == 0) {
        return 0;
    }
    NodeCalcWorldMatrix_186130(o, &m);
    NodeGetScale_186560(o, &s);
    if (s.x == 0.0f || s.y == 0.0f || s.z == 0.0f) {
        return 0;
    }
    MtxInverse_13cf40(&inv, &m);
    MtxMulPoint_13c890(&d, &inv, pos);
    if (!(VecLength_13d4a0(&d) <= 1.0f)) {
        return 0;
    }
    if (out != 0) {
        if (o->n > 0) {
            out->n = o->n;
        }
        out->mode = mode;
        flags = o->flags;
        a = flags & 2;
        if (a != 0 || (flags & 4)) {
            if (mode == 0) {
                if (a != 0) {
                    return 0;
                }
                if (flags & 4) {
                    return 0;
                }
            } else if (mode == 1) {
                if (a == 0) {
                    return 0;
                }
            } else if (mode == 2) {
                if (!(flags & 4)) {
                    return 0;
                }
            }
        }
        out->m.r[0] = m.r[0];
        out->m.r[1] = m.r[1];
        out->m.r[2] = m.r[2];
        out->m.r[3] = m.r[3];
    }
    if (dist != 0) {
        *dist = VecDistance_13d3d0(&q, pos);
    }
    return 1;
}
