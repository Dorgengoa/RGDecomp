/* rgp:protos */
#define RGP_SELF_UiPlaceItemIconInQuadrant_29f720 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

s32 UiPlaceItemIconInQuadrant_29f720(s32 arg0, void *arg1, s32 arg2, s32 arg3) {
    s16 *p;

    if (arg2 != -1) {
        p = ((s16 *)UiSetItemIconSprite_288490(arg0 + 0x5C, arg1, arg2, 0x28, 0x2D, 1));
    } else {
        p = *(s16 **)((u8 *)arg1 + 0x20);
    }

    if (p == NULL) {
        return 0;
    }
    switch (arg3) {
    case 0:
        *p = 0x21;
        *(p + 1) = 0x17;
        break;
    case 1:
        *p = 0x61;
        *(p + 1) = 0x17;
        break;
    case 2:
        *p = 0x21;
        *(p + 1) = 0x56;
        break;
    case 3:
        *p = 0x61;
        *(p + 1) = 0x56;
        break;

    }
    return 1;
}
