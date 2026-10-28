/* rgp:protos */
#define RGP_SELF_MapCfgFuncData_18a090 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
extern s32 strcmp(const char *, const char *);
extern char D_00459C60[];
extern char D_00459C68[];
extern void *D_00481250;
extern s32 D_0048125C;
extern s32 D_004812D8;
extern s32 D_004812DC;
extern s32 D_004812EC;

s32 MapCfgFuncData_18a090(s32 arg0) {
    s32 var_5;
    s32 temp_2;
    s32 temp_2_2;

    if (D_004812EC == 0) {
        FuncDataTableReserve_190b70((u8 *)D_00481250 + 0x1664, 0x40, D_0048125C);
        D_004812EC = 1;
    }
    temp_2 = SlotGetInt_15f720(arg0);
    if (temp_2 == 0) {
        return 0;
    }
    if (!strcmp((char *)temp_2, D_00459C60)) {
        var_5 = 6;
        *(s32 *)((u8 *)D_00481250 + 0x1660) = 1;
        goto block_14;
    }
    if (strcmp((char *)temp_2, D_00459C68) == 0) {
        var_5 = 9;
        goto block_14;
    }
    return 0;
block_14:
    temp_2_2 = ((s32)FuncDataTableTakeFree_1909b0((u8 *)D_00481250 + 0x1664, var_5, 0, 0));
    D_004812DC = temp_2_2;
    D_004812D8 = temp_2_2;
    if (temp_2_2 == 0) {
        return 0;
    }
    return 1;
}
