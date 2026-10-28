/* rgp:protos */
#define RGP_SELF_LeaderRideObjIsStillMaybe_2f5270 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Inner001fede0 {
    u8 pad00[0x18E];
    s16 unk18E;
} Inner001fede0;

typedef struct Obj001fede0 {
    u8 pad00[0x18];
    Inner001fede0 *unk18;
} Obj001fede0;

typedef struct Obj00233b50 {
    u8 pad00[0x3D8];
    s32 unk3D8;
} Obj00233b50;

typedef struct Obj00238450 {
    u8 pad00[0x40];
    s16 unk40;
} Obj00238450;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 LeaderRideObjIsStillMaybe_2f5270(void) {
    u8 sp20[16] __attribute__((aligned(16)));
    s32 temp_16_2;
    Obj001fede0 *temp_16;
    Obj00233b50 *temp_2;

    temp_16 = ((Obj001fede0 *)GetGameData_1fede0());
    temp_2 = ((Obj00233b50 *)ActionMgrFindById_233b50(((s32)GetActionMgr_1fdb50()), temp_16->unk18->unk18E));
    if (temp_2 == NULL) {
        return 0;
    }
    if (!(temp_2->unk3D8 & 4)) {
        return 0;
    }
    temp_16_2 = ((s32)GetEventObjMgr_2d1960());
    EventObjMgrGetPosRecPosById_2e8950(temp_16_2, sp20, ((Obj00238450 *)CharaGetGroundTri_238450(temp_2, 0))->unk40);
    if (VecLengthSq_1cb470(sp20, 0) != 0.0f) {
        return 0;
    }
    return 1;
}
