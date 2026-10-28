/* rgp:protos */
#define RGP_SELF_ItemDefGetIconIndex_40e1b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

s32 ItemDefGetIconIndex_40e1b0(u8 *a)
{
    switch (*(s8 *)(a + 2)) {
    case 0:
        return 0;
    case 1:
        return 1;
    case 2:
        return 2;
    case 3:
        return 3;
    case 4:
        return 4;
    case 0xB:
        switch (*(s16 *)(a + 4)) {
        case 0x44C:
            return 0xB;
        case 0x44D:
            return 10;
        case 0x44E:
            return 9;
        case 0x44F:
            return 8;
        case 0x450:
            return 7;
        default:
            return 5;
        }
    case 0x15:
        switch (*(s16 *)(a + 4)) {
        case 0x451:
            return 0xC;
        default:
            return 5;
        }
    default:
        return 5;
    }
}
