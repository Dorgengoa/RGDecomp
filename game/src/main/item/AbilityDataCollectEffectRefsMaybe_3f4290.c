/* rgp:protos */
#define RGP_SELF_AbilityDataCollectEffectRefsMaybe_3f4290 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

typedef struct Sub4290 { u8 pad[0x48]; s32 unk48; } Sub4290;
typedef struct Obj4290 { s32 unk0; Sub4290 *unk4; } Obj4290;
typedef struct Ret4290 { u8 pad[0x10]; s32 unk10; s32 unk14; } Ret4290;

s32 AbilityDataCollectEffectRefsMaybe_3f4290(Obj4290 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    Ret4290 *temp_2;

    if (arg0->unk4 == NULL) {
        return arg4;
    }
    if (arg1 == 0) {
        return arg4;
    }
    temp_2 = AbilityDataGetKind0Rec_3f5db0(arg1);
    if (temp_2 == NULL) {
        return arg4;
    }
    arg0 = (Obj4290 *)arg0->unk4->unk48;
    if (arg0 == NULL) {
        return arg4;
    }
    return BtlEffSetRowCollectRefsMaybe_3f9da0((s32)arg0, temp_2->unk14, arg2, arg3,
                         BtlEffSetRowCollectRefsMaybe_3f9da0((s32)arg0, temp_2->unk10, arg2, arg3, arg4));
}
