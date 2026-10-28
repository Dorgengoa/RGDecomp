/* rgp:protos */
#define RGP_SELF_MenuEasyStackInit_206360 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern s32 D_00481BF0 __attribute__((section(".sdata")));
extern u8 D_004BBEC0[];
extern u8 D_004BBB60[];
extern char D_0045C480[];

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern u32 strlen(const char *s);
extern char *strcpy(char *d, const char *s);

s32 MenuEasyStackInit_206360(void *a)
{
    if (D_00481BF0 != 0) {
        return 0;
    }
    MemStackClear_14dff0(D_004BBEC0);
    MemStackInit_14d810(D_004BBEC0, MemStackAllocQw_14d950(D_004BBB60, a), a);
    if (strlen(D_0045C480) < 0x10) {
        strcpy((char *)D_004BBEC0, D_0045C480);
    }
    MemStackReset_14d830(D_004BBEC0);
    MemStackAlign64_14d8e0(D_004BBEC0);
    D_00481BF0 = 1;
    return 0;
}
