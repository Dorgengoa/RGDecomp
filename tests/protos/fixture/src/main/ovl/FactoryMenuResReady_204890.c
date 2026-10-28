#include "types.h"
/* FACTORY is resident here */
extern s32 func_4EC000(void);

s32 FactoryMenuResReady_204890(void)
{
    return func_4EC000() != 0;
}
