#include "types.h"

extern s32 TargetRefIsValid_2e6e40(void *);

s32 EvNodeAttachObjIsTargetActive_353110(void *arg0) {
    if (TargetRefIsValid_2e6e40((u8 *)arg0 + 0xA0) == 0) {
        return 0;
    }
    if (TargetRefIsValid_2e6e40((u8 *)arg0 + 0xF4) == 0) {
        return 0;
    }
    if (*(s32 *)((u8 *)arg0 + 0x124) == 0) {
        return 0;
    }
    return *(s32 *)((u8 *)arg0 + 0x128) != 0;
}
