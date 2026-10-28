/* rgp:protos */
#line 1
#pragma optimization_level 3
#include "types.h"
#pragma opt_common_subs off

class Node {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    void v40() { VCM0(void, 0x40); }
    
    void v48() { VCM0(void, 0x48); }
    
    
    
    s32 v58() { return VCM0(s32, 0x58); }
    s32 v5C() { return VCM0(s32, 0x5C); }
};

class Chk {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v3D0() { return VCM0(s32, 0x3D0); }
};

typedef struct {
    s16 a;
    s16 b;
    s16 c;
    s16 d;
    s16 e;
    s16 f;
    u8 pad[4];
} Rec;

typedef struct {
    u8 pad0[0x23C];
    Rec *unk23C;
    s32 unk240;
} Obj;

typedef struct {
    u8 pad0[0x10];
    s16 *unk10;
} Arg3;

extern "C" {
extern void CharaIsPartyLeader_3ae1a0(s32);
extern Chk * ActorCastToUnit_3b8770(Node *, int, int, int);
extern s32 ActorCastToChara_3b87b0(Node *, int, int, int);
extern Node *ActorFindById_3eb870(s32, s32);
extern s32 D_00465C88[];
extern s32 D_004837C0;
}

extern "C" s32 BattleRecordDefeat_3a3410(Obj *arg0, s32 arg1, s32 arg2, Arg3 *arg3, s16 *arg4)
{
    Node *n0;
    Node *n1;
    Chk *c;
    s32 r;
    s32 id0;
    s32 id1;
    s32 id2;
    s32 id3;
    s16 x;
    s16 y;
    Rec *e;

    if (arg0->unk240 >= D_00465C88[0]) {
        return 0;
    }
    n0 = ActorFindById_3eb870(D_004837C0, arg1);
    if (n0 == 0) {
        return 0;
    }
    id0 = n0->v5C();
    id1 = n0->v58();
    n0->v48();
    n1 = ActorFindById_3eb870(D_004837C0, arg2);
    id3 = id2 = -1;
    if (n1 != 0) {
        id2 = n1->v5C();
        id3 = n1->v58();
        n1->v40();
        r = ActorCastToChara_3b87b0(n1, 0, 0, 0);
        if (r != 0) {
            CharaIsPartyLeader_3ae1a0(r);
        }
    }
    if (id0 == 0x30DB) {
        return 1;
    }
    c = ActorCastToUnit_3b8770(n0, 0, 0, 0);
    if (c != 0 && c->v3D0() != 0) {
        return 1;
    }
    x = -1;
    if (arg3 != 0) {
        x = *arg3->unk10;
    }
    y = -1;
    if (arg4 != 0) {
        y = *arg4;
    }
    r = arg0->unk240;
    arg0->unk240 = arg0->unk240 + 1;
    e = &arg0->unk23C[r];
    e->a = id0;
    e->b = id1;
    e->c = id2;
    e->d = id3;
    e->e = x;
    e->f = y;
    return 1;
}
