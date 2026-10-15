#include "types.h"

typedef struct Attr {
    s8 a;
    u8 b;
    u8 c;
} Attr;

void GetGameData_1fede0(void);
void EntryGetGridSize_323bb0(s8 *, s32 *, s32 *);
Attr *EntryGridGetCellXY_3239b0(s8 *, s32, s32);
s32 AngleToQuadrant_323fd0(s8 *);
s32 MinimapIsCellExploredXZ_3254f0(s8 *, s8 *, s32, f32, f32);
void MinimapDrawTile_328f10(s8 *, s8 *, s32, s32, Attr *, s32, s32);

s32 MinimapDrawTiles_328c50(s8 *self, s8 *map, s32 arg2, s32 cols, s32 rows, s32 arg5, f32 ox, f32 oy) {
    s32 w;
    s32 h;
    Attr attr;
    s32 y;
    s32 x;
    f32 fy;
    f32 u;
    f32 v;
    s32 iu;
    s32 iv;
    Attr *cell;

    if (map == NULL) {
        return 0;
    }
    GetGameData_1fede0();
    EntryGetGridSize_323bb0(map, &w, &h);
    for (y = 0; y < rows; y++) {
        fy = (f32)y + oy;
        for (x = 0; x < cols; x++) {
            switch (AngleToQuadrant_323fd0(self)) {
            case 1:
                u = (f32)(w - 1) - fy;
                v = (f32)x + ox;
                break;
            case 2:
                u = (f32)(w - 1) - ((f32)x + ox);
                v = (f32)(h - 1) - fy;
                break;
            case 3:
                u = fy;
                v = (f32)(h - 1) - ((f32)x + ox);
                break;
            default:
            case 0:
                u = (f32)x + ox;
                v = fy;
                break;
            }
            if (u < 0.0f || v < 0.0f) {
                continue;
            }
            iv = (s32)v;
            iu = (s32)u;
            cell = EntryGridGetCellXY_3239b0(map, iu, iv);
            if (cell == NULL) {
                continue;
            }
            attr.a = cell->a;
            attr.b = cell->b;
            attr.c = cell->c;
            attr.c += (u8)AngleToQuadrant_323fd0(self);
            if (attr.c >= 4) {
                attr.c -= 4;
            }
            if (MinimapIsCellExploredXZ_3254f0(self, map, 0, (f32)iu, (f32)iv) == 0) {
                continue;
            }
            MinimapDrawTile_328f10(self, map, arg2, arg5, &attr, x, y);
        }
    }
    return 1;
}
