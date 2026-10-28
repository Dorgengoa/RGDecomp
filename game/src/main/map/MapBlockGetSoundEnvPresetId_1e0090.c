/* rgp:protos */
#define RGP_SELF_MapBlockGetSoundEnvPresetId_1e0090 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s16 at +0x68. */

typedef struct Obj_FUN_001e0090 {
    u8 pad000[0x68];
    s16 field;         /* +0x68 */
} Obj_FUN_001e0090;

s16 MapBlockGetSoundEnvPresetId_1e0090(Obj_FUN_001e0090 *o)
{
    return o->field;
}
