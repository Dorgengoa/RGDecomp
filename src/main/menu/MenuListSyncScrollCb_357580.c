#include "types.h"

struct S357580 { u8 pad000[0x16C]; u8 m16C; };

extern struct S357580 *D_00482380;
extern void MenuListSyncScrollMaybe_357480(void);

s32 MenuListSyncScrollCb_357580(void)
{
    u8 v;

    v = D_00482380->m16C;
    switch (v) {
    case 0:
        break;
    case 1:
        MenuListSyncScrollMaybe_357480();
        break;
    }
    return 1;
}
