#include "types.h"
/* MenuTransIsReady_203870 shape: MAIN reads the overlay ready poll through the
   import name (NORMAL is resident) */
extern s32 func_4EC100(void);

u8 TransReady_203870(void)
{
    s32 r;

    r = func_4EC100();
    return (r != 0);
}
