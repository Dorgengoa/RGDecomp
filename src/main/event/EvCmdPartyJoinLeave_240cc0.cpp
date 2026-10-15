#include "types.h"


typedef struct Res00240cc0 {
    u8 pad000[0x14];
    void *unk14;
    void *unk18;
} Res00240cc0;

class Ent00240cc0 {
public:
    /* +0x008 */ virtual void slot008();
    /* +0x00C */ virtual void slot00C();
    /* +0x010 */ virtual void slot010();
    /* +0x014 */ virtual void slot014();
    /* +0x018 */ virtual void slot018();
    /* +0x01C */ virtual void slot01C();
    /* +0x020 */ virtual void slot020();
    /* +0x024 */ virtual void slot024();
    /* +0x028 */ virtual void slot028();
    /* +0x02C */ virtual void slot02C();
    /* +0x030 */ virtual void slot030();
    /* +0x034 */ virtual void slot034();
    /* +0x038 */ virtual void slot038();
    /* +0x03C */ virtual s32 slot03C();
    /* +0x040 */ virtual void slot040();
    /* +0x044 */ virtual void slot044();
    /* +0x048 */ virtual void slot048();
    /* +0x04C */ virtual void slot04C();
    /* +0x050 */ virtual void slot050();
    /* +0x054 */ virtual void slot054();
    /* +0x058 */ virtual void slot058();
    /* +0x05C */ virtual void slot05C();
    /* +0x060 */ virtual void slot060();
    /* +0x064 */ virtual void slot064();
    /* +0x068 */ virtual void slot068();
    /* +0x06C */ virtual void slot06C();
    /* +0x070 */ virtual void slot070();
    /* +0x074 */ virtual void slot074();
    /* +0x078 */ virtual void slot078();
    /* +0x07C */ virtual void slot07C();
    /* +0x080 */ virtual void slot080();
    /* +0x084 */ virtual void slot084();
    /* +0x088 */ virtual void slot088();
    /* +0x08C */ virtual void slot08C();
    /* +0x090 */ virtual void slot090();
    /* +0x094 */ virtual void slot094();
    /* +0x098 */ virtual void slot098();
    /* +0x09C */ virtual void slot09C();
    /* +0x0A0 */ virtual void slot0A0();
    /* +0x0A4 */ virtual void slot0A4();
    /* +0x0A8 */ virtual void slot0A8();
    /* +0x0AC */ virtual void slot0AC();
    /* +0x0B0 */ virtual void slot0B0();
    /* +0x0B4 */ virtual void slot0B4();
    /* +0x0B8 */ virtual void slot0B8();
    /* +0x0BC */ virtual void slot0BC();
    /* +0x0C0 */ virtual s32 slot0C0();
    /* +0x0C4 */ virtual void slot0C4();
    /* +0x0C8 */ virtual void slot0C8();
    /* +0x0CC */ virtual void slot0CC();
    /* +0x0D0 */ virtual void slot0D0();
    /* +0x0D4 */ virtual void slot0D4();
    /* +0x0D8 */ virtual void slot0D8();
    /* +0x0DC */ virtual void slot0DC();
    /* +0x0E0 */ virtual void slot0E0();
    /* +0x0E4 */ virtual void slot0E4();
    /* +0x0E8 */ virtual void slot0E8();
    /* +0x0EC */ virtual void slot0EC();
    /* +0x0F0 */ virtual void slot0F0();
    /* +0x0F4 */ virtual void slot0F4(s32 a);

    u8 pad0F8[0x230];
    u8 bit0 : 1;
    u8 rest : 7;
};

typedef struct Vec3w1_00240cc0 {
    f32 x, y, z, w;
} Vec3w1_00240cc0;

typedef struct Tagged1_00240cc0 {
    s32 tag0;
    f32 val;
    s32 tag1;
    f32 w;
} Tagged1_00240cc0;

extern "C" s32 GetActionMgr_1fdb50();
extern "C" void *GetGameData_1fede0();
extern "C" s32 ActionMgrFindById_233b50(s32, s32);
extern "C" void CharaSetPosVec_2387a0(s32, Vec3w1_00240cc0 *);
extern "C" void CharaSetRotFromVec_2387b0(s32, Tagged1_00240cc0 *);
extern "C" f32 TaggedGetFloat_2490d0(s32);
extern "C" s32 ScriptGetInt_2490f0(s32);
extern "C" void PartyRefreshMembersMaybe_2f40b0(s32);
extern "C" Ent00240cc0 *CharaMgrPoolFindById_3a8c60(void *, s32);
extern "C" void CharaSetFlag234Bit2Related_3ae370(Ent00240cc0 *, s32);
extern "C" void PartyPromoteReserve_3c17c0(void *, s32, s32, s32);
extern "C" void PartyMoveToReserve_3c19b0(void *, s32, s32, s32);


extern "C" s32 EvCmdPartyJoinLeave_240cc0(s64 *arg0, s32 arg1)
{
    s32 id;
    Ent00240cc0 *e;
    Res00240cc0 *r;
    s32 handle;
    Vec3w1_00240cc0 v1;
    Tagged1_00240cc0 v2;

    if (arg1 < 2 && arg1 > 6) {
        return 0;
    }

    r = (Res00240cc0 *)GetGameData_1fede0();
    id = ScriptGetInt_2490f0((s32)arg0++);
    e = CharaMgrPoolFindById_3a8c60(r->unk14, id);
    if (e == 0) {
        return 0;
    }

    if (ScriptGetInt_2490f0((s32)arg0++) != 0) {
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
                v1.x = TaggedGetFloat_2490d0((s32)arg0++);
                v1.y = TaggedGetFloat_2490d0((s32)arg0++);
                v1.z = TaggedGetFloat_2490d0((s32)arg0++);
                v1.w = 1.0f;
                CharaSetPosVec_2387a0(handle, &v1);
                if (arg1 >= 6) {
                    v2.tag0 = 0;
                    v2.val = TaggedGetFloat_2490d0((s32)arg0);
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
            flag = ScriptGetInt_2490f0((s32)arg0);
        }
        CharaSetFlag234Bit2Related_3ae370(e, flag != 0);
    }
    }
    return 1;
}
