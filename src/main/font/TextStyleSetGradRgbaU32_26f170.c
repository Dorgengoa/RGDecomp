#include "types.h"

typedef struct X X;

extern void PackRgba_26ffb0(u64 *out);
extern void TextStyleSetGradRgbaQuad_26f1b0(X *p, u64 v);

void TextStyleSetGradRgbaU32_26f170(X *p)
{
    u64 t;
    PackRgba_26ffb0(&t);
    TextStyleSetGradRgbaQuad_26f1b0(p, t);
}
