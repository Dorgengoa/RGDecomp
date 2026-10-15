#include "types.h"

/* factory.bin overlay, 0x00004EC7B0 -- constant 0.
 *
 * Pass-27 conversion (session 7): a spimdisasm auto-name this overlay's
 * symbol file never carried.  `daddu $2, $0, $0` in the `jr $31` delay
 * slot is mwcc's materialisation of a returned 0.
 */

s32 func_004EC7B0(void)
{
    return 0;
}
