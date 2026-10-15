#include "types.h"
/* normal 0x00516A40 -- `sltu $3, $0, $4 / jr $31 / sb $3, -0xA28($28)`.
 * `sltu $3, $0, $4` is `0 < (unsigned)a`, i.e. the `a != 0` bool built in one
 * expression -- the recorded u8-bool idiom, stored to the gp flag
 * normal_TransMenuIsOpen_516a50 reads back.  One of the 55 unnamed functions. */
extern u8 D_00484748;

void normal_TransMenuSetOpen_516a40(s32 a)
{
    D_00484748 = a != 0;
}
