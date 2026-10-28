#include "types.h"


typedef struct Res0025b450 {
    u8 pad000[0x14];
    void *unk14;
    void *unk18;
} Res0025b450;

class Ent0025b450 {
public:
    /* +0x008 */ VC_VPTR_MEMBER;
    /* +0x00C */ 
    /* +0x010 */ 
    /* +0x014 */ 
    /* +0x018 */ 
    /* +0x01C */ 
    /* +0x020 */ 
    /* +0x024 */ 
    /* +0x028 */ 
    /* +0x02C */ 
    /* +0x030 */ 
    /* +0x034 */ 
    /* +0x038 */ 
    /* +0x03C */ s32 slot03C() { return VCM0(s32, 0x3C); }
    /* +0x040 */ 
    /* +0x044 */ 
    /* +0x048 */ 
    /* +0x04C */ 
    /* +0x050 */ 
    /* +0x054 */ 
    /* +0x058 */ 
    /* +0x05C */ 
    /* +0x060 */ 
    /* +0x064 */ 
    /* +0x068 */ 
    /* +0x06C */ 
    /* +0x070 */ 
    /* +0x074 */ 
    /* +0x078 */ 
    /* +0x07C */ 
    /* +0x080 */ 
    /* +0x084 */ 
    /* +0x088 */ 
    /* +0x08C */ 
    /* +0x090 */ 
    /* +0x094 */ 
    /* +0x098 */ 
    /* +0x09C */ 
    /* +0x0A0 */ 
    /* +0x0A4 */ 
    /* +0x0A8 */ 
    /* +0x0AC */ 
    /* +0x0B0 */ 
    /* +0x0B4 */ 
    /* +0x0B8 */ 
    /* +0x0BC */ 
    /* +0x0C0 */ s32 slot0C0() { return VCM0(s32, 0xC0); }
    /* +0x0C4 */ 
    /* +0x0C8 */ 
    /* +0x0CC */ 
    /* +0x0D0 */ 
    /* +0x0D4 */ 
    /* +0x0D8 */ 
    /* +0x0DC */ 
    /* +0x0E0 */ 
    /* +0x0E4 */ 
    /* +0x0E8 */ 
    /* +0x0EC */ 
    /* +0x0F0 */ 
    /* +0x0F4 */ void slot0F4(s32 a) { VCM(void, (void *, s32), 0xF4, a); }

    u8 pad0F8[0x230];
    u8 bit0 : 1;
    u8 rest : 7;
};

typedef struct Vec3w1_0025b450 {
    f32 x, y, z, w;
} Vec3w1_0025b450;

typedef struct Tagged1_0025b450 {
    s32 tag0;
    f32 val;
    s32 tag1;
    f32 w;
} Tagged1_0025b450;

extern "C" s32 GetActionMgr_1fdb50();
extern "C" void *GetGameData_1fede0();
extern "C" s32 ActionMgrFindById_233b50(s32, s32);
extern "C" void CharaSetPosVec_2387a0(s32, Vec3w1_0025b450 *);
extern "C" void CharaSetRotFromVec_2387b0(s32, Tagged1_0025b450 *);
extern "C" f32 TaggedGetFloat_26a280(s32);
extern "C" s32 ScriptGetInt_26a2a0(s32);
extern "C" void PartyRefreshMembersMaybe_2f40b0(s32);
extern "C" Ent0025b450 *CharaMgrPoolFindById_3a8c60(void *, s32);
extern "C" void CharaSetFlag234Bit2Related_3ae370(Ent0025b450 *, s32);
extern "C" void PartyPromoteReserve_3c17c0(void *, s32, s32, s32);
extern "C" void PartyMoveToReserve_3c19b0(void *, s32, s32, s32);


extern "C" s32 EvCmdPartyJoinLeave_25b450(s64 *arg0, s32 arg1)
{
    s32 id;
    Ent0025b450 *e;
    Res0025b450 *r;
    s32 handle;
    Vec3w1_0025b450 v1 __attribute__((aligned(16)));
    Tagged1_0025b450 v2 __attribute__((aligned(16)));

    if (arg1 < 2 && arg1 > 6) {
        return 0;
    }

    r = (Res0025b450 *)GetGameData_1fede0();
    id = ScriptGetInt_26a2a0((s32)arg0++);
    e = CharaMgrPoolFindById_3a8c60(r->unk14, id);
    if (e == 0) {
        return 0;
    }

    if (ScriptGetInt_26a2a0((s32)arg0++) != 0) {
        CharaSetFlag234Bit2Related_3ae370(e, 0);
        PartyPromoteReserve_3c17c0(r->unk18, id, 1, 0);
        if (e->slot0C0() != 0) {
            e->slot0F4(1);
            e->slot03C();
        }
        if (arg1 >= 5) {
            PartyRefreshMembersMaybe_2f40b0(1);
            handle = GetActionMgr_1fdb50();
            if (handle != 0) {
                handle = ActionMgrFindById_233b50(handle, id);
                if (handle != 0) {
                v1.x = TaggedGetFloat_26a280((s32)arg0++);
                v1.y = TaggedGetFloat_26a280((s32)arg0++);
                v1.z = TaggedGetFloat_26a280((s32)arg0++);
                v1.w = 1.0f;
                CharaSetPosVec_2387a0(handle, &v1);
                if (arg1 >= 6) {
                    v2.tag0 = 0;
                    v2.val = TaggedGetFloat_26a280((s32)arg0);
                    v2.w = 1.0f;
                    v2.tag1 = 0;
                    CharaSetRotFromVec_2387b0(handle, &v2);
                }
                } else {
                    return 0;
                }
            }
        }
    } else {
    if (e->bit0) {
        e->bit0 = 0;
    }
        PartyMoveToReserve_3c19b0(r->unk18, id, 1, 0);
    {
        s32 flag = 0;
        if (arg1 >= 3) {
            flag = ScriptGetInt_26a2a0((s32)arg0);
        }
        CharaSetFlag234Bit2Related_3ae370(e, flag != 0);
    }
    }
    return 1;
}
