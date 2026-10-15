#include "event_vm.h"

/* Event command 0x1e: compute a camera-track index and install it on camera
   id 2. This is where the town's track 64 comes from. */

extern s32 ScriptGetCodeAddr_249050(void *vm);
extern s32 EventCastFindKeyByName_24bb50(void *sub, s32 arg);
extern s32 EventCastGetObjId_24c160(void *sub, s32 arg);
extern void CameraModeSetTrackIndex_309ed0(s32 trackIndex);

s32 EvCmdCameraSetTrack_247250(void *vm)
{
    void *sub = gEventContext->player->sub60;

    CameraModeSetTrackIndex_309ed0(EventCastGetObjId_24c160(sub, EventCastFindKeyByName_24bb50(sub, ScriptGetCodeAddr_249050(vm))));
    return 1;
}
