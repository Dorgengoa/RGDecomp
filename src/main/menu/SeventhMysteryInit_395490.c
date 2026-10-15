#include "types.h"

typedef struct Obj_FUN_00395490 Obj_FUN_00395490;
typedef struct P_FUN_00395490 P_FUN_00395490;

extern s32 D_00483468;
extern s16 D_0048348C;
extern Obj_FUN_00395490 *D_0048346C;
extern u8 D_00483484;
extern s16 D_00483488;
extern u8 D_00483480;
extern s16 D_0047FF20;
extern s32 SceneSoundGetSlot0HandleCur_207df0(void);
extern Obj_FUN_00395490 *GetMenuTransdataStack_206a60(void);
extern void MemStackReset_14d830(Obj_FUN_00395490 *o);
extern P_FUN_00395490 *GetDrawCtxNameTable_15de40(void);
extern void NameTableFreeGroup_158ac0(P_FUN_00395490 *p, s32 n);
extern void SeventhMysteryResRequest_395660(void);
extern void SeventhMysteryResPoll_395560(void);

void SeventhMysteryInit_395490(void)
{
    Obj_FUN_00395490 *o;
    P_FUN_00395490 *p;

    D_00483468 = SceneSoundGetSlot0HandleCur_207df0();
    D_0048348C = 0;
    o = GetMenuTransdataStack_206a60();
    D_0048346C = o;
    MemStackReset_14d830(o);
    D_00483484 = 0;
    D_00483488 = 1;
    D_00483480 = 1;
    D_0047FF20 = 1;
    p = GetDrawCtxNameTable_15de40();
    NameTableFreeGroup_158ac0(p, 0x32D);
    SeventhMysteryResRequest_395660();
    SeventhMysteryResPoll_395560();
}
