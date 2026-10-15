#include "types.h"
#include "vec.h"

typedef struct M3 {
    f32 m[16];
} M3;

typedef struct Tgt {
    u8 pad0[0x180];
    Vec4 pos;
    f32 m[16];
} Tgt;

typedef struct Pl {
    u8 pad0[0x180];
    f32 m[16];
} Pl;

typedef struct St {
    f32 f0;
    f32 f4;
    f32 f8;
    f32 fC;
    f32 f10;
    f32 f14;
    f32 f18;
    f32 f1C;
    f32 f20;
    f32 f24;
    f32 f28;
    f32 f2C;
    f32 f30;
    f32 f34;
    f32 f38;
    f32 f3C;
    f32 f40;
    s32 x44;
    s32 x48;
    u8 b4C;
    u8 pad4D[3];
    f32 f50;
} St;

typedef struct Ply {
    u8 pad0[0x18];
    u8 *x18;
} Ply;

class Cam {
public:
    u8 pad0[0xC0];
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual void d5();
    virtual void d6();
    virtual void d7();
    virtual void d8();
    virtual void d9();
    virtual void d10();
    virtual void d11();
    virtual void d12();
    virtual void d13();
    virtual void d14();
    virtual void d15();
    virtual void d16();
    virtual void d17();
    virtual void d18();
    virtual void d19();
    virtual void d20();
    virtual void d21();
    virtual void d22();
    virtual void d23();
    virtual void d24();
    virtual void d25();
    virtual void d26();
    virtual void d27();
    virtual void d28();
    virtual void d29();
    virtual void d30();
    virtual void d31();
    virtual void d32();
    virtual void d33();
    virtual void d34();
    virtual void d35();
    virtual void d36();
    virtual void d37();
    virtual void d38();
    virtual void getPos(Vec4 *v);
    virtual void getAt(Vec4 *v);
    virtual void d41();
    virtual void setPos(Vec4 *v);
    virtual void setAt(Vec4 *v);
    u8 padC4[0xE0 - 0xC4];
    Vec4 vE0;
    Vec4 vF0;
    u8 pad100[0x254 - 0x100];
    s32 i254;
    s32 i258;
};

