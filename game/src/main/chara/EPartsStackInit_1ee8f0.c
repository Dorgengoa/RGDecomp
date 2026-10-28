/* rgp:protos */
#define RGP_SELF_EPartsStackInit_1ee8f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern char *strcpy(char *, const char *);
extern u32 strlen(const char *);
extern char D_0045B700[16];
extern char D_0045B710[16];
extern char D_0045B720[16];
extern char D_0045B730[16];
extern char D_0045B740[16];

void EPartsStackInit_1ee8f0(u8 *arg0, s32 arg1, s32 arg2)
{
    if (*(s16 *)(arg0 + 0x8) != 6) {
        MemStackClear_14dff0(arg0 + 0xC);
        MemStackInit_14d810(arg0 + 0xC, MemStackAllocAligned64_14da10(arg1, arg2), arg2);
        MemStackReset_14d830(arg0 + 0xC);
    } else {
        MemStackClear_14dff0(arg0 + 0xC);
        MemStackHeapInit_14dee0(arg0 + 0xC, MemStackAllocAligned64_14da10(arg1, arg2), arg2);
        MemStackHeapReinit_14de90(arg0 + 0xC);
    }
    switch (*(s16 *)(arg0 + 0x8)) {
    case 0:
        if (strlen(D_0045B700) < 0x10U) {
            strcpy((char *)(arg0 + 0xC), D_0045B700);
        }
        break;
    case 2:
        if (strlen(D_0045B710) < 0x10U) {
            strcpy((char *)(arg0 + 0xC), D_0045B710);
        }
        break;
    case 3:
        if (strlen(D_0045B720) < 0x10U) {
            strcpy((char *)(arg0 + 0xC), D_0045B720);
        }
        break;
    case 4:
        if (strlen(D_0045B730) < 0x10U) {
            strcpy((char *)(arg0 + 0xC), D_0045B730);
        }
        break;
    case 6:
        if (strlen(D_0045B740) < 0x10U) {
            strcpy((char *)(arg0 + 0xC), D_0045B740);
        }
        break;

    }
}
