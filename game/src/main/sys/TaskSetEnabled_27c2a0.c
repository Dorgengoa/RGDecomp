/* rgp:protos */
#define RGP_SELF_TaskSetEnabled_27c2a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Forwards both arguments to TaskTableSetEnabledByName_1f5500 with a fixed object in front --
   `&D_004D7FA0` is the first argument, so this is a bound-receiver wrapper.
   No frame at all: the whole body is the argument shuffle plus the tail call,
   and the shuffle goes through $2 because $4 and $5 both have to move. */

extern u8 D_004D7FA0[];

/*rgp*/

int TaskSetEnabled_27c2a0(s32 a, const u8 *b)
{
    return TaskTableSetEnabledByName_1f5500(D_004D7FA0, a, b);
}
