/* rgp:protos */
#define RGP_SELF_DataTableCompareEntries_4129d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

s32 DataTableCompareEntries_4129d0(void *arg0, void *arg1, void *arg2)
{
    s16 temp_2;
    s16 temp_2_2;
    s16 temp_3;
    s16 temp_3_2;
    s32 var_2;

    var_2 = CompareNullness_368070((void *)arg0, (int)arg1, (int)arg2);
    if ((!((var_2 == 0) && (arg1 != NULL))) || (arg2 == NULL)) return var_2;
    temp_3 = *(s16 *)((u8 *)arg2 + 0x2);
    temp_2 = *(s16 *)((u8 *)arg1 + 0x2);
    if (temp_2 < temp_3) {
        return 1;
    }
    if (temp_3 < temp_2) {
        return -1;
    }
    if(*(s32 *)((u8 *)arg1+8)==0) return *(s32 *)((u8 *)arg2+8)!=0;
    return -(u8)((*(s32 *)((u8 *)arg2+8)!=0)^1);
}
