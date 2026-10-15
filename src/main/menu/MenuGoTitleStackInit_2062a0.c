#include "types.h"

extern s32 D_00481BF4 __attribute__((section(".sdata")));
extern u8 D_004BBF20[];
extern u8 D_004BBB60[];
extern const char D_0045C470[];

extern void MemStackClear_14dff0(void *a);
extern void *MemStackAllocQw_14d950(void *a, void *b);
extern void MemStackInit_14d810(void *a, void *b, void *c);
extern void MemStackReset_14d830(void *a);
extern void MemStackAlign64_14d8e0(void *a);
extern u32 strlen(const char *s);
extern char *strcpy(char *d, const char *s);

s32 MenuGoTitleStackInit_2062a0(void *a)
{
    if (D_00481BF4 != 0) {
        return 0;
    }
    MemStackClear_14dff0(D_004BBF20);
    MemStackInit_14d810(D_004BBF20, MemStackAllocQw_14d950(D_004BBB60, a), a);
    if (strlen(D_0045C470) < 0x10) {
        strcpy((char *)D_004BBF20, D_0045C470);
    }
    MemStackReset_14d830(D_004BBF20);
    MemStackAlign64_14d8e0(D_004BBF20);
    D_00481BF4 = 1;
    return 0;
}
