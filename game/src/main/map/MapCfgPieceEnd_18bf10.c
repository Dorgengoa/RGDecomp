/* rgp:protos */
#define RGP_SELF_MapCfgPieceEnd_18bf10 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern void *D_00481254;
extern void *D_00481258;
/*rgp*/
/*rgp*/

s32 MapCfgPieceEnd_18bf10(void)
{
    void *r;
    if (D_00481254 == 0) goto zero;
    if (D_00481258 != 0) goto ok;
zero:
    return 0;
ok:
    r = ListNodeGetData_18a370(D_00481254);
    if (r == 0) return 0;
    NodeObjAppendChild_1950c0(r, D_00481258);
    return 1;
}
