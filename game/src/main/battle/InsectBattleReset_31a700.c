/* rgp:protos */
#define RGP_SELF_InsectBattleReset_31a700 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Obj_FUN_0031a700 Obj_FUN_0031a700;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void InsectBattleReset_31a700(void)
{
    Obj_FUN_0031a700 *o;

    InsectBattleGetMemStack_31a8c0();
    o = ((Obj_FUN_0031a700 *)InsectBattleGet_31a8d0());
    if (o == 0) {
        InsectBattleShutdown_31a230();
    } else {
        func_50E640(o);
        CameraPopModeCurrent_309b70();
    }
}
