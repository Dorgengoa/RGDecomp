/* rgp:protos */
#define RGP_SELF_insect_InsectFormationInit_4efe50 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x004EFE50 -- a 4-instruction leaf.  Retail stores +0x04 FIRST, then
 * +0x00, then +0x08 in the `jr`'s delay slot, so the block is written in that
 * order rather than ascending. */
typedef struct QRec {
    s32 f00;
    s32 f04;
    s32 f08;
} QRec;

void insect_InsectFormationInit_4efe50(QRec *p, s32 v)
{
    p->f04 = v;
    p->f00 = 0;
    p->f08 = 0;
}
