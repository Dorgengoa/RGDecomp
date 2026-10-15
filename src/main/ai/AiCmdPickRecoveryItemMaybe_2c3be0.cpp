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
    virtual void vf96(); virtual void vf97(); virtual void vf98(); virtual void vf99(); virtual void vf100(); virtual void vf101();
    virtual void vf102(); virtual void vf103(); virtual void vf104(); virtual void vf105(); virtual void vf106(); virtual void vf107();
    virtual void vf108(); virtual void vf109(); virtual void vf110(); virtual void vf111(); virtual void vf112(); virtual void vf113();
    virtual void vf114(); virtual void vf115(); virtual void vf116(); virtual void vf117();
    virtual s32 Can(s32); /* 0x1E0 */
};

typedef struct Tbl {
    s32 v[10];
} Tbl;

typedef struct Gm {
    u8 pad0[0x18];
    s32 x18;
} Gm;

extern "C" {
Gm *GetGameData_1fede0(void);
s32 PartyCountMembers_3c2010(s32, s32, s32);
s32 PartyGetMemberId_3c2490(s32, s32);
s32 ActorGetHpById_2cd870(s32, s32 *);
s32 ActorGetMpById_2cd780(s32, s32 *);
s32 InvFindFirstOwned_2c4350(s32 *, s32);
void ScriptSlotStoreIntRef_2cc900(void *, s32);
Unit *ActorFindById_3eb870(Gm *, s32);
extern f32 D_0047D1E8;
extern f32 D_0047D288;
extern s32 D_00451150[10];
extern s32 D_00451180[10];
s32 AiCmdPickRecoveryItemMaybe_2c3be0(void *self);
}

#define TRY()                                   \
    {                                           \
        s32 r_ = InvFindFirstOwned_2c4350(list, n);         \
        if (r_ >= 0) {                          \
            ScriptSlotStoreIntRef_2cc900(self, r_);             \
            return 1;                           \
        }                                       \
        n = 0;                                  \
    }

extern "C" s32 AiCmdPickRecoveryItemMaybe_2c3be0(void *self)
{
    s32 ids[4];
    s32 hp[4];
    s32 hpmax[4];
    s32 mp[4];
    s32 mpmax[4];
    Unit *un[4];
    s32 cntk[4];
    s32 list[8];
    Tbl tbl;
    s32 flags[10];
    Tbl tbl2;
    Gm *gm;
    s32 cnt;
    s32 n;
    s32 i;
    s32 j;
    s32 a;
    s32 k;
    f32 f;

    gm = GetGameData_1fede0();
    cnt = PartyCountMembers_3c2010(gm->x18, 1, 1);
    n = 0;
    for (i = 0; i < cnt; i++) {
        ids[i] = PartyGetMemberId_3c2490(gm->x18, i);
    }
    for (i = 0; i < cnt; i++) {
        hp[i] = ActorGetHpById_2cd870(ids[i], &hpmax[i]);
    }
    for (i = 0; i < cnt; i++) {
        mp[i] = ActorGetMpById_2cd780(ids[i], &mpmax[i]);
    }
    k = 0;
    for (i = 0; i < cnt; i++) {
        if (hp[i] == 0) {
            hp[i] = 999;
            k++;
        }
    }
    if (!(k < 2)) {
        list[0] = 0x40D7;
        list[1] = 0x40D6;
        list[2] = 0x40D8;
        n = 3;
    }
    TRY();
    if (k == 1) {
        list[0] = 0x40D6;
        list[1] = 0x40D7;
        list[2] = 0x40D8;
        n = 3;
    }
    TRY();
    f = 0.3f;
    k = 0;
    for (i = 0; i < cnt; i++) {
        if (hp[i] < f * hpmax[i]) {
            if (mp[i] < f * mpmax[i]) {
                k++;
            }
        }
    }
    if (!(k < 2)) {
        list[0] = 0x40CB;
        list[1] = 0x40CA;
        n = 2;
    }
    TRY();
    if (k == 1) {
        list[0] = 0x40CA;
        list[1] = 0x40CB;
        n = 2;
    }
    TRY();
    f = 0.3f;
    k = 0;
    for (i = 0; i < cnt; i++) {
        if (hp[i] < f * hpmax[i]) {
            k++;
        }
    }
    if (!(k < 2)) {
        list[0] = 0x40C7;
        list[1] = 0x40C6;
        list[2] = 0x40C5;
        list[3] = 0x40C4;
        n = 4;
    }
    TRY();
    if (k == 1) {
        list[0] = 0x40C5;
        list[1] = 0x40C4;
        list[2] = 0x40C7;
        list[3] = 0x40C6;
        n = 4;
    }
    TRY();
    tbl = *(Tbl *)D_00451150;
    {
        u8 *p_ = (u8 *)flags;
        u32 n_ = 0x28;
        if (p_) {
            while (n_) {
                *p_ = 0;
                n_--;
                p_++;
            }
        }
    }
    for (j = 0; j < cnt; j++) {
        s32 *pc = &cntk[j];
        Unit **pu = &un[j];
        *pc = 0;
        *pu = ActorFindById_3eb870(gm, ids[j]);
        if (*pu == 0) {
            continue;
        }
        for (i = 0; i < 10; i++) {
            s32 *pf = &flags[i];
            if (*pf == 1) {
                continue;
            }
            if ((*pu)->Can(tbl.v[i])) {
                (*pc)++;
                *pf = 1;
            }
        }
    }
    k = 0;
    for (i = 0; i < cnt; i++) {
        if (cntk[i] > 0) {
            k++;
        }
    }
    tbl2 = *(Tbl *)D_00451180;
    for (a = 0; a < 10; a++) {
        for (i = 0; i < cnt; i++) {
            Unit **pu = &un[i];
            if (*pu == 0) {
                continue;
            }
            for (j = 0; j < 10; j++) {
                if ((*pu)->Can(tbl.v[j])) {
                    list[0] = tbl2.v[j];
                    n = 1;
                    TRY();
                }
            }
        }
    }
    f = 0.6f;
    k = 0;
    for (i = 0; i < cnt; i++) {
        if (hp[i] < f * hpmax[i]) {
            k++;
        }
    }
    if (!(k < 2)) {
        list[0] = 0x40C6;
        list[1] = 0x40C4;
        n = 2;
    }
    TRY();
    if (k == 1) {
        list[0] = 0x40C4;
        list[1] = 0x40C6;
        n = 2;
    }
    TRY();
    f = 0.3f;
    k = 0;
    for (i = 0; i < cnt; i++) {
        if (mp[i] < f * mpmax[i]) {
            k++;
        }
    }
    if (!(k < 2)) {
        list[0] = 0x40C9;
        list[1] = 0x40C8;
        n = 2;
    }
    TRY();
    if (k == 1) {
        list[0] = 0x40C8;
        list[1] = 0x40C9;
        n = 2;
    }
    TRY();
    ScriptSlotStoreIntRef_2cc900(self, -1);
    return 1;
}
