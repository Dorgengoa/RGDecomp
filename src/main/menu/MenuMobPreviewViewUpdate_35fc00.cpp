#include "types.h"
#include "vec.h"

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
    virtual void setPos(Vec4 *v);
    virtual void d40();
    virtual void d41();
    virtual void d42();
    virtual void d43();
    virtual void d44();
    virtual void d45();
    virtual void d46();
    virtual void d47();
    virtual void setF(f32 f);
    u8 padC4[0xE0 - 0xC4];
    Vec4 vE0;
    Vec4 vF0;
};

class Mdl {
public:
    u8 pad0[0x1B0];
    virtual void e0();
    virtual void e1();
    virtual void e2();
    virtual void e3();
    virtual void upd18(f32 f);
    virtual void e5();
    virtual void e6();
    virtual void e7();
    virtual void e8();
    virtual void e9();
    virtual void e10();
    virtual void e11();
    virtual void e12();
    virtual void e13();
    virtual void e14();
    virtual void upd44(f32 f);
};

typedef struct Obj {
    u8 pad0[0x5C];
    u8 x5C[0x240 - 0x5C];
    s32 x240;
    u8 pad244[0x250 - 0x244];
    Mdl *mdl;
    f32 f254;
    f32 f258;
    f32 f25C;
    f32 f260;
    f32 f264;
    f32 f268;
    u8 pad26C[0x271 - 0x26C];
    u8 x271;
} Obj;

