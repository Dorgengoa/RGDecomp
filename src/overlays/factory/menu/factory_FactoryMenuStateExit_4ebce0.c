#include "types.h"

extern u8    D_00484A6C;
extern void *func_206A40(void);
extern void  func_42B650(void *p, s32 a);

s32 factory_FactoryMenuStateExit_4ebce0(void)
{
    func_42B650(func_206A40(), 2);
    D_00484A6C = 0;
    return 1;
}
