/* rgp:protos */
#line 1
/* Draft note: the first PartyCountMembers_3c2010() call showed an incomplete arg list
   in the m2c IR ("(void*)1, 1"); guessed as PartyCountMembers_3c2010(arg0, 1, 1) to
   match the second (complete) call in this same function -- same
   "empty-paren-call reuses an untouched register" trap as elsewhere in
   this lane. Unverified against the raw asm. */
#include "types.h"
#pragma inline_depth(8)
#undef NULL
#define NULL 0
extern "C" {

extern void *PoolGetUsedElem_36acb0(s32 arg0, s32 arg1);
extern void **CharaMgrPoolFindById_3a8c60(s32 arg0, s32 arg1);
extern s32 PartyCountReserve_3c1c20(void *arg0, s32 arg1, s32 arg2);
extern s32 PartyCountMembers_3c2010(void *arg0, s32 arg1, s32 arg2);
extern s32 ItemInInvCategory0_3d4960(void *arg0);
extern s32 D_00465B50[];
extern void *D_00483890;

class VC_0 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void f(s32 x0, s32 x1) { VCM(void, (void *, s32, s32), 0x2B8, x0, x1); }
};
class VC_1 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void f(s32 x0) { VCM(void, (void *, s32), 0xC4, x0); }
};

typedef struct {
    u8 pad0[0xA];
    u8 f0 : 1;
    u8 f1 : 1;
    u8 fr : 6;
} Bits3c0;

static inline s32 slotId(void *arg0, s32 i) {
    s32 k;
    if (i < 0 || i >= 0xA) return -1;
    k = PartyCountMembers_3c2010(arg0, 1, 1);
    if (i < k) return *(s16 *)((u8 *)arg0 + i * 2 + 0x190);
    if (i < k + 7) return *(s16 *)((u8 *)arg0 + (i - k) * 2 + 0x196);
    return -1;
}

static inline void **getObj(void *arg0, s32 i) {
    s32 id;
    if (D_00483890 == NULL) return NULL;
    id = slotId(arg0, i);
    if (id < 0) return NULL;
    return CharaMgrPoolFindById_3a8c60(*(s32 *)((u8 *)D_00483890 + 0x14), id);
}

s32 PartyFullRestoreAll_3c0930(void *arg0)
{
    s32 n;
    s32 i;
    void **o;
    s32 m;
    s32 j;
    void *q;

    n = PartyCountMembers_3c2010(arg0, 1, 1) + PartyCountReserve_3c1c20(arg0, 1, 1);
    for (i = 0; i < n; i++) {
        o = getObj(arg0, i);
        if (o != NULL) {
            ((VC_0 *)(o))->f(0, 0);
        }
    }
    m = D_00465B50[0];
    for (j = 0; j < m; j++) {
        q = PoolGetUsedElem_36acb0(*(s32 *)((u8 *)arg0 + 0x168), j);
        if (q != NULL && ((unsigned char)ItemInInvCategory0_3d4960(q)) != 0 && !((Bits3c0 *)q)->f1) {
            ((VC_1 *)(q))->f(1);
        }
    }
    return 1;
}

}
