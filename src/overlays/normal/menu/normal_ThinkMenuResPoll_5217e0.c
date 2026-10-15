#include "types.h"
/* normal 0x005217E0 -- two-slot poll loop over the 0x38-byte D_00528110 array. */

typedef struct Slot { u8 pad00[0x38]; } Slot;

extern Slot D_00528110[];

extern s8    D_00484940;          /* gp - 0x830 */
extern void *D_0048491C;          /* gp - 0x854 */
extern void *D_00484970;          /* gp - 0x800 */

extern s32  func_28B220(Slot *s);
extern s32  func_28B210(Slot *s);
extern s32  func_28B2E0(Slot *s);
extern void *func_28B270(Slot *s, void **out);
extern void func_28B320(Slot *s, void *a, s32 b, void *c);
extern void func_28B230(Slot *s);
extern s32  func_28B070(Slot *s, s32 n);
extern void normal_ThinkMenuLayoutBuild_521400(void *a);

s32 normal_ThinkMenuResPoll_5217e0(void)
{
    s32 i;
    Slot *s;
    void *out;
    void *r;

    for (i = 0; i < 2; i++) {
        s = &D_00528110[i];
        if (func_28B220(s) != -1) {
            if (func_28B210(s) != 0) {
                if (func_28B2E0(s) == 1) {
                    r = func_28B270(s, &out);
                    if (i == 1) {
                        normal_ThinkMenuLayoutBuild_521400(r);
                    } else {
                        func_28B320(s, D_00484970, 0x32E, D_0048491C);
                    }
                    func_28B230(s);
                }
            }
        }
    }
    if (func_28B070(D_00528110, 2) == 1) {
        D_00484940 = 1;
        return 1;
    }
    return 0;
}
