/* rgp:protos */
#define RGP_SELF_insect_InsectPlaySe_510870 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x00510870 -- 80 bytes, 20 instructions.  Names the CALL RESULT so the
 * handle test sits between the two calls; the 1.0f is an inline `lui 0x3F80` /
 * `mtc1`, not a .lit4 pool load. */

/*rgp*/
/*rgp*/

void insect_InsectPlaySe_510870(s32 id)
{
    s32 h;

    if (id != -1) {
        h = GetCurrentScene_1f5be0();
        if (h != 0) {
            GameSceneSoundSlot5PlaySeVol_1d05d0(h, id, 1.0f);
        }
    }
}
