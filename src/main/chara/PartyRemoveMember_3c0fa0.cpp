#include "types.h"

class Obj {
public:
    virtual void v008();
    virtual void v00C();
    virtual void v010();
    virtual void v014();
    virtual void v018();
    virtual void v01C();
    virtual void v020();
    virtual void v024();
    virtual void v028();
    virtual void v02C();
    virtual void v030();
    virtual void v034();
    virtual void v038();
    virtual void v03C();
    virtual void v040();
    virtual void v044();
    virtual void v048();
    virtual void v04C();
    virtual void v050();
    virtual void v054();
    virtual void v058();
    virtual void v05C();
    virtual void v060();
    virtual void v064();
    virtual void v068();
    virtual void v06C();
    virtual void v070();
    virtual void v074();
    virtual void v078();
    virtual void v07C();
    virtual void v080();
    virtual void v084();
    virtual void v088();
    virtual void v08C();
    virtual void v090();
    virtual void v094();
    virtual void v098();
    virtual void v09C();
    virtual void v0A0();
    virtual void v0A4();
    virtual void v0A8();
    virtual void v0AC();
    virtual void v0B0();
    virtual void v0B4();
    virtual void v0B8();
    virtual void v0BC();
    virtual void v0C0();
    virtual void v0C4();
    virtual void v0C8();
    virtual void v0CC();
    virtual void v0D0();
    virtual void v0D4();
    virtual void v0D8();
    virtual void v0DC();
    virtual void v0E0();
    virtual void v0E4();
    virtual void v0E8();
    virtual void v0EC();
    virtual void v0F0();
    virtual void v0F4();
    virtual void v0F8();
    virtual void v0FC();
    virtual void v100();
    virtual void v104();
    virtual void v108();
    virtual void v10C();
    virtual void v110();
    virtual void v114();
    virtual void v118();
    virtual void v11C();
    virtual void v120();
    virtual void v124();
    virtual void v128();
    virtual void v12C();
    virtual void v130();
    virtual void v134();
    virtual void v138();
    virtual void v13C();
    virtual void v140();
    virtual void v144();
    virtual void v148();
    virtual void v14C();
    virtual void v150();
    virtual void v154();
    virtual void v158();
    virtual void v15C();
    virtual void v160();
    virtual void v164();
    virtual void v168();
    virtual void v16C();
    virtual void v170();
    virtual void v174();
    virtual void v178();
    virtual void v17C();
    virtual void v180();
    virtual void v184();
    virtual void v188();
    virtual void v18C();
    virtual void v190();
    virtual void v194();
    virtual void v198();
    virtual void v19C();
    virtual void v1A0();
    virtual void v1A4();
    virtual void v1A8();
    virtual void v1AC();
    virtual void v1B0();
    virtual void v1B4();
    virtual void v1B8();
    virtual void v1BC();
    virtual void v1C0();
    virtual void v1C4();
    virtual void v1C8();
    virtual void v1CC();
    virtual void v1D0();
    virtual void v1D4();
    virtual void v1D8();
    virtual void v1DC();
    virtual void v1E0();
    virtual void v1E4();
    virtual void v1E8();
    virtual void v1EC();
    virtual void v1F0();
    virtual void v1F4();
    virtual void v1F8();
    virtual void v1FC();
    virtual void v200();
    virtual void v204();
    virtual void v208();
    virtual void v20C();
    virtual void v210();
    virtual void v214();
    virtual void v218();
    virtual void v21C();
    virtual void v220();
    virtual void v224();
    virtual void v228();
    virtual void v22C();
    virtual void v230();
    virtual void v234();
    virtual void v238();
    virtual void v23C();
    virtual void v240();
    virtual void v244();
    virtual void v248();
    virtual void v24C();
    virtual void v250();
    virtual void v254();
    virtual void v258();
    virtual void v25C();
    virtual void v260();
    virtual void v264();
    virtual void v268();
    virtual void v26C();
    virtual void v270();
    virtual void v274();
    virtual void v278();
    virtual void v27C();
    virtual void v280();
    virtual void v284();
    virtual void v288();
    virtual void v28C();
    virtual void v290();
    virtual void v294();
    virtual void v298();
    virtual void v29C();
    virtual void v2A0();
    virtual void v2A4();
    virtual void v2A8();
    virtual void v2AC();
    virtual void v2B0();
    virtual void v2B4();
    virtual void v2B8();
    virtual void v2BC();
    virtual void v2C0();
    virtual void v2C4();
    virtual void v2C8();
    virtual void v2CC();
    virtual void v2D0();
    virtual void v2D4();
    virtual void v2D8();
    virtual void v2DC();
    virtual void v2E0();
    virtual void v2E4();
    virtual void v2E8();
    virtual void v2EC();
    virtual void v2F0();
    virtual void v2F4();
    virtual void v2F8();
    virtual void v2FC();
    virtual void v300();
    virtual void v304();
    virtual void v308();
    virtual void v30C();
    virtual void v310();
    virtual void v314();
    virtual void v318();
    virtual void v31C();
    virtual void v320();
    virtual void v324();
    virtual void v328();
    virtual void v32C();
    virtual void v330();
    virtual void v334();
    virtual void v338();
    virtual void v33C();
    virtual void v340();
    virtual void v344();
    virtual void v348();
    virtual void v34C();
    virtual void v350();
    virtual void v354();
    virtual void v358();
    virtual void v35C();
    virtual void v360();
    virtual void v364();
    virtual void v368();
    virtual void v36C();
    virtual void v370();
    virtual void v374();
    virtual void v378();
    virtual void v37C();
    virtual void v380();
    virtual void v384();
    virtual s32 get1();
    virtual s32 get2();
    virtual void v390();
    virtual void v394();
    virtual void v398();
    virtual void v39C();
    virtual void v3A0();
    virtual void done1();
    virtual void done2();
    virtual void v3AC();
    virtual void v3B0();
    virtual void v3B4();
    virtual void v3B8();
    virtual void v3BC();
    virtual void v3C0();
    virtual s32 get3();
    virtual void v3C8();
    virtual void done3();
    virtual void v3D0();
    virtual void v3D4();
    virtual void v3D8();
    virtual void v3DC();
    virtual void finish();
};

