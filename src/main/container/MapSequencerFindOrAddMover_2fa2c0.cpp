#include "types.h"

typedef struct Node002FA2C0 {
    u8 pad0[0x10];
    u8 body[0x10];
} Node002FA2C0;

class Mgr002FA2C0 {
    u8 pad0[0xC];
public:
    virtual s32 add(Node002FA2C0 *);
    u8 pad10[0x10];
    s32 unk20;
    s32 unk24;
};

extern "C" {
void MemStackHeapFree_14dcb0(s32, Node002FA2C0 *);
Node002FA2C0 *MemStackHeapAllocBack_14dcf0(s32, u32);
u32 AlignUp16_1cacd0(s32);
s32 MapNodeMoverInit_2fa6a0(void *, s32, s32, const char *);
const char *MapNodeMoverGetNodeName_2fa790(void *);
s32 MapNodeMoverGetAreaId_2fa7a0(void *);
s32 MapNodeMoverGetId_2fa7b0(void *);
void MapNodeMoverClear_2fa7c0(void *);
Node002FA2C0 *DListGetHead_42ea60(void);
Node002FA2C0 *DListGetNext_42eb30(Node002FA2C0 *);
void DListNodeInit_42ec10(Node002FA2C0 *);
s32 strcmp(const char *, const char *);
}

extern "C" s32 MapSequencerFindOrAddMover_2fa2c0(Mgr002FA2C0 *arg0, s32 arg1, const char *arg2)
{
    Node002FA2C0 *p;

    if (arg0->unk20 == 0) {
        return -1;
    }
    if (arg2 == NULL) {
        return -1;
    }
    for (p = DListGetHead_42ea60(); p != NULL; p = DListGetNext_42eb30(p)) {
        if (arg1 == MapNodeMoverGetAreaId_2fa7a0(p->body) && strcmp(arg2, MapNodeMoverGetNodeName_2fa790(p->body)) == 0) {
            return MapNodeMoverGetId_2fa7b0(p->body);
        }
    }
    p = MemStackHeapAllocBack_14dcf0(arg0->unk20, AlignUp16_1cacd0(0x60) >> 4);
    if (p == NULL) {
        MemStackHeapFree_14dcb0(arg0->unk20, p);
        return -1;
    }
    DListNodeInit_42ec10(p);
    MapNodeMoverClear_2fa7c0(p->body);
    if (MapNodeMoverInit_2fa6a0(p->body, arg0->unk24, arg1, arg2) == 0) {
        MemStackHeapFree_14dcb0(arg0->unk20, p);
        return -1;
    }
    if (arg0->add(p) == 0) {
        MemStackHeapFree_14dcb0(arg0->unk20, p);
        return -1;
    }
    arg0->unk24++;
    return MapNodeMoverGetId_2fa7b0(p->body);
}
