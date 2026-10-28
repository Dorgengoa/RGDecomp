/* rgp:protos */
#define RGP_SELF_AiCmdObjRecHasFlags6_2ca4c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct E8 { s32 a; s32 b; } E8;

/*rgp*/
/*rgp*/
/*rgp*/

extern s32 D_004DB920;

s32 AiCmdObjRecHasFlags6_2ca4c0(E8 *p0)
{
    s32 t0;
    s32 r0;
    s32 r1;
    s32 r2;

    t0 = *(volatile s32 *)&D_004DB920;
    r0 = ScriptSlotGetInt_2cc9c0(p0++);
    r1 = ((unsigned char)ObjRecHasFlags6_1c3eb0(t0, 1, r0));
    r2 = (ScriptSlotStoreIntRef_2cc900(p0, r1), (s32)0);
    return 1;
}
