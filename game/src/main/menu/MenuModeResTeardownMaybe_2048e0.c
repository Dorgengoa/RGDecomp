/* rgp:protos */
#define RGP_SELF_MenuModeResTeardownMaybe_2048e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void MenuModeResTeardownMaybe_2048e0(s32 p0)
{
    s32 r2;

    if (p0 != 0) {
        MenuMainClose_296de0(1);
        MenuReadBufRelease_206410();
        r2 = GetDrawCtxNameTable_15de40();
        NameTableFreeGroup_158ac0(r2, 0x32D);
        NameTableFreeGroup_158ac0(r2, 0x32F);
        NameTableFreeGroup_158ac0(r2, 0x32E);
        return;
    }
    MenuExitFreeGroupsMaybe_204970();
    MenuMainStackRelease_206910();
    MenuCapStackRelease_2068e0();
    MenuReadBufRelease_206410();
}
