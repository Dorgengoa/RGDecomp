#include "types.h"

/* Node-append tail of the same list-append idiom as the already-admitted
   sibling src/s18M3/MotionEventBlockNewEvent_1b1df0.cpp (Node/Owner layout, D_00471048
   vtable init, VT14 slot 8 = virtual #0, K=0x14). m2c's signature skips
   straight from arg0 to arg2 -- arg1 is the real (unnamed, pass-through)
   heap arg forwarded unchanged into MemStackNew_14e230(0x18, arg1), same
   dropped-middle-parameter lever seen elsewhere in this lane. */

class VT14 {
    u8 pad_[0x14];
public:
    virtual void f8();
};

struct Node { Node *f0; Node *f4; u8 p8[0x8]; s32 f10; void *f14; };
struct Owner { u8 pad00[0x10]; Node *f10; };

extern "C" void *MemStackNew_14e230(s32, void *);
extern "C" u8 D_00471048[];

extern "C" void MotionEventBlockAppendEvent_1b2370(Owner *arg0, void *arg1, s32 arg2)
{
    Node *nd;
    Node *cur;
    Node *nx;

    nd = (Node *)MemStackNew_14e230(0x18, arg1);
    if (nd != 0) {
        nd->f14 = D_00471048;
        ((VT14 *)nd)->f8();
    }
    if (nd != 0) {
        nd->f10 = arg2;
        cur = arg0->f10;
        if (cur != 0) {
            while (cur != 0) {
                nx = cur->f0;
                if (nx == 0) {
                    break;
                }
                cur = nx;
            }
            cur->f0 = nd;
            if (nd != 0) {
                nd->f4 = cur;
            }
        } else {
            arg0->f10 = nd;
        }
    }
}