extern "C" {
f32 fabsf(f32);
f32 Cosf_128d30(f32);
f32 Sinf_128fd0(f32);
f32 Atan2f_1291a8(f32, f32);
Pl *GetDrawCtxCamera_15de60(void);
f32 PadGetAnalogRYNorm_183b90(void *);
f32 PadGetAnalogRXNorm_183c30(void *);
Tgt *ObjRecGetLiveObject_1c4a90(s32, s32);
s32 CollSphereSweepNearest_1c8880(Vec4 *, Vec4 *, u8 *, s32, s32, Vec4 *, Vec4 *, f32 *, f32);
s32 CollTriListCompact_1ca3e0(u8 *, s32);
f32 VecDistXZ_1cb3f0(Vec4 *, Vec4 *);
void VecMinMax_1cb570(Vec4 *, Vec4 *, Vec4 *, Vec4 *);
f32 MtxInverseAffine_1cb640(void *, void *);
void VecLerpPoint_1cbac0(Vec4 *, Vec4 *, Vec4 *, f32);
void VecScale_1cbca0(Vec4 *, Vec4 *, f32);
void VecSub_1cbd00(Vec4 *, Vec4 *, Vec4 *);
void VecAdd_1cbdc0(Vec4 *, Vec4 *, Vec4 *);
void VecCopy_1cbe30(Vec4 *, Vec4 *);
f32 VecAngleXZ_1cbe60(Vec4 *, Vec4 *);
f32 AngleWrap_1cbf30(f32);
s32 MapEvQueryCollTrisMaybe_1ff1e0(u8 *, s32, Vec4 *, s32);
St *GetCameraFollowParams_1f6d80(void);
Ply *GetGameData_1fede0(void);
s32 ObjGetNthAttachPointPosSafe_23b0c0(Tgt *, s32, s32, Vec4 *);
extern u8 D_004522C0[];
extern f32 D_0045B080[];
extern f32 D_0047D5D0;
extern f32 D_0047D844;
extern u8 D_004B2570[];

void CameraTargetFollowUpdate_307340(Cam *o, s32 arg1)
{
    volatile f32 hit;
    Vec4 tgt;
    Vec4 t1;
    Vec4 t2;
    Vec4 mid;
    Vec4 pos;
    Vec4 at;
    Vec4 ref;
    f32 inv[16];
    M3 m;
    Vec4 d2;
    Vec4 d1;
    Vec4 dir;
    Vec4 dv;
    Vec4 box[2];
    u8 buf[0x6000];
    Vec4 ofs;
    Vec4 hp;
    Vec4 hn;
    Vec4 at2;
    St *st;
    Tgt *me;
    Tgt *rf;
    Tgt *t;
    Pl *pl;
    s32 dummy;
    f32 kx;
    f32 ky;
    f32 f;
    f32 old;
    f32 lo;
    f32 cr;
    f32 ang;
    f32 len;
    f32 yaw;
    f32 pit;
    f32 c;
    f32 r;
    s32 n;

    st = GetCameraFollowParams_1f6d80();
    me = ObjRecGetLiveObject_1c4a90(arg1, *(s16 *)(GetGameData_1fede0()->x18 + 0x18E));
    if (me == 0) {
        return;
    }
    kx = (f32)o->i258 * PadGetAnalogRXNorm_183c30(D_004B2570);
    ky = (f32)o->i254 * PadGetAnalogRYNorm_183b90(D_004B2570);
    rf = ObjRecGetLiveObject_1c4a90(arg1, 0x80);
    if (rf == 0) {
        return;
    }
    if (st->x44 == 2) {
        if (ObjGetNthAttachPointPosSafe_23b0c0(me, 0x82, 0, &tgt) == 0) {
            tgt = rf->pos;
        }
        t1 = rf->pos;
        tgt.y = t1.y;
    } else if (st->x44 == 1) {
        t = ObjRecGetLiveObject_1c4a90(arg1, 0x81);
        if (t == 0) {
            return;
        }
        if (ObjGetNthAttachPointPosSafe_23b0c0(t, 0x82, 0, &tgt) == 0) {
            tgt = t->pos;
        }
        t2 = rf->pos;
        VecLerpPoint_1cbac0(&tgt, &t2, &tgt, 0.25f);
    } else {
        tgt = rf->pos;
    }
    pl = GetDrawCtxCamera_15de60();
    if (pl == 0) {
        return;
    }
    o->getPos(&pos);
    o->getAt(&at);
    if (st->x44 != st->x48) {
        o->vF0 = pos;
        o->vE0 = at;
        st->x48 = st->x44;
    }
    ref = me->pos;
    ref.y += 25.0f;
    tgt.y = ref.y;
    *(M3 *)&m = *(M3 *)D_004522C0;
    m.m[0] = pl->m[0];
    m.m[1] = pl->m[1];
    m.m[2] = pl->m[3];
    m.m[4] = pl->m[4];
    m.m[5] = pl->m[5];
    m.m[6] = pl->m[7];
    m.m[8] = pl->m[8];
    m.m[9] = pl->m[9];
    m.m[10] = pl->m[11];
    m.m[12] = pl->m[12];
    m.m[13] = pl->m[13];
    m.m[14] = pl->m[15];
    MtxInverseAffine_1cb640(inv, &m);
    old = st->f38;
    lo = st->f0;
    st->f38 = (VecDistXZ_1cb3f0(&ref, &tgt) - lo) / (st->f4 - lo);
    st->f38 = 1.0f - st->f38;
    if (st->f38 < 0.0f) {
        st->f38 = 0.0f;
    }
    if (!(st->f38 <= 1.0f)) {
        st->f38 = 1.0f;
    }
    st->f38 = old + D_0047D844 * (st->f38 - old);
    VecSub_1cbd00(&d1, &ref, &pos);
    VecSub_1cbd00(&d2, &tgt, &ref);
    cr = VecAngleXZ_1cbe60(&d1, &d2);
    if (fabsf(cr) <= st->f20) {
        cr = 0.0f;
    } else {
        f = st->f20;
        f = (cr < 0.0f) ? f : -f;
        cr += f;
    }
    len = st->f8 + st->f38 * (st->fC - st->f8);
    ang = Atan2f_1291a8(pos.x - at.x, pos.z - at.z);
    pit = st->f10 + st->f38 * (st->f14 - st->f10);
    st->f3C = st->f3C + st->f24 * (st->f18 * kx - st->f3C);
    st->f40 = st->f40 + st->f28 * (-st->f1C * ky - st->f40);
    yaw = AngleWrap_1cbf30(ang + st->f3C + st->f2C * cr);
    pit = AngleWrap_1cbf30(pit + st->f40);
    dir.x = Sinf_128fd0(pit) * Sinf_128fd0(yaw);
    dir.y = -Cosf_128d30(pit);
    dir.z = Sinf_128fd0(pit) * Cosf_128d30(yaw);
    *(s32 *)&dir.w = 0;
    VecScale_1cbca0(&dir, &dir, len);
    VecLerpPoint_1cbac0(&mid, &tgt, &ref, 0.5f * st->f38);
    VecLerpPoint_1cbac0(&at, &mid, &at, st->f30);
    VecAdd_1cbdc0(&mid, &at, &dir);
    VecSub_1cbd00(&dv, &mid, &ref);
    r = D_0045B080[0];
    VecMinMax_1cb570(&box[0], &box[1], &mid, &ref);
    *(s32 *)&box[1].w = 0x3F800000;
    *(s32 *)&box[0].w = 0x3F800000;
    box[0].x += r;
    box[0].y += r;
    box[0].z += r;
    box[1].x -= r;
    box[1].y -= r;
    box[1].z -= r;
    n = CollTriListCompact_1ca3e0(buf, MapEvQueryCollTrisMaybe_1ff1e0(buf, 0x100, box, -1));
    VecCopy_1cbe30(&ofs, &pos);
    VecAdd_1cbdc0(&mid, &ref, &dv);
    VecLerpPoint_1cbac0(&ofs, &mid, &ofs, st->f34);
    if (CollSphereSweepNearest_1c8880(&hp, &hn, buf, n, 0, &ref, &dv, (f32 *)&hit, 0.25f * r) >= 0) {
        c = hit;
        c = (c > 0.0f) ? c : 0.0f;
        hit = c;
        c = (c < 1.0f) ? c : 1.0f;
        hit = c;
        VecScale_1cbca0(&dv, &dv, c);
        VecCopy_1cbe30(&at, &ref);
        st->f50 = D_0047D5D0;
    }
    VecAdd_1cbdc0(&mid, &ref, &dv);
    VecLerpPoint_1cbac0(&pos, &mid, &pos, st->f34);
    pos.y = ofs.y;
    o->getAt(&at2);
    VecSub_1cbd00(&at, &at, &at2);
    VecScale_1cbca0(&at, &at, st->f50);
    VecAdd_1cbdc0(&at, &at, &at2);
    st->f50 = st->f50 + D_0047D844;
    if (!(st->f50 <= 1.0f)) {
        st->f50 = 1.0f;
    }
    if (pos.y < ref.y) {
        pos.y = ref.y;
    }
    o->setPos(&pos);
    o->setAt(&at);
    o->vF0 = pos;
    o->vE0 = at;
    st->b4C = 0;
}
}
