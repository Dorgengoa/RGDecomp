#include "types.h"

class VC3a7500 {
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
    virtual void d101();
    virtual void d102();
    virtual void d103();
    virtual void d104();
    virtual void d105();
    virtual void d106();
    virtual void d107();
    virtual void d108();
    virtual void d109();
    virtual void d110();
    virtual void d111();
    virtual void d112();
    virtual void d113();
    virtual void d114();
    virtual void d115();
    virtual void d116();
    virtual void d117();
    virtual void d118();
    virtual void d119();
    virtual void d120();
    virtual void d121();
    virtual void d122();
    virtual void d123();
    virtual void d124();
    virtual void d125();
    virtual void d126();
    virtual void d127();
    virtual void d128();
    virtual void d129();
    virtual void d130();
    virtual void d131();
    virtual void d132();
    virtual void d133();
    virtual void d134();
    virtual void d135();
    virtual void d136();
    virtual void d137();
    virtual void d138();
    virtual void d139();
    virtual void d140();
    virtual void d141();
    virtual void d142();
    virtual void d143();
    virtual void d144();
    virtual void d145();
    virtual void d146();
    virtual void d147();
    virtual void d148();
    virtual void d149();
    virtual void d150();
    virtual void d151();
    virtual void d152();
    virtual void d153();
    virtual void d154();
    virtual void d155();
    virtual void d156();
    virtual void d157();
    virtual void d158();
    virtual void d159();
    virtual void d160();
    virtual void d161();
    virtual void d162();
    virtual void d163();
    virtual void d164();
    virtual void d165();
    virtual void d166();
    virtual void d167();
    virtual void d168();
    virtual void d169();
    virtual void d170();
    virtual void d171();
    virtual void d172();
    virtual void d173();
    virtual void d174();
    virtual s32 count();
    virtual void *get(s32);
};

extern "C" {
extern s32 StrNotEqual_1f5300(s8 *, void *);
extern s32 EquipSlotGetRecId_3a0760(void *);
extern s8 *EquipSlotGetRecName_3a07a0(void *);
extern s32 ExecInfoInitFromEquipSlot_3a7690(s32, s32, s32, s32);
extern VC3a7500 *ActorFindById_3eb870(s32);
extern s32 D_004837B0;

s32 ExecInfoInitFromEquipSlotByName_3a7500(s32 arg0, s32 arg1, s8 *arg2, s32 arg3)
{
    s32 temp_17;
    VC3a7500 *temp_2;
    s32 var_20;
    s32 var_3;
    s8 *temp_2_3;
    s32 var_19;
    void *temp_2_2;

    if (D_004837B0 == 0) {
        return 0;
    }
    if (arg2 == NULL) {
        return 0;
    }
    temp_2 = ActorFindById_3eb870(D_004837B0);
    if (temp_2 == NULL) {
        return 0;
    }
    var_20 = -1;
    temp_17 = temp_2->count();
    var_19 = 0;
    while (var_19 < temp_17) {
        temp_2_2 = temp_2->get(var_19);
        if ((temp_2_2 != NULL) && (*(s32 *)((u8 *)temp_2_2 + 0x4) != 0) &&
            ((temp_2_3 = EquipSlotGetRecName_3a07a0(temp_2_2)) != NULL)) {
            var_3 = *temp_2_3 != *arg2;
            if (var_3 == 0) {
                var_3 = StrNotEqual_1f5300(temp_2_3 + 1, arg2 + 1) != 0;
            }
            if (!(var_3 & 0xFF)) {
                var_20 = EquipSlotGetRecId_3a0760(temp_2_2);
                break;
            }
        }
        var_19 += 1;
    }
    return ExecInfoInitFromEquipSlot_3a7690(arg0, arg1, var_20, arg3);
}
}
