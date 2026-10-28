/* rgp:protos */
#define RGP_SELF_TextStyleSetGradRgbaQuad_26f1b0 1
#define RGP_SELF_TextStyleSetRgbaQuad_26f250 1
#define RGP_SELF_insect_InsectBattleDrawText_4f0db0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x004F0DB0 -- 428 bytes, 107 instructions, ONE conditional branch:
 * picked by the branch-density rule (bytes / (1 + br)), not by size.
 *
 * Six integer parameters.  The 0x48-byte frame object at $29+0x90 is
 * constructed by func_26C610 and then driven through the func_26Cxxx/26Dxxx/
 * 26Exxx/26Fxxx family, which is this game's text/print object.
 *
 * `sd $2, 0xF0($29)` and `sd $2, 0xE8($29)` sit in the FOLLOWING call's delay
 * slot, which is the recorded "a store written before a call fills that call's
 * delay slot" shape -- the copies are written ahead of the calls in source.
 * The four 0x80 arguments are written out as literals and mwcc shares the one
 * `addiu $5,$0,0x80` between them.
 *
 * THREE LEVERS CARRIED THIS UNIT, in this order; each was measured:
 *
 * 1. The out-pointer-plus-`u64` reading of func_26F2A0 / func_26F200 is WRONG
 *    even though it is the right instructions: mwcc forwards the loaded u64 in
 *    a callee-saved register, drops the store, needs a NINTH callee-saved
 *    register and spills a parameter to the frame -- 85 of 107 words wrong at
 *    the RIGHT LENGTH, and the tell was the extra `sq $30` plus `sw $7,<frame>`
 *    against retail's `daddu $23,$7,$0`.  An 8-byte STRUCT through the same
 *    out-pointer fixes the whole register file in one edit.
 * 2. mwcc then COALESCES the out-buffer with the named local and both copies
 *    vanish (4 words short, and `x_ogap.py` localises it as -2 in exactly the
 *    two gaps).  `volatile` on the NAMED local is what keeps them -- the
 *    anti-dead-store lever met on a struct copy rather than on a global.
 * 3. The last 13 words were pure FRAME SLOTS, and among these locals mwcc
 *    allocates LATER declarations to LOWER addresses, so the declaration order
 *    of the four 8-byte locals and of the two `s32`s had to be reversed.
 *    (The 0x48-byte object is exempt and stays lowest wherever it is
 *    declared.) */

typedef struct Owner {
    u8 pad00[0xC0];
    void *fC0;         /* +0xC0 */
} Owner;

typedef struct Prn { u8 raw[0x48]; } Prn;

/* An 8-BYTE STRUCT RETURNED BY VALUE.  `addiu $4,$29,0xE0 / daddu $5,$17,$0 /
 * jal func_26F2A0` is mwcc's hidden-return-buffer ABI -- $4 is &temp and $5 is
 * the real first argument -- and the `ld`/`sd` pair straight after is the copy
 * of that temp into a NAMED local, which is the recorded "a by-value struct
 * only keeps its copy if it comes from a named local" shape.  Written as an
 * out-pointer + u64 instead, mwcc forwards the value in a callee-saved
 * register, drops the store, needs a ninth callee-saved register and spills a
 * parameter: 85 of 107 words wrong at the RIGHT length. */
typedef struct V8 { s32 a, b; } V8;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern void TextStyleSetRgbaQuad_26f250(Prn *p, V8 b);
extern void TextStyleSetGradRgbaQuad_26f1b0(Prn *p, V8 b);
/*rgp*/

void insect_InsectBattleDrawText_4f0db0(Owner *o, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5)
{
    Prn sp90 __attribute__((aligned(16)));
    volatile V8 c1 __attribute__((aligned(16)));
    volatile V8 c2 __attribute__((aligned(16)));
    V8 t1 __attribute__((aligned(16)));
    V8 t2 __attribute__((aligned(16)));
    s32 spFC;
    s32 spF8;
    Prn *p;
    s32 h;
    s32 g;

    TextStyleInit_26c610(&sp90);
    p = &sp90;
    TextStyleInitPreset_26c540(p, a5);
    DrawListAddTexLoad_1418c0(o->fC0, 0x338, 1.0f);
    TextStyleGetRgba_26f2a0(&t1, p);
    c1 = t1;
    TextStyleGetGradRgba_26f200(&t2, p);
    c2 = t2;
    h = ((signed char)TextStyleGetFontType_26ede0(p));
    g = ((short)TextStyleGetAlpha_26dd30(p));
    TextStyleSetFontType_26edf0(p, a5);
    TextStyleAddSpacing_26f2b0(p, 3, 0);
    if (a4 != 0) {
        spFC = 0;
        spF8 = 0;
        FontMeasureString_26daf0(p, a1, &spFC, &spF8);
        a2 = a2 + (a4 - spFC);
    }
    TextStyleSetAlpha_26dd40(p, 0x80);
    TextStyleSetRgba_26f280(p, 0x80, 0x80, 0x80, 0x80);
    TextStyleSetGradRgba_26f1e0(p, 0x80, 0x80, 0x80, 0x80);
    FontDrawText_26cdc0(p, a1, a2, a3);
    TextStyleSetAlpha_26dd40(p, g);
    TextStyleSetRgbaQuad_26f250(p, *(V8 *)&c1);
    TextStyleSetGradRgbaQuad_26f1b0(p, *(V8 *)&c2);
    TextStyleSetFontType_26edf0(p, h);
    TextStyleClearClipRect_26f600(p);
}
