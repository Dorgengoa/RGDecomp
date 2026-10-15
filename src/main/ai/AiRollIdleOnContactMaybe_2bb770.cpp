#include "types.h"

typedef unsigned __int128 u128;

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
    virtual void d39();
    virtual void d40();
    virtual void d41();
    virtual void d42();
    virtual void d43();
    virtual void d44();
    virtual void d45();
    virtual void d46();
    virtual void d47();
    virtual void d48();
    virtual void d49();
    virtual void d50();
    virtual void d51();
    virtual void d52();
    virtual u8 *f53();
};

void AiRollIdleOnContactMaybe_2bb770(u8 *arg0, s32 arg1, s32 arg2)
{
    V4 va;
    V4 vb;
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
