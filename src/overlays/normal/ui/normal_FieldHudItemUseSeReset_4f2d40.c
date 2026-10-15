#include "types.h"
/* normal 0x004F2D40 -- invalidates the formation panel's two cached slots. */
extern s32 D_004804A4;            /* gp - 0x4CCC */
extern s32 D_004804A8;            /* gp - 0x4CC8 */
extern void normal_FieldHudItemUseSeReset_4f2d40(void);
void normal_FieldHudItemUseSeReset_4f2d40(void)
{
    D_004804A4 = -1;
    D_004804A8 = -1;
}
