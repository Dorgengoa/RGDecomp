#include "types.h"

typedef struct X X;

extern void PackRgba_26ffb0(u64 *out);
extern void TextStyleSetRgbaQuad_26f250(X *p, u64 v);

void TextStyleSetRgbaU32_26f210(X *p)
{
    u64 t;
    PackRgba_26ffb0(&t);
    TextStyleSetRgbaQuad_26f250(p, t);
}
