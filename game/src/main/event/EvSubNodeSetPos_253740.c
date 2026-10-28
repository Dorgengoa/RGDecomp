/* rgp:protos */
#define RGP_SELF_EvSubNodeSetPos_253740 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

s32 EvSubNodeSetPos_253740(void *a, void *b)
{
    sceVu0CopyVector((u8 *)b + 0x70, (u8 *)a + 0x10);
    return 0;
}
