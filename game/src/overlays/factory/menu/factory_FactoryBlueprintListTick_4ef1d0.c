/* rgp:protos */
#define RGP_SELF_factory_FactoryBlueprintListTick_4ef1d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* factory.bin overlay, 0x004EF1D0 -- 212 B / 53 words, 5 branches, 6 calls.
 * EPILOGUE TAIL-MERGE family (scripts/f_tmerge.py), lane fy02.
 *
 * IF-ELSE cell of lane fy01's family key: `b .L004EF294` carries
 * `ld $31,0x10($29)` in its delay slot but the guard is NOT two rows above it
 * (there is a body between), so it is an if/else-if CHAIN and the case order is
 * AS WRITTEN -- confirmed by the `bnel` PAST each arm rather than `beql` into
 * it.  ONE trailing `return 1`.
 *
 * * The chain's first arm is a `&&`, not a nested `if`: when
 *   `factory_FactoryBlueprintCancel_4fb5a0` returns 0 retail branches to .L004EF24C, which is
 *   the NEXT comparison's `addiu $2,$0,1`, i.e. it rejoins the chain instead of
 *   falling out of it.  A nested `if` would jump past everything.
 * * The last arm's `&&` is indistinguishable from a nested `if` because nothing
 *   follows it; it is written `&&` for symmetry with the first.
 * * The result of `func_28E170` must be NAMED -- it is live in $16 across three
 *   compares and two calls.
 * * `extern const u8 D_004B2570[];` gives the `lui 0x4B / addiu 0x2570` pair.
 */

typedef struct Ctx {
    u8    pad00[0x84];
    void *f84;                                  /* +0x84 */
    void *f88;                                  /* +0x88 */
} Ctx;

extern u8 D_004B2570[];
extern Ctx     *D_00484A48;                     /* _gp - 0x728 */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 factory_FactoryBlueprintListTick_4ef1d0(s32 unused, s32 start)
{
    s32 r;

    if (start != 0) {
        UiEntryListSelectByTag_28ea90(D_00484A48->f84, 0x88CC, 1);
    }
    r = MenuGridCursorInput_28e170(D_00484A48->f84, D_004B2570, 2, 0);
    if ((r == 2) && (factory_FactoryBlueprintCancel_4fb5a0(D_00484A48) != 0)) {
        StateMachineSetState_28ede0(D_00484A48->f88, 0x88E0, 0);
    } else if (r == 1) {
        factory_FactoryBlueprintConfirm_4fb840(D_00484A48);
    } else if ((r == 6) && (PadIsTriggered_1839f0(D_004B2570, 0x10) != 0)) {
        factory_FactoryBlueprintAskClear_4fae70(D_00484A48);
    }
    return 1;
}
