#include "types.h"

typedef struct Pool {
    u8  pad000[0x7C];
    s16 count;
} Pool;

extern Pool *D_004830F8;
extern s16   D_004830FC;
extern s32   D_00480234;
extern s32   VariantGetInt_15f780(void);

s32 DataTableCmdRevelationBoardSetCellValue_4089f0(void)
{
    Pool *p = D_004830F8;
    s32 n = p->count;
    s32 i;

    if (n <= 0) return 1;
    i = D_004830FC;
    if (i - 1 >= n) return 1;
    D_00480234 = VariantGetInt_15f780();
    return 1;
}
