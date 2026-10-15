#include "types.h"
/* insect 0x0051D320 -- 68 bytes.  `dsll32/dsra32 ..,16` on a register
 * parameter is an explicit (s16) cast of an s32 local. */

extern void func_100840(void);

void *insect_InsectAbilityDtor_51d320(void *p, s32 n)
{
    if (p != 0) {
        if ((s16)n > 0) {
            func_100840();
        }
    }
    return p;
}
