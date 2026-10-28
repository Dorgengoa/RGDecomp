/* rgp:protos */
#define RGP_SELF_GameSceneSoundNoteListAlloc_1d1480 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct Big {
    u8 pad000[0xB0A4];
    s32 mB0A4;
};

/*rgp*/
/*rgp*/
/*rgp*/

void GameSceneSoundNoteListAlloc_1d1480(struct Big *p0, s32 p1)
{
    SoundNoteListInit_1b4ee0(&p0->mB0A4);
    SoundNoteListAlloc_1b4f00(&p0->mB0A4, 0x30, p1);
    SoundNoteListReset_1b4e80(&p0->mB0A4);
}
