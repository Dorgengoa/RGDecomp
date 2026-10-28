/* rgp:protos */
#define RGP_SELF_InsectBattleResumePhaseSeq_3197b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Obj_FUN_003197b0 Obj_FUN_003197b0;

/*rgp*/
/*rgp*/
/*rgp*/

void InsectBattleResumePhaseSeq_3197b0(void)
{
    Obj_FUN_003197b0 *o;

    if (GetLoadedOverlayId_1c3200() == 5) {
        o = ((Obj_FUN_003197b0 *)InsectBattleGet_31a8d0());
        if (o != 0) {
            func_50DAD0(o, 7);
        }
    }
}
