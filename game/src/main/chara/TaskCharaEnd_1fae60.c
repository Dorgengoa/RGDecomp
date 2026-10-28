/* rgp:protos */
#define RGP_SELF_TaskCharaEnd_1fae60 1
#define RGP_SELF_chk 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct { f32 x, y, z, w; } Vec;

typedef struct Obj {
    u8 pad0[0x3D0];
    s64 f3d0;
    s32 f3d8;
} Obj;

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
extern u8 D_0045B080[0x400];
extern u8 D_004B8680[0x400];

static inline s32 chk(Obj *o) { return (o->f3d0 & 0x0100000000000000LL) != 0; }

void TaskCharaEnd_1fae60(void)
{
    Vec pos __attribute__((aligned(16)));
    Vec dir __attribute__((aligned(16)));
    u8 *node;
    Obj *o;
    f32 scale;
    f32 range;
    f32 r;
    s16 k;

    ActionMgrPostUpdateAll_232670(D_004B8680);
    node = ((u8 *)DListGetHead_42ea60(((s32)ActionMgrGetCharaList_233b40(D_004B8680))));
    scale = *(f32 *)D_0045B080;
    range = 2.0f * scale;
    while (node != 0) {
        o = (Obj *)(node + 0x10);
        node = ((u8 *)DListGetNext_42eb30(node));
        if (((short)CharaGetId_214a80(o)) < 0) continue;
        if (((short)CharaGetId_214a80(o)) >= 12) continue;
        if (!chk(o) == 0) continue;
        if ((o->f3d8 & 0x10) &&
            (k = *(s16 *)(((u8 *)CharaGetWaterTriMaybe_2383d0(o, 0)) + 0x40), k >= 0x40) && k < 0x50) {
            if (((unsigned char)CharaIsDeadBodyKeptMaybe_210ae0(o)) != 0 && (!(o->f3d8 & 4) || !(CharaGetHeightAboveGround_238380(o) <= range))) {
                GameFlowGetBattleCenter_283390(&pos);
                r = RandRangeFloat_1ca5d0(2.0f); pos.x += (r - 1.0f) * scale;
                r = RandRangeFloat_1ca5d0(2.0f); pos.z += (r - 1.0f) * scale;
                CharaGetRot_2388b0(o, &dir);
                CharaPlaceAt_2f3a40(((short)CharaGetId_214a80(o)), &pos, 15, dir.y);
            } else if (((unsigned char)CharaIsHeadUnderwaterMaybe_238250(o)) != 0) {
                CharaRequestTint_213fd0(o, 1, 2, 250.0f, 118.0f, 80.0f, 90.0f, 18.0f);
            } else {
                CharaRequestTint_213fd0(o, 2, 2, 250.0f, 118.0f, 80.0f, 90.0f, 18.0f);
            }
        } else if (o->f3d8 & 1) {
            k = *(s16 *)(((u8 *)CharaGetGroundTri_238450(o, 0)) + 0x40);
            if (k >= 0x40 && k < 0x50) {
                CharaRequestTint_213fd0(o, 2, 2, 250.0f, 118.0f, 80.0f, 90.0f, 18.0f);
            }
        }
    }
}
