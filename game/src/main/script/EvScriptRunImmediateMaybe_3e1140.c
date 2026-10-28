/* rgp:protos */
#define RGP_SELF_EvScriptRunImmediateMaybe_3e1140 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Elem { u8 pad0[0x38]; } Elem;
typedef struct A {
    u8 pad0[8];
    Elem e[64];
    u8 padE08[4];
    u8 flag : 1;
    u8 rest : 7;
    u8 padE0D[3];
} A;
typedef struct B { u8 pad0[0x30]; } B;
typedef struct O {
    u8 pad0[0xC];
    s16 unkC;
    u8 padE[0x16];
    s32 unk24;
} O;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 EvScriptRunImmediateMaybe_3e1140(O *arg0)
{
    B b __attribute__((aligned(16)));
    A a __attribute__((aligned(16)));
    Elem *p;

    if (arg0 == NULL) {
        return 0;
    }
    if (arg0->unkC > 0 && arg0->unk24 != 0) {
        ActionPacketClear_3e3e90(&b);
        p = a.e;
        do {
            VariantInit_36ff00(p);
            p++;
        } while (p < &a.e[64]);
        VariantPoolReset_3e01f0(&a);
        a.flag = 1;
        ScriptExecOpStream_3dffa0(&a, arg0->unkC, arg0->unk24, &b);
        return 1;
    }
    return 0;
}
