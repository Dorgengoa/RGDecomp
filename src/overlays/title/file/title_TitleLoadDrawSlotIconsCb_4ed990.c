#include "types.h"

/* title.bin overlay, 0x004ED990 -- same shape as title_TitleLoadDrawBgCb_4ed9e0, but the
 * third argument is the RESULT of the inner call.
 *
 * ⚠ `daddu $6, $2, $0` reads $2 AFTER the jal, so it carries the callee's
 * return value -- not the `lw $2, -0x1000($28)` that was tested a few
 * instructions earlier and is dead by then.  Reading it as the global would
 * be a plausible and wrong parameter list.
 */

extern void *D_00484170;
extern s16 title_TitleLoadGetSlotScroll_4edde0(void);
extern void func_3764B0(void *o, s32 b, s16 c);

s32 title_TitleLoadDrawSlotIconsCb_4ed990(void *o, s32 b, s32 c, s32 d, s32 e)
{
    if (e != 0) {
        if (D_00484170 != 0) {
            func_3764B0(o, 1, title_TitleLoadGetSlotScroll_4edde0());
        }
    }
    return 1;
}
