/* rgp:protos */
#line 1
#include "types.h"

class Unit {
public:
    VC_VPTR_MEMBER;     
         
         
         
         
         
         
         
         
       
    s32 Qty() { return VCM0(s32, 0xF0); } /* 0xF0 */
         
         
         
         
         
         
         
    s32 Has(s32 a0) { return VCM(s32, (void *, s32), 0x19C, a0); } /* 0x19C */
         
         
         
         
         
         
         
         
         
         
         
         
         
         
         
         
         
         
         
         
         
         
         
         
         
         
        
    s32 Busy() { return VCM0(s32, 0x424); } /* 0x424 */
};

typedef struct Ent {
    u8 pad0[0x13C];
    s16 x13C;
    u8 pad13E[0x148 - 0x13E];
    s16 x148;
    u8 pad14A[0x16A - 0x14A];
    u8 x16A;
} Ent;

typedef struct Chr {
    u8 pad0[0x3D0];
    u64 x3D0;
} Chr;

typedef struct Gm {
    u8 pad0[0x14];
    s32 x14;
    u8 pad18[4];
    s32 x1C;
} Gm;

extern "C" {
Gm *GetGameData_1fede0(void);
Ent *CharaGetAiById_2cedd0(s32);
Unit *ObjFindById_3bb3a0(s32, s32);
Unit *CharaMgrPoolFindById_3a8c60(s32, s32);
s32 TargetMngHasTargetId_313bf0(void);
s32 ActionMgrFindByIdGlobal_2cee10(s32);
s32 CharaGetTargetRef_214a30(s32);
s32 TargetRefGetId_2e7120(s32);
void AiLinkTargetsMaybe_2ce660(s32, s32, s32);
s32 CopyWords_1d7ca0(s32 *, s32 *, s32);
s32 ArrayCopyExcept_1d7c50(s32 *, s32 *, s32, s32);
s32 IntArrayFindIndex_1d7cd0(s32, s32 *, s32);
s32 GetActionMgr_1fdb50(void);
Chr *ActionMgrFindById_233b50(s32, s32);
s32 BattleFindNearestTarget_2ce520(s32, s32, s32 *, s32);
s32 ActorGetHpById_2cd870(s32, s32);
extern u8 D_004DB920[];
extern s32 D_004DB924[];
extern s32 D_004DB97C[];
extern s32 D_004DBA40[];
extern s32 D_004DBA44[];
extern s32 D_004DBA84[];
extern s32 D_004DBA88[];
void BattleAiTargetRefreshMaybe_2cdd80(s32);
}

