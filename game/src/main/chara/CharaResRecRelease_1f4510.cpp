#include "types.h"

class VE {
public:
    u8 pad000[0x1B0];
    VC_VPTR_MEMBER;  
      
      
      
      
     void s16() { VCM0(void, 0x48); } 
     
    void s20() { VCM0(void, 0x58); }               /* slot 0x58 */
};

struct Slot {
    s16 id;
    s16 x2;
    s16 x4;
    u8 x6;
    u8 state;
    VE *obj;
    char name[0x28];
    s32 x34;
    u8 pad38[0x2C];
    s16 x64;
};

struct T1 {
    u8 pad00[0x6C];
    s16 x6C;
    u8 pad6e[2];
    s32 x70;
};

struct T2 {
    u8 pad00[0x54];
    u8 sub[0x58];
    s16 xAC;
    s16 xAE;
    s16 xB0;
    s16 xB2;
    u8 padb4[4];
    s32 xB8;
};

extern "C" {
s32 GetCharaDataMgr_1fdb70(void);
void GetWorldDataMgr_1fedf0(void);
void GameSceneObjReleaseMaybe_1cfc50(s32, s32);
T1 *CharaDataFindById_1ed990(s32, s32);
s32 GetActionMgr_1fdb50(void);
s32 ActionMgrFindById_233b50(s32, s32);
T2 *CharaGetAi_214a10(s32);
void ScriptVmReset_176bd0(void *);
void MemStackHeapFree_14dcb0(s32, s32);
void MemStackClear_14dff0(char *);
u32 strlen(const char *);
char *strcpy(char *, const char *);
extern char D_0045B8B8[0x400];
}

static inline bool valid(s32 x) {
    bool r;
    r = false;
    if (x < 0) {
        goto done;
    }
    if (x >= 12) {
        goto done;
    }
    r = true;
done:
    return r;
}

extern "C" void CharaResRecRelease_1f4510(Slot *slot, s32 arg1, s32 arg2) {
    s32 h;
    bool b1;
    bool b2;
    T1 *p;
    s32 q;
    T2 *t;

    h = GetCharaDataMgr_1fdb70();
    GetWorldDataMgr_1fedf0();
    b1 = false;
    b2 = false;
    if (slot->obj != 0) {
        GameSceneObjReleaseMaybe_1cfc50(arg1, slot->id);
        slot->obj->s20();
        b1 = true;
        b2 = true;
        p = CharaDataFindById_1ed990(h, slot->x4);
        if (p != 0 && p->x6C > 0) {
            p->x6C--;
        }
    } else {
        GameSceneObjReleaseMaybe_1cfc50(arg1, slot->id);
        if (slot->state == 0) {
            GameSceneObjReleaseMaybe_1cfc50(arg1, valid(slot->id) ? slot->id * 4 + 0xC : -1);
            GameSceneObjReleaseMaybe_1cfc50(arg1, valid(slot->id) ? slot->id * 4 + 0xD : -1);
            GameSceneObjReleaseMaybe_1cfc50(arg1, valid(slot->id) ? slot->id * 4 + 0xE : -1);
            GameSceneObjReleaseMaybe_1cfc50(arg1, valid(slot->id) ? slot->id * 4 + 0xF : -1);
        }
        if (slot->state == 2) {
            b1 = true;
            p = CharaDataFindById_1ed990(h, slot->x4);
            if (p != 0 && slot->id == p->x70) {
                b2 = true;
                p->x70 = -1;
            }
        }
        if (slot->x2 == 0x2F11) {
            GameSceneObjReleaseMaybe_1cfc50(arg1, 0x9C);
        }
    }
    q = ActionMgrFindById_233b50(GetActionMgr_1fdb50(), slot->id);
    if (q != 0) {
        t = CharaGetAi_214a10(q);
        if (t != 0) {
            ScriptVmReset_176bd0(t);
            t->xAC = -1;
            t->xAE = -1;
            ScriptVmReset_176bd0(t->sub);
            t->xB0 = -1;
            t->xB2 = -1;
            t->xB8 = 0;
        }
    }
    if (b1) {
        if (b2 && arg2 != 0 && slot->x34 != 0) {
            MemStackHeapFree_14dcb0(arg2, slot->x34);
        }
        MemStackClear_14dff0(slot->name);
        if (strlen(D_0045B8B8) < 16) {
            strcpy(slot->name, D_0045B8B8);
        }
    }
    slot->state = 0xFF;
    slot->id = -1;
    slot->x2 = -1;
    slot->x4 = -1;
    slot->obj = 0;
    slot->x6 = 0;
    slot->x64 = 0;
}
