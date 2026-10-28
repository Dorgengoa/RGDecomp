/* rgp:protos */
#define RGP_SELF_CopyQword_18bb60 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Copy one 16-byte row.  u128 is the only type that moves a qword in a single instruction. */

typedef rg_u128 u128;

void CopyQword_18bb60(u128 *dst, const u128 *src)
{
    *dst = *src;
}
