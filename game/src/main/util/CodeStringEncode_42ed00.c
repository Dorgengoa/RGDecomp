/* rgp:protos */
#define RGP_SELF_CodeStringEncode_42ed00 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

s32 CodeStringEncode_42ed00(s32 p0, s32 p1, s32 p2, s32 p3, s32 p4, s32 p5)
{
    s32 q;
    s32 r5;

    if ((p1 % 8) != 0) {
        return 0;
    }
    q = p1 / 8;
    if (p5 < q * 11 + 1) {
        return 0;
    }
    CodeCipherEncode_42eee0(p0, p1, p2, p3);
    r5 = Base58EncodeChecked_42f120(p0, p1, p4);
    return (r5 > 0);
}
