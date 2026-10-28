/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsGetLoadSysMsgBuf_4f9700 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* insmenu 0x004F9700 (12 bytes) -- hand back the address of an overlay-data
 * buffer.
 *
 * ★ insmenu_D_004FA280 is an INCOMPLETE ARRAY extern, which is the small-data escape
 * for an overlay global the image also WRITES (insmenu_InsectVsSaveScreenOpen_4f8ef0 memsets
 * it).  mwcc small-datas any <= 4-byte extern and an incomplete type has no
 * size for it to test, so the address comes out as %hi/%lo rather than a gp
 * displacement -- and unlike `const` it does not lie about mutability. */

extern u8 insmenu_D_004FA280[];

u8 *insmenu_InsectVsGetLoadSysMsgBuf_4f9700(void)
{
    return insmenu_D_004FA280;
}
