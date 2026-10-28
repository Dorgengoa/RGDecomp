/* rgp:protos */
#define RGP_SELF_MapAreaLoadDef_1ea080 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma optimize_for_size on
#pragma divbyzerocheck on

typedef struct { u8 pad[0x828]; u8 on; u8 pad829[7]; } Obj42;
typedef struct { u32 w[42]; } Tbl21;
typedef struct { u32 w[10]; } Tbl5;
typedef struct { u32 w[8]; } Sub54;
typedef struct { u32 w[19]; } Sub74;
typedef struct {
    u8 pad0[0x2C];
    s32 flags;
    u8 pad30[0x54 - 0x30];
    Sub54 s54;
    Sub74 s74;
    s32 wC0;
    s32 wC4;
    s16 hC8;
    s16 hCA;
} Ent;
typedef struct { u8 pad0[4]; s16 *p4; u8 pad8[8]; s8 n; u8 pad11[5]; s16 h16; s16 h18; } Info;
typedef struct {
    u8 pad0[0x38];
    s16 h38;
    s16 h3A;
    s16 h3C;
    s16 h3E;
    s32 w40;
    Ent *p44;
    void *p48;
    s32 w4C;
} Map;
typedef struct { u8 pad0[2]; s16 n; void *p4; } Rec;
typedef struct { s16 id; s16 cnt; } Cnt;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern void Sprintf_1343b8(char *, char *, ...);
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
extern u32 D_0044B490[];
extern u32 D_0044B540[];
extern char D_0045B668[];
extern char D_0045B678[];
extern char D_0045B688[];
extern char D_0045B698[];
extern char D_0045B6A8[];
extern char D_0045B6C0[];
extern s32 D_004818F8;
extern void *D_004818FC;
extern s16 D_00481900;
extern s16 D_00481904;
extern s16 D_00481910;

