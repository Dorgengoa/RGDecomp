/* rgp:protos */
#define RGP_SELF_MenuBattleEndResRelease_204250 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Obj_FUN_00204250 Obj_FUN_00204250;
typedef struct Q_FUN_00204250 Q_FUN_00204250;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void MenuBattleEndResRelease_204250(void)
{
    Obj_FUN_00204250 *o;

    MenuBattleEndLoaderRelease_2042b0();
    ResGroupUnloadGroup_42b650(((Q_FUN_00204250 *)GetMenuResGroup_206a40()), 2);
    MenuBattleEndStackRelease_206590();
    o = ((Obj_FUN_00204250 *)GetDrawCtxNameTable_15de40());
    NameTableFreeGroup_158ac0(o, 0x32D);
    NameTableFreeGroup_158ac0(o, 0x32C);
}
