/* rgp:protos */
#define RGP_SELF_insect_InsectAiCfgSelectLevel_522d30 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x00522D30 -- 60 bytes, 15 instructions.  Resolve a cursor index (-1
 * meaning "the stored one") into a 16-byte record pointer. */

typedef struct Rec { u8 raw[0x10]; } Rec;

typedef struct List {
    u8   pad00[0x4];
    Rec *f04;                       /* +0x04 */
    u8   pad08[0xC - 0x8];
    s16  f0C;                       /* +0x0C */
    s16  f0E;                       /* +0x0E */
} List;

Rec *insect_InsectAiCfgSelectLevel_522d30(List *l, s32 i)
{
    if (i == -1) {
        i = l->f0E;
    }
    if (i >= l->f0C) {
        return 0;
    }
    l->f0E = (s16)i;
    return &l->f04[i];
}
