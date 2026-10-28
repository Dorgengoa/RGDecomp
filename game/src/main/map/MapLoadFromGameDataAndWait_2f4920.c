/* rgp:protos */
#define RGP_SELF_MapLoadFromGameDataAndWait_2f4920 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Info {
    u8 pad0[4];
    s16 f4;
    s16 f6;
    s16 f8;
} Info;

typedef struct Self {
    u8 pad0[8];
    s32 f8;
    u8 padc[0xC];
    Info *f18;
} Self;

typedef struct Found {
    u8 pad0[0xC];
    s32 fC;
    s16 f10;
    s16 f12;
} Found;

extern void DelayThread_117618(s32);
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void MapLoadFromGameDataAndWait_2f4920(void)
{
    Self *self;
    s32 h;
    Found *f;
    s32 a;
    s32 b;
    s32 c;
    s32 timer;

    self = ((Self *)GetGameData_1fede0());
    h = ((s32)GetMapMgr_201a90());
    f = ((Found *)PlanetAreaMatrixLookupByProgress_3ed840(self, self->f18->f4));
    b = -1;
    a = 0;
    c = b;
    if (f != NULL) {
        a = f->fC;
        b = f->f10;
        c = f->f12;
    }
    MapSetSlot0AreaId_1e4140(h, self->f18->f6);
    MapSetSlot1AreaId_1e4130(h, EvtInfoGetIdMaybe_3ed810(self));
    MapLocSetNameMaybe_1e4070(h, a, b, c);
    MapSetSkyId_1e41b0(h, self->f18->f8);
    timer = ((s32)GetLoaderMgr_1f59d0());
    for (;;) {
        LoaderTickGlobal_2f74c0();
        TaskLoadMap_201200();
        EffectMgrLoadPollGlobal_2d8880();
        if (((unsigned char)MapLoadIsSettledMaybe_1e4e10(h, 0)) != 0) break;
        DelayThread_117618(10);
    }
    for (;;) {
        LoaderTickGlobal_2f74c0();
        GameDataRefreshWorldFwd_1fec10();
        if (WorldDataMgrNoRequestPending_3eef10(self->f8) != 0) break;
        DelayThread_117618(10);
    }
    SysGetModeMsg_1c39b0();
    TaskUpdateMapInfo_201340();
    PartyLeaderRebuildBlockIdList_2012e0();
    GameDataTick_1febd0();
    for (;;) {
        LoaderTickGlobal_2f74c0();
        TaskLoadMap_201200();
        EffectMgrLoadPollGlobal_2d8880();
        if (LoaderCountQueued_1cd620(timer) <= 0 && ((unsigned char)MapLoadIsSettledMaybe_1e4e10(h, 0)) != 0) break;
        DelayThread_117618(10);
    }
    TaskUpdateMapInfo_201340();
    for (;;) {
        LoaderTickGlobal_2f74c0();
        GameDataRefreshWorldFwd_1fec10();
        if (LoaderCountQueued_1cd620(timer) <= 0) break;
        DelayThread_117618(10);
    }
}
