#include "types.h"

/* MEASURED: retail's two byte-identical arms survive only if the two arms are
   written through DIFFERENT struct typedefs (one arm casts).  A union, a
   static inline helper, an inline helper taking two aliasing union members,
   and array-vs-member indexing are all INERT -- one object sha1 0c84583d,
   with the branch folded away entirely. */

typedef struct { f32 x, y, z, w; } V4;

typedef struct { u8 pad00[0x24]; f32 qx, qy, qz; s16 m30; } ObjQ;
typedef struct { u8 pad00[0x24]; f32 ex, ey, ez; s16 m30; } ObjE;

void NodeSetTranslation_1866b0(ObjQ *p, V4 *in)
{
    if (p->m30 != 0) {
        p->qx = in->x;
        p->qy = in->y;
        p->qz = in->z;
    } else {
        ((ObjE *)p)->ex = in->x;
        ((ObjE *)p)->ey = in->y;
        ((ObjE *)p)->ez = in->z;
    }
}
