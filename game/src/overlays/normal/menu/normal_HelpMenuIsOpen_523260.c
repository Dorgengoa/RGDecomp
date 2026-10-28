/* rgp:protos */
#define RGP_SELF_normal_HelpMenuIsOpen_523260 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x00523260 -- `jr $31 / lbu $2, -0x7B8($28)`.  A gp-relative byte
 * read returned straight out.  One of the 55 unnamed functions; see
 * scripts/n_unnamed.py. */
extern u8 D_004849B8;

s32 normal_HelpMenuIsOpen_523260(void)
{
    return D_004849B8;
}
