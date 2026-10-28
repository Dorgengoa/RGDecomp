/* rgp:protos */
#define RGP_SELF_ResGroupCmdObjLinkSlot_42a8f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* The two range guards branch the same way -> `&&'.  The scan is a for(;;)
   with two breaks: retail's back edge is the `bnel' whose delay slot holds
   the q += 2.  The addu operand order needs the NAMED product `off'. */

typedef struct Tok {
    s32 a;
    s32 b;
} Tok;

extern void *D_00483FE0;

/*rgp*/
/*rgp*/

s32 ResGroupCmdObjLinkSlot_42a8f0(Tok *p)
{
    void *t;
    s32 a;
    s32 b;
    s32 off;
    s32 *slot;
    s32 *q;

    t = ResGroupListCurElem_42a510();
    if (t == 0) {
        return 1;
    }
    a = VariantGetInt_15f780(p++);
    b = VariantGetInt_15f780(p++);
    if (a >= 0 && a < 8) {
        off = a * 4;
        slot = (s32 *)(off + (s32)t + 0x20);
        *slot = 0;
        q = *(s32 **)D_00483FE0;
        for (;;) {
            if (q[0] < 0) {
                break;
            }
            if (q[0] == b) {
                *slot = q[1];
                break;
            }
            q += 2;
        }
    }
    return 1;
}
