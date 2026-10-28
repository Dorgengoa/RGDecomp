/* rgp:protos */
#define RGP_SELF_AiCmdFloatToInt_2cbdd0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct { s32 a; s32 b; } T_002cbdd0;

/*rgp*/
/*rgp*/

s32 AiCmdFloatToInt_2cbdd0(T_002cbdd0 *q)
{
    f32 f;

    f = ScriptSlotGetFloat_2cc9a0(q++);
    ScriptSlotStoreIntRef_2cc900(q, (s32)f);
    return 1;
}
