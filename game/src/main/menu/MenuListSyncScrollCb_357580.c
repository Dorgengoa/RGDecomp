/* rgp:protos */
#define RGP_SELF_MenuListSyncScrollCb_357580 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct S357580 { u8 pad000[0x16C]; u8 m16C; };

extern struct S357580 *D_00482380;
/*rgp*/

s32 MenuListSyncScrollCb_357580(void *rgp_a0)
{
    u8 v;

    v = D_00482380->m16C;
    switch (v) {
    case 0:
        break;
    case 1:
        MenuListSyncScrollMaybe_357480((void *)rgp_a0);
        break;
    }
    return 1;
}
