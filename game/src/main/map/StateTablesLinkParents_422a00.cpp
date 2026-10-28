/* rgp:protos */
#line 1
#include "types.h"
#pragma optimize_for_size on

struct Iter { u8 pad[8]; };
struct List { u8 pad[0xC]; };
struct Pad88 { u8 pad[0x88]; };
struct Pad4 { u32 pad; };
struct Top : Pad88, List { };
struct Mid : Pad4, List { void *x10; };
struct Leaf { u8 pad[8]; Mid *x8; };

extern "C" void *IterNext_370040(Iter *arg0);
extern "C" void IterInit_370170(Iter *, List *, int, int);

extern "C" s32 StateTablesLinkParents_422a00(Top *arg0, s32 arg1, int rgp_a2, int rgp_a3)
{
    Iter sp48 __attribute__((aligned(16)));
    Iter sp40 __attribute__((aligned(16)));
    Iter sp38 __attribute__((aligned(16)));
    Mid *b;
    Mid *a;
    Leaf *c;

    if (arg1 == 0) {
        return 0;
    }
    IterInit_370170(&sp48, arg0, (int)rgp_a2, (int)rgp_a3);
    while (a = (Mid *)IterNext_370040(&sp48), a != 0) {
        IterInit_370170(&sp40, a, 0, 0);
        while (b = (Mid *)IterNext_370040(&sp40), b != 0) {
            b->x10 = a;
            IterInit_370170(&sp38, b, 0, 0);
            while ((c = (Leaf *)IterNext_370040(&sp38)) != 0) {
                c->x8 = b;
            }
        }
    }
    return 1;
}
