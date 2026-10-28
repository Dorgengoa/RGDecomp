/* rgp:protos */
#line 1
#include "types.h"

#undef NULL
#define NULL 0
extern "C" {
typedef struct Vec4 { f32 x, y, z, w; } Vec4;

class Cam {
public:
    u8 pad[0xC0];
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void GetTgt(Vec4 * a0) { VCM(void, (void *, Vec4 *), 0xA4, a0); }
    void GetPos(Vec4 * a0) { VCM(void, (void *, Vec4 *), 0xA8, a0); }
    
    int SetTgt(Vec4 * a0) { return VCM(int, (void *, Vec4 *), 0xB0, a0); }
    void SetPos(Vec4 * a0) { VCM(void, (void *, Vec4 *), 0xB4, a0); }
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
f32 VecLengthSqXZ_1cb450(Vec4 *, void *);
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

int CameraFirstPersonUpdate_307f00(Cam *self) { int rgp_v0;
    Vec4 tgt __attribute__((aligned(16)));
    Vec4 pos __attribute__((aligned(16)));
    Vec4 look __attribute__((aligned(16)));
    Vec4 d __attribute__((aligned(16)));
    Vec4 off __attribute__((aligned(16)));
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
    if (VecLengthSqXZ_1cb450(&d, 0) > 1.0f) {
        self->pitch *= 0.75f;
    }
    ZERO(&off, 0x10)
    off.x = 5.0f * Sinf_128fd0(self->yaw) * Cosf_128d30(self->pitch);
    off.y = 5.0f * Sinf_128fd0(self->pitch);
    off.z = 5.0f * Cosf_128d30(self->yaw) * Cosf_128d30(self->pitch);
    VecAdd_1cbdc0(&pos, &tgt, &off);
    CharaSetYaw_2138f0(chr, self->yaw);
    self->SetPos(&pos);
    rgp_v0 = self->SetTgt(&tgt);
return rgp_v0; }
}
