#include "types.h"
extern s32 StatusEntryIsRunning_3a6190(s32);
extern void StatusEntryExpire_3a5f40(s32, s32);
struct Obj0 { u8 pad000[0xB94]; s32 mB94; };

s32 CharaSysStatusExpireAll_3a1550(struct Obj0 *p0)
{
    s32 l2;
    s32 l1;
    s32 l0;

    l0 = 0;
    l1 = p0->mB94 + 4;
    l2 = 0;
    do {
        if (StatusEntryIsRunning_3a6190(l1) != 0) {
            StatusEntryExpire_3a5f40(l1, 0);
            l2 = l2 + 1;
        }
        l0 = l0 + 1;
        l1 = l1 + 8;
    } while (l0 < 0x20);
    return l2;
}
