/* PARKED at triage (0 round trips): VariantSetS32_36f040 call-site arg-count
 * mismatch (same pattern as ScriptFnPartyMoveToReserve_3d8710/ScriptFnCharaSetAltFormFlagMaybe_3d81e0, already parked
 * elsewhere) combined with an unresolved "?" sp60 stack local passed by
 * address -- compounding risk not worth taking without a raw-asm read.
 * Deferred to preserve lane throughput. See asm/matchings/main/ScriptFnPartyJoin_3d8800.s. */
/* s49m: 45 bad (right length) */
#include "types.h"
#include "vec.h"

struct Obj {
    virtual void v000();
    virtual void v001();
    virtual void v002();
    virtual void v003();
    virtual void v004();
    virtual void v005();
    virtual void v006();
    virtual void v007();
    virtual void v008();
    virtual void v009();
    virtual void v010();
    virtual void v011();
    virtual void v012();
    virtual void v3C();  /* +0x3C */
    virtual void v014();
    virtual void v015();
    virtual void v016();
    virtual void v017();
    virtual void v018();
    virtual void v019();
    virtual void v020();
    virtual void v021();
    virtual void v022();
    virtual void v023();
    virtual void v024();
    virtual void v025();
    virtual void v026();
    virtual void v027();
    virtual void v028();
    virtual void v029();
    virtual void v030();
    virtual void v031();
    virtual void v032();
    virtual void v033();
    virtual void v034();
    virtual void v035();
    virtual void v036();
    virtual void v037();
    virtual void v038();
    virtual void v039();
    virtual void v040();
    virtual void v041();
    virtual void v042();
    virtual void v043();
    virtual void v044();
    virtual void v045();
    virtual s32 vC0();  /* +0xC0 */
    virtual void v047();
    virtual void v048();
    virtual void v049();
    virtual void v050();
    virtual void v051();
    virtual void v052();
    virtual void v053();
    virtual void v054();
    virtual void v055();
    virtual void v056();
    virtual void v057();
    virtual void v058();
    virtual void vF4(s32);  /* +0xF4 */
    u8 pad4[8];
    s32 mC;
};

struct G {
    u8 pad0[0x14];
    void *m14;
    void *m18;
};

extern G *D_00483960;
extern s32 D_00483964;
extern "C" {
void VariantSetS32_36f040(s32, s32, s32);
s16 VariantGetS16_36fcc0(u8 *);
Obj *CharaMgrPoolFindByDataId_3a8a70(void *, s64, s32, s32, s32, s32, s32);
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
    Vec4 v;
    Vec4 s;
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
    obj = CharaMgrPoolFindByDataId_3a8a70(D_00483960->m14, VariantGetS16_36fcc0(data), 1, 1, 0, 0, 0);
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
