/* rgp:protos */
#define RGP_SELF_SoundStreamThreadMain_1c1050 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

void SoundStreamThreadMain_1c1050(void *p)
{
    s32 ok;

    do {
        ok = !SoundStreamProcessCmds_1c05f0(p);
    } while (ok);
}
