/* rg-override: replaces game/src/main/effect/EffObjStepChannels_1a9b50.cpp sha256 2d72a692d5863363f849d034f21f80a540c5fc25d0f50a2920bdca15d62a9b1a
 * why: i686 x87 stack: slot 0x18 is the EffCurveApply* family (19 of 20 return f32: D_00470A40..E00); a void view left ST0 on the x87 stack per call, 8 calls overflowed it and every later x87 load read the indefinite NaN (Insectron battle, docs/X64-PLAN.md 0.9) */
#include "types.h"

/* Two virtual calls through the same class shape: slot 0x18 (index 4,
 * one s32 arg) and slot 0x1C (index 5, s32 + f32 args).
 * [[jalr-is-cpp-virtual]] */

class VE {
public:
    VC_VPTR_MEMBER;  
    
    /* rg-override: the f32 view pops ST0 on i686 (EffCurveApplyNop_1a1830, the one void target, leaves
     * nothing: the pop of the empty register is a masked no-op) */
    void v4(s32 a0) { (void)VCM(f32, (void *, s32), 0x18, a0); }        /* slot 0x18 */
    void v5(f32 a0, s32 a1) { VCM(void, (void *, s32, f32), 0x1C, a1, a0); }         /* slot 0x1C */
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
