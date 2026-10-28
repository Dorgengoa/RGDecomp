/* rgp:protos */
#define RGP_SELF_TicksToSeconds_3d6460 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

double TicksToSeconds_3d6460(unsigned long long rgp_a0)
{
    return dpdiv(U64ToDouble_100370((unsigned long long)rgp_a0), 60.0);
}
