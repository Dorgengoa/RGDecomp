#include "types.h"

/* title.bin overlay, 0x004EA000 -- the New Game / Continue / Options cursor.
 *
 * Polls the pad through func_28E170 (1 = down, 2 = up), moves the highlight
 * between the three rows, and once a row is committed (D_0048418C) runs the
 * confirm flash and hands off.  D_004803AC is the selected row and
 * D_00484178 the confirm latch, with 0xFF meaning "the extra fourth row".
 *
 * The idle timeout compares against 120.0f * D_0045B078, an absolute-addressed
 * const float outside the gp window.
 *
 * ★★★★★★ SOLVED (session 3f).  The last word was retail's
 * `daddiu $17, $0, 0x64` against our `addiu`, and the cause is the TYPE of the
 * widget id, not the constant.  Three things had to be true together:
 *   1. the widget id is a SEPARATE local from the pad result -- they share $17
 *      because their live ranges are disjoint, not because they are one
 *      variable;
 *   2. it is `u16`.  An UNSIGNED NARROW type is what makes mwcc materialise a
 *      constant with `daddiu` rather than `addiu`; and
 *   3. the three callees take it as `u16` too.  With an `s32` parameter the
 *      u16 -> int promotion is a zero-extending `andi` that mwcc sinks to the
 *      JOIN of the two arms -- one word long, and it also pushed the constant
 *      into $3 so the arms no longer wrote $17 directly.
 * ⚠ Measured and NOT the answer: `u32`, `0x64L`, `100U`, `(u16)0x64` on an
 * s32 local (all still 1 word); `long`, `unsigned long`, `s64` (+8, the
 * sibling assignment then needs a conversion); `s64` with the callees widened
 * (+5); one `u16` variable for BOTH roles with `func_28E170` returning `u16`
 * (+2, the return then needs truncating).
 * ★ How it was found, and it is the reusable part: `daddiu rX, $0, imm`
 * occurs in 660 of the tree's 20,195 reference listings and in ZERO of the
 * 5,262 matched units -- our toolchain had never been asked for it.  A corpus
 * scan for the same shape found `normal_FieldHudLogClose_4f88b0`, where the identical
 * `daddiu $17,$0,0x7A` is paired with `addiu $3,$17,1 / andi $17,$3,0xFFFF`,
 * which is the u16 wraparound idiom and named the type.
 * ★★★★ FOUR STRUCTURAL FIXES TOOK THIS FROM `len` TO ONE WORD, and three of
 * them are BLOCK ORDER, not spelling:
 *  1. In the D_0048418C != 0 section the `D_00484178 != 0xFF` body is
 *     PHYSICALLY LAST in retail, reached by a forward branch, with the
 *     `== 0xFF` body falling through and the long 290690/290F50 chain in the
 *     middle.  Writing it as m2c does -- `!= 0xFF` first -- keeps the call
 *     sequence correct and redistributes seventeen call gaps.  This one edit
 *     took ogap.py's divergent-gap count from 17 to 3.
 *  2. The tail's `== 0xFF` arm is likewise the fall-through.
 *  3. `D_004803AC = t;` after an if/else must be written as a STORE INSIDE
 *     BOTH ARMS -- retail duplicates it, the joined form is two words short.
 *     Same shape as the `return 1` corollary in [[overlay-c-pipeline]].
 *  4. ★ Two adjacent stores to different gp globals: mwcc REORDERS them
 *     freely, so the source order does not set the store order -- but it does
 *     set which value gets $2 and which $3.  Swapping
 *     `D_00484178 = 0xFF; D_0048418C = D_004803AC;` was worth EIGHT words
 *     across two sites, and permuting the three statements of the arm at
 *     0x004EA0D4 scored 4 / 1 / 4 / 5 / 5 / 5 -- one order out of six.
 */

typedef struct Sel {
    u8 pad0[0x12];
    s16 f12;
} Sel;

extern const f32 D_0045B078;
extern f32 D_0047D248;
extern f32 D_0047D35C;
extern f32 D_0047D464;
extern f32 D_0047D51C;
extern f32 D_0047D520;
extern f32 D_0047D52C;
extern f32 D_0047D540;
extern f32 D_0047D544;
extern s16 D_004803AC;
extern void *D_00484158;
extern void *D_0048415C;
extern void *D_00484170;
extern s16 D_00484178;
extern s16 D_0048417C;
extern s16 D_00484188;
extern s16 D_0048418C;
extern const u8 D_004B2570;

extern void func_1CF730(void *a, s32 b, f32 x, f32 y, f32 z);
extern void *func_1F5BE0(void);
extern s32 func_28E170(void *a, void *b, s32 c, s32 d);
extern Sel *func_28EC60(void *a);
extern void func_28EDE0(void *a, s32 b, s32 c);
extern f32 *func_2904B0(void *a, u16 b);
extern void func_2904E0(void *a, u16 b, f32 x, f32 y, f32 z, f32 w, f32 t);
extern void func_2905B0(void *a, u16 b, f32 x, f32 y, f32 z, f32 w);
extern void func_290690(void *a, s32 b, f32 x, f32 y, f32 z);
extern f32 func_290770(void *a, s32 b);
extern void func_290F50(void *a, s32 b, s32 x, s32 y, s32 e, f32 f);
extern void func_291110(void *a, s32 b, s32 c, s32 d);
extern void func_2F5A60(void);
extern f32 func_2F5AB0(void);
extern void func_2F5AC0(void);
extern s32 title_TitleDemoPvRowEnabledMaybe_4ed340(void);
extern void title_TitleSceneOverlayModeOff_4eaa00(void);

