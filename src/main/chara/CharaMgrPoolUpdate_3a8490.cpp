#include "types.h"

/* Same "vptr at object offset +0" shape as include/worldobj_cpp.h's
   WorldEntity, used locally (per the project convention seen in
   src/s13o/CharaGetEquippedWeapon_3acd40.cpp etc.) since only the one used slot needs a real
   signature. Used slot is +0xD0 -> virtual index (0xD0-8)/4 = 50, taking the
   function's own f32 argument. */

class V {
public:
    virtual void slot008();
    virtual void slot00C();
    virtual void slot010();
    virtual void slot014();
    virtual void slot018();
    virtual void slot01C();
    virtual void slot020();
    virtual void slot024();
    virtual void slot028();
    virtual void slot02C();
    virtual void slot030();
    virtual void slot034();
    virtual void slot038();
    virtual void slot03C();
    virtual void slot040();
    virtual void slot044();
    virtual void slot048();
    virtual void slot04C();
    virtual void slot050();
    virtual void slot054();
    virtual void slot058();
    virtual void slot05C();
    virtual void slot060();
    virtual void slot064();
    virtual void slot068();
    virtual void slot06C();
    virtual void slot070();
    virtual void slot074();
    virtual void slot078();
    virtual void slot07C();
    virtual void slot080();
    virtual void slot084();
    virtual void slot088();
    virtual void slot08C();
    virtual void slot090();
    virtual void slot094();
    virtual void slot098();
    virtual void slot09C();
    virtual void slot0A0();
    virtual void slot0A4();
    virtual void slot0A8();
    virtual void slot0AC();
    virtual void slot0B0();
    virtual void slot0B4();
    virtual void slot0B8();
    virtual void slot0BC();
    virtual void slot0C0();
    virtual void slot0C4();
    virtual void slot0C8();
    virtual void slot0CC();
    virtual void slot0D0(f32 arg1);
};

typedef struct ObjFUN_003a8490 {
    u8 pad0[0x8];
    s32 unk8;
} ObjFUN_003a8490;

extern "C" V *PoolGetUsedElem_36acb0(s32 arg0, s32 arg1);
extern "C" const s32 D_004659B8;

extern "C" s32 CharaMgrPoolUpdate_3a8490(ObjFUN_003a8490 *arg0, f32 fparg0)
{
    s32 temp16;
    s32 i;
    V *temp2;

    if (arg0->unk8 == 0) {
        return 0;
    }
    temp16 = D_004659B8;
    for (i = 0; i < temp16; i++) {
        temp2 = PoolGetUsedElem_36acb0(arg0->unk8, i);
        if (temp2 != NULL) {
            temp2->slot0D0(fparg0);
        }
    }
    return 1;
}
