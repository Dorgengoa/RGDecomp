/* rgp:protos */
#define RGP_SELF_MinimapMgrSelectActive_321f60 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct { u8 pad[0x510]; s32 f510; } T;

/*rgp*/
/*rgp*/

void MinimapMgrSelectActive_321f60(T *p, void *rgp_a1)
{
    p->f510 = MinimapMgrFindSlotByName_322340(p, (void *)rgp_a1);
    if (p->f510 != 0) {
        MinimapFadeIn_329ef0(p->f510, 10.0f);
    }
}
