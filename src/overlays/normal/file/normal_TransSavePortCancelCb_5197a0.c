#include "types.h"
/* normal 0x005197A0 -- linear prologue then a two-arm split on
 * normal_TransMenuIsQuickOpen_514a00's result. */

typedef struct Obj {
    u8  pad000[0x12];
    s16 f12;
} Obj;

extern s8    D_00484804;   /* gp - 0x96C */
extern void *D_004847D8;   /* gp - 0x998 */
extern void *D_004847D0;   /* gp - 0x9A0 */

extern void normal_TransSaveShowMsg_519ff0(s32 a);
extern void normal_TransSavePortCursorBob_5187c0(s32 a, s32 b, s32 c);
extern s32  normal_TransMenuIsQuickOpen_514a00(void);
extern void func_28EA90(void *w, s32 a, s32 b);
extern void func_37BB70(void);
extern void func_28EDE0(void *w, s32 a, s32 b);

s32 normal_TransSavePortCancelCb_5197a0(Obj *p)
{
    D_00484804 = 1;
    normal_TransSaveShowMsg_519ff0(-1);
    normal_TransSavePortCursorBob_5187c0(p->f12, 0, 0);
    if (normal_TransMenuIsQuickOpen_514a00() != 0) {
        func_28EA90(D_004847D8, 7, 0);
    } else {
        func_37BB70();
        func_28EDE0(D_004847D0, 7, 0);
    }
    return 1;
}
