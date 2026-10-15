#include "types.h"

/* Erase a handle's entry from the table's side map, then release the record.
   Head of a 4-member clone group (192 B each) with EffHdlRemove_1a36e0 /
   EffHdlRemove_1a3900 / EffHdlRemove_1a3c80, which differ only in their three callees.

   The handle lookup is the body of HandleTableGet_1a1d50, INLINED -- read that unit for
   why the null test, the `||` and the `(g = k.h.gen)` assignment are spelled
   the way they are.  Three things here are measured:

   * the helper must be `inline`.  Plain `static` is NOT inlined at -O4: mwcc
     emits it as its own `.text` and the unit fails admission condition 4
     ([[levers.d/mwcc-section-per-function]]).  ⚠ bytecheck scored that object
     at 30 words -- the HELPER's length -- so a two-.text unit reads as a
     plausible near miss, not as an error.
   * `*(volatile u32 *)&h` at the last call.  Without the pin mwcc keeps the
     handle in a callee-saved register (`daddu s1,a1,$0` + an `s1` save pair +
     a `dsll32`/`dsra32` widening) and the unit is 4 words long; retail re-reads
     the parameter's home slot ([[levers.d/mwcc-volatile-access-site-pin]]).
     The callee's parameter TYPE is inert here -- five spellings, one object.
   * declaration order `it, k, it2` sets the three stack slots
     (0x2C / 0x28 / 0x24): earlier-declared takes the HIGHER slot.  Declaring
     the copy inside the inline helper instead always puts it lowest, and
     scope-nesting the locals moves nothing (K/L arms). */

typedef union Handle {
    u32 all;
    struct { u16 idx; u16 gen; } h;
} Handle;

typedef struct Rec {
    u8  pad000[0x4];
    u32 m4;
    u8  pad008[0x8];
} Rec;

typedef struct Table {
    u8    pad000[0x4];
    u32   count;
    Rec  *recs;
    u8    pad00C[0x8];
    u32  *tags;
    u8    pad018[0xC];
    u32   m24;
} Table;

extern void StrMapFind_1a4ca0(u32 *out, u32 *map, u32 *key);
extern void StrMapErase_1a5640(u32 *map, u32 *it);
extern void EffHdlRelease_1a3f70(Table *t, u32 id);

static inline Rec *lookup(Table *t, Handle *kp)
{
    u16 g;

    if (((kp->all != 0) ^ 1) != 0) {
        return NULL;
    }
    if (kp->h.idx >= t->count || t->tags[kp->h.idx] != (g = kp->h.gen)) {
        return NULL;
    }
    return &t->recs[kp->h.idx];
}

void EffHdlRemove_1a3c80(Table *t, Handle h)
{
    Rec *r;
    u32 it;
    Handle k;
    u32 it2;

    k = h;
    r = lookup(t, &k);
    if (r != NULL) {
        StrMapFind_1a4ca0(&it, &t->m24, &r->m4);
        it2 = it;
        StrMapErase_1a5640(&t->m24, &it2);
        EffHdlRelease_1a3f70(t, *(volatile u32 *)&h);
    }
}
