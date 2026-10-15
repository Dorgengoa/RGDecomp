#include "types.h"
/* normal 0x00520800 -- copy-or-clear of the 0x80-byte D_00528090 buffer.
 * Both arms reload the buffer address, so it is written at each use. */

extern const u8 D_00528090;

extern void func_134A98(const u8 *d, const u8 *s);
extern void func_131B60(const u8 *p, s32 v, s32 n);

s32 normal_ThinkMenuSetPrompt_520800(const u8 *s)
{
    if (s != NULL) {
        func_134A98(&D_00528090, s);
    } else {
        func_131B60(&D_00528090, 0, 0x80);
    }
    return 1;
}
