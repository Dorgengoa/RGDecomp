/* rgp:protos */
#define RGP_SELF_GameSceneTimeScaleIsLockedMaybe_1cebc0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the u8 at +0x5E14. */

typedef struct Obj_FUN_001cebc0 {
    u8 pad000[0x5E14];
    u8 field;         /* +0x5E14 */
} Obj_FUN_001cebc0;

u8 GameSceneTimeScaleIsLockedMaybe_1cebc0(Obj_FUN_001cebc0 *o)
{
    return o->field;
}
