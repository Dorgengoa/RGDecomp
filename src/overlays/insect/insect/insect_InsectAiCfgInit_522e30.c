#include "types.h"
/* insect 0x00522E30 -- 24 B / 6 words.  Branch-free, five stores of $0 through
 * $4: three words then two halfwords.  A straight zero-init in ascending
 * offset order; nothing is scheduled out of place, so the emission order IS
 * the source order. */
typedef struct Rec {
    s32 f00;
    s32 f04;
    s32 f08;
    s16 f0C;
    s16 f0E;
} Rec;

void insect_InsectAiCfgInit_522e30(Rec *o)
{
    o->f00 = 0;
    o->f04 = 0;
    o->f08 = 0;
    o->f0C = 0;
    o->f0E = 0;
}
