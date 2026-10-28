/* rgp:protos */
#define RGP_SELF_normal_TransMenuIsOpen_516a50 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x00516A50 -- `jr $31 / lbu $2, -0xA28($28)`.  A gp-relative byte
 * read returned straight out.  One of the 55 unnamed functions; see
 * scripts/n_unnamed.py. */
extern u8 D_00484748;

s32 normal_TransMenuIsOpen_516a50(void)
{
    return D_00484748;
}
