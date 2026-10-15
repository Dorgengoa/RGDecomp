#include "types.h"

class Obj {
public:
    u8 pad000[0xC0];
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void v05();
    virtual void v06();
    virtual void v07();
    virtual void v08();
    virtual void v09();
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
    virtual void getPos(void *);
};

extern "C" {
s32 DrawEnvGetHeight_1451d0(s32);
s32 DrawEnvGetWidth_1451e0(s32);
s32 ProjectToScreenOffset_15d160(s32 *, void *);
s32 GetDrawCtx_15de80();
Obj *ObjRecGetLiveObject_1c3bc0(void *, s32);
f32 VecDistSq_1cb3c0(void *, void *);
void *GetCurrentScene_1f5be0();
s32 GetActionMgr_1fdb50();
void *GetGameData_1fede0(...);
s32 ActionMgrFindById_233b50(s32, s32);
void CharaGetPos_2388a0(s32, f32 *);
s32 EvDoorObjGetSidePoint_3039a0(u8 *, void *, f32 *, s32);
s32 EvDoorObjGetCursor_303b20(u8 *);
void EvDoorObjUpdateCursor_303b70(u8 *);
void DoorCursorFadeOut_304a10(s32);
u8 *DListGetHead_42ea60(u8 *);
u8 *DListGetNext_42eb30(u8 *);
}
extern f32 D_0045B080[];
extern f32 D_0047EF40;
extern f32 D_0047EF44;
extern f32 D_0047EF48;
extern f32 D_0047EF4C;

extern "C" void EventObjMgrUpdateDoorCursors_2e8060(u8 *arg0)
{
    u8 sp80[0x10];
    f32 sp70[4];
    u8 sp60[0x10];
    s32 sp50[4];
    void *w;
    Obj *o;
    void *p;
    s32 r;
    s32 h;
    s32 lim0;
    s32 lim1;
    u8 *e;
    f32 f;
    f32 dist;

    w = GetCurrentScene_1f5be0();
    o = ObjRecGetLiveObject_1c3bc0(w, *(s32 *)((u8 *)w + 0x4344));
    if (o == NULL) {
        return;
    }
    o->getPos(sp80);
    sp70[0] = D_0047EF40;
    sp70[1] = D_0047EF44;
    sp70[2] = D_0047EF48;
    sp70[3] = D_0047EF4C;
    p = GetGameData_1fede0();
    r = ActionMgrFindById_233b50(GetActionMgr_1fdb50(), *(s16 *)(*(u8 **)((u8 *)p + 0x18) + 0x18E));
    if (r != 0) {
        CharaGetPos_2388a0(r, sp70);
    }
    h = GetDrawCtx_15de80();
    lim0 = DrawEnvGetWidth_1451e0(h) << 4;
    lim1 = DrawEnvGetHeight_1451d0(h) << 4;
    e = DListGetHead_42ea60(arg0 + 0xE0);
    f = D_0045B080[0];
    f = (volatile f32)f * 45.0f;
    dist = f * f;
    while (e != NULL) {
        if (EvDoorObjGetSidePoint_3039a0(e + 0x10, sp60, sp70, -1) != 0) {
            if (!(VecDistSq_1cb3c0(sp60, sp80) <= dist) || ProjectToScreenOffset_15d160(sp50, sp60) == 0 || sp50[0] < 0 || sp50[0] >= lim0 || sp50[1] < 0 || lim1 <= sp50[1]) {
                DoorCursorFadeOut_304a10(EvDoorObjGetCursor_303b20(e + 0x10));
            }
            EvDoorObjUpdateCursor_303b70(e + 0x10);
        }
        e = DListGetNext_42eb30(e);
    }
}
