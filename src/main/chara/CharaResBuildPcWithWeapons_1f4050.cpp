#include "types.h"

typedef struct {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    u8 unk6;
    u8 pad7[0x5d];
    s16 unk64;
} T1f4050_arg0;

extern "C" {
s32 CharaDataGetKind4NodeDataMaybe_1ed460(u8 *, s16, s32, s32 *, s32 *);
s32 CharaDataGetLoadState_1ed5a0(u8 *, s32);
u8 *CharaDataGetNodeModel_1ed540(u8 *, s32, s32);
s32 CharaDataFindNode_1ed6d0(u8 *, s32, s32, s32);
u8 *CharaDataNodeGetSubObj_1eeb30(s32, s32);
void GameSceneObjBindMaybe_1cfcd0(s32, s32, u8 *, s32);
void ObjRecSetFlag2_1c3e80(s32, s32, s32);
u8 *GetCharaDataMgr_1fdb70();
s32 GetActionMgr_1fdb50();
u8 *ActionMgrFindById_233b50(s32, s32);
u8 *CharaGetAi_214a10(u8 *);
void AiScriptLoad_2bbc50(u8 *, s32, s32, s32, s32);
void AiResetState_2bbc30(u8 *);
}

static inline s32 slotOf(s16 k, s32 off)
{
    bool ok = false;

    if (k >= 0 && k < 12) {
        ok = true;
    }
    if (ok) {
        return k * 4 + off;
    }
    return -1;
}

extern "C" void CharaResBuildPcWithWeapons_1f4050(T1f4050_arg0 *arg0, s32 arg1)
{
    u8 *mgr;
    s32 kind;
    s32 st;
    u8 *e;
    s32 sl;
    s32 h;
    u8 *e2;
    s32 sp7C;
    s32 sp78;
    s32 r;
    u8 *o;
    u8 *o2;

    mgr = GetCharaDataMgr_1fdb70();
    kind = arg0->unk2;
    if (kind == 0x2F11) {
        kind = 0x2B00;
    }
    st = CharaDataGetLoadState_1ed5a0(mgr, arg0->unk4);
    if (st != 2 && st != 4) {
    if (!(arg0->unk6 & 1)) {
        if ((e = CharaDataGetNodeModel_1ed540(mgr, arg0->unk4, 0)) != NULL) {
            GameSceneObjBindMaybe_1cfcd0(arg1, arg0->unk0, e, 0);
            ObjRecSetFlag2_1c3e80(arg1, 1, arg0->unk0);
            *(s32 *)(e + 0x464) = 0x1F;
            *(s8 *)(e + 0x468) = 0;
            arg0->unk6 |= 1;
        }
    }
    if (!(arg0->unk6 & 2)) {
        if ((e = CharaDataGetNodeModel_1ed540(mgr, arg0->unk4, 2)) != NULL) {
            sl = slotOf(arg0->unk0, 0xC);
            GameSceneObjBindMaybe_1cfcd0(arg1, sl, e, 0);
            ObjRecSetFlag2_1c3e80(arg1, 1, sl);
            *(s32 *)(e + 0x464) = 0x1F;
            *(s8 *)(e + 0x468) = 0;
            arg0->unk6 |= 2;
            if (kind == 0x2AFC || kind == 0x2B00) {
                h = CharaDataFindNode_1ed6d0(GetCharaDataMgr_1fdb70(), arg0->unk4, 2, 0);
                if (h != 0) {
                    e2 = CharaDataNodeGetSubObj_1eeb30(h, 0);
                    if (e2 != NULL) {
                        GameSceneObjBindMaybe_1cfcd0(arg1, slotOf(arg0->unk0, 0xD), e2, 0);
                    }
                }
            }
        }
    }
    if (!(arg0->unk6 & 4)) {
        if ((e = CharaDataGetNodeModel_1ed540(mgr, arg0->unk4, 3)) != NULL) {
            sl = slotOf(arg0->unk0, 0xE);
            GameSceneObjBindMaybe_1cfcd0(arg1, sl, e, 0);
            *(s32 *)(e + 0x464) = 0x1F;
            *(s8 *)(e + 0x468) = 0;
            ObjRecSetFlag2_1c3e80(arg1, 1, sl);
            arg0->unk6 |= 4;
            if (kind == 0x2AFD) {
                h = CharaDataFindNode_1ed6d0(GetCharaDataMgr_1fdb70(), arg0->unk4, 3, 0);
                if (h != 0) {
                    e2 = CharaDataNodeGetSubObj_1eeb30(h, 0);
                    if (e2 != NULL) {
                        GameSceneObjBindMaybe_1cfcd0(arg1, slotOf(arg0->unk0, 0xF), e2, 0);
                    }
                }
            }
        }
    }
    if (!(arg0->unk6 & 8)) {
        r = CharaDataGetKind4NodeDataMaybe_1ed460(mgr, arg0->unk4, -1, &sp7C, &sp78);
        if (r != 0 && sp7C != 0) {
            o = ActionMgrFindById_233b50(GetActionMgr_1fdb50(), arg0->unk0);
            if (o != NULL) {
                o2 = CharaGetAi_214a10(o);
                if (o2 != NULL) {
                    AiScriptLoad_2bbc50(o2, r, sp7C, sp78, 0);
                    AiResetState_2bbc30(o2);
                }
                arg0->unk6 |= 8;
            }
        }
    }
    arg0->unk6 |= 0x80;
    arg0->unk64 = 3;
    }
}
