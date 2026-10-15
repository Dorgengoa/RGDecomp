#include "types.h"

struct Node19B;

class VE19B {
public:
    u8 pad000[0x40];
    virtual s32 v0(s32, s32, s32);
};

struct Node19B { Node19B *next; VE19B *obj; };

extern "C" s32 EffFrameCollectDrawEntries_19b370(void *arg0, s32 arg1, void *arg2, s32 arg3) {
    Node19B *var_18;
    s32 var_17;
    s32 var_16;
    VE19B *temp_4;

    var_17 = 0;
    var_18 = *(Node19B **)((u8 *)arg0 + 0x44);
    var_16 = 0;
    while ((((var_18 != NULL) ^ 1) == 0) && (var_16 < *(s32 *)((u8 *)arg2 + 0xC0))) {
        temp_4 = var_18->obj;
        var_17 += temp_4->v0(arg1, *(s32 *)((u8 *)arg2 + 0xC4) + (var_16 * 0x110), arg3);
        var_18 = var_18->next;
        var_16 += 1;
    }
    return var_17;
}
