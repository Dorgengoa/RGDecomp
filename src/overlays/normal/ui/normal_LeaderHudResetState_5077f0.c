#include "types.h"
/* normal 0x005077F0 -- tear down the 0x14-byte record at D_00527C20.  The
 * record is OVERLAY data reached absolutely, so it must be declared as an
 * incomplete array to stay OUT of small data. */
extern s32   D_00527C20[];
extern void *D_00484560;          /* gp - 0xC10 */
extern s32   D_0048457C;          /* gp - 0xBF4 */
extern void func_131B60(void *p, s32 v, s32 n);
extern void func_28EDE0(void *w, s32 id, s32 a);
extern s32 normal_LeaderHudResetState_5077f0(void *p, s32 b);
s32 normal_LeaderHudResetState_5077f0(void *p, s32 b)
{
    if (b != 0) {
        func_131B60(D_00527C20, 0, 0x14);
        D_00527C20[0] = -1;
        func_28EDE0(D_00484560, 0x59DB, 0);
        D_0048457C = 0;
    }
    return 1;
}
