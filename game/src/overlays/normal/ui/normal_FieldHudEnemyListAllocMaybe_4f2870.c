/* rgp:protos */
#define RGP_SELF_normal_FieldHudEnemyListAllocMaybe_4f2870 1
#include "port/game_protos.h"
#line 1
/* normal 0x004F2870 -- BYTE-IDENTICAL (s23).  The residue was ONE word,
 * `addiu $20,$0,0x4A` where retail has `daddiu`, and it took THREE coordinates
 * at once.  Every one of them had been swept ALONE and every such sweep has a
 * floor of 1 bad or a wrong length, because the winning cell is off all three
 * axes.
 *
 *   1. `u16 id`  -- [[mwcc-daddiu-unsigned-narrow]]: `daddiu rX,$0,K` is
 *      emitted only for a REGISTER-RESIDENT u8/u16.  Alone this is TWO WORDS
 *      SHORT (mwcc folds the `(u16)id` promotion, frees a callee-saved
 *      register and coalesces loop-1's `i` with loop-2's `j`).
 *   2. `id++`    -- NOT `id = (u16)(id + 1)`.  The re-narrowing cast in the
 *      increment is what let mwcc fold the promotion; with a bare `id++` the
 *      unit is back at the RIGHT LENGTH (21 bad).  `id += 1` and `++id` are
 *      the same object; `id = id + 1` is 2 short again.
 *   3. `func_290460(void *p, u16 id)` and the derived ids passed UNCAST.
 *      Retail's shape is `andi $18,$20,0xFFFF / addiu $3,$18,-0x5 /
 *      andi $5,$3,0xFFFF` -- promote, subtract in int, NARROW AT THE CALL --
 *      and the narrowing at the call is the CALLEE'S PARAMETER WIDTH
 *      ([[pk-callee-param-width]]), not a cast in the caller.  With the
 *      parameter declared `s32` and the cast written in the source the
 *      promotion schedules 13 words early and nothing moves it.
 *
 * => The park's recorded contradiction -- "the init wants a NARROW type and
 * the CSE wants a WIDE one, and no C spelling supplies both" -- was true only
 * of the sub-lattice that had been built.  `u16` supplies the narrow init;
 * `id++` stops mwcc proving the promotion redundant; the u16 CALLEE
 * PARAMETER puts the narrowing where retail has it.
 * ⚠ The recorded nulls all still hold on their own bases: 24 declaration
 * permutations (one object), 488 knob variants twice, 8 init spellings, 12
 * separate-copy shapes, 7 id types on the double-cast shape.  None of them
 * bind here -- a measured null does not bind a base it was not measured on.
 */
#include "types.h"
/* ==================================================================== *
 *  PARKED -- RIGHT LENGTH, **ONE** BAD WORD.
 *  DELIBERATELY *NOT* IN config/ocunits/normal.txt.  Right length is the
 *  one residue olink's length guard cannot catch, so admitting this would
 *  ship a wrong image that still links byte-identical.
 *
 *  THE WHOLE RESIDUE IS THE WIDGET-ID's INIT:
 *      0x004F28E4   ours 2414004A  addiu  $20,$0,0x4A
 *                 retail 6414004A  daddiu $20,$0,0x4A
 *
 *  AND IT IS A GENUINE CONTRADICTION, not an unexplored spelling:
 *   * `daddiu $r,$0,K` is emitted only when the DESTINATION type is
 *     narrower than 32 bits (the recorded `daddiu` rule from the FACTORY
 *     board).  Measured here: u16/s16/u8 -> daddiu, u32/s32/s64 -> addiu,
 *     and NO init SPELLING moves it (`0x4Au`, `74u`, `(u16)0x4A`,
 *     `(u8)0x4A`, `0x4AULL`, `(u64)0x4A`, `0x4Al`, `(s64)0x4A`, and a
 *     separate `u16 base` feeding it -- eight arms, all `addiu`).
 *   * but retail also CSEs `(u16)id` into its OWN callee-saved register
 *     ($18) and keeps `id` in $20, which needs `(u16)id` to be a REAL
 *     narrowing -- and on a u16 mwcc folds it, allocates the promotion
 *     back into `id`'s register, and the unit comes out TWO WORDS SHORT
 *     (exactly the sq/lq pair for the sixth callee-saved register).
 *  => the init wants a NARROW type and the CSE wants a WIDE one.
 *
 *  MEASURED NEGATIVES, so they are not re-ground:
 *   * ALL 24 DECLARATION ORDERS of {w,i,j,id} give the IDENTICAL object
 *     (ec28433f).  A clean sweep is the recorded stopping rule for the
 *     register tie-break (levers.d/insect-scheduler-tiebreak);
 *     build/n_2870perm.py.
 *   * the SEPARATE-COPY shape (`t = id;` for the two derived ids), three
 *     placements x four types, build/n_2870arms.py: `pre:s32` 22 bad is
 *     the best and puts the `andi` one call too EARLY; `mid` coalesces the
 *     copy away and goes short again; `top` 41.
 *   * seven id TYPES with the double-cast shape: u32/s32 -> 1, s64/u64 ->
 *     length, u16/u8 -> 2 short, s16 -> 4 long.
 *   * THE WHOLE COMPILER-KNOB AXIS, TWICE.  `n_knob.py --all`, 488
 *     variants over the 244 recognised pragmas in both polarities, on the
 *     u16 base (build/n_knob_2870_all.log: 469 inert / 19 live, and NOT
 *     ONE variant reaches 0x1b0) and on THIS 1-bad arm
 *     (build/n_knob_2870_one.log: 469 inert / 19 live, nothing below 1).
 * ==================================================================== */
