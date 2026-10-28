/* rgp:protos */
#define RGP_SELF_MenuBattleEndStackInit_2065e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_propagation off
#pragma opt_propagation on

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern char *strcpy(char *, const char *);
extern u32 strlen(const char *);
extern char D_0045C4C0[];
extern s32 D_00481BDC;
extern u8 D_004BBD40[];
extern u8 D_004BBD68[0x400];

s32 MenuBattleEndStackInit_2065e0(void) {
            void * arg_h1;

    s32 temp_2;

    if (D_00481BDC != 0) {
        return 0;
    }
    temp_2 = ((s32)GetLoaderMgr_1f59d0());
    if (temp_2 != 0) {
        MemStackClear_14dff0(D_004BBD40);
        MemStackInit_14d810(D_004BBD40, HeapHandleAllocBack_1cdb10(temp_2, 0x11290), 0x11290);
        if (strlen(D_0045C4C0) < 0x10U) {
            arg_h1 = D_0045C4C0;
            strcpy((char *)D_004BBD40, arg_h1);
        }
        MemStackReset_14d830(D_004BBD40);
        MemStackAlign64_14d8e0(D_004BBD40);
        if ((*(s32 *)D_004BBD68) != 0) {
            D_00481BDC = 1;
        }
    }
    return 0;
}
