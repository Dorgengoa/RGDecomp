/* rgp:protos */
#define RGP_SELF_ModelGetRootFrame_1511a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Two guards and a forward. Three things had to be right, and each one is a
   recorded recipe meeting a new site:

   1. The first guard is an early `return 0`, spelled `<= 0`. Writing it as a
      positive `if (... > 0) { ... }` wrapper merges the zeroing into a
      `blezl` and loses the load that belongs in the delay slot.
   2. The value is fetched as `*self->unk110`, a DEPENDENT pair of loads.
      That is what puts `lw v1, 0x110(a0)` in the first guard's `bgtzl` slot
      and `lw a1, 0x0(v1)` in the second guard's: the scheduler slots the
      independent `lw v0, 0x0(a0)` between them to cover the load-use
      latency. Holding the pointer in a local and dereferencing it at the
      call instead sinks both loads past the guard -- 7 bad words.
   3. The tail is an explicit `else`, not a `goto` to a shared label. With
      the `goto`, mwcc fills the trailing `b`'s delay slot by duplicating the
      epilogue's `ld ra` and retargeting the branch; retail leaves that slot
      EMPTY. This is the CameraModeUpdate_309770 finding -- an explicit `else`
      suppresses the duplication -- reproduced at a second site. */

typedef struct Obj001511a0 {
    s32 unk0;
    u8 pad4[0x104 - 0x4];
    s32 unk104;
    u8 pad108[0x10C - 0x108];
    s32 unk10C;
    s32 *unk110;
} Obj001511a0;

/*rgp*/

s32 ModelGetRootFrame_1511a0(Obj001511a0 *self)
{
    s32 v;

    if (self->unk10C <= 0) {
        return 0;
    }
    v = *self->unk110;
    if (self->unk0 != 0) {
        return ArrayGetChecked_152fd0(self->unk104, v);
    } else {
        return 0;
    }
}
