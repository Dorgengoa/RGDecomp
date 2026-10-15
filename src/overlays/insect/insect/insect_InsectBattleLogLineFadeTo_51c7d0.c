#include "types.h"
/* insect 0x0051C7D0 -- 13 instructions, no frame.  The `dsll32/dsra32 ..,24`
 * pair into a FRESH register (retail keeps $6 for the final `sb`) is an s8
 * PARAMETER promoted for the negation, not an (s8) cast of an s32 -- the cast
 * spelling reuses $6.  The guard loads 0x52 BEFORE 0x51, so m52 is the LEFT
 * operand of the compare. */

typedef struct Obj {
    u8 pad00[0x51];
    u8 m51;                         /* +0x51 */
    u8 m52;                         /* +0x52 */
    s8 m53;                         /* +0x53 */
} Obj;

void insect_InsectBattleLogLineFadeTo_51c7d0(Obj *p, s32 a, s8 b)
{
    p->m52 = a;
    p->m53 = -b;
    if (p->m52 > p->m51) {
        p->m53 = b;
    }
}
