#include "types.h"

typedef rg_u128 u128;

typedef struct {
    f32 x, y, z, w;
} V4 __attribute__((aligned(16)));

extern "C" {
s32 Rand_133710(void);
f32 VecDistance_13d3d0(V4 *, V4 *);
u8 *ObjRecGetLiveObject_1c4a90(s32, s32);
s32 GetCurrentScene_1f5be0(void);
s32 GetActionMgr_1fdb50(void);
u8 *GetGameData_1fede0(void);
s32 CharaIsGroundReadyMaybe_210850(s32);
s32 ActionMgrFindById_233b50(s32, s32);
void CharaSetSrtVec40_2387c0(s32, f32, f32, f32);
void *ActorFindById_3eb870(u8 *, s32);
void SrtSetVec40Thunk_1c7170(s32, f32, f32, f32);
extern f32 D_0047D240;
void AiRollIdleOnContactMaybe_2bb770(u8 *arg0, s32 arg1, s32 arg2);
}

class VObj {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    u8 * f53() { return VCM0(u8 *, 0xDC); }
};

void AiRollIdleOnContactMaybe_2bb770(u8 *arg0, s32 arg1, s32 arg2)
{
    V4 va __attribute__((aligned(16)));
    V4 vb __attribute__((aligned(16)));
    s32 h;
    s32 m;
    u8 *a;
    u8 *b;
    u8 *g;
    VObj *e;
    u8 *r;
    s16 n;
    f32 ra;
    f32 rb;
    f32 k;
    s16 st;

    st = *(s16 *)(arg0 + 0xAE);
    if (st == 400) {
        return;
    }
    if (st == 600) {
        return;
    }
    if (st != 200) {
        return;
    }
    if (*(u8 *)(arg0 + 0x16C) != 0) {
        return;
    }
    if (arg2 != 0) {
        *(s16 *)(arg0 + 0x172) = 60;
        *(s16 *)(arg0 + 0x174) = 0;
        *(s16 *)(arg0 + 0xAC) = 600;
        return;
    }
    h = ActionMgrFindById_233b50(GetActionMgr_1fdb50(), *(s16 *)(arg0 + 0xA8));
    if (h == 0) {
        return;
    }
    if (CharaIsGroundReadyMaybe_210850(h) == 0) {
        return;
    }
    m = GetCurrentScene_1f5be0();
    a = ObjRecGetLiveObject_1c4a90(m, *(s16 *)(arg0 + 0xA8));
    if (a == 0) {
        return;
    }
    b = ObjRecGetLiveObject_1c4a90(m, arg1);
    if (b == 0) {
        return;
    }
    k = D_0047D240;
    ra = k * *(f32 *)(a + 0x4C8);
    rb = k * *(f32 *)(b + 0x4C8);
    *(u128 *)&va = *(u128 *)(a + 0x180);
    *(u128 *)&vb = *(u128 *)(b + 0x180);
    k = VecDistance_13d3d0(&va, &vb);
    if (!(0.0f + k - 0.5f * (ra + rb) <= 50.0f)) {
        return;
    }
    g = GetGameData_1fede0();
    e = (VObj *)ActorFindById_3eb870(g, *(s16 *)(arg0 + 0xA8));
    if (e == 0) {
        return;
    }
    r = e->f53();
    if (r == 0) {
        return;
    }
    n = *(s16 *)(r + 2);
    if (*(s16 *)(*(s32 *)(g + 0xC) + 0x24) == 3) {
        n <<= 1;
    }
    if (Rand_133710() % 50 < n) {
        *(s16 *)(arg0 + 0x172) = 60;
        *(s16 *)(arg0 + 0x174) = 0;
        *(s16 *)(arg0 + 0xAC) = 600;
        CharaSetSrtVec40_2387c0(h, 0.0f, 0.0f, 0.0f);
        SrtSetVec40Thunk_1c7170(h, 0.0f, 0.0f, 0.0f);
    }
}
