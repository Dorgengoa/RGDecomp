#include "types.h"

extern const u8 D_00471508[];
extern const u8 D_00471638[];
extern const u8 D_00471648[];
extern const u8 D_00471658[];
extern void UskMemoryReset_42e030(void *);
extern void UskStackClear_42e460(void *);
extern void DListClear_42ea80(void *);
extern void OperatorDelete_100840(void *);

struct Obj_FUN_002d1c90 {
    u8 pad000[0xC];
    const u8 *m0C;
};

void *UskMemoryDtor_2d1c90(struct Obj_FUN_002d1c90 *o, s16 flag)
{
    void *p;

    if (o != 0) {
        UskMemoryReset_42e030(o);
        p = (u8 *)o + 0x14;
        if (p != 0) {
            UskStackClear_42e460(p);
        }
        if (o != 0) {
            o->m0C = D_00471508;
            DListClear_42ea80(o);
            if (o != 0) {
                o->m0C = D_00471638;
                DListClear_42ea80(o);
                if (o != 0) {
                    o->m0C = D_00471648;
                    DListClear_42ea80(o);
                    if (o != 0) {
                        o->m0C = D_00471658;
                        DListClear_42ea80(o);
                        if (o != 0) {
                            DListClear_42ea80(o);
                        }
                    }
                }
            }
        }
        if (flag > 0) {
            OperatorDelete_100840(o);
        }
    }
    return o;
}
