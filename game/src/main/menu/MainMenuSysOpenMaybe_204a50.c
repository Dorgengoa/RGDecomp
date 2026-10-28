/* rgp:protos */
#define RGP_SELF_MainMenuSysOpenMaybe_204a50 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern u8 D_004BBBC0[];
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void MainMenuSysOpenMaybe_204a50(void)
{
    MenuMainStackInit_206920();
    MemStackReset_14d830(D_004BBBC0);
    MenuReadBufInit_206460(0x120C8);
    MenuCapStackInit_2068f0();
    MenuSysInitMaybe_297640();
}
