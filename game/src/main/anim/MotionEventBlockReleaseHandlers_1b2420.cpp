#include "types.h"

/* Iterates arg0's Node list (Node.f0 = next); each Node's f10 field holds a
   pointer-to-object-pointer ("slot"); if the slot is non-NULL and holds a
   live object, calls the object's virtual method at vtable+0x14
   (virtual_index = (0x14-8)/4 = 3) passing the slot itself as the argument,
   and counts how many objects were notified. */

class Base {
public:
    VC_VPTR_MEMBER;
    
    
    void v3(void *arg1) { VCM(void, (void *, void *), 0x14, arg1); }
};

struct Node {
    Node *f0;
    u8 pad4[0xC];
    Base **f10;
};

struct Owner {
    u8 pad0[0x10];
    Node *f10;
};

extern "C" s32 MotionEventBlockReleaseHandlers_1b2420(Owner *arg0)
{
    s32 count;
    Node *node;
    Base **slot;
    Base *obj;
    s32 hit;

    count = 0;
    node = arg0->f10;
    while (node != 0) {
        slot = node->f10;
        if (slot != 0) {
            obj = *slot;
            if (obj == 0) {
                hit = 0;
            } else {
                obj->v3(slot);
                hit = 1;
            }
            count += hit;
        }
        node = node->f0;
    }
    return count;
}
