#include "types.h"

extern void MemStackResetChildren_14d170(void);

void MemStackReset_14d830(void *arg0) {
    u8 c = *(u32 *)((u8 *)arg0 + 0x28) != 0;
    if (c == 0) {
        *(s32 *)((u8 *)arg0 + 0x2C) = 0;
        *(s32 *)((u8 *)arg0 + 0x30) = -1;
        *(s32 *)((u8 *)arg0 + 0x3C) = 0;
        *(s32 *)((u8 *)arg0 + 0x20) = 0;
        return;
    }
    if (*(s32 *)((u8 *)arg0 + 0x24) > 0) {
        while (*(s32 *)((u8 *)arg0 + 0x54) != 0) {
        }
    }
    *(s32 *)((u8 *)arg0 + 0x2C) = 0;
    *(s32 *)((u8 *)arg0 + 0x30) = -1;
    *(s32 *)((u8 *)arg0 + 0x3C) = 0;
    *(s32 *)((u8 *)arg0 + 0x20) = 0;
    MemStackResetChildren_14d170();
}
