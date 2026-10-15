/* MATCH (s41a5): the loop compare is SIGNED (`slt`) but the counter web is
   s32 and the bound u32, compared as `var_18 < (s32)temp_17`.  u32 counter
   gave `sltu` (the old 1-bad residue); s32 both re-scheduled (4 bad). */
#include "types.h"
extern "C" {

typedef struct S2F2 {
    u8 pad0[0x1C];
    void *unk1C;
} S2F2;

extern void *GetGameData_1fede0(void);
extern void CharaUnloadById_2f3090(s32 arg0, s32 arg1);
extern void *PoolGetUsedElem_36acb0(s32 arg0, s32 arg1);
extern s32 ObjMgrGetPoolCapacity_3bb0a0(void *arg0);

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
    virtual s32 f();
};
void ObjMgrUnloadDead_2f2fa0(s32 arg0)
{
    s32 var_19;
    s32 temp_4;
    s32 var_16;
    s32 var_18;
    u32 temp_17;
    S2F2 *temp_2;
    void *temp_3;
    s32 sp[0x10];
    void *var_21;

    var_19 = 0;
    temp_2 = (S2F2 *)GetGameData_1fede0();
    temp_17 = ObjMgrGetPoolCapacity_3bb0a0(temp_2->unk1C);
    var_18 = 0;
    while (var_18 < (s32)temp_17) {
        temp_4 = *(s32 *)((u8 *)temp_2->unk1C + 0x10);
        if (temp_4 != 0) {
            var_21 = PoolGetUsedElem_36acb0(temp_4, var_18);
        } else {
            var_21 = NULL;
        }
        if ((var_21 != NULL) && (((VC_0 *)(var_21))->f() != 0)) {
            sp[var_19] = *(s32 *)((u8 *)var_21 + 0xC);
            var_19 += 1;
        }
        var_18 += 1;
    }
    var_16 = 0;
    while (var_16 < var_19) {
        CharaUnloadById_2f3090(sp[var_16], arg0);
        var_16 += 1;
    }
}

}
