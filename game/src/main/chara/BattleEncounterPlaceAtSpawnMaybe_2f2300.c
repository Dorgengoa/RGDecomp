/* rgp:protos */
#define RGP_SELF_BattleEncounterPlaceAtSpawnMaybe_2f2300 1
#define RGP_SELF_GetE 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_propagation off

typedef struct J { f32 x, y, z, w; s32 pad; } J;
typedef struct K { u8 pad[8]; f32 x, y, z, w; u8 pad2[4]; } K;
typedef struct E {
    u8 pad[0x44];
    f32 x, y, z, w;
    s32 pad54;
    J j[1];
    u8 pad6C[0x7E - 0x6C];
    s8 flag : 1; s8 rest : 7;
    u8 pad7F;
    K *k;
} E;
typedef struct X { u8 pad[0xC]; s32 id; } X;
typedef struct Ref { X *x; s32 pad; } Ref;
typedef struct Sub238 { u8 pad[0x18]; E *e; u8 pad1C[0x44 - 0x1C]; s16 n; u8 pad46[0x4C - 0x46]; Ref r[1]; } Sub238;
typedef struct Sub20 { u8 pad[0x238]; Sub238 *s; } Sub20;
typedef struct Sub18 { u8 pad[0x18E]; s16 id; } Sub18;
typedef struct Root { u8 pad[0x18]; Sub18 *f18; s32 pad1C; Sub20 *f20; } Root;
typedef struct V { f32 v[4]; } V;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

static inline E *GetE(Sub20 *p) {
    if (p->s != 0) return p->s->e;
    return 0;
}

s32 BattleEncounterPlaceAtSpawnMaybe_2f2300(void) {
    V v __attribute__((aligned(16)));
    s32 ctx;
    Root *root;
    E *e;
    s32 o;
    s32 n;
    s32 i;
    Sub238 *s;
    s32 j;
    s32 p;

    ctx = ((s32)GetActionMgr_1fdb50());
    root = ((Root *)GetGameData_1fede0());
    e = GetE(root->f20);
    if (e == 0) return 0;
    if (CharaSysStateFlag24Bit2Related_3a3880(root->f20) == 0 && e->flag) {
        o = ((s32)ActionMgrFindById_233b50(ctx, root->f18->id));
        if (o != 0) {
            CharaSetYaw_2138f0(o, e->w);
            CharaSetPosXYZ_2139e0(o, e->x, e->y, e->z);
            CharaSavePlacedPosMaybe_238270(o);
        }
        n = PartyCountExcludingLeader_3c2610(root->f18, 1, 1);
        for (i = 0; i < n; i++) {
            o = ((s32)ActionMgrFindById_233b50(ctx, ((short)PartyGetNonLeaderId_3c2750(root->f18, i))));
            if (o != 0) {
                CharaSetPosXYZ_2139e0(o, e->j[i].x, e->j[i].y, e->j[i].z);
                CharaSetYaw_2138f0(o, e->j[i].w);
                CharaSavePlacedPosMaybe_238270(o);
            }
        }
    }
    if (CharaSysStateFlag24Bit2Related_3a3880(root->f20) != 0 || e->flag) {
        s = root->f20->s;
        for (j = 0; j < s->n; j++) {
            p = ((s32)ActionMgrFindById_233b50(ctx, s->r[j].x->id));
            if (p != 0) {
                CharaSetPosXYZ_2139e0(p, e->k[j].x, e->k[j].y, e->k[j].z);
                CharaSetYaw_2138f0(p, e->k[j].w);
                CharaGetPos_2388a0(p, &v);
                CameraWarpHookNopMaybe_1cad10();
            }
        }
    }
    return 1;
}
