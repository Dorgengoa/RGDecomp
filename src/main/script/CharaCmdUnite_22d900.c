#include "types.h"
#include "vec.h"

typedef struct Info {
    u8 pad0[4];
    s32 f4;
    u8 pad8[0x20];
    s8 f28;
} Info;

typedef struct Conn {
    u8 pad0[0xA44];
    u32 fA44;
} Conn;

typedef struct Blk {
    s32 a;
    s32 b;
    s32 c;
    s32 d;
} Blk;

extern void FrameSetDirty_14a5e0(Info *);
extern void ModelSetRot_151080(void *, Blk *);
extern void ModelSetPos_151110(void *, volatile Vec4 *);
extern Info *ModelGetRootFrame_1511a0(void *);
extern void *ObjRecGetLiveObject_1c4a90(void *, s32);
extern s32 GetObjNodeByName_1ce3a0(s32, s32, s32);
extern s32 GetLiveObjById_1ce420(s32, s32);
extern void *GetCurrentScene_1f5be0(void);
extern void *GetActionMgr_1fdb50(void);
extern void CharaSetYaw_2138f0(Conn *, f32);
extern void CharaSetPosXYZ_2139e0(Conn *, f32, f32, f32);
extern Conn *ActionMgrFindById_233b50(void *, s32);
extern s32 ScriptArgGetStr_302cb0(u8 *);
extern s32 ScriptArgGetInt_302d70(u8 *);
extern f32 D_0047E690;
extern f32 D_0047E694;
extern f32 D_0047E698;
extern f32 D_0047E69C;
static inline void clr(void *p, s32 n)
{
    u8 *q = (u8 *)p;
    if (q != NULL) {
        do {
            *q++ = 0;
        } while (--n != 0);
    }
}

s32 CharaCmdUnite_22d900(s32 pad0, u8 *arg1, s32 arg2)
{
    volatile Vec4 v;
    Blk b;
    void *mgr;
    void *slot;
    Info *info;
    Conn *conn;
    s32 hi;
    s32 lo;
    s32 fl;
    u8 *p;
    volatile Vec4 *vp;
    u32 n;

    if (arg2 != 4) {
        return 0;
    }
    mgr = GetCurrentScene_1f5be0();
    if (mgr == NULL) {
        return 1;
    }
    slot = ObjRecGetLiveObject_1c4a90(mgr, ScriptArgGetInt_302d70(arg1));
    if (slot == NULL) {
        return 1;
    }
    info = ModelGetRootFrame_1511a0(slot);
    if (info->f28 != 0) {
        info->f4 = 0;
    }
    hi = ScriptArgGetInt_302d70(arg1 + 5);
    lo = ScriptArgGetInt_302d70(arg1 + 0xA);
    fl = ScriptArgGetStr_302cb0(arg1 + 0xF);
    if (GetLiveObjById_1ce420(hi, lo) == 0) {
        return 1;
    }
    fl = GetObjNodeByName_1ce3a0(hi, lo, fl);
    if (fl != 0) {
        info = ModelGetRootFrame_1511a0(slot);
        info->f28 = 1;
        info->f4 = fl;
        FrameSetDirty_14a5e0(info);
        vp = (Vec4 *)&v;
        vp->x = D_0047E690;
        vp->y = D_0047E694;
        vp->z = D_0047E698;
        vp->w = D_0047E69C;
        vp->x = 0.0f;
        vp->y = 0.0f;
        vp->z = 0.0f;
        ModelSetPos_151110(slot, vp);
        p = (u8 *)&b;
        n = 16;
        if (p != NULL) {
            do {
                *p = 0;
                n--;
                p++;
            } while (n != 0);
        }
        b.a = 0;
        b.b = 0;
        b.c = 0;
        ModelSetRot_151080(slot, &b);
    }
    mgr = GetActionMgr_1fdb50();
    conn = ActionMgrFindById_233b50(mgr, ScriptArgGetInt_302d70(arg1));
    if (conn != NULL) {
        conn->fA44 |= 0x80000;
        CharaSetPosXYZ_2139e0(conn, 0.0f, 0.0f, 0.0f);
        CharaSetYaw_2138f0(conn, 0.0f);
    }
    return 1;
}
