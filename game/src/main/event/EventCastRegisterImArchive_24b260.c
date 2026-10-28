/* rgp:protos */
#define RGP_SELF_EventCastRegisterImArchive_24b260 1
#include "port/game_protos.h"
#line 1
/* PARK 1/3: RIGHT LENGTH (64w), 31 bad -- register/structure mismatch, not length. Needs a closer asm read on the memcpy/shift args. */
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
void *memcpy(void *, const void *, s32);

s32 EventCastRegisterImArchive_24b260(s32 pdA, s32 arg1, s32 arg2, s32 pdB, s32 arg4, s32 arg5, s32 arg6) {
    u32 temp_16;
    s32 temp_19;
    s32 temp_2;
    s32 temp_2_2;
    s32 var_2;

    temp_19 = GetDrawCtxNameTable_15de40();
    if ((temp_2 = ((s32)RecStackGetSlot_1c4330(arg1, arg2))) == 0) {
        return 0;
    }
    MemStackAlign64_14d8e0(temp_2);
    var_2 = arg6 >> 4;
    if (arg6 < 0) {
        var_2 = (s32) (arg6 + 0xF) >> 4;
    }
    temp_16 = var_2 + 1;
    temp_2_2 = MemStackPeekQw_14d9d0(temp_2, temp_16);
    if (temp_2_2 == 0) {
        return 0;
    }
    MemStackAllocAligned64_14da10(temp_2, temp_16);
    memcpy((void *)temp_2_2, (void *)arg5, arg6);
    NameTableFreeGroup_158ac0(temp_19, arg4);
    NameTableRegisterImArchive_1594d0(temp_19, temp_2_2, arg4, temp_2, 0);
    return 1;
    return 0;
}
