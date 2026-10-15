#include "types.h"

/* Two virtual calls through the same class shape: slot 0x18 (index 4,
 * one s32 arg) and slot 0x1C (index 5, s32 + f32 args).
 * [[jalr-is-cpp-virtual]] */

class VE {
public:
    virtual void v0(); virtual void v1(); virtual void v2();
    virtual void v3();
    virtual void v4(s32);              /* slot 0x18 */
    virtual void v5(f32, s32);         /* slot 0x1C */
};

typedef struct Node {
    struct Node *next;   /* unk0 */
    VE *obj;             /* unk4 */
} Node;

typedef struct Self {
    u8    pad00[0xC];
    Node *listA;   /* unkC */
    Node *listB;   /* unk10 */
} Self;

extern "C" void XformPairResetDelta_19a200(s32);

extern "C" void EffObjStepChannels_1a9b50(Self *arg0, s32 arg1, f32 fparg0) {
    Node *var_16;
    Node *var_16_2;

    var_16 = arg0->listA;
    while (var_16 != NULL) {
        var_16->obj->v5(fparg0, arg1);
        var_16 = var_16->next;
    }
    if (arg0->listB != NULL) {
        XformPairResetDelta_19a200(arg1);
        var_16_2 = arg0->listB;
        while (var_16_2 != NULL) {
            var_16_2->obj->v4(arg1);
            var_16_2 = var_16_2->next;
        }
    }
}
