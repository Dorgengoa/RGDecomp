/* rgp:protos */
#define RGP_SELF_ObjTypeVehicleTargetPairInit_3386b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct { u8 pad[0x60]; void *f60; } T_003386b0;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void ObjTypeVehicleTargetPairInit_3386b0(T_003386b0 *p, s32 a, s32 b, void *c, void *d)
{
    void *r;

    TargetRefSetLocalNode_2e6330(p, c, 0.0f);
    TargetRefSetMapObj_2e6470((void *)((s32)p + 0x30), a, b, 0.0f);
    r = GetEventObjMgr_2d1960();
    p->f60 = EventObjMgrFindPathRecByName_2e9c90(r, d);
}
