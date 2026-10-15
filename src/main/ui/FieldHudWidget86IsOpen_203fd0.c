#include "types.h"

/* Tail-call adapter: marshal and forward a global address. */

extern u8 D_00527020[];

extern s32 func_4F9490(void *);

s32 FieldHudWidget86IsOpen_203fd0(void)
{
    return func_4F9490(D_00527020);
}
