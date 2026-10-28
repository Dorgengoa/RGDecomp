/* rgp:protos */
#define RGP_SELF_GroupViewCtor_425440 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
extern u8 D_00472250[];
extern u8 D_0047C450[];
extern u8 D_0047C5D0[];

void *GroupViewCtor_425440(void *arg0, void *arg1, s16 arg2, s32 arg3)
{
    *(void **)((u8 *)arg0 + 0x0) = D_00472250;
    *(void **)((u8 *)arg0 + 0x0) = D_0047C5D0;
    *(void **)((u8 *)arg0 + 0x0) = D_0047C450;
    if (arg1 != NULL) {
        *(s32 *)((u8 *)arg0 + 0x4) = *(s32 *)((u8 *)(*(void **)((u8 *)arg1 + 0x8)) + 0x74);
    } else {
        *(s32 *)((u8 *)arg0 + 0x4) = 0;
    }
    *(s16 *)((u8 *)arg0 + 0x8) = arg2;
    *(s32 *)((u8 *)arg0 + 0xC) = arg3;
    GroupViewCountEntries_425300(arg0);
    return arg0;
}
