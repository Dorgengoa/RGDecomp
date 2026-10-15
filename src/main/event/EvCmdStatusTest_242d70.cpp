#include "types.h"
#undef NULL
#define NULL 0
extern "C" {

typedef struct Obj0242d70 Obj0242d70;
typedef struct VT0242d70 {
    u8 pad0[0x19C];
    s32 (*unk19C)(Obj0242d70 *, s32);
} VT0242d70;
struct Obj0242d70 {
    VT0242d70 *vtable;
};

extern s32 GetGameData_1fede0(...);
extern void ScriptSetRefInt_249030(s32, s32);
extern s32 ScriptGetInt_2490f0(s32);
extern Obj0242d70 *ActorFindById_3eb870(s32, s32);

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
s32 EvCmdStatusTest_242d70(s64 *arg0) {
    s32 result;
    Obj0242d70 *temp_2;
    s32 temp_16_2;
    s32 temp_17;
    s32 temp_16;

    temp_17 = GetGameData_1fede0();
    temp_16 = ScriptGetInt_2490f0((s32)arg0++);
    temp_16_2 = ScriptGetInt_2490f0((s32)arg0++);
    temp_2 = ActorFindById_3eb870(temp_17, temp_16);
    if (temp_2 == NULL) {
        return 0;
    }
    ScriptSetRefInt_249030((s32)arg0, ((VC_0 *)(temp_2))->f(temp_16_2) & 0xFF);
    return 1;
}

}
