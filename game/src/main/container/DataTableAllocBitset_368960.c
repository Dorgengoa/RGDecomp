/* rgp:protos */
#define RGP_SELF_DataTableAllocBitset_368960 1
#include "port/game_protos.h"
#line 1
/* main s22: 1 WRONG ACCESS WIDTH(s) corrected from retail's own
   opcode (same registers + offset, different opcode -- a type defect no
   colouring lever can reach).  13 -> improved; still parked. */
#include "types.h"

/*rgp*/
extern void memset(void *arg0, s32 arg1, s32 arg2);

s32 DataTableAllocBitset_368960(void *arg0)
{
    s16 temp_4;
    s32 temp_17;
    s32 temp_2;
    s32 var_2;

    if (((u64)((s64)(*(u8 *)((u8 *)arg0 + 0x7A)) << 0x3D) >> 0x3F) == 0) {
        return 0;
    }
    temp_4 = *(s16 *)((u8 *)arg0 + 0x7C);
    temp_17 = temp_4 / 8 + (s32)((temp_4 % 8) > 0);
    temp_2 = ArenaAllocAligned_370330((u8 *)arg0 + 0x6C, temp_17, *(s16 *)((u8 *)arg0 + 0x80), -1);
    *(s32 *)((u8 *)arg0 + 0x84) = temp_2;
    if (temp_2 == 0) {
        return 0;
    }
    memset((void *)(s32)temp_2, 0, temp_17);
    return 1;
}
