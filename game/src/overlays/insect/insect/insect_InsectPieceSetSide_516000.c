/* rgp:protos */
#define RGP_SELF_insect_InsectPieceSetSide_516000 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x00516000 -- 20 bytes, 5 instructions.  Two flag bytes written in
 * SOURCE order 0x71 then 0x70, then a tail `j` to the refresh with both float
 * arguments zero (`mtc1 $0,$f12` + `mov.s $f13,$f12` -- one zero, reused). */

typedef struct Sub {
    u8 pad00[0x70];
    s8 f70;                         /* +0x70 */
    s8 f71;                         /* +0x71 */
} Sub;

/*rgp*/

void insect_InsectPieceSetSide_516000(Sub *s, s8 v)
{
    s->f71 = v;
    s->f70 = v;
    insect_InsectPieceSetYawTarget_5156d0(s, 0.0f, 0.0f);
}
