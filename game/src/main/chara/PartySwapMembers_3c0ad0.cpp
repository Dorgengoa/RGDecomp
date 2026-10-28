#pragma opt_propagation off
#pragma inline_depth(8)
#include "types.h"

#define V1(n) virtual void v##n();
#define V4(n) V1(n##0) V1(n##1) V1(n##2) V1(n##3)
#define V16(n) V4(n##0) V4(n##1) V4(n##2) V4(n##3)

class Chr {
public:
    VC_VPTR_MEMBER;                                                                                                                               
                                                                                                                                   
                       
    void Refresh(s32 a0) { VCM(void, (void *, s32), 0x458, a0); }
};

typedef struct {
    u8 b0 : 1;
    u8 b1 : 1;
    u8 b2 : 1;
} Flags;

typedef struct {
    u8 pad[0x18C];
    s16 count;
    s16 pad2;
    s16 act[3];
    s16 res[7];
} Party;

extern "C" {
extern Chr *CharaMgrPoolFindById_3a8c60(s32, s32);
extern void PartyCompactSlots_3c2c50(Party *);
extern s32 PartyFindSlotOfId_3c3070(Party *, s32);
extern u8 *D_00483890;
}

static inline s32 findAct(Party *p, s32 id) {
    s32 i;
    if (id < 0) {
        return -1;
    }
    for (i = 0; i < p->count; i++) {
        if (p->act[i] == id) {
            return i;
        }
    }
    return -1;
}

static inline s32 findRes(Party *p, s32 id) {
    s32 i;
    if (id < 0) {
        return -1;
    }
    for (i = 0; i < 7; i++) {
        if (p->res[i] == id) {
            return i;
        }
    }
    return -1;
}

static inline s32 isAct(Party *p, s32 id) {
    s32 r = findAct(p, id);
    return (r < 0) ^ 1;
}

static inline bool valid(Party *p, s32 id) {
    return !(PartyFindSlotOfId_3c3070(p, id) < 0);
}

extern "C" s32 PartySwapMembers_3c0ad0(Party *p, s32 a, s32 b, s32 pad, s32 test) {
    Chr *ca;
    Chr *cb;
    s32 inA;
    s32 inB;
    s32 ia;
    s32 ib;
    Chr *actC;
    Chr *resC;
    s32 actId;
    s32 resId;

    if (a < 0 || b < 0) {
        return 0;
    }
    if (a == b) {
        return 0;
    }
    ca = CharaMgrPoolFindById_3a8c60(*(s32 *)(D_00483890 + 0x14), a);
    if (ca == 0) {
        return 0;
    }
    cb = CharaMgrPoolFindById_3a8c60(*(s32 *)(D_00483890 + 0x14), b);
    if (cb == 0) {
        return 0;
    }
    if (!valid(p, a) || !valid(p, b)) {
        return 0;
    }
    inA = findAct(p, a) >= 0;
    inB = findAct(p, b);
    if ((u8)inA == (inB >= 0)) {
        if (inA) {
            ia = findAct(p, a);
            ib = findAct(p, b);
            if (ia >= 0 && ib >= 0) {
                if (!test) {
                    p->act[ib] = a;
                    p->act[ia] = b;
                    PartyCompactSlots_3c2c50(p);
                }
                return 1;
            }
        } else {
            ia = findRes(p, a);
            ib = findRes(p, b);
            if (ia >= 0 && ib >= 0) {
                if (!test) {
                    p->res[ib] = a;
                    p->res[ia] = b;
                    PartyCompactSlots_3c2c50(p);
                }
                return 1;
            }
        }
    } else {
        if (inA) {
            actC = ca;
            actId = a;
            ia = findAct(p, a);
            resC = cb;
            resId = b;
            ib = findRes(p, b);
        } else {
            actC = cb;
            actId = b;
            ia = findAct(p, b);
            resC = ca;
            resId = a;
            ib = findRes(p, a);
        }
        if (ia >= 0 && resId >= 0 && actC != 0 && !((Flags *)((u8 *)actC + 0x234))->b0 &&
            !((Flags *)((u8 *)resC + 0x234))->b2) {
            if (!test) {
                p->act[ia] = resId;
                p->res[ib] = actId;
                PartyCompactSlots_3c2c50(p);
                if (((Flags *)(*(u8 **)(D_00483890 + 0x20) + 0x24C))->b0 && resC != 0) {
                    resC->Refresh(1);
                }
            }
            return 1;
        }
    }
    return 0;
}
