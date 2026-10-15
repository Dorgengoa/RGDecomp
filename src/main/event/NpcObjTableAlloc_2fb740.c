#include "types.h"
#pragma opt_common_subs off

extern s32 ConstructNewArray_100710(s32 arg0, void *arg1, s32 arg2, s32 arg3, s32 arg4);
extern s32 MemStackNew_14e1b0(s32 arg0);
extern void NpcObjInit_2fcd50(s32 arg0);
extern void NpcObjCtor_2fb7e0(void);

void NpcObjTableAlloc_2fb740(void *arg0, s32 padding, s32 arg2) {
    s32 temp_2;
    s32 rec;
    s32 i;

    temp_2 = ConstructNewArray_100710(MemStackNew_14e1b0((arg2 * 0xE0) + 0x10), &NpcObjCtor_2fb7e0, 0, 0xE0, arg2);
    *(s32 *)((u8 *)arg0 + 0x4) = temp_2;
    if (temp_2 != 0) {
        *(s16 *)((u8 *)arg0 + 0x8) = arg2;
        rec = *(s32 *)((u8 *)arg0 + 0x4);
        for (i = 0; i < *(s16 *)((u8 *)arg0 + 0x8); ) {
            NpcObjInit_2fcd50(rec);
            i++;
        rec += 0xE0;
        }
    }
}
