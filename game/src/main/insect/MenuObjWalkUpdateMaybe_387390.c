/* rgp:protos */
#define RGP_SELF_MenuObjWalkUpdateMaybe_387390 1
#define RGP_SELF_nz 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#include "vec.h"


typedef struct V4 {
    f32 x, y, z, w;
} V4;

typedef struct Prm {
    f32 f0;
    f32 f4;
    f32 f8;
    f32 fC;
    f32 f10;
    f32 f14;
    u8 pad[0x128];
} Prm;

typedef struct Node {
    u8 pad[0x20];
    struct Node *next;
} Node;

typedef struct Obj {
    u8 pad0[0x180];
    Vec4 v180;
    Vec4 v190;
    u8 pad1A0[0x968 - 0x1A0];
    Node *p968;
    u8 pad96C[0x984 - 0x96C];
    s8 b984;
    s8 b985;
    u8 pad986[0x990 - 0x986];
    u8 sub990[0x20];
    s32 f9B0;
    s32 f9B4;
    s32 f9B8;
    s32 f9BC;
    s32 f9C0;
    void *f9C4;
    void *f9C8;
} Obj;

void *memset(void *, s32, u32);
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern f32 D_0047D2D0;
extern f32 D_0047D3E8;
extern f32 D_0047D404;
extern f32 D_0047D434;
extern f32 D_0047D438;
extern f32 D_0047D43C;
extern f32 D_0047D44C;
extern f32 D_0047D450;
extern f32 D_0047FCB0, D_0047FCB4, D_0047FCB8, D_0047FCBC;
extern f32 D_0047FCC0, D_0047FCC4, D_0047FCC8, D_0047FCCC;
extern s32 D_004832B8;
extern u8 D_00464108[];
extern u8 D_00464110[];

static inline s32 nz(void *p) { return p != 0; }

void MenuObjWalkUpdateMaybe_387390(Obj *o, s32 a1, s32 a2) {
    Prm p __attribute__((aligned(16)));
    Vec4 v0 __attribute__((aligned(16)));
    Vec4 t __attribute__((aligned(16)));
    Vec4 q __attribute__((aligned(16)));
    Vec4 r __attribute__((aligned(16)));
    Vec4 s __attribute__((aligned(16)));
    Vec4 v1 __attribute__((aligned(16)));
    V4 u __attribute__((aligned(16)));
    V4 w __attribute__((aligned(16)));
    f32 ang;
    f32 cur;
    f32 d;
    s32 done;
    void *x;
    u8 f;

    if (o->b985 == 0 || a1 == 0 || a2 <= 0) return;
    memset(&p, 0, 0x140);
    p.f0 = D_0047D438;
    p.f4 = D_0047D438;
    p.f8 = 0.75f * MenuObjGetMarkerHeight_387170(o);
    if (o->b984) p.f8 = 0.5f * MenuObjGetMarkerHeight_387170(o);
    p.fC = 0.5f * p.f8;
    p.f14 = 1.0f;
    v0 = o->v180;
    v1 = o->v190;
    MenuObjGetMoveDirMaybe_386fe0(o, &q, &r);
    if (o->b984) {
        p.f14 = D_0047D3E8;
    } else {
        q.y += D_0047D43C;
    }
    *(u128 *)&s = *(u128 *)&q;
    CollMoveCharacterMaybe_16e530(&v0, &q, &t, &p, a1, a2, 0);
    { f32 ty = *(volatile f32 *)&t.y; f32 lim = *(volatile f32 *)&D_0047D44C; if (ty < lim) t.y = lim; }
    if (!(t.y <= 10.0f)) t.y = 10.0f;
    ModelSetPos_151110(o, &t);
    switch (o->f9B0) {
    case 0:
        break;
    case 1:
        goto mode1;
    default:
        return;
    }
    if (D_0047D3E8 < VecLengthXZ_13d470(&q)) {
        ang = Atan2f_1291a8(q.x, q.z);
        { f32 *p_ = (f32 *)&u; p_[0] = D_0047FCB0; p_[1] = D_0047FCB4; p_[2] = D_0047FCB8; p_[3] = D_0047FCBC; }
        u.y = ang;
        cur = v1.y;
        while (cur < 0.0f) cur += *(const f32 *)&D_0047D434;
        { f32 k2 = *(volatile f32 *)&D_0047D434; while (ang < 0.0f) ang += k2; }
        d = ang - cur;
        d = (d < 0.0f) ? -d : d;
        if (d < D_0047D404) {
            u.y = AngleStepToward_13c150((*(volatile f32 *)&v1.y), u.y, *(volatile f32 *)&D_0047D2D0, 0);
        } else {
            u.y = AngleStepToward_13c150((*(volatile f32 *)&v1.y), u.y, *(volatile f32 *)&D_0047D450, 0);
        }
        ModelSetRot_151080(o, &u);
    } else if (0.0f < VecLength_13d4a0(&s)) {
        ang = Atan2f_1291a8(s.x, s.z);
        { f32 *p_ = (f32 *)&w; p_[0] = D_0047FCC0; p_[1] = D_0047FCC4; p_[2] = D_0047FCC8; p_[3] = D_0047FCCC; }
        w.y = ang;
        cur = v1.y;
        while (cur < 0.0f) cur += *(const f32 *)&D_0047D434;
        { f32 k2 = *(volatile f32 *)&D_0047D434; while (ang < 0.0f) ang += k2; }
        d = ang - cur;
        d = (d < 0.0f) ? -d : d;
        if (d < D_0047D404) {
            w.y = AngleStepToward_13c150((*(volatile f32 *)&v1.y), w.y, *(volatile f32 *)&D_0047D2D0, 0);
        } else {
            w.y = AngleStepToward_13c150((*(volatile f32 *)&v1.y), w.y, *(volatile f32 *)&D_0047D450, 0);
        }
        ModelSetRot_151080(o, &w);
    }
    ModelObjPlayMotionByName_1867a0(o, D_00464110, 0);
    done = 0;
    if (o->p968 != 0) {
        d = VecDistanceXZ_13d390(&t, &r);
        o->f9BC++;
        if (d < 1.0f || o->f9BC > 0xF0) {
            o->f9BC = 0;
            o->p968 = o->p968->next;
            MenuObjParamsRollSpeed_387ea0(o->sub990);
            if (o->p968 == 0) done = 1;
        }
    } else {
        done = 1;
    }
    if (!done) return;
    if (o->f9B8 <= 0) {
        o->f9B0 = 1;
        MenuObjParamsRollTime_387f60(o->sub990);
        return;
    }
    f = o->f9C4 != 0;
    if (f != 0) {
        x = o->f9C4;
    } else {
        f = o->f9C8 != 0;
        if (f != 0) {
            x = o->f9C8;
        } else {
            x = 0;
        }
    }
    if (x != 0) o->f9B0 = 0;
    MenuObjBuildRandomRoute_3871a0(o, &D_004832B8, 4);
    o->f9B8--;
    return;
mode1:
    ModelObjPlayMotionByName_1867a0(o, D_00464108, 0);
    if (--o->f9B4 > 0) return;
    o->f9B0 = 0;
    MenuObjParamsRollCountMaybe_387ef0(o->sub990);
    MenuObjBuildRandomRoute_3871a0(o, &D_004832B8, 4);
    MenuObjGetMoveDirMaybe_386fe0(o, &q, &r);
}
