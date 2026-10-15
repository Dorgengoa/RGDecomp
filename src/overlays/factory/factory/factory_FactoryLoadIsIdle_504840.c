#include "types.h"

/* factory.bin overlay, 0x00504840 -- is the mode one of the first three?
 *
 * Pass-27 conversion (session 7).  `sltiu` (not `slti`) says the compare is
 * UNSIGNED, so the field is unsigned; it sits in the `jr $31` delay slot
 * because the load is the only thing ahead of it.
 */

typedef struct Mode {
    u8  pad00[0x50];
    u32 f50;
} Mode;

s32 factory_FactoryLoadIsIdle_504840(Mode *o)
{
    return o->f50 < 3;
}
