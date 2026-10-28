/* rgp:protos */
#define RGP_SELF_ActInfoEvntClone_22f1e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct E_0022f1e0 { u8 b[12]; } E_0022f1e0;

typedef struct D_0022f1e0 {
    s32 f0;
    E_0022f1e0 *f4;
    s16 f8;
    s16 fA;
} D_0022f1e0;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 ActInfoEvntClone_22f1e0(D_0022f1e0 *out, D_0022f1e0 *src, s32 p2, void *ctx)
{
    s32 n;
    s32 i;
    void *q;
    E_0022f1e0 *r;
    s32 r2;
    out->f0 = 0;
    out->f4 = 0;
    out->f8 = 0;
    out->fA = 0;
    if (src == 0) goto zero;
    if (src->f0 == 0) goto zero;
    if (src->f4 == 0) goto zero;
    n = src->f8;
    if (n <= 0) goto zero;
    if (p2 != 0) goto ok;
zero:
    return 0;
ok:
    if (src->f4 != 0) {
        if (n > 0) {
            q = MemStackNew_14e1b0(12 * n + 0x10, p2);
            r = ConstructNewArray_100710(q, 0, 0, 0xC, n);
            out->f4 = r;
            if (r == 0) return 0;
            out->f8 = src->f8;
        }
    }
    r2 = ((s32)StrPoolIntern_302fd0(ctx, src->f0, p2));
    out->f0 = r2;
    if (r2 == 0) return 0;
    for (i = 0; i < out->f8; i++) {
        if (VariantArrayClone_3027d0(&out->f4[i], &src->f4[i], p2, 0) == 0) return 0;
    }
    return 1;
}
