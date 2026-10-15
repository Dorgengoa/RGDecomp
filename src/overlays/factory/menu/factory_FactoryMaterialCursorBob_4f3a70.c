#include "types.h"

/* factory.bin overlay, 0x004F3A70 -- 772 B.  BYTE-IDENTICAL (session 23, lane
 * fz23e).  193 words, MATCH.
 *
 * ★★★★★★ THE LEVER: `return;` IN THE MIDDLE OF AN IF LEAVES FOUR ORPHANED
 * BRANCH-LIKELY TARGET HEADS.  The parked draft was FOUR WORDS LONG and every
 * one of the four was mwcc copying a branch target block's first instruction
 * into a likely-branch delay slot, bumping the target past it, and LEAVING the
 * now-unreachable original in .text (object offsets 0x138, 0x164, 0x168, 0x1e0).
 * The cause was NOT in the arms the dead words sit in.  It was the shape
 *     if (o->f78 == 2) { ...; return; }
 *     <else code>
 * Rewriting that one guard as a real two-armed `if (o->f78 == 2) {...} else
 * {...}` and exiting the then-arm with `goto done;` to a label AFTER the shared
 * tail call deletes ALL FOUR at once and gives a byte-identical object.
 * This is [[insect-return-vs-break]] reached on factory from the if/else side:
 * a block that ends in a RETURN is not threaded, a block that ends in a JUMP TO
 * A JOIN is, and threading is what lets mwcc delete the orphaned heads.
 * ⇒ AN ORPHANED BRANCH-LIKELY HEAD IS A STATEMENT-SHAPE DEFECT, NOT A
 *   SCHEDULING ONE.  Look at how the enclosing arm EXITS, not at the arm the
 *   dead word is in.
 *
 * ⚠ THE TAIL CALL MUST STAY SHARED.  The intermediate arm of this session --
 * same if/else but with `factory_FactoryMaterialFrameScroll_4f3a40(o)` written out in each of the
 * three paths that need it -- ALSO deleted all four dead words but cost SIX:
 * mwcc did NOT tail-merge the three call sites (0x314 -> 0x31c).  One call site
 * plus `goto done;` is the spelling that pays.
 *
 * MEASURED INERT ON THIS UNIT (do not re-run): `#pragma optimization_level 3`
 * (byte-identical object); flipping the polarity of BOTH inner guards together
 * with the arms swapped (object changed, length stayed 0x314).
 */

typedef struct W {
    s16 f00;
    s16 f02;
    s16 f04;
    s16 f06;
    u8  pad08[0x8];
    s16 f10;
    s16 f12;
} W;

typedef struct P {
    s16 f00;
    u8  pad02[0x16];
    s16 f18;
} P;

typedef struct Scr {
    f32   f00;
    u8    pad04[0x1A];
    s8    f1E;
    u8    pad1F[0x21];
    void *f40;
    void *f44;
    u8    pad48[0x8];
    u8    f50[0x28];
    u8    f78;
} Scr;

extern f32   D_0047D3D0;                        /* _gp - 0x7DA0 */
extern f32   D_0047D3EC;                        /* _gp - 0x7D84 */
extern void *D_004807EC;                        /* _gp - 0x4984 */

extern void  factory_FactoryMaterialFrameScroll_4f3a40(Scr *o);
extern f32   func_128FD0(f32 t);
extern void  func_28DAA0(void *p, s32 id, s32 x, s32 y);
extern W    *func_28EC60(void *h);
extern void  func_28FCD0(void *w, s32 id, s32 v, s32 n);
extern P    *func_28FE10(void *w, s32 id, s32 n);
extern void  func_290F50(void *w, s32 id, s32 x, s32 y, s32 a, f32 t);
extern void  func_290F60(void *w, s32 id, s32 x, s32 y);

void factory_FactoryMaterialCursorBob_4f3a70(Scr *o, s32 flag, s32 mode)
{
    W  *w;
    P  *p;
    f32 s;
    s32 x;
    s32 y;

    if (mode == 0) {
        o->f00 = o->f00 + D_0047D3D0;
        if (o->f00 > 0.0f) {
            o->f00 = D_0047D3EC;
        }
        s = 6.0f * func_128FD0(o->f00);
        w = func_28EC60(o->f44);
        if (o->f78 == 2) {
            x = (s32)(s + (f32)(w->f00 + w->f10 * w->f04));
            y = w->f02 + w->f12 * w->f06;
            if (flag != 0) {
                func_290F60(D_004807EC, 0x97, x, y);
            } else {
                func_290F50(D_004807EC, 0x97, x, y, 0, 0.5f);
            }
            if (o->f1E != w->f10) {
                p = func_28FE10(o->f40, 0x75, 0);
                if (w->f10 == 0) {
                    func_28FCD0(o->f40, 0x75, p->f00 + 2, 3);
                } else {
                    func_28FCD0(o->f40, 0x75, p->f00 + 2 + p->f18, 3);
                }
                o->f1E = w->f10;
            }
            goto done;
        } else {
            x = (s32)(s + (f32)(w->f00 + 0x1E + w->f10 * w->f04));
            y = (s32)(s + (f32)(w->f02 + 0x23 + w->f12 * w->f06));
            if (flag != 0) {
                func_290F60(o->f40, 0x64, x, y);
            } else {
                func_290F50(o->f40, 0x64, x, y, 0, 0.5f);
            }
            func_28DAA0(o->f50, 0x63, w->f10 * w->f04 + 0x17,
                        w->f12 * w->f06 + 0x17);
        }
    } else if (mode == 1) {
        o->f00 = o->f00 + D_0047D3D0;
        if (o->f00 > 0.0f) {
            o->f00 = D_0047D3EC;
        }
        s = 6.0f * func_128FD0(o->f00);
        w = func_28EC60(o->f44);
        x = (s32)(s + (f32)(w->f00 + w->f10 * w->f04));
        y = w->f02 + w->f12 * w->f06;
        if (flag != 0) {
            func_290F60(o->f40, 0x76, x, y);
        } else {
            func_290F50(o->f40, 0x76, x, y, 0, 0.5f);
        }
    }
    factory_FactoryMaterialFrameScroll_4f3a40(o);
done:
    ;
}
