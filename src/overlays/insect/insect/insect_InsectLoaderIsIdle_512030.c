#include "types.h"
/* insect 0x00512030 -- 40 bytes, 10 instructions.  The trailing `andi 0xFF`
 * is the u8 return type.
 */

extern s32 func_1F59D0(void);
extern s32 func_1CD5B0(s32);

u8 insect_InsectLoaderIsIdle_512030(void)
{
    return func_1CD5B0(func_1F59D0());
}
