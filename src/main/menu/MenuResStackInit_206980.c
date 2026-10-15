#include "types.h"

extern s32 Memalign_130ba8(s32, s32);
extern void MemStackInit_14d810(void *, s32, s32);
extern void MemStackReset_14d830(void *);
extern void MemStackClear_14dff0(void *);
extern s32 MenuResStackSize_202610(void);
extern s32 GetMenuResGroup_206a40(void);
extern void MenuResGroupStacksInit_42c810(s32, void *);
extern s8 *strcpy(s8 *, const s8 *);
extern u32 strlen(const s8 *);
extern s8 D_0045C518[];
extern u8 D_004BC040[];

s32 MenuResStackInit_206980(void)
{
    s32 v1;
    s32 v2;

    v1 = MenuResStackSize_202610();
    v2 = Memalign_130ba8(0x10, v1 * 0x10);
    if (v2 == 0) {
        return 0;
    }
    MemStackClear_14dff0(D_004BC040);
    MemStackInit_14d810(D_004BC040, v2, v1);
    if (strlen(D_0045C518) < 0x10U) {
        strcpy((s8 *)D_004BC040, D_0045C518);
    }
    MemStackReset_14d830(D_004BC040);
    MenuResGroupStacksInit_42c810(GetMenuResGroup_206a40(), D_004BC040);
    return v1;
}
