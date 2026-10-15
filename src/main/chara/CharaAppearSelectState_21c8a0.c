#include "types.h"

s16 CharaAppearSelectState_21c8a0(void *arg0) {
    s16 v;
    s16 v2;

    v = *(s16 *)((u8 *)arg0 + 0xA34);
    switch (v) {
    case 0x14:
    case 0x15:
    case 0x16:
    case 0xA:
        return v;
    }
    v2 = *(s16 *)((u8 *)arg0 + 0xB48);
    switch (v2) {
    case 1:
        return 0xA;
    case 2:
        return 0x14;
    }
    return 0;
}
