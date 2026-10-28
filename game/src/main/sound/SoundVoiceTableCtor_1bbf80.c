/* rgp:protos */
#define RGP_SELF_SoundVoiceTableCtor_1bbf80 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/          /* extern, return type unused */
/*rgp*/          /* extern, return type unused */

void *SoundVoiceTableCtor_1bbf80(void *arg0) {
    u8 *base;
    u8 *var_16;
    u8 *var_4;

    base = (u8 *) arg0;
    var_16 = base + 0x30;
    do {
        var_4 = var_16 + 8;
        do {
            *var_4 = 0;
            var_4 += 4;
        } while (var_4 < var_16 + 0xC);
        SoundSeqChanInit_1b5ef0(var_16);
        var_16 += 0xC;
    } while (var_16 < base + 0x90);
    SoundSeqPlayerInit_1b5a90(base);
    return arg0;
}
