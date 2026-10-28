/* rgp:protos */
#line 1
#include "types.h"

typedef struct Ent {
    s16 id;
    u8 pad2[0xA];
} Ent;

typedef struct Flags {
    u8 b0 : 1;
    u8 b1 : 1;
    u8 b2 : 1;
} Flags;

typedef struct Ev {
    s16 x0;
    u8 pad2[0x2];
    s16 x4;
    s16 x6;
    s16 x8;
    s16 xA;
    s16 xC;
    s16 xE;
    s16 x10;
    s16 x12;
    u8 pad14[0x2];
    s16 x16;
    s16 x18[2];
    Ent ent[2];
    s16 x34;
    s16 x36;
    s16 x38;
    s16 x3A;
    Flags x3C;
} Ev;

typedef struct Unit {
    u8 pad0[0x18C];
    s16 x18C;
    s16 x18E;
} Unit;

typedef struct Obj {
    u8 pad0[0xC];
    s32 xC;
} Obj;

typedef struct Chr {
    u8 pad0[0x234];
    bool f0 : 1;
} Chr;

typedef struct Btl {
    u8 pad0[0xC];
    s32 xC;
    s32 x10;
    s32 x14;
    Unit *x18;
    u8 pad1C[0x8];
    s32 x24;
    s32 x28;
} Btl;

extern "C" {
extern Obj *CharaMgrPoolFindByDataId_3a8a70(s32, s32, s32, s32, s32, s32, s32);
extern Chr *CharaMgrPoolFindById_3a8c60(s32, s32);
extern s32 CharaIsPartyMember_3ae110(Chr *);
extern s32 CharaIsInParty_3ae1d0(Obj *);
extern void CharaSetFlag234Bit2Related_3ae370(Obj *, s32);
extern void DataTableOwnerLoadResidentBin_3b8b70(s32, s32, s32, s32);
extern void PartySwapMembers_3c0ad0(Unit *, s32, s32, s32, s32);
extern void PartyRemoveMember_3c0fa0(Unit *, s32, s32, s32);
extern void PartyCharaEquipDefaultsMaybe_3c1250(Unit *, s32);
extern s32 PartyAddMember_3c1430(Unit *, s32, s32);
extern void PartySetLeader_3c1600(Unit *, s32, s32);
extern void PartyPromoteReserve_3c17c0(Unit *, s32, s32, s32);
extern s32 PartyMoveToReserve_3c19b0(Unit *, s32, s32, s32);
extern s32 PartyCountReserve_3c1c20(Unit *, s32, s32);
extern s32 PartyGetReserveId_3c1d90(Unit *, s32);
extern void PartySetActiveCount_3c1ec0(Unit *, s32);
extern s32 PartyGetMemberId_3c2490(Unit *, s32);
extern s32 PartyGetNonLeaderId_3c2750(Unit *, s32);
extern s32 PartyContainsId_3c2ea0(Unit *, s32);
extern void InvAddItemCoreMaybe_3c6540(Unit *, s32, s32, s32, s32, s32, s32);
extern s32 InvHasItemInCategory_3c7f40(Unit *, s32, s32, s32);
extern void PartySetSpotMaybe_3ca7c0(Unit *, long long, int, int);
extern void PartySetSubAreaMaybe_3ca890(Unit *, s32, s32, int);
extern void PartySetAreaMaybe_3cab50(Unit *, s32, s32, s32);
extern void StateVarAdd_3cc8e0(s32, s32, s32);
extern void StateVarSet_3cc9c0(s32, s32, s32, s32);
extern void ProgressValueSet_3cd020(s32, s32, s32, s32, s32, s32);
extern void ProgressSetChapter_3cd480(s32, s32, int, int);
extern void OptionsSetDataSetIndexMaybe_3d5f00(s32, s32);
extern void GameDataFlagsSetOrClear_3e4580(Btl *, s32, s32);
extern void GameDataSetPendingEncounterId_3e67b0(Btl *, s32);
extern void GameStartRecFillPresetMaybe_3e7440(Btl *, Ev *);
extern void NewGamePartyInitMaybe_3e74f0(Btl *);
extern void RecordSetMode_431310(s32, s32);
extern s32 D_0045B090[];
extern s32 D_0045B098[];
}

