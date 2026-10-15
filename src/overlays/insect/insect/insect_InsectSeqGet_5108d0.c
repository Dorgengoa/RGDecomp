#include "types.h"
/* insect 0x005108D0 -- 12 bytes, 3 instructions.  Returns the address of the
 * overlay data block at D_00525E00, rematerialised with its own lui/addiu.
 */

extern u8 D_00525E00[];

void *insect_InsectSeqGet_5108d0(void)
{
    return D_00525E00;
}