s32 title_TitleDemoMenuTick_4ea000(void *unused, s32 first)
{
    Sel *o;
    s32 id;
    u16 wid;
    f32 v;
    s16 t;

    if (first != 0) {
        func_2F5AC0();
    }
    if (D_0048418C == 0) {
        id = func_28E170(D_0048415C, (void *)&D_004B2570, 0, 0);
        o = func_28EC60(D_0048415C);
        func_2F5A60();
        if (func_2F5AB0() > 120.0f * D_0045B078) {
            D_0048418C = D_004803AC;
            D_00484178 = 0xFF;
        } else if (id == 1 && D_0048418C == 0) {
            func_2F5AC0();
            D_0048418C = D_004803AC;
            if (title_TitleDemoPvRowEnabledMaybe_4ed340() != 0 && o->f12 == 2) {
                D_00484178 = 0xFF;
                D_0048417C = 3;
                wid = 0x64;
            } else {
                D_00484178 = 1;
                wid = D_004803AC + 0x61;
            }
            func_2905B0(D_00484170, wid, D_0047D464, D_0047D464, D_0047D464, 1.0f);
            func_2904E0(D_00484170, wid, D_0047D35C, D_0047D35C, D_0047D35C, 1.0f,
                        D_0047D520);
            func_290690(D_00484170, 0x65, 0.0f, D_0047D540, -1.0f);
        } else if (id == 2 && D_0048418C == 0) {
            func_2F5AC0();
            D_0048418C = D_004803AC;
            D_00484178 = 0xFF;
        }
        if (D_0048418C == 0) {
            if (o->f12 == 0) {
                func_2905B0(D_00484170, 0x62, 1.0f, 1.0f, 1.0f, 1.0f);
                func_2905B0(D_00484170, 0x63, D_0047D248, D_0047D248, D_0047D248,
                            1.0f);
                func_2905B0(D_00484170, 0x64, D_0047D248, D_0047D248, D_0047D248,
                            1.0f);
                D_004803AC = 1;
            }
            if (o->f12 == 1) {
                func_2905B0(D_00484170, 0x62, D_0047D248, D_0047D248, D_0047D248,
                            1.0f);
                func_2905B0(D_00484170, 0x63, 1.0f, 1.0f, 1.0f, 1.0f);
                func_2905B0(D_00484170, 0x64, D_0047D248, D_0047D248, D_0047D248,
                            1.0f);
                if (title_TitleDemoPvRowEnabledMaybe_4ed340() != 0) {
                    D_004803AC = 4;
                } else {
                    D_004803AC = 2;
                }
            }
            if (o->f12 == 2) {
                func_2905B0(D_00484170, 0x62, D_0047D248, D_0047D248, D_0047D248,
                            1.0f);
                func_2905B0(D_00484170, 0x63, D_0047D248, D_0047D248, D_0047D248,
                            1.0f);
                func_2905B0(D_00484170, 0x64, 1.0f, 1.0f, 1.0f, 1.0f);
                D_004803AC = 4;
            }
        }
    }
    if (D_0048418C != 0) {
        if (D_00484178 == 0xFF) {
            if (title_TitleDemoPvRowEnabledMaybe_4ed340() != 0 && D_0048417C == 3) {
                v = *func_2904B0(D_00484170, 0x64);
                if (v >= D_0047D35C) {
                    func_2904E0(D_00484170, 0x64, 1.0f, 1.0f, 1.0f, 1.0f, D_0047D51C);
                } else if (v <= 1.0f) {
                    func_290690(D_00484170, 0x61, 0.0f, D_0047D544, -1.0f);
                }
            } else {
            func_290690(D_00484170, 0x62, 0.0f, D_0047D52C, -1.0f);
            func_290F50(D_00484170, 0x62, 0x100, 0, 1, 20.0f);
            func_290690(D_00484170, 0x63, 0.0f, D_0047D52C, -1.0f);
            func_290F50(D_00484170, 0x63, 0x1C8, 0, 1, 20.0f);
            func_290690(D_00484170, 0x64, 0.0f, D_0047D52C, -1.0f);
            func_290F50(D_00484170, 0x64, 0x290, 0, 1, 20.0f);
            func_291110(D_00484170, 0x65, 0, 1);
            func_290690(D_00484170, 0x61, 0.0f, D_0047D51C, -1.0f);
            func_1CF730(func_1F5BE0(), 0xA, 0.0f, 0.0f, 0.0f);
            }
        } else {
            wid = D_004803AC + 0x61;
            v = *func_2904B0(D_00484170, wid);
            if (v >= D_0047D35C) {
                func_2904E0(D_00484170, wid, 1.0f, 1.0f, 1.0f, 1.0f, D_0047D51C);
            } else if (v <= 1.0f) {
                func_290690(D_00484170, 0x61, 0.0f, D_0047D544, -1.0f);
            }
        }
    }
    if (func_290770(D_00484170, 0x61) <= 0.0f) {
        if (D_00484178 == 0xFF) {
            D_00484178 = 0;
            title_TitleSceneOverlayModeOff_4eaa00();
            func_28EDE0(D_00484158, 4, 0);
        } else {
            D_0048417C = 0;
            D_00484188 = 2;
            D_00484178 = 0;
        }
    }
    return 1;
}
