/* rgp:protos */
#define RGP_SELF_normal_BtlChgPageInit_5062f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x005062F0 -- the longer sibling of normal_BtlChgPageResetState_506290. */
typedef struct Obj {
    u8  pad000[0x74];
    s16 f074;
    s16 f076;
    s16 f078;
    u8  pad07A[0x43C - 0x7A];
    s16 f43C;
    s16 f43E;
    s32 f440;
    u8  pad444[0x44C - 0x444];
    s16 f44C;
    s16 f44E;
    s16 f450;
    s16 f452;
    s8  f454;
    u8  pad455[1];
    s8  f456;
} Obj;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 normal_BtlChgPageInit_5062f0(Obj *p)
{
    UiPageClearMemStack_289c50(p);
    normal_BtlChgPageSetStateId_5061d0(p, -1);
    normal_BtlChgPageSetCommand_505da0(p, -1);
    normal_BtlChgPageSetCloseCode_505fc0(p, 0);
    p->f43E = 0;
    p->f440 = 0;
    p->f074 = 0;
    p->f076 = 0;
    p->f078 = 0;
    p->f43C = 0;
    p->f44C = 0;
    p->f44E = 0;
    p->f454 = 0;
    p->f450 = -1;
    p->f452 = -1;
    p->f456 = 0;
    return 0;
}
