/* rgp:protos */
#define RGP_SELF_EntryListAllocChildren_3236c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 EntryListAllocChildren_3236c0(void *arg0)
{
    s32 temp_16;
    s32 temp_2;
    s32 temp_2_2;
    s32 var_17;
    s32 var_16;

    temp_16 = EntryListGetHeap_3237d0((void *)arg0);
    temp_2 = ((unsigned char)EntryListGetChildCount_323790(arg0));
    if (temp_2 <= 0) {
        return 0;
    }
    if (temp_16 == 0) {
        return 0;
    }
    temp_2_2 = ((s32)ConstructNewArray_100710(((s32)MemStackNew_14e1b0((temp_2 * 8) + 0x10, temp_16)), (void *)EntryChildCtor_323da0, 0, 8, temp_2));
    *(s32 *)((u8 *)arg0 + 4) = temp_2_2;
    var_17 = temp_2_2;
    if (temp_2_2 == 0) {
        return 0;
    }
    var_16 = 0;
    while (var_16 < temp_2) {
        EntryChildInit_323d90(var_17);
        var_17 += 8;
        var_16 += 1;
        continue;
    }
    return 1;
    return 0;
}
