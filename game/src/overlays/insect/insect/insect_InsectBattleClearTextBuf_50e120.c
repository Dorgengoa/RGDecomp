/* rgp:protos */
#define RGP_SELF_insect_InsectBattleClearTextBuf_50e120 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x0050E120 -- 124 bytes, 31 instructions.  The `beq $5, 3` jumps to
 * the LOOP, so the fall-through is the single-slot arm and the source tests
 * `!= 3` first.  Stride 0x40 based at the unaligned +0x5F02. */

typedef struct Obj {
    u8 pad0000[0x5F02];
    u8 f5F02[3][0x40];              /* +0x5F02 */
} Obj;

extern void memset(void *d, s32 c, s32 n);

void insect_InsectBattleClearTextBuf_50e120(Obj *o, s32 k)
{
    s32 i;

    if (k != 3) {
        memset(o->f5F02[k], 0, 0x40);
    } else {
        for (i = 0; i < 3; i++) {
            memset(o->f5F02[i], 0, 0x40);
        }
    }
}
