/* rgp:protos */
#define RGP_SELF_MinimapWorldPosToGrid_32c0f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct V3 {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} V3;

typedef struct Game {
    u8 pad[0x510];
    void *p510;
    void *p514;
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

void MinimapWorldPosToGrid_32c0f0(f32 *out, f32 *in, void *a2, void *a3)
{
    Game *g;
    void *obj;
    void *chr;
    f32 scale;
    s32 n;
    f32 x;
    f32 y;
    s32 u;
    s32 w;
    V3 v __attribute__((aligned(16)));
    void *m;
    void *e;
    s32 i;

    g = ((Game *)GetMinimapMgr_201a70());
    if (g == 0) {
        return;
    }
    obj = g->p514;
    if (obj == 0) {
        obj = g->p510;
    }
    if (a2 != 0) {
        obj = a2;
    }
    if (obj == 0) {
        return;
    }
    chr = MinimapGetPendingOrCurEntry_32a8f0(obj);
    if (chr == 0) {
        chr = MinimapGetCurOrPendingEntry_32a920(obj);
    }
    if (a3 != 0) {
        chr = a3;
    }
    if (chr == 0) {
        return;
    }
    GetGameData_1fede0();
    scale = EntryGetScale_323b30(chr);
    n = EntryGetTileSize_323ad0(chr);
    MinimapGetEntryGridOrigin_323e40(obj, chr, &x, &y);
    EntryGetGridSize_323bb0(chr, &u, &w);
    m = GetMapMgr_201a90();
    if (m != 0) {
        e = MapSlotsFindBlockByName_1e4910(m, (u8 *)chr + 0x34, 0);
        if (e != 0) {
            MapDataGetPosVec4_1e7740(e, &v);
        }
    }
    x += v.x;
    y += v.z;
    for (i = 0; i < 3; i++) {
        out[i] = in[i];
    }
    MinimapWorldToMapXZ_32c280(out, scale, x, y, (f32)n);
}
