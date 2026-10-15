#include "types.h"

/* Camera mode 5's entry point: hand the town's driver the track index the
   second camera stack is holding. A tail call -- mwcc turns it into a `j`. */

typedef struct CameraMode {
    u8 pad000[0x270];
    s32 trackIndex;   /* +0x270, the town's 64 */
} CameraMode;

extern void CameraTrackUpdate_305960(void *camera, s32 trackIndex);

void CameraModeTrackUpdate_307b30(CameraMode *this, void *camera)
{
    CameraTrackUpdate_305960(camera, this->trackIndex);
}
