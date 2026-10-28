/* rgp:protos */
#line 1
#include "types.h"

class Unit {
public:
    VC_VPTR_MEMBER;     
         
         
         
         
         
         
         
         
         
         
         
         
         
         
         
        
    s32 Has(s32 a0) { return VCM(s32, (void *, s32), 0x19C, a0); } /* 0x19C */
         
         
       
    s32 Can(s32 a0) { return VCM(s32, (void *, s32), 0x1E0, a0); } /* 0x1E0 */
};

typedef struct Pair {
    s32 a;
    s32 b;
} Pair;

typedef struct Tbl {
    s32 v[10];
} Tbl;

typedef struct Gm {
    u8 pad0[0x18];
    s32 x18;
    u8 pad1C[4];
    s32 x20;
} Gm;

extern "C" {
Gm *GetGameData_1fede0(void);
Unit *ActorFindById_3eb870(Gm *, s32);
s32 InvHasItemById_2c43f0(s32);
s32 CharaSysStateField28ValidRelated_3a3920(s32);
s32 Rand_133710(void);
s32 PartyCountMembers_3c2010(s32, s32, s32);
s32 PartyGetMemberId_3c2490(s32, s32);
s32 ActorGetHpById_2cd870(s32, s32);
void ScriptSlotStoreIntRef_2cc900(void *, s32);
extern s32 D_004DB928[];
extern s32 D_004511B0[10];
s32 AiCmdPickCureItemMaybe_2c3500(void *self);
}

#pragma divbyzerocheck on

extern "C" s32 AiCmdPickCureItemMaybe_2c3500(void *self)
{
    s32 list[12] __attribute__((aligned(16)));
    s32 id[12] __attribute__((aligned(16)));
    Unit *un[12];
    s32 k[12] __attribute__((aligned(16)));
    Tbl tbl __attribute__((aligned(16)));
    Gm *gm;
    Unit *u;
    bool c;
    bool b;
    bool a;
    s32 n;
    s32 m;
    s32 cnt;
    s32 i;
    s32 j;
    s32 q;

    gm = GetGameData_1fede0();
    u = ActorFindById_3eb870(gm, D_004DB928[0]);
    if (u == 0) {
        return 0;
    }
    c = false;
    b = false;
    a = false;
    if (u->Has(0xB) || u->Has(0xC) || u->Has(0xD) || u->Has(0xE) || u->Has(0x23)) {
        a = true;
    }
    if (u->Has(0xF) || u->Has(0x10) || u->Has(0x18) || u->Has(0x19) || u->Has(0x15) || u->Has(0x16) ||
        u->Has(0x17) || u->Has(0x1D) || u->Has(0x1E) || u->Has(0x21)) {
        b = true;
    }
    if (u->Has(0x11) || u->Has(0x12) || u->Has(0x13) || u->Has(0x14) || u->Has(0x27) || u->Has(0x28) ||
        u->Has(0x20)) {
        c = true;
    }
    if (u->Has(0x29) || u->Has(0x2A) || u->Has(0x22)) {
        b = c = true;
    }
    n = 0;
    if (!c && ((unsigned char)InvHasItemById_2c43f0(0x40DA))) {
        list[n++] = 0x40DA;
    }
    if (!b && ((unsigned char)InvHasItemById_2c43f0(0x40DB))) {
        list[n++] = 0x40DB;
    }
    if (!c && !b && ((unsigned char)InvHasItemById_2c43f0(0x40DC))) {
        list[n++] = 0x40DC;
    }
    if (!a && ((unsigned char)InvHasItemById_2c43f0(0x40DD))) {
        list[n++] = 0x40DD;
    }
    m = 3;
    if (((unsigned char)CharaSysStateField28ValidRelated_3a3920(gm->x20))) {
        m = 10;
    }
    if (((unsigned char)InvHasItemById_2c43f0(0x40DE)) && Rand_133710() % m == 0) {
        list[n++] = 0x40DE;
    }
    if (((unsigned char)InvHasItemById_2c43f0(0x40DF)) && Rand_133710() % m == 0) {
        list[n++] = 0x40DF;
    }
    {
        s32 t = PartyCountMembers_3c2010(gm->x18, 1, 1);
        tbl = *(Tbl *)D_004511B0;
        cnt = t;
    }
    for (i = 0; i < cnt; i++) {
        s32 r;
        s32 *pid;
        s32 *pk;
        Unit **pu;
        Unit *v;
        r = ((short)PartyGetMemberId_3c2490(gm->x18, i));
        pk = &k[i];
        pid = &id[i];
        pu = &un[i];
        *pid = r;
        *pk = 0;
        *pu = ActorFindById_3eb870(gm, *pid);
        v = *pu;
        if (v == 0) {
            continue;
        }
        if (ActorGetHpById_2cd870(*pid, 0) <= 0) {
            continue;
        }
        for (j = 0; j < 10; j++) {
            if (v->Can(tbl.v[j])) {
                (*pk)++;
            }
        }
    }
    q = 0;
    for (i = 0; i < cnt; i++) {
        if (k[i] > 0) {
            q++;
        }
    }
    if (q > 0 && ((unsigned char)InvHasItemById_2c43f0(0x40CC))) {
        list[0] = 0x40CC;
        n = 1;
    }
    if (!(q < 2) && ((unsigned char)InvHasItemById_2c43f0(0x40CD))) {
        list[0] = 0x40CD;
        n = 1;
    }
    if (n > 0) {
        ScriptSlotStoreIntRef_2cc900(self, list[Rand_133710() % n]);
        return 1;
    }
    ScriptSlotStoreIntRef_2cc900(self, -1);
    return 1;
}
