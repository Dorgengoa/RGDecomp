/* rgp:protos */
#define RGP_SELF_CharaDataSubRecAddLoad_1ee830 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

typedef struct {
    u8 pad0[0xa];
    u8 unkA;
    u8 padB[0x59];
    s32 unk64;
} T1ee830_arg0;

s32 CharaDataSubRecAddLoad_1ee830(T1ee830_arg0 *arg0, s32 arg1)
{
    s32 temp_2;
    s32 temp_4;
    u8 var_2;

    temp_2 = ((s32)MemStackNew_14e230(0x3C, (s32)((u8 *)arg0 + 0xC)));
    if (temp_2 != 0) {
        ListNodeInit_1efa20(temp_2);
        CharaDataNodeInit_1ef940(temp_2);
    }
    if (temp_2 == 0) {
        return 0;
    }
    temp_4 = arg0->unk64;
    if (temp_4 == 0) {
        arg0->unk64 = temp_2;
    } else {
        ListAppendTail_1ef9e0(temp_4, temp_2);
    }
    if (CharaDataNodeFromLoadInfo_1ef7b0(temp_2, arg1) != 0) {
        arg0->unkA = 2;
    } else {
        arg0->unkA = 4;
    }
    return arg0->unkA == 2;
    return 0;
}
