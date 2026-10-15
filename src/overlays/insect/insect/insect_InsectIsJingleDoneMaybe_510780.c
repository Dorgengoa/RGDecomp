#include "types.h"
/* insect 0x00510780 -- 72 bytes, 18 instructions. */

extern void *func_207EA0(void);
extern s32   func_1D65F0(void *p, s32 k);

s32 insect_InsectIsJingleDoneMaybe_510780(void)
{
    void *p;

    p = func_207EA0();
    if (p != 0) {
        if (func_1D65F0(p, 1) == 2) {
            return 1;
        }
    }
    return 0;
}
