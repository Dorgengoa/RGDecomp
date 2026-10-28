/* rgp:protos */
#define RGP_SELF_SlotRecordStore_3e52f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_common_subs off

/*rgp*/                       /* extern */
/*rgp*/              /* extern */
/*rgp*/                                   /* extern */
/*rgp*/                             /* extern */
s32 memcpy(u8 *, s32, s32);                           /* extern */
extern u8 D_004658F0[0x400];

u8 *SlotRecordStore_3e52f0(s32 arg0, s16 arg1, s32 arg2, s32 arg3) {
    s16 temp_17;
    s16 temp_17_2;
    s16 temp_18;
    u8 *temp_2;

    if ((arg2 == 0) || (arg3 < (*(s32 *)D_004658F0))) {
        return 0;
    }
    SaveDataClearError_3e6350((void *)arg0);
    temp_2 = ((u8 *)SlotRecordFindById_3e4e80(arg0, arg1));
    if (temp_2 == 0) {
        return 0;
    }
    if (SlotRecordValidate_3e52b0(arg0, arg2, arg3, 1, 0) & 0xFF) {
        goto copy;
    }
    temp_18 = (*(u16 *)((u8 *)temp_2 + 0x0));
    temp_17_2 = (*(u16 *)((u8 *)temp_2 + 0x2));
    SlotRecordReset_3eeca0(temp_2);
    (*(u16 *)((u8 *)temp_2 + 0x0)) = temp_18;
    (*(u16 *)((u8 *)temp_2 + 0x2)) = temp_17_2;
    return 0;
copy:
    temp_17 = (*(s16 *)((u8 *)temp_2 + 0x0));
    memcpy(temp_2, arg2, 0x350);
    (*(s16 *)((u8 *)temp_2 + 0x0)) = temp_17;
    (*(s16 *)((u8 *)temp_2 + 0x2)) = arg1;
    return temp_2;
}
