#include "types.h"

extern const u8 D_004BBBC0[];
extern void MenuMainStackInit_206920(void);
extern void MemStackReset_14d830(const u8 *p);
extern void MenuReadBufInit_206460(s32 n);
extern void MenuCapStackInit_2068f0(void);
extern void MenuSysInitMaybe_297640(void);

void MainMenuSysOpenMaybe_204a50(void)
{
    MenuMainStackInit_206920();
    MemStackReset_14d830(D_004BBBC0);
    MenuReadBufInit_206460(0x120C8);
    MenuCapStackInit_2068f0();
    MenuSysInitMaybe_297640();
}
