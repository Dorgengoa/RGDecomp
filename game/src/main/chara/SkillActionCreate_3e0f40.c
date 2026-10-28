/* rgp:protos */
#define RGP_SELF_SkillActionCreate_3e0f40 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    u8 pad0[0x84];
    s32 unk84;
} Obj00483994;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern Obj00483994 *D_00483994;
extern u8 D_004839A0;
extern u8 D_004839A4;
extern u8 D_004839A8;
extern u8 D_004E9770[];

void *SkillActionCreate_3e0f40(s64 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4)
{
    s32 temp_2;
    s32 temp_2_2;
    s32 temp_2_3;
    u8 *temp_16;

    if (D_00483994 == NULL) {
        return NULL;
    }
    if ((arg3 == 0) && (D_004839A0 == 0)) {
        return NULL;
    }
    if (((arg3 == 0) && (D_004839A4 != 0))) return NULL;
    if (((arg3 == 0) && (D_004839A8 != 0))) return NULL;
    temp_2 = GetGameMode_1f59c0();
    if ((arg3 == 0) && (arg4 == 0) && (temp_2 != 7) && (temp_2 != 0x12) && (temp_2 != 0x11) && (temp_2 != 6)) {
        return NULL;
    }
    temp_2_2 = SkillActionFindFreeSlot_3e10b0();
    if (temp_2_2 < 0) {
        return NULL;
    }
    temp_2_3 = SkillDefFindMaybe_40ea70(D_00483994->unk84, (short)((s16)arg0), arg1);
    if (temp_2_3 == 0) {
        return NULL;
    }
    temp_16 = D_004E9770 + (temp_2_2 * 0x48);
    SkillActionInitFromDef_3e3d50(temp_16, arg2, temp_2_3);
    return temp_16;
}
