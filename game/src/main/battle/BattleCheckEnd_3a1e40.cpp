#include "types.h"
#pragma opt_propagation off

extern "C" {
void Abort_12de80(void);
void Fprintf_12f9a0(s32, void *);
void CharaSysBattleEndRequest_3a1f80(u8 *, s32, s32);
s32 ObjMgrAllDown_3babd0(s32);
s32 PartyAllIncapacitated_3c07c0(s32, s32);
extern u8 *D_00449858[];
extern u8 D_00465E20[];
extern u8 *D_004837C0;
}

class BitRef {
public:
    s64 *m_p;
    s32 m_n;
    BitRef(s64 *p) {
        m_p = p;
        m_n = 0;
    }
    bool Test(s32 i) {
        if (i) {
            Fprintf_12f9a0(*(s32 *)(D_00449858[0] + 0xC), D_00465E20);
            Abort_12de80();
        }
        return (*m_p & ((s64)1 << i)) != 0;
    }
};

extern "C" s32 BattleCheckEnd_3a1e40(u8 *arg0, s32 arg1)
{
    s64 *p;
    s16 h;
    s32 r;
    s32 i;

    if (D_004837C0 == NULL) {
        return 0;
    }
    if (!(*(u8 *)(arg0 + 0x24C) & 1)) {
        return 0;
    }
    p = *(s64 **)(arg0 + 0x238);
    if (p != NULL) {
        BitRef b(p);
        BitRef &rb = b;
        i = 0;
        if (rb.Test(i)) {
            return 0;
        }
    }
    p = *(s64 **)(arg0 + 0x238);
    if (p != NULL) {
        h = *(s16 *)((u8 *)p + 0x168);
        if (h != 0) {
            return h;
        }
    }
    r = 0;
    if (PartyAllIncapacitated_3c07c0(*(s32 *)(D_004837C0 + 0x18), 1) != 0) {
        r = 2;
    } else if (ObjMgrAllDown_3babd0(*(s32 *)(D_004837C0 + 0x1C)) != 0) {
        r = 1;
    }
    if (r != 0 && arg1 != 0) {
        CharaSysBattleEndRequest_3a1f80(arg0, r, 0);
    }
    return r;
}
