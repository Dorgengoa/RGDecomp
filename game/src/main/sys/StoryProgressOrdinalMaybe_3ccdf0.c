/* rgp:protos */
#define RGP_SELF_StoryProgressOrdinalMaybe_3ccdf0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

#define S16(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define PTR(p, o) (*(void **)((u8 *)(p) + (o)))

/*rgp*/
/*rgp*/

s32 StoryProgressOrdinalMaybe_3ccdf0(void *arg0, int rgp_a1, int rgp_a2, int rgp_a3)
{
    u8 sp68[8];
    u8 sp60[8];
    u8 sp58[8];
    void *t;
    s16 *a;
    s16 *b;
    s16 *c;
    s32 lim;
    s32 lim2;
    s32 cnt;

    t = PTR(arg0, 4);
    if (t == NULL) {
        return -1;
    }
    a = PTR(t, 8);
    lim = S16(arg0, 8);
    cnt = -1;
    if (a != NULL) {
        a += 0x44;
    }
    IterInit_370170(sp68, a, (int)rgp_a2, (int)rgp_a3);
    while (a = ((s16 *)IterNext_370040(sp68)), a != NULL) {
        if (*a > lim) {
            goto out;
        }
        if (a != NULL) {
            a += 2;
        }
        IterInit_370170(sp60, a, 0, 0);
        while (b = ((s16 *)IterNext_370040(sp60)), b != NULL) {
            lim2 = S16((u8 *)arg0 + S16(b, 8) * 2, 0xA);
            if (b != NULL) {
                b += 2;
            }
            IterInit_370170(sp58, b, 0, 0);
            while ((c = ((s16 *)IterNext_370040(sp58))) != NULL) {
                if (*c > lim2) {
                    break;
                }
                cnt++;
            }
        }
    }

out:
    return cnt;
}
