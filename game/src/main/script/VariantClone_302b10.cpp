/* rgp:protos */
#line 1
#include "types.h"

typedef struct Val {
    u8 b0;
    u8 b1;
    u8 b2;
    u8 b3;
} Val;

typedef struct Var {
    s8 type;
    Val v;
} Var;

#define VI(t) (*(s32 *)&(t))
#define VS(t) (*(s8 **)&(t))

extern "C" s32 MemStackStrDup_14cff0(s8 *, s32);
extern "C" s32 StrPoolIntern_302fd0(void *, s8 *, int);

extern "C" s32 VariantClone_302b10(Var *out, Var *in, s32 a2, void *a3)
{
    Val tin __attribute__((aligned(16)));
    Val tout __attribute__((aligned(16)));
    Val t2 __attribute__((aligned(16)));
    Val t1 __attribute__((aligned(16)));
    Val tz __attribute__((aligned(16)));
    Val t0 __attribute__((aligned(16)));

    VI(t0) = 0;
    out->type = 0;
    out->v = t0;
    if (in == 0 || a2 == 0) {
        return 0;
    }
    if (in->type == 2) {
        tin = in->v;
        if (VS(tin) != 0 && *VS(tin) != 0) {
            if (a3 != 0) {
                VI(t2) = StrPoolIntern_302fd0(a3, VS(tin), (int)a2);
                out->type = 2;
                out->v = t2;
            } else {
                VI(t1) = MemStackStrDup_14cff0(VS(tin), a2);
                out->type = 2;
                out->v = t1;
            }
            tout = out->v;
            if (VI(tout) == 0) {
                return 0;
            }
            return 1;
        } else {
            VI(tz) = 0;
            out->type = 2;
            out->v = tz;
        }
    } else {
        *out = *in;
    }
    return 1;
}
