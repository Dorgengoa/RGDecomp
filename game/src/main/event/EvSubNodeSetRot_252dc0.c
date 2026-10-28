/* rgp:protos */
#define RGP_SELF_EvSubNodeSetRot_252dc0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

s32 EvSubNodeSetRot_252dc0(void *a, void *b)
{
    sceVu0CopyVector((u8 *)b + 0x80, (u8 *)a + 0x10);
    return 0;
}
