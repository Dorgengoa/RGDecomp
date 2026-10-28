/* rgp:protos */
#define RGP_SELF_MapBlockShowObjs_1de910 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct E_001de910 {
    u8 pad000[0x18];
} E_001de910;

typedef struct Obj_001de910 {
    u8 pad000[0xC4];
    E_001de910 *base;
    u8 pad0C8[0x2];
    s16 count;
} Obj_001de910;

/*rgp*/
/*rgp*/

void MapBlockShowObjs_1de910(Obj_001de910 *o)
{
    s32 i;

    if (((unsigned char)MapDataIsLoadedOrUnloading_1e7980((int)o)) == 0) {
        return;
    }
    if (o->base == 0) {
        return;
    }
    for (i = 0; i < o->count; i++) {
        MapObjShow_1e05e0(&o->base[i]);
    }
}
