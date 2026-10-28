/* rgp:protos */
#define RGP_SELF_TransMenuClose_2037b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

void TransMenuClose_2037b0(void)
{
    MenuTransResRelease_2037e0();
    MenuTransdataRelease_206260();
    MenuTranstempRelease_206230();
}
