#include "types.h"

/* title.bin overlay, 0x004EDEC0 -- the memory-card step of the boot sequence,
 * a two-state machine on D_0048421C.  The compare chain tests 1 then 0, which
 * by the reversed-case-order rule is source order `case 0: case 1:`, and the
 * two-case switch is what produces it.
 *
 * $at in `slti $1, $2, 0x3` says the loop condition was consumed straight by
 * the branch, so it is a plain `while`, not a materialised flag.
 *
 * +0x16 is `volatile` and that is load-bearing: the loop TEST and the loop
 * BODY each read it, and plain, mwcc propagates the test's value into the body
 * and sinks the decrement into the `beql` delay slot -- one word short.  Retail
 * re-loads at the top of the body (the duplicated `lh` IS the body's first
 * instruction, hoisted into the delay slot by the usual loop rotation).  Third
 * distinct anti-CSE use of `volatile` in this tree, after the const-extern
 * hoist and the across-a-call CSE in title_FUN_004EC700.
 */

typedef struct Obj_title_FUN_004edec0 {
    u8 pad000[0x16];
    volatile s16 field016;      /* +0x16 */
    u8 pad018[0x2];
    s16 field01A;      /* +0x1A */
} Obj_title_FUN_004edec0;

extern s8 D_0048421C;
extern void *D_004841E8;

extern s32 func_37BAA0(void);
extern u8 func_37B9B0(s32 a);
extern void title_TitleLoadShowError_4eeb70(s32 a);
extern s32 func_37B970(void);
extern void func_37B9E0(s32 a);
extern s32 title_TitleGetSaveCtx_4ef380(void);
extern s32 func_373340(s32 a);
extern void title_TitleLoadShowMsg_4eeb60(s32 a);
extern Obj_title_FUN_004edec0 *func_28EA40(void *a, s32 b);
extern void func_28EB40(void *a, void *b);
extern void func_37BA50(s32 *out);
extern void func_28EA90(void *a, s32 b, s32 c);
extern void title_TitleLoadFadeWidgets_4eda30(s32 a);
extern void func_376B20(s32 a);

s32 title_TitleLoadCardScanTickCb_4edec0(void)
{
    Obj_title_FUN_004edec0 *o;
    s32 n;
    s32 r;

    switch (D_0048421C) {
    case 0:
        if (func_37BAA0() == 0) {
            break;
        }
        if (func_37B9B0(0) == 0) {
            title_TitleLoadShowError_4eeb70(8);
            return 1;
        }
        r = func_37B970();
        if (r == 0) {
            func_37B9E0(3);
            D_0048421C = D_0048421C + 1;
        } else if (r == 7) {
            title_TitleLoadShowError_4eeb70(7);
        } else {
            title_TitleLoadShowError_4eeb70(5);
        }
        break;
    case 1:
        if (func_37BAA0() == 0) {
            break;
        }
        r = func_37B970();
        if (r == 0 || r == 7) {
            if (func_373340(title_TitleGetSaveCtx_4ef380()) <= 0) {
                title_TitleLoadShowError_4eeb70(0x10);
                break;
            }
            title_TitleLoadShowMsg_4eeb60(-1);
            o = func_28EA40(D_004841E8, 0x7534);
            func_28EB40(D_004841E8, o);
            if (o != 0) {
                func_37BA50(&n);
                o->field016 = n;
                while (o->field016 >= 3) {
                    o->field016 = o->field016 - 1;
                    o->field01A = o->field01A + 1;
                }
            }
            func_28EA90(D_004841E8, 0x7534, 0);
            title_TitleLoadFadeWidgets_4eda30(1);
            func_376B20(0x23);
        } else {
            title_TitleLoadShowError_4eeb70(5);
        }
        break;
    }
    return 1;
}
