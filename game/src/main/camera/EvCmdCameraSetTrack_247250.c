/* rgp:protos */
#define RGP_SELF_EvCmdCameraSetTrack_247250 1
#include "port/game_protos.h"
#line 1
#include "event_vm.h"

/* Event command 0x1e: compute a camera-track index and install it on camera
   id 2. This is where the town's track 64 comes from. */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 EvCmdCameraSetTrack_247250(void *vm)
{
    void *sub = gEventContext->player->sub60;

    CameraModeSetTrackIndex_309ed0(EventCastGetObjId_24c160(sub, EventCastFindKeyByName_24bb50(sub, ScriptGetCodeAddr_249050(vm)), 0));
    return 1;
}
