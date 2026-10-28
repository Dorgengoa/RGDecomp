/* rgp:protos */
#define RGP_SELF_FactorySetMapHeap_367ef0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Write the small-data s32 D_004830F0.  The value arrives in $a0: the object pointer most setters here take is absent, so the value IS the first parameter. */

extern s32 D_004830F0;

void FactorySetMapHeap_367ef0(s32 value)
{
    D_004830F0 = value;
}
