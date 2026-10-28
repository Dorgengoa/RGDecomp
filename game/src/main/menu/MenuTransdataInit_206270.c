/* rgp:protos */
#define RGP_SELF_MenuTransdataInit_206270 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_0045C460[];
extern s32 D_00481BF8;
extern u8 D_004BBF80[];

void MenuTransdataInit_206270(void)
{
    RecStackMemStackCreate_201d80(D_004BBF80, &D_00481BF8, D_0045C460, 0xFA00);
}
