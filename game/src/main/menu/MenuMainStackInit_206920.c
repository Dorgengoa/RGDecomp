/* rgp:protos */
#define RGP_SELF_MenuMainStackInit_206920 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_0045C508[];
extern s32 D_00481BC0;
extern u8 D_004BBBC0[];

void MenuMainStackInit_206920(void)
{
    RecStackMemStackCreate_201d80(D_004BBBC0, &D_00481BC0, D_0045C508, 0xC1CC);
}
