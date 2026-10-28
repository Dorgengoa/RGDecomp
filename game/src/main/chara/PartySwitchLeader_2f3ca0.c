/* rgp:protos */
#define RGP_SELF_PartySwitchLeader_2f3ca0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Four 16-byte stack vectors: A(0xA0) B(0x90) C(0x80) D(0x70).  The last
   declared gets the lowest address, so they are declared A,B,C,D.
   The two entities SWAP: e1 saves into A/B and later reads D/C, e2 saves
   into C/D and later reads B/A.
   The `if (q != 0) do { *q = 0; ... }` zero loop is the same inlined helper
   used by EvDoorObjAreaCheckFacingMaybe_3040b0.
   The final loop's latch is spelled `i <= 0xB`, not `i < 0xC`: the compare
   lands in $at unless the branch-taken condition is a bare `<`. */

extern f32 D_0047EFA0;
extern f32 D_0047EFA4;
extern f32 D_0047EFA8;
extern f32 D_0047EFAC;
extern f32 D_0047EFB0;
extern f32 D_0047EFB4;
extern f32 D_0047EFB8;
extern f32 D_0047EFBC;

typedef struct Scn {
    u8   pad0[0x14];
    void *f14;
    void *f18;
} Scn;

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
/*rgp*/
/*rgp*/
/*rgp*/

s32 PartySwitchLeader_2f3ca0(s32 id, s32 flag)
{
    f32 va[4] __attribute__((aligned(16)));
    f32 vb[4] __attribute__((aligned(16)));
    f32 vc[4] __attribute__((aligned(16)));
    f32 vd[4] __attribute__((aligned(16)));
    Scn *scn;
    void *mgr;
    void *e1;
    void *e2;
    void *o;
    u8 *q;
    u32 n;
    s32 cur;
    s32 i;

    scn = ((Scn *)GetGameData_1fede0());
    mgr = GetActionMgr_1fdb50();
    cur = *(s16 *)((u8 *)scn->f18 + 0x18E);
    if (id == cur) {
        return 0;
    }
    if (flag == 0) {
        o = ActionMgrFindById_233b50(mgr, cur);
        if (o != 0) {
            CharaResetAim_212b90(o, 0);
        }
    }
    e1 = ActionMgrFindById_233b50(mgr, cur);
    e2 = ActionMgrFindById_233b50(mgr, id);
    va[0] = D_0047EFA0;
    va[1] = D_0047EFA4;
    va[2] = D_0047EFA8;
    va[3] = D_0047EFAC;
    q = (u8 *)vb;
    n = 0x10;
    if (q != 0) {
        do {
            *q = 0;
            n--;
            q++;
        } while (n != 0);
    }
    vc[0] = D_0047EFB0;
    vc[1] = D_0047EFB4;
    vc[2] = D_0047EFB8;
    vc[3] = D_0047EFBC;
    q = (u8 *)vd;
    n = 0x10;
    if (q != 0) {
        do {
            *q = 0;
            n--;
            q++;
        } while (n != 0);
    }
    if (flag != 0) {
        if (e1 != 0) {
            CharaGetPos_2388a0(e1, va);
            CharaGetRot_2388b0(e1, vb);
        }
        if (e2 != 0) {
            CharaGetPos_2388a0(e2, vc);
            CharaGetRot_2388b0(e2, vd);
        }
    }
    o = PoolGetUsedElem_36acb0(*(void **)((u8 *)scn->f14 + 8), id);
    if (o == 0) {
        return 0;
    }
    if (CharaCanBeLeader_3ae200(o, 1, 0, 0) == 0) {
        return 0;
    }
    PartySetLeaderId_3c27c0(scn->f18, id);
    PartyUpdateLeaderFlags_1fc3c0();
    /* ONE `return 1`: retail's beql targets the epilogue with the
       `addiu $2,$0,1` duplicated into its delay slot. */
    if (flag != 0) {
        if (e1 != 0) {
            CharaSetYaw_2138f0(e1, vd[1]);
            CharaSetPos_213a40(e1, vc);
            CharaSavePlacedPosMaybe_238270(e1);
        }
        if (e2 != 0) {
            CharaSetYaw_2138f0(e2, vb[1]);
            CharaSetPos_213a40(e2, va);
            CharaSavePlacedPosMaybe_238270(e2);
        }
        for (i = 0; i <= 0xB; i++) {
            o = ActionMgrFindById_233b50(mgr, i);
            if (o != 0) {
                CharaResetBattleStateMaybe_212f20(o, 0);
            }
        }
    }
    return 1;
}
