#include "types.h"

s32 CharaGetActionCategory_213690(u8 *arg0)
{
    s32 f;

    f = *(s32 *)(arg0 + 0xA44);
    if (f & 0x10) {
        return 7;
    }
    if (f & 2) {
        return 8;
    }
    if (*(s16 *)(arg0 + 0xA38) != 0) {
        goto end;
    }
    switch (*(s16 *)(arg0 + 0xA32)) {
    case 0:
    case 1:
    case 2:
    case 3:
        switch (*(s16 *)(arg0 + 0xA34)) {
        case 0:
        case 30:
        case 31:
        case 14:
            return 0;
        case 1:
            return 1;
        case 2:
            return 2;
        }
        break;
    case 6:
        return 5;
    case 4:
        return 4;
    case 5:
        return 3;
    case 15:
        return 9;
    case 16:
        return 10;
    }
end:
    return 0xB;
}
