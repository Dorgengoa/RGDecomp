/* rgp:protos */
#define RGP_SELF_OcclusionPlaneAdd_189280 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#include "vec.h"

typedef struct Entry00189280 {
    s32 flag;
    u8 pad4[0xC];
    u128 vecs[4];
    u8 pad50[0x70];
} Entry00189280;

typedef struct S00189280 {
    u8 pad0[0xA20];
    s32 count;
    u8 padGap[0xC];
    Entry00189280 entries[16];
} S00189280;

void OcclusionPlaneAdd_189280(void *arg0v, void *arg1) {
    S00189280 *arg0 = (S00189280 *)arg0v;
    u128 *src = (u128 *)arg1;
    s32 i;

    if (arg0->count < 0x10) {
        arg0->entries[arg0->count].flag = 1;
        for (i = 0; i < 4; i++) {
            arg0->entries[arg0->count].vecs[i] = src[i];
        }
        arg0->count = arg0->count + 1;
    }
}
