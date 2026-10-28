/* rgp:protos */
#define RGP_SELF_MovieSectorsDescramble_1d3560 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern s32 D_004817F0;
/*rgp*/

void MovieSectorsDescramble_1d3560(s32 *p1, s32 count, void *p3)
{
    s32 i;
    s32 seed;
    s32 j;
    s32 v;

    if (D_004817F0 == 0) {
        return;
    }
    for (i = 0; i < count; i++) {
        seed = StrSum4_1d3600(p3);
        for (j = 0; j < 0x200; j++) {
            v = *p1;
            v = v ^ seed;
            seed = seed * 0x02E90EDD;
            *p1 = v;
            p1++;
        }
    }
}
