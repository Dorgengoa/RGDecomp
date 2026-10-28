/* rgp:protos */
#define RGP_SELF_RevelationBoardCellToPixel_34d010 1
#include "port/game_protos.h"
#line 1
#include "types.h"

void RevelationBoardCellToPixel_34d010(s32 unused, s32 *ox, s32 *oy, s32 a, s32 b, s32 c, s32 d)
{
    *ox = c + a * 42 + 0x26;
    *oy = d + b * 46 + 0x26;
}
