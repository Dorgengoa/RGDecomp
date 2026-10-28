/* rgp:protos */
#define RGP_SELF_MemStackAddChild_14d650 1
#include "port/game_protos.h"
#line 1
/* MemStackAddChild_14d650 -- shape-identical to merged FrameAddChild_149d70 (18 instructions); the donor's
   source with the symbol renamed, 1 call target(s) and 2 immediate(s) substituted:
     FrameAppendSibling_149dc0 -> MemStackAppendSibling_14d6a0
     imm 4 -> 64
     imm 8 -> 76
   Found by build/zz/s23_xclone.py. */
#include "types.h"

struct Obj1;

struct Obj0 {
    u8  pad000[76];
    struct Obj1 *m08;
};

struct Obj1 {
    u8  pad000[64];
    struct Obj0 *m04;
};

/*rgp*/

void MemStackAddChild_14d650(struct Obj0 *p0, struct Obj1 *p1)
{
    if (p1 != 0) {
        if (p0->m08 != 0) {
            MemStackAppendSibling_14d6a0(p0->m08, (void *)p1);
        } else {
            p0->m08 = p1;
        }
        p1->m04 = p0;
    }
}
