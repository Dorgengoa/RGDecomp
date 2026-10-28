/* rgp:protos */
#define RGP_SELF_SoundStreamSlotsDtor_1bf6a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

extern u8 D_004A25F0[];
/*rgp*/

void SoundStreamSlotsDtor_1bf6a0(void)
{
    DestroyArray_1005b0(D_004A25F0, SoundStreamSlotDtor_1bf6c0, 0x128, 4);
}
