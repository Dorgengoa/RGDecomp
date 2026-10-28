/* rgp:protos */
#define RGP_SELF_insect_InsectSeqGet_5108d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x005108D0 -- 12 bytes, 3 instructions.  Returns the address of the
 * overlay data block at insect_D_00525E00, rematerialised with its own lui/addiu.
 */

extern u8 insect_D_00525E00[];

void *insect_InsectSeqGet_5108d0(void)
{
    return insect_D_00525E00;
}
