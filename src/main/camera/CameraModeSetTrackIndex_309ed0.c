#include "types.h"

/* Install a camera-track index on camera id 2 -- the second camera stack.
   This is where the town's track 64 lands; event command 0x1e computes the
   index and calls here. */

typedef struct Camera {
    u8 pad000[0x270];
    s32 trackIndex;   /* +0x270 */
} Camera;

extern void *GetCurrentScene_1f5be0(void);
extern Camera *ObjRecGetLiveObject_1c3bc0(void *sceneMgr, s32 id);

void CameraModeSetTrackIndex_309ed0(s32 trackIndex)
{
    Camera *camera = ObjRecGetLiveObject_1c3bc0(GetCurrentScene_1f5be0(), 2);

    camera->trackIndex = trackIndex;
}
