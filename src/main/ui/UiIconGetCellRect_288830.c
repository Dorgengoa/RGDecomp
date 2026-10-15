/* PARK s17c: 3 round trips. Two-digit grid-cell (sprite atlas row/col from
   arg0%100, base coords from UiIconGetSheetPos_288720(arg0/1000,(arg0%1000)/100)) with a
   float accumulator chain (retail uses adda.s+madd.s for the row calc, plain
   mul.s+add.s for the col calc -- PS2 float accumulator lever). Best 122
   words vs retail 120 (+8 bytes) WITH `#pragma divbyzerocheck on` (needed:
   without it, retail's two dead `break 0,7` blocks after the /1000 and
   (%1000)/100 divisions disappear and length drops to 115, -20 bytes, so
   "on" is confirmed correct, just not sufficient). Retail has only 2 break
   blocks total (guarding the /1000 and the followup /100 divs) -- NOT one
   per div (the %100 and %1000 divs get no check), so the checks are tied to
   specific div sites, not blanket-on; the +2 words residue is elsewhere,
   not yet isolated. */
#include "types.h"

#pragma divbyzerocheck on

extern void UiIconGetSheetPos_288720(s32, s32, s16 *, s16 *);

s32 UiIconGetCellRect_288830(s32 arg0, s16 *arg1, s16 *arg2, s16 *arg3, s16 *arg4)
{
    s16 sp7E;
    s16 sp7C;
    f32 temp_f5;
    s32 var_5;
    s16 var_4;
    s32 var_16;
    s32 modB;
    s32 modA;

    if (arg0 >= 0) {
        var_16 = (arg0 % 100) - 1;
        UiIconGetSheetPos_288720(arg0 / 1000, (arg0 % 1000) / 100, &sp7E, &sp7C);
        if ((var_16 < 0) || (var_16 > 0x40)) {
            var_16 = 0;
        }
        var_4 = 0x20;
        var_5 = 0x20;
        if (arg0 == 0x8FD) {
            var_4 = 0x28;
            var_5 = 0x28;
        }
        modB = var_16 % 8;
        temp_f5 = (f32)modB * (f32)var_5;
        *arg1 = (s16)(s32)((f32)sp7E + temp_f5);

        modA = (var_16 / 8) % 8;
        *arg2 = (s16)(s32)((f32)sp7C + (f32)modA * (f32)var_4);

        if (!(((f32)sp7E + temp_f5) < 992.0f)) {
            var_5 -= 1;
        }
        *arg3 = var_5;
        *arg4 = var_4;
    } else {
        *arg2 = 0;
        *arg1 = 0;
        *arg4 = 0;
        *arg3 = 0;
    }
    return 1;
}
