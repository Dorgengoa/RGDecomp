/* rgp:protos */
#define RGP_SELF_MenuCapStackInit_2068f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_0045C4F8[];
extern s32 D_00481BC4;
extern u8 D_004BBC20[];

void MenuCapStackInit_2068f0(void)
{
    RecStackMemStackCreate_201d80(D_004BBC20, &D_00481BC4, D_0045C4F8, 0x4010);
}
