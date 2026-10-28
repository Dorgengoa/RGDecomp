/* rgp:protos */
#define RGP_SELF_NodeInit_185f60 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* NodeXformReset_186490's body plus the +0x3C..+0x64 init block (same block and same
   store order as +0x1C8 in ModelObjBaseInit_1867b0). */

typedef rg_u128 u128;

typedef struct { f32 x, y, z, w; } V4;
typedef struct { f32 x, y, z; } V3;
typedef struct { f32 ex, ey, ez; } E3;
typedef union { u128 q; V3 v3; E3 e3; } Q16;

typedef struct {
    V4 a;
    Q16 b;
} Tmp_185f60;

typedef struct {
    u8 pad00[0x0C];
    V3 r0C;
    f32 m18;
    f32 m1C;
    f32 m20;
    V3 r24;
    s16 m30;
    s16 m32;
    s32 m34;
    s32 m38;
    s32 m3C;
    s32 m40;
    s32 m44;
    f32 m48;
    f32 m4C;
    s32 m50;
    s32 m54;
    f32 m58;
    f32 m5C;
    s32 m60;
    f32 m64;
} Obj_185f60;

typedef struct {
    u8 pad00[0x24];
    E3 e24;
} ObjE_185f60;

/*rgp*/
extern f32 D_0047E040;
extern f32 D_0047E050;

void NodeInit_185f60(Obj_185f60 *p)
{
    Tmp_185f60 t __attribute__((aligned(16)));
    f32 fa;
    f32 fb;

    p->m32 = 1;
    p->m30 = 0;
    p->m34 = 0;
    p->m38 = 0;
    t.b.q = 0;
    VecSetOnes_13e180(&t);
    if (p->m30 != 0) {
        p->r24 = t.b.v3;
    } else {
        ((ObjE_185f60 *)p)->e24 = t.b.e3;
    }
    if (p->m30 == 0) {
        p->r0C = t.b.v3;
    }
    if (p->m30 == 0) {
        p->m18 = t.a.x;
        p->m1C = t.a.y;
        p->m20 = t.a.z;
    }
    p->m64 = 1.0f;
    fa = D_0047E040;
    p->m3C = 0;
    fb = D_0047E050;
    p->m44 = 0;
    p->m48 = -1.0f;
    p->m4C = -1.0f;
    p->m50 = 0;
    p->m54 = 0;
    p->m58 = fa;
    p->m5C = fb;
    p->m40 = 0;
}
