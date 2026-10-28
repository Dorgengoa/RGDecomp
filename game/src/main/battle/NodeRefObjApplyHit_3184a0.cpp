/* rgp:protos */
#line 1
#include "types.h"
#include "vec.h"

class Self {
public:
    u8 pad0[0x80];
    s32 unk80;
    u8 pad84[2];
    s16 unk86;
    u8 pad88[2];
    s16 unk8A;
    u8 pad8C[2];
    s16 unk8E;
    u8 pad90[0x20];
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    s32 v30(s32 a0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(s32, (void *, s32, int, int), 0x30, a0, rgp_fwd2, rgp_fwd3); }
    
    
    
    
    
    
    s32 v4C(Self * a0) { return VCM(s32, (void *, Self *), 0x4C, a0); }
    u8 padB4[4];
    s16 unkB8;
    u8 padBA[0x170 - 0xBA];
    Vec4 unk170;
};

typedef struct {
    s32 unk0;
    u8 pad4[4];
    s32 unk8;
    s32 unkC;
    s32 unk10;
    u8 pad14[0xC];
    Vec4 unk20;
    u8 pad30[4];
    s32 unk34;
    s32 unk38;
    u8 unk3C;
} Msg;

typedef struct {
    u8 pad0[0x3D0];
    s64 unk3D0;
} Actor;

struct Evt {
    f32 x, y, z, w;
    s16 id[8];
};

struct Ref {
    Self *self;
    Evt *evt;
};

extern "C" {
extern void VecCopy_1cbe30(Evt *, Vec4 *);
extern s32 GetActionMgr_1fdb50(void);
extern s32 CharaIsPlayedMotion_2124f0(Actor *, u8 *);
extern s32 CharaGetMoveReq_2149e0(Actor *);
extern Actor *ActionMgrFindById_233b50(s32, s32);
extern s32 BattleApplyHit_2ef930(Ref *);
extern void CharaMoveReqResetThunk_2194d0(s32);
extern u8 D_00462378[];
}

extern "C" s32 NodeRefObjApplyHit_3184a0(Self *self, Msg *msg, int rgp_a2, int rgp_a3)
{
    Evt e __attribute__((aligned(16)));
    Ref r __attribute__((aligned(16)));
    Actor *a;
    s32 t;

    if (self->v30(msg->unk8, (int)(long)(rgp_a2), (int)(long)(rgp_a3)) == 0) {
        return 0;
    }
    if (self->v4C(self) == 0) {
        return 0;
    }
    t = msg->unk34;
    self->unk8E = t;
    e.w = 1.0f;
    e.id[0] = -1;
    e.id[1] = -1;
    e.id[2] = -1;
    e.id[3] = -1;
    e.id[4] = -1;
    e.id[5] = -1;
    e.id[6] = -1;
    e.x = 0.0f;
    e.y = 0.0f;
    e.z = 0.0f;
    VecCopy_1cbe30(&e, &msg->unk20);
    e.id[0] = msg->unk0;
    e.id[1] = msg->unk8;
    e.id[2] = msg->unk10;
    e.id[3] = msg->unkC;
    e.id[4] = msg->unk38;
    e.id[5] = self->unkB8;
    e.id[6] = msg->unk34;
    r.self = self;
    r.evt = &e;
    if (BattleApplyHit_2ef930(&r) == 0) {
        return 0;
    }
    if (msg->unk3C != 0 && self->unk8A == 1) {
        a = ActionMgrFindById_233b50(GetActionMgr_1fdb50(), self->unk86);
        if (a != 0 && CharaIsPlayedMotion_2124f0(a, D_00462378) != 0) {
            a->unk3D0 |= 0x20000;
            CharaMoveReqResetThunk_2194d0(CharaGetMoveReq_2149e0(a));
        }
    }
    self->unk170 = msg->unk20;
    self->unk80 |= 2;
    self->unkB8++;
    return 1;
}
