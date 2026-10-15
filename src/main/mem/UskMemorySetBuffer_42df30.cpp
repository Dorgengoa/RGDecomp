/* MATCH (s41m). Stale pre-match note follows -- PARK: length 0xD4 vs retail 0xE4 (0x10 short) after 1 round. Not re-tried. */
#include "types.h"
extern "C" {

extern u32 AlignDownAdd_42e2b0(s32 arg0, s32 arg1, s32 arg2);
extern u32 AlignUp_42e2d0(s32 arg0, s32 arg1);
extern void UskStackClear_42e460(void *arg0);
extern void DListClear_42ea80(void *arg0);
extern void DListNodeInit_42ec10(u32 arg0);

class VC_0 {
public:
    u8 pad[0xC];
    virtual void f(u32 x0);
};
s32 UskMemorySetBuffer_42df30(void *arg0, s32 arg1, s32 arg2)
{
    s32 temp_18;
    u32 temp_16;
    u32 temp_2;

    *(s32 *)((u8 *)arg0 + 0x10) = 0;
    UskStackClear_42e460((u8 *)arg0 + 0x14);
    DListClear_42ea80(arg0);
    if (arg1 == 0) {
        return 0;
    }
    temp_16 = AlignUp_42e2d0(arg1, 0x10);
    temp_2 = AlignDownAdd_42e2b0(arg1, arg2, 0x10);
    if (temp_2 <= temp_16) {
        return 0;
    }
    temp_18 = temp_2 - temp_16;
    if (temp_18 - 0x20 == 0) {
        return 0;
    }
    DListNodeInit_42ec10(temp_16);
    *(s32 *)((u8 *)temp_16 + 0x14) = 0;
    *(s32 *)((u8 *)temp_16 + 0x10) = 0;
    *(s32 *)((u8 *)temp_16 + 0x18) = 0;
    *(s32 *)((u8 *)temp_16 + 0x10) = temp_18 - 0x20;
    *(s32 *)((u8 *)temp_16 + 0x14) = *(s32 *)((u8 *)temp_16 + 0x14) & ~2;
    ((VC_0 *)(arg0))->f(temp_16);
    return 1;
}

}
