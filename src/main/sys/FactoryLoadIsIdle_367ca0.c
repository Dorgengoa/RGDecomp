#include "types.h"
extern void *GetFactoryObj_367f30(void);
extern s32 func_504840(void *p);

s32 FactoryLoadIsIdle_367ca0(void)
{
    void *p;

    p = GetFactoryObj_367f30();
    if (p != 0) {
        return func_504840(p);
    }
    return 0;
}
