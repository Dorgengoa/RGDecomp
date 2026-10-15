#include "types.h"

struct E31E530 { u64 v; };
struct T31E530 { u8 pad000[0x20]; struct E31E530 f20[1]; };

void HpGaugeClearTimer_31e530(struct T31E530 *p, s32 i)
{
    if (i >= 0x10) {
        i = 0xF;
    }
    p->f20[i].v = 0;
}
