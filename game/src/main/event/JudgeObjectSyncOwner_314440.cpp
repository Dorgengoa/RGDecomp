/* rgp:protos */
#line 1
#include "types.h"

class Unit00314440 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v19C(s32 a0) { return VCM(s32, (void *, s32), 0x19C, a0); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void v280(void * a0) { VCM(void, (void *, void *), 0x280, a0); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v424() { return VCM0(s32, 0x424); }
};

typedef struct {
    u8 pad0[0x10];
    s16 unk10;
    u8 pad12[2];
    s16 unk14;
    u8 pad16[0x7C - 0x16];
    s32 unk7C;
    u8 pad80[6];
    s16 unk86;
    u8 pad88[2];
    s16 unk8A;
    u8 pad8C[0xB4 - 0x8C];
    s16 unkB4;
    s16 unkB6;
} Obj00314440;

extern "C" {
s32 GetGameData_1fede0();
s32 IsInBattle_288420(void);
Unit00314440 * ActorCastToUnit_3b8770(Unit00314440 *, int, int, int);
Unit00314440 * ActorCastToChara_3b87b0(Unit00314440 *, int, int, int);
Unit00314440 *ActorFindById_3eb870(s32, s32);
}

extern "C" void JudgeObjectSyncOwner_314440(Obj00314440 *arg0)
{
    Unit00314440 *o;
    Unit00314440 *q;

    switch (arg0->unk8A) {
    case 1:
        if (arg0->unk14 == 0) {
            return;
        }
        if (((unsigned char)IsInBattle_288420()) == 0) {
            break;
        }
        o = ActorFindById_3eb870(GetGameData_1fede0(), arg0->unk86);
        if (o == NULL) {
            arg0->unkB6 = 1;
            return;
        }
        if (o->v19C(3) != 0) {
            arg0->unk7C |= 0x100;
        }
        q = ActorCastToChara_3b87b0(o, 0, 0, 0);
        if (q != NULL) {
            q->v280(&arg0->unk10);
        }
        o = ActorCastToUnit_3b8770(o, 0, 0, 0);
        if (o == NULL) {
            break;
        }
        o->v280(&arg0->unk10);
        if (!(arg0->unk7C & 0x800) && o->v424() != 0) {
            arg0->unk7C |= 0x200;
        }
        break;
    case 2:
        break;
    }

    arg0->unk10 = arg0->unkB4;
}
