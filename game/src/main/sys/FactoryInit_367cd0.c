/* rgp:protos */
#define RGP_SELF_FactoryInit_367cd0 1
#include "port/game_protos.h"
#line 1
/* PARKED s15i: ~17 unknown-typed ("?") externs including several
 * pointer-returning helpers (MemStackCtor_14e030/MemStackNew_14e130/FactoryGetHeap_367f10) whose
 * struct shapes are not inferable from this function alone; 0 round trips
 * spent. Needs cross-referencing a sibling call site (or the asm) to pin the
 * struct layout before writing typed C -- guessing offsets on a function
 * this call-heavy risks more wrong guesses than the round-trip budget
 * allows. Not attempted. */
/* s49m: MATCH */
#include "types.h"

typedef struct T58 {
    u8 pad[0x58];
} T58;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern u8 D_004830EC;
extern u8 D_004830F4;
extern u8 D_00462EA8[];
extern u8 D_00462EB8[];
extern u8 D_00462EC8[];

void FactoryInit_367cd0(void)
{
    T58 t __attribute__((aligned(16)));
    s32 id;
    s32 r;
    u8 *heap;
    u8 *p;
    u8 *q;
    s32 h28;
    s32 a;

    FactorySetObj_367f20(NULL);
    heap = ((u8 *)FactoryGetHeap_367f10());
    RecStackMemStackCreate_201d80(heap, &D_004830EC, D_00462EA8, 0x80);
    h28 = *(s32 *)(heap + 0x28);
    p = ((u8 *)MemStackNew_14e130(0x490, heap));
    if (p != NULL) {
        MemStackCtor_14e030(p + 0x68);
        MemStackCtor_14e030(p + 0x238);
        MemStackCtor_14e030(p + 0x304);
    }
    FactorySetObj_367f20(p);
    q = ((u8 *)MemStackNew_14e130(0x58, heap));
    if (q != NULL) {
        q = (u8 *)((T58 *)MemStackCtor_14e030(q));
    }
    FactorySetMapHeap_367ef0((T58 *)q);
    r = GetFactoryObj_367f30();
    if (r == 0 || FactoryGetMapHeap_367f00() == 0) {
        RecStackSlotRelease_201d10(((u8 *)FactoryGetHeap_367f10()), &D_004830EC);
        FactoryReset_367e80();
        return;
    }
    RecStackHeapCreate_201f10(FactoryGetMapHeap_367f00(), &D_004830F4, D_00462EB8, 0x26000);
    a = ((s32)GetMapMgr_201a90());
    MapMgrSetHeap_1e33f0(a, FactoryGetMapHeap_367f00());
    MemStackCtor_14e030(&t);
    id = -1;
    RecStackMemStackCreate_201d80(&t, &id, D_00462EC8, 0x14000);
    func_5049B0(r);
    func_5041A0(r, h28, 0x2000, 0x2000, 0x1C000);
    func_5048E0(r);
    func_505D60();
}
