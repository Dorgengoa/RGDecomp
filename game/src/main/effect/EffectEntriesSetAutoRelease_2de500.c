/* rgp:protos */
#define RGP_SELF_EffectEntriesSetAutoRelease_2de500 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

void EffectEntriesSetAutoRelease_2de500(s32 arg0, void *arg1, s32 arg2) {
    s16 v;
    s32 i;
    void *rec;
    void *result;

    i = 0;
    v = (s16)(arg2 & 0xFF);
    do {
        rec = (u8 *)arg0 + i * 0xE0;
        if (*(s16 *)((u8 *)rec + 0xE) == *(s32 *)((u8 *)arg1 + 8)) {
            result = EffectEntryFindNodeById_2da140(rec, arg1);
            if (result != NULL) {
                *(s16 *)((u8 *)result + 6) = v;
            }
        }
        i += 1;
    } while (i < 0x30);
}
