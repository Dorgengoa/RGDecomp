#include "types.h"
#pragma opt_propagation off

typedef struct E001aae30 {
    s32 unk0;
    u8 pad4[0x1C];
} E001aae30;

typedef struct M001aae30 {
    u8 pad0[0x20C];
    s32 unk20C;
    E001aae30 *unk210;
} M001aae30;

extern E001aae30 *ConstructNewArray_100710(void *, void (*)(void), s32, s32, s32);
extern void *MemStackNew_14e1b0(s32, s32);
extern s32 VariantGetInt_15f780();
extern void ObjAttachPointCtor_1aae00(void);
extern M001aae30 *D_0049D418[];
extern s32 D_0049D398[];
extern s32 D_0049D430[];

s32 InfoCfgObjectNameNumCmd_1aae30(void) {
    M001aae30 *m;
    s32 heap;
    s32 n;
    s32 i;
    s32 k;

    m = D_0049D418[0];
    heap = D_0049D398[0];
    if (m == NULL || heap == 0) {
        return 0;
    }
    if (m->unk210 == NULL) {
        n = VariantGetInt_15f780();
        if (n > 0) {
            m->unk20C = n;
            k = n;
            m->unk210 = ConstructNewArray_100710(MemStackNew_14e1b0((k << 5) + 0x10, heap), ObjAttachPointCtor_1aae00, 0, 0x20, k);
            if (m->unk210 == NULL) {
                m->unk20C = 0;
            } else {
                for (i = 0; i < m->unk20C; i++) {
                    m->unk210[i].unk0 = -1;
                }
            }
        } else {
            m->unk20C = 0;
            m->unk210 = NULL;
        }
        D_0049D430[0] = 0;
    }
    return 1;
}
