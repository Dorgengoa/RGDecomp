/* rgp:protos */
#define RGP_SELF_insect_InsectCmdMenuInit_4efd80 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x004EFD80 -- 3-instruction leaf. */
typedef struct QRec { s32 f00; s32 f04; } QRec;

void insect_InsectCmdMenuInit_4efd80(QRec *p, s32 v)
{
    p->f00 = v;
    p->f04 = 0;
}
