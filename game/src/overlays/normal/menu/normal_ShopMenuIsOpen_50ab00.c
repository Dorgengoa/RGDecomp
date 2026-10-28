/* rgp:protos */
#define RGP_SELF_normal_ShopMenuIsOpen_50ab00 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x0050AB00 -- `jr $31 / lbu $2, -0xB98($28)`.  A gp-relative byte
 * read returned straight out.  One of the 55 unnamed functions; see
 * scripts/n_unnamed.py. */
extern u8 D_004845D8;

s32 normal_ShopMenuIsOpen_50ab00(void)
{
    return D_004845D8;
}
