/* rgp:protos */
#define RGP_SELF_title_TitleUvToFixed_4f13a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* title.bin overlay, 0x004F13A0 -- sll 4 then addiu 8 */

s32 title_TitleUvToFixed_4f13a0(s32 n)
{
    return (n << 4) + 8;
}
