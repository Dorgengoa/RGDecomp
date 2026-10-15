#include "types.h"

/* insmenu 0x004F6250 (444 bytes, 111 instructions, 20 calls) -- the two-step
 * map-transition state machine.
 *
 * The OUTER dispatch is a `switch` and the two inner ones are if/else chains,
 * and the tell is block order against test order: the outer tests `== 1` first
 * but lays the `== 0` body out first, while both inner ones emit their bodies
 * in test order.
 *
 * ★ `obj->field16 -= 1;` -- NOT `obj->field16 = obj->field16 - 1;`.  The long
 * form lets mwcc reuse the loop condition's loaded value and sink the `addiu`
 * into the `beql` delay slot; the compound form re-reads the field, which is
 * what retail does, and it is one word.
 *
 * ⚠⚠  * CLOSED (L3, 2026-08-26), 111/111 words byte-identical.  The five-word
 * residue was ONE token: an explicit `return 1;` after
 * `insmenu_InsectVsSaveSetError_4f6e20(8)` INSIDE the inner if-arm.  That makes mwcc
 * materialise the return value in that block (`b <epilogue+4>` with
 * `addiu $2,$0,1` in the delay slot) and puts the shared `addiu $2,$0,1` AHEAD
 * of `ld $31` in the tail, which is the whole five-word diff.
 * !! It is the INNER return ONLY.  `default: return 1;` costs +4 words,
 * `case 0: ... return 1;` costs +1, and both together are what an earlier
 * attempt measured and recorded as "return 1 was tried".  Do not add either.
 * Measured null on the same base (build/v6250_im03.py, 13 arms, 5 inert /
 * 8 live): an rc local, a volatile rc local, optimization_level 3,
 * optimize_for_size on/off, an (s32) cast on the selector, an s8 selector
 * local, and case order swapped (12 bad).  The 117-pragma knob screen
 * (build/i_knob_batch2.log block 3, floor 5) predates the fix.
 *
 * SUPERSEDED PARK NOTE FOLLOWS.
 * PARKED AT 5 WORDS, RIGHT LENGTH -- deliberately NOT in
 * config/ocunits/insmenu.txt, because the length guard would pass it and the
 * link would emit a differing image.
 *
 * The residue is ONE fact in five places: retail's shared tail is
 * `addiu $2, $0, 1` FOLLOWED BY `ld $31, 0x10($29)`, so the two branches into
 * it carry the `addiu` in their delay slots; ours emits the restore first and
 * carries the `ld`.  Fifteen spellings measured and none moved it: `default:`
 * present, absent, and placed first; `return 1` inside one case, both cases and
 * neither; the selector read as the global, through an `s8` local and through
 * an `(s32)` cast; and the four loop rotations.  Every other word matches.
 */

typedef struct Obj Obj;
struct Obj {
    u8  pad00[0x16];
    s16 field16;
    u8  pad18[2];
    s16 field1A;
};

extern const u8 D_004FA1A0[];

extern s8 D_00484390;       /* gp - 0xDE0 */

extern s32 func_37BAA0(void);
extern u8  func_37B9B0(s32 a);
extern void insmenu_InsectVsSaveSetError_4f6e20(s32 a);
extern s32 func_37B970(void);
extern void func_37B9E0(s32 a);
extern s32 insmenu_InsectVsGetSaveCtx_4f3850(void);
extern s32 func_373340(s32 a);
extern void insmenu_InsectVsSaveShowMsg_4f6e00(s32 a, s32 b, s32 c);
extern Obj *func_28EA40(const void *a, s32 b);
extern void func_28EB40(const void *a, Obj *b);
extern void func_37BA50(s32 *a);
extern void func_28EA90(const void *a, s32 b, s32 c);
extern void insmenu_InsectVsLoadWidgetsFade_4f6ac0(s32 a);
extern void func_376B20(s32 a);

s32 insmenu_InsectVsLoadCardScanStepCb_4f6250(void)
{
    Obj *obj;
    s32 r;
    s32 v;

    switch (D_00484390) {
    case 0:
        if (func_37BAA0() != 0) {
            if (func_37B9B0(0) == 0) {
                insmenu_InsectVsSaveSetError_4f6e20(8);
                return 1;
            } else {
                r = func_37B970();
                if (r == 0) {
                    func_37B9E0(3);
                    D_00484390 = D_00484390 + 1;
                } else if (r == 7) {
                    insmenu_InsectVsSaveSetError_4f6e20(7);
                } else {
                    insmenu_InsectVsSaveSetError_4f6e20(5);
                }
            }
        }
        break;
    case 1:
        if (func_37BAA0() != 0) {
            r = func_37B970();
            if ((r == 0) || (r == 7)) {
                if (func_373340(insmenu_InsectVsGetSaveCtx_4f3850()) <= 0) {
                    insmenu_InsectVsSaveSetError_4f6e20(0x10);
                } else {
                    insmenu_InsectVsSaveShowMsg_4f6e00(-1, 0, -1);
                    obj = func_28EA40(D_004FA1A0, 0x88BB);
                    func_28EB40(D_004FA1A0, obj);
                    if (obj != 0) {
                        func_37BA50(&v);
                        obj->field16 = v;
                        while (obj->field16 >= 3) {
                            obj->field16 -= 1;
                            obj->field1A += 1;
                        }
                    }
                    func_28EA90(D_004FA1A0, 0x88BB, 0);
                    insmenu_InsectVsLoadWidgetsFade_4f6ac0(1);
                    func_376B20(0x23);
                }
            } else {
                insmenu_InsectVsSaveSetError_4f6e20(5);
            }
        }
        break;
    }
    return 1;
}
