/* rgp:protos */
#define RGP_SELF_MapAreaPlace_1da680 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Rng {
    f32 x120;
    f32 x124;
} Rng;

typedef struct Obj {
    u8 pad0[8];
    s32 x8;
    u8 padC[0x120 - 0xC];
    Rng r;
} Obj;

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
extern Rng D_0047D1EC;
#define D_rng D_0047D1EC

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

void MapAreaPlace_1da680(Obj *arg0, void *arg1, f32 arg2) {
    f32 spF0[4][4] __attribute__((aligned(16)));
    f32 spE0[4] __attribute__((aligned(16)));
    f32 spD0[4] __attribute__((aligned(16)));
    f32 sp90[4][4] __attribute__((aligned(16)));
    f32 sp80[4] __attribute__((aligned(16)));
    f32 sp70[4] __attribute__((aligned(16)));
    void *t;
    f32 lo;
    f32 hi;
    u8 *e;
    s32 n;
    s32 i;
    u8 *p;
    s32 m;
    s32 j;
    u8 *q;
    s32 k;
    s32 i2;
    void *o;

    if (arg0->x8 == 0) {
        return;
    }
    t = MinimapFindForArea_1dcb50(arg0);
    if (t != NULL) {
        MinimapSetOrigin_323fb0(t, arg1);
        MinimapSetAngle_324160(t, arg2);
    }
    MapDataSetPos_1e7420(arg0, arg1);
    MapDataSetRotY_1e7400(arg0, arg2);
    MapDataPlaceModel_1e6dd0(arg0, arg1, arg2);
    arg0->r = D_rng;
    e = ((u8 *)MapAreaGetBlocks_1dce30(arg0));
    if (e != NULL) {
        MatRotY_1cb200(spF0, arg2);
        VecCopy_1cbe30(spF0[3], arg1);
        n = MapAreaGetBlockCount_1dce20(arg0);
        for (i = 0; i < n; i++, e += 0xCC) {
            MapDataGetOffsetPosVec4_1e76e0(e, spE0);
            MapDataGetOffsetRotVec4_1e76c0(e, spD0);
            MatFromRotPos_1caf90(sp90, spD0, spE0);
            MatMul_1cb700(sp90, spF0, sp90);
            MatToRotPos_1cade0(spD0, spE0, sp90);
            MapDataSetPos_1e7420(e, spE0);
            MapDataSetRotY_1e7400(e, spD0[1]);
            MapDataPlaceModelThunk_1e6dd0(e, arg1, arg2);
            MapBlockBoxesPlace_1df7b0(e, arg1, arg2);
            arg0->r.x120 = MIN(arg0->r.x120, MapBlockGetBoxBottomY_1dfe60(e));
            arg0->r.x124 = MAX(arg0->r.x124, MapBlockGetBoxTopY_1dfe70(e));
        }
    }
    p = ((u8 *)MapAreaGetPartTables_1dce00(arg0));
    m = MapAreaGetPartTableCount_1dcdf0(arg0);
    for (j = 0; j < m; j++, p += 0x3C) {
        MapPartTableCalcBounds_1de210(p);
    }
    q = ((u8 *)MapAreaGetBoxes_1dcde0(arg0));
    if (q != NULL) {
        k = MapAreaGetBoxCount_1dcdd0(arg0);
        for (i2 = 0; i2 < k; i2++, q += 0x50) {
            o = MapAreaFindBlockById_1dc760(arg0, ((short)MapBoxGetBlockId_1ddef0(q)));
            if (o != NULL) {
                MapDataGetPosVec4_1e7740(o, sp80);
                MapDataGetRotVec4_1e7720(o, sp70);
            } else {
                MapDataGetPosVec4_1e7740(arg0, sp80);
                MapDataGetRotVec4_1e7720(arg0, sp70);
            }
            AreaBoxPlace_1e94a0(q, sp80, sp70[1]);
        }
    }
}
