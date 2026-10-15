#include "types.h"

class VO24dc90 {
public:
    u8 pad0[0x1B0];
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
    virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20();
};

extern "C" {

typedef struct {
    u8 pad0[0x8];
    u32 state;
    u8 padC[0x4];
    s32 m10;
    u8 pad14[0x8];
    s32 id;
    s32 m20;
    s32 m24;
    s32 *list;
    s32 count;
    s32 m30;
    u8 pad34[0x4];
    s32 m38;
    s32 m3C;
    u8 pad40[0x4];
    s32 m44;
    u8 pad48[0xD4 - 0x48];
    s32 mD4;
} Ctl24dc90;

typedef struct {
    u8 pad0[0x4];
    s32 m4;
    u8 pad8[0x28 - 0x8];
    s8 m28;
} Sub24dc90;

typedef struct VT24dc90 {
    u8 pad0[0x58];
    void (*f58)(void *);
} VT24dc90;

extern void Sprintf_1343b8(char *, char *, s32);
extern void FrameSetDirty_14a5e0(Sub24dc90 *);
extern Sub24dc90 *ModelGetRootFrame_1511a0(u8 *);
extern void NameTableFreeGroup_158ac0(u8 *, s32);
extern void DrawCtxVif1HandlerStop_15dc40(void);
extern u8 *GetDrawCtxNameTable_15de40(void);
extern s32 ArrayGetChecked_1ad400(u8 *, s32);
extern void ModelObjExRemoveAttachById_1b0b10(u8 *, s32);
extern void ObjRecClearFlags_1c3dc0(s32, s32, s32, s32);
extern void RecStackPop_1c4140(s32, s32);
extern u8 *ObjRecGetLiveObject_1c4a90(s32, s32);
extern void ObjRecReleaseResAndReset_1c4c70(s32, s32);
extern void LoaderReleaseById_1cd340(s32, s32);
extern void GameSceneObjSetCBlurMaybe_1cf900(s32, s32, s32, f32);
extern void GameSceneSoundSlot6Free_1d0850(s32);
extern s32 GetLoaderMgr_1f59d0(void);
extern void EventCastDataGroupIdFree_250380(void);
extern char *strcpy(char *, const char *);
extern char D_0045EB70[];

}

extern "C" void EventCastRecordRelease_24dc90(Ctl24dc90 *arg0, s32 arg1)
{
    char buf[0x20];
    u8 *g;
    s32 h;
    u8 *o;
    Sub24dc90 *s;
    s32 v;
    u8 *g2;
    u8 *o2;
    s32 i;

    DrawCtxVif1HandlerStop_15dc40();
    g = GetDrawCtxNameTable_15de40();
    h = GetLoaderMgr_1f59d0();
    LoaderReleaseById_1cd340(h, arg0->m24);
    LoaderReleaseById_1cd340(h, arg0->m38);
    if (arg0->m10 >= 0) {
        if ((o = ObjRecGetLiveObject_1c4a90(arg1, arg0->id)) != NULL) {
            s = ModelGetRootFrame_1511a0(o);
            if (s != NULL && s->m28 != 0) {
                s->m4 = 0;
            }
        }
        v = arg0->mD4;
        if (v != 0) {
            s = ModelGetRootFrame_1511a0(o);
            if (s != NULL) {
                s->m28 = 1;
                s->m4 = v;
                FrameSetDirty_14a5e0(s);
            }
        }
        GameSceneObjSetCBlurMaybe_1cf900(arg1, arg0->id, 0, 1.0f);
        if (o != NULL && ArrayGetChecked_1ad400(o, 0) != 0) {
            *(s32 *)(o + 0x460) = 1;
        }
        ObjRecClearFlags_1c3dc0(arg1, 1, arg0->id, 0x8000);
        ObjRecClearFlags_1c3dc0(arg1, 1, arg0->id, 0x20);
        arg0->id = -1;
        arg0->m20 = -1;
        arg0->m24 = -1;
        arg0->m38 = -1;
        arg0->list = 0;
        arg0->count = 0;
        arg0->m30 = 0;
        arg0->m3C = 0;
        arg0->m44 = -1;
    } else {
        switch (arg0->state) {
        case 1:
        case 2:
        case 3:
        case 6:
        case 7:
            if (arg0->m20 <= -1 || arg0->id < 0x40 || arg0->id >= 0x80) {
                if ((o = ObjRecGetLiveObject_1c4a90(arg1, arg0->id)) != NULL) {
                    s = ModelGetRootFrame_1511a0(o);
                    if (s != NULL && s->m28 != 0) {
                        s->m4 = 0;
                    }
                }
            } else {
                g2 = GetDrawCtxNameTable_15de40();
                if ((o = ObjRecGetLiveObject_1c4a90(arg1, arg0->id)) != NULL) {
                    if (arg0->m44 < 0) {
                        v = *(s32 *)(o + 0x4DC);
                        if (v >= 0x209 && v < 0x249) {
                            NameTableFreeGroup_158ac0(g2, v);
                        }
                    }
                    ((VO24dc90 *)o)->v20();
                }
                ObjRecReleaseResAndReset_1c4c70(arg1, arg0->id);
            }
            break;
        case 5:
            if (arg0->m20 > -1) {
                if ((o2 = ObjRecGetLiveObject_1c4a90(arg1, arg0->id)) != NULL) {
                    g2 = GetDrawCtxNameTable_15de40();
                    Sprintf_1343b8(buf, D_0045EB70, arg0->id);
                    if (arg0->id >= 0x40 && arg0->id < 0x80) {
                        strcpy((char *)g2 + 0x1E4, buf);
                    }
                    for (i = 0; i < arg0->count; i++) {
                        ModelObjExRemoveAttachById_1b0b10(o2, arg0->list[i]);
                    }
                    if (arg0->id >= 0x40 && arg0->id < 0x80) {
                        g2[0x1E4] = 0;
                    }
                }
            }
            break;
        case 8:
            if (arg0->m20 >= 0) {
                NameTableFreeGroup_158ac0(g, arg0->id);
                EventCastDataGroupIdFree_250380();
            }
            break;
        case 9:
            GameSceneSoundSlot6Free_1d0850(arg1);
            break;
        }
        if (arg0->m20 > -1) {
            RecStackPop_1c4140(arg1, arg0->m20);
        }
        arg0->id = -1;
        arg0->m20 = -1;
        arg0->m24 = -1;
        arg0->m38 = -1;
        arg0->list = 0;
        arg0->count = 0;
        arg0->m30 = 0;
        arg0->m3C = 0;
        arg0->m44 = -1;
    }
}
