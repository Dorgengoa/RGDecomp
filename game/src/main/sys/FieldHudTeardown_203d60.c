/* rgp:protos */
#define RGP_SELF_FieldHudTeardown_203d60 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Obj_FUN_00203d60 Obj_FUN_00203d60;

extern s32 D_00481C5C;
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void FieldHudTeardown_203d60(void)
{
    Obj_FUN_00203d60 *o;

    FieldHudRelease_203dc0();
    o = ((Obj_FUN_00203d60 *)GetDrawCtxNameTable_15de40());
    NameTableFreeGroup_158ac0(o, 0x32D);
    NameTableFreeGroup_158ac0(o, 0x32C);
    D_00481C5C = 0;
    MenuBattleStackRelease_2067d0();
    MenuBattleIconStackRelease_2066c0();
}
