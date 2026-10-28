#include "types.h"
/* rule agg-view (2026-10-25): the definition takes the colour as one 8-byte integer (one EE
   GPR); FontDrawGaiji_26dd50's callers view it as an over-aligned struct by value, which
   i686-windows-msvc passes BY ADDRESS (the callee read the pointer as the colour) */
void GaijiDraw_402000(s32 *out, s64 rgba)
{
    out[0] = (s32)rgba;
    out[1] = (s32)(rgba >> 32);
}
