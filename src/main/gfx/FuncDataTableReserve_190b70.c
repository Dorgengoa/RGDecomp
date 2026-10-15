#include "types.h"
#pragma optimization_level 3

typedef struct Data { u8 pad[0x40]; s32 f40; u8 pad2[0x6C]; } Data;
typedef struct Node { struct Node *next; struct Node *prev; s32 pad[2]; Data *data; s32 pad2; } Node;
typedef struct Obj { s32 f0; Node **list; } Obj;

extern void *MemStackNew_14e1b0(s32 size, s32 heap);
extern void *ConstructNewArray_100710(void *p, void *ctor, void *dtor, s32 size, s32 n);
extern void FuncDataTableNodeCtor_190d50();
extern void FuncDataRecCtor_190d30();

void FuncDataTableReserve_190b70(Obj *arg0, s32 arg1, s32 arg2) {
    s32 i;
    Node *node;
    Node **head;
    Node *p;
    Node *nodes;
    Data *datas;
    Data **pd;

    if (arg0->list == 0) {
        arg0->list = MemStackNew_14e1b0(0x34, arg2);
        if (arg0->list != 0) {
            for (i = 0; i < 13; i++) {
                arg0->list[i] = 0;
            }
        }
    }
    if (arg1 <= 0) return;
    nodes = ConstructNewArray_100710(MemStackNew_14e1b0(arg1 * 0x18 + 0x10, arg2), FuncDataTableNodeCtor_190d50, 0, 0x18, arg1);
    datas = ConstructNewArray_100710(MemStackNew_14e1b0(arg1 * 0xB0 + 0x10, arg2), FuncDataRecCtor_190d30, 0, 0xB0, arg1);
    if (nodes == 0 || datas == 0) return;
    for (i = 0; i < arg1; i++) {
        node = &nodes[i];
        pd = &node->data;
        *pd = &datas[i];
        head = arg0->list;
        if (head != 0 && node != 0) {
            p = *head;
            if (p == 0) {
                *head = node;
            } else {
                while (p != 0) {
                    if (p->next == 0) break;
                    p = p->next;
                }
                p->next = &nodes[i];
                if (&nodes[i] != 0) {
                    node->prev = p;
                }
            }
            (*pd)->f40 = 0;
        }
    }
}
