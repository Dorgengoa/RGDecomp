/* rgp:protos */
#define RGP_SELF_LetterboxIsEnabled_277fe0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the u8 at +0x14. */

typedef struct Obj_FUN_00277fe0 {
    u8 pad000[0x14];
    u8 field;         /* +0x14 */
} Obj_FUN_00277fe0;

u8 LetterboxIsEnabled_277fe0(Obj_FUN_00277fe0 *o)
{
    return o->field;
}
