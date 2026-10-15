#include "types.h"

/* insmenu 0x004F3860 (2380 bytes, 595 instructions) -- the map screen state
 * machine, dispatched on the s16 at gp - 0xDD4 (D_0048439C).
 * BYTE-IDENTICAL (lane L9, 2026-08-26).
 *
 * Three readings took this from 6 words SHORT to MATCH:
 *
 * 1. It is a `switch`, not an if/else-if chain.  The tell is that the five
 *    arms are LAID OUT ascending 0,1,2,3,4 while the compare chain TESTS
 *    them descending 4,3,2,1,0.  An if/else-if chain lays its blocks out in
 *    test order; a compiled switch with no jump table reverses the tests and
 *    keeps source order for the blocks.  Written as a chain this unit is 6
 *    words short and the whole body mis-aligns.
 * 2. The id chain is `if (id == K && D_0048436C == 2)`, not
 *    `if (id == K) { if (D_0048436C == 2) ... }`.  The tell is retail's
 *    `bnel $3, $2, .L004F397C` with the NEXT id constant in the delay slot:
 *    failing the inner test drops into the NEXT id test, which only an `&&`
 *    inside one else-if arm can do.  The nested form branches to the join.
 * 3. `dst` and `rec` are a CALLEE-SAVED REGISTER PAIR SWAP ($17/$18), and
 *    here -- unlike insmenu_InsectVsWatchEnter_4ed450, where all six permutations are
 *    INERT -- a single DECLARATION-ORDER SWAP fixes it.  `Rec *rec;` must be
 *    declared BEFORE `void *dst;` even though `rec` is assigned first.
 *    The pointee TYPES are irrelevant (Rec pointer vs void pointer give the identical object);
 *    only the ORDER moves it, and `register` on either is INERT.
 *
 * Also pinned by the listing:
 * - func_37A2B0 is called with ONE argument in case 4 and THREE in case 1,
 *   in the same TU, so it is declared with an EMPTY parameter list;
 * - `field10` is a bitfield byte (bit3 is `dsll32 28 / dsrl32 31`) and
 *   `r->bit3 = r->bit3 ^ 1;` is the xori/andi/sll-3/or insert;
 * - func_430B30/func_430B50 return a record whose byte at 0x4 is a bitfield;
 *   `and -2 / or 1` is `bit0 = 1`, `and -3 / or 2` is `bit1 = 1`;
 * - the 0/1 flags sel/alt/ok4 are `u8` tested BARE -- the same lever that
 *   closed insmenu_InsectVsTeamListStepCb_4f46b0 and that insmenu_InsectVsTeamListTitleUpdate_4f5400 records;
 * - `(s16) insmenu_InsectVsTeamListGetIndex_4f41b0()` is the dsll32/dsra32 16 pair.
 *
 * objdump -h shows .text 0x94c with no .lit4 and no .rodata -- identical
 * section set to the in-ocunits control insmenu_InsectVsTeamInfoStepCb_4f43f0 -- so this unit
 * needs NO link plumbing and is admissible to config/ocunits/insmenu.txt. */

typedef struct Rec Rec;
struct Rec {
    u8 pad00[0x10];
    u8 bit0 : 1;
    u8 bit1 : 1;
    u8 bit2 : 1;
    u8 bit3 : 1;
    u8 pad11[0xCF];
};

typedef struct Ent Ent;
struct Ent {
    u8 pad00[4];
    u8 bit0 : 1;
    u8 bit1 : 1;
};

typedef struct Info Info;
struct Info {
    s32 field0;
    s32 field4;
    s32 field8;
};

typedef struct Ctx Ctx;
struct Ctx {
    u8   pad00[4];
    s32  field4;
    Rec  field08[0x14];
    Info *field1188;
};

typedef struct Handle Handle;
struct Handle {
    u8   pad00[0x24];
    Ctx *field24;
};

typedef struct Widget Widget;
struct Widget {
    u8  pad00[0x16];
    s16 field16;
    u8  pad18[2];
    s16 field1A;
};

