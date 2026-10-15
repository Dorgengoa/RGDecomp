#include "types.h"

class VE {
    u8 pad_[0x28];
public:
    virtual void f08();
};

/* `new` shape: allocate, then the inlined ctor guarded by its own null test,
   then a SECOND null test for the body (mwcc does not fold the two - each is a
   separate inlined block).  The tail append walks with `list != 0 && next != 0`
   which is why the store `list->next = node` is duplicated into the delay slot.
   Indirect call: table pointer at 0x28 of the new object, slot 0x8.
   $5 is never read - the second parameter is unused. */


extern "C" void *MemStackNew_14e230(s32, void *);
extern "C" void MotionEventBlockInit_1b2520(void *);
extern "C" void *SlotGetInt_15f720(void *);
extern "C" void *MemStackStrDup_14cff0(void *, void *);
extern "C" u8 D_004710D8[];

extern "C" s32 MotionEventCfgStartCmd_1b4460(void *a0, void *a1, void **holder)
{
    u8 *o;
    void *heap;
    u8 **tail;
    u8 *node;
    u8 *list;
    u8 *nxt;
    u8 *r;
    void *x;
    void *y;
    u8 *q;
    s32 v1;

    o = (u8 *)*holder;
    heap = *(void **)(o + 0x30);
    tail = *(u8 ***)(o + 0x34);
    node = (u8 *)MemStackNew_14e230(0x2C, heap);
    if (node != 0) {
        *(u8 **)(node + 0x28) = D_004710D8;
        MotionEventBlockInit_1b2520(node + 0x10);
        ((VE *)node)->f08();
    }
    if (node == 0) {
        r = 0;
    } else {
        list = *tail;
        if (list != 0) {
            while (list != 0) {
                nxt = *(u8 **)(list + 0x0);
                if (nxt == 0) {
                    break;
                }
                list = nxt;
            }
            *(u8 **)(list + 0x0) = node;
            if (node != 0) {
                *(u8 **)(node + 0x4) = list;
            }
        } else {
            *tail = node;
        }
        r = node + 0x10;
    }
    *(u8 **)(o + 0x3C) = r;
    if (r == 0) {
        return 0;
    }
    x = MemStackStrDup_14cff0(SlotGetInt_15f720(a0), heap);
    y = MemStackStrDup_14cff0(*(void **)(o + 0x10), heap);
    *(void **)(*(u8 **)(o + 0x3C) + 0x8) = x;
    *(void **)(*(u8 **)(o + 0x3C) + 0xC) = y;
    v1 = *(s32 *)(o + 0x4);
    q = *(u8 **)(o + 0x3C);
    *(s32 *)(q + 0x0) = *(s32 *)(o + 0x0);
    *(s32 *)(q + 0x4) = v1;
    return 1;
}
