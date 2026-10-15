#include "types.h"
#pragma opt_common_subs off

extern void VecCopy_1cbe30(void *, void *);
extern s32 InsectCageMgrFindSlotById_39b0c0(void);
extern void InsectCageSlotGetRot_39b320(s32, void *);
extern void InsectCageSlotGetPos_39b340(s32, void *);

typedef struct {
    u8 pad0[0xF0];
    s32 unkF0;
    s32 unkF4;
} Obj0039AFB0;

void CagePlaceCursorSetFromSlot_39afb0(Obj0039AFB0 *arg0, s32 arg1) {
    s32 temp_2;

    temp_2 = InsectCageMgrFindSlotById_39b0c0();
    if (temp_2 != 0) {
        InsectCageSlotGetPos_39b340(temp_2, (u8 *)arg0 + 0xB0);
        InsectCageSlotGetRot_39b320(temp_2, (u8 *)arg0 + 0xC0);
        VecCopy_1cbe30((u8 *)arg0 + 0xD0, (u8 *)arg0 + 0xB0);
        VecCopy_1cbe30((u8 *)arg0 + 0xE0, (u8 *)arg0 + 0xC0);
        arg0->unkF0 = arg1;
        arg0->unkF4 = 0;
    }
}
