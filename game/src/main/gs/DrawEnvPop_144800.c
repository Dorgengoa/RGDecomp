/* rgp:protos */
#define RGP_SELF_DrawEnvPop_144800 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct T144800 { u8 pad000[0x270]; u8 *f270; };

void DrawEnvPop_144800(struct T144800 *p)
{
    if (p->f270 > (u8 *)p + 0x280) {
        p->f270 = p->f270 - 0x190;
    }
}
