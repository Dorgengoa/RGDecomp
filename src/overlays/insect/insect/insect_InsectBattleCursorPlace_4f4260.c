#include "types.h"
/* insect 0x004F4260 -- 77 instructions, the phase-advance / func_290F50
 * readout family (NORMAL's normal_BtlChgMenuCursorBob_503750 / normal_BtlChgMenuAbilityConfirmCursorBobCb_4fc380 are the
 * same shape).  CLOSED insect session 67 (2026-09-14) on
 * [[levers.d/mwcc-const-sdata-load-hoist]]: the phase accumulator
 * D_00484FAC (_gp-0x1C4) is READ AND WRITTEN here, and a written gp extern's
 * load will not hoist across the prologue's stack stores; declared
 * `extern const ... section(".sdata")` and written through `*(f32 *)&` the
 * load schedules in slot 2 of the prologue, where retail has it.  The two
 * float constants (0.1570796371f, 3.14159274f) are MAIN's .lit4 pool and are
 * written as literals; the scorer reads their two unrelocated words as bad,
 * the link retargets them (t_lit4) and reads BYTE-IDENTICAL.
 *
 * The float PRODUCT is a NAMED LOCAL: written inline mwcc contracts the
 * `mul.s`/`add.s` into `madd.s`, takes the IEEE float-to-int path instead of
 * the R5900 `cvt.w.s`, and swaps the `add.s` operands. */

typedef struct Wnd {
    u8   pad000[0x87C];
    s32  m87C;                      /* +0x87C */
} Wnd;

extern const f32 D_00484FAC __attribute__((section(".sdata")));   /* gp-0x1C4 */

extern f32 func_128FD0(f32 a);
extern void func_290F60(s32 w, s32 id, s32 x, s32 y);
extern void func_290F50(s32 w, s32 id, s32 x, s32 y, s32 c, f32 t);

s32 insect_InsectBattleCursorPlace_4f4260(Wnd *w, s32 x, s32 y, s32 dx, s32 dy,
                        s32 sx, s32 sy, s32 sel)
{
    f32 p;
    f32 v;

    p = (*(f32 *)&D_00484FAC);
    p += 0.1570796371f;
    (*(f32 *)&D_00484FAC) = p;
    if ((*(f32 *)&D_00484FAC) > 0.0f) {
        (*(f32 *)&D_00484FAC) = (*(f32 *)&D_00484FAC) - 3.14159274f;
    }
    v = 6.0f * func_128FD0((*(f32 *)&D_00484FAC));
    if (sel != 0) {
        func_290F60(w->m87C, 0xC37D, (s32)(v + (x + dx * sx)), y + dy * sy);
    } else {
        func_290F50(w->m87C, 0xC37D, (s32)(v + (x + dx * sx)), y + dy * sy,
                    0, 0.5f);
    }
    return 1;
}
