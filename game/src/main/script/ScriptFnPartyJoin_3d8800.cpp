/* rgp:protos */
#line 1
/* PARKED at triage (0 round trips): VariantSetS32_36f040 call-site arg-count
 * mismatch (same pattern as ScriptFnPartyMoveToReserve_3d8710/ScriptFnCharaSetAltFormFlagMaybe_3d81e0, already parked
 * elsewhere) combined with an unresolved "?" sp60 stack local passed by
 * address -- compounding risk not worth taking without a raw-asm read.
 * Deferred to preserve lane throughput. See asm/matchings/main/ScriptFnPartyJoin_3d8800.s. */
/* s49m: 45 bad (right length) */
#include "types.h"
#include "vec.h"

struct Obj {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    void v3C() { VCM0(void, 0x3C); }  /* +0x3C */
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 vC0() { return VCM0(s32, 0xC0); }  /* +0xC0 */
    
    
    
    
    
    
    
    
    
    
    
    
    void vF4(s32 a0) { VCM(void, (void *, s32), 0xF4, a0); }  /* +0xF4 */
    u8 pad4[8];
    s32 mC;
};

struct G {
    u8 pad0[0x14];
    void *m14;
    void *m18;
};

extern "C" G *D_00483960;
extern "C" s32 D_00483964;
extern "C" {
void VariantSetS32_36f040(s32, s32, s32);
s16 VariantGetS16_36fcc0(u8 *);
Obj * CharaMgrPoolFindByDataId_3a8a70(void *, int, s32, s32, s32, s32, s32);
void CharaSetFlag234Bit2Related_3ae370(Obj *, s32);
s32 PartyPromoteReserve_3c17c0(void *, s32, s32, s32);
void PartyRefreshMembersMaybe_2f40b0(s32);
s32 GetActionMgr_1fdb50(void);
s32 ActionMgrFindById_233b50(s32, s32);
f32 VariantGetFloat_36f7a0(u8 *);
void CharaSetPosVec_2387a0(s32, Vec4 *);
void CharaSetRotFromVec_2387b0(s32, Vec4 *);
}

extern "C" void ScriptFnPartyJoin_3d8800(s32 a0, s32 a1, s32 lvl, u8 *data)
{
    Vec4 v __attribute__((aligned(16)));
    Vec4 s __attribute__((aligned(16)));
    Obj *obj;
    s32 h;
    s32 p;
    s32 q;

    if (a0 == 0) {
        return;
    }
    VariantSetS32_36f040(a0, 0, 1);
    if (D_00483960 == 0 || D_00483964 == 0) {
        return;
    }
    if (data == 0 || lvl <= 0) {
        return;
    }
    obj = CharaMgrPoolFindByDataId_3a8a70(D_00483960->m14, (int)(VariantGetS16_36fcc0(data)), 1, 1, 0, 0, 0);
    if (obj == 0) {
        return;
    }
    h = obj->mC;
    CharaSetFlag234Bit2Related_3ae370(obj, 0);
    VariantSetS32_36f040(a0, PartyPromoteReserve_3c17c0(D_00483960->m18, h, 1, 0) != 0, 1);
    if (obj->vC0()) {
        obj->vF4(1);
        obj->v3C();
    }
    if (lvl < 4) {
        return;
    }
    PartyRefreshMembersMaybe_2f40b0(1);
    p = GetActionMgr_1fdb50();
    if (p == 0) {
        return;
    }
    q = ActionMgrFindById_233b50(p, h);
    if (q == 0) {
        return;
    }
    v.x = VariantGetFloat_36f7a0(data + 0x38);
    v.y = VariantGetFloat_36f7a0(data + 0x70);
    v.z = VariantGetFloat_36f7a0(data + 0xA8);
    v.w = 1.0f;
    CharaSetPosVec_2387a0(q, &v);
    if (lvl < 5) {
        return;
    }
    v.x = 1.0f;
    v.y = VariantGetFloat_36f7a0(data + 0xE0);
    v.z = 1.0f;
    v.w = 1.0f;
    CharaSetRotFromVec_2387b0(q, &s);
}
