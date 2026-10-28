/* rgp:protos */
#define RGP_SELF_DrawListAddTexLoadChecked_140560 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct T140560 { u8 pad000[0x3BB4]; s32 f3BB4; };

/*rgp*/

s32 DrawListAddTexLoadChecked_140560(struct T140560 *p, s32 i)
{
    if (i < 0 || i >= p->f3BB4) {
        return 0;
    }
    DrawListAddTexLoad_1418c0(p, i, 0.0f);
    return 1;
}
