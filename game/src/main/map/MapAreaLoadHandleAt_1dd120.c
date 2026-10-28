/* rgp:protos */
#define RGP_SELF_MapAreaLoadHandleAt_1dd120 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* s88m de-asm: bounds-checked address of a 1-entry table of 12-byte records.
 * The `&&` inside the ternary gives retail's bltzl/blezl layout. */
typedef struct {
    u8 b[12];
} E;

void *MapAreaLoadHandleAt_1dd120(E *o, s32 n)
{
    return (n >= 0 && n < 1) ? &o[n] : 0;
}
