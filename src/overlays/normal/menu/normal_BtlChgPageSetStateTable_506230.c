#include "types.h"
/* normal 0x00506230 -- one call, then `return 1`. */
extern void func_289C10(void);

s32 normal_BtlChgPageSetStateTable_506230(void)
{
    func_289C10();
    return 1;
}
