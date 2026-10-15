/* MATCH (s41m). Stale pre-match note follows -- PARKED (round 1): length 0x78 vs retail 0x74 (4 bytes over). The flat s32
   scan loop or the aggregate-copy loop shape likely needs adjusting. */
#include "types.h"

typedef struct Entry {
    s32 a;
    s32 b;
} Entry;

extern Entry D_004546C0[4];

s32 ItemMaxClassSize_3d58f0(void)
{
    s32 var_4_2;
    Entry local[4];
    s32 temp_3;
    Entry *var_6;
    Entry *var_5;
    s32 var_2;
    s32 var_4;

    var_6 = D_004546C0;
    var_5 = local;
    var_4 = 4;
    do {
        var_4 -= 1;
        var_5->a = var_6->a;
        var_5->b = var_6->b;
        var_6 += 1;
        var_5 += 1;
    } while (var_4 > 0);

    var_2 = 0;
    var_4_2 = 0;
    while (1) {
        temp_3 = ((s32 *)local)[var_4_2];
        if (temp_3 <= 0) {
            break;
        }
        if (var_2 < temp_3) {
            var_2 = temp_3;
        }
        var_4_2 += 1;
    }
    return var_2;
}
