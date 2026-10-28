/* rgp:protos */
#define RGP_SELF_EffectEntriesSetNodeName_2dd8d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct K2DD8D0 { u8 pad000[0x8]; s32 f08; };

/*rgp*/

void EffectEntriesSetNodeName_2dd8d0(u8 *base, struct K2DD8D0 *k, s32 c)
{
    s32 i;
    u8 *e;

    for (i = 0; i < 0x30; i++) {
        e = base + i * 224;
        if (*(s16 *)(e + 0xE) == k->f08) {
            EffectEntryNodeSetName_2d99f0(e, k, c);
            return;
        }
    }
}
