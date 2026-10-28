/* rgp:protos */
#define RGP_SELF_Get 1
#define RGP_SELF_ModelObjUpdate_1adf90 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    u8 pad[0x170];
} E1adf90;

typedef struct N1adf90 {
    struct N1adf90 *next;
    u8 pad4[0x10];
    s32 unk14;
} N1adf90;

typedef struct {
    u8 pad0[0x1F0];
    u8 unk1F0[0x14];
    s32 count;
    E1adf90 *base;
    u8 pad20c[0x14];
    N1adf90 *list;
    u8 pad224[0x23C];
    s32 unk460;
    s32 unk464;
    u8 unk468;
} O1adf90;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

static inline E1adf90 *Get(O1adf90 *o, s32 i)
{
    if (o->base == NULL || o->count == 0) {
        return NULL;
    }
    if (i < 0 || i >= o->count) {
        return NULL;
    }
    return &o->base[i];
}

void ModelObjUpdate_1adf90(O1adf90 *arg0, f32 f) {
    E1adf90 *e;
    N1adf90 *n;
    s32 i;
    s32 k;
    s32 j;
    s32 cnt;
    u8 flag;

    for (i = 0; i < arg0->count; i++) {
        e = Get(arg0, i);
        if (e == NULL) {
            break;
        }
        DynClothRefreshPoseFramesMaybe_16a240(e);
    }
    MotionListUpdateAll_171e40(arg0->unk1F0, f);
    ModelObjSyncShadowModelFrames_1adbc0(arg0);
    for (n = arg0->list; n != NULL; n = n->next) {
        if (n->unk14 != 0) {
            TexAnimSeqUpdate_163dd0(n->unk14, f);
        }
    }
    if (arg0->unk464 != 0) {
        for (i = 0; i < arg0->count; i++) {
            e = Get(arg0, i);
            if (e == NULL) {
                break;
            }
            DynClothResetToRest_16a340(e);
        }
        if (arg0->unk464 > 0x1E) {
            arg0->unk464 = 0x1E;
        }
        if (arg0->unk464 > 1) {
            flag = arg0->unk468;
            cnt = arg0->unk464 - 1;
            for (k = 0; k < cnt; k++) {
                if (flag) {
                    ModelObjSyncShadowModelFrames_1adbc0(arg0);
                }
                if (arg0->unk460 != 0) {
                    for (j = 0; j < arg0->count; j++) {
                        e = Get(arg0, j);
                        if (e == NULL) {
                            break;
                        }
                        DynClothSubstep_1697c0(e);
                    }
                }
            }
        }
        if (arg0->unk468) {
            ModelObjSyncShadowModelFrames_1adbc0(arg0);
        }
        arg0->unk464 = 0;
        arg0->unk468 = 0;
    }
    if (arg0->unk460 != 0) {
        for (i = 0; i < arg0->count; i++) {
            e = Get(arg0, i);
            if (e == NULL) {
                break;
            }
            DynClothSubstep_1697c0(e);
        }
    }
}
