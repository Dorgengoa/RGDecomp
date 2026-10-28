#include "types.h"

typedef struct Slot {
    u8 b[8];
} Slot;

typedef struct Info {
    s16 id;
} Info;

class Item {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    s32 getKind() { return VCM0(s32, 0x30); }
};

class Party {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    Info * getInfo() { return VCM0(Info *, 0x33C); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void refresh() { VCM0(void, 0x47C); }
};

class Unit {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    Info * getInfo() { return VCM0(Info *, 0x350); }
};

typedef struct Game {
    u8 pad[0x14];
    s32 x14;
    u8 pad18[4];
    s32 x1C;
} Game;

extern "C" {
extern s32 D_004DB920[0x100];
extern Game *GetGameData_1fede0(void);
extern s32 ScriptSlotGetInt_2cc9c0(Slot *s);
extern Party *CharaMgrPoolFindById_3a8c60(s32 a, s32 b);
extern Item *CharaFindSlotByRecId_3ad390(Party *p, s32 i);
extern s32 CharaCountAbilitiesFilteredMaybe_3add30(Party *p, s32 a, s32 b, s32 c);
extern Item *CharaGetEquipSlot_3ad420(Party *p, s32 i);
extern void AbilityReqSet_27a450(s32 w, s32 id, s32 who, Item *it, s32 kind);
extern Unit *ObjFindById_3bb3a0(s32 a, s32 b);
extern Item *UnitFindSlotByRecId_3bd840(Unit *u, s32 i);
extern s32 UnitGetSlotCount_3bd8c0(Unit *u);
extern Item *UnitGetEquipSlot_3bd7e0(Unit *u, s32 i);
}

#define GIVE_A(it) \
    if ((it) == 0) { \
        return 0; \
    } \
    party->refresh(); \
    AbilityReqSet_27a450(world, id, who, (it), (it)->getKind());

#define GIVE_B2(it) \
    if ((it) == 0) { \
        return 0; \
    } \
    AbilityReqSet_27a450(world, id, who2, (it), (it)->getKind());

#define GIVE_B(it) \
    if ((it) == 0) { \
        return 0; \
    } \
    AbilityReqSet_27a450(world, id, who, (it), (it)->getKind());

extern "C" s32 AiCmdAbilityReqSet_2caeb0(Slot *args, s32 argc)
{
    s32 who;
    s32 n;
    Unit *unit;
    Item *item2;
    s32 world;
    s32 id;
    Info *uinfo;
    s32 idx;
    Item *it2;
    s32 who2;
    Item *item;
    Item *it;
    Party *party;
    Game *game;
    Info *info;

    if (argc != 2) {
        return 0;
    }
    world = D_004DB920[0];
    game = GetGameData_1fede0();
    id = ScriptSlotGetInt_2cc9c0(args++);
    idx = ScriptSlotGetInt_2cc9c0(args);
    party = CharaMgrPoolFindById_3a8c60(game->x14, id);
    if (party != 0) {
        info = party->getInfo();
        if (info == 0) {
            return 0;
        }
        who = info->id;
        item = CharaFindSlotByRecId_3ad390(party, idx);
        if (item != 0) {
            GIVE_A(item);
        } else {
            n = CharaCountAbilitiesFilteredMaybe_3add30(party, -1, -1, 0);
            if (!(n > 0)) return 0;
            if (!(n > idx)) return 0;
            item2 = CharaGetEquipSlot_3ad420(party, idx);
            GIVE_A(item2);
        }
        return 1;
    }
    unit = ObjFindById_3bb3a0(game->x1C, id);
    if (unit != 0) {
        uinfo = unit->getInfo();
        if (uinfo == 0) {
            return 0;
        }
        who2 = uinfo->id;
        it = UnitFindSlotByRecId_3bd840(unit, idx);
        if (it != 0) {
            GIVE_B2(it);
        } else {
            n = UnitGetSlotCount_3bd8c0(unit);
            if (!(n > 0)) return 0;
            if (!(n > idx)) return 0;
            it2 = UnitGetEquipSlot_3bd7e0(unit, 0);
            GIVE_B2(it2);
        }
    }
    return 1;
}
