/* rgp:protos */
#define RGP_SELF_GameSceneObjSetCBlurMaybe_1cf900 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void GameSceneObjSetCBlurMaybe_1cf900(void *p, s32 unused, f32 t, s32 flag)
{
    void *r;
    f32 v;
    s32 x;

    r = ObjRecGetLiveObject_1c4a90(p, (int)unused);
    if (r == 0) return;
    v = 1.0f;
    x = 0;
    if (flag != 0) {
        x = ((s32)CBlurTexFindTex_1791a0((void *)((s32)p + 0x58C0)));
        v = t;
    }
    ModelObjSetCBlurTexMaybe_1ad5d0(r, x);
    ModelObjSetCBlurAlphaMaybe_1ad5c0(r, v);
}
