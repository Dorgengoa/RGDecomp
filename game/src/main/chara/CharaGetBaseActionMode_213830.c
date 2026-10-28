/* rgp:protos */
#define RGP_SELF_CharaGetBaseActionMode_213830 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the s16 at +0xA2E. */

typedef struct Obj_FUN_00213830 {
    u8 pad000[0xA2E];
    s16 field;         /* +0xA2E */
} Obj_FUN_00213830;

s16 CharaGetBaseActionMode_213830(Obj_FUN_00213830 *o)
{
    return o->field;
}
