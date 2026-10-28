/* rgp:protos */
#define RGP_SELF_NavGraphsSyncAreaXform_30c980 1
#define RGP_SELF_get 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

typedef struct { u8 pad[0xc]; s32 *arr; u32 n; } L;

static inline s32 get(L *l, u32 i) {
    s32 r;
    if (l->arr != 0) {
        if (l->n <= i) r = 0;
        else r = l->arr[i];
    } else r = 0;
    return r;
}

void NavGraphsSyncAreaXform_30c980(L *arg0) {
    s32 sp70[4] __attribute__((aligned(16)));
    s32 sp60[4] __attribute__((aligned(16)));
    s32 h;
    u32 i;
    s32 obj;
    s32 t;

    h = ((s32)GetMapMgr_201a90());
    for (i = 0; (obj = get(arg0, i)) != 0; i++) {
        t = ((s32)MapFindAreaSlotById_1e4cb0(h, ((short)NavGraphGetAreaId_310e80(obj))));
        if (t != 0) {
            if (((unsigned char)MapDataIsLoaded_1e79d0(t)) != 0 && ((signed char)NavGraphHasXform_310e60(obj)) != 0) {
                MapDataGetPosVec4_1e7740(t, sp60);
                MapDataGetRotVec4_1e7720(t, sp70);
                NavGraphSetXform_310dc0(obj, sp70, sp60);
            }
        }
    }
}
