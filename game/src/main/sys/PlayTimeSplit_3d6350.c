/* rgp:protos */
#define RGP_SELF_PlayTimeSplit_3d6350 1
#include "port/game_protos.h"
#line 1
/* main s27m: 6 -> 2 on an UNUSED LEADING PARAMETER (retail reads $a1..$t0). The residue
   is the argument-setup-order class (li a1,60 / move a0 swapped). */
/* PARK: same length as retail, 6 bad words (pure register-permutation +
   one 2-instruction swap, per objdump). Tried reordering temp declarations
   to first-use order (temp_2_2, temp_2, temp_2_3, temp_16) -- no change.
   2 rounds. Not re-tried further. */
#include "types.h"
#pragma opt_propagation off

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s64 PlayTimeSplit_3d6350(long long arg0, s32 *arg1, s32 *arg2, s32 *arg3, s32 *arg4)
{
    s32 arg_h1;

    double temp_2_2;
    s64 temp_2;
    s64 temp_2_3;
    double temp_16;

    temp_2_2 = TicksToSeconds_3d6460((unsigned long long)arg0);
    temp_2 = DoubleToU64_13ab28(temp_2_2);
    temp_2_3 = UDivDi3_139eb0(temp_2, (unsigned long long)(0x3C));
    *arg1 = (s32) UDivDi3_139eb0(temp_2_3, (unsigned long long)(0x3C));
    *arg2 = (s32) UModDi3_13a430(temp_2_3, (unsigned long long)(0x3C));
    arg_h1 = 0x3C;
    *arg3 = (s32) UModDi3_13a430(temp_2, (unsigned long long)(arg_h1));
    temp_16 = litodp(0x3E8);
    *arg4 = dptoli(dpmul(temp_16, dpsub(temp_2_2, U64ToDouble_100370(temp_2))));
    return temp_2;
}
