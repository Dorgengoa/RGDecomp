#pragma opt_propagation off
#include "types.h"

struct V4 {
    f32 x, y, z, w;
};

struct Obj {
    u8 pad[0x2C];
    u32 flags;

    void SetFlag(u32 m, bool on) {
        if (on) {
            flags |= m;
        } else {
            flags &= ~m;
        }
    }
    void ClrFlag(u32 m) {
        flags &= ~m;
    }
};

extern "C" {
u8 MapAreaLoadUpdate_1d9300(Obj *);
u8 MapAreaRelease_1d9ee0(Obj *, s32);
void MapAreaRebuildActiveLists_1dc580(Obj *);
s32 MapAreaGetBlockCount_1dce20(Obj *);
u8 *MapAreaGetBlocks_1dce30(Obj *);
s32 MapAreaGetShareCount_1dce50(Obj *);
u8 *MapAreaGetShares_1dce60(Obj *);
u8 MapBlockStreamUpdate_1dece0(u8 *, V4 *, f32);
void MapDataGetRotVec4_1e7720(Obj *, V4 *);
void MapDataGetPosVec4_1e7740(Obj *, V4 *);
s32 MapDataGetState_1e7a00(Obj *);
s32 MapDataIsEnabled_1e7c20(Obj *);
u8 MapShareStreamUpdate_1ecc20(u8 *, V4 *, f32);
}

extern "C" bool MapAreaTick_1d9a20(Obj *o)
{
    bool res;
    V4 a;
    V4 b;
    u8 *e;
    s32 n;
    s32 i;
    u32 f;
    bool on;

    f = o->flags;
    on = (f & 0x40) != 0;
    res = false;
    if (on) {
        f |= 0x80;
    } else {
        f &= ~0x80;
    }
    o->flags = f;
    o->flags = f = f & ~2;
    o->flags = f = f & ~4;
    o->flags = f & ~0x40;
    if (MapDataIsEnabled_1e7c20(o) == 0) {
        switch (MapDataGetState_1e7a00(o)) {
        case 1:
        case 2:
        case 3:
            res = MapAreaRelease_1d9ee0(o, 1) != 0;
            break;
        }
    } else {
        switch (MapDataGetState_1e7a00(o)) {
        case 1:
            res = MapAreaLoadUpdate_1d9300(o) != 0;
            break;
        case 2:
        case 3:
            MapDataGetRotVec4_1e7720(o, &a);
            MapDataGetPosVec4_1e7740(o, &b);
            e = MapAreaGetShares_1dce60(o);
            n = MapAreaGetShareCount_1dce50(o);
            for (i = 0; i < n; i++, e += 0x58) {
                res |= MapShareStreamUpdate_1ecc20(e, &b, a.y);
            }
            e = MapAreaGetBlocks_1dce30(o);
            n = MapAreaGetBlockCount_1dce20(o);
            for (i = 0; i < n; i++, e += 0xCC) {
                res |= MapBlockStreamUpdate_1dece0(e, &b, a.y);
            }
            break;
        }
    }
    MapAreaRebuildActiveLists_1dc580(o);
    return res;
}
