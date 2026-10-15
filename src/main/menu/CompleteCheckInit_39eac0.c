#include "types.h"

typedef struct Obj_FUN_0039eac0 Obj_FUN_0039eac0;
typedef struct P_FUN_0039eac0 P_FUN_0039eac0;

extern s16 D_004836AC;
extern Obj_FUN_0039eac0 *D_00483688;
extern u8 D_004836A4;
extern s16 D_004836A8;
extern u8 D_004836A0;
extern s16 D_0047FFD0;
extern Obj_FUN_0039eac0 *GetMenuTransdataStack_206a60(void);
extern void MemStackReset_14d830(Obj_FUN_0039eac0 *o);
extern P_FUN_0039eac0 *GetDrawCtxNameTable_15de40(void);
extern void NameTableFreeGroup_158ac0(P_FUN_0039eac0 *p, s32 n);
extern void CompleteCheckResRequest_39ec70(void);
extern void CompleteCheckResPoll_39eb80(void);

void CompleteCheckInit_39eac0(void)
{
    Obj_FUN_0039eac0 *o;
    P_FUN_0039eac0 *p;

    D_004836AC = 0;
    o = GetMenuTransdataStack_206a60();
    D_00483688 = o;
    MemStackReset_14d830(o);
    D_004836A4 = 0;
    D_004836A8 = 1;
    D_004836A0 = 1;
    D_0047FFD0 = 1;
    p = GetDrawCtxNameTable_15de40();
    NameTableFreeGroup_158ac0(p, 0x32D);
    CompleteCheckResRequest_39ec70();
    CompleteCheckResPoll_39eb80();
}
