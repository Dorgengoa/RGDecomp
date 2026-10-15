#include "types.h"

typedef struct Obj_FUN_001e36b0 Obj_FUN_001e36b0;
typedef struct T_FUN_001e36b0 T_FUN_001e36b0;

extern T_FUN_001e36b0 *MapGetAreaSlot2_1e5740(Obj_FUN_001e36b0 *o);
extern s32 MapDataIsEnabled_1e7c20(T_FUN_001e36b0 *t);
extern s32 MapDataIsLoaded_1e79d0(T_FUN_001e36b0 *t);
extern void MapAreaGetNorthAngle_1dcb90(T_FUN_001e36b0 *t);
extern T_FUN_001e36b0 *MapGetActiveArea_1e56e0(Obj_FUN_001e36b0 *o);

void MapGetNorthAngle_1e36b0(Obj_FUN_001e36b0 *o)
{
    T_FUN_001e36b0 *t;

    t = MapGetAreaSlot2_1e5740(o);
    if (t != 0) {
        if (MapDataIsEnabled_1e7c20(t) != 0) {
            if (MapDataIsLoaded_1e79d0(t) != 0) {
                MapAreaGetNorthAngle_1dcb90(t);
                return;
            }
        }
    }
    MapAreaGetNorthAngle_1dcb90(MapGetActiveArea_1e56e0(o));
}
