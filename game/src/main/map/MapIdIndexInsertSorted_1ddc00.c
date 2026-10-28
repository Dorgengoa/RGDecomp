/* rgp:protos */
#define RGP_SELF_MapIdIndexInsertSorted_1ddc00 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
extern s32 strcmp(s32, s32);

typedef struct S001ddc00 {
    s32 *a;
    s32 *b;
    s16 hi;
    s16 lo;
} S001ddc00;

void MapIdIndexInsertSorted_1ddc00(S001ddc00 *arg0, s32 arg1, s32 arg2)
{
    s32 i;
    s32 j;
    s32 t;

    if (arg0->a != 0) {
        for (i = 0; i < arg2; i++) {
            if (((short)MapDataGetId_1e7bd0(arg0->a[i])) < 0) {
                i = arg2;
                break;
            }
            if (((short)MapDataGetId_1e7bd0(arg0->a[i])) > ((short)MapDataGetId_1e7bd0(arg1))) {
                break;
            }
        }
        if (arg0->lo > ((short)MapDataGetId_1e7bd0(arg1))) {
            arg0->lo = ((short)MapDataGetId_1e7bd0(arg1));
        }
        if (arg0->hi < ((short)MapDataGetId_1e7bd0(arg1))) {
            arg0->hi = ((short)MapDataGetId_1e7bd0(arg1));
        }
        S32ArrayInsertAt_1dde90(arg0->a, arg2, arg1, i);
    }
    if (arg0->b != 0) {
        for (j = 0; j < arg2; j++) {
            if (MapDataGetName_1e7bf0(arg0->b[j]) == 0) {
                j = arg2;
                break;
            }
            if (strcmp(MapDataGetName_1e7bf0(arg1), MapDataGetName_1e7bf0(arg0->b[j])) < 0) {
                break;
            }
        }
        S32ArrayInsertAt_1dde90(arg0->b, arg2, arg1, j);
    }
}
