#include "types.h"
/* normal 0x004FCB90 -- the 0x3C widget's close handler.  `$4` is never read
 * (the f(void *, s32) state-handler family); the guard is on `b` and every
 * path returns 1.  The three-way tail is a compare chain on the s16 mode at
 * gp-0xC8C, not a switch: the shared `lw $4,-0xCD8($28)` in the second
 * `bnel`'s delay slot is the scheduler duplicating one source argument. */

extern void *D_00484498;          /* gp - 0xCD8 */
extern void *D_0048449C;          /* gp - 0xCD4 */
extern s16   D_004844E4;          /* gp - 0xC8C */

extern void func_28EDE0(void *p, s32 id, s32 a);
extern void func_291110(void *p, u16 id, s32 c, s32 d);

s32 normal_BtlChgMenuMsgBoxCloseState_4fcb90(void *a, s32 b)
{
    if (b != 0) {
        func_291110(D_0048449C, 0x3C, 0, 1);
    }
    if (D_004844E4 == 2) {
        func_28EDE0(D_00484498, 0x560A, 0);
    } else if (D_004844E4 == 3) {
        func_28EDE0(D_00484498, 0x5601, 0);
    } else {
        func_28EDE0(D_00484498, 0x5606, 0);
    }
    return 1;
}
