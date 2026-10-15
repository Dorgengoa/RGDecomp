#include "types.h"

extern void MenuTransdataInit_206270(void);
extern void MenuTranstempInit_206240(void);
extern void func_50AB50(void);

void ShopMenuOpen_203780(void)
{
    MenuTransdataInit_206270();
    MenuTranstempInit_206240();
    func_50AB50();
}
