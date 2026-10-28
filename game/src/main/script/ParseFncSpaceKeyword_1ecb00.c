/* rgp:protos */
#define RGP_SELF_ParseFncSpaceKeyword_1ecb00 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern u8 D_0044B3B0[];
/*rgp*/

void *ParseFncSpaceKeyword_1ecb00(void *p)
{
    if (p != 0) {
        return LookupNameValueNoCase_1cab50(p, D_0044B3B0, 0);
    }
    return 0;
}
