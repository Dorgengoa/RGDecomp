/* rgp:protos */
#define RGP_SELF_HelpMenuClose_203200 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

void HelpMenuClose_203200(void)
{
    MenuHelpResRelease_203230();
    MenuTransdataRelease_206260();
    MenuTranstempRelease_206230();
}