extern "C" s32 GameDataApplyStartConfigMaybe_3e69c0(Btl *self, Ev *ev, s32 arg2) {
    s32 j;
    Obj *arr[2];
    bool save;
    s32 saved;
    Chr *p0;
    bool f;
    Unit *q;
    s32 a;
    s32 b;
    s32 c;
    Obj *p;
    s32 i;
    s32 id;
    s32 cur;
    s32 cnt;
    Obj *e;
    s32 k;
    bool g;
    Obj *e2;

    GameDataFlagsSetOrClear_3e4580(self, 1, 0);
    saved = 3;
    p0 = 0;
    save = false;
    f = false;
    if (ev->x0 == 5 || ev->x0 == 6 || ev->x0 == 2 || ev->x0 == 4) {
        f = true;
    }
    if (f) {
        NewGamePartyInitMaybe_3e74f0(self);
        {
            Chr *c_ = CharaMgrPoolFindById_3a8c60(self->x14, 0);
            p0 = c_;
            if (c_ != 0) {
                save = c_->f0;
                c_->f0 = false;
            }
        }
        q = self->x18;
        saved = q->x18C;
        PartySetActiveCount_3c1ec0(q, 3);
    }
    if (ev->x0 == 5) {
        if (arg2 != 0) {
            s32 w = self->x28;
            s32 v = ev->x3A;
            if (w != 0) {
                DataTableOwnerLoadResidentBin_3b8b70(w, arg2, v, 0);
            }
        }
    } else if (ev->x0 == 6) {
        if (arg2 != 0) {
            s32 w = self->x28;
            s32 v = ev->x12;
            if (w != 0) {
                DataTableOwnerLoadResidentBin_3b8b70(w, arg2, v, 0);
            }
        }
    } else if (ev->x0 == 2) {
        GameStartRecFillPresetMaybe_3e7440(self, ev);
        if (arg2 != 0) {
            s32 w = self->x28;
            s32 v = ev->xC;
            if (w != 0) {
                DataTableOwnerLoadResidentBin_3b8b70(w, arg2, v, 0);
            }
        }
    } else if (ev->x0 == 4) {
        GameStartRecFillPresetMaybe_3e7440(self, ev);
        if (arg2 != 0) {
            s32 w = self->x28;
            s32 v = ev->x6;
            if (w != 0) {
                DataTableOwnerLoadResidentBin_3b8b70(w, arg2, v, 0);
            }
        }
    }
    if (ev->x0 == 5) {
        a = ev->x34;
        b = ev->x36;
        c = ev->x38;
        ProgressSetChapter_3cd480(self->x10, a, 0, 0);
        if (ev->x3C.b0 || ev->x3C.b1 || ev->x3C.b2) {
            StateVarSet_3cc9c0(self->x10, 2, 0, 0);
        }
        if (ev->x3C.b0) {
            if (a == 8) {
                ProgressValueSet_3cd020(self->x10, 8, 1, 0x1E, 0, 0);
            }
            StateVarAdd_3cc8e0(self->x10, 2, 1);
            if (InvHasItemInCategory_3c7f40(self->x18, 0x4178, 0, 0) == 0) {
                InvAddItemCoreMaybe_3c6540(self->x18, 0x4178, 0xA, 1, -1, 0, 0);
            }
        }
        if (ev->x3C.b1) {
            if (a == 8) {
                ProgressValueSet_3cd020(self->x10, 8, 2, 0x1E, 0, 0);
            }
            StateVarAdd_3cc8e0(self->x10, 2, 1);
            if (InvHasItemInCategory_3c7f40(self->x18, 0x4179, 0, 0) == 0) {
                InvAddItemCoreMaybe_3c6540(self->x18, 0x4179, 0xA, 1, -1, 0, 0);
            }
        }
        if (ev->x3C.b2) {
            if (a == 8) {
                ProgressValueSet_3cd020(self->x10, 8, 3, 0x1E, 0, 0);
            }
            StateVarAdd_3cc8e0(self->x10, 2, 1);
            if (InvHasItemInCategory_3c7f40(self->x18, 0x417A, 0, 0) == 0) {
                InvAddItemCoreMaybe_3c6540(self->x18, 0x417A, 0xA, 1, -1, 0, 0);
            }
        }
        ProgressValueSet_3cd020(self->x10, a, b, c, 0, 1);
    } else if (ev->x0 == 6) {
        a = ev->xC;
        b = ev->xE;
        c = ev->x10;
        ProgressSetChapter_3cd480(self->x10, a, 0, 0);
        ProgressValueSet_3cd020(self->x10, a, b, c, 0, 1);
    }
    OptionsSetDataSetIndexMaybe_3d5f00(self->xC, -1);
    if (ev->x0 == 5) {
        PartySetSubAreaMaybe_3ca890(self->x18, ev->x4, 1, 0);
        if (ev->x6 >= 0) {
            PartySetSpotMaybe_3ca7c0(self->x18, (long long)(ev->x6), 0, 0);
        }
    } else if (ev->x0 == 6) {
        PartySetAreaMaybe_3cab50(self->x18, ev->x4, 1, 0);
        PartySetSubAreaMaybe_3ca890(self->x18, ev->x6, 0, 0);
    } else if (ev->x0 == 2) {
        PartySetAreaMaybe_3cab50(self->x18, ev->x4, 1, 0);
        PartySetSubAreaMaybe_3ca890(self->x18, ev->x6, 0, 0);
    }
    if (ev->x0 == 5) {
        p = 0;
        if (ev->x8 >= 0) {
            p = CharaMgrPoolFindByDataId_3a8a70(self->x14, ev->x8, 1, 1, 0, 0, 0);
        }
        {
            u8 *p_ = (u8 *)arr;
            u32 n_ = 8;
            if (p_ != 0) {
                while (n_ != 0) {
                    *p_ = 0;
                    n_--;
                    p_++;
                }
            }
        }
        for (i = 0; i < 2; i++) {
            if (ev->ent[i].id >= 0) {
                arr[i] = CharaMgrPoolFindByDataId_3a8a70(self->x14, ev->ent[i].id, 1, 1, 0, 0, 0);
            }
        }
        if (p != 0) {
            id = p->xC;
            CharaSetFlag234Bit2Related_3ae370(p, 0);
            CharaSetFlag234Bit2Related_3ae370(p, 0);
            if (CharaIsInParty_3ae1d0(p) == 0 && PartyAddMember_3c1430(self->x18, id, 0) != 1) {
                PartyRemoveMember_3c0fa0(self->x18, ((short)PartyGetReserveId_3c1d90(self->x18, 2)), 1, 0);
                PartyAddMember_3c1430(self->x18, id, 0);
            }
            PartyCharaEquipDefaultsMaybe_3c1250(self->x18, id);
            q = self->x18;
            cur = q->x18E;
            if (id != cur) {
                if (cur >= 0) {
                    PartySwapMembers_3c0ad0(q, id, cur, 1, 0);
                    PartySetLeader_3c1600(self->x18, id, 0);
                } else {
                    PartyPromoteReserve_3c17c0(q, id, 1, 0);
                    PartySetLeader_3c1600(self->x18, id, 0);
                }
            }
        }
        cnt = 0;
        for (i = 0; i < 2; i++) {
            e = arr[i];
            if (e != 0) {
                id = e->xC;
                CharaSetFlag234Bit2Related_3ae370(e, 0);
                CharaSetFlag234Bit2Related_3ae370(e, 0);
                if (((unsigned char)PartyContainsId_3c2ea0(self->x18, id)) == 0 && PartyAddMember_3c1430(self->x18, id, 0) != 1) {
                    PartyRemoveMember_3c0fa0(self->x18, ((short)PartyGetReserveId_3c1d90(self->x18, i + 3)), 1, 0);
                    PartyAddMember_3c1430(self->x18, id, 0);
                }
                PartyCharaEquipDefaultsMaybe_3c1250(self->x18, id);
                cur = ((short)PartyGetNonLeaderId_3c2750(self->x18, i));
                if (id != cur) {
                    if (cur >= 0) {
                        PartySwapMembers_3c0ad0(self->x18, id, cur, 1, 0);
                    } else {
                        PartyPromoteReserve_3c17c0(self->x18, id, 1, 0);
                    }
                }
                cnt++;
            } else if (p != 0) {
                k = ((short)PartyGetNonLeaderId_3c2750(self->x18, cnt));
                if (k >= 0 && PartyMoveToReserve_3c19b0(self->x18, k, 1, 0) != 1) {
                    PartyRemoveMember_3c0fa0(self->x18, k, 1, 0);
                }
            }
        }
    } else if (ev->x0 == 6) {
        if (ev->x18[0] >= 0) {
            cnt = 0;
            for (j = 0; j < 3; j++) {
                e2 = 0;
                if (ev->x18[j] >= 0) {
                    e2 = CharaMgrPoolFindByDataId_3a8a70(self->x14, ev->x18[j], 1, 1, 0, 0, 0);
                }
                if (e2 != 0) {
                    id = e2->xC;
                    CharaSetFlag234Bit2Related_3ae370(e2, 0);
                    CharaSetFlag234Bit2Related_3ae370(e2, 0);
                    if (((unsigned char)PartyContainsId_3c2ea0(self->x18, id)) == 0 && PartyAddMember_3c1430(self->x18, id, 0) != 1) {
                        PartyRemoveMember_3c0fa0(self->x18, ((short)PartyGetReserveId_3c1d90(self->x18, PartyCountReserve_3c1c20(self->x18, 1, 1) - 1)), 1, 0);
                        PartyAddMember_3c1430(self->x18, id, 0);
                    }
                    PartyCharaEquipDefaultsMaybe_3c1250(self->x18, id);
                    cur = ((short)PartyGetMemberId_3c2490(self->x18, j));
                    if (id != cur) {
                        if (cur >= 0) {
                            PartySwapMembers_3c0ad0(self->x18, id, cur, 1, 0);
                        } else {
                            PartyPromoteReserve_3c17c0(self->x18, id, 1, 0);
                        }
                    }
                    if (j == 0) {
                        PartySetLeader_3c1600(self->x18, id, 0);
                    }
                    cnt++;
                } else {
                    k = ((short)PartyGetMemberId_3c2490(self->x18, cnt));
                    if (k >= 0) {
                        PartyRemoveMember_3c0fa0(self->x18, k, 1, 0);
                    }
                }
            }
        }
    }
    if (ev->x0 == 6 && ev->x16 >= 0) {
        GameDataSetPendingEncounterId_3e67b0(self, ev->x16);
    }
    if (f) {
        if (p0 != 0 && save && CharaIsPartyMember_3ae110(p0) != 0) {
            p0->f0 = true;
        }
        PartySetActiveCount_3c1ec0(self->x18, saved);
    }
    g = false;
    if (ev->x0 == 2) {
        g = true;
    } else if (ev->x0 == 6 && ev->x4 == 4 && (ev->xA == D_0045B090[0] || ev->xA == D_0045B098[0])) {
        g = true;
    }
    if (g) {
        RecordSetMode_431310(self->x24, 1);
    }
    GameDataFlagsSetOrClear_3e4580(self, 1, 1);
    return 1;
}
