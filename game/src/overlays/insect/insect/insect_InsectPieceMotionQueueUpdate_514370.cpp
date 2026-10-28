/* rgp:protos */
#line 1
#include "types.h"
/* insect 0x00514370 -- C++ virtual dispatch, vptr at +0x1B0, slot 0x44 =
 * virtual #15.  [[jalr-is-cpp-virtual]]
 * The two-way `beq` chain on e[0].f01 with the arms in ADDRESS order 1 then 2
 * is a `switch` written case 1 first; the compare chain is REVERSED.
 * [[insect-dispatch-branch-polarity]] */

class VE {
public:
    u8 pad000[0x1B0];
    VC_VPTR_MEMBER;  
      
      
      
      
    void s15(f32 t) { VCM(void, (void *, f32), 0x44, t); }          /* slot 0x44 */
};

struct E {
    u8  f00;
    s8  f01;
    u8  pad02[6];
    f32 f08;
    u8  f0C[0x14];
};

struct O {
    u8  pad000[0x6C];
    s16 f6C;
    u8  pad06E[0xE8 - 0x6E];
    E   e[8];
};

extern "C" void insect_InsectPieceMotionSlotCopy_514790(E *a, E *b);
extern "C" void insect_InsectPieceMotionSlotClear_514810(E *a);
extern "C" void *GetCurrentScene_1f5be0(void);
extern "C" VE *ObjRecGetLiveObject_1c4a90(void *h, s32 n);
extern "C" void ModelObjPlayMotionByName_1867a0(VE *p, void *s, s32 f);
extern "C" f32 ModelObjGetMotionPhase_1add70(VE *p);

extern "C" void insect_InsectPieceMotionQueueUpdate_514370(O *o)
{
    s32 i;
    VE *p;
    E  *e;
    s32 n;
    void *h;
    f32 lim;

    e = &o->e[0];
    if (o->e[0].f01 == 0) {
        for (i = 0; i < 7; i++) {
            insect_InsectPieceMotionSlotCopy_514790(&o->e[i], &o->e[i + 1]);
        }
        insect_InsectPieceMotionSlotClear_514810(&o->e[7]);
    } else if ((e->f00 & 2) == 0 && o->e[1].f01 != 0) {
        for (i = 0; i < 7; i++) {
            insect_InsectPieceMotionSlotCopy_514790(&o->e[i], &o->e[i + 1]);
        }
        insect_InsectPieceMotionSlotClear_514810(&o->e[7]);
    }
    n = o->f6C;
    h = GetCurrentScene_1f5be0();
    p = ObjRecGetLiveObject_1c4a90(h, n);
    switch (e->f01) {
    case 1:
        if (p != 0) {
            ModelObjPlayMotionByName_1867a0(p, e->f0C, e->f00);
            if ((e->f00 & 4) != 0) {
                p->s15(1.0f);
            }
            e->f01 = 2;
        }
        break;
    case 2:
        if (p != 0) {
            if ((e->f00 & 2) != 0) {
                lim = e->f08;
                if (ModelObjGetMotionPhase_1add70(p) >= lim) {
                    e->f01 = 0;
                }
            }
        }
        break;
    }
}
