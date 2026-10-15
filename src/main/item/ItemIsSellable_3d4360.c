#include "types.h"

typedef struct { u8 pad[0x1F]; s8 bit : 1; s8 pad2 : 7; } BF;
extern s32 InsectRecSlotCountItems_3cfb80(s32);
extern s32 CageRecIsPlaced_3d0d20(s32);
extern s32 InvObjCastToCage_3d3c80(void *);
extern s32 InvObjCastToItem4B0_3d3cd0(void *);
extern s32 PartyFindItemHolder_3d4c20(void);

s32 ItemIsSellable_3d4360(void *arg0) {
    s32 temp_2_2;
    s32 t;
    s32 temp_2_3;
    void *temp_2;

    temp_2 = *(void **)((u8 *)arg0 + 0x10);
    if (temp_2 == NULL) {
        return 0;
    }
    if (!((BF *)temp_2)->bit) {
        return 0;
    }
    t = PartyFindItemHolder_3d4c20() != 0;
    if (t) {
        return 0;
    }
    temp_2_2 = InvObjCastToItem4B0_3d3cd0(arg0);
    if (temp_2_2 != 0 && CageRecIsPlaced_3d0d20(temp_2_2) != 0) {
        return 0;
    }
    temp_2_3 = InvObjCastToCage_3d3c80(arg0);
    if (temp_2_3 != 0 && InsectRecSlotCountItems_3cfb80(temp_2_3) > 0) {
        return 0;
    }
    return 1;
}
