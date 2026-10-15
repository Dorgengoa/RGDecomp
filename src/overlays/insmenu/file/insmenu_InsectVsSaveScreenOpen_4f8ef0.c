#pragma opt_dead_assignments off
#include "types.h"

/* insmenu 0x004F8EF0 (1,216 bytes, 304 instructions, 41 calls) -- the menu's
 * per-frame driver: an optional reset pass, a one-shot open pass gated on the
 * fade having finished, and then the confirm dispatch on the selected entry id.
 *
 * `c.lt.s $f0, $f1` with `bc1tl` branching AWAY means the guarded body is the
 * `>= 1.0f` case -- the fall-through, as always.  (004EE860's `> 0.0f` is the
 * other member of the pair, `c.le.s` + `bc1f`.)
 *
 * The three-way `sel == 0x1F6 || sel == 0x1F7 || sel == 0x193` head guard is an
 * OR chain, not a switch: the `beql`/`beq`/`bnel` carry the NEXT constant, and
 * the two arms that fall into the shared `D_00484358 = 0` reach it from
 * different tests.
 *
 * `ids[]` is copied out of D_004F9780 by an explicit word-pair loop rather than
 * being an initialised local, for the same .rodata-duplication reason written
 * up in insmenu_InsectVsLoadPanelLayout_4f7dd0.c.  Its index is s16 -- retail re-normalises with
 * `dsll32 16 / dsra32 16` on every iteration before scaling by 4.
 *
 * PARKED AT ONE INSTRUCTION, A LENGTH DEFECT.  0x4BC against retail's 0x4C0.
 * The whole deficit is the array-index addressing in the search loop: retail
 * materialises the element address as
 *     sll <i> / addu <x>, <i>, $29 / addiu <x>, <x>, <frame off> / lw <x>, 0(<x>)
 * and we fold the frame displacement into the load,
 *     sll <i> / addu <x>, <i>, $29 / lw <x>, <frame off>(<x>).
 * The SAME one word blocks insmenu_InsectVsLoadPanelLayout_4f7dd0 and insmenu_InsectVsSaveScreenOpen_4f8ef0 --
 * 2,512 bytes on one fix -- so it was probed properly rather than swept.
 *
 * ⚠ MEASURED BOUNDED NEGATIVE, 23 SPELLINGS IN TWO PROBE-TU ROUNDS
 * (src/overlays/insmenu/improbe.c, deleted after use).  Every one of these
 * FOLDS: s16 index, s32 index, u16 index, s64 index, a named `const s32 *p = a`
 * read as `p[i]`, `*(const s32 *)((const u8 *)a + i*4)`, the same with `i << 2`,
 * `*(&a[i] + 0)`, `q = a + i` then `*q`, `b = a` re-taken every iteration then
 * `b[i]`, the array inside a struct local, an array of one-member structs, an
 * array of 8-byte structs read at member 0, a nested-struct first member, a
 * whole-struct copy in the test, a second local below it, a 2 KB pad in front
 * of it, and a `volatile` array (which hoists a pointer instead).
 *
 * ★ EXACTLY ONE SPELLING PRODUCES RETAIL'S SHAPE, and it is not this code:
 * when the element ADDRESS is genuinely live at two uses --
 * `q = &a[i]; g(*q); g2(q);` -- mwcc emits `addiu s1, a0, 48 / lw a0, 0(s1)`.
 * Here retail's address register is dead the instant the load consumes it
 * (`lw $4, 0x0($4)` overwrites it), so that mechanism does not apply.
 * ★ And retail folds in the very same function where the member offset is
 * NON-ZERO: 004F7DD0's `.val` read is `addu $2, $5, $29 / lh $2, 0xB4($2)`.
 * So the split is specifically member-offset-zero, which is where there is
 * nothing to gain from folding -- and our build folds anyway.
 * Do not sweep this further without a different compiler build.
 */

typedef struct Item Item;
struct Item {
    s32 field00;
    u8 bit0 : 1;
    u8 bit1 : 1;
};

