#include "types.h"

extern void ArenaCtxInit_370610(void *, s32);
extern s32 ResGroupGetStack_42c720(void *, s32);
extern void MemStackClear_14dff0(s32);

/* `ori $2,$0,0xFFFF` is the POSITIVE constant 0xFFFF, not -1. */

s32 ResGroupReset_42c760(u8 *p)
{
    *(u16 *)(p + 0x164) = 0xFFFF;
    ArenaCtxInit_370610(p + 0x168, 0);
    *(s16 *)(p + 0x174) = 0;
    *(s16 *)(p + 0x176) = 0;
    *(s16 *)(p + 0x178) = 0;
    *(s16 *)(p + 0x17A) = 0;
    *(s16 *)(p + 0x17C) = 0;
    *(s32 *)(p + 0x180) = 0;
    *(s32 *)(p + 0x184) = 0;
    *(s32 *)(p + 0x188) = 0;
    *(s32 *)(p + 0x18C) = 0;
    *(s32 *)(p + 0x190) = 0;
    *(s32 *)(p + 0x194) = 0;
    *(s32 *)(p + 0x198) = 0;
    *(s32 *)(p + 0x19C) = 0;
    *(s32 *)(p + 0x1A0) = 0;
    *(s32 *)(p + 0x1A4) = 0;
    MemStackClear_14dff0(ResGroupGetStack_42c720(p, 1));
    MemStackClear_14dff0(ResGroupGetStack_42c720(p, 2));
    MemStackClear_14dff0(ResGroupGetStack_42c720(p, 3));
    return 1;
}
