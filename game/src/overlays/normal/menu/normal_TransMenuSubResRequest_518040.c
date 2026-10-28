/* rgp:protos */
#define RGP_SELF_normal_TransMenuSubResRequest_518040 1
#include "port/game_protos.h"
#line 1
/* NORMAL 0x00518040, 348 function bytes; following four bytes are alignment.
 * Cache the signed byte count before constructors. Keep the signed table
 * index separate from the unsigned count/guard view: retail extends id twice.
 * The second extension remains live across the loop for the id == 1 guard.
 * func_1CDB10 forwards its second argument through 0014dcf0 to 0014dd20.
 */
#include "types.h"

extern void *D_00484794;          
extern void *D_0048478C;          
extern void *D_00484784;          
extern s16   D_004806CC;          
extern s32   D_004806D0[1];       
extern s32   normal_D_00525FB0[];
extern s8    normal_D_00526590[];

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

typedef struct Rec {
    u8 pad000[56];
} Rec;

s32 normal_TransMenuSubResRequest_518040(s32 id)
{
    s32 *tab;
    s32  i;
    s32 count;

    NameTableFreeGroup_158ac0(GetDrawCtxNameTable_15de40(), 0x32C);
    D_00484794 = NULL;
    tab = &normal_D_00525FB0[(s16)id];
    if ((s16)id == 0) {
        tab = D_004806D0;
    }
    count = normal_D_00526590[(u32)(s16)id];
    for (i = 0; i < count; i++) {
        LoadHandleFree_28b230(&((Rec *)D_0048478C)[i]);
        LoadHandleInit_28b610(&((Rec *)D_0048478C)[i]);
        if ((u32)(s16)id == 1) {
            D_00484784 = HeapHandleAllocBack_1cdb10(GetLoaderMgr_1f59d0(), 0xF081);
            LoadHandleRequest_28b470(&((Rec *)D_0048478C)[i], tab[(u32)i], 1, D_00484784,
                        0xF080, 0);
        } else {
            LoadHandleRequestFile_28b550(&((Rec *)D_0048478C)[i], tab[(u32)i], 1, 0);
        }
        if (LoadHandleGetId_28b220(&((Rec *)D_0048478C)[i]) == -1) {
            return 1;
        }
    }
    D_004806CC = id;
    return 0;
}
