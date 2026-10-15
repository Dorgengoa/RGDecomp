#include "types.h"

typedef struct {
    u8 pad0[0x10];
    s32 x10;
} Sub;

typedef struct {
    u8 pad0[0x18];
    s32 x18;
    Sub *x1C;
} Ctx;

typedef struct {
    u8 pad0[0xC];
    s32 xC;
} Item;

extern void ObjRecSetFlag2_1c3e80(s32, s32, s32);
extern s32 GetCurrentScene_1f5be0(void);
extern Ctx *GetGameData_1fede0(void);
extern Item *PoolGetUsedElem_36acb0(s32, s32);
extern s32 ObjMgrGetPoolCapacity_3bb0a0(Sub *);
extern s32 PartyCountMembers_3c2010(s32, s32, s32);
extern s32 PartyGetMemberId_3c2490(s32, s32);

static inline Item *getItem(Sub *s, s32 i)
{
    if (s->x10 != 0) {
        return PoolGetUsedElem_36acb0(s->x10, i);
    }
    return NULL;
}

static inline s32 GetN1(s32 a) { return PartyCountMembers_3c2010(a, 1, 1); }
void PartyMarkObjRecsMaybe_2f2a20(void)
{
    Ctx *p;
    s32 h;
    s32 n;
    s32 i;
    s32 k;
    s32 j;
    Item *it;
    s32 e;

    p = GetGameData_1fede0();
    h = GetCurrentScene_1f5be0();
    n = GetN1(p->x18);
    for (i = 0; i < n; i++) {
        k = PartyGetMemberId_3c2490(p->x18, i);
        if (k >= 0) {
            ObjRecSetFlag2_1c3e80(h, 1, k);
            e = (k + 1) * 4 + 0xB;
            for (j = k * 4 + 0xC; j < e; j++) {
                ObjRecSetFlag2_1c3e80(h, 1, j);
            }
        }
    }
    n = ObjMgrGetPoolCapacity_3bb0a0(p->x1C);
    for (i = 0; i < n; i++) {
        it = getItem(p->x1C, i);
        if (it != NULL) {
            if (it->xC >= 0) {
                ObjRecSetFlag2_1c3e80(h, 1, it->xC);
            }
        }
    }
}
