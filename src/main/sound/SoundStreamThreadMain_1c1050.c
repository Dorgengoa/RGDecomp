#include "types.h"

extern s32 SoundStreamProcessCmds_1c05f0(void *p);

void SoundStreamThreadMain_1c1050(void *p)
{
    s32 ok;

    do {
        ok = !SoundStreamProcessCmds_1c05f0(p);
    } while (ok);
}
