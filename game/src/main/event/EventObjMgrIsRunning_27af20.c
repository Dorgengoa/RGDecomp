/* rgp:protos */
#define RGP_SELF_EventObjMgrIsRunning_27af20 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
extern u8 D_00482188;

s32 EventObjMgrIsRunning_27af20(void)
{
    s32 t;

    t = GetGameMode_1f59c0();
    switch (t) {
    case 6:
    case 7:
        return 1;
    }
    return !(D_00482188 != 0);
}