/* normal 0x004F2870 -- builds the item-grid page: one 0x3C0 arena, sixteen
 * 0x30 scratch blocks, then five icon cells each wired into three widgets.
 * Pass-33 LIST rank: 432 bytes, 108 instructions, TWO conditional branches,
 * 8 calls, 34 stores -- two straight-line loop bodies and nothing else.
 *
 * `daddiu $20,$0,0x4A` is the tell that the widget id is a NARROW UNSIGNED
 * local, not an s32 (`addiu` would mean s32).  Everything the `andi
 * ..,0xFFFF`s do follows from `id` being a `u16` and func_290460 taking a
 * `u16` parameter: passing `id` straight through is a bare `daddu`, while
 * `id - 5` and `id - 0xA` promote to int and have to be masked back -- and
 * because there are TWO of them mwcc CSEs the promotion of `id` itself into
 * `andi $18,$20,0xFFFF`.  Same rule as normal_FUN_004F57F0, both directions.
 *
 * 0x2931A0 is a main-image FUNCTION address, so it is declared as a function
 * and passed by name; a cast integer would be `lui`/`ori`.
 *
 * The six widget clears reload `p->f3F0[j]` before each one -- a load will not
 * cross a store through a pointer that might alias it -- which is why the
 * source writes the array element out longhand instead of naming a local. */

typedef struct Cell {
    s16 f00;
    s16 f02;
    s32 f04;
    u8  pad08[0x0A - 0x08];
    s8  f0A;
    u8  pad0B[1];
    s32 f0C;
    s16 f10;
} Cell;

typedef struct Wid {
    u8    pad00[0x14];
    s32   f14;
    s32   f18;
    s16   f1C;
    u8    pad1E[2];
    s32   f20;
    s32   f24;
    Cell *f28;
} Wid;

typedef struct Page {
    u8     pad000[0x3F0];
    Cell  *f3F0[5];
    u8     pad404[0x434 - 0x404];
    s32    f434;
    u8    *f438[0x10];
} Page;

extern void  memset(void *p, s32 v, s32 n);
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

extern void normal_FieldHudEnemyListAllocMaybe_4f2870(Page *p, void *q);

void normal_FieldHudEnemyListAllocMaybe_4f2870(Page *p, void *q)
{
    Wid *w;
    s32  i;
    s32  j;
    u16  id;

    p->f434 = ((s32)MemStackNew_14e1b0(0x3C0, q));
    for (i = 0; i < 0x10; i++) {
        p->f438[i] = ((u8 *)MemStackAllocQw_14d950(q, 3));
        memset(p->f438[i], 0, 0x30);
    }
    id = 0x4A;
    for (j = 0; j < 5; j++) {
        p->f3F0[j] = ((Cell *)ConstructNewArray_100710((void *)((s32)MemStackNew_14e1b0(0x30, q)), UiTextElemInit_2931a0, 0, 0x10, 2));
        p->f3F0[j]->f00 = 4;
        p->f3F0[j]->f02 = 1;
        p->f3F0[j]->f04 = 0;
        p->f3F0[j]->f0A = 1;
        p->f3F0[j]->f0C = 0xFF606060;
        p->f3F0[j]->f10 = -1;

        w = ((Wid *)UiFindWidget_290460(p, id));
        w->f14 = 0;
        w->f18 = 0;
        w->f1C = 0;
        w->f20 = 0;
        w->f24 = 0;
        w->f28 = p->f3F0[j];

        w = ((Wid *)UiFindWidget_290460(p, id - 5));
        w->f14 = 0;
        w->f18 = 0;
        w->f1C = 0;
        w->f20 = 0;
        w->f24 = 0;
        w->f28 = p->f3F0[j];

        w = ((Wid *)UiFindWidget_290460(p, id - 0xA));
        w->f14 = 0;
        w->f18 = 0;
        w->f1C = 0;
        w->f20 = 0;
        w->f24 = 0;
        w->f28 = p->f3F0[j];
        id++;
    }
}
