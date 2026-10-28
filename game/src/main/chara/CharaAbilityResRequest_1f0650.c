/* rgp:protos */
#define RGP_SELF_CharaAbilityResRequest_1f0650 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Desc {
    s32 f0;
    s32 f4;
    s32 f8;
    s32 fC;
    s32 f10;
    s32 f14;
    s8 *f18;
    s32 f1C;
    s32 f20;
    s32 f24;
    s32 f28;
    s32 f2C;
    s32 f30;
    s32 f34;
} Desc;

extern s32 Sprintf_1343b8(s8 *, const s8 *, ...);
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern s8 D_0045B7B0[0x20];
extern s8 D_0045B7D0[0x20];

s32 CharaAbilityResRequest_1f0650(s32 arg0, s32 arg1, s32 arg2, s32 arg3)
{
    s8 buf[0x40] __attribute__((aligned(16)));
    Desc d __attribute__((aligned(16)));
    s32 mgr;
    s32 id;

    if (((unsigned char)IsPcCharaId_1f52d0(arg1)) == 0) {
        return 0;
    }
    mgr = ((s32)GetCharaDataMgr_1fdb70());
    id = PcDefGetCharaDataId_1f5060(arg1);
    d.f0 = -1;
    d.f4 = -1;
    d.f8 = -1;
    d.fC = -1;
    d.f10 = -1;
    d.f14 = -1;
    d.f1C = -1;
    d.f24 = -1;
    d.f30 = -1;
    d.f18 = 0;
    d.f20 = 0;
    d.f28 = 0;
    d.f2C = 0;
    d.f34 = 0;
    CharaAbilityDataReleaseSubRecs_1f0570(arg0, arg1);
    if (arg2 != 0) {
        d.f0 = id - 0x3D1;
        d.f4 = 1;
        d.f8 = 4;
        d.fC = 2;
        d.f1C = ((s32)PcIdToResIndexMaybe_1f4f90(arg1));
        d.f14 = PcDefGetCharaDataId_1f5060(arg1);
        d.f18 = buf;
        Sprintf_1343b8(buf, D_0045B7B0, arg1 - 0x2AF8, arg2);
        CharaDataLoadSubRecById_1eda70(mgr, &d);
    }
    if (arg3 != 0) {
        CharaDataReleaseSubRecsByKey_1ed750(((s32)GetCharaDataMgr_1fdb70()), id, 5);
        d.f0 = id;
        d.f14 = id;
        d.f4 = 0;
        d.f8 = 5;
        d.fC = 5;
        d.f24 = 7;
        d.f18 = buf;
        Sprintf_1343b8(buf, D_0045B7D0, arg3);
        CharaDataLoadSubRecById_1eda70(mgr, &d);
    }
    LoaderQueueAppendSeparator_1cd670(((s32)GetLoaderMgr_1f59d0()));
    return 1;
}
