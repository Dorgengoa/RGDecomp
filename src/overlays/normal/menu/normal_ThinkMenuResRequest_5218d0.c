#include "types.h"
/* normal 0x005218D0 -- teardown counterpart of 0x005217E0.  The `== -1` test is
 * SHARED after the if/else (retail materialises -1 in both arms and tests once),
 * and D_00484968 must be declared as an 8-byte array so its indexed load keeps
 * the gp-relative `addiu $2,$28,-0x808` base instead of a lui/%lo pair. */

typedef struct Slot { u8 pad00[0x38]; } Slot;

extern Slot D_00528110[];

extern void *D_00484968[2];       /* gp - 0x808 */
extern void *D_00484970;          /* gp - 0x800 */
extern void *D_0048491C;          /* gp - 0x854 */

extern void func_28B160(Slot *s, s32 n);
extern s32  func_28B3E0(Slot *s, void **a, void *b, s32 c, void *d, s32 e);
extern s32  func_28B550(Slot *s, void *a, s32 b, s32 c);
extern void func_28AFD0(void);

s32 normal_ThinkMenuResRequest_5218d0(void)
{
    s32 i;
    s32 r;

    func_28B160(D_00528110, 2);
    for (i = 0; i < 2; i++) {
        if (i == 0) {
            r = func_28B3E0(&D_00528110[i], &D_00484970, D_00484968[i], 0,
                            D_0048491C, 0);
        } else {
            r = func_28B550(&D_00528110[i], D_00484968[i], 0, 0);
        }
        if (r == -1) {
            break;
        }
    }
    func_28AFD0();
    return 0;
}
