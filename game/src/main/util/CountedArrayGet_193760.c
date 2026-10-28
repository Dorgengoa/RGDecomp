/* rgp:protos */
#define RGP_SELF_CountedArrayGet_193760 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Asymmetric guard pair: count at +0x00, s32 table at +0x04.  Byte-identical
   body to TexAnimSeqIsPlaying_162a60 in another TU. */

typedef struct Owner00b {
    s32 count;         /* +0x00 */
    s32 rec[1];        /* +0x04 */
} Owner00b;

s32 CountedArrayGet_193760(Owner00b *o, s32 index)
{
    u8 ok;

    if (index < 0) {
        goto none;
    }
    ok = index < o->count;
    if (ok != 0) {
        goto found;
    }
none:
    return 0;
found:
    return o->rec[index];
}
