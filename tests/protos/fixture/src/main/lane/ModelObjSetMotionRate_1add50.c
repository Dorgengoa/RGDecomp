#include "types.h"
/* the float in the third slot: EE int/float lanes are independent */
extern s32 MotionListSetRateById_172110(s32, s32, f32, s32);

void ModelObjSetMotionRate_1add50(void *m, f32 vol)
{
    MotionListSetRateById_172110(m, 0, vol, 3);
}
