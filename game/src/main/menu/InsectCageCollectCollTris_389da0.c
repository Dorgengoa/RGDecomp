/* rgp:protos */
#define RGP_SELF_InsectCageCollectCollTris_389da0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct O_FUN_00389da0 O_FUN_00389da0;

extern void *D_004832C4;
extern s16 D_004832C8;
extern u8 D_00454310[];
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void InsectCageCollectCollTris_389da0(s32 a)
{
    O_FUN_00389da0 *o;

    D_004832C4 = ConstructNewArray_100710(MemStackNew_14e1b0(0x4990, a), 0, 0, 0x60, 0xC4);
    o = ((O_FUN_00389da0 *)MapMgrGetAuxAreaFwd_389e40());
    if (o != 0) {
        D_004832C8 = MapDataCollectCollTrisMaybe_1e6c80(o, D_004832C4, 0xC4, D_00454310);
    }
}
