#include "types.h"
/* normal 0x00524590 -- `jr $31 / lbu $2, -0x7B8($28)`.  A gp-relative byte
 * read returned straight out.  One of the 55 unnamed functions; see
 * scripts/n_unnamed.py. */
extern u8 D_004849B8;

s32 normal_InsectEntryMenuIsOpen_524590(void)
{
    return D_004849B8;
}
