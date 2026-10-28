/* rgp:protos */
#define RGP_SELF_EffectEntriesReleaseAll_2de210 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

typedef struct {
    u8 pad0[0xE];
    s16 v[2];
} Sub;

void EffectEntriesReleaseAll_2de210(u8 *arg0)
{
    s32 h;
    s32 i;
    s32 j;
    u8 *e;
    Sub *sub;
    s16 *p;
    s32 v;

    h = ((s32)GetLoaderMgr_1f59d0());
    if (h == 0) {
        return;
    }
    for (i = 0; i < 0x30; i++) {
        e = arg0 + i * 0xE0;
        sub = (Sub *)(e + 0xC);
        for (j = 0; j < 2; j++) {
            p = &sub->v[j];
            if (*p != -1) {
                LoaderReleaseById_1cd340(h, *p);
                *p = -1;
            }
        }
        EffectEntryReleaseFull_2da420(e);
    }
}
