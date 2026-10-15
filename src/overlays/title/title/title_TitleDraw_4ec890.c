#include "types.h"

/* title.bin overlay, 0x004EC890 -- a chain of guards that all bail out with 1,
 * then a conditional pair of calls and an unconditional one.
 *
 * The `bnel`/`beql` delay slots here carry the NEXT guard's load rather than a
 * return value, so this is an ordinary early-return chain.
 */

extern void *D_00484160;
extern s16 D_004803A8;
extern u8 D_004803A4;
extern void *D_00484170;
extern void *D_00484174;
extern void func_291910(void *a);
extern void *func_1F5BE0(void);
extern void func_1CF6D0(void *a);

s32 title_TitleDraw_4ec890(void)
{
    if (D_00484160 == 0) {
        return 1;
    }
    if (D_004803A8 != 0) {
        return 1;
    }
    if (D_004803A4 == 1) {
        func_291910(D_00484170);
        if (D_00484174 != 0) {
            func_291910(D_00484174);
        }
    }
    func_1CF6D0(func_1F5BE0());
    return 1;
}