typedef struct Sub Sub;
struct Sub {
    u8 pad00[8];
    s16 field08;
};

typedef struct Ctx Ctx;
struct Ctx {
    u8 pad0000[0x1188];
    Sub *field1188;
};

typedef struct Handle Handle;
struct Handle {
    u8 pad00[0x24];
    void *field24;
};

extern const u8 D_004FA180[];
extern const u8 D_004FA1A0[];
extern u8 D_004FA280[];
extern const s32 D_004F9780[8];
extern const u8 D_004B2570[];
extern const u8 D_004B27E0[];

extern s16 D_00480464;      /* gp - 0x4D0C */
extern u8  D_00484344;      /* gp - 0xE2C */
extern u8  D_00484348;      /* gp - 0xE28 */
extern u8  D_00484350;      /* gp - 0xE20 */
extern u8  D_00484358;      /* gp - 0xE18 */
extern u8  D_00484360;      /* gp - 0xE10 */
extern s16 D_00484364;      /* gp - 0xE0C */
extern s16 D_00484368;      /* gp - 0xE08 */
extern s16 D_0048436C;      /* gp - 0xE04 */
extern u8  D_00484370;      /* gp - 0xE00 */
extern s16 D_00484374;      /* gp - 0xDFC */
extern u8  D_004842E8;      /* gp - 0xE88, passed by address*/
extern f32 D_0047D460;

extern void insmenu_InsectVsTasksSuspend_4e9fc0(void);
extern void func_291110(const void *a, u32 b, s32 c, s32 d);
extern void func_290690(const void *a, s32 b, f32 x, f32 y, f32 z);
extern f32 func_290770(const void *a, s32 b);
extern void insmenu_InsectVsSceneRenderHide_4e9f80(void);
extern void insmenu_InsectVsSaveSysInit_4f95d0(void);
extern void func_131B60(void *a, s32 b, s32 c);
extern void insmenu_InsectVsSaveResultCbSet_4ebce0(void);
extern void insmenu_InsectVsSaveProgressWindowShow_4f6b90(s32 a, s32 b);
extern void func_2907A0(const void *a, s32 b, f32 t);
extern void insmenu_InsectVsSetSceneBgFlagMaybe_4f3310(s32 a);
extern void func_28EB10(const void *a, u16 b);
extern void func_183960(const void *a);
extern void func_183D50(const void *a, s32 b, s32 c, s32 d);
extern void func_183950(const void *a, s32 b);
extern void func_37BAC0(s32 a);
extern s32 func_290D30(const void *a, s32 b);
extern Handle *func_1FEDE0(void);
extern Item *func_430B30(void *a);
extern Item *func_430B50(void *a);
extern s32 func_430580(void *a, s32 b);
extern void func_379400(s32 a, s32 b);
extern void func_28EDE0(void *a, s32 b, s32 c);
extern s32 insmenu_InsectVsGetLoadedTeam_4f9440(s16 *a);
extern void func_379BE0(s32 a, s32 b, s32 c, s32 d);

