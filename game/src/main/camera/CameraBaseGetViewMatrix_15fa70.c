/* rgp:protos */
#define RGP_SELF_CameraBaseGetViewMatrix_15fa70 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Tail-call adapter: marshal and forward a global address. */

/*rgp*/

s32 CameraBaseGetViewMatrix_15fa70(void *p4, s32 a5)
{
    return (sceVu0InversMatrix(a5, (u8 *)p4 + 0x10), (s32)0);
}
