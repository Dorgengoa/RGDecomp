/* rgp:protos */
#define RGP_SELF_CameraModeDebugDraw_3096d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

void CameraModeDebugDraw_3096d0(void *arg0) {
    s32 t;

    t = GetCurrentScene_1f5be0();
    if (*(s32 *)((u8 *)arg0 + 0x268) != 0) {
        switch (CameraModeGetCurrent_309370(arg0)) {
        case 9:
        case 0xA:
        case 0xB:
        case 0xC:
        case 0xD:
            CameraModeDbgDrawSphere_3061b0(arg0);
            break;
        }
    }
}
