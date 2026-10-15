#include "types.h"

/* Retail's `beql $1,$0` skips the strcpy when the length is >= 0x10, so the
   source guard is `if (strlen(..) < 0x10)`.  Both string symbols are %hi/%lo
   => incomplete arrays. */

extern char D_00462330[];
extern char D_004E7B40[];

extern u32 strlen(const char *s);
extern char *strcpy(char *d, const char *s);
extern s32 MemStackAllocQw_14d950(void *p, s32 n);
extern void MemStackInit_14d810(void *p, s32 a, s32 b);
extern void MemStackReset_14d830(void *p);

s32 SysFontHeapInit_3134e0(void *p)
{
    if (p == 0) {
        return 0;
    }
    if (strlen(D_00462330) < 0x10) {
        strcpy(D_004E7B40, D_00462330);
    }
    MemStackInit_14d810(D_004E7B40, MemStackAllocQw_14d950(p, 0x6500), 0x6500);
    MemStackReset_14d830(D_004E7B40);
    return 1;
}
