/* rgp:protos */
#define RGP_SELF_MinimapDrawTiles_328c50 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Attr {
    s8 a;
    u8 b;
    u8 c;
} Attr;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 MinimapDrawTiles_328c50(s8 *self, s8 *map, s32 arg2, s32 cols, s32 rows, s32 arg5, f32 ox, f32 oy) {
    s32 w;
    s32 h;
    Attr attr __attribute__((aligned(16)));
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
            cell = ((Attr *)EntryGridGetCellXY_3239b0(map, iu, iv));
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
