/* rgp:protos */
#line 1
#include "types.h"

extern "C" void MotionListInit_1726f0(void *);

class VE {
public:
    u8 pad000[0xE0];
    VC_VPTR_MEMBER;
    
    s32 v2(int rgp_fwd1 = 0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(s32, (void *, int, int, int), 0x10, rgp_fwd1, rgp_fwd2, rgp_fwd3); }
};

struct VT { u8 pad[0x10]; void (*f10)(void *); };
struct P { s32 a; s32 b; };

struct Obj {
    u8 pad0[0xF0];
    void *unkF0;
    u8 pad_F4[0x1B0 - 0xF4];
    void *unk1B0;
    u8 pad1B4[0x228 - 0x1B4];
    P arr1[4];
    P arr2[4];
    u8 pad268[0x360 - 0x268];
    void *unk360;
    u8 pad364[0x420 - 0x364];
    void *unk420;
    u8 pad424[0x430 - 0x424];
    s32 m430, m434, m438, m43C, m440;
};

extern "C" VT D_0046FFA0;
extern "C" u8 D_0046FFC0[];
extern "C" u8 D_00470440[];
extern "C" u8 D_00470690[];
extern "C" u8 D_00470ED0[];

extern "C" Obj *ModelObjCtor_1ef500(Obj *arg0, int rgp_a1, int rgp_a2, int rgp_a3)
{
    P *p;
    P *q;

    arg0->unk1B0 = D_0046FFC0;
    arg0->unkF0 = &D_0046FFA0;
    ((VE *)((u8 *)arg0 + 0x10))->v2((int)(long)(rgp_a1), (int)(long)(rgp_a2), (int)(long)(rgp_a3));
    arg0->unk1B0 = D_00470440;
    arg0->unk1B0 = D_00470690;
    MotionListInit_1726f0((u8 *)arg0 + 0x1F0);
    p = arg0->arr1;
    arg0->unk1B0 = D_00470ED0;
    do {
        p->b = -1;
        p->a = -1;
        p++;
    } while (p < (q = arg0->arr2));
    do {
        q->b = -1;
        q->a = -1;
        q++;
    } while (q < arg0->arr2 + 4);
    arg0->unk420 = D_0046FFC0;
    arg0->unk360 = &D_0046FFA0;
    ((VE *)((u8 *)arg0 + 0x280))->v2();
    arg0->m430 = 0;
    arg0->m438 = 0;
    arg0->m434 = 0;
    arg0->m440 = 0;
    arg0->m43C = 0;
    return arg0;
}
