#include "types.h"
#include "vec.h"

class VO1f6a00 {
public:
    u8 pad0[0xC0];
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
    virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24();
    virtual void v25(); virtual void v26(); virtual void v27(); virtual void v28(); virtual void v29();
    virtual void v30(); virtual void v31(); virtual void v32(); virtual void v33(); virtual void v34();
    virtual void v35(); virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39();
    virtual void v40(Vec4 *);
};

typedef struct {
    f32 f0;
    f32 f4;
    u8 pad8[0x8];
    f32 m10;
    u8 pad14[0x8];
    f32 f1C;
    f32 f20;
} Cam1f6a00;

typedef struct {
    u8 pad0[0x50];
    Vec4 m50;
    Vec4 m60;
    u8 pad70[0xE0 - 0x70];
    Vec4 mE0;
    Vec4 mF0;
    u8 pad100[0x15C - 0x100];
    Cam1f6a00 cam;
} Obj1f6a00;

typedef struct {
    u8 pad0[0x18E];
    s16 m18E;
} Sub1f6a00;

typedef struct {
    u8 pad0[0x18];
    Sub1f6a00 *m18;
} Ctx1f6a00;

extern "C" {
f32 Cosf_128d30(f32);
f32 Sinf_128fd0(f32);
void CameraQueueEyeYaw_161220(Obj1f6a00 *, f32);
Obj1f6a00 *ObjRecGetLiveObject_1c3bc0(void *, s32);
void CameraWarpHookNopMaybe_1cad10(Vec4 *);
void VecScale_1cbca0(Vec4 *, Vec4 *, f32);
void VecSub_1cbd00(Vec4 *, Vec4 *, Vec4 *);
f32 AngleWrap_1cbf30(f32);
u8 *GetCurrentScene_1f5be0(void);
s32 GetActionMgr_1fdb50(void);
Ctx1f6a00 *GetGameData_1fede0(void);
s32 ActionMgrFindById_233b50(s32, s16);
void CharaGetPos_2388a0(s32, Vec4 *);
void CharaGetRot_2388b0(s32, Vec4 *);
void CameraModeUpdate_309770(Obj1f6a00 *, f32);
extern const f32 D_0047D1FC __attribute__((section(".sdata")));
extern u8 D_00481A18;
extern u8 D_00481A1C;
extern f32 D_00481A20;
}

extern "C" void CameraSnapToLeader_1f6a00(void)
{
    Vec4 a;
    Vec4 p;
    Vec4 r;
    Vec4 b;
    Vec4 m;
    Obj1f6a00 *obj;
    Ctx1f6a00 *c;
    Cam1f6a00 *cam;
    s32 h;
    u8 *g;

    g = GetCurrentScene_1f5be0();
    obj = ObjRecGetLiveObject_1c3bc0(g, *(s32 *)(g + 0x4344));
    if (D_00481A18 != 0) {
        c = GetGameData_1fede0();
        h = ActionMgrFindById_233b50(GetActionMgr_1fdb50(), c->m18->m18E);
        if (h != 0) {
            CharaGetPos_2388a0(h, &p);
            p.y += 25.0f;
            obj->m50 = p;
            obj->mE0 = p;
            CameraWarpHookNopMaybe_1cad10(&p);
        }
        D_00481A18 = 0;
    }
    if (D_00481A1C != 0) {
        c = GetGameData_1fede0();
        h = ActionMgrFindById_233b50(GetActionMgr_1fdb50(), c->m18->m18E);
        if (h != 0) {
            cam = &obj->cam;
            CharaGetRot_2388b0(h, &b);
            b.y = AngleWrap_1cbf30(b.y + D_00481A20);
            {
                Vec4 z = {0};
                z.x = Sinf_128fd0(b.y);
                z.z = Cosf_128d30(b.y);
                ((VO1f6a00 *)obj)->v40(&m);
                VecScale_1cbca0(&z, &z, 0.5f * (cam->f4 + cam->f0));
                cam->m10 = 0.0f;
                z.y -= 0.5f * (cam->f1C + cam->f20);
                VecSub_1cbd00(&r, &m, &z);
            }
            obj->m60 = r;
            obj->mF0 = r;
            CameraQueueEyeYaw_161220(obj, AngleWrap_1cbf30(D_0047D1FC + b.y));
            D_00481A20 = 0.0f;
            CameraWarpHookNopMaybe_1cad10(&r);
        }
        D_00481A1C = 0;
    }
    CameraModeUpdate_309770(obj, 1.0f);
}
