#include "types.h"

extern void BitArraySetReturnOld_384360(void *, s32, s32);
extern void *D_004832AC;
extern u8 D_00483360;

void InsectCageMenuSetStateFlagMaybe_390aa0(s32 arg0, s32 arg1) {
    s32 i;

    if (arg0 == 2) {
        i = 0;
        do {
            BitArraySetReturnOld_384360((u8 *)D_004832AC + (i * 0x9D0) + 0x986, 8, arg1);
            i += 1;
        } while (i < 5);
        return;
    }
    BitArraySetReturnOld_384360(&D_00483360, arg0, arg1);
}
