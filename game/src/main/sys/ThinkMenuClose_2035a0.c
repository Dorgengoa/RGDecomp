/* rgp:protos */
#define RGP_SELF_ThinkMenuClose_2035a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

void ThinkMenuClose_2035a0(void)
{
    MenuThinkResRelease_2035d0();
    MenuTransdataRelease_206260();
    MenuTranstempRelease_206230();
}