extern "C" {
f32 Cosf_128d30(f32);
f32 Sinf_128fd0(f32);
void ModelSetRot_151080(Mdl *, Vec4 *);
void CameraSetLag_177170(Cam *, f32, f32);
s32 PadIsTriggered_1839f0(void *, s32);
s32 PadIsHeld_183a20(void *, s32);
s32 PadGetAnalogLY_184050(void *);
s32 PadGetAnalogLX_1840d0(void *);
s32 PadGetAnalogRY_184150(void *);
s32 PadGetAnalogRX_1841d0(void *);
void EffTableUpdate_1a0620(void *, f32);
s32 ReturnZero_207fe0(void);
f32 GetSceneTimeStep_293350(void);
void *memset(void *, s32, u32);
extern f32 D_0047D1FC;
extern f32 D_0047D858;
extern f32 D_0047D90C;
extern f32 D_0047DA28;
extern f32 D_0047F840;
extern f32 D_0047F844;
extern f32 D_0047F848;
extern f32 D_0047F84C;
extern f32 D_0047F850;
extern f32 D_0047F854;
extern f32 D_0047F858;
extern f32 D_0047F85C;
extern Cam *D_004823D4;
extern u8 D_004B2570[];

static inline void setAng(Mdl *m, f32 a)
{
    Vec4 r;
    u8 *p = (u8 *)&r;
    u32 n = 16;
    if (p != 0) {
        do {
            *p = 0;
            n--;
            p++;
        } while (n != 0);
    }
    r.y = a;
    r.x = 0.0f;
    r.z = 0.0f;
    ModelSetRot_151080(m, &r);
}

void MenuMobPreviewViewUpdate_35fc00(Obj *o)
{
    Vec4 up;
    Vec4 pos;
    f32 m[4][4];
    Vec4 v;
    Vec4 r;
    f32 s;
    f32 x;
    f32 y;
    f32 z;
    f32 w;
    f32 d;
    f32 *pf;
    Cam *cm;

    if (o->mdl == 0) {
        return;
    }
    cm = D_004823D4;
    if (cm != 0 && o->x271 == 0) {
        pf = (f32 *)&up;
        pf[0] = D_0047F840;
        pf[1] = D_0047F844;
        pf[2] = D_0047F848;
        pf[3] = D_0047F84C;
        pf = (f32 *)&pos;
        pf[0] = D_0047F850;
        pf[1] = D_0047F854;
        pf[2] = D_0047F858;
        pf[3] = D_0047F85C;
        if (o->x240 == 0x2EE1) {
            up.y = 36.0f;
            pos.z = 572.0f;
            pos.y = 36.0f;
        }
        cm->setPos(&pos);
        if (o->x240 == 0x2EE1) {
            s = 2.0f * GetSceneTimeStep_293350();
            if (PadGetAnalogLY_184050(D_004B2570) < -60) {
                o->f25C += s;
            }
            if (PadGetAnalogLY_184050(D_004B2570) > 60) {
                o->f25C -= s;
            }
            if (!(o->f25C <= 772.0f)) {
                o->f25C = 772.0f;
            }
            if (o->f25C < 532.0f) {
                o->f25C = 532.0f;
            }
        } else {
            s = D_0047D90C * GetSceneTimeStep_293350();
            if (PadGetAnalogLY_184050(D_004B2570) < -60) {
                o->f25C += s;
            }
            if (PadGetAnalogLY_184050(D_004B2570) > 60) {
                o->f25C -= s;
            }
            if (!(o->f25C <= 200.0f)) {
                o->f25C = 200.0f;
            }
            if (o->f25C < 130.0f) {
                o->f25C = 130.0f;
            }
        }
        s = GetSceneTimeStep_293350();
        if (PadGetAnalogRY_184150(D_004B2570) < -60) {
            o->f258 += s;
        }
        if (PadGetAnalogRY_184150(D_004B2570) > 60) {
            o->f258 -= s;
        }
        if (!(o->f258 <= 30.0f)) {
            o->f258 = 30.0f;
        }
        if (o->f258 < -30.0f) {
            o->f258 = -30.0f;
        }
        memset(m, 0, 0x40);
        m[3][3] = 1.0f;
        m[0][0] = 1.0f;
        m[1][1] = Cosf_128d30(D_0047D1FC * o->f258 / 180.0f);
        m[1][2] = Sinf_128fd0(D_0047D1FC * o->f258 / 180.0f);
        m[2][1] = -Sinf_128fd0(D_0047D1FC * o->f258 / 180.0f);
        m[2][2] = Cosf_128d30(D_0047D1FC * o->f258 / 180.0f);
        {
            u8 *p = (u8 *)&v;
            u32 n = 16;
            if (p != 0) {
                do {
                    *p = 0;
                    n--;
                    p++;
                } while (n != 0);
            }
        }
        v.x = o->f260 * o->f25C;
        v.y = o->f264 * o->f25C;
        v.z = o->f268 * o->f25C;
        w = m[3][3] + (m[0][3] * v.x + m[1][3] * v.y + m[2][3] * v.z);
        pos.x = (m[3][0] + (m[0][0] * v.x + m[1][0] * v.y + m[2][0] * v.z)) / w;
        pos.y = (m[3][1] + (m[0][1] * v.x + m[1][1] * v.y + m[2][1] * v.z)) / w;
        pos.z = (m[3][2] + (m[0][2] * v.x + m[1][2] * v.y + m[2][2] * v.z)) / w;
        D_004823D4->vE0 = up;
        D_004823D4->vF0 = pos;
        CameraSetLag_177170(D_004823D4, 1.0f, -1.0f);
        D_004823D4->setF(-1.0f);
        s = D_0047DA28 * GetSceneTimeStep_293350();
        if (PadGetAnalogRX_1841d0(D_004B2570) < -60 || PadGetAnalogLX_1840d0(D_004B2570) < -60) {
            o->f254 -= s;
        }
        if (PadGetAnalogRX_1841d0(D_004B2570) > 60 || PadGetAnalogLX_1840d0(D_004B2570) > 60) {
            o->f254 += s;
        }
        if (o->f254 <= 0.0f) {
            o->f254 = D_0047D858;
        } else if (!(o->f254 < D_0047D858)) {
            o->f254 = 0.0f;
        }
        setAng(o->mdl, o->f254);
    }
    if (ReturnZero_207fe0() != 0 && PadIsTriggered_1839f0(D_004B2570, 0x10) != 0 && PadIsHeld_183a20(D_004B2570, 8) != 0) {
        o->x271 ^= 1;
    }
    s = GetSceneTimeStep_293350() / 2.0f;
    o->mdl->upd44(s);
    o->mdl->upd18(s);
    EffTableUpdate_1a0620(o->x5C, s);
}
}
