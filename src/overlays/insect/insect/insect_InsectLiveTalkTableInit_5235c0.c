#include "types.h"
/* insect 0x005235C0 -- 24 B / 6 words.  `sw $0, 0x98($28)` is D_00485208
 * (_gp = 0x00485170, so _gp+0x98) set back to NULL: the same context global
 * insect_InsectLiveTalkTableLoad_523540 publishes around its run call and insect_InsectLiveTalkTableCmdNextRecord_5235e0 reads.
 * It is written FIRST, ahead of the four word clears through the parameter --
 * stores are not reordered against one another, so that is source order. */
typedef struct Rec {
    s32 f00;
    s32 f04;
    s32 f08;
    s32 f0C;
} Rec;

extern void *D_00485208;

void insect_InsectLiveTalkTableInit_5235c0(Rec *o)
{
    D_00485208 = 0;
    o->f00 = 0;
    o->f04 = 0;
    o->f08 = 0;
    o->f0C = 0;
}
