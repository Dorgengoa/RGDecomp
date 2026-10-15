#include "types.h"

/* N5: this unit is a .cpp for ONE word.  Its only residue in C was
   0x0022E9AC `daddiu $2,$0,0x1` vs our `addiu` -- the literal-1 width, which
   M5 measured unreachable from every C spelling (s32 and u64 helper return
   types gave identical objects).  M1 overturned that null in C++: `bool`
   was not among the nine arms and reaches `daddiu`.  Helper returns bool. */

typedef struct {
    void *a;
    f32 b;
    f32 c;
} Item;

typedef struct {
    void *f0;
    s16 f4;
    s16 f6;
    Item *f8;
} Rec;

extern "C" void *MemStackNew_14e1b0(s32, void *);
extern "C" Item *ConstructNewArray_100710(void *, void *, s32, s32, s32);
extern "C" void *StrPoolIntern_302fd0(void *, void *, void *);
extern "C" void CharaTableSubRecItemCtor_22ea40(void);

static inline bool CopyItem(Item *dp, Item *sp, void *heap, void *ctx)
{
    dp->a = 0;
    dp->b = 1.0f;
    dp->c = 0.0f;
    if (sp == 0 || heap == 0) {
        return false;
    }
    dp->a = sp->a;
    dp->b = sp->b;
    dp->c = sp->c;
    dp->a = StrPoolIntern_302fd0(ctx, sp->a, heap);
    if (dp->a == 0) {
        return false;
    }
    return true;
}

extern "C" s32 CharaTableSubRecCloneMaybe_22e880(Rec *d, Rec *s, void *heap, void *ctx)
{
    s32 i;
    s32 n;

    d->f0 = 0;
    d->f4 = 0;
    d->f6 = 0;
    d->f8 = 0;
    if (s == 0 || heap == 0) {
        return 0;
    }
    if (s->f8 != 0) {
        n = s->f6;
        if (n > 0) {
            d->f8 = ConstructNewArray_100710(MemStackNew_14e1b0(n * 12 + 0x10, heap), CharaTableSubRecItemCtor_22ea40, 0, 0xC, n);
            if (d->f8 == 0) {
                return 0;
            }
            d->f6 = s->f6;
            for (i = 0; i < d->f6; i++) {
                /* N5: `== 0` on a bool return PROMOTES it and costs an
                   `andi $2,$2,0xFF` at the join (102 words vs retail's 101).
                   Testing the bool directly keeps retail's bare `bnel`. */
                if (!CopyItem(d->f8 + i, s->f8 + i, heap, ctx)) {
                    return 0;
                }
            }
        }
    }
    d->f4 = s->f4;
    d->f0 = StrPoolIntern_302fd0(ctx, s->f0, heap);
    return d->f0 != 0;
}
