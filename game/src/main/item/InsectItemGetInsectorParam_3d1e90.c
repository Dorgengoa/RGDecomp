/* rgp:protos */
#define RGP_SELF_InsectItemGetInsectorParam_3d1e90 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Ent { u8 pad000[0x4]; s32 m04; } Ent;
typedef struct Hdr { u8 pad000[0x10]; void *m10; } Hdr;

/*rgp*/

s32 InsectItemGetInsectorParam_3d1e90(Hdr *o)
{
    void *p;
    Ent *e;

    p = o->m10;
    if (p == 0) {
        return 0;
    }
    e = ((Ent *)ItemDefGetInsectData_40e0b0(p));
    if (e != 0) {
        return e->m04;
    }
    return 0;
}