s32 MapAreaLoadDef_1ea080(u8 *self)
{
    s32 n1;
    s32 n2;
    char name1[0x40] __attribute__((aligned(16)));
    char name2[0x40] __attribute__((aligned(16)));
    Tbl21 tbl __attribute__((aligned(16)));
    Obj42 obj __attribute__((aligned(16)));
    Tbl5 tbl2 __attribute__((aligned(16)));
    Obj42 obj2 __attribute__((aligned(16)));
    s32 grp[104] __attribute__((aligned(16)));
    s32 kind[104] __attribute__((aligned(16)));
    s32 perm[32] __attribute__((aligned(16)));
    char b300[0x20] __attribute__((aligned(16)));
    char b2E0[0x20] __attribute__((aligned(16)));
    char b2C0[0x20] __attribute__((aligned(16)));
    char b2A0[0x20] __attribute__((aligned(16)));
    Cnt cnt[128] __attribute__((aligned(16)));
    Rec *rec;
    void *d1;
    void *d2;
    Map *map;
    s32 used;
    u8 *w3;
    s32 i;
    s32 k;
    s32 pass;
    s32 j3;
    s32 prev;
    s32 nsw;
    s32 a;
    s32 b;
    s32 used2;
    s32 j;
    s32 *pk;
    s32 r;
    s32 lvl;
    Ent *src;
    Ent *e;
    Info *inf;
    u8 *q;
    s32 m;
    s32 t;
    s32 lo;
    void *arr;
    u8 *qa;
    u8 *qb;
    s32 xa;
    s32 xb;
    s32 xc;

    D_004818FC = 0;
    LoadHandlePollThunk_1ccb00(self + 0xA8);
    D_004818F8 = MapDataGetHeap_1e7850(self);
    if (D_004818F8 == 0) {
        return -1;
    }
    rec = ((Rec *)MapAreaLoadHandleAt_1dd120(self + 0xA8, 0));
    if (rec == 0) {
        return -1;
    }
    if (rec->n == 0) {
        return 0;
    }
    Sprintf_1343b8(name1, D_0045B668, MapDataGetFileName_1e7be0(self));
    Sprintf_1343b8(name2, D_0045B678, MapDataGetFileName_1e7be0(self));
    d1 = ArchiveGetFileByPath_1c2800(rec->p4, name1, &n1);
    d2 = ArchiveGetFileByPath_1c2800(rec->p4, name2, &n2);
    map = ((Map *)MapAreaDefGetRecTable_1dcf20(self));
    map->w40 = 0;
    map->h38 = 0;
    map->p44 = 0;
    map->h3A = 0;
    map->p48 = 0;
    map->h3C = 0;
    map->w4C = 0;
    map->h3E = 0;
    D_004818FC = self;
    D_00481900 = 0;
    D_00481904 = 0;
    D_00481910 = 0;
    tbl = *(Tbl21 *)D_0044B490;
    CfgVmReset_42fc10(&obj);
    obj.on = 1;
    CfgVmRegisterCmds_42fb00(&obj, &tbl);
    CfgVmLoad_42fac0(&obj, d1, n1);
    CfgVmRun_42fa20(&obj);
    MapDataSetParentId_1e7480(self, ((short)MapDataGetId_1e7bd0(self)));
    map->h38 = D_00481900;
    map->h3A = D_00481904;
    map->h3E = D_00481910;
    if (d2 != 0 && n2 > 0) {
        tbl2 = *(Tbl5 *)D_0044B540;
        CfgVmReset_42fc10(&obj2);
        obj2.on = 1;
        CfgVmRegisterCmds_42fb00(&obj2, &tbl2);
        CfgVmLoad_42fac0(&obj2, d2, n2);
        CfgVmRun_42fa20(&obj2);
    }
    if (*(s32 *)(self + 0x2C) & 1) {
        used = 0;
        if (RandomLayoutLoad_1fef50(grp, kind) == 0) {
            for (i = 0; i <= 100; i++) {
                grp[i] = -1;
                kind[i] = -1;
                switch (i % 10) {
                case 9:
                    kind[i] = 3;
                    break;
                case 0:
                    kind[i] = 2;
                    break;
                }
            }
            k = 0;
            prev = -1;
            for (pass = 0; pass < 3; pass++) {
                i = 0;
                do {
                    t = i + 1;
                    perm[i] = t;
                    i = t;
                } while (i < 30);
                m = ((short)MapAreaGetShuffleCount_1dcdc0(self));
                nsw = 0;
                while (nsw < m) {
                    a = Rand_133710() % 30;
                    b = Rand_133710() % 30;
                    if (a == b) {
                        continue;
                    }
                    if (a == 0 && perm[b] == prev) {
                        continue;
                    }
                    t = perm[a];
                    perm[a] = perm[b];
                    perm[b] = t;
                    nsw++;
                }
                for (j = 0; j < 30; ) {
                    if (k % 10 != 0) {
                        grp[k] = perm[j];
                        j++;
                    }
                    k++;
                }
                prev = perm[29];
            }
            prev = -1;
            for (i = 0; i < 100; i++) {
                pk = &kind[i];
                if (*pk < 0) {
                    do {
                        r = Rand_133710() % 4 + 1;
                    } while (r == prev || r == pk[1]);
                    *pk = r;
                }
                prev = *pk;
            }
            RandomLayoutSave_1ff030(grp, kind);
        }
        for (i = 0; i < 100; i++) {
            pk = &grp[i];
            if (*pk < 0) {
                continue;
            }
            lvl = (i + 32) / 33;
            Sprintf_1343b8(b300, D_0045B688, *pk);
            src = ((Ent *)MapRecTableFindBlockByName_1dd270(map, b300));
            if (src == 0) {
                continue;
            }
            Sprintf_1343b8(b2E0, D_0045B698, i);
            e = &(map->p44 + D_00481904)[used];
            MapDataCopy_1eac90(e, src);
            e->s54 = src->s54;
            e->s74 = src->s74;
            e->wC0 = src->wC0;
            e->wC4 = src->wC4;
            e->hC8 = src->hC8;
            e->hCA = src->hCA;
            MapDataSetId_1e74e0(e, i + 20000);
            MapDataSetName_1e7500(e, ((s32)MemStackStrDup_14cff0(b2E0, D_004818F8)));
            MapDataClearAttrFlags_1e7b20(e, 0x20);
            e->flags &= ~1;
            inf = ((Info *)MapBlockGetInfo_1e00b0(e));
            inf->h16 = lvl + 8000;
            inf->p4 = 0;
            inf->n = 0;
            inf->h18 = (lvl - 1) * 30 + grp[i];
            inf->h18 += (inf->h18 - 1) / 9 + 1000;
            used++;
        }
        for (i = 0; i < 100; i++) {
            pk = &kind[i];
            if (*pk < 0) {
                continue;
            }
            lvl = i / 33;
            if (lvl > 2) {
                lvl = 2;
            }
            Sprintf_1343b8(b2C0, D_0045B6A8, *pk);
            src = ((Ent *)MapRecTableFindBlockByName_1dd270(map, b2C0));
            if (src == 0) {
                continue;
            }
            Sprintf_1343b8(b2A0, D_0045B6C0, lvl + 0x61, *pk, i - lvl * 33 + 1);
            MapRecTableFindBlockByName_1dd270(map, b2A0);
            e = &(map->p44 + D_00481904)[used];
            MapDataCopy_1eac90(e, src);
            e->s54 = src->s54;
            e->s74 = src->s74;
            e->wC0 = src->wC0;
            e->wC4 = src->wC4;
            e->hC8 = src->hC8;
            e->hCA = src->hCA;
            MapDataSetId_1e74e0(e, i + 21000);
            MapDataSetName_1e7500(e, ((s32)MemStackStrDup_14cff0(b2A0, D_004818F8)));
            MapDataClearAttrFlags_1e7b20(e, 0x20);
            e->flags &= ~1;
            inf = ((Info *)MapBlockGetInfo_1e00b0(e));
            inf->h16 = -1;
            used++;
            inf->p4 = 0;
            inf->n = 0;
        }
        D_00481904 += (s16)used;
        map->h3A = D_00481904;
        for (i = 0; i <= 100; i++) {
            e = ((Ent *)MapRecTableFindBlockById_1dd410(map, i + 20000));
            if (e == 0) {
                continue;
            }
            e->flags |= 0x100;
            inf = ((Info *)MapBlockGetInfo_1e00b0(e));
            inf->p4 = MemStackNew_14e1b0(8, D_004818F8);
            if (inf->p4 == 0) {
                continue;
            }
            for (j = 0; j < 2; j++) {
                e = ((Ent *)MapRecTableFindBlockById_1dd410(map, i + 20999 + j));
                if (e == 0) {
                    continue;
                }
                inf->p4[inf->n] = ((short)MapDataGetId_1e7bd0(e));
                inf->n++;
            }
        }
    }
    map->h38 = D_00481900;
    map->h3A = D_00481904;
    map->h3E = D_00481910;
    D_00481900 = 0;
    D_00481904 = 0;
    D_00481910 = 0;
    q = ((u8 *)MapAreaGetShares_1dce60(self));
    if (q != 0) {
        i = MapAreaGetShareCount_1dce50(self);
        MapIdIndexInit_1ddda0(self + 0xFC, i, D_004818F8);
        for (a = 0; a < i; a++, q += 0x58) {
            MapDataSetParentId_1e7480(q, ((short)MapDataGetId_1e7bd0(self)));
            MapIdIndexInsertSorted_1ddc00(self + 0xFC, q, a);
        }
    }
    used2 = 0;
    for (i = 0; i < 128; i++) {
        cnt[i].id = -1;
        cnt[i].cnt = 0;
    }
    qa = ((u8 *)MapAreaGetBlocks_1dce30(self));
    if (qa != 0) {
        b = MapAreaGetBlockCount_1dce20(self);
        MapIdIndexInit_1ddda0(self + 0x10C, b, D_004818F8);
        for (xa = 0; xa < b; xa++, qa += 0xCC) {
            MapDataSetParentId_1e7480(qa, ((short)MapDataGetId_1e7bd0(self)));
            MapIdIndexInsertSorted_1ddc00(self + 0x10C, qa, xa);
            for (j = 0; j < used2; j++) {
                if (cnt[j].id == ((short)MapBlockGetLocationId_1e0070(qa))) {
                    break;
                }
            }
            cnt[j].cnt++;
            if (j >= used2) {
                cnt[j].id = ((short)MapBlockGetLocationId_1e0070(qa));
                used2++;
            }
        }
    }
    arr = ConstructNewArray_100710(MemStackNew_14e1b0(used2 * 60 + 16, D_004818F8), 0, 0, 60, used2);
    map->p48 = arr;
    if (arr != 0) {
        w3 = arr;
        for (j3 = 0; j3 < used2; j3++, w3 += 60) {
            if (MapPartTableInit_1de4e0(w3, cnt[j3].id, cnt[j3].cnt, D_004818F8) == 0) {
                continue;
            }
            {
                u8 *s = ((u8 *)MapAreaGetBlocks_1dce30(self));
                s32 ns = MapAreaGetBlockCount_1dce20(self);
                for (b = 0; b < ns; b++, s += 0xCC) {
                    t = ((short)MapBlockGetLocationId_1e0070(s));
                    if (t != ((short)MapPartTableGetId_1de200(w3))) {
                        continue;
                    }
                    MapPartTableAddUnique_1de460(w3, s);
                }
            }
        }
        map->h3C = used2;
    }
    qa = ((u8 *)MapAreaGetBoxes_1dcde0(self));
    if (qa != 0) {
        b = MapAreaGetBoxCount_1dcdd0(self);
        for (xa = 0; xa < b; xa++, qa += 0x50) {
            lo = *(s16 *)(self + 0x11C);
            if (((short)MapBoxGetNumMaybe_1ddf00(qa)) < lo) {
                *(s16 *)(self + 0x11C) = ((short)MapBoxGetNumMaybe_1ddf00(qa));
            }
            lo = *(s16 *)(self + 0x11E);
            if (lo < ((short)MapBoxGetNumMaybe_1ddf00(qa))) {
                *(s16 *)(self + 0x11E) = ((short)MapBoxGetNumMaybe_1ddf00(qa));
            }
        }
    }
    if (((short)MapDataGetId_1e7bd0(self)) == 0x6A4 && (*(s32 *)(self + 0x2C) & 0x200)) {
        MemStackNew_14e1b0(0x4000, D_004818F8);
    }
    D_004818FC = 0;
    D_00481900 = 0;
    D_00481904 = 0;
    D_00481910 = 0;
    MapAreaRefreshBlocksEnabled_1da5a0(self);
    return 2;
}
