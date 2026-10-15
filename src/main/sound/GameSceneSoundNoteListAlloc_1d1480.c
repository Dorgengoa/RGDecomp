#include "types.h"

struct Big {
    u8 pad000[0xB0A4];
    s32 mB0A4;
};

extern void SoundNoteListInit_1b4ee0(void *);
extern void SoundNoteListAlloc_1b4f00(void *, s32, s32);
extern void SoundNoteListReset_1b4e80(void *);

void GameSceneSoundNoteListAlloc_1d1480(struct Big *p0, s32 p1)
{
    SoundNoteListInit_1b4ee0(&p0->mB0A4);
    SoundNoteListAlloc_1b4f00(&p0->mB0A4, 0x30, p1);
    SoundNoteListReset_1b4e80(&p0->mB0A4);
}
