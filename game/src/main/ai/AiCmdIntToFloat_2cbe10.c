/* rgp:protos */
#define RGP_SELF_AiCmdIntToFloat_2cbe10 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct { s32 a; s32 b; } T_002cbe10;

/*rgp*/
/*rgp*/

s32 AiCmdIntToFloat_2cbe10(T_002cbe10 *q)
{
    s32 n;

    n = ScriptSlotGetInt_2cc9c0(q++);
    ScriptSlotStoreFloatRef_2cc8e0(q, (f32)n);
    return 1;
}
