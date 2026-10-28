/* rgp:protos */
#line 1
#include "types.h"
/* insect 0x0051DA90 -- C++ virtual dispatch, vptr at +0x1B0, slot 0x58 =
 * virtual #20.  [[jalr-is-cpp-virtual]]
 * insect_jtbl_00525480 has NINE entries and every one of them is 0x0051DB1C, so the
 * switch is nine MERGED case labels over one body. */

class VE {
public:
    u8 pad000[0x1B0];
    VC_VPTR_MEMBER;  
      
      
      
      
      
     
    void s20() { VCM0(void, 0x58); }               /* slot 0x58 */
};

struct E {
    void *f00;
    u8    pad004[0x8 - 0x4];
    s32   f08;
    u8    pad00C[0x10 - 0xC];
    s32   f10;
    s32   f14;
};

struct O {
    void *f00;
    u8    pad004[0x8 - 0x4];
    E    *arr[15];
};

extern "C" void *GetDrawCtxNameTable_15de40(void);
extern "C" void NameTableFreeGroup_158ac0(void *p, s32 id);
extern "C" void MemStackHeapFree_14dcb0(void *h, s32 k);

extern "C" s32 insect_InsectBattleEffectsRemove_51da90(O *o, s32 a, s32 b)
{
    s32 i;
    E *e;
    s32 h;

    for (i = 0; i < 15; i++) {
        e = o->arr[i];
        if (e != 0) {
            if ((b == e->f14 && e->f08 == a) || e->f14 == -1) {
                h = e->f10;
                if (h != 0) {
                    switch (b) {
                    case 0x1A: case 0x1B: case 0x1C: case 0x1D: case 0x1E:
                    case 0x1F: case 0x20: case 0x21: case 0x22:
                        NameTableFreeGroup_158ac0(GetDrawCtxNameTable_15de40(), 0x29D);
                        break;
                    }
                    if (o->arr[i]->f00 != 0) {
                        ((VE *)o->arr[i]->f00)->s20();
                    }
                    MemStackHeapFree_14dcb0(o->f00, h);
                    o->arr[i] = 0;
                    return 1;
                }
            }
        }
    }
    return 0;
}