extern "C" void BattleAiTargetRefreshMaybe_2cdd80(s32 ctx)
{
    s32 A[32] __attribute__((aligned(16)));
    s32 B[32] __attribute__((aligned(16)));
    s32 tmp[32] __attribute__((aligned(16)));
    s32 t160[32] __attribute__((aligned(16)));
    s32 tE0[32] __attribute__((aligned(16)));
    Gm *gm;
    s32 i;
    s32 k;
  s32 k_w165;
  s32 k_w142;
    s32 id;
    s32 busy;
    s32 na;
    s32 nb;
    s32 j;
    s32 *pp;
    s32 *dst;
    s32 *src;
    s32 c1;
    s32 c2;
    s32 n;
    s32 x;
    s32 r;
    s32 c;
    s32 mx;
    s32 best;
    s32 c2b;
    s32 mb;
    s32 bb;
    s32 h;
    s32 w;
    Unit *u;
    Ent *e;
    Chr *ch;

    gm = GetGameData_1fede0();
    if (D_004DBA40[0] == 0 || D_004DBA84[0] == 0) {
        return;
    }
    for (i = 0; i < D_004DB97C[0]; i++) {
        id = *(s32 *)(D_004DB920 + i * 4 + 0x60);
        if (id < 0) {
            continue;
        }
        e = CharaGetAiById_2cedd0(id);
        if (e != 0) {
            e->x148 = -1;
            e->x16A = 0;
        }
    }
    na = 0;
    nb = 0;
    busy = 0;
    for (i = 0; i < D_004DBA84[0]; i++) {
        u = ObjFindById_3bb3a0(gm->x1C, *(s32 *)(D_004DB920 + i * 4 + 0x168));
        if (u == 0) {
            continue;
        }
        if (u->Busy()) {
            busy++;
        }
    }
    for (i = 0; i < D_004DBA84[0]; i++) {
        pp = (s32 *)(D_004DB920 + i * 4 + 0x168);
        u = ObjFindById_3bb3a0(gm->x1C, *pp);
        if (u == 0) {
            continue;
        }
        if (u->Qty() <= 0) {
            continue;
        }
        if (u->Has(3) && !u->Busy() && !(D_004DBA84[0] - busy < 2)) {
            A[na++] = *pp;
        } else if (!u->Has(3) && u->Busy()) {
            A[na++] = *pp;
        } else {
            B[nb++] = *pp;
        }
    }
    for (i = 0; i < D_004DBA40[0]; i++) {
        pp = (s32 *)(D_004DB920 + i * 4 + 0x124);
        u = CharaMgrPoolFindById_3a8c60(gm->x14, *pp);
        if (u == 0) {
            continue;
        }
        if (u->Qty() <= 0) {
            continue;
        }
        if (u->Has(3)) {
            B[nb++] = *pp;
        } else {
            A[na++] = *pp;
        }
    }
    id = D_004DB924[0];
    CharaGetAiById_2cedd0(id);
    if (((unsigned char)TargetMngHasTargetId_313bf0())) {
        w = ActionMgrFindByIdGlobal_2cee10(id);
        if (w != 0) {
            w = CharaGetTargetRef_214a30(w);
            if (w != 0) {
                AiLinkTargetsMaybe_2ce660(id, ((short)TargetRefGetId_2e7120(w)), 0);
            }
        }
    }
    for (j = 0; j < na; j++) {
        id = A[j];
        if (id == D_004DB924[0]) {
            continue;
        }
        c1 = ArrayCopyExcept_1d7c50(tmp, tmp, CopyWords_1d7ca0(tmp, D_004DBA88, D_004DBA84[0]), id);
        dst = tmp;
        src = tmp;
        for (k = 0; k < c1; k++, src++) {
            u = ObjFindById_3bb3a0(gm->x1C, *src);
            if (u == 0) {
                continue;
            }
            if (!u->Busy()) {
                *dst++ = *src;
            }
        }
        c2 = dst - tmp;
        x = GetActionMgr_1fdb50();
        dst = tmp;
        src = tmp;
        for (k = 0; k < c2; k++, src++) {
            ch = ActionMgrFindById_233b50(x, *src);
            if (ch == 0) {
                continue;
            }
            if (!(ch->x3D0 & 0x10000)) {
                *dst++ = *src;
            }
        }
        n = dst - tmp;
        if (D_004DBA84[0] < na) {
            r = BattleFindNearestTarget_2ce520(ctx, id, tmp, n);
        } else {
            if (n > 0) {
                if (n > 1) {
                mx = 0;
                best = 0;
                for (k_w142 = 0; k_w142 < n; k_w142++) {
                    e = CharaGetAiById_2cedd0(tmp[k_w142]);
                    if (e == 0) {
                        continue;
                    }
                    if (mx <= e->x16A) {
                        mx = e->x16A;
                        best = k_w142;
                    }
                }
                c = ArrayCopyExcept_1d7c50(t160, tmp, n, tmp[best]);
                }
            } else {
                c = CopyWords_1d7ca0(t160, tmp, n);
            }
            r = BattleFindNearestTarget_2ce520(ctx, id, t160, c);
        }
        if (r < 0) {
            r = BattleFindNearestTarget_2ce520(ctx, id, tmp, n);
        }
        AiLinkTargetsMaybe_2ce660(id, r, 0);
    }
    for (k_w165 = 0; k_w165 < nb; k_w165++) {
        id = B[k_w165];
        e = CharaGetAiById_2cedd0(id);
        if (e == 0) {
            continue;
        }
        r = -1;
        c2b = ArrayCopyExcept_1d7c50(tE0, tE0, CopyWords_1d7ca0(tE0, D_004DBA44, D_004DBA40[0]), id);
        c2b = (s32)(u32)c2b;
        if (c2b > 1 && c2b < nb) {
            mb = 0;
            bb = 0;
            for (i = 0; i < c2b; i++) {
                Ent *f = CharaGetAiById_2cedd0(tE0[i]);
                if (f == 0) {
                    continue;
                }
                if (mb <= f->x16A) {
                    mb = f->x16A;
                    bb = i;
                }
            }
            c2b = ArrayCopyExcept_1d7c50(tE0, tE0, c2b, tE0[bb]);
        }
        h = e->x13C;
        if (ActorGetHpById_2cd870(h, 0) > 0 && IntArrayFindIndex_1d7cd0(h, tE0, c2b) >= 0) {
            r = h;
        }
        if (r < 0) {
            r = BattleFindNearestTarget_2ce520(ctx, id, tE0, c2b);
        }
        if (r < 0) {
            r = BattleFindNearestTarget_2ce520(ctx, id, D_004DBA44, D_004DBA40[0]);
        }
        AiLinkTargetsMaybe_2ce660(id, r, 0);
    }
}
