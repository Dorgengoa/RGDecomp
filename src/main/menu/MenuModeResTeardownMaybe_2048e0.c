#include "types.h"

extern void MenuMainClose_296de0(s32);
extern void MenuReadBufRelease_206410(void);
extern s32 GetDrawCtxNameTable_15de40(void);
extern void NameTableFreeGroup_158ac0(s32, s32);
extern void MenuExitFreeGroupsMaybe_204970(s32);
extern void MenuMainStackRelease_206910(void);

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
    MenuExitFreeGroupsMaybe_204970(p0);
    MenuMainStackRelease_206910();
    MenuCapStackRelease_2068e0();
    MenuReadBufRelease_206410();
}
