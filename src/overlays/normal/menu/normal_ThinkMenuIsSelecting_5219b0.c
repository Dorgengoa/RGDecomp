#include "types.h"
/* normal 0x005219B0 -- `jr $31 / lb $2, -0x81C($28)`.  `lb`, not `lbu`, so
 * the global is SIGNED.  One of the 55 unnamed functions. */
extern s8 D_00484954;

s32 normal_ThinkMenuIsSelecting_5219b0(void)
{
    return D_00484954;
}
