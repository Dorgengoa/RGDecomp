/* rgp:protos */
#define RGP_SELF_LoaderShutdown_1cdfe0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Obj_FUN_001cdfe0 Obj_FUN_001cdfe0;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void LoaderShutdown_1cdfe0(Obj_FUN_001cdfe0 *o)
{
    LoaderPurgeAll_1cd240(o);
    while (LoaderCountQueued_1cd620(o) > 0) {
        LoaderTick_1ccc30(o);
    }
    LoaderClear_1ce040(o);
    FileReqCancelAll_182510();
}
