#include "types.h"

/* factory.bin overlay, 0x004FB5A0 -- advance the parts-shop confirm dialog and
 * tear its widgets down when it closes.
 *
 * A compiled `switch` over states 0..9, so mwcc emits a real jump table;
 * scripts/f_jtbl.py points it at the overlay's own jtbl_0050CD20.
 *
 * ★ Entries 3..7 all hold ONE block's address, so those five case labels share
 * a body; the out-of-range default reaches the shared `return 0`.  Physical
 * block order is 0, 1, 2, 3-7, 8, 9 -- ascending, which is source order for a
 * jump table.
 *
 * ★ THE SEVEN-STATEMENT TEARDOWN IS AN INLINED HELPER, PROVED BY THE COPY
 * COUNT: retail emits it THREE times, once in each of cases 1, 2 and 3-7.  A
 * shared `goto` label would have emitted it once.
 *
 * ★ `o->f7C = 0` is NOT part of that helper -- cases 1 and 2 write it BEFORE
 * their own func_290010 and case 3-7 writes it AFTER, so it is a statement in
 * each arm.
 *
 * ⚠⚠ `factory_FactoryBlueprintDialogSetStyle_4f7c70(o, 1)` MARSHALS NOTHING HERE, AND BOTH HALVES OF
 * THAT COST A BUILD.  `bnel $5, $2, .L004FB718` carries `lw $4, -0x4988($28)`
 * and 0x004FB714 is that same load, so the slot is the ordinary likely-branch
 * duplication of the MERGE's first instruction -- it belongs to the following
 * `func_290010`, NOT to this call, and reading it as this call's argument is
 * worth one word and a wrong prototype.
 *   And the callee is no evidence either: it never reads `$4`, it loads that
 * global itself.  Its OTHER TWO call sites (0x004F8E5x) both emit
 * `daddu $4, $20, $0`, which is what proves the arity -- an unused first
 * parameter is invisible from inside the callee.
 *   ★★ Passing `o` is not cosmetic: it keeps `o` LIVE IN $4 across the guard,
 * so mwcc cannot reuse `a0` for `state`, `state` lands in `$5` as retail has
 * it, and `daddu $16, $4, $0` becomes free to sink into the bound check's
 * delay slot.  Dropping the argument moves `state` into `a0`, forces the
 * callee-saved copy AHEAD of the `lbu`, and degrades the bound check to
 * `beqzl` -- one word, in a completely different part of the function.
 *
 * ★ `daddu $7, $6, $0` is mwcc sharing the `1` it already materialised for
 * $6 -- write the literal in both argument positions.
 *
 * ★ `ori $5, $0, 0x88CC` is how mwcc materialises a constant with no sign
 * extension; a plain `0x88CC` in the source produces it.
 */

typedef struct Glyph {
    u8  pad0[4];
    s16 f04;
    s16 f06;
} Glyph;

typedef struct Dialog {
    u8    pad0[0x7C];
    u8    f7C;
    u8    pad7D[3];
    void *f80;
    void *f84;
} Dialog;

extern void *D_004807E8;
extern void *D_004807EC;

extern void   factory_FactoryBlueprintDialogSetStyle_4f7c70(Dialog *o, s32 on);
extern void   factory_FactoryBlueprintDialogLayout_4f7ed0(Dialog *o);
extern void   factory_FactoryBlueprintGridRefresh_4f9ac0(Dialog *o);
extern void   factory_FactoryBlueprintShowName_4f9db0(Dialog *o);
extern Glyph *func_28EA40(void *ctx, s32 id);
extern void   func_28EA90(void *ctx, s32 id, s32 a);
extern void   func_290010(void *ctx, s32 id, s32 a, s32 b);
extern void   func_290F60(void *ctx, s32 id, s32 x, s32 y);
extern void   func_291110(void *ctx, s32 id, s32 a, s32 b);

static inline void teardown(Dialog *o)
{
    func_291110(D_004807EC, 0x97, 0, 1);
    func_291110(o->f80, 0x40, 1, 1);
    func_291110(o->f80, 0x26, 1, 1);
    func_28EA90(o->f84, 0x88CC, 0);
    func_290010(o->f80, 0x20, 1, -1);
    factory_FactoryBlueprintGridRefresh_4f9ac0(o);
    factory_FactoryBlueprintShowName_4f9db0(o);
}

s32 factory_FactoryBlueprintCancel_4fb5a0(Dialog *o)
{
    u8     state;
    Glyph *g;

    state = o->f7C;
    switch (state) {
    case 0:
        return 1;
    case 1:
        o->f7C = 0;
        func_290010(o->f80, 0x27, 0, -1);
        teardown(o);
        break;
    case 2:
        o->f7C = 0;
        func_290010(o->f80, 0x27, 0, -1);
        teardown(o);
        break;
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
        if (state == 4) {
            factory_FactoryBlueprintDialogSetStyle_4f7c70(o, 1);
        }
        func_290010(D_004807E8, 0x92, 0, -1);
        o->f7C = 0;
        teardown(o);
        break;
    case 8:
        func_291110(D_004807EC, 0x97, 1, 1);
        o->f7C = 3;
        factory_FactoryBlueprintDialogLayout_4f7ed0(o);
        break;
    case 9:
        o->f7C = 1;
        func_290010(D_004807E8, 0x92, 0, -1);
        func_28EA90(o->f84, 0x88D6, 0);
        g = func_28EA40(o->f84, 0x88D6);
        func_290F60(D_004807EC, 0x97, g->f04 + 0x37, g->f06 + 0x36);
        break;
    }
    return 0;
}
