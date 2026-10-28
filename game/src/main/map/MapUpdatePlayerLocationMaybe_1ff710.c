/* rgp:protos */
#define RGP_SELF_MapUpdatePlayerLocationMaybe_1ff710 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Elem {
    u8 b[16];
} Elem;

typedef struct Info {
    u8 pad00[0x30];
    s16 x30;
    u8 pad32[0x18E - 0x32];
    s16 x18E;
} Info;

typedef struct Game {
    u8 pad00[0x18];
    Info *info;
} Game;

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
extern s32 D_00481B00;

void MapUpdatePlayerLocationMaybe_1ff710(Elem *arg0, s32 arg1) {
    s32 a;
    s32 b;
    s32 c;
    s32 list[20] __attribute__((aligned(16)));
    s32 ids[20] __attribute__((aligned(16)));
    s32 kinds[20] __attribute__((aligned(16)));
    Game *game;
    s32 va;
    s32 vd;
    s32 vb;
    s32 nids;
    s32 n;
    s32 nkinds;
    s32 h;
    s32 i;
    s32 vc;
    s32 id;
    s32 j;
    s32 cur;
    s32 ctx;
    s32 *p;
    s32 ve;
    s64 vf;
    u8 vg;

    game = ((Game *)GetGameData_1fede0());
    ctx = ((s32)GetMapMgr_201a90());
    h = GetCurrentScene_1f5be0();
    if (((unsigned char)ObjRecHasFlags6_1c3eb0(h, 1, game->info->x18E)) == 0) {
        return;
    }
    if (((s32)ObjRecGetLiveObject_1c4a90(h, game->info->x18E)) == 0) {
        return;
    }
    va = -1;
    vg = 0;
    vd = va;
    vb = va;
    vc = va;
    ve = va;
    vf = va;
    MapLocateAtPos_1e3a60(ctx, &a, &b, &c, arg0 + PartyGetLeaderIndex_3c2850(game->info), 0.0f);
    if (a != 0) {
        va = ((short)MapDataGetId_1e7bd0(a));
    }
    if (b != 0) {
        vd = ((short)MapDataGetId_1e7bd0(b));
        vb = ((short)MapBlockGetLocationId_1e0070(b));
        vc = MapBlockGetNavGraphId_1e0050(b);
        vf = MapBlockGetPlaceNameMsgId_1e0060(b);
        vg = MapDataIsJasterOnly_1e7a90(b);
    }
    if (c != 0) {
        ve = ((short)MapBoxGetNumMaybe_1ddf00(c));
    }
    PartySetLocationMaybe_3c9cd0(game->info, va, vb, vc, vd, ve, arg0, arg1, vg, (int)(vf), (unsigned char)(0));
    n = MapCollectActiveBlocks_1e3e70(ctx, list, 20);
    nids = 0;
    nkinds = 0;
    for (i = 0; i < n; i++) {
        p = &list[i];
        for (j = 0; j < nids; j++) {
            cur = ids[j];
            if (cur == ((short)MapBlockGetLocationId_1e0070(*p))) {
                break;
            }
        }
        if (j >= nids) {
            ids[nids++] = ((short)MapBlockGetLocationId_1e0070(*p));
        }
        for (j = 0; j < nkinds; j++) {
            cur = kinds[j];
            if (cur == MapBlockGetNavGraphId_1e0050(*p)) {
                break;
            }
        }
        if (j >= nkinds) {
            kinds[nkinds++] = MapBlockGetNavGraphId_1e0050(*p);
        }
    }
    GameDataZoneEntriesUpdateMaybe_3ec4b0(game, nids, ids);
    GameDataAreaEntriesUpdateMaybe_3ec470(game, nkinds, kinds);
    id = game->info->x30;
    if (id == 0x55F0) {
        id = 0x4E20;
    }
    if (id == 0x55F1) {
        id = 0x4E20;
    }
    if (D_00481B00 != id && GetGameMode_1f59c0() == 6) {
        if (id >= 0x4E20 && id < 0x4E85) {
            MapMgrCaptionLoad_1e2f10(ctx, id - 0x3264, 1);
        }
        D_00481B00 = id;
    }
}
