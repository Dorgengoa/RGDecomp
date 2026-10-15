/* ==== LANE im38, 2026-08-27 -- MATCH.  70 words, 0 bad. ===================
 *
 * THE RESIDUE WAS A MISREAD ADDEND, NOT AN ALLOCATION-ORDER MYSTERY.
 *
 * Twelve sessions read `dsll32 $3,$5,16 / dsra32 $3,$3,16` as "the s16 local
 * `y` being sign-extended for the addition", and then spent 191 measured arms
 * trying to make mwcc colour that sign-extension before `y`.  It never would,
 * because retail's addend is not `y` at all:
 *
 *     top = it->field0060 + it->field0064;
 *
 * `it->field0064` is READ BACK one statement after it was written, and mwcc
 * FORWARDS the just-stored value out of the store's source register instead of
 * re-issuing an `lh` -- the forward is exactly `dsll32 16 / dsra32 16`, because
 * the field is s16 and the register holds a full 32-bit `h - 0x20`.  The
 * forwarded value is therefore a temp DISTINCT from `y`, defined at the store
 * and dead at the `addu`, so it is coloured before `y` ($3), the real `lh` of
 * field0060 takes $7 (with $4/$5/$6 held by the pending call's arguments) and
 * `y` -- now the LAST of the three to be coloured -- lands on $5.  All six
 * "renamed" words fall out of that one reading; no pragma, no declaration
 * order, no volatile.
 *
 * WHERE IT CAME FROM: factory_FactoryMaterialClearConfirmLayout_4f2170, already MATCHED and already
 * carrying the note, has the identical motif --
 *     row->f18 = t;
 *     func_28FD10(o->f40, 0x75, row->f0 + 2 + row->f18, y + 0x24, 3);
 *     -> sh $16,0x18($2) / dsll32 $3,$16,16 / lh $2,0x0($2) / dsra32 / addu
 * i.e. the forwarded read-back gets the LOW register and the real `lh` the
 * high one, the same signature as here.  Grepping the matched listings for
 * "an `addu` whose two operands are an `lh` destination and a `dsra32`
 * destination" produced twelve sites and found it in one pass.
 *
 * MEASURED EQUIVALENCES (identical .text sha1 26f76f8d, 12 arms):
 *   `s32 y` == `s16 y` == `int y`;  `s16 top` == `s32 top`;  the read-back
 *   captured in a local first;  a named `f` for the 0x60 load;  no `y` local
 *   at all (`h - 0x20` written twice).
 * MEASURED NEGATIVES on this unit: reading back field0084 instead of field0064
 *   loses the dsll32/dsra32 entirely (the 0x84 store is not the immediately
 *   preceding one); `it->field0064 + it->field0060` (addend order flipped)
 *   gives the base colouring back.
 * ======================================================================== */
#include "types.h"

/* insmenu 0x004EA4E0 (280 bytes) -- place the list frame and centre the caption
 * inside it, dimmed unless the panel is active.
 *
 * * `bgez / sra 1` with an `addiu 1` on the negative side is a SIGNED divide by
 * two, not a shift: both halves are written `/ 2` in the source.
 * * D_0047D3DC is NOT a global: 0x0047D1D0-0x0047D7FF is mwcc's `.lit4` float
 * literal pool, so the dim tint is the literal `0.4f`.  Scoring this unit
 * REQUIRES the `.lit4` retarget pass (build/os_im01.py, never plain
 * dv_osbuild.py) or the `lwc1` at 0x004EA5BC reads as a phantom seventh bad
 * word with a zero gp immediate.  See [[mwcc-float-literal-pool]].
 */

typedef struct Item Item;
struct Item {
    s16 field0000;
    s16 field0002;
    s16 field0004;
    u8  pad0006[0x5A];
    s16 field0060;
    u8  pad0062[2];
    s16 field0064;
    u8  pad0066[0x1E];
    s16 field0084;
    u8  pad0086[0x1A];
    s16 field00A0;
    u8  pad00A2[0x1E];
    s16 field00C0;
    u8  pad00C2[0x1E];
    s16 field00E0;
};

extern const u8 D_004FA180[];

extern Item *func_28FE10(const void *a, s32 id, s32 n);
extern void func_2905B0(const void *a, s32 id, f32 r, f32 g, f32 b, f32 t);

void insmenu_InsectVsListFrameFit_4ea4e0(s32 frame, s32 label, s32 h, s32 lit)
{
    Item *it;
    s32 y;
    s16 top;

    it = func_28FE10(D_004FA180, frame, 0);
    if (it == 0) {
        return;
    }
    y = h - 0x20;
    it->field0084 = y;
    it->field0064 = y;
    top = it->field0060 + it->field0064;
    it->field00E0 = top;
    it->field00C0 = top;
    it->field00A0 = top;
    it = func_28FE10(D_004FA180, label, 0);
    if (it == 0) {
        return;
    }
    it->field0000 = h / 2 - it->field0004 / 2;
    if (lit) {
        func_2905B0(D_004FA180, label, 1.0f, 1.0f, 1.0f, 1.0f);
    } else {
        func_2905B0(D_004FA180, label, 0.4f, 0.4f, 0.4f, 1.0f);
    }
}
