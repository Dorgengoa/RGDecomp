/* rgp:protos */
#line 1
#include "types.h"

struct Ent0042 {
    u8 pad0[0xD];
    u8 xD;
    u8 xE;
    u8 padF[0x24 - 0xF];
    s32 x24;
};

struct Grp0042 {
    u8 pad0[0x18];
    Ent0042 ent[5];
};

class Obj0042fc60 {
public:
    VC_VPTR_MEMBER; s32 slot08() { return VCM0(s32, 0x8); }
    
    s32 slot10(int rgp_fwd1 = 0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(s32, (void *, int, int, int), 0x10, rgp_fwd1, rgp_fwd2, rgp_fwd3); }
    u8 pad4[0x8 - 0x4];
    Grp0042 grp[20];
    s32 unk1188;
};

struct G3 { u8 pad[0x8]; s32 x8; };
struct G2 { u8 pad[0x40]; G3 *x40; };
struct G1 { u8 pad[0x8]; G2 *x8; };

extern "C" void *memcpy(void *, const void *, u32);
extern "C" s32 ItemDefFindInsect_40c690(s32, s32, s32);
extern "C" G1 *D_004840D8;

extern "C" s32 InsectTeamTableLoadBlob_42fc60(Obj0042fc60 *obj, void *src, s32 len, int rgp_a3)
{
    s32 s1188;
    s32 n;
    Grp0042 *g;
    s32 i;
    s32 j;
    Ent0042 *e;

    if (src == NULL || len <= 0) {
        return 0;
    }

    s1188 = obj->unk1188;
    n = obj->slot10((int)(long)(src), (int)(long)(len), (int)(long)(rgp_a3));
    if (len < n) {
        n = len;
    }

    memcpy((u8 *)obj + obj->slot08(), src, n);
    g = obj->grp;
    for (i = 0; i < 20; i++, g++) {
        e = g->ent;
        for (j = 0; j < 5; j++, e++) {
            e->x24 = ItemDefFindInsect_40c690(D_004840D8->x8->x40->x8, e->xD, e->xE);
        }
    }
    obj->unk1188 = s1188;
    return n;
}
