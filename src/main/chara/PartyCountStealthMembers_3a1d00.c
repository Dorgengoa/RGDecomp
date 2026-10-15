#include "types.h"

extern void *PartyGetSlotChara_3c2fb0(s32, s32);
extern void *D_004837C0;

s32 PartyCountStealthMembers_3a1d00(void)
{
    s32 count = 0;
    s32 idx = 0;
    void *rec;

    for (;;) {
        rec = PartyGetSlotChara_3c2fb0(*(s32 *)((u8 *)D_004837C0 + 0x18), idx);
        if (rec == NULL) {
            break;
        }
        if (((u64) ((s64) *(u8 *)((u8 *)rec + 0x4B4) << 0x3E) >> 0x3F) != 0) {
            count++;
        }
        idx++;
    }
    return count;
}
