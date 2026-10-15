#include "types.h"

#undef NULL
#define NULL 0
extern "C" {
typedef struct Vec4 { f32 x, y, z, w; } Vec4;

class Cam {
public:
    u8 pad[0xC0];
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
    virtual void GetTgt(Vec4 *);
    virtual void GetPos(Vec4 *);
    virtual void d41();
    virtual void SetTgt(Vec4 *);
    virtual void SetPos(Vec4 *);
    u8 padC4[0x2A4 - 0xC4];
    f32 yaw;    /* 0x2A4 */
    f32 pitch;  /* 0x2A8 */
};

f32 Cosf_128d30(f32);
f32 Sinf_128fd0(f32);
f32 PadGetAnalogLYNorm_183a50(void *);
f32 PadGetAnalogLXNorm_183af0(void *);
f32 PadGetAnalogRYNorm_183b90(void *);
f32 PadGetAnalogRXNorm_183c30(void *);
f32 VecLengthSqXZ_1cb450(Vec4 *);
void VecScale_1cbca0(Vec4 *, Vec4 *, f32);
void VecSub_1cbd00(Vec4 *, Vec4 *, Vec4 *);
void VecAdd_1cbdc0(Vec4 *, Vec4 *, Vec4 *);
f32 AngleWrap_1cbf30(f32);
s32 GetActionMgr_1fdb50(void);
u8 *GetGameData_1fede0(void);
void CharaSetYaw_2138f0(u8 *, f32);
u8 *ActionMgrFindById_233b50(s32, s32);
void CharaGetPos_2388a0(u8 *, Vec4 *);
extern f32 D_0047D614;
extern f32 D_0047D8A8;
extern f32 D_0047D8AC;
extern u8 D_004B2570[];

#define ZERO(d, n) { u8 *p_ = (u8 *)(d); u32 n_ = (n); if (p_ != NULL) { while (n_ != 0) { *p_ = 0; n_--; p_++; } } }

void CameraFirstPersonUpdate_307f00(Cam *self) {
    Vec4 tgt;
    Vec4 pos;
    Vec4 look;
    Vec4 d;
    Vec4 off;
    u8 *sys;
    u8 *chr;
    f32 a;
    f32 b;
    f32 c;
    f32 e;
    s32 flags;
    f32 p;
    f32 mx;

    sys = GetGameData_1fede0();
    chr = ActionMgrFindById_233b50(GetActionMgr_1fdb50(), *(s16 *)(*(u8 **)(sys + 0x18) + 0x18E));
    self->GetPos(&pos);
    self->GetTgt(&tgt);
    CharaGetPos_2388a0(chr, &look);
    look.y += 32.0f;
    a = PadGetAnalogLXNorm_183af0(D_004B2570);
    b = PadGetAnalogRXNorm_183c30(D_004B2570);
    c = PadGetAnalogLYNorm_183a50(D_004B2570);
    e = PadGetAnalogRYNorm_183b90(D_004B2570);
    flags = *(s16 *)(*(u8 **)(GetGameData_1fede0() + 0xC) + 0x1A);
    if (flags & 4) {
        a *= -1.0f;
        b *= -1.0f;
    }
    if (flags & 2) {
        c *= -1.0f;
        e *= -1.0f;
    }
    self->yaw = AngleWrap_1cbf30(self->yaw - D_0047D614 * (a + b));
    p = AngleWrap_1cbf30(self->pitch - D_0047D614 * (e + c));
    mx = D_0047D8A8;
    self->pitch = p;
    if (p > mx) {
        self->pitch = mx;
    }
    p = self->pitch;
    if (p < D_0047D8AC) {
        self->pitch = D_0047D8AC;
    }
    VecSub_1cbd00(&d, &look, &tgt);
    VecScale_1cbca0(&d, &d, 0.25f);
    VecAdd_1cbdc0(&tgt, &tgt, &d);
    if (VecLengthSqXZ_1cb450(&d) > 1.0f) {
        self->pitch *= 0.75f;
    }
    ZERO(&off, 0x10)
    off.x = 5.0f * Sinf_128fd0(self->yaw) * Cosf_128d30(self->pitch);
    off.y = 5.0f * Sinf_128fd0(self->pitch);
    off.z = 5.0f * Cosf_128d30(self->yaw) * Cosf_128d30(self->pitch);
    VecAdd_1cbdc0(&pos, &tgt, &off);
    CharaSetYaw_2138f0(chr, self->yaw);
    self->SetPos(&pos);
    self->SetTgt(&tgt);
}
}
