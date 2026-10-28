/* rgp:protos */
#define RGP_SELF_NpcObjTableSetup_312800 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* D_004E72B0 is reached by %hi/%lo => incomplete array.  The two halfword
   stores are the first two s16 members of that object. */

extern s16 D_004E72B0[];

/*rgp*/
/*rgp*/

void NpcObjTableSetup_312800(void *arg)
{
    NpcObjTableInit_2fb710(D_004E72B0);
    NpcObjTableAlloc_2fb740(D_004E72B0, arg, 0x1E);
    D_004E72B0[0] = 0xC0;
    D_004E72B0[1] = 0x20;
}
