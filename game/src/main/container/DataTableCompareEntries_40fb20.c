/* rgp:protos */
#define RGP_SELF_DataTableCompareEntries_40fb20 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

s32 DataTableCompareEntries_40fb20(s32 pd0, void *arg1, void *arg2)
{
    s16 temp_2_2;
    s16 temp_2_4;
    s16 temp_3_2;
    s16 temp_3_3;
    s16 temp_3_5;
    s32 temp_2;
    s32 temp_2_3;
    s32 temp_3;
    s32 temp_3_4;
    s32 var_2;
    s32 ca, cc;

    var_2 = CompareNullness_368070((void *)pd0, (int)arg1, (int)arg2);
    if ((!((var_2 == 0) && (arg1 != NULL))) || (arg2 == NULL)) return var_2;
    temp_3 = *(u8*)((u8 *)arg1 + 0xE) & 1;
    if ((temp_3 == 0) && (*(u8*)((u8 *)arg2 + 0xE) & 1)) {
        return -1;
    }
    if ((temp_3 != 0) && !(*(u8*)((u8 *)arg2 + 0xE) & 1)) {
        return 1;
    }
    temp_3_2 = *(s16 *)((u8 *)arg2 + 0x2);
    temp_2_2 = *(s16 *)((u8 *)arg1 + 0x2);
    if (temp_2_2 < temp_3_2) {
        return -1;
    }
    if (temp_3_2 < temp_2_2) {
        return 1;
    }
    ca = *(s16*)((u8 *)arg1 + 0xA);
    cc = *(s16*)((u8 *)arg2 + 0xA);
    temp_2 = ByteKeyCompare_428a70(ca, *(s32*)((u8 *)arg1 + 0x20), cc, *(s32*)((u8 *)arg2 + 0x20));
    if (temp_2 != 0) {
        return temp_2;
    }
    temp_3_3 = *(s16 *)((u8 *)arg1 + 0x10);
    if ((temp_3_3 >= 0) && (*(s16 *)((u8 *)arg2 + 0x10) < 0)) {
        return -1;
    }
    if ((temp_3_3 < 0) && (*(s16 *)((u8 *)arg2 + 0x10) >= 0)) {
        return 1;
    }
    temp_3_4 = *(s32*)((u8 *)arg2 + 0x4);
    temp_2_3 = *(s32*)((u8 *)arg1 + 0x4);
    if (temp_2_3 < temp_3_4) {
        return -1;
    }
    if (temp_3_4 < temp_2_3) {
        return 1;
    }
    temp_3_5 = *(s16 *)((u8 *)arg2 + 0x0);
    temp_2_4 = *(s16 *)((u8 *)arg1 + 0x0);
    if (temp_2_4 < temp_3_5) {
        return -1;
    }
    var_2 = temp_3_5 < temp_2_4;
    return var_2;
    return var_2;
}