extern const u8 D_004FA180[];
extern const u8 D_004FA1A0[];
extern const u8 D_004B2570[];
extern const u8 D_004B27E0[];

extern u8  D_00484354;      /* gp - 0xE1C */
extern s16 D_004842E8;      /* gp - 0xE88 */
extern s16 D_0048435C;      /* gp - 0xE14 */
extern s16 D_0048436C;      /* gp - 0xE04 */
extern s32 D_004843A0;      /* gp - 0xDD0 */
extern s16 D_0048439C;      /* gp - 0xDD4 */
extern f32 D_0047D3BC;

extern Handle *func_1FEDE0(void);
extern Widget *func_28EA40(const void *a, s32 id);
extern Rec *insmenu_InsectVsTeamListGetSelRec_4f93b0(void);
extern Ent *func_430B30(Ctx *c);
extern Ent *func_430B50(Ctx *c);
extern void *func_430580(Ctx *c, s32 b);

extern s32  func_37B970(void);
extern s32  func_37B9B0(s32 a);
extern void insmenu_InsectVsSaveSetError_4f6e20(s32 a);
extern s32  func_2F6660(void);
extern s32  func_1839F0(const void *a, s32 b);
extern s32  func_2882C0(void);
extern void func_37A2B0();
extern void insmenu_InsectVsTeamListTitleUpdate_4f5400(void);
extern void func_376B20(s32 a);
extern void insmenu_InsectVsSaveShowMsg_4f6e00(s32 a, s32 b, s32 c);
extern void func_430DB0(Ctx *c, s32 b, s32 d);
extern void insmenu_InsectVsSetBusyFlagMaybe_4f32e0(s32 a);
extern void func_290690(const void *a, s32 b, f32 x, f32 y, f32 z);
extern void func_28EDE0(void *a, s32 b, s32 c);
extern void func_28EA90(const void *a, s32 b, s32 c);
extern void func_37B9E0(s32 a);
extern s32  insmenu_InsectVsTeamListGetIndex_4f41b0(void);
extern void func_377180(void *a);
extern void insmenu_InsectVsLoadYesNoCursorBob_4f69e0(s32 a, s32 b, s32 c);
extern void func_1319A8(void *a, void *b, s32 n);
extern void func_431480(Ctx *c, void *b, s32 n);
extern s32  func_430170(Ctx *c);
extern void func_4302C0(Ctx *c, s32 b);
extern void func_4313E0(Ctx *c, s32 b);
extern void insmenu_InsectVsSaveProgressWindowShow_4f6b90(s32 a, s32 b);
extern void func_37B460(s32 a);
extern s32  func_37BAA0(void);
extern void func_373100(void);

