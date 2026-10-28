/* rgp:protos */
#define RGP_SELF_AiCmdGetCtxListId_2c5120 1
#include "port/game_protos.h"
#line 1
#include "types.h"
typedef struct { s32 a, b; } E8_2c5120;
/*rgp*/
/*rgp*/
extern s32 D_004DB934[];

s32 AiCmdGetCtxListId_2c5120(E8_2c5120 *p0)
{
    s32 r;
    s32 v;

    r = ScriptSlotGetInt_2cc9c0(p0++);
    v = -1;
    if (r < 0x10) {
        v = D_004DB934[r];
    }
    ScriptSlotStoreIntRef_2cc900(p0, v);
    return 1;
}
