/* rgp:protos */
#define RGP_SELF_normal_BtlChgPageResetState_506290 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x00506290 -- three resets on the same object, then a store run. */
typedef struct Obj {
    u8  pad000[0x43E];
    s16 f43E;
    s32 f440;
    u8  pad444[0x44E - 0x444];
    s16 f44E;
    s16 f450;
    s16 f452;
    s8  f454;
} Obj;

/*rgp*/
/*rgp*/
/*rgp*/

s32 normal_BtlChgPageResetState_506290(Obj *p)
{
    normal_BtlChgPageSetStateId_5061d0(p, -1);
    normal_BtlChgPageSetCommand_505da0(p, -1);
    normal_BtlChgPageSetCloseCode_505fc0(p, 0);
    p->f43E = 0;
    p->f440 = 0;
    p->f44E = 0;
    p->f454 = 0;
    p->f450 = -1;
    p->f452 = -1;
    return 0;
}
