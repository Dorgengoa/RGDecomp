#include "types.h"

/* factory.bin overlay, 0x0000504DD0 -- forwarder to func_1867B0.
 *
 * Pass-27 conversion (session 7).  `j func_1867B0` with a NOP delay slot: no
 * argument is marshalled, so every parameter is passed straight through and
 * mwcc turns the tail `return` into the jump.
 */

extern s32 func_1867B0(void *p);

s32 factory_ModelObjBaseInitThunk_504dd0(void *p)
{
    return func_1867B0(p);
}
