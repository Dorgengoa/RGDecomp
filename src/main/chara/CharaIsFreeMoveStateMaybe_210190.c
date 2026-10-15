#include "types.h"

s32 CharaIsFreeMoveStateMaybe_210190(u8 *p) {
    if (*(s16 *)(p + 0xA38) != 0) {
        return 0;
    }
    if (*(s32 *)(p + 0x940) > 0) {
        return 0;
    }
    switch (*(s16 *)(p + 0xA32)) {
    case 0:
    case 1:
    case 2:
    case 3:
        switch (*(s16 *)(p + 0xA34)) {
        case 0:
        case 1:
        case 2:
        case 20:
        case 21:
        case 22:
        case 14:
        case 30:
        case 31:
            return 1;
        }
        break;
    }
    return 0;
}
