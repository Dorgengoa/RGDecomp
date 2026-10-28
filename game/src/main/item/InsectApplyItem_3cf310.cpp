/* rgp:protos */
#line 1
#pragma opt_propagation off
#include "types.h"

struct Info {
    s16 h0;
    s8 b2;
    s8 b3;
    s16 h4;
    s16 h6;
};

class Unit {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 GetHp() { return VCM0(s32, 0x13C); }
    
    
    void Set148(s32 a0) { VCM(void, (void *, s32), 0x148, a0); }
    
    void Set150(s32 a0) { VCM(void, (void *, s32), 0x150, a0); }
    
    
    
    
    
    
    void Set16c(s32 a0) { VCM(void, (void *, s32), 0x16C, a0); }
    
    
    void Set178(s32 a0) { VCM(void, (void *, s32), 0x178, a0); }
    
    
    void Set184(s32 a0) { VCM(void, (void *, s32), 0x184, a0); }
    
    
    void Set190(s32 a0, s32 a1) { VCM(void, (void *, s32, s32), 0x190, a0, a1); }
    
    
    u8 Get19c() { return VCM0(u8, 0x19C); }
    
    s32 Get1a4() { return VCM0(s32, 0x1A4); }
    
    
    
    
    
    void Set1bc(u16 a0, s32 a1, s32 a2) { VCM(void, (void *, u16, s32, s32), 0x1BC, a0, a1, a2); }

    s16 h4;             /* +0x04 */
    u8 pad6[0xA];
    Info *info;         /* +0x10 */
};

struct Rec {
    s16 a;              /* +0x00 */
    s16 b;              /* +0x02 */
    s16 c;              /* +0x04 */
    s16 pad6;
    s16 val;            /* +0x08 */
    s16 padA;
    s32 xC;             /* +0x0C */
};

struct Date {
    s16 a;
    s16 b;
    s16 c;
    s16 d;
    s16 e;
};

struct Ev {
    s16 id;             /* +0x00 */
    s16 val;            /* +0x02 */
    s16 h4;             /* +0x04 */
    s16 h6;             /* +0x06 */
};

struct Ev2 {
    s16 id;             /* +0x00 */
    s8 b2;
    s8 b3;
    s8 b4;
    s8 b5[6];
    s8 padB;
    u16 hC;             /* +0x0C */
    s8 padE;
    s8 bF;              /* +0x0F */
};

struct Cfg { u8 pad0[0x26]; s16 h26; s16 h28; s16 h2a; };
struct Lists { u8 pad0[0xC]; u8 *l0c; u8 *l10; u8 *l14; };
struct Db { u8 pad0[8]; s32 x8; };
struct Game { u8 pad0[0x40]; Db *db; u8 pad44[0x58]; Lists *lists; };
struct Key { u8 pad0[0x10]; s16 *id; };

extern "C" {
s32 InsectItemUsable_3cf910(int, int, void *, void *);
s32 ItemIsKindDId515_3d4570(Key *);
s32 ItemIsKindDId514_3d4530(Key *);
s32 ItemIsInsectFood_3d45b0(Key *);
s32 ItemGetInsectFoodId_3d45d0(Key *);
void InsectBreedRecReset_3d2730(Rec *);
void IterInit_370170(void *, void *, int, int);
void *IterNext_370040(void *);
s16 *ItemDefFindByKeys_40c6b0(s32, s32, s32, s32, s32);
void InsectRecPushBreedEntry_3cedf0(void *, Rec *);
s32 Rand_133710(void);
void InsectRollStatGain_3d11e0(Unit *, s32, s32);
u8 *ItemDefGetInsectData_40e0b0(Info *);
void InsectItemAddPersonalityMaybe_3d18f0(Unit *, s32);
void InsectItemCheckBecomeAdult_3cf880(Unit *, int, int, int);
void ItemConsume_3d41b0(Key *, s32, s32, int);
}
extern "C" s32 D_00465D80[];
extern "C" s32 D_004838E8;
extern "C" Game *D_004838EC;

