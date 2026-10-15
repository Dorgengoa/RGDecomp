/* main s27m: 6 -> 2 on an UNUSED LEADING PARAMETER (retail reads $a1..$t0). The residue
   is the argument-setup-order class (li a1,60 / move a0 swapped). */
/* PARK: same length as retail, 6 bad words (pure register-permutation +
   one 2-instruction swap, per objdump). Tried reordering temp declarations
   to first-use order (temp_2_2, temp_2, temp_2_3, temp_16) -- no change.
   2 rounds. Not re-tried further. */
#include "types.h"
#pragma opt_propagation off

extern s32 U64ToDouble_100370(s64 arg0);
extern s64 UDivDi3_139eb0(s64 arg0, s32 arg1);
extern s64 UModDi3_13a430(s64 arg0, s32 arg1);
extern s64 DoubleToU64_13ab28(s32 arg0);
extern s32 dpmul(s32 arg0, s32 arg1);
extern s32 litodp(s32 arg0);
extern s32 dptoli(s32 arg0);
extern s32 TicksToSeconds_3d6460(void);
extern s32 dpsub(s32 arg0, s32 arg1);

s64 PlayTimeSplit_3d6350(s32 arg0, s32 *arg1, s32 *arg2, s32 *arg3, s32 *arg4)
{
    s32 arg_h1;

    s32 temp_2_2;
    s64 temp_2;
    s64 temp_2_3;
    s32 temp_16;

    temp_2_2 = TicksToSeconds_3d6460();
    temp_2 = DoubleToU64_13ab28(temp_2_2);
    temp_2_3 = UDivDi3_139eb0(temp_2, 0x3C);
    *arg1 = (s32) UDivDi3_139eb0(temp_2_3, 0x3C);
    *arg2 = (s32) UModDi3_13a430(temp_2_3, 0x3C);
    arg_h1 = 0x3C;
    *arg3 = (s32) UModDi3_13a430(temp_2, arg_h1);
    temp_16 = litodp(0x3E8);
    *arg4 = dptoli(dpmul(temp_16, dpsub(temp_2_2, U64ToDouble_100370(temp_2))));
    return temp_2;
}
