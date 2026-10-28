/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsWatchEnter_4ed450 1
#include "port/game_protos.h"
#line 1
/* insmenu 0x004ED450 (140 bytes, 35 instructions) -- clear both of a record's
 * 0x8F-byte name slots and mark the panel dirty.
 * BYTE-IDENTICAL (lane P1 / tag im10, 2026-08-26).  MATCH printed by
 * build/dv_osbuild.py; objdump section set is .text only (no .lit4, no
 * .rodata), so it needs no link plumbing.
 *
 * It was parked for four sessions at 4 bad words -- a clean callee-saved PAIR
 * SWAP, retail holding the CONTEXT in $16 and the RECORD in $17 and mwcc the
 * other way round -- with the DECLARATION-ORDER axis recorded as not merely
 * null but INERT (all six permutations of {ctx, rec, i} emit object 98477666).
 * That is re-confirmed here and it is not the lever.  The lever is:
 *
 *   BOTH `ctx` and `rec` are DEREF-ONLY -- neither is ever used as a bare
 *   value, only as the base of a member access.  A deref-only pointer is
 *   invisible to the declaration-order tie-break (measured in the mini-repro
 *   build/mr-im10w3: with both pointers used bare the swap is LIVE, and ONE
 *   deref-only member of the pair is enough to make it INERT).  Give the
 *   SECOND pointer an intermediate named local -- `tmp = f(); rec = tmp;` --
 *   and the axis REOPENS, because `tmp` has a bare use.  Inside that regime
 *   the only thing that decides the numbering is whether the loop counter is
 *   declared BEFORE the intermediate: `i` before `tmp` gives retail's
 *   ctx=$16 / rec=$17 / i=$18, `tmp` before `i` gives 9 bad words.  Measured
 *   over all 24 permutations, 12/12, in build/mr-im10w5.
 *
 * ★ `sll 3 / addu / sll 4 / subu` on the induction variable is mwcc's expansion
 * of a multiply by 143 -- the element stride of a `[2][0x8F]` array member, not
 * a shift the source wrote.  The same 0x8F is the clear's length, which is what
 * identifies the stride as the element size.
 * ★ `return 1;` closed 2 of the original 6: a constant stored and also
 * returned lands in $2. */
#include "types.h"

typedef struct Ctx Ctx;
struct Ctx {
    u8   pad00[0x24];
    void *field24;
};

typedef struct Rec Rec;
struct Rec {
    u8 pad0000[0x1D0];
    u8 field01D0[2][0x8F];
};

extern u8 D_00484304;           /* gp - 0xE6C */

/*rgp*/
/*rgp*/
/*rgp*/
extern void memset(void *p, s32 v, s32 n);

s32 insmenu_InsectVsWatchEnter_4ed450(void)
{
    Ctx *ctx;
    Rec *rec;
    s32 i;
    Rec *tmp;

    ctx = ((Ctx *)GetGameData_1fede0());
    tmp = ((Rec *)RecordGetPayloadIfKind32_430b30(ctx->field24));
    rec = tmp;
    for (i = 0; i < 2; i++) {
        memset(rec->field01D0[i], 0, 0x8F);
    }
    RecordAdvanceState_430bf0(ctx->field24, 0);
    D_00484304 = 1;
    return 1;
}
