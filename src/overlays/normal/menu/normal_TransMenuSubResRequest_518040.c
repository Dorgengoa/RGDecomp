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
extern s32   D_00525FB0[];
extern s8    D_00526590[];

extern void *func_15DE40(void);
extern void  func_158AC0(void *p, s32 k);
extern void  func_28B230(void *p);
extern void  func_28B610(void *p);
extern void *func_1F59D0(void);
extern void *func_1CDB10(void *h, s32 k);
extern s32   func_28B470(void *p, s32 a, s32 b, void *c, s32 d, s32 e);
extern s32   func_28B550(void *p, s32 a, s32 b, s32 c);
extern s32   func_28B220(void *p);

typedef struct Rec {
    u8 pad000[56];
} Rec;

s32 normal_TransMenuSubResRequest_518040(s32 id)
{
    s32 *tab;
    s32  i;
    s32 count;

    func_158AC0(func_15DE40(), 0x32C);
    D_00484794 = NULL;
    tab = &D_00525FB0[(s16)id];
    if ((s16)id == 0) {
        tab = D_004806D0;
    }
    count = D_00526590[(u32)(s16)id];
    for (i = 0; i < count; i++) {
        func_28B230(&((Rec *)D_0048478C)[i]);
        func_28B610(&((Rec *)D_0048478C)[i]);
        if ((u32)(s16)id == 1) {
            D_00484784 = func_1CDB10(func_1F59D0(), 0xF081);
            func_28B470(&((Rec *)D_0048478C)[i], tab[(u32)i], 1, D_00484784,
                        0xF080, 0);
        } else {
            func_28B550(&((Rec *)D_0048478C)[i], tab[(u32)i], 1, 0);
        }
        if (func_28B220(&((Rec *)D_0048478C)[i]) == -1) {
            return 1;
        }
    }
    D_004806CC = id;
    return 0;
}
