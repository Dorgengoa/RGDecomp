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
    virtual void vf54(); virtual void vf55(); virtual void vf56(); virtual void vf57();
    virtual s32 Qty(void); /* 0xF0 */
    virtual void vf59(); virtual void vf60(); virtual void vf61(); virtual void vf62(); virtual void vf63(); virtual void vf64();
    virtual void vf65(); virtual void vf66(); virtual void vf67(); virtual void vf68(); virtual void vf69(); virtual void vf70();
    virtual void vf71(); virtual void vf72(); virtual void vf73(); virtual void vf74(); virtual void vf75(); virtual void vf76();
    virtual void vf77(); virtual void vf78(); virtual void vf79(); virtual void vf80(); virtual void vf81(); virtual void vf82();
    virtual void vf83(); virtual void vf84(); virtual void vf85(); virtual void vf86(); virtual void vf87(); virtual void vf88();
    virtual void vf89(); virtual void vf90(); virtual void vf91(); virtual void vf92(); virtual void vf93(); virtual void vf94();
    virtual void vf95(); virtual void vf96(); virtual void vf97(); virtual void vf98(); virtual void vf99(); virtual void vf100();
    virtual s32 Has(s32); /* 0x19C */
    virtual void vf102(); virtual void vf103(); virtual void vf104(); virtual void vf105(); virtual void vf106(); virtual void vf107();
    virtual void vf108(); virtual void vf109(); virtual void vf110(); virtual void vf111(); virtual void vf112(); virtual void vf113();
    virtual void vf114(); virtual void vf115(); virtual void vf116(); virtual void vf117(); virtual void vf118(); virtual void vf119();
    virtual void vf120(); virtual void vf121(); virtual void vf122(); virtual void vf123(); virtual void vf124(); virtual void vf125();
    virtual void vf126(); virtual void vf127(); virtual void vf128(); virtual void vf129(); virtual void vf130(); virtual void vf131();
    virtual void vf132(); virtual void vf133(); virtual void vf134(); virtual void vf135(); virtual void vf136(); virtual void vf137();
    virtual void vf138(); virtual void vf139(); virtual void vf140(); virtual void vf141(); virtual void vf142(); virtual void vf143();
    virtual void vf144(); virtual void vf145(); virtual void vf146(); virtual void vf147(); virtual void vf148(); virtual void vf149();
    virtual void vf150(); virtual void vf151(); virtual void vf152(); virtual void vf153(); virtual void vf154(); virtual void vf155();
    virtual void vf156(); virtual void vf157(); virtual void vf158(); virtual void vf159(); virtual void vf160(); virtual void vf161();
    virtual void vf162(); virtual void vf163(); virtual void vf164(); virtual void vf165(); virtual void vf166(); virtual void vf167();
    virtual void vf168(); virtual void vf169(); virtual void vf170(); virtual void vf171(); virtual void vf172(); virtual void vf173();
    virtual void vf174(); virtual void vf175(); virtual void vf176(); virtual void vf177(); virtual void vf178(); virtual void vf179();
    virtual void vf180(); virtual void vf181(); virtual void vf182(); virtual void vf183(); virtual void vf184(); virtual void vf185();
    virtual void vf186(); virtual void vf187(); virtual void vf188(); virtual void vf189(); virtual void vf190(); virtual void vf191();
    virtual void vf192(); virtual void vf193(); virtual void vf194(); virtual void vf195(); virtual void vf196(); virtual void vf197();
    virtual void vf198(); virtual void vf199(); virtual void vf200(); virtual void vf201(); virtual void vf202(); virtual void vf203();
    virtual void vf204(); virtual void vf205(); virtual void vf206(); virtual void vf207(); virtual void vf208(); virtual void vf209();
    virtual void vf210(); virtual void vf211(); virtual void vf212(); virtual void vf213(); virtual void vf214(); virtual void vf215();
    virtual void vf216(); virtual void vf217(); virtual void vf218(); virtual void vf219(); virtual void vf220(); virtual void vf221();
    virtual void vf222(); virtual void vf223(); virtual void vf224(); virtual void vf225(); virtual void vf226(); virtual void vf227();
    virtual void vf228(); virtual void vf229(); virtual void vf230(); virtual void vf231(); virtual void vf232(); virtual void vf233();
    virtual void vf234(); virtual void vf235(); virtual void vf236(); virtual void vf237(); virtual void vf238(); virtual void vf239();
    virtual void vf240(); virtual void vf241(); virtual void vf242(); virtual void vf243(); virtual void vf244(); virtual void vf245();
    virtual void vf246(); virtual void vf247(); virtual void vf248(); virtual void vf249(); virtual void vf250(); virtual void vf251();
    virtual void vf252(); virtual void vf253(); virtual void vf254(); virtual void vf255(); virtual void vf256(); virtual void vf257();
    virtual void vf258(); virtual void vf259(); virtual void vf260(); virtual void vf261(); virtual void vf262();
    virtual s32 Busy(void); /* 0x424 */
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
    s32 A[32];
    s32 B[32];
    s32 tmp[32];
    s32 t160[32];
    s32 tE0[32];
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
    if (TargetMngHasTargetId_313bf0()) {
        w = ActionMgrFindByIdGlobal_2cee10(id);
        if (w != 0) {
            w = CharaGetTargetRef_214a30(w);
            if (w != 0) {
                AiLinkTargetsMaybe_2ce660(id, TargetRefGetId_2e7120(w), 0);
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
