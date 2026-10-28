/* rgp:protos */
#define RGP_SELF_GameSceneMapEffectStep_1cef40 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Obj_FUN_001cef40 Obj_FUN_001cef40;
typedef struct Ent_FUN_001cef40 Ent_FUN_001cef40;

/*rgp*/
/*rgp*/
/*rgp*/

void GameSceneMapEffectStep_1cef40(Obj_FUN_001cef40 *o)
{
    Ent_FUN_001cef40 *arr[0x14];
    s32 n;
    s32 i;

    n = ObjRecCollectLiveObjects_1c5150(o, arr, 0x14);
    for (i = 0; i < n; i++) {
        MapAreaModelTickFrame_1876f0(arr[i]);
    }
    ParticleSwirlUpdate_17dae0((u8 *)o + 0x59E0);
}
