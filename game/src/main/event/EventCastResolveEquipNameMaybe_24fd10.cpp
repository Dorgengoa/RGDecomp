#include "types.h"

struct Ent { u8 pad0[0x26]; s16 h26; s16 h28; s16 h2a; };
struct Sub { u8 pad0[0x10]; s16 *val; };
class Obj {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    Ent * GetEnt() { return VCM0(Ent *, 0x33C); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    Sub * GetSub(s32 a0) { return VCM(Sub *, (void *, s32), 0x384, a0); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    Sub * GetMain() { return VCM0(Sub *, 0x3C4); }
};
class Db {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void * Find(s16 a0) { return VCM(void *, (void *, s16), 0x70, a0); }
};
struct DbHolder { u8 pad0[8]; Db *db; };
struct Sys { u8 pad0[0x40]; DbHolder *h; };
struct Actor { u8 pad0[0x14]; s32 x14; s32 x18; };
struct Slot { u8 pad0[0xC]; s32 id; };
extern "C" {
s32 Sprintf_1343b8(char *, const char *, ...);
s32 Strstr_135138(const char *, const char *);
Actor *GetGameData_1fede0(void);
Sys *GetWorldDataMgr_1fedf0(void);
Obj *CharaMgrPoolFindById_3a8c60(s32, s32);
s32 PartyCountMembers_3c2010(s32, s32, s32);
Slot *PartyGetMemberChara_3c2420(s32, s32);
char *CharaPcResNameBuildMaybe_40dc60(void *);
}
extern "C" char D_0045EA20[];
extern "C" char D_0045EC78[];
extern "C" char D_0045EC80[];
extern "C" char D_0045EC90[];
extern "C" char D_0045ECA0[];
extern "C" char D_0045ECA8[];
extern "C" char D_0045ECB0[];
extern "C" char D_0045ECB8[];
extern "C" char D_0045ECC0[];
extern "C" char D_0045ECC8[];
extern "C" char D_0045ECD0[];
extern "C" char D_0045ECD8[];
extern "C" char D_0045ECE0[];
extern "C" char D_0045ECF0[];
extern "C" char D_0045ED00[];
extern "C" char D_0045ED10[];
extern "C" char D_0045ED20[];

extern "C" s32 EventCastResolveEquipNameMaybe_24fd10(char *arg0, char *out, s32 *res, s32 *idx)
{
    bool ok;
    Actor *actor;
    s32 i;
    Sys *sys;
    Ent *e;
    s32 v;
    s32 kind;
    s32 n;
    s32 ret;
    Obj *o;
    Sub *p;
    void *r;

    if (*arg0 != 0x23) {
        return -1;
    }
    if (Strstr_135138(arg0, D_0045EC78) != 0) {
        kind = 0;
    } else if (Strstr_135138(arg0, D_0045EC80) != 0) {
        kind = 1;
    } else if (Strstr_135138(arg0, D_0045EC90) != 0) {
        kind = 2;
    } else {
        return -1;
    }
    if (Strstr_135138(arg0, D_0045ECA0) != 0) {
        *idx = 0;
    } else if (Strstr_135138(arg0, D_0045ECA8) != 0) {
        *idx = 1;
    } else if (Strstr_135138(arg0, D_0045ECB0) != 0) {
        *idx = 2;
    } else if (Strstr_135138(arg0, D_0045ECB8) != 0) {
        *idx = 3;
    } else if (Strstr_135138(arg0, D_0045ECC0) != 0) {
        *idx = 4;
    } else if (Strstr_135138(arg0, D_0045ECC8) != 0) {
        *idx = 5;
    } else if (Strstr_135138(arg0, D_0045ECD0) != 0) {
        *idx = 6;
    } else if (Strstr_135138(arg0, D_0045ECD8) != 0) {
        *idx = 7;
    } else if (Strstr_135138(arg0, D_0045ECE0) != 0) {
        *idx = 8;
    } else if (Strstr_135138(arg0, D_0045ECF0) != 0) {
        *idx = 9;
    } else if (Strstr_135138(arg0, D_0045ED00) != 0) {
        *idx = -1;
    } else if (Strstr_135138(arg0, D_0045ED10) != 0) {
        *idx = -2;
    } else {
        return -1;
    }
    actor = GetGameData_1fede0();
    sys = GetWorldDataMgr_1fedf0();
    if (*idx < 0) {
        n = PartyCountMembers_3c2010(actor->x18, 1, 1);
        for (i = 0; i < n; i++) {
            v = PartyGetMemberChara_3c2420(actor->x18, i)->id;
            if (v != 0) {
                if (*idx == -1) {
                    *idx = v;
                    break;
                }
                *idx = *idx + 1;
            }
        }
    }
    ret = -1;
    o = CharaMgrPoolFindById_3a8c60(actor->x14, *idx);
    if (o == 0) {
        return ret;
    }
    e = o->GetEnt();
    if (e == 0) {
        return ret;
    }
    switch (kind) {
    case 0:
        p = o->GetMain();
        if (p != 0) {
            ret = *p->val;
        } else {
            ret = e->h2a;
        }
        r = sys->h->db->Find(ret);
        if (r != 0) {
            Sprintf_1343b8(out, D_0045EA20, CharaPcResNameBuildMaybe_40dc60(r));
        } else {
            ret = -1;
        }
        *res = -1;
        break;
    case 1:
        p = o->GetSub(0);
        if (p != 0) {
            ret = *p->val;
        } else {
            ret = e->h26;
        }
        r = sys->h->db->Find(ret);
        if (r != 0) {
            Sprintf_1343b8(out, D_0045ED20, CharaPcResNameBuildMaybe_40dc60(r));
        } else {
            ret = -1;
        }
        ok = false;
        if (*idx >= 0 && *idx < 12) {
            ok = true;
        }
        *res = ok ? *idx * 4 + 0xC : -1;
        break;
    case 2:
        p = o->GetSub(1);
        if (p != 0) {
            ret = *p->val;
        } else {
            ret = e->h28;
        }
        r = sys->h->db->Find(ret);
        if (r != 0) {
            Sprintf_1343b8(out, D_0045ED20, CharaPcResNameBuildMaybe_40dc60(r));
        } else {
            ret = -1;
        }
        ok = false;
        if (*idx >= 0 && *idx < 12) {
            ok = true;
        }
        *res = ok ? *idx * 4 + 0xE : -1;
        break;
    }
    return ret;
}