extern "C" s32 InsectApplyItem_3cf310(void *self, Key *key, Unit *a, Unit *b)
{
    Unit *pair[2];
    Unit **pp;
    __attribute__((aligned(16))) unsigned char rgp_blk1[(0x0 + sizeof(Rec)) + (0x14)];
    Date dates[2] __attribute__((aligned(16)));
    u32 it[2];
    u32 it2[2];
    s32 aDead;
    s32 bDead;
    s32 i;
    Info *src;
    Date *dst;
    u8 *l;
    s32 found;
    Ev *e;
    Date *p;
    s32 m;
    s32 d;
    s32 y;
    s32 h;
    s16 *r;
    s32 n;
    s32 t;
    Ev2 *e2;
    s32 id;
    Cfg *cfg;
    s32 j;

    if (D_004838E8 == 0) {
        return 0;
    }
    if (key == 0 || a == 0) {
        return 0;
    }
    if (InsectItemUsable_3cf910((int)self, (int)key, (void *)a, (void *)b) == 0) {
        return 0;
    }
    aDead = a->GetHp() <= 0;
    bDead = 0;
    if (b != 0) {
        bDead = b->GetHp() <= 0;
    }
    if (ItemIsKindDId515_3d4570(key) != 0) {
        InsectBreedRecReset_3d2730(&(*(Rec *)(rgp_blk1 + 0x0)));
        (*(Rec *)(rgp_blk1 + 0x0)).a = a->h4;
        (*(Rec *)(rgp_blk1 + 0x0)).b = b->h4;
        (*(Rec *)(rgp_blk1 + 0x0)).c = 2;
        (*(Rec *)(rgp_blk1 + 0x0)).xC = 0;
        if (a->Get19c() == 1) {
            pair[0] = a;
            pair[1] = b;
        } else {
            pair[0] = b;
            pair[1] = a;
        }
        i = 0;
        do {
            pp = (Unit **)((u32)&pair[i]);
            src = (*pp)->info;
            { s16 v = src->h0;
            dst = &dates[i];
            dst->a = v; }
            dst->b = src->b2;
            dst->c = src->h4;
            dst->d = src->b3;
            dst->e = src->h6;
            i++;
        } while (i < 2);
        l = D_004838EC->lists->l14;
        if (l != 0) {
            l += 0x88;
        }
        IterInit_370170(it, l, 0, 0);
        found = 0;
        for (;;) {
            e = (Ev *)IterNext_370040(it);
            if (e == 0) {
                break;
            }
            if (e->h4 == dates[0].a && e->h6 == dates[1].a) {
                found = 1;
            }
            if (e->h6 == dates[0].a && e->h4 == dates[1].a) {
                found = 1;
            }
            if ((found != 0) ^ 1) {
                continue;
            }
            (*(Rec *)(rgp_blk1 + 0x0)).val = e->val;
            break;
        }
        if (!found) {
            p = &dates[0];
            if (dates[0].d != dates[1].d && dates[0].d < dates[1].d) {
                p = &dates[1];
            }
            if (dates[0].c == 0x7DF || dates[1].c == 0x7DF) {
                (*(Rec *)(rgp_blk1 + 0x0)).val = 0x424A;
            } else {
                d = p->d + 1;
                m = p->b;
                y = p->c;
                h = p->e;
                if (d >= 8) {
                    d = 7;
                }
                if (y == 0x7DF) {
                    goto zero;
                }
                if (y == 0x7E0) {
                zero:
                    d = 0;
                }
                r = ItemDefFindByKeys_40c6b0(D_004838EC->db->x8, m, y, d, h);
                if (r != 0) {
                    (*(Rec *)(rgp_blk1 + 0x0)).val = *r;
                }
            }
        }
        InsectRecPushBreedEntry_3cedf0(self, &(*(Rec *)(rgp_blk1 + 0x0)));
    } else if (ItemIsKindDId514_3d4530(key) != 0) {
        b->Set16c(D_00465D80[0]);
        if (!aDead) {
            a->Set148(-1);
            n = Rand_133710() % 10 + 1;
            t = a->Get1a4();
            InsectRollStatGain_3d11e0(a, t * n, 1);
        }
        if (!bDead) {
            b->Set148(-1);
            n = Rand_133710() % 10 + 1;
            t = b->Get1a4();
            InsectRollStatGain_3d11e0(b, t * n, 1);
        }
    } else {
        if (((unsigned char)ItemIsInsectFood_3d45b0(key)) == 0) {
            return 0;
        }
        l = D_004838EC->lists->l0c;
        if (l != 0) {
            l += 0x88;
        }
        IterInit_370170(it2, l, 0, 0);
        for (;;) {
            e2 = (Ev2 *)IterNext_370040(it2);
            if (e2 == 0) {
                break;
            }
            if (e2->id == ItemGetInsectFoodId_3d45d0(key)) {
                break;
            }
        }
        if (e2 != 0) {
            id = *key->id;
            cfg = (Cfg *)(ItemDefGetInsectData_40e0b0(a->info));
            if (cfg != 0) {
                if (cfg->h26 == id || cfg->h28 == id) {
                    InsectItemAddPersonalityMaybe_3d18f0(a, -2);
                } else if (cfg->h2a == id) {
                    InsectItemAddPersonalityMaybe_3d18f0(a, 1);
                } else {
                    InsectItemAddPersonalityMaybe_3d18f0(a, -1);
                }
            }
            if (!aDead) {
                a->Set148(e2->bF);
                a->Set150(e2->b2);
                a->Set178(e2->b3);
                a->Set184(e2->b4);
                j = 0;
                do {
                    a->Set190(j, e2->b5[j]);
                    j++;
                } while (j < 6);
                a->Set1bc(e2->hC, 0, 0);
            }
        }
    }
    InsectItemCheckBecomeAdult_3cf880(a, 0, 0, 0);
    InsectItemCheckBecomeAdult_3cf880(b, 0, 0, 0);
    a->Set16c(D_00465D80[0]);
    ItemConsume_3d41b0(key, 1, 0, 0);
    return 1;
}
