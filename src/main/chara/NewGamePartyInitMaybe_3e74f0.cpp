#include "types.h"

typedef struct Btn {
    u8 pad0[0x234];
    bool on : 1;
} Btn;

class Pnl {
public:
    virtual void v08();
    virtual void v0C();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1C();
};

typedef struct Menu {
    u8 pad0[0x14];
    s32 m14;
    Pnl *pnl;
} Menu;

extern "C" {
extern void CharaMgrPoolClear_3a8d40(s32);
extern Btn *CharaCreateFromPcDef_3a8d80(s32, s32, s32);
extern void PartySetAreaMaybe_3cab50(Pnl *, s32, s32, s32);
extern void GameDataFlagsSetOrClear_3e4580(Menu *, s32, s32);
}

extern "C" s32 NewGamePartyInitMaybe_3e74f0(Menu *self)
{
    Btn *b0;
    Btn *b1;
    Btn *b2;
    Btn *b3;
    Btn *b4;
    Btn *b5;
    Btn *b6;
    Btn *b7;
    Btn *b8;
    Btn *b9;

    CharaMgrPoolClear_3a8d40(self->m14);
    b0 = CharaCreateFromPcDef_3a8d80(self->m14, 0, 0x2AF9);
    b1 = CharaCreateFromPcDef_3a8d80(self->m14, 1, 0x2AFC);
    b2 = CharaCreateFromPcDef_3a8d80(self->m14, 2, 0x2AFB);
    b3 = CharaCreateFromPcDef_3a8d80(self->m14, 3, 0x2AFD);
    b4 = CharaCreateFromPcDef_3a8d80(self->m14, 4, 0x2AFA);
    b5 = CharaCreateFromPcDef_3a8d80(self->m14, 5, 0x2AFF);
    b6 = CharaCreateFromPcDef_3a8d80(self->m14, 6, 0x2AFE);
    b7 = CharaCreateFromPcDef_3a8d80(self->m14, 7, 0x2B00);
    b8 = CharaCreateFromPcDef_3a8d80(self->m14, 8, 0x2B01);
    b9 = CharaCreateFromPcDef_3a8d80(self->m14, 9, 0x2B02);
    if (b0 != 0) {
        b0->on = true;
    }
    if (b1 != 0) {
        b1->on = false;
    }
    if (b2 != 0) {
        b2->on = false;
    }
    if (b3 != 0) {
        b3->on = false;
    }
    if (b4 != 0) {
        b4->on = false;
    }
    if (b5 != 0) {
        b5->on = false;
    }
    if (b6 != 0) {
        b6->on = false;
    }
    if (b7 != 0) {
        b7->on = false;
    }
    if (b8 != 0) {
        b8->on = false;
    }
    if (b9 != 0) {
        b9->on = false;
    }
    if (self->pnl != 0) {
        self->pnl->v1C();
    }
    PartySetAreaMaybe_3cab50(self->pnl, 2, 1, 0);
    GameDataFlagsSetOrClear_3e4580(self, 1, 1);
    return 1;
}
