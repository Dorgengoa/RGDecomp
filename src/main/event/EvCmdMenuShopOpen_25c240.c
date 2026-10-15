#include "types.h"

extern void TaskSetEnabled_27c2a0(s32, void *);
extern s32 ShopMenuOpen_203780(void);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_0045EF40[];
extern u8 D_0045EF50[];

s32 EvCmdMenuShopOpen_25c240(void)
{
    s32 r2;

    TaskSetEnabled_27c2a0(1, D_0045EF40);
    TaskSetEnabled_27c2a0(1, D_0045EF50);
    r2 = ShopMenuOpen_203780();
    return 1;
}
