/* rgp:protos */
#define RGP_SELF_TexAnimSeqIsPlaying_162a60 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Asymmetric guard pair: count at +0x00, s32 table at +0x04. */

typedef struct Owner00 {
    s32 count;         /* +0x00 */
    s32 rec[1];        /* +0x04 */
} Owner00;

s32 TexAnimSeqIsPlaying_162a60(Owner00 *o, s32 index)
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
