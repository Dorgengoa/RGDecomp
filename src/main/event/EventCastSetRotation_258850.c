#include "types.h"

typedef struct {
    f32 x, y, z, w;
} V4;

typedef struct {
    s32 type;
    s32 id;
    s32 pad;
    s32 obj;
} Ent;

extern void FrameSetRot_14a390(s32, V4 *);
extern void ModelSetRot_151080(s32, V4 *);
extern void NodeSetRotation_186620(s32, V4 *);
extern s32 GetActionMgr_1fdb50(void);
extern void CharaSetYaw_2138f0(s32, f32);
extern s32 ActionMgrFindById_233b50(s32, s32);
extern void MenuWinSetRotZ_26c240(s32, f32);

s32 EventCastSetRotation_258850(Ent *arg0, s32 arg1, f32 x, f32 y, f32 z)
{
    V4 d;
    s32 h;
    s32 o;

    if (arg1 < 0 || arg1 >= 0x20) {
        return 0;
    }
    switch (arg0[arg1].type) {
    case 0:
        o = arg0[arg1].obj;
        if (o == 0) {
            return 0;
        }
        {
            V4 a = {0};
            a.x = x;
            a.z = z;
            a.y = y;
            ModelSetRot_151080(o, &a);
        }
        h = ActionMgrFindById_233b50(GetActionMgr_1fdb50(), arg0[arg1].id);
        if (h != 0) {
            CharaSetYaw_2138f0(h, y);
        }
        return 1;
    case 1:
        o = arg0[arg1].obj;
        if (o == 0) {
            return 0;
        }
        {
            V4 b = {0};
            b.x = x;
            b.z = z;
            b.y = y;
            NodeSetRotation_186620(o, &b);
        }
        return 1;
    case 3:
        o = arg0[arg1].obj;
        if (o == 0) {
            return 0;
        }
        {
            V4 c = {0};
            c.x = x;
            c.z = z;
            c.y = y;
            FrameSetRot_14a390(o, &c);
        }
        return 1;
    case 2:
        o = arg0[arg1].obj;
        if (o == 0) {
            return 0;
        }
        MenuWinSetRotZ_26c240(o, z);
        return 1;
    case 4:
        o = arg0[arg1].obj;
        if (o == 0) {
            return 0;
        }
        d.x = x;
        d.w = 1.0f;
        d.z = z;
        d.y = y;
        NodeSetRotation_186620(o, &d);
        return 1;
    default:
        return 0;
    }
}
