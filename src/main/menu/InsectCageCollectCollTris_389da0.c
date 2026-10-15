#include "types.h"

typedef struct O_FUN_00389da0 O_FUN_00389da0;

extern void *D_004832C4;
extern s16 D_004832C8;
extern const u8 D_00454310[];
extern void *MemStackNew_14e1b0(s32 sz, s32 tag);
extern void *ConstructNewArray_100710(void *m, s32 a, s32 b, s32 c, s32 d);
extern O_FUN_00389da0 *MapMgrGetAuxAreaFwd_389e40(void);
extern s32 MapDataCollectCollTrisMaybe_1e6c80(O_FUN_00389da0 *o, void *p, s32 n, const u8 *q);

void InsectCageCollectCollTris_389da0(s32 a)
{
    O_FUN_00389da0 *o;

    D_004832C4 = ConstructNewArray_100710(MemStackNew_14e1b0(0x4990, a), 0, 0, 0x60, 0xC4);
    o = MapMgrGetAuxAreaFwd_389e40();
    if (o != 0) {
        D_004832C8 = MapDataCollectCollTrisMaybe_1e6c80(o, D_004832C4, 0xC4, D_00454310);
    }
}
