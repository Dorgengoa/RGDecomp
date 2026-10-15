#include "types.h"

/* Guards 1 and 2 are 12-byte STRUCT assignments (three lwc1 then three swc1
   -- batched).  Guard 3 is three separate member assignments (interleaved
   lwc1/swc1).  Guard 1's two arms are byte-identical in retail: they survive
   only through two DIFFERENT struct typedefs (measured on NodeSetTranslation_1866b0;
   union / static inline / array-vs-member are one object, branch folded). */

typedef unsigned __int128 u128;

typedef struct { f32 x, y, z, w; } V4;
typedef struct { f32 x, y, z; } V3;
typedef struct { f32 ex, ey, ez; } E3;
typedef union { u128 q; V3 v3; E3 e3; } Q16;

typedef struct {
    V4 a;       /* +0x00 */
    Q16 b;      /* +0x10 */
} Tmp_186490;

typedef struct {
    u8 pad00[0x0C];
    V3 r0C;     /* +0x0C */
    f32 m18;
    f32 m1C;
    f32 m20;
    V3 r24;     /* +0x24 */
    s16 m30;
    s16 m32;
    s32 m34;
    s32 m38;
} Obj_186490;

typedef struct {
    u8 pad00[0x24];
    E3 e24;
} ObjE_186490;

extern void VecSetOnes_13e180(void *p);

void NodeXformReset_186490(Obj_186490 *p)
{
    Tmp_186490 t;

    p->m32 = 1;
    p->m30 = 0;
    p->m34 = 0;
    p->m38 = 0;
    t.b.q = 0;
    VecSetOnes_13e180(&t);
    if (p->m30 != 0) {
        p->r24 = t.b.v3;
    } else {
        ((ObjE_186490 *)p)->e24 = t.b.e3;
    }
    if (p->m30 == 0) {
        p->r0C = t.b.v3;
    }
    if (p->m30 == 0) {
        p->m18 = t.a.x;
        p->m1C = t.a.y;
        p->m20 = t.a.z;
    }
}
