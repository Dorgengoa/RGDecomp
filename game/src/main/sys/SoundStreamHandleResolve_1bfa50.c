/* rgp:protos */
#define RGP_SELF_SoundStreamHandleResolve_1bfa50 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Elem001bfa50 {
    u8 pad0[0x86];
    u16 unk86;
} Elem001bfa50;

void SoundStreamHandleResolve_1bfa50(void **out, s32 table, s32 *arg2)
{
    s32 val;
    u16 *halves;
    s32 lo;
    u16 hi;
    Elem001bfa50 *elem;
    void *result;
    s32 off;

    val = *arg2;
    halves = (u16 *) &val;
    hi = halves[1];
    lo = halves[0];
    if (hi == 0 || lo >= *(u32 *) table) {
        result = NULL;
    } else {
        elem = (Elem001bfa50 *) ((u8 *) (lo * 0x84) + table);
        if (elem->unk86 != hi) {
            result = NULL;
        } else {
            result = (u8 *) elem + 4;
        }
    }
    *out = result;
}
