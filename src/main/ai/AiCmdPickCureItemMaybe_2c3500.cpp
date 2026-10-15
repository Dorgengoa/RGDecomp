#include "types.h"

class Unit {
public:
    virtual void vf0(); virtual void vf1(); virtual void vf2(); virtual void vf3(); virtual void vf4(); virtual void vf5();
    virtual void vf6(); virtual void vf7(); virtual void vf8(); virtual void vf9(); virtual void vf10(); virtual void vf11();
    virtual void vf12(); virtual void vf13(); virtual void vf14(); virtual void vf15(); virtual void vf16(); virtual void vf17();
    virtual void vf18(); virtual void vf19(); virtual void vf20(); virtual void vf21(); virtual void vf22(); virtual void vf23();
    virtual void vf24(); virtual void vf25(); virtual void vf26(); virtual void vf27(); virtual void vf28(); virtual void vf29();
    virtual void vf30(); virtual void vf31(); virtual void vf32(); virtual void vf33(); virtual void vf34(); virtual void vf35();
    virtual void vf36(); virtual void vf37(); virtual void vf38(); virtual void vf39(); virtual void vf40(); virtual void vf41();
    virtual void vf42(); virtual void vf43(); virtual void vf44(); virtual void vf45(); virtual void vf46(); virtual void vf47();
    virtual void vf48(); virtual void vf49(); virtual void vf50(); virtual void vf51(); virtual void vf52(); virtual void vf53();
    virtual void vf54(); virtual void vf55(); virtual void vf56(); virtual void vf57(); virtual void vf58(); virtual void vf59();
    virtual void vf60(); virtual void vf61(); virtual void vf62(); virtual void vf63(); virtual void vf64(); virtual void vf65();
    virtual void vf66(); virtual void vf67(); virtual void vf68(); virtual void vf69(); virtual void vf70(); virtual void vf71();
    virtual void vf72(); virtual void vf73(); virtual void vf74(); virtual void vf75(); virtual void vf76(); virtual void vf77();
    virtual void vf78(); virtual void vf79(); virtual void vf80(); virtual void vf81(); virtual void vf82(); virtual void vf83();
    virtual void vf84(); virtual void vf85(); virtual void vf86(); virtual void vf87(); virtual void vf88(); virtual void vf89();
    virtual void vf90(); virtual void vf91(); virtual void vf92(); virtual void vf93(); virtual void vf94(); virtual void vf95();
    virtual void vf96(); virtual void vf97(); virtual void vf98(); virtual void vf99(); virtual void vf100();
    virtual s32 Has(s32); /* 0x19C */
    virtual void vf102(); virtual void vf103(); virtual void vf104(); virtual void vf105(); virtual void vf106(); virtual void vf107();
    virtual void vf108(); virtual void vf109(); virtual void vf110(); virtual void vf111(); virtual void vf112(); virtual void vf113();
    virtual void vf114(); virtual void vf115(); virtual void vf116(); virtual void vf117();
    virtual s32 Can(s32); /* 0x1E0 */
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
    s32 list[12];
    s32 id[12];
    Unit *un[12];
    s32 k[12];
    Tbl tbl;
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
    if (!c && InvHasItemById_2c43f0(0x40DA)) {
        list[n++] = 0x40DA;
    }
    if (!b && InvHasItemById_2c43f0(0x40DB)) {
        list[n++] = 0x40DB;
    }
    if (!c && !b && InvHasItemById_2c43f0(0x40DC)) {
        list[n++] = 0x40DC;
    }
    if (!a && InvHasItemById_2c43f0(0x40DD)) {
        list[n++] = 0x40DD;
    }
    m = 3;
    if (CharaSysStateField28ValidRelated_3a3920(gm->x20)) {
        m = 10;
    }
    if (InvHasItemById_2c43f0(0x40DE) && Rand_133710() % m == 0) {
        list[n++] = 0x40DE;
    }
    if (InvHasItemById_2c43f0(0x40DF) && Rand_133710() % m == 0) {
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
        r = PartyGetMemberId_3c2490(gm->x18, i);
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
    if (q > 0 && InvHasItemById_2c43f0(0x40CC)) {
        list[0] = 0x40CC;
        n = 1;
    }
    if (!(q < 2) && InvHasItemById_2c43f0(0x40CD)) {
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