s32 insmenu_InsectVsTeamCommitCb_4f3860(void)
{
    Handle *h;
    Ctx *ctx;
    Info *info;
    Rec *base;
    Rec *r;
    Ent *e;
    Widget *w;
    Rec *rec;
    void *dst;
    s32 st;
    s32 m;
    s32 id;
    s32 id2;
    s32 a;
    s32 b;
    s32 c;
    s32 code;
    s32 n;
    s32 v;
    s32 r2;
    s16 idx;
    u8 sel;
    u8 alt;
    u8 ok4;

    st = D_0048439C;
    if (st != 3 && st != 2) {
        m = func_37B970();
        if ((func_37B9B0(1) & 0xFF) == 0 || m == 6 || m == 5 || m == 8) {
            insmenu_InsectVsSaveSetError_4f6e20(8);
            return 1;
        }
    }
    h = func_1FEDE0();
    st = D_0048439C;
    switch (st) {
    case 0:
        func_430580(h->field24, 0);
        sel = 0;
        alt = 0;
        id = h->field24->field1188->field8;
        code = 5;
        if (id == 0x193 && D_0048436C == 2) {
            sel = 1;
        } else if (id == 0x1F6 && D_0048436C == 2) {
            sel = 1;
        } else if (id == 0x1F7 && D_0048436C == 2) {
            sel = 1;
        } else if (id == 0x278) {
            alt = 1;
        }
        if (sel) {
            code = 0x15;
        } else if (alt && D_00484354 == 0) {
            code = 0x258;
        } else if (alt && D_00484354 != 0) {
            code = 0x262;
        }
        insmenu_InsectVsSaveShowMsg_4f6e00(code, 1, (s16) insmenu_InsectVsTeamListGetIndex_4f41b0());
        D_004843A0 = 1;
        insmenu_InsectVsLoadYesNoCursorBob_4f69e0(1, 1, 1);
        func_37B460(0x890D);
        insmenu_InsectVsSaveProgressWindowShow_4f6b90(1, 0);
        D_0048439C = D_0048439C + 1;
        break;
    case 1:
        func_377180(&D_004843A0);
        insmenu_InsectVsLoadYesNoCursorBob_4f69e0(D_004843A0, 0, 1);
        if (func_2F6660() == 0) {
            if (func_1839F0(D_004B2570, 0x20) != 0 ||
                (func_2882C0() != 0 && func_1839F0(D_004B27E0, 0x20) != 0) ||
                ((func_1839F0(D_004B2570, 0x40) != 0 ||
                  (func_2882C0() != 0 && func_1839F0(D_004B27E0, 0x40) != 0)) &&
                 D_004843A0 == 1)) {
                insmenu_InsectVsLoadYesNoCursorBob_4f69e0(D_004843A0, 1, 0);
                func_376B20(6);
                insmenu_InsectVsSaveShowMsg_4f6e00(-1, 0, -1);
                func_28EA90(D_004FA1A0, 0x88BD, 0);
            } else if (func_1839F0(D_004B2570, 0x40) != 0 ||
                       (func_2882C0() != 0 && func_1839F0(D_004B27E0, 0x40) != 0)) {
                ctx = h->field24;
                sel = 0;
                alt = 0;
                id = ctx->field1188->field8;
                if (id == 0x193 && D_0048436C == 2) {
                    sel = 1;
                } else if (id == 0x1F6 && D_0048436C == 2) {
                    sel = 1;
                } else if (id == 0x1F7 && D_0048436C == 2) {
                    sel = 1;
                } else if (id == 0x278) {
                    alt = 1;
                }
                if (sel) {
                    rec = insmenu_InsectVsTeamListGetSelRec_4f93b0();
                    dst = func_430580(h->field24, 0);
                    func_28EA40(D_004FA1A0, 0x88BD);
                    if (dst != 0) {
                        if (rec != 0) {
                            func_1319A8(dst, rec, 0xE0);
                        }
                    }
                    insmenu_InsectVsLoadYesNoCursorBob_4f69e0(D_004843A0, 1, 0);
                    ctx = h->field24;
                    id2 = ctx->field1188->field8;
                    if (id2 == 0x1F6) {
                        e = func_430B30(ctx);
                        if (e != 0) {
                            e->bit0 = 1;
                        }
                    } else if (id2 == 0x1F7) {
                        e = func_430B30(ctx);
                        if (e != 0) {
                            e->bit1 = 1;
                        }
                    } else if (id2 == 0x193) {
                        e = func_430B50(ctx);
                        if (e != 0) {
                            e->bit1 = 1;
                        }
                    }
                    insmenu_InsectVsSaveShowMsg_4f6e00(0x16, 1, (s16) insmenu_InsectVsTeamListGetIndex_4f41b0());
                    func_376B20(0x23);
                    D_0048439C = 4;
                } else if (alt && D_00484354 == 0) {
                    w = func_28EA40(D_004FA1A0, 0x88BD);
                    base = h->field24->field08;
                    if (base != 0) {
                        if (w != 0) {
                            idx = (s16) (w->field16 + w->field1A);
                            r = &base[idx];
                            r->bit3 = r->bit3 ^ 1;
                            func_37A2B0(w->field1A, r, base);
                            insmenu_InsectVsTeamListTitleUpdate_4f5400();
                        }
                    }
                    insmenu_InsectVsLoadYesNoCursorBob_4f69e0(D_004843A0, 1, 0);
                    insmenu_InsectVsSaveShowMsg_4f6e00(0x259, 0, -1);
                    func_376B20(0x23);
                    D_0048439C = 4;
                } else {
                    dst = func_430580(ctx, 0);
                    w = func_28EA40(D_004FA1A0, 0x88BD);
                    n = 0;
                    if (w != 0) {
                        n = w->field1A + w->field16;
                    }
                    insmenu_InsectVsLoadYesNoCursorBob_4f69e0(D_004843A0, 1, 0);
                    func_376B20(5);
                    func_431480(h->field24, dst, n);
                    ctx = h->field24;
                    v = ctx->field4;
                    r2 = func_430170(ctx);
                    func_4302C0(h->field24, v);
                    func_4313E0(h->field24, r2);
                    insmenu_InsectVsSaveProgressWindowShow_4f6b90(1, 1);
                    D_0048439C = D_0048439C + 1;
                }
            }
        }
        break;
    case 2:
        func_290690(D_004FA180, 0x890D, 0.0f, D_0047D3BC, -1.0f);
        func_37B9E0(4);
        insmenu_InsectVsSaveShowMsg_4f6e00(6, 1, (s16) insmenu_InsectVsTeamListGetIndex_4f41b0());
        D_0048439C = D_0048439C + 1;
        break;
    case 3:
        if (func_37BAA0() != 0) {
            m = func_37B970();
            if (m == 6 || m == 5 || m == 8) {
                func_376B20(0x24);
                insmenu_InsectVsSaveSetError_4f6e20(6);
            } else {
                insmenu_InsectVsSaveProgressWindowShow_4f6b90(1, 0);
                func_376B20(0x23);
                insmenu_InsectVsSaveShowMsg_4f6e00(9, 1, (s16) insmenu_InsectVsTeamListGetIndex_4f41b0());
                func_373100();
                D_0048439C = D_0048439C + 1;
            }
        }
        break;
    case 4:
        func_37A2B0(D_0048435C);
        insmenu_InsectVsTeamListTitleUpdate_4f5400();
        if (func_2F6660() == 0) {
            if (func_1839F0(D_004B2570, 0x60) != 0 ||
                (func_2882C0() != 0 && func_1839F0(D_004B27E0, 0x60) != 0)) {
                func_376B20(5);
                insmenu_InsectVsSaveShowMsg_4f6e00(-1, 0, -1);
                ok4 = 0;
                ctx = func_1FEDE0()->field24;
                info = ctx->field1188;
                a = info->field0;
                b = info->field4;
                c = info->field8;
                if (a == 6) {
                    if (b == 0x3C) {
                        if (c == 0x25D) {
                            ok4 = 1;
                            func_430DB0(ctx, 0x25E, a);
                            insmenu_InsectVsSetBusyFlagMaybe_4f32e0(1);
                        }
                    } else if (b == 0x3D) {
                        if (c == 0x268) {
                            ok4 = 1;
                            func_430DB0(ctx, 0x269, a);
                            insmenu_InsectVsSetBusyFlagMaybe_4f32e0(1);
                        }
                    } else if (b == 0x3F) {
                        if (c == 0x278 && D_00484354 != 0) {
                            ok4 = 1;
                        }
                    }
                } else if (a == 5) {
                    if (b == 0x32 && (c == 0x1F6 || c == 0x1F7)) {
                        ok4 = 1;
                    }
                } else if (a == 4) {
                    if (b == 0x28 && c == 0x193) {
                        ok4 = 1;
                    }
                }
                if (ok4) {
                    func_290690(D_004FA180, 0x9CAA, 0.0f, D_0047D3BC, 0.0f);
                    func_28EDE0(&D_004842E8, 0x88BB, 0);
                } else {
                    func_28EA90(D_004FA1A0, 0x88BD, 0);
                }
            }
        }
        break;
    }
    return 1;
}
