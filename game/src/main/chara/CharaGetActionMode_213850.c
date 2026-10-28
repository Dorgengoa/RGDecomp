/* rgp:protos */
#define RGP_SELF_CharaGetActionMode_213850 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s16 at +0xA32. */

typedef struct Obj_FUN_00213850 {
    u8 pad000[0xA32];
    s16 field;         /* +0xA32 */
} Obj_FUN_00213850;

s16 CharaGetActionMode_213850(Obj_FUN_00213850 *o)
{
    return o->field;
}
