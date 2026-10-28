/* rgp:protos */
#define RGP_SELF_ParseMemOrderKeyword_1ecb40 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern u8 D_0044B390[];
/*rgp*/

void *ParseMemOrderKeyword_1ecb40(void *p)
{
    if (p != 0) {
        return LookupNameValueNoCase_1cab50(p, D_0044B390, 0);
    }
    return 0;
}
