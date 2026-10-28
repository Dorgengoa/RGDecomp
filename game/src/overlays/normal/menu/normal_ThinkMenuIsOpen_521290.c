/* rgp:protos */
#define RGP_SELF_normal_ThinkMenuIsOpen_521290 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x00521290 -- `jr $31 / lbu $2, -0x838($28)`.  A gp-relative byte
 * read returned straight out.  One of the 55 unnamed functions; see
 * scripts/n_unnamed.py. */
extern u8 D_00484938;

s32 normal_ThinkMenuIsOpen_521290(void)
{
    return D_00484938;
}
