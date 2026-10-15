#include "types.h"

typedef struct { s32 w[12]; } Hdr;
typedef struct { f32 x, y, z, w; } V4;
typedef struct { s16 h[10]; } H10;

typedef struct {
    Hdr a;
    V4 v;
    H10 s;
    s32 x54;
    u8 pad58[8];
} Elem;

typedef struct {
    u8 pad0[0x4C8];
    f32 m4C8;
} Sub;

typedef struct {
    u8 pad0[0x50];
    u8 m50[0x14];
    f32 m64;
    u8 pad68[0x290 - 0x68];
    Hdr a;
    V4 v;
    H10 s;
    s32 x2E4;
    u8 pad2E8[0x3D8 - 0x2E8];
    s32 m3D8;
    u8 pad3DC[0x3F4 - 0x3DC];
    Sub *m3F4;
    u8 pad3F8[0x40E - 0x3F8];
    s16 m40E;
} Obj;

extern f32 Cosf_128d30(f32);
extern f32 Sinf_128fd0(f32);
extern void SrtGetPos_1c7430(void *, V4 *);
extern s32 CollRaycastNearestFiltered_1c8500(s32, s32, s32, V4 *, V4 *, s32 *, f32, f32);
extern void VecScale_1cbca0(V4 *, V4 *, f32);
extern const f32 D_0045B080[];
extern f32 D_0047D288;
extern f32 D_0047DB14;
extern f32 D_0047DB3C;
extern f32 D_0047DB50;

void CharaCollProbeAheadMaybe_237340(Obj *obj, s32 arg1, s32 arg2)
{
    s32 p7C;
    V4 v60;
    V4 v50;
    f32 lim;
    f32 m;
    f32 h;
    f32 r;
    s32 i;
    s32 off;

    obj->m3D8 &= ~0x40;
    if (obj->m3F4 == NULL || arg1 == 0 || arg2 <= 0) {
        return;
    }
    SrtGetPos_1c7430(obj->m50, &v60);
    v50.x = Sinf_128fd0(obj->m64);
    *(s32 *)&v50.y = 0;
    v50.z = Cosf_128d30(obj->m64);
    *(s32 *)&v50.w = 0;
    m = 0.0f;
    lim = D_0047DB50 * *(f32 *)&D_0045B080[0];
    if (obj->m3F4 != NULL) {
        m = obj->m3F4->m4C8 * (D_0047DB14 * *(f32 *)&D_0045B080[0]);
    }
    r = (m > lim) ? m : lim;
    lim = D_0045B080[0];
    h = 0.5f * lim;
    VecScale_1cbca0(&v50, &v50, r + h);
    v60.y += h;
    i = CollRaycastNearestFiltered_1c8500(arg1, arg2, obj->m40E, &v60, &v50, &p7C, D_0047DB3C, D_0047D288);
    if (i < 0) {
        return;
    }
    obj->m3D8 |= 0x40;
    off = i * 0x60;
    obj->a = ((Elem *)(arg1 + off))->a;
    {
        Elem *e = (Elem *)((u8 *)off + arg1);
        obj->v = e->v;
        obj->s = e->s;
    }
    obj->x2E4 = ((Elem *)(off + (u32)arg1))->x54;
}
