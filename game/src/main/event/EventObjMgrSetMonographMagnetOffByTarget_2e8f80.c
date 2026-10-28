/* rgp:protos */
#define RGP_SELF_EventObjMgrSetMonographMagnetOffByTarget_2e8f80 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

int EventObjMgrSetMonographMagnetOffByTarget_2e8f80(void *p, void *b, s32 n)
{ int rgp_v0 = 0;
    void *l;
    void *e;

    l = EventObjMgrGetTypeList_2e9d60(p, 5);
    e = (rgp_v0 = DListGetHead_42ea60(l));
    while (e != 0) {
        ObjTypeMonographSetMagnetOffIfTarget_3726b0((void *)((s32)e + 0x10), b, (f32)n);
        e = (rgp_v0 = DListGetNext_42eb30(e));
    }
return rgp_v0; }
