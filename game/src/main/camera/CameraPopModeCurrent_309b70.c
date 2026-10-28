/* rgp:protos */
#define RGP_SELF_CameraPopModeCurrent_309b70 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Head of a 2-member BYTE-IDENTICAL group (60 B each): CameraPopModeCurrent_309b70 /
   CameraPopModeCurrent_309db0.  Find the camera bound to the current scene and poke it. */

typedef struct World {
    u8  pad0000[0x4344];
    s32 m4344;
} World;

/*rgp*/
/*rgp*/
/*rgp*/

void CameraPopModeCurrent_309b70(void)
{
    World *w;
    void  *cam;

    w = ((World *)GetCurrentScene_1f5be0());
    cam = ObjRecGetLiveObject_1c3bc0(w, w->m4344);
    if (cam != 0) {
        CameraModePop_309390(cam, 1);
    }
}
