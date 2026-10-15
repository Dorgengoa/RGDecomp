#include "types.h"

extern void MemStackInit_14d810(void *, s32, s32);
extern void MemStackReset_14d830(void *);
extern void MemStackAlign64_14d8e0(void *);
extern void MemStackClear_14dff0(void *);
extern s32 HeapHandleAllocBack_1cdb10(s32, s32);
extern s32 GetLoaderMgr_1f59d0(void);
extern void strcpy(void *, void *);
extern u32 strlen(void *);
extern u8 D_0045C490[0x10];
extern s32 D_00481BEC;
extern u8 D_004BBE60[0x10];

s32 MenuReadBufInit_206460(s32 arg0)
{
    s32 temp_2;

    if (D_00481BEC != 0) {
        return 0;
    }
    temp_2 = GetLoaderMgr_1f59d0();
    if (temp_2 != 0) {
        MemStackClear_14dff0(D_004BBE60);
        MemStackInit_14d810(D_004BBE60, HeapHandleAllocBack_1cdb10(temp_2, arg0), arg0);
        if (strlen(D_0045C490) < 0x10U) {
            strcpy(D_004BBE60, D_0045C490);
        }
        MemStackReset_14d830(D_004BBE60);
        MemStackAlign64_14d8e0(D_004BBE60);
        D_00481BEC = 1;
    }
    return 0;
}
