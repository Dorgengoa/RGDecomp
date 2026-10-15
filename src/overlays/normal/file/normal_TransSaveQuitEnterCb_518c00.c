#include "types.h"
/* normal 0x00518C00 -- the gp POINTER handle is named BEFORE the `sb $0` store
 * to D_00484820; a gp load will not move above a store to a global, and retail
 * has exactly one load above it and the deref below it. */

typedef struct Obj {
    u8  pad000[0x10];
    s16 f10;
} Obj;

extern s8   D_00484820;   /* gp - 0x950 */
extern s32 *D_00484744;   /* gp - 0xA2C */

extern void normal_TransSaveShowMsg_519ff0(s32 a);
extern void normal_TransSaveYesNoCursorBob_5188c0(s32 a, s32 b, s32 c);

s32 normal_TransSaveQuitEnterCb_518c00(Obj *p)
{
    s32 *q = D_00484744;

    D_00484820 = 0;
    if (*q > 0) {
        normal_TransSaveShowMsg_519ff0(0x12D);
    } else {
        normal_TransSaveShowMsg_519ff0(0x12C);
    }
    normal_TransSaveYesNoCursorBob_5188c0(1, 1, 1);
    p->f10 = 1;
    return 1;
}
