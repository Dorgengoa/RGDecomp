/* rgp:protos */
#define RGP_SELF_CharaSetFlags_212470 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the s64 at +0x568. */

typedef struct Obj_FUN_00212470 {
    u8 pad000[0x568];
    s64 field;         /* +0x568 */
} Obj_FUN_00212470;

void CharaSetFlags_212470(Obj_FUN_00212470 *o, s64 value)
{
    o->field = value;
}
