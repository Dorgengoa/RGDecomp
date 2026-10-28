/* rgp:protos */
#define RGP_SELF_CharaTableEntryGetWaitFrameParam_2260c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* s88m de-asm: bounds-checked read of a 2-entry s32 table at +0x3C.
 * The `&&` inside the ternary gives retail's bltzl/bnezl layout. */
typedef struct {
    u8 pad[0x3C];
    s32 a[2];
} O;

s32 CharaTableEntryGetWaitFrameParam_2260c0(O *o, s32 n)
{
    return (n >= 0 && n < 2) ? o->a[n] : 0;
}
