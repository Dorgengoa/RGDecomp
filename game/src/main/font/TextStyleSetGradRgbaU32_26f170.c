/* rgp:protos */
#define RGP_SELF_TextStyleSetGradRgbaU32_26f170 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct X X;

/*rgp*/
/*rgp*/

void TextStyleSetGradRgbaU32_26f170(X *p, unsigned int rgp_a1)
{
    u64 t;
    PackRgba_26ffb0(&t, (unsigned int)rgp_a1);
    TextStyleSetGradRgbaQuad_26f1b0(p, t);
}
