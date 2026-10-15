#include "types.h"

/* insmenu 0x004F9700 (12 bytes) -- hand back the address of an overlay-data
 * buffer.
 *
 * ★ D_004FA280 is an INCOMPLETE ARRAY extern, which is the small-data escape
 * for an overlay global the image also WRITES (insmenu_InsectVsSaveScreenOpen_4f8ef0 memsets
 * it).  mwcc small-datas any <= 4-byte extern and an incomplete type has no
 * size for it to test, so the address comes out as %hi/%lo rather than a gp
 * displacement -- and unlike `const` it does not lie about mutability. */

extern u8 D_004FA280[];

u8 *insmenu_InsectVsGetLoadSysMsgBuf_4f9700(void)
{
    return D_004FA280;
}
