/* rgp:protos */
#define RGP_SELF_GetSceneTimeStep_293350 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

f32 GetSceneTimeStep_293350(void)
{
    void *p;

    p = GetCurrentScene_1f5be0();
    if (p != 0) {
        return GameSceneGetTimeStep_1ceba0(p);
    }
    return 1.0f;
}
