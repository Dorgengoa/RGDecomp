/* rgp:protos */
#define RGP_SELF_TextStyleSetRgbaU32_26f210 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct X X;

/*rgp*/
/*rgp*/

void TextStyleSetRgbaU32_26f210(X *p, unsigned int rgp_a1)
{
    u64 t;
    PackRgba_26ffb0(&t, (unsigned int)rgp_a1);
    TextStyleSetRgbaQuad_26f250(p, t);
}
