/* rgp:protos */
#define RGP_SELF_ShopMenuClose_2036a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

void ShopMenuClose_2036a0(void)
{
    ShopMenuRelease_2036d0();
    MenuTransdataRelease_206260();
    MenuTranstempRelease_206230();
}
