/* rgp:protos */
#define RGP_SELF_ScriptCmdVecSet_334740 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct T { u8 b[0x10]; } T;

/*rgp*/
/*rgp*/

s32 ScriptCmdVecSet_334740(u8 *a, s32 k)
{
    T tmp __attribute__((aligned(16)));

    if (k != 6) return 0;
    ScriptSlotsToVec4_334810(&tmp, a + 0x18);
    ScriptSlotStoreVec3_334790(a, &tmp);
    return 1;
}
