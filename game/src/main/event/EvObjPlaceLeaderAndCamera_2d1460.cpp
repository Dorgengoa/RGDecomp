/* rgp:protos */
#line 1
/* PARKED s17b: not attempted, no draft read yet this session. See
   asm/matchings/main/EvObjPlaceLeaderAndCamera_2d1460.s and build/b_drafts/EvObjPlaceLeaderAndCamera_2d1460.txt
   (m2c draft already generated, just not worked). */
/* s49m: 20 bad (right length) */
#include "types.h"
#include "vec.h"

struct Cam {
    u8 pad0[0x60];
    Vec4 m60;
    u8 pad70[0x50];
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void getpos(Vec4 * a0) { VCM(void, (void *, Vec4 *), 0xA4, a0); }  /* +0xA4 */
};

typedef struct V4 {
    f32 x, y, z, w;
} V4;

extern "C" {
u8 *GetCurrentScene_1f5be0(void);
Cam *ObjRecGetLiveObject_1c3bc0(u8 *, s32);
s32 EvObjLiftVolumeContainsPoint_335e50(u8 *, Vec4 *);
u8 *GetGameData_1fede0(void);
s32 GetActionMgr_1fdb50(void);
s32 ActionMgrFindById_233b50(s32, s32);
void MatFromRotPos_1caf90(Mtx4 *, Vec4 *, Vec4 *);
s32 EvObjGetXform_2f9c90(u8 *);
void XformGetUnscaledMatrix_2e7760(s32, Mtx4 *);
void MatMul_1cb700(Mtx4 *, Mtx4 *, Mtx4 *);
f32 Atan2f_1291a8(f32, f32);
void CharaSetPos_213a40(s32, Vec4 *);
void CharaSetYaw_2138f0(s32, f32);
void CharaResetBattleStateMaybe_212f20(s32, s32);
void CharaAddFlags_212460(s32, long long);
void MatMulPoint_1cb8e0(Vec4 *, Mtx4 *, Vec4 *);
void CameraQueueEyeYaw_161220(Cam *, f32);
void ScreenFadeReset_1cf760(u8 *);
void ScreenFadeCaptureFrame_1cf550(u8 *);
void ScreenFadeDissolveIn_1cf720(u8 *, s32, f32);
}
extern "C" f32 D_0045B080[4];
extern "C" V4 D_0047EE30 __attribute__((section(".sdata")));
extern "C" V4 D_0047EE40 __attribute__((section(".sdata")));

extern "C" void EvObjPlaceLeaderAndCamera_2d1460(u8 *self)
{
    Vec4 v100 __attribute__((aligned(16)));
    Mtx4 mC0 __attribute__((aligned(16)));
    Mtx4 m80 __attribute__((aligned(16)));
    Vec4 v70 __attribute__((aligned(16)));
    Vec4 v60 __attribute__((aligned(16)));
    Vec4 *p;
    u8 *g;
    Cam *cam;
    u8 *q;
    s32 r;
    f32 s;
    f32 ang;

    if (self == 0) {
        return;
    }
    if (!(*(s32 *)(self + 0xD0) & 0x2000)) {
        return;
    }
    g = GetCurrentScene_1f5be0();
    cam = ObjRecGetLiveObject_1c3bc0(g, *(s32 *)(g + 0x4344));
    if (cam == 0) {
        return;
    }
    cam->getpos(&v100);
    if (EvObjLiftVolumeContainsPoint_335e50(self, &v100) != 0) {
        return;
    }
    q = GetGameData_1fede0();
    r = ActionMgrFindById_233b50(GetActionMgr_1fdb50(), *(s16 *)(*(u8 **)(q + 0x18) + 0x18E));
    if (r == 0) {
        return;
    }
    { f32 *pa = (f32 *)&v70; pa[0] = D_0047EE30.x; pa[1] = D_0047EE30.y; pa[2] = D_0047EE30.z; pa[3] = D_0047EE30.w; }
    { f32 *pb = (f32 *)&v60; pb[0] = D_0047EE40.x; pb[1] = D_0047EE40.y; pb[2] = D_0047EE40.z; pb[3] = D_0047EE40.w; }
    s = D_0045B080[0];
    p = &v60;
    p->x = -1.75f * s;
    p->z = 0.75f * s;
    MatFromRotPos_1caf90(&m80, &v70, &v60);
    XformGetUnscaledMatrix_2e7760(EvObjGetXform_2f9c90(self), &mC0);
    MatMul_1cb700(&m80, &mC0, &m80);
    ang = Atan2f_1291a8(m80.r[2].x, m80.r[2].z);
    CharaSetPos_213a40(r, &m80.r[3]);
    CharaSetYaw_2138f0(r, ang);
    CharaResetBattleStateMaybe_212f20(r, 1);
    CharaAddFlags_212460(r, (long long)(0x802));
    v100.x = 0.0f;
    v100.y = v100.y - m80.r[3].y;
    v100.z = -2.0f * s;
    v100.w = 1.0f;
    MatMulPoint_1cb8e0(&v100, &mC0, &v100);
    CameraQueueEyeYaw_161220(cam, Atan2f_1291a8(v100.x - m80.r[3].x, v100.z - m80.r[3].z));
    cam->m60 = v100;
    *(Vec4 *)((u8 *)cam + 0xF0) = v100;
    ScreenFadeReset_1cf760(g);
    ScreenFadeCaptureFrame_1cf550(g);
    ScreenFadeDissolveIn_1cf720(g, 0xF, 1.0f);
}
