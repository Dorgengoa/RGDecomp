/* rgp:protos */
#define RGP_SELF_CompleteCheckInit_39eac0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Obj_FUN_0039eac0 Obj_FUN_0039eac0;
typedef struct P_FUN_0039eac0 P_FUN_0039eac0;

extern s16 D_004836AC;
extern Obj_FUN_0039eac0 *D_00483688;
extern u8 D_004836A4;
extern s16 D_004836A8;
extern u8 D_004836A0;
extern s16 D_0047FFD0;
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void CompleteCheckInit_39eac0(void)
{
    Obj_FUN_0039eac0 *o;
    P_FUN_0039eac0 *p;

    D_004836AC = 0;
    o = ((Obj_FUN_0039eac0 *)GetMenuTransdataStack_206a60());
    D_00483688 = o;
    MemStackReset_14d830(o);
    D_004836A4 = 0;
    D_004836A8 = 1;
    D_004836A0 = 1;
    D_0047FFD0 = 1;
    p = ((P_FUN_0039eac0 *)GetDrawCtxNameTable_15de40());
    NameTableFreeGroup_158ac0(p, 0x32D);
    CompleteCheckResRequest_39ec70();
    CompleteCheckResPoll_39eb80();
}
