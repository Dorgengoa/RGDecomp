/* rgp:protos */
#line 1
#include "types.h"


struct V4 { f32 x, y, z, w; };
class Cam {
public:
    u8 pad0[0xC0];
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void GetPos(struct V4 * a0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { VCM(void, (void *, struct V4 *, int, int), 0xA4, a0, rgp_fwd2, rgp_fwd3); }
    void GetTgt(struct V4 * a0) { VCM(void, (void *, struct V4 *), 0xA8, a0); }
    
    void SetPos(struct V4 * a0) { VCM(void, (void *, struct V4 *), 0xB0, a0); }
    int SetTgt(struct V4 * a0) { return VCM(int, (void *, struct V4 *), 0xB4, a0); }
};

extern "C" {
void *GetGameData_1fede0(void);
void *GetActionMgr_1fdb50(void);
f32 PadGetAnalogLXNorm_183af0(void *);
f32 PadGetAnalogLYNorm_183a50(void *);
f32 PadGetAnalogRXNorm_183c30(void *);
f32 PadGetAnalogRYNorm_183b90(void *);
s32 PadIsHeld_183a20(void *, s32);
void CameraOrbitCalcMaybe_1c9020(V4 *, V4 *, V4 *, V4 *, f32, f32, f32, f32, f32);
void *ActionMgrFindById_233b50(void *, s32);
void CharaGetPos_2388a0(void *, V4 *);
void VecSub_13be40(V4 *, V4 *, V4 *);
void VecAdd_13be20(V4 *, V4 *, V4 *);
void VecNormalize_13bd90(V4 *, V4 *);
void VecScale_13be00(V4 *, V4 *, f32);
void VecCopy_1cbe30(V4 *, V4 *);
s32 MapEvCollectCollTrisNearMaybe_1ff130(void *, s32, V4 *, V4 *, s32, f32);
void VecSub_1cbd00(V4 *, V4 *, V4 *);
s32 CollRaycastNearest_1c86e0(void *, s32, s32, V4 *, V4 *, f32 *);
void VecAdd_1cbdc0(V4 *, V4 *, V4 *);
}
extern "C" f32 D_0045B078[];
extern "C" f32 D_0045B080[];
extern "C" f32 D_0045B088[];
extern "C" f32 D_0047D614;
extern "C" f32 D_0047D7CC;
extern "C" f32 D_0047D8E4;
extern "C" u8 D_004B2570[];

#define ZERO(d, n) { u8 *p_ = (u8 *)(d); u32 n_ = (n); if (p_) while (n_) { *p_ = 0; n_--; p_++; } }

extern "C" int CameraDebugFreeUpdate_305c60(Cam *self, s32 h, s32 mode, int rgp_a3) { int rgp_v0;
    f32 hit;
    V4 pos __attribute__((aligned(16)));
    V4 tgt __attribute__((aligned(16)));
    V4 in __attribute__((aligned(16)));
    V4 v __attribute__((aligned(16)));
    V4 d __attribute__((aligned(16)));
    u8 buf[0x6000] __attribute__((aligned(16)));
    __attribute__((aligned(16))) unsigned char rgp_blk1[(0x10 + sizeof(V4)) + (0x0 + sizeof(V4)) + (0x20) + (0x10)]; typedef char rgp_blk1_chk0[(0x0) + sizeof(V4) <= (0x10) && (0x0) >= 0 ? 1 : -1];
    
    V4 c70 __attribute__((aligned(16)));
    V4 c60 __attribute__((aligned(16)));
    V4 c50 __attribute__((aligned(16)));
    u8 *g;
    void *e;
    s32 n;
    f32 f;

    self->GetPos(&pos, (int)(long)(mode), (int)(long)(rgp_a3));
    self->GetTgt(&tgt);
    GetGameData_1fede0();
    GetActionMgr_1fdb50();
    ZERO(&in, 0x10);
    in.x = PadGetAnalogLXNorm_183af0(D_004B2570);
    in.y = PadGetAnalogLYNorm_183a50(D_004B2570);
    in.z = PadGetAnalogRXNorm_183c30(D_004B2570);
    in.w = PadGetAnalogRYNorm_183b90(D_004B2570);
    if (mode == 11) {
        in.y = 0.0f;
        in.x = 0.0f;
    }
    if (PadIsHeld_183a20(D_004B2570, 0x80) != 0) {
        in.x *= 40.0f;
        in.y *= 40.0f;
    } else {
        in.x *= 8.0f;
        in.y *= 8.0f;
    }
    if (PadIsHeld_183a20(D_004B2570, 1) != 0) {
        f = in.y;
        in.y = 0.0f;
        pos.y -= f;
        tgt.y -= f;
    }
    in.z *= D_0047D614;
    if (PadIsHeld_183a20(D_004B2570, 8) != 0) {
        CameraOrbitCalcMaybe_1c9020(&pos, &tgt, &pos, &tgt, in.x, in.y, in.z, 0.0f, 0.0f);
    } else if (PadIsHeld_183a20(D_004B2570, 2) != 0) {
        CameraOrbitCalcMaybe_1c9020(&pos, &tgt, &pos, &tgt, in.x, in.y, in.z, 0.0f, 12.0f * in.w);
    } else {
        CameraOrbitCalcMaybe_1c9020(&pos, &tgt, &pos, &tgt, in.x, in.y, in.z, D_0047D8E4 * in.w, 0.0f);
    }
    if (mode == 9 || mode == 10) {
        g = (u8 *)GetGameData_1fede0();
        e = ActionMgrFindById_233b50(GetActionMgr_1fdb50(), *(s16 *)(*(u8 **)(g + 0x18) + 0x18E));
        if (e != 0) {
            CharaGetPos_2388a0(e, &v);
            v.y += 25.0f;
            VecSub_13be40(&d, &v, &tgt);
            VecAdd_13be20(&pos, &pos, &d);
            VecAdd_13be20(&tgt, &tgt, &d);
            if (mode == 9) {
                VecSub_13be40(&d, &pos, &tgt);
                d.y = 0.0f;
                VecNormalize_13bd90(&d, &d);
                VecScale_13be00(&d, &d, D_0047D7CC);
                pos.x = tgt.x;
                pos.z = tgt.z;
                VecAdd_13be20(&pos, &pos, &d);
            }
        }
    }
    if (mode == 12 && PadIsHeld_183a20(D_004B2570, 1) == 0) {
        VecCopy_1cbe30(&(*(V4 *)(rgp_blk1 + 0x10)), &tgt);
        VecCopy_1cbe30(&(*(V4 *)(rgp_blk1 + 0x0)), &tgt);
        (*(V4 *)(rgp_blk1 + 0x10)).x -= 10.0f;
        (*(V4 *)(rgp_blk1 + 0x10)).y -= 20.0f + (f32)h;
        (*(V4 *)(rgp_blk1 + 0x10)).z -= 10.0f;
        (*(V4 *)(rgp_blk1 + 0x0)).x += 10.0f;
        (*(V4 *)(rgp_blk1 + 0x10)).w = 1.0f;
        (*(V4 *)(rgp_blk1 + 0x0)).w = 1.0f;
        (*(V4 *)(rgp_blk1 + 0x0)).y += 20.0f;
        (*(V4 *)(rgp_blk1 + 0x0)).z += 10.0f;
        n = MapEvCollectCollTrisNearMaybe_1ff130(buf, 0x100, &(*(V4 *)(rgp_blk1 + 0x0)), &tgt, -1, 10.0f);
        VecCopy_1cbe30(&c60, &tgt);
        c60.y -= (f32)h;
        c60.y = c60.y - 16.0f * (D_0045B088[0] * (D_0045B080[0] / (D_0045B078[0] * D_0045B078[0])));
        VecCopy_1cbe30(&c70, &c60);
        c70.y += 20.0f;
        VecSub_1cbd00(&c50, &c60, &c70);
        if (CollRaycastNearest_1c86e0(buf, n, 0, &c70, &c50, &hit) >= 0) {
            c60.y = c70.y + hit * c50.y;
        }
        c60.y += (f32)h;
        VecSub_1cbd00(&c50, &c60, &tgt);
        VecAdd_1cbdc0(&tgt, &tgt, &c50);
        VecAdd_1cbdc0(&pos, &pos, &c50);
    }
    self->SetPos(&pos);
    rgp_v0 = self->SetTgt(&tgt);
return rgp_v0; }
