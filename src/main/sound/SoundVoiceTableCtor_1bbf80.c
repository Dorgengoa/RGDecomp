#include "types.h"

extern void SoundSeqChanInit_1b5ef0(void *arg0);          /* extern, return type unused */
extern void SoundSeqPlayerInit_1b5a90(void *arg0);          /* extern, return type unused */

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
