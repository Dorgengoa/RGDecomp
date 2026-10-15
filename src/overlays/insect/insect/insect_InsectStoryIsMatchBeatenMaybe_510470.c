#include "types.h"
/* insect 0x00510470 -- 8 B / 2 words.  `j insect_InsectStoryCheckMatchBeatenMaybe_510660` with
 * `daddu $4, $0, $0` in the delay slot: a no-argument wrapper that passes 0.
 * 00510660 tests its $4 against zero and returns 0/1/2, so it is s32(s32). */

extern s32 insect_InsectStoryCheckMatchBeatenMaybe_510660(s32 a);

s32 insect_InsectStoryIsMatchBeatenMaybe_510470(void)
{
    return insect_InsectStoryCheckMatchBeatenMaybe_510660(0);
}
