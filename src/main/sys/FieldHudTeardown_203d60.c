#include "types.h"

typedef struct Obj_FUN_00203d60 Obj_FUN_00203d60;

extern s32 D_00481C5C;
extern void FieldHudRelease_203dc0(void);
extern Obj_FUN_00203d60 *GetDrawCtxNameTable_15de40(void);
extern void NameTableFreeGroup_158ac0(Obj_FUN_00203d60 *o, s32 n);
extern void MenuBattleStackRelease_2067d0(void);
extern void MenuBattleIconStackRelease_2066c0(void);

void FieldHudTeardown_203d60(void)
{
    Obj_FUN_00203d60 *o;

    FieldHudRelease_203dc0();
    o = GetDrawCtxNameTable_15de40();
    NameTableFreeGroup_158ac0(o, 0x32D);
    NameTableFreeGroup_158ac0(o, 0x32C);
    D_00481C5C = 0;
    MenuBattleStackRelease_2067d0();
    MenuBattleIconStackRelease_2066c0();
}
