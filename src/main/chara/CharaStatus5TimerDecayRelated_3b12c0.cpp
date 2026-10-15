/* MATCH (s41 agent36): store through `fp = &arr[i]`, `var_f1 = *fp; var_f1 -= ...`. */
#include "types.h"
#undef NULL
#define NULL 0
extern "C" {

typedef struct VTvar2 {
    u8 pad70[0x70];
    u8 *(*unk70)(void *, s32);
} VTvar2;

typedef struct Vtarg0 {
    u8 pad19C[0x19C];
    s32 (*unk19C)(void *, s32);
} Vtarg0;

extern u8 *D_0048381C;
extern u8 D_0045B078[0x400];

class VC_0 {
public:
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual void d5();
    virtual void d6();
    virtual void d7();
    virtual void d8();
    virtual void d9();
    virtual void d10();
    virtual void d11();
    virtual void d12();
    virtual void d13();
    virtual void d14();
    virtual void d15();
    virtual void d16();
    virtual void d17();
    virtual void d18();
    virtual void d19();
    virtual void d20();
    virtual void d21();
    virtual void d22();
    virtual void d23();
    virtual void d24();
    virtual void d25();
    virtual void d26();
    virtual void d27();
    virtual void d28();
    virtual void d29();
    virtual void d30();
    virtual void d31();
    virtual void d32();
    virtual void d33();
    virtual void d34();
    virtual void d35();
    virtual void d36();
    virtual void d37();
    virtual void d38();
    virtual void d39();
    virtual void d40();
    virtual void d41();
    virtual void d42();
    virtual void d43();
    virtual void d44();
    virtual void d45();
    virtual void d46();
    virtual void d47();
    virtual void d48();
    virtual void d49();
    virtual void d50();
    virtual void d51();
    virtual void d52();
    virtual void d53();
    virtual void d54();
    virtual void d55();
    virtual void d56();
    virtual void d57();
    virtual void d58();
    virtual void d59();
    virtual void d60();
    virtual void d61();
    virtual void d62();
    virtual void d63();
    virtual void d64();
    virtual void d65();
    virtual void d66();
    virtual void d67();
    virtual void d68();
    virtual void d69();
    virtual void d70();
    virtual void d71();
    virtual void d72();
    virtual void d73();
    virtual void d74();
    virtual void d75();
    virtual void d76();
    virtual void d77();
    virtual void d78();
    virtual void d79();
    virtual void d80();
    virtual void d81();
    virtual void d82();
    virtual void d83();
    virtual void d84();
    virtual void d85();
    virtual void d86();
    virtual void d87();
    virtual void d88();
    virtual void d89();
    virtual void d90();
    virtual void d91();
    virtual void d92();
    virtual void d93();
    virtual void d94();
    virtual void d95();
    virtual void d96();
    virtual void d97();
    virtual void d98();
    virtual void d99();
    virtual void d100();
    virtual s32 f(s32 x0);
};
class VC_1 {
public:
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual void d5();
    virtual void d6();
    virtual void d7();
    virtual void d8();
    virtual void d9();
    virtual void d10();
    virtual void d11();
    virtual void d12();
    virtual void d13();
    virtual void d14();
    virtual void d15();
    virtual void d16();
    virtual void d17();
    virtual void d18();
    virtual void d19();
    virtual void d20();
    virtual void d21();
    virtual void d22();
    virtual void d23();
    virtual void d24();
    virtual void d25();
    virtual u8 * f(s32 x0);
};
s32 CharaStatus5TimerDecayRelated_3b12c0(Vtarg0 **arg0) {
    f32 var_f1;
    s16 temp_4_2;
    VTvar2 **temp_4;
    u8 *var_2;
    u8 *base;
    u8 *p2;
    f32 *fp;
    f32 x;
    f32 d;
    f32 two;

    if (((VC_0 *)(arg0))->f(5) != 0) {
        p2 = *(u8 **)(D_0048381C + 0x58);
        temp_4 = *(VTvar2 ***)(p2 + 8);
        if (temp_4 != NULL) {
            var_2 = ((VC_1 *)(temp_4))->f(5);
        } else {
            var_2 = NULL;
        }
        if (var_2 != NULL) {
            temp_4_2 = *(s16 *)(var_2 + 0x3C);
            if (((s16 *)((u8 *)(u8 *)arg0 + 0x150))[temp_4_2] == 5) {
                fp = &((f32 *)((u8 *)arg0 + 0xD0))[temp_4_2];
                var_f1 = *fp;
                var_f1 -= 2.0f * (*(f32 *)D_0045B078);
                if (var_f1 < 1.0f) {
                    var_f1 = 1.0f;
                }
                *fp = var_f1;
            }
        }
    }
    return 1;
}

}
