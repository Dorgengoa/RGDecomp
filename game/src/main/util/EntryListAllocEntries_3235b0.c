/* rgp:protos */
#define RGP_SELF_EntryCtor_323cc0 1
#define RGP_SELF_EntryListAllocEntries_3235b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern u8 EntryCtor_323cc0[];

s32 EntryListAllocEntries_3235b0(void *arg0) {
    u8 *p;
    s32 temp_17;
    s32 temp_2;
    s32 temp_2_2;
    s32 rec;
    s32 i;

    p = (u8 *)arg0;
    temp_17 = EntryListGetHeap_3237d0((void *)arg0);
    temp_2 = ((short)EntryListGetCount_323680(p));
    if (temp_2 <= 0) {
        return 0;
    }
    if (temp_17 == 0) {
        return 0;
    }
    temp_2_2 = ((s32)ConstructNewArray_100710(((s32)MemStackNew_14e1b0((temp_2 * 0x78) + 0x10, temp_17)), EntryCtor_323cc0, 0, 0x78, temp_2));
    *(s32 *)(p + 8) = temp_2_2;
    if (temp_2_2 == 0) {
        return 0;
    }
    for (rec = temp_2_2, i = 0; i < temp_2; rec += 0x78, i++) {
        EntryReset_323c20(rec);
    }
    return 1;
}
