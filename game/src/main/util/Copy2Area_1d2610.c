/* rgp:protos */
#define RGP_SELF_Copy2Area_1d2610 1
#include "port/game_protos.h"
#line 1
/* PARK: fully re-derived from asm (m2c's memcpy() calls dropped the dest
   arg since $4 was unchanged from entry). length 0x134 vs retail 0x130
   (4 over) -- objdump shows one extra `move v0,s8` before return, a
   register-allocation residue, not a value bug. Not re-tried. */
#include "types.h"

extern void memcpy(void *dst, void *src, s32 n);

s32 Copy2Area_1d2610(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7)
{
    s32 temp_19;
    s32 temp_23;

    temp_23 = arg5 + arg7;
    if ((arg1 + arg3) < temp_23) {
        return 0;
    }
    if (arg5 >= arg1) {
        memcpy((void *) arg0, (void *) arg4, arg1);
        memcpy((void *) arg2, (void *) (arg4 + arg1), arg5 - arg1);
        memcpy((void *) ((arg2 + arg5) - arg1), (void *) arg6, arg7);
    } else {
        if (arg7 >= (arg1 - arg5)) {
            memcpy((void *) arg0, (void *) arg4, arg5);
            temp_19 = arg1;
            temp_19 -= arg5;
            memcpy((void *) (arg0 + arg5), (void *) arg6, temp_19);
            memcpy((void *) arg2, (void *) ((arg6 + arg1) - arg5), arg7 - temp_19);
        } else {
            memcpy((void *) arg0, (void *) arg4, arg5);
            memcpy((void *) (arg0 + arg5), (void *) arg6, arg7);
        }
    }
    return temp_23;
}
