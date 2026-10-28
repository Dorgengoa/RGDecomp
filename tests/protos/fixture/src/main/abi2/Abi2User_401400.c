#include "types.h"
/* callers of src/main/abi2/Abi2_401200.c and LinkCpp_401500.cpp with the views the
   decomp spelled */
typedef unsigned _BitInt(128) __attribute__((aligned(16))) u128;
extern s32 V0Pick_4012c0(s32 *o, s32 f);
extern s32 V0Early_401300(s32 *o, s32 f);
extern u128 U128Id_401340(s32 *p);
extern void LinkTake_401500(void);

s32 V0User_401400(s32 *o, s32 f)
{
    return V0Pick_4012c0(o, f) + 100;
}

s32 U128User_401440(s32 *p)
{
    u128 a;

    a = U128Id_401340(p);
    return (s32)a;
}

void LinkUser_401480(s32 *p)
{
    LinkTake_401500();
}

s32 V0EarlyUser_4014c0(s32 *o, s32 f)
{
    return V0Early_401300(o, f) * 2;
}
