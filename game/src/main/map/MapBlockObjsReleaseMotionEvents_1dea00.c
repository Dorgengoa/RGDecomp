/* rgp:protos */
#define RGP_SELF_MapBlockObjsReleaseMotionEvents_1dea00 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct E_001dea00 {
    u8 pad000[0x18];
} E_001dea00;

typedef struct Obj_001dea00 {
    u8 pad000[0xC4];
    E_001dea00 *base;
    u8 pad0C8[0x2];
    s16 count;
} Obj_001dea00;

/*rgp*/
/*rgp*/

void MapBlockObjsReleaseMotionEvents_1dea00(Obj_001dea00 *o)
{
    s32 i;

    if (((unsigned char)MapDataIsLoadedOrUnloading_1e7980((int)o)) == 0) {
        return;
    }
    if (o->base == 0) {
        return;
    }
    for (i = 0; i < o->count; i++) {
        MapObjReleaseMotionEvents_1e07f0(&o->base[i]);
    }
}
