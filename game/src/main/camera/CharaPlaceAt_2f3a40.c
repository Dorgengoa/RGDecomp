/* rgp:protos */
#define RGP_SELF_CharaPlaceAt_2f3a40 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Three guards all branch the SAME way -> one && chain.
   Stack locals: last-declared gets the LOWEST address, so v (0xA0) is
   declared before w (0x90). */

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
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void CharaPlaceAt_2f3a40(s32 id, f32 *dst, void *c, f32 t)
{
    f32 v[4] __attribute__((aligned(16)));
    f32 w[4] __attribute__((aligned(16)));
    void *scn;
    void *mgr;
    void *ent;
    void *cam;
    void *o;
    void *p;

    scn = GetGameData_1fede0();
    mgr = GetActionMgr_1fdb50();
    ent = ActionMgrFindById_233b50(mgr, id);
    if (ent == 0) {
        return;
    }
    cam = GetCurrentScene_1f5be0();
    ParamTableSetAlpha_1cfb10(cam, id, 0.0f);
    ParamTableFadeToOne_1cf9e0(cam, id, c);
    VecCopy_1cbe30(v, dst);
    if (id >= 0 && id < 0xC && id != 0) {
        if (GetGameMode_1f59c0() != 5) {
            o = ActionMgrFindById_233b50(mgr, *(s16 *)((u8 *)*(void **)((u8 *)scn + 0x18) + 0x18E));
            if (o != 0) {
                CharaGetPos_2388a0(o, w);
                p = GetMapMgr_201a90();
                o = MapFindBlockAtPos_1e3a00(p, w, 0.0f);
                if (o != 0) {
                    o = MapDataIsJasterOnly_1e7a90(o);
                    if (o != 0) {
                        p = MapGetAreaSlot1_1e5750(p);
                        if (p != 0) {
                            if (MapDataIsLoaded_1e79d0(p) != 0) {
                                MapDataGetPosVec4_1e7740(p, v);
                            }
                        }
                    }
                }
            }
        }
    }
    EventObjMgrMovePosOutOfVolumesMaybe_2d0740(((void)(CharaGetCollIgnoreMask_238950(ent)), v), 0.0f);
    CharaSetPos_213a40(ent, v);
    CharaSetYaw_2138f0(ent, t);
    CharaResetBattleStateMaybe_212f20(ent, 1);
    o = ObjRecGetLiveObject_1c4a90(cam, id);
    if (o != 0) {
        *(s32 *)((u8 *)o + 0x464) = 0x1F;
        *(s8 *)((u8 *)o + 0x468) = 0;
    }
    o = GetLiveObjById_1ce420(id, -10);
    if (o != 0) {
        *(s32 *)((u8 *)o + 0x464) = 0x1F;
        *(s8 *)((u8 *)o + 0x468) = 0;
    }
    o = GetLiveObjById_1ce420(id, -11);
    if (o != 0) {
        *(s32 *)((u8 *)o + 0x464) = 0x1F;
        *(s8 *)((u8 *)o + 0x468) = 0;
    }
    o = GetLiveObjById_1ce420(id, -20);
    if (o != 0) {
        *(s32 *)((u8 *)o + 0x464) = 0x1F;
        *(s8 *)((u8 *)o + 0x468) = 0;
    }
    o = GetLiveObjById_1ce420(id, -21);
    if (o != 0) {
        *(s32 *)((u8 *)o + 0x464) = 0x1F;
        *(s8 *)((u8 *)o + 0x468) = 0;
    }
}
