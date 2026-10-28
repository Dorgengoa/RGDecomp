/* rgp:protos */
#define RGP_SELF_title_TitleLoadProgressWindowShow_4ede10 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* title.bin overlay, 0x004EDE10 -- tail call into main, arguments SHIFTED:
 * the two incoming arguments become a1/a2 and a gp-relative global becomes a0.
 * The daddu pair through $2 is register allocation, not source.
 */

extern void *D_00484174;
/*rgp*/

void title_TitleLoadProgressWindowShow_4ede10(void *b, void *c)
{
    SaveProgressWindowShow_377690(D_00484174, b, c);
}
