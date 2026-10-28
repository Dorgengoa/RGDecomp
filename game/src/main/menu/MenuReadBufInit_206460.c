/* rgp:protos */
#define RGP_SELF_MenuReadBufInit_206460 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
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
    temp_2 = ((s32)GetLoaderMgr_1f59d0());
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
