/* rgp:protos */
#define RGP_SELF_insect_InsectTeamGetPiece_5138d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x005138D0 -- 28 bytes.  `((i*16 - i) * 4 + i) * 8` = i * 0x1E8, so
 * this is plain pointer arithmetic over a 0x1E8-byte record. */

typedef struct E {
    u8 raw[0x1E8];
} E;

E *insect_InsectTeamGetPiece_5138d0(E *a, s32 i)
{
    return a + i;
}
