/* rgp:protos */
#define RGP_SELF_MapGetNorthAngle_1e36b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Obj_FUN_001e36b0 Obj_FUN_001e36b0;
typedef struct T_FUN_001e36b0 T_FUN_001e36b0;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

float MapGetNorthAngle_1e36b0(Obj_FUN_001e36b0 *o)
{ float rgp_v0 = 0;
    T_FUN_001e36b0 *t;

    t = ((T_FUN_001e36b0 *)MapGetAreaSlot2_1e5740(o));
    if (t != 0) {
        if (((unsigned char)MapDataIsEnabled_1e7c20(t)) != 0) {
            if (((unsigned char)MapDataIsLoaded_1e79d0(t)) != 0) {
                (rgp_v0 = MapAreaGetNorthAngle_1dcb90(t));
                return rgp_v0;
            }
        }
    }
    (rgp_v0 = MapAreaGetNorthAngle_1dcb90(((T_FUN_001e36b0 *)MapGetActiveArea_1e56e0(o))));
return rgp_v0; }
