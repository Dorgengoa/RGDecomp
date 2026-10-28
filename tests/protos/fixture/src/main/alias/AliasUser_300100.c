#include "types.h"
/* calls MAIN code by address: renamed to the symbol defined there */
extern s32 func_300000(s32, s32);

s32 AliasUser_300100(void)
{
    return func_300000(10, 3);
}
