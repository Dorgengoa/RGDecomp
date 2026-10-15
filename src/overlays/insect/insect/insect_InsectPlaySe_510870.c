#include "types.h"
/* insect 0x00510870 -- 80 bytes, 20 instructions.  Names the CALL RESULT so the
 * handle test sits between the two calls; the 1.0f is an inline `lui 0x3F80` /
 * `mtc1`, not a .lit4 pool load. */

extern s32  func_1F5BE0(void);
extern void func_1D05D0(s32 h, s32 id, f32 v);

void insect_InsectPlaySe_510870(s32 id)
{
    s32 h;

    if (id != -1) {
        h = func_1F5BE0();
        if (h != 0) {
            func_1D05D0(h, id, 1.0f);
        }
    }
}
