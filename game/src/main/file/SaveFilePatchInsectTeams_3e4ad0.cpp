#include "types.h"

typedef rg_u128 u128;

class Mgr003e4ad0 {
public:
    VC_VPTR_MEMBER;
    
    
    s32 run(u8 * a0, s32 a1) { return VCM(s32, (void *, u8 *, s32), 0x14, a0, a1); }
    s32 unk4;
};

struct Obj003e4ad0 {
    u8 pad0[0x24];
    Mgr003e4ad0 *unk24;
};

struct Unit003e4ad0 {
    u8 pad0[0x10];
    u8 b0 : 1;
    u8 b1 : 1;
    u8 b2 : 1;
    u8 b3 : 1;
    u8 b4 : 4;
    u8 pad11[0xE0 - 0x11];
};

struct Elem003e4ad0 {
    u8 b0 : 1;
    u8 b1 : 7;
    s32 n;
    u8 *p;
};

struct Tgt003e4ad0 {
    u8 pad0[0x10];
    s32 unk10;
    u8 pad14[0x20 - 0x14];
    u128 unk20;
    s32 unk30;
    u8 pad34[0x40 - 0x34];
    u128 unk40;
    u8 pad50[0x34E - 0x50];
    u8 unk34E;
};

struct Sub003e4ad0 {
    s32 unk0;
    u8 pad4[0xC];
    u128 unk10;
    s32 unk20;
    u8 pad24[0xC];
    u128 unk30;
};

struct Req003e4ad0 {
    s32 unk0;
    Tgt003e4ad0 *unk4;
    Elem003e4ad0 e[6];
};

extern "C" {
u128 Md5DigestQword_369050(u8 *, s32);
s32 SaveDataDeserialize_3e5c30(Obj003e4ad0 *, u8 *, s32, Req003e4ad0 *);
void ReqListResetWithFlagMaybe_3ee640(Req003e4ad0 *, s32);
void ReqListResetMaybe_3ee6b0(Req003e4ad0 *);
void ReqEntryInit_3ee700(Elem003e4ad0 *);
void InsectTeamTableResetTeams_431420(Mgr003e4ad0 *);
void InsectTeamTableAddTeam_431480(Mgr003e4ad0 *, Unit003e4ad0 *, s32);
}

extern "C" s32 SaveFilePatchInsectTeams_3e4ad0(Obj003e4ad0 *arg0, Unit003e4ad0 *arg1, s32 arg2, u8 *arg3, s32 arg4)
{
    s32 r;
    s32 i;
    s32 n;
    u8 *p;
    Elem003e4ad0 *e;
    Tgt003e4ad0 *t;
    Sub003e4ad0 *sub;
    Req003e4ad0 req __attribute__((aligned(16)));

    if (arg1 == 0 || arg3 == 0 || arg4 <= 0) {
        return 0;
    }
    e = req.e;
    do {
        ReqEntryInit_3ee700(e);
        e++;
    } while (e < &req.e[6]);
    ReqListResetMaybe_3ee6b0(&req);
    ReqListResetWithFlagMaybe_3ee640(&req, 0);
    req.e[5].b0 = 1;
    r = SaveDataDeserialize_3e5c30(arg0, arg3, arg4, &req);
    if (r <= 0) {
        return 0;
    }
    n = req.e[5].n;
    p = req.e[5].p;
    if (n <= 0 || p == 0) {
        return 0;
    }
    InsectTeamTableResetTeams_431420(arg0->unk24);
    for (i = 0; i < 20; i++, arg1++) {
        if (arg1->b0 && !arg1->b3) {
            InsectTeamTableAddTeam_431480(arg0->unk24, arg1, i);
        }
    }
    if (arg0->unk24->run(p - 0xC, n + 0xC) <= 0) {
        return 0;
    }
    t = req.unk4;
    if (req.unk0 <= 0) {
        return 0;
    }
    p = arg3 + 0x50;
    sub = (Sub003e4ad0 *)&t->unk10;
    t->unk34E = arg0->unk24->unk4;
    sub->unk30 = Md5DigestQword_369050(p, t->unk30);
    sub->unk10 = Md5DigestQword_369050(p, sub->unk0);
    return r;
}
