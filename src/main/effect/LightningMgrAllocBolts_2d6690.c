#include "types.h"

extern s32 ConstructNewArray_100710(s32, void *, s32, s32, s32);
extern s32 MemStackNew_14e1b0(s32);
extern void LightningBoltInit_2d6750(s32);
extern void LightningBoltCtor_2d6720(void);

void LightningMgrAllocBolts_2d6690(s32 *arg0) {
    s32 i;

    *arg0 = ConstructNewArray_100710(MemStackNew_14e1b0(0x3410), (void *)LightningBoltCtor_2d6720, 0, 0xD0, 0x40);
    i = 0;
    do {
        LightningBoltInit_2d6750(*arg0 + (i * 0xD0));
        i += 1;
    } while (i < 0x40);
}
