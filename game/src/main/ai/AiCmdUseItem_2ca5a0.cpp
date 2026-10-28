/* rgp:protos */
#line 1
#pragma divbyzerocheck on
#include "types.h"

typedef struct {
    s32 v[10];
} Tbl10;

typedef struct {
    u8 pad[8];
    s8 pad8 : 5;
    s8 kind : 3;
} Info;

class Obj {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 has(s32 a0) { return VCM(s32, (void *, s32), 0x1E0, a0); }
};


extern "C" {
extern s32 Rand_133710(void);
extern s32 GetGameData_1fede0(void);
extern s32 ScriptSlotGetInt_2cc9c0(s32);
extern s32 PartyCollectLiveMemberIds_2cd6e0(s32 *);
extern s32 ActorGetMpById_2cd780(s32, s32 *);
extern s32 ActorGetHpById_2cd870(s32, s32 *);
extern void CharaQueueItemUse_2ef680(s32, s32, s32, s32, s32);
extern s32 PartyCountReserve_3c1c20(s32, s32, s32);
extern s32 PartyCountMembers_3c2010(s32, s32, s32);
extern s32 PartyGetSlotId_3c3120(s32, s32);
extern u8 *InvFindInCategoryRange_3c8370(s32, s32, s32, s32, s32, s32);
extern Info *ItemGetEffect28Maybe_3d4ee0(u8 *);
extern Obj *ActorFindById_3eb870(s32, s32);
}
extern "C" s32 D_00451120[10];

#define BZERO(d, n) { u8 *p_ = (u8 *)(d); u32 n_ = (n); if (p_) while (n_) { *p_ = 0; n_--; p_++; } }

extern "C" s32 AiCmdUseItem_2ca5a0(s64 *arg0) {
    s32 buf260[12] __attribute__((aligned(16)));
    s32 buf230[12] __attribute__((aligned(16)));
    s32 buf200[12] __attribute__((aligned(16)));
    s32 buf1D0[12] __attribute__((aligned(16)));
    s32 buf1A0[12] __attribute__((aligned(16)));
    s32 buf170[12] __attribute__((aligned(16)));
    s32 buf140[12] __attribute__((aligned(16)));
    s32 ids[12] __attribute__((aligned(16)));
    s32 cnt[12] __attribute__((aligned(16)));
    Tbl10 tbl __attribute__((aligned(16)));
    s32 k;
    s32 best;
    s32 best2;
    s32 a;
    s32 id;
    s32 gm;
    Info *info;
    s32 kind;
    s32 t;
    s32 sel;
    s32 n;
    Obj *obj;
    s32 i;
    s32 i5;
    s32 i4;
    s32 i3;
    s32 i2;
    s32 j;
    s32 j3;
    s32 j2;
    s32 v;
    s32 *pids;
    s32 *pcnt;



    u8 *ent;


    a = ScriptSlotGetInt_2cc9c0((s32)arg0++);
    id = ScriptSlotGetInt_2cc9c0((s32)arg0);
    gm = GetGameData_1fede0();
    ent = InvFindInCategoryRange_3c8370(*(s32 *)(gm + 0x18), id, 0, -1, 0, 0);
    if (ent == 0) {
        return 0;
    }
    info = ItemGetEffect28Maybe_3d4ee0(ent);
    if (info != 0) {
        kind = info->kind;
        kind = (s8)kind;
        if (kind == 0) {
            switch (id) {
            case 0x40D6:
            case 0x40D7:
            case 0x40D8:
                t = *(s32 *)(gm + 0x18);
                v = PartyCountMembers_3c2010(t, 1, 1);
                n = v + PartyCountReserve_3c1c20(t, 1, 1);
                k = 0;
                for (i = 0; i < n; i++) {
                    v = PartyGetSlotId_3c3120(*(s32 *)(gm + 0x18), i);
                    if (ActorGetHpById_2cd870(v, 0) <= 0) {
                        buf260[k++] = v;
                    }
                }
                if (k == 0) {
                    return 1;
                }
                sel = buf260[Rand_133710() % k];
                break;
            case 0x40C8:
                n = PartyCollectLiveMemberIds_2cd6e0(buf230);
                if (n == 0) {
                    return 0;
                }
                for (i2 = 0; i2 < n; i2++) {
                    buf200[i2] = ActorGetMpById_2cd780(buf230[i2], &buf1D0[i2]);
                }
                best = 9999;
                sel = -1;
                for (j = 0; j < n; j++) {
                    pids = &buf200[j];
                    if (buf1D0[j] != buf200[j] && buf200[j] < best) {
                        sel = buf230[j];
                        best = *pids;
                    }
                }
                if (sel == -1) {
                    return 1;
                }
                break;
            default:
                n = PartyCollectLiveMemberIds_2cd6e0(buf1A0);
                if (n == 0) {
                    return 0;
                }
                for (i3 = 0; i3 < n; i3++) {
                    buf170[i3] = ActorGetHpById_2cd870(buf1A0[i3], &buf140[i3]);
                }
                best2 = 9999;
                sel = -1;
                for (j2 = 0; j2 < n; j2++) {
                    pids = &buf170[j2];
                    if (buf140[j2] != buf170[j2] && buf170[j2] < best2) {
                        sel = buf1A0[j2];
                        best2 = *pids;
                    }
                }
                if (sel == -1) {
                    return 1;
                }
                break;
            }
        }
    } else {
        kind = 2;
    }
    if (id == 0x40CC) {
        n = PartyCollectLiveMemberIds_2cd6e0(ids);
        BZERO(cnt, 0x30);
        tbl = *(Tbl10 *)D_00451120;
        sel = -1;
        for (i4 = 0; i4 < n; i4++) {
            pids = &ids[i4];
            pcnt = &cnt[i4];
            *pcnt = 0;
            obj = ActorFindById_3eb870(gm, *pids);
            if (obj == 0) {
                continue;
            }
            for (j3 = 0; j3 < 10; j3++) {
                if (obj->has(tbl.v[j3]) == 0) {
                    continue;
                }
                (*pcnt)++;
                if (*pcnt >= 2) {
                    sel = *pids;
                    break;
                }
            }
        }
        if (sel == -1) {
            for (i5 = 0; i5 < n; i5++) {
                if (cnt[i5] > 0) {
                    sel = ids[i5];
                    break;
                }
            }
        }
        if (sel == -1) {
            return 1;
        }
        kind = 0;
    }
    switch (kind) {
    case 0:
        CharaQueueItemUse_2ef680(a, *(s16 *)(ent + 4), sel, 1, 0x7FFE);
        break;
    case 2:
        CharaQueueItemUse_2ef680(a, *(s16 *)(ent + 4), -2, 1, 0x7FFE);
        break;
    }
    return 1;
}
