/* PARKED s17b: m2c fails outright (jump table not provided). Not attempted. */
/* s49m: MATCH (jtbl, rodata_check) */
#include "types.h"

class Obj {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void f464(s32 a0) { VCM(void, (void *, s32), 0x464, a0); }
    u8 pad4[8];
    s32 id;
    u8 pad10[0x234 - 0x10];
    u8 b0 : 1;
    u8 b1 : 1;
};

typedef struct G {
    u8 pad0[0x94];
    u8 *unk94;
    u8 pad98[2];
    unsigned char f0 : 1;
    unsigned char f1 : 1;
    unsigned char f2 : 1;
} __attribute__((aligned(8))) G;

extern "C" G *D_004830F8;
extern "C" s32 VariantGetInt_15f780(s32);
extern "C" Obj *CharaMgrPoolFindByDataId_3a8a70(s32, s32, s32, s32, s32, s32, s32);
extern "C" void PartyRemoveMember_3c0fa0(s32, s32, s32, s32);
extern "C" void PartyAddMember_3c1430(s32, s32, s32);
extern "C" void PartyPromoteReserve_3c17c0(s32, s32, s32, s32);
extern "C" void PartySetLeader_3c1600(s32, s32, s32);
extern "C" void PartyMoveToReserve_3c19b0(s32, s32, s32, s32);
extern "C" void CharaSetFlag234Bit2Related_3ae370(Obj *, s32);

extern "C" s32 WorldDataCmdSetPartyMember_3b9b00(s64 *arg0)
{
    G *g;
    s32 a;
    u32 k;
    Obj *obj;
    s32 id;

    g = D_004830F8;
    if (!g->f2) {
        return 1;
    }
    a = VariantGetInt_15f780((s32)arg0++);
    k = VariantGetInt_15f780((s32)arg0);
    obj = CharaMgrPoolFindByDataId_3a8a70(*(s32 *)(g->unk94 + 0x14), a, 1, 1, 0, 0, 0);
    if (obj == NULL) {
        return 1;
    }
    id = obj->id;
    *(s16 *)((u8 *)g + 0x9C) = id;
    switch (k) {
    case 0:
        PartyRemoveMember_3c0fa0(*(s32 *)(g->unk94 + 0x18), id, 1, 0);
        obj->b1 = 0;
        break;
    case 1:
    case 6:
        PartyAddMember_3c1430(*(s32 *)(g->unk94 + 0x18), id, 0);
        PartyPromoteReserve_3c17c0(*(s32 *)(g->unk94 + 0x18), id, 1, 0);
        PartySetLeader_3c1600(*(s32 *)(g->unk94 + 0x18), id, 0);
        break;
    case 2:
        PartyAddMember_3c1430(*(s32 *)(g->unk94 + 0x18), id, 0);
        PartyPromoteReserve_3c17c0(*(s32 *)(g->unk94 + 0x18), id, 1, 0);
        break;
    case 3:
        PartyAddMember_3c1430(*(s32 *)(g->unk94 + 0x18), id, 0);
        PartyMoveToReserve_3c19b0(*(s32 *)(g->unk94 + 0x18), id, 1, 0);
        break;
    case 4:
    case 5:
        PartyAddMember_3c1430(*(s32 *)(g->unk94 + 0x18), id, 0);
        PartyMoveToReserve_3c19b0(*(s32 *)(g->unk94 + 0x18), id, 1, 0);
        CharaSetFlag234Bit2Related_3ae370(obj, 1);
        if (k == 5) {
            PartyRemoveMember_3c0fa0(*(s32 *)(g->unk94 + 0x18), id, 0, 0);
        }
        break;
    }
    *(s16 *)((u8 *)g + 0x9E) = 0;
    *(s16 *)((u8 *)g + 0xA0) = 0;
    if (k == 6) {
        obj->f464(1);
    }
    return 1;
}
