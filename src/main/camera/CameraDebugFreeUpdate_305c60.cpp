#include "types.h"


struct V4 { f32 x, y, z, w; };
class Cam {
public:
    u8 pad0[0xC0];
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void v21();
    virtual void v22();
    virtual void v23();
    virtual void v24();
    virtual void v25();
    virtual void v26();
    virtual void v27();
    virtual void v28();
    virtual void v29();
    virtual void v30();
    virtual void v31();
    virtual void v32();
    virtual void v33();
    virtual void v34();
    virtual void v35();
    virtual void v36();
    virtual void v37();
    virtual void v38();
    virtual void GetPos(struct V4 *);
    virtual void GetTgt(struct V4 *);
    virtual void v41();
    virtual void SetPos(struct V4 *);
    virtual void SetTgt(struct V4 *);
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
extern f32 D_0045B078[];
extern f32 D_0045B080[];
extern f32 D_0045B088[];
extern f32 D_0047D614;
extern f32 D_0047D7CC;
extern f32 D_0047D8E4;
extern u8 D_004B2570[];

#define ZERO(d, n) { u8 *p_ = (u8 *)(d); u32 n_ = (n); if (p_) while (n_) { *p_ = 0; n_--; p_++; } }

extern "C" void CameraDebugFreeUpdate_305c60(Cam *self, s32 h, s32 mode) {
    f32 hit;
    V4 pos;
    V4 tgt;
    V4 in;
    V4 v;
    V4 d;
    u8 buf[0x6000];
    V4 mn;
    V4 mx;
    V4 c70;
    V4 c60;
    V4 c50;
    u8 *g;
    void *e;
    s32 n;
    f32 f;

    self->GetPos(&pos);
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
        VecCopy_1cbe30(&mn, &tgt);
        VecCopy_1cbe30(&mx, &tgt);
        mn.x -= 10.0f;
        mn.y -= 20.0f + (f32)h;
        mn.z -= 10.0f;
        mx.x += 10.0f;
        mn.w = 1.0f;
        mx.w = 1.0f;
        mx.y += 20.0f;
        mx.z += 10.0f;
        n = MapEvCollectCollTrisNearMaybe_1ff130(buf, 0x100, &mx, &tgt, -1, 10.0f);
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
    self->SetTgt(&tgt);
}
