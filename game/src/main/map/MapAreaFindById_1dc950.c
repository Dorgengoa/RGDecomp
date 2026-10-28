/* rgp:protos */
#define RGP_SELF_MapAreaFindById_1dc950 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void *MapAreaFindById_1dc950(void *self, s32 idx)
{
    void *r;

    if (idx < 0) {
        return NULL;
    }
    if (MapDataIsStreamActive_1e7920((int)self) == 0) {
        return NULL;
    }
    if (idx == ((short)MapDataGetId_1e7bd0(self))) {
        return self;
    }
    r = MapAreaFindShareById_1dc820(self, idx);
    if (r != NULL) {
        return r;
    }
    r = MapAreaFindBlockById_1dc760(self, idx);
    if (r != NULL) {
        return r;
    }
    return NULL;
}
