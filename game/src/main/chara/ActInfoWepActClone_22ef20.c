/* rgp:protos */
#define RGP_SELF_ActInfoWepActClone_22ef20 1
#define RGP_SELF_CopyPair 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    void *a;
    void *b;
} Pair;

typedef struct {
    s16 f0;
    s16 f2;
    Pair *f4;
    s16 f8;
} Rec;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

static inline s32 CopyPair(Pair *dp, Pair *sp, void *heap, void *ctx)
{
    u8 ok;

    dp->a = 0;
    dp->b = 0;
    if (sp == 0 || heap == 0) {
        return 0;
    }
    dp->a = StrPoolIntern_302fd0(ctx, sp->a, heap);
    dp->b = StrPoolIntern_302fd0(ctx, sp->b, heap);
    ok = (dp->a != 0);
    if (ok != 0) {
        ok = (dp->b != 0);
    }
    return ok;
}

s32 ActInfoWepActClone_22ef20(Rec *d, Rec *s, void *heap, void *ctx)
{
    s32 i;
    s32 n;

    d->f0 = -1;
    d->f2 = -1;
    d->f4 = 0;
    d->f8 = 0;
    if (s == 0 || heap == 0) {
        return 0;
    }
    if (s->f4 != 0) {
        n = s->f8;
        if (n > 0) {
            d->f4 = ((Pair *)ConstructNewArray_100710(MemStackNew_14e1b0(n * 8 + 0x10, heap), ActInfoAliasPairCtor_22f100, 0, 8, n));
            if (d->f4 == 0) {
                return 0;
            }
            d->f8 = s->f8;
            for (i = 0; i < d->f8; i++) {
                if (CopyPair(d->f4 + i, s->f4 + i, heap, ctx) == 0) {
                    return 0;
                }
            }
        }
    }
    d->f0 = s->f0;
    d->f2 = s->f2;
    return 1;
}
