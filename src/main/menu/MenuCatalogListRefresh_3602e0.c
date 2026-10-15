#include "types.h"

/* The three callees all take arg0: retail sets up NO argument register before
   any of the three `jal`s because `$a0` still holds it. Declaring them
   `(void)` is 4 bad -- mwcc then treats `$a0` as dead after the switch load
   and puts the loaded value there. [[levers.d/main-session22-levers]]'s
   missing-call-argument class, read from the register-choice side. */
extern void MenuCatalogRankRowsFill_35cd70(void *);
extern void MenuCatalogBountyRowsFillMaybe_35cfe0(void *);
extern void MenuCatalogItemGridFill_35d5e0(void *);

void MenuCatalogListRefresh_3602e0(void *arg0)
{
    s32 temp_5;

    temp_5 = *(s32 *)((u8 *)arg0 + 0x284);
    switch (temp_5) {
    case 0:
        MenuCatalogItemGridFill_35d5e0(arg0);
        return;
    case 1:
        MenuCatalogBountyRowsFillMaybe_35cfe0(arg0);
        return;
    case 2:
        MenuCatalogRankRowsFill_35cd70(arg0);
        return;
    }
}