s32 insmenu_InsectVsSaveScreenOpen_4f8ef0(s32 arg0, s32 reset)
{
    s32 ids[8];
    s16 sp5E;
    const s32 *ws;
    s32 *wd;
    s32 k;
    s32 w0;
    s32 w1;
    s16 n;
    s16 sel;
    Handle *hnd;
    Item *it;
    s32 t;

    if (reset != 0) {
        insmenu_InsectVsTasksSuspend_4e9fc0();
        func_291110(D_004FA180, 0x88B9, 1, 1);
        func_290690(D_004FA180, 0x88B9, 1.0f, D_0047D460, 0.0f);
        D_00484374 = 0;
        D_00484350 = 0;
        D_00484360 = 0;
        D_00484348 = 0;
        D_0048436C = 0;
        D_00484368 = 0;
        D_00484364 = 0;
        D_00484358 = 0;
        D_00484370 = 0;
    }
    if (func_290770(D_004FA180, 0x88B9) >= 1.0f) {
        if (D_00484374 == 0) {
            insmenu_InsectVsSceneRenderHide_4e9f80();
            insmenu_InsectVsSaveSysInit_4f95d0();
            func_131B60(D_004FA280, 0, 0x70);
            insmenu_InsectVsSaveResultCbSet_4ebce0();
            insmenu_InsectVsSaveProgressWindowShow_4f6b90(2, 0);
            func_2907A0(D_004FA180, 0x9CA7, 0.0f);
            insmenu_InsectVsSetSceneBgFlagMaybe_4f3310(0);
            D_00484344 = 0;
            D_00484374 = 1;
            D_00480464 = 1;
            ws = D_004F9780;
            wd = ids;
            k = 4;
            do {
                w0 = ws[0];
                w1 = ws[1];
                wd[0] = w0;
                wd[1] = w1;
                ws += 2;
                wd += 2;
            } while (--k > 0);
            n = 0;
            while (ids[n] != -1) {
                func_28EB10(D_004FA1A0, ids[n]);
                n++;
            }
            func_183960(D_004B2570);
            func_183D50(D_004B2570, 0xF00C, 0xC, 7);
            func_183950(D_004B2570, 0x78);
            func_183960(D_004B27E0);
            func_183D50(D_004B27E0, 0xF00C, 0xC, 7);
            func_183950(D_004B27E0, 0x78);
        }
    }
    if (D_00484374 == 1) {
        func_37BAC0(0);
        if (func_290D30(D_004FA180, 0x88BA) == 0) {
            hnd = func_1FEDE0();
            sel = ((Ctx *)hnd->field24)->field1188->field08;
            if (sel == 0x1F6 || sel == 0x1F7 || sel == 0x193) {
                D_00484358 = 0;
                if (sel == 0x1F6) {
                    it = func_430B30(hnd->field24);
                    if (it != 0) {
                        if (it->bit0) {
                            D_00484358 = 1;
                        }
                    }
                } else if (sel == 0x1F7) {
                    it = func_430B30(hnd->field24);
                    if (it != 0) {
                        if (it->bit1) {
                            D_00484358 = 1;
                        }
                    }
                } else if (sel == 0x193) {
                    it = func_430B50(hnd->field24);
                    if (it != 0) {
                        if (it->bit1) {
                            D_00484358 = 1;
                        }
                    }
                }
                if (D_00484358 != 0) {
                    t = func_430580(hnd->field24, 0);
                    if (t != 0) {
                        func_291110(D_004FA180, 0x9CA7, 1, 1);
                        func_290690(D_004FA180, 0x9CA7, 1.0f, D_0047D460, 0.0f);
                        func_379400(t, 0);
                        func_28EDE0(&D_004842E8, 0x88C4, 0);
                    }
                } else {
                    func_28EDE0(&D_004842E8, 0x88C6, 0);
                }
            } else {
                func_28EB10(D_004FA1A0, 0x88B9);
                if (sel == 0x25C || sel == 0x267) {
                    t = func_430580(hnd->field24, 0);
                    if (t != 0) {
                        func_291110(D_004FA180, 0x9CA7, 1, 1);
                        func_290690(D_004FA180, 0x9CA7, 1.0f, D_0047D460, 0.0f);
                        func_379400(t, 0);
                        func_28EDE0(&D_004842E8, 0x88C4, 0);
                    }
                } else if (sel == 0x26F) {
                    func_28EDE0(&D_004842E8, 0x88C0, 0);
                } else {
                    sp5E = 0;
                    t = insmenu_InsectVsGetLoadedTeam_4f9440(&sp5E);
                    if (t != 0) {
                        D_00484350 = 1;
                        func_379BE0(t, D_00480464, sp5E, 0);
                    }
                    if (D_00484350 != 0) {
                        func_28EDE0(&D_004842E8, 0x88BD, 0);
                    } else {
                        func_28EDE0(&D_004842E8, 0x88BE, 0);
                    }
                }
            }
        }
    }
    return 1;
}
