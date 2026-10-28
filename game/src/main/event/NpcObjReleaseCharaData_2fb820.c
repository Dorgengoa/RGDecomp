/* rgp:protos */
#define RGP_SELF_NpcObjReleaseCharaData_2fb820 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    u16 unk0;
    u8 pad2[0xC8 - 2];
    s16 unkC8;
} Obj002FB820;

/*rgp*/
/*rgp*/
/*rgp*/

void NpcObjReleaseCharaData_2fb820(Obj002FB820 *arg0) {
    s16 temp_4;
    s32 temp_2;

    if (arg0->unk0 & 4) {
        temp_4 = arg0->unkC8;
        if (temp_4 != -1) {
            temp_2 = ((s32)GetCharaResMgr_1fdb60());
            if (((short)CharaDataGetRefCount_1f0480(temp_2, arg0->unkC8)) <= 0) {
                CharaResReleaseCharaDataWithTexIds_1f0fb0(temp_2, arg0->unkC8);
                arg0->unkC8 = -1;
            }
            arg0->unk0 = (u16)(arg0->unk0 & 0xFFFB);
        }
    }
}
