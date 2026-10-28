/* rgp:protos */
#define RGP_SELF_GameSceneTimeScaleIsSuspendedMaybe_1cebb0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the u8 at +0x5E15. */

typedef struct Obj_FUN_001cebb0 {
    u8 pad000[0x5E15];
    u8 field;         /* +0x5E15 */
} Obj_FUN_001cebb0;

u8 GameSceneTimeScaleIsSuspendedMaybe_1cebb0(Obj_FUN_001cebb0 *o)
{
    return o->field;
}
