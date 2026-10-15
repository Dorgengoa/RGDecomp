#include "types.h"

typedef struct Obj_FUN_002b0990 Obj_FUN_002b0990;

extern Obj_FUN_002b0990 *GetNpcDataHeap_1fdd70(void);
extern void *MemStackHeapAlloc_14db10(Obj_FUN_002b0990 *o, s32 a, s32 b, s32 c);
extern void MemStackHeapFree_14dcb0(Obj_FUN_002b0990 *o, void *m);

s32 NpcDataHeapCanAlloc_2b0990(void)
{
    Obj_FUN_002b0990 *o;
    void *m;

    o = GetNpcDataHeap_1fdd70();
    if (o == 0) {
        return 0;
    }
    m = MemStackHeapAlloc_14db10(o, 3, 0x780, 0x40);
    if (m != 0) {
        MemStackHeapFree_14dcb0(o, m);
    }
    return m != 0;
}
