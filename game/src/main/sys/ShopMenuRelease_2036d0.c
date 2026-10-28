/* rgp:protos */
#define RGP_SELF_ShopMenuRelease_2036d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Obj_FUN_002036d0 Obj_FUN_002036d0;

/*rgp*/
/*rgp*/
/*rgp*/

void ShopMenuRelease_2036d0(void)
{
    Obj_FUN_002036d0 *o;

    func_50A630();
    o = ((Obj_FUN_002036d0 *)GetDrawCtxNameTable_15de40());
    NameTableFreeGroup_158ac0(o, 0x32D);
    NameTableFreeGroup_158ac0(o, 0x32E);
    NameTableFreeGroup_158ac0(o, 0x32F);
}
