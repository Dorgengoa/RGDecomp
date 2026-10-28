/* rgp:protos */
#define RGP_SELF_FileReadByPath_181f80 1
#include "port/game_protos.h"
#line 1
/* PARK: 2 bad words @ 0x181FD8 (zero-fill loop back-edge branch register)
   and 0x181FE4 (arg reg for FileMakeDevicePath_181980 call). length/frame/regs all
   otherwise exact after adding the dropped leading arg0 and fixing sp60 to
   a real s8[0x100] array. Decl-order sweep of var_2/var_3 tried, this
   ordering is the best found (8 -> 2). */
#include "types.h"

/*rgp*/                    /* extern */
/*rgp*/                          /* extern */
/*rgp*/                      /* extern */
/*rgp*/                        /* extern */
/*rgp*/                          /* extern */
/*rgp*/                          /* extern */

s32 FileReadByPath_181f80(s32 arg0, s32 arg1, s32 *arg2, s32 arg3, s32 arg4) {
    s32 sp16C;
    s8 sp60[0x100] __attribute__((aligned(16)));
    s8 *var_3;
    s32 temp_17;
    s32 temp_2;
    s32 var_16;
    u32 var_2;

    var_16 = arg4;
    if (arg3 < 0) {
        return 0;
    }
    var_3 = sp60;
    var_2 = 0x100;
    if (var_3 != NULL) {
        do {
            *var_3 = 0;
            var_2 -= 1;
            var_3 += 1;
        } while (var_2 != 0);
    }
    FileMakeDevicePath_181980(arg0, sp60);
    temp_2 = FileSlotOpen_180710(sp60, 0);
    if (temp_2 < 0) {
        return 0;
    }
    if (var_16 < 0) {
        var_16 = FileSlotGetSize_180d50(temp_2, &sp16C, 0) - arg3;
    }
    if (arg3 > 0) {
        FileSlotSeek_180ed0(temp_2, arg3, 0);
    }
    temp_17 = FileReadChunked_180400(temp_2, arg1, var_16);
    FileSlotCloseThunk_180540(temp_2);
    if (temp_17 < var_16) {
        var_16 = temp_17;
    }
    if (arg2 != NULL) {
        *arg2 = var_16;
    }
    return temp_2 >= 0;
}
