#include "types.h"
/* normal 0x00519830 -- two guards that both return 0, then the live body.
 * `sb $4,-0x96C` in the jal's delay slot is the latch write sharing the `1`
 * that the blezl delay slot already materialised. */

typedef struct Obj {
    u8  pad000[0x12];
    s16 f12;
} Obj;

typedef struct W {
    u8  pad000[0x1C];
    s32 f1C;
} W;

extern s8  D_00484804;   /* gp - 0x96C */
extern s8  D_00484808;   /* gp - 0x968 */
extern W  *D_004847D8;   /* gp - 0x998 */

extern void func_376B10(s32 a);
extern void normal_TransSavePortSelectDraw_519e80(s32 a);
extern void normal_TransSavePortCursorBob_5187c0(s32 a, s32 b, s32 c);
extern void func_28EA90(W *w, s32 a, s32 b);

s32 normal_TransSavePortConfirmCb_519830(Obj *p)
{
    if ((D_004847D8->f1C & 1) != 0) {
        return 0;
    }
    if (D_00484808 > 0) {
        return 0;
    }
    D_00484804 = 1;
    func_376B10(1);
    normal_TransSavePortSelectDraw_519e80(p->f12);
    normal_TransSavePortCursorBob_5187c0(p->f12, 0, 0);
    func_28EA90(D_004847D8, 3, 1);
    return 1;
}
