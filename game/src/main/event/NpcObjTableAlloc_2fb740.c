/* rgp:protos */
#define RGP_SELF_NpcObjTableAlloc_2fb740 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_common_subs off

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void NpcObjTableAlloc_2fb740(void *arg0, s32 padding, s32 arg2) {
    s32 temp_2;
    s32 rec;
    s32 i;

    temp_2 = ((s32)ConstructNewArray_100710(((s32)MemStackNew_14e1b0((arg2 * 0xE0) + 0x10, (void *)padding)), &NpcObjCtor_2fb7e0, 0, 0xE0, arg2));
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
