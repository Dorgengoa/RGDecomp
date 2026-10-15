#include "types.h"

extern void MenuTransdataInit_206270(void);
extern void MenuTranstempInit_206240(void);
extern void func_5212B0(void);

void ThinkMenuOpen_203670(void)
{
    MenuTransdataInit_206270();
    MenuTranstempInit_206240();
    func_5212B0();
}
