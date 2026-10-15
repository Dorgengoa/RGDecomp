#include "types.h"
/* insmenu 0x004F6E20 -- store the argument into a gp s16, then TAIL CALL.
 * `ori $5, $0, 0x88BC` rather than `addiu`: 0x88BC does not fit a signed
 * 16-bit immediate, which is the recorded tell for a plain id constant. */
extern s16 D_00484380;      /* gp - 0xDF0 */
extern u8 D_004842E8;       /* gp - 0xE88, passed by address */
extern void func_28EDE0(void *a, s32 id, s32 c);

void insmenu_InsectVsSaveSetError_4f6e20(s32 a)
{
    D_00484380 = a;
    func_28EDE0(&D_004842E8, 0x88BC, 0);
}
