/* rgp:protos */
#define RGP_SELF_CameraModeSetTrackIndex_309ed0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Install a camera-track index on camera id 2 -- the second camera stack.
   This is where the town's track 64 lands; event command 0x1e computes the
   index and calls here. */

typedef struct Camera {
    u8 pad000[0x270];
    s32 trackIndex;   /* +0x270 */
} Camera;

/*rgp*/
/*rgp*/

void CameraModeSetTrackIndex_309ed0(s32 trackIndex)
{
    Camera *camera = ((Camera *)ObjRecGetLiveObject_1c3bc0(GetCurrentScene_1f5be0(), 2));

    camera->trackIndex = trackIndex;
}
