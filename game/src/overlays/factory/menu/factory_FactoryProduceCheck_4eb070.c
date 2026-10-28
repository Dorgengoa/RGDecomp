/* rgp:protos */
#define RGP_SELF_factory_FactoryProduceCheck_4eb070 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Node {
    s16 f0;
    u8  pad02[0x12];
    s8  f14;
} Node;

typedef struct Hold {
    u8    pad00[0x4];
    Node *f4;
} Hold;

typedef struct Ctx {
    u8    pad00[0x70];
    Hold *f70;
} Ctx;

typedef struct Obj {
    u8    pad00[0x18];
    void *f18;
} Obj;

extern Ctx  *D_00484A48;                        /* _gp - 0x728 */
extern void *D_00484A58;                        /* _gp - 0x718 */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 factory_FactoryProduceCheck_4eb070(void)
{
    void *w;
    Obj  *o;
    Node *n;
    s32   id;
    s32   v;
    s32   r;

    w = GetFactoryObj_367f30();
    if (w == 0) {
        return 0;
    }
    o = ((Obj *)GetGameData_1fede0());
    if (o == 0) {
        return 0;
    }
    if (D_00484A48->f70 == 0) {
        factory_FactoryMenuShowNotice_4ea590(0xE);
        return 0;
    }
    n = D_00484A48->f70->f4;
    id = n->f0;
    v = 0;
    if (n->f14 >= 0) {
        v = n->f14;
    }
    if (factory_FactoryHoppersAllFilled_4ffb50(w) == 0) {
        factory_FactoryMenuShowNotice_4ea590(0x10);
        return 0;
    }
    r = (s8)factory_FactoryMaterialMatchBlueprint_4f2750();
    if (r == -1) {
        factory_FactoryMenuShowNotice_4ea590(0x753E);
        return 0;
    }
    if (r == 0) {
        factory_FactoryMenuShowNotice_4ea590(0x7538);
        return 0;
    }
    if (InvAddItemCheckedMaybe_3c6460(o->f18, id, 1, v, 0) == 0) {
        factory_FactoryMenuShowNotice_4ea590(0x753F);
        return 0;
    }
    if (factory_FactoryPartsAllRunning_4ffc80(w) == 0 || factory_FactorySlotRoutesReachMachine_4ffd00(w) == 0) {
        factory_FactoryMenuShowNotice_4ea590(0xF);
        return 0;
    }
    return 1;
}
