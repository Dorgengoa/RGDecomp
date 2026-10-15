#include "types.h"
/* normal 0x00506270 -- one call, then `return 1`. */
extern void func_289C40(void);

s32 normal_BtlChgPageSetMemStack_506270(void)
{
    func_289C40();
    return 1;
}
