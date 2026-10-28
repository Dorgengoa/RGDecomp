/* rgp:protos */
#line 1
#include "types.h"

class Unit {
public:
    VC_VPTR_MEMBER;     
         
         
         
         
         
         
         
         
         
         
         
         
         
         
         
         
         
         
       
    s32 Can(s32 a0) { return VCM(s32, (void *, s32), 0x1E0, a0); } /* 0x1E0 */
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
    s32 ids[4] __attribute__((aligned(16)));
    s32 hp[4] __attribute__((aligned(16)));
    s32 hpmax[4] __attribute__((aligned(16)));
    s32 mp[4] __attribute__((aligned(16)));
    s32 mpmax[4] __attribute__((aligned(16)));
    Unit *un[4];
    s32 cntk[4] __attribute__((aligned(16)));
    s32 list[8] __attribute__((aligned(16)));
    Tbl tbl __attribute__((aligned(16)));
    s32 flags[10] __attribute__((aligned(16)));
    Tbl tbl2 __attribute__((aligned(16)));
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
        ids[i] = ((short)PartyGetMemberId_3c2490(gm->x18, i));
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
