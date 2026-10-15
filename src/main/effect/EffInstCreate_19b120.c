/* main s27m: CLOSED -- the tail is `if (!p) return NULL; if (f(...) != 0) return p; return NULL;`;
   the `== 0 -> p = NULL` and ternary spellings are 1 word long or 8 bad. */
#include "types.h"

extern void *MemStackNew_14e230(s32 arg0);
extern void XformPairInit_19a240(void *arg0);
extern s32 EffInstBuildNodes_19af80(s32 arg0, s32 arg1, void *arg2);

void *EffInstCreate_19b120(s32 arg0, s32 arg1)
{
    void *var_16;

    var_16 = MemStackNew_14e230(0x140);
    if (var_16 != NULL) {
        *(s32 *)((u8 *)var_16 + 4) = 0;
        *(s32 *)((u8 *)var_16 + 0) = 0;
        *(s32 *)((u8 *)var_16 + 0xC) = 0;
        *(s32 *)((u8 *)var_16 + 0xB0) = -1;
        XformPairInit_19a240(var_16);
        *(s32 *)((u8 *)var_16 + 8) = 0;
        *(s32 *)((u8 *)var_16 + 0xB4) = 0;
        *(s32 *)((u8 *)var_16 + 0xE0) = 0;
        *(s32 *)((u8 *)var_16 + 0xC0) = 0;
        *(s32 *)((u8 *)var_16 + 0xC4) = 0;
        *(s32 *)((u8 *)var_16 + 0xDC) = 0;
        *(s32 *)((u8 *)var_16 + 0xE4) = 0;
        *(s32 *)((u8 *)var_16 + 0xD8) = 0;
        *(s32 *)((u8 *)var_16 + 0xD4) = 0;
        *(s32 *)((u8 *)var_16 + 0xC8) = 0;
        *(s32 *)((u8 *)var_16 + 0xCC) = 0;
        *(s32 *)((u8 *)var_16 + 0xEC) = 0;
        *(u8 *)((u8 *)var_16 + 0xE8) = 0;
        *(s32 *)((u8 *)var_16 + 0xD0) = 0;
        *(u8 *)((u8 *)var_16 + 0xF0) = 0;
        *(u8 *)((u8 *)var_16 + 0xF1) = 0;
    }
    if (var_16 == NULL) {
        return NULL;
    }
    if (EffInstBuildNodes_19af80(arg0, arg1, var_16) != 0) {
        return var_16;
    }
    return NULL;
}
