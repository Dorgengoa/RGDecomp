/* rgp:protos */
#define RGP_SELF_EvObjLiftTargetPairInit_337000 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct { u8 pad[0x60]; void *f60; s32 f64; } T_00337000;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void EvObjLiftTargetPairInit_337000(T_00337000 *p, s32 a, s32 b, void *c, void *d, s32 e)
{
    void *r;

    TargetRefSetMapObj_2e6470(p, a, b, 0.0f);
    TargetRefSetLocalNode_2e6330((void *)((s32)p + 0x30), c, 0.0f);
    p->f64 = e;
    r = GetEventObjMgr_2d1960();
    p->f60 = EventObjMgrFindPathRecByName_2e9c90(r, d);
}
