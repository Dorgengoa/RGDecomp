#include "types.h"

/* factory.bin overlay, 0x00504DE0 -- forward to func_186DC0 on a sub-object.
 *
 * Pass-27 conversion (session 7).  The delay slot carries `addiu $4, $4, 0x1C8`,
 * so the one argument is the caller's own pointer displaced by 0x1C8.
 */

extern s32 func_186DC0(void *p);

s32 factory_ModelObjGetFadeAlpha_504de0(void *p)
{
    return func_186DC0((u8 *)p + 0x1C8);
}
