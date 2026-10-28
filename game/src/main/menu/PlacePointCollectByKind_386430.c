/* rgp:protos */
#define RGP_SELF_PlacePointCollectByKind_386430 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct Obj1 { u8 pad000[0x10]; s32 m10; };
struct Obj0 { struct Obj1 *m00; s32 m04; };

/*rgp*/

s32 PlacePointCollectByKind_386430(struct Obj0 *p0, s32 p1, s32 p2, s32 p3)
{
    s32 cnt;
    struct Obj1 *cur;
    s32 i;

    if (p2 != 0) {
        if (p3 > 0) {
            goto ok;
        }
    }
    return 0;
ok:
    cur = p0->m00;
    cnt = 0;
    i = 0;
    while (i < p0->m04) {
        if (cur->m10 == p1) {
            Copy20Bytes_3869c0((p2 + (cnt << 5)), cur);
            cnt = cnt + 1;
            if (cnt >= p3) {
                break;
            }
        }
        i = i + 1;
        cur = (struct Obj1 *)((u8 *)cur + 0x20);
    }
    return cnt;
}
