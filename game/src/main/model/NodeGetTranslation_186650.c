/* rgp:protos */
#define RGP_SELF_NodeGetTranslation_186650 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct { f32 x, y, z, w; } V4;

typedef struct { u8 pad00[0x24]; f32 qx, qy, qz; s16 m30; } ObjQ;
typedef struct { u8 pad00[0x24]; f32 ex, ey, ez; s16 m30; } ObjE;

void NodeGetTranslation_186650(ObjQ *p, V4 *out)
{
    if (p->m30 != 0) {
        out->x = p->qx;
        out->y = p->qy;
        out->z = p->qz;
        out->w = 1.0f;
    } else {
        out->x = ((ObjE *)p)->ex;
        out->y = ((ObjE *)p)->ey;
        out->z = ((ObjE *)p)->ez;
        out->w = 1.0f;
    }
}
