#include "types.h"

typedef struct Obj_FUN_002036d0 Obj_FUN_002036d0;

extern void func_50A630(void);
extern Obj_FUN_002036d0 *GetDrawCtxNameTable_15de40(void);
extern void NameTableFreeGroup_158ac0(Obj_FUN_002036d0 *o, s32 n);

void ShopMenuRelease_2036d0(void)
{
    Obj_FUN_002036d0 *o;

    func_50A630();
    o = GetDrawCtxNameTable_15de40();
    NameTableFreeGroup_158ac0(o, 0x32D);
    NameTableFreeGroup_158ac0(o, 0x32E);
    NameTableFreeGroup_158ac0(o, 0x32F);
}
