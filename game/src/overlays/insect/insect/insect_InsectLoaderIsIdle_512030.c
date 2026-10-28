/* rgp:protos */
#define RGP_SELF_insect_InsectLoaderIsIdle_512030 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x00512030 -- 40 bytes, 10 instructions.  The trailing `andi 0xFF`
 * is the u8 return type.
 */

/*rgp*/
/*rgp*/

u8 insect_InsectLoaderIsIdle_512030(void)
{
    return LoaderIsIdle_1cd5b0(((s32)GetLoaderMgr_1f59d0()));
}
