/* rgp:protos */
#define RGP_SELF_StaticInitSoundStreamSlots_4697f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern u8 D_004A25F0[];
extern s32 D_004814E0;
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void StaticInitSoundStreamSlots_4697f0(void)
{
    ConstructArray_100620(D_004A25F0, (void *)SoundStreamSlotCtor_1bf720, (void *)SoundStreamSlotDtor_1bf6c0, 0x128, 4);
    RegisterGlobalObject_100dc0(0, (void *)SoundStreamSlotsDtor_1bf6a0, &D_004814E0);
}
