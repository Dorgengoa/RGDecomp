/* rgp:protos */
#define RGP_SELF_DataTableCmdAllocSubEntries_3f47a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_propagation off

/* s44g clone pair (DataTableCmdAllocSubEntries_3f47a0 / DataTableCmdAllocSubEntries_416120). Draft, 8 bad of 50 words
   (exact length). The discovered parameter (arg0, passed straight through
   to VariantGetInt_15f780 -- retail never writes $4 before that call, which m2c
   missed and rendered as a `void` function) fixed the first 10 of the
   original 24 bad words (a register-allocation cascade: without it mwcc
   put `index` in a0 instead of retail's a1 all the way through the guard
   chain).

   ⚠ RESIDUE: the remaining 8 words are a register-lifetime scheduling
   difference around `ret = VariantGetInt_15f780(arg0)` inside `if (ret > 0)`.
   Retail keeps the raw call return in v0 for the store, the branch test
   AND the `* 0xC` multiply, and defers copying it to a callee-saved
   register (s2) until just before the FIRST call that would clobber it
   (ArenaNew_3f5e80), using s2 only for the LAST argument of the following
   ConstructNewArray_100710 call. Every spelling tried here that keeps a single
   `ret` variable for all four uses (store, test, multiply, final arg)
   makes mwcc promote it to s2 immediately after the call -- BEFORE the
   branch is even tested -- which is 2 words of pure reordering, not a
   different instruction count. Rereading the field back via
   `elem->unk8` for the multiply and the final argument (this file's
   current spelling) fixes the ordering of the branch+store (now
   byte-identical through 0x3D47FC) but turns the deferred COPY into a
   real reload (`lw s2,8(s1)` instead of retail's `daddu s2,v0,0`),
   which is the remaining 8-word residue. Using `elem->unk8` for the
   final argument ALONE (keeping `ret` for the multiply) compiles 3
   words SHORT: mwcc proves the reload has no intervening call to
   survive and drops the saved register entirely. Untried: whatever
   source shape makes mwcc special-case "the immediately-preceding call
   result, not yet copied anywhere" as sinkable into a delay slot one
   statement later than usual -- likely needs the branch's OWN condition
   written as a comma-expression the way the mirrored branch-likely case
   in mwcc-branch-likely-duplication.md was solved, but no combination of
   comma/assignment-expression forms tried here moved the copy. */

typedef struct Elem003f47a0 {
    u8 pad0[0x8];
    s32 unk8;
    s32 unkC;
    u8 pad10[0x14 - 0x10];
} Elem003f47a0;

typedef struct Ctx003f47a0 {
    u8 pad00[0x6C];
    u8 unk6C[0x10];
    s16 unk7C;
    u8 pad7E[0x8C - 0x7E];
    Elem003f47a0 *unk8C;
    u8 pad90[0x94 - 0x90];
    s32 unk94;
} Ctx003f47a0;

extern Ctx003f47a0 *D_004830F8;
extern s16 D_004830FC;

/*rgp*/
/*rgp*/
/*rgp*/

/* arg0 flows straight through to VariantGetInt_15f780 and is otherwise unused --
   retail never writes $4 between function entry and that call. */
s32 DataTableCmdAllocSubEntries_3f47a0(s32 arg0)
{
    Ctx003f47a0 *ctx;
    s16 count;
    s32 index;
    Elem003f47a0 *elem;
    s32 ret;

    ctx = D_004830F8;
    count = ctx->unk7C;
    if (count <= 0) {
        return 1;
    }
    index = D_004830FC - 1;
    if (index >= count) {
        return 1;
    }
    elem = ctx->unk8C + index;
    elem->unk8 = VariantGetInt_15f780(arg0);
    if (elem->unk8 > 0) {
        elem->unkC = ((s32)ConstructNewArray_100710(ArenaNew_3f5e80(elem->unk8 * 0xC + 0x10, ctx->unk6C, 4, -1), 0, 0, 0xC, elem->unk8));
    } else {
        elem->unkC = 0;
    }
    ctx->unk94 = 0;
    return 1;
}
