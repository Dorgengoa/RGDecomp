/* rgp:protos */
#define RGP_SELF_CharaResMgrSetMonSndLoad_1f0050 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the s16 at +0xD14. */

typedef struct Obj_FUN_001f0050 {
    u8 pad000[0xD14];
    s16 field;         /* +0xD14 */
} Obj_FUN_001f0050;

void CharaResMgrSetMonSndLoad_1f0050(Obj_FUN_001f0050 *o, s16 value)
{
    o->field = value;
}
