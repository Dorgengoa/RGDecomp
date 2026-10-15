#include "types.h"

/* title.bin overlay, 0x004EE8F0 -- add two halfword fields, publish the sum to
 * a gp-relative global, then branch on a call result.
 *
 * `dsll32 $4, $2, 16` / `dsra32 $4, $4, 16` is a 16-bit sign extension of the
 * sum before it is passed on, i.e. the sum is an s16.
 *
 * ★ `return 1` belongs INSIDE both arms.  With one return after the join mwcc
 * hoists `ld $31` into each arm and materialises the 1 once; retail does the
 * opposite -- the 1 twice, the epilogue shared.
 */

typedef struct Obj_title_FUN_004ee8f0 {
    u8 pad000[0x12];
    s16 field012;      /* +0x12 */
    u8 pad014[0x2];
    s16 field016;      /* +0x16 */
} Obj_title_FUN_004ee8f0;

extern s16 D_004841F8;
extern void *D_004841E8;
extern void func_37B9C0(s16 a);
extern s32 title_TitleGetSaveCtx_4ef380(void);
extern s32 func_373440(s32 a, s16 b);
extern void func_376B20(s32 a);
extern void func_28EA90(void *a, s32 b, s32 c);

s32 title_TitleLoadSlotListConfirm_4ee8f0(Obj_title_FUN_004ee8f0 *o)
{
    s16 sum;

    sum = o->field016 + o->field012;
    D_004841F8 = sum;
    func_37B9C0(sum);
    if (func_373440(title_TitleGetSaveCtx_4ef380(), D_004841F8) != 0) {
        func_376B20(5);
        func_28EA90(D_004841E8, 0x7535, 0);
        return 1;
    }
    func_376B20(6);
    return 1;
}
