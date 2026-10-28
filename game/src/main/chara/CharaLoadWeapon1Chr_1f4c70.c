/* rgp:protos */
#define RGP_SELF_CharaLoadWeapon1Chr_1f4c70 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern void Sprintf_1343b8(void *, const void *, s32);
/*rgp*/

extern u8 D_0045B870[];

typedef struct {
    s32 unk00;
    s32 unk04;
    s32 unk08;
    s32 unk0C;
    s32 unk10;
    s32 unk14;
    void *unk18;
    s32 unk1C;
    s32 unk20;
    s32 unk24;
    s32 unk28;
    s32 unk2C;
    s32 unk30;
    s32 unk34;
} DvArgs;

int CharaLoadWeapon1Chr_1f4c70(s32 arg0, s32 arg1, s32 arg2, s16 *arg3)
{
    u8 buf[0x20] __attribute__((aligned(16)));
    DvArgs a __attribute__((aligned(16)));
    s32 h;

    h = ((s32)GetCharaDataMgr_1fdb70());
    a.unk18 = 0;
    a.unk08 = 2;
    a.unk20 = 0;
    a.unk0C = -1;
    a.unk10 = -1;
    a.unk14 = -1;
    a.unk1C = -1;
    a.unk24 = -1;
    a.unk30 = -1;
    a.unk28 = 0;
    a.unk2C = 0;
    a.unk34 = 0;
    a.unk00 = arg1;
    a.unk04 = 0;
    a.unk10 = *arg3;
    a.unk18 = buf;
    if (arg2 == 0) {
        a.unk0C = 0;
        a.unk1C = PcIdToWeaponResIndexMaybe_1f4f70(arg0, 0);
    } else if (arg2 == 1) {
        a.unk0C = 1;
        a.unk1C = ((s32)PcIdToResIndexMaybe_1f4f90(arg0));
        a.unk14 = arg1;
    }
    Sprintf_1343b8(buf, D_0045B870, ((s32)CharaPcResNameBuildMaybe_40dc60(arg3)));
    if (arg0 == 0x2AFC) {
        a.unk28 = 1;
    }
    if (arg0 == 0x2B00) {
        a.unk28 = 1;
    }
    return CharaDataLoadSubRecById_1eda70(h, &a);
}
