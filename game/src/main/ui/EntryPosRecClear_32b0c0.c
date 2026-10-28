/* rgp:protos */
#define RGP_SELF_EntryPosRecClear_32b0c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

void EntryPosRecClear_32b0c0(void *p)
{
    Vec3Set_32b0b0(p, 0.0f, 0.0f, 0.0f);
    EntryPosRecSetEntry_32b0a0(p, 0);
}
