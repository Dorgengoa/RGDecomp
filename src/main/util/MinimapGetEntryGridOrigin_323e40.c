#include "types.h"

s32 EntryGetTileSize_323ad0(s32);
void EntryGetOrigin_323b10(s32, f32 *, f32 *);
f32 EntryGetScale_323b30(s32);
void EntryGetGridSize_323bb0(s32, s32 *, s32 *);
s32 AngleToQuadrant_323fd0(s32);

void MinimapGetEntryGridOrigin_323e40(s32 arg0, s32 arg1, f32 *arg2, f32 *arg3) {
    f32 k;
    f32 nx;
    f32 ny;
    f32 x;
    f32 y;
    s32 n;
    s32 sp7C;
    s32 sp78;
    f32 sp74;
    f32 sp70;

    *arg2 = 0.0f;
    *arg3 = 0.0f;
    if (arg1 == 0) {
        return;
    }
    k = EntryGetScale_323b30(arg1);
    n = EntryGetTileSize_323ad0(arg1);
    EntryGetGridSize_323bb0(arg1, &sp7C, &sp78);
    EntryGetOrigin_323b10(arg1, &sp74, &sp70);
    nx = -sp74;
    ny = -sp70;
    { f32 kk = (f32)n * k;
    x = (f32)sp7C * kk;
    y = (f32)sp78 * kk; }
    switch (AngleToQuadrant_323fd0(arg0)) {
    case 1:
        *arg2 = -ny;
        *arg3 = -(x - nx);
        break;
    case 2:
        *arg2 = -(x - nx);
        *arg3 = -(y - ny);
        break;
    case 3:
        *arg2 = -(y - ny);
        *arg3 = -nx;
        break;
    case 0:
    default:
        *arg2 = sp74;
        *arg3 = sp70;
        break;
    }
}
