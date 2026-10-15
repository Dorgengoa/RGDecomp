#include "types.h"

extern void *D_00481254;
extern void *D_00481258;
extern void *ListNodeGetData_18a370(void *);
extern void NodeObjAppendChild_1950c0(void *, void *);

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
