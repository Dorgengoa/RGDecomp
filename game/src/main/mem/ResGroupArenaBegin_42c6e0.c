/* rgp:protos */
#define RGP_SELF_ResGroupArenaBegin_42c6e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

void *ResGroupArenaBegin_42c6e0(void *arg0) {
    void *v = ResGroupGetStack_42c720(arg0, *(u16 *)((u8 *)arg0 + 0x164));
    ArenaCtxInit_370610((u8 *)arg0 + 0x168, v);
    return (void *)((u32)arg0 + 0x168);
}
