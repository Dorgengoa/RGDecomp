/* rgp:protos */
#define RGP_SELF_ActInfoAbltClone_22ec60 1
#define RGP_SELF_CopyPair 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    void *a;
    void *b;
} Pair;

typedef struct {
    void *f0;
    Pair *f4;
    s16 f8;
    s16 fA;
} Rec;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

/* N5: the helper returns s32 and `ok` is the u8 LOCAL.  Retail's two `andi
   $2,$2,0xFF` are the SUNK narrowing of the u8 local -- one duplicated into
   the beql's likely delay slot, one after the second sltu -- and no third andi
   at the call site.  Measured: (u8 local, u8 return) 104 words and
   (s32 local, u8 return) 104 words, both one long against retail's 103; the
   extra word is the caller-side `andi` of the u8 RETURN TYPE. */
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

s32 ActInfoAbltClone_22ec60(Rec *d, Rec *s, void *heap, void *ctx)
{
    s32 i;
    s32 n;

    d->f0 = 0;
    d->f4 = 0;
    d->f8 = 0;
    d->fA = -1;
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
    d->f0 = StrPoolIntern_302fd0(ctx, s->f0, heap);
    if (d->f0 == 0) {
        return 0;
    }
    d->fA = s->fA;
    return 1;
}
