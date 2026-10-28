/* rgp:protos */
#define RGP_SELF_MapDataUnload_1e6690 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    s32 x0;
    s32 x4;
    s32 x8;
    s32 pad[8];
    s32 flags;
} Obj;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 MapDataUnload_1e6690(Obj *arg0, s32 arg1)
{
    s32 f;

    arg0->flags |= 0x40;
    switch (((signed char)MapDataGetState_1e7a00(arg0))) {
    case 0:
    case -1:
        arg0->flags &= ~0x40;
        return 0;
    case 1:
        break;
    case 2:
        if (arg1 == 0 && (arg0->flags & 2)) {
            return 0;
        }
        EventNotifyAreaUnload_1ffa30(((short)MapDataGetId_1e7bd0(arg0)));
        MapDataSetState_1e72c0(arg0, 3);
    case 3:
        if (arg1 == 0) {
            f = arg0->flags;
            if (f & 2) {
                MapDataSetState_1e72c0(arg0, 2);
                return 0;
            }
            if (f & 4) {
                return 0;
            }
        }
        break;
    }
    if (arg0->x8 != 0) {
        DrawCtxVif1HandlerStop_15dc40();
        MapAreaDataRelease_1e8ef0(arg0->x8);
    }
    if (arg0->x4 != 0 && arg0->x0 != 0) {
        MemStackHeapFree_14dcb0(arg0->x4, arg0->x0);
    }
    MapDataClearLoadState_1e7c30(arg0);
    return 1;
}
