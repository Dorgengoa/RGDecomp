/* rgp:protos */
#define RGP_SELF_DamagePopupListReleaseHeap_2d2d50 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct T2D2D50 { void *f0; };

/*rgp*/

void DamagePopupListReleaseHeap_2d2d50(struct T2D2D50 *p)
{
    void *v;

    v = p->f0;
    if (v != 0) {
        MemStackReset_14d830(v);
        p->f0 = 0;
    }
}
