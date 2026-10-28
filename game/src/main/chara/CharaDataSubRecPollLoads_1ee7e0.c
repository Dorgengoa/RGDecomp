/* rgp:protos */
#define RGP_SELF_CharaDataSubRecPollLoads_1ee7e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct N1EE7E0 { u8 pad000[0x4]; struct N1EE7E0 *f04; };
struct T1EE7E0 { u8 pad000[0x64]; struct N1EE7E0 *f64; };

/*rgp*/

void CharaDataSubRecPollLoads_1ee7e0(struct T1EE7E0 *p)
{
    struct N1EE7E0 *n;

    n = p->f64;
    if (n == 0) {
        return;
    }
    while (n != 0) {
        CharaDataNodeLoadPoll_1ef6f0(n);
        n = n->f04;
    }
}
