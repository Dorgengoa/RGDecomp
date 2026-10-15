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

extern const u8 D_004B2570[];
extern Ctx     *D_00484A48;                     /* _gp - 0x728 */

extern s32  factory_FactoryBlueprintCancel_4fb5a0(Ctx *o);
extern void factory_FactoryBlueprintConfirm_4fb840(Ctx *o);
extern void factory_FactoryBlueprintAskClear_4fae70(Ctx *o);
extern s32  func_1839F0(const void *a, s32 b);
extern s32  func_28E170(void *h, const void *a, s32 b, s32 c);
extern void func_28EA90(void *h, s32 id, s32 a);
extern void func_28EDE0(void *ctx, s32 id, s32 a);

s32 factory_FactoryBlueprintListTick_4ef1d0(s32 unused, s32 start)
{
    s32 r;

    if (start != 0) {
        func_28EA90(D_00484A48->f84, 0x88CC, 1);
    }
    r = func_28E170(D_00484A48->f84, D_004B2570, 2, 0);
    if ((r == 2) && (factory_FactoryBlueprintCancel_4fb5a0(D_00484A48) != 0)) {
        func_28EDE0(D_00484A48->f88, 0x88E0, 0);
    } else if (r == 1) {
        factory_FactoryBlueprintConfirm_4fb840(D_00484A48);
    } else if ((r == 6) && (func_1839F0(D_004B2570, 0x10) != 0)) {
        factory_FactoryBlueprintAskClear_4fae70(D_00484A48);
    }
    return 1;
}
