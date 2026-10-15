#include "types.h"

extern "C" s32 MenuObjInsectIsAdult_386c90(void *arg0);
extern "C" s32 MenuObjInsectGetSex_386cf0(void *arg0);
extern "C" void *D_004832AC;

inline s32 chk(void *p, s32 o) { return *(s32 *)((u8 *)p + o) != 0; }

extern "C" s32 MenuObjHasBreedCandidate_390c10(void *arg0)
{
    s32 temp_19;
    void *var_17;
    s32 var_16;

    if (arg0 == 0) {
        return 0;
    }
    var_17 = D_004832AC;
    var_16 = 0;
    while (var_16 < 5) {
        if ((*(s8 *)((u8 *)var_17 + 0x985) != 0) && (var_17 != arg0) &&
            (MenuObjInsectIsAdult_386c90(var_17) != 0) && !chk(var_17, 0x9C4) &&
            !chk(var_17, 0x9C8)) {
            temp_19 = MenuObjInsectGetSex_386cf0(arg0);
            if (temp_19 != MenuObjInsectGetSex_386cf0(var_17)) {
                return 1;
            }
        }
        var_16 += 1;
        var_17 = (u8 *)var_17 + 0x9D0;
    }
    return 0;
}
