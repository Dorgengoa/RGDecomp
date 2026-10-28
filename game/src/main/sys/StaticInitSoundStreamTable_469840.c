/* rgp:protos */
#define RGP_SELF_StaticInitSoundStreamTable_469840 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

extern void *D_00481518;
extern s32 D_004A3AC0[];
extern u8 D_004A3AC4[];
extern s16 D_004A3EE4[];

void StaticInitSoundStreamTable_469840(void)
{
    D_004A3AC0[0] = 8;
    ConstructArray_100620(D_004A3AC4, (void *)SoundStreamTableEntryCtor_1bfd10, (void *)SoundStreamDtor_1bfc30, 0x84, 8);
    D_004A3EE4[0] = 1;
    RegisterGlobalObject_100dc0(D_004A3AC0, (void *)SoundStreamTableDtor_1c2790, &D_00481518);
}
