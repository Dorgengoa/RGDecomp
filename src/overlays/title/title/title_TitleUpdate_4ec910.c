#include "types.h"

/* title.bin overlay, 0x004EC910 -- the per-frame tick.  BYTE-IDENTICAL
 * (session 9), after two sessions parked at 56 bad words.  Two defects, both
 * found by the worked-example census over 8,392 matched units
 * (scripts/t_census.py, build/ti-census9.txt):
 *
 * 1. THE UNSUNK `addiu / b / nop` RETURN.  Retail's second guard falls
 *    through into `addiu $2,1 / b <epilogue> / nop` -- the addiu refusing
 *    the delay slot.  normal_SpaceMenuIsBusy_511690 (normal, matched) shows the spelling: a
 *    SHARED result block with a fall-through predecessor plus a goto
 *    predecessor, placed physically BEFORE the following block.  Here that
 *    means guard 1 `goto`s ret1, guard 2 branches AWAY POSITIVE
 *    (`if (g2 != 0) goto body;`) so ret1 is its fall-through, and ret1 sits
 *    between guard 2 and the body.  The session-7 shared-label forms failed
 *    only because they needed an explicit `goto work` -- one extra word; the
 *    polarity flip removes it.  Retail's own conversions confirm the shape:
 *    guard 1's `beql` carries a DUPLICATED copy of ret1's addiu (a
 *    likely-converted edge that targeted the block), and guard 2's `bnel`
 *    carries the body's first `lh`.
 *
 * 2. `D_004841A4 = func_372DB0();` -- THE STORED VALUE IS THE CALL'S RETURN,
 *    NOT THE CONSTANT 2.  Written `= 2`, mwcc must rematerialise the 2 after
 *    the call (`li $2,2`, one word long); retail stores $2 straight out of
 *    func_372DB0 in func_372F20's delay slot, which is only legal data flow
 *    if the source stores the return value.  m2c read the constant off the
 *    guard compare -- a plausible-but-wrong reading the schedule refutes.
 *    (The value coincides with 2 at runtime; the BYTES decide the spelling.)
 *
 * The +0x20 byte is written as a one-bit BITFIELD at bit 1: `= 1` folds to a
 * `daddiu 2` while `= 0` keeps the whole `andi $0,1 / sll 1` insert -- the
 * asymmetry is what identifies it as a bitfield rather than a masked byte
 * assignment.
 *
 * `D_004803A8 = 0;` BEFORE `title_TitleSetNoAnalogPause_4f13b0(0)` puts the store in the
 * call's delay slot.  The inner `return 1` after func_37BDA0(1) is a plain
 * single-predecessor return and its addiu correctly SINKS into its b's slot
 * (retail 0x004EC98C) -- the same function carries both forms, which is what
 * made the block-predecessor reading testable.
 */

typedef struct Sys_title_FUN_004ec910 {
    u8 pad000[0x20];
    u8 bit0 : 1;
    u8 bit1 : 1;
} Sys_title_FUN_004ec910;

extern void *D_00484158;
extern Sys_title_FUN_004ec910 *D_0048415C;
extern void *D_00484160;
extern void *D_00484170;
extern void *D_00484174;
extern s16 D_0048419C;
extern s16 D_004841A0;
extern s16 D_004841A4;
extern u8 D_004841A8;
extern s16 D_004803A8;

extern void title_TitleSetNoAnalogPause_4f13b0(s32 a);
extern void func_28EDE0(void *a, s32 b, s32 c);
extern u8 title_TitleIsPadReady_4f13d0(void);
extern s32 title_TitleGetNoAnalogPause_4f13c0(void);
extern void func_37BDA0(s32 a);
extern void func_37BD90(void);
extern s32 func_372DB0(void);
extern u8 func_372F20(void);
extern void func_2913A0(void *a);
extern void func_28ED70(void *a);
extern void title_TitleMenuUpdateExtraRow_4eca70(void);
extern void *func_1F5BE0(void);
extern void func_1CF6E0(void *a);

s32 title_TitleUpdate_4ec910(void)
{
    if (D_00484160 == 0) {
        goto ret1;
    }
    if (D_00484158 != 0) {
        goto body;
    }
ret1:
    return 1;
body:
    if (D_004803A8 != 0) {
        D_004803A8 = 0;
        title_TitleSetNoAnalogPause_4f13b0(0);
        func_28EDE0(D_00484158, 1, 1);
    }
    if (title_TitleIsPadReady_4f13d0() != 0) {
        goto clear;
    }
    if (title_TitleGetNoAnalogPause_4f13c0() != 0) {
        goto set;
    }
    func_37BDA0(1);
    return 1;
set:
    func_37BD90();
    D_0048415C->bit1 = 1;
    goto joined;
clear:
    func_37BD90();
    D_0048415C->bit1 = 0;
joined:
    D_004841A0 = D_0048419C;
    if (D_004841A8 != 0) {
        if (D_004841A4 != 2) {
            D_004841A4 = func_372DB0();
            D_0048419C = func_372F20();
        }
    }
    func_2913A0(D_00484170);
    if (D_00484174 != 0) {
        func_2913A0(D_00484174);
    }
    func_28ED70(D_00484158);
    title_TitleMenuUpdateExtraRow_4eca70();
    func_1CF6E0(func_1F5BE0());
    return 1;
}
