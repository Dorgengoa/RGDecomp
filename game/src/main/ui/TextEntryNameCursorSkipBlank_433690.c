/* rgp:protos */
#define RGP_SELF_TextEntryNameCursorSkipBlank_433690 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 TextEntryNameCursorSkipBlank_433690(s32 p0, s32 p1)
{
    s32 r;

    r = TextEntryGridSkipBlankCell_434290(p0, p1, (p0 + 0x197), (p0 + 0x2C));
    return 1;
}
