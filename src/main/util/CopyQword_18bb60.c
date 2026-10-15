#include "types.h"

/* Copy one 16-byte row.  u128 is the only type that moves a qword in a single instruction. */

typedef unsigned __int128 u128;

void CopyQword_18bb60(u128 *dst, const u128 *src)
{
    *dst = *src;
}