typedef struct Self {
    u8 pad0[0x168];
    s32 scene;
    u8 pad16C[0x20];
    s16 n;
    u8 pad18E[2];
    s16 list[3];
    s16 slots[7];
} Self;

typedef struct Mgr {
    u8 pad0[0x14];
    s32 db;
} Mgr;

extern "C" {
void PoolFreeElemByPtr_36aa80(s32, s32);
Obj *CharaMgrPoolFindById_3a8c60(s32, s32);
void PartyCompactSlots_3c2c50(Self *);
s32 PartyFindSlotOfId_3c3070();
void ItemMarkRemoved_3d4130(s32, s32);
extern Mgr *D_00483890;
}

static inline s32 ready() {
    return PartyFindSlotOfId_3c3070() >= 0;
}

static inline s32 findList(Self *self, s32 id) {
    s32 i;
    if (id < 0) {
        return -1;
    }
    for (i = 0; i < self->n; i++) {
        if (self->list[i] == id) {
            return i;
        }
    }
    return -1;
}

static inline s32 findSlot(Self *self, s32 id) {
    s32 i;
    if (id < 0) {
        return -1;
    }
    for (i = 0; i < 7; i++) {
        if (self->slots[i] == id) {
            return i;
        }
    }
    return -1;
}

static inline void attach(Self *self, s32 r) {
    if (r != 0 && self->scene != 0) {
        ItemMarkRemoved_3d4130(r, 1);
        PoolFreeElemByPtr_36aa80(self->scene, r);
    }
}

extern "C" s32 PartyRemoveMember_3c0fa0(Self *self, s32 id, s32 arg2, s32 arg3) {
    s32 idx;
    s32 found;
    Obj *obj;
    s32 k;
    s32 r;

    if (id < 0) {
        return 0;
    }
    if (D_00483890 == NULL) {
        return 0;
    }
    if (!ready()) {
        return 0;
    }
    found = 0;
    idx = findList(self, id);
    if (idx >= 0) {
        if (arg3 == 0) {
            self->list[idx] = -1;
            PartyCompactSlots_3c2c50(self);
        }
        found = 1;
    }
    if (found != 1) {
        idx = findSlot(self, id);
        if (idx >= 0) {
            if (arg3 == 0) {
                self->slots[idx] = -1;
                PartyCompactSlots_3c2c50(self);
            }
            found = 1;
        }
    }
    if (found == 1) {
        obj = CharaMgrPoolFindById_3a8c60(D_00483890->db, id);
        if (obj != NULL) {
            if (arg2 != 0) {
                k = 1;
                do {
                    r = 0;
                    switch (k) {
                    case 1:
                        r = obj->get1();
                        obj->done1();
                        break;
                    case 2:
                        r = obj->get2();
                        obj->done2();
                        break;
                    case 3:
                        r = obj->get3();
                        obj->done3();
                        break;
                    }
                    if (r != 0) {
                        attach(self, r);
                    }
                    k++;
                } while (k <= 3);
            }
            if (arg2 != 0) {
                obj->finish();
            }
        }
    }
    return found;
}
