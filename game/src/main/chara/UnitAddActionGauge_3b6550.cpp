/* rgp:protos */
#line 1
#include "types.h"

extern "C" {
extern const struct rgp_anon_D_00465CD0 { s32 v; s32 pad[3]; } D_00465CD0;
extern struct rgp_anon_D_00465CD8 { s32 v; s32 pad[3]; } D_00465CD8;
extern void * ActorCastToChara_3b87b0(void *, int, int, int);
extern s32 CharaIsPartyLeader_3ae1a0(void *);
extern void *GetCurrentScene_1f5be0(void);
extern void ActionPacketReset_3e3d00(void *req);
extern void ActionPacketInitGaugeEmpty_3e3030(void *req, void *x, void *o);
extern void EventFireTriggers_3e2660(void *req, s32 z);
}

class C {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v153(f32 a0) { return VCM(s32, (void *, f32), 0x26C, a0); }
    u8 pad4[0x1C0 - 4];
    bool f0 : 1;
    f32 val;
    bool g0 : 1;
};

extern "C" s32 UnitAddActionGauge_3b6550(C *o, s32 n)
{
    return o->v153((f32)((s32)o->val + n));
}

extern "C" s32 func_003B6580(C *o, f32 v, int rgp_a1, int rgp_a2, int rgp_a3)
{
    f32 lim;
    s32 m;
    s32 r;
    void *p;
    void *x;
    u8 req[0x30] __attribute__((aligned(16)));
    r = o->f0;
    o->val = v;
    m = D_00465CD0.v;
    if (!(o->val < (f32)m)) {
        o->val = (f32)m;
        o->f0 = true;
        o->g0 = false;
    }
    if (o->val <= 0.0f) {
        lim = (f32)D_00465CD8.v;
        if (o->val < lim) o->val = lim;
        o->f0 = false;
        o->g0 = true;
        p = ActorCastToChara_3b87b0(o, (int)rgp_a1, (int)rgp_a2, (int)rgp_a3);
        if (p != 0 && CharaIsPartyLeader_3ae1a0(p) != 0) {
            x = GetCurrentScene_1f5be0();
            ActionPacketReset_3e3d00(req);
            ActionPacketInitGaugeEmpty_3e3030(req, x, o);
            EventFireTriggers_3e2660(req, 0);
        }
    }
    return r;
}
