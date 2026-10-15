#include "types.h"
#pragma opt_propagation off

s32 XformPairInit_19a240(u8 *);
s32 EffObjInitEmitterRec_1a9660(s32, s32);
s32 EffObjInitRecord_1a9bf0(u8 *, u8 *);

void EffInstResetRecords_19aba0(u8 *arg0, u8 *arg1) {
    u8 **pp;
    u8 *e;
    s32 i;

    XformPairInit_19a240(arg1);
    EffObjInitRecord_1a9bf0(arg0, arg1);
    e = *(u8 **)(arg1 + 0xC4);
    pp = *(u8 ***)(arg0 + 0xA0);
    if (e == NULL) {
        return;
    }
    for (i = 0; i < *(s32 *)(arg0 + 0x9C); i++, pp++, e += 0x120) {
        u8 *o;
        o = *(u8 **)(*pp + 0xC);
        if (o != NULL) {
            XformPairInit_19a240(e);
            EffObjInitRecord_1a9bf0(o, e);
            {
            u8 *node;
            s32 j;
            s32 a;
            node = *(u8 **)(o + 0x44);
            j = 0;
            while (node && j < *(s32 *)(e + 0xC0)) {
                a = *(s32 *)(node + 4);
                EffObjInitEmitterRec_1a9660(a, *(s32 *)(e + 0xC4) + j * 0x110);
                node = *(u8 **)node;
                j++;
            }
            }
        }
    }
}
