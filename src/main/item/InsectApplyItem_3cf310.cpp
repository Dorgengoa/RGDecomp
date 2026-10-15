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
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void v21();
    virtual void v22();
    virtual void v23();
    virtual void v24();
    virtual void v25();
    virtual void v26();
    virtual void v27();
    virtual void v28();
    virtual void v29();
    virtual void v30();
    virtual void v31();
    virtual void v32();
    virtual void v33();
    virtual void v34();
    virtual void v35();
    virtual void v36();
    virtual void v37();
    virtual void v38();
    virtual void v39();
    virtual void v40();
    virtual void v41();
    virtual void v42();
    virtual void v43();
    virtual void v44();
    virtual void v45();
    virtual void v46();
    virtual void v47();
    virtual void v48();
    virtual void v49();
    virtual void v50();
    virtual void v51();
    virtual void v52();
    virtual void v53();
    virtual void v54();
    virtual void v55();
    virtual void v56();
    virtual void v57();
    virtual void v58();
    virtual void v59();
    virtual void v60();
    virtual void v61();
    virtual void v62();
    virtual void v63();
    virtual void v64();
    virtual void v65();
    virtual void v66();
    virtual void v67();
    virtual void v68();
    virtual void v69();
    virtual void v70();
    virtual void v71();
    virtual void v72();
    virtual void v73();
    virtual void v74();
    virtual void v75();
    virtual void v76();
    virtual s32 GetHp();
    virtual void v78();
    virtual void v79();
    virtual void Set148(s32);
    virtual void v81();
    virtual void Set150(s32);
    virtual void v83();
    virtual void v84();
    virtual void v85();
    virtual void v86();
    virtual void v87();
    virtual void v88();
    virtual void Set16c(s32);
    virtual void v90();
    virtual void v91();
    virtual void Set178(s32);
    virtual void v93();
    virtual void v94();
    virtual void Set184(s32);
    virtual void v96();
    virtual void v97();
    virtual void Set190(s32, s32);
    virtual void v99();
    virtual void v100();
    virtual u8 Get19c();
    virtual void v102();
    virtual s32 Get1a4();
    virtual void v104();
    virtual void v105();
    virtual void v106();
    virtual void v107();
    virtual void v108();
    virtual void Set1bc(u16, s32, s32);

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
s32 InsectItemUsable_3cf910(void);
s32 ItemIsKindDId515_3d4570(Key *);
s32 ItemIsKindDId514_3d4530(Key *);
s32 ItemIsInsectFood_3d45b0(Key *);
s32 ItemGetInsectFoodId_3d45d0(Key *);
void InsectBreedRecReset_3d2730(Rec *);
void IterInit_370170(void *, void *);
void *IterNext_370040(void *);
s16 *ItemDefFindByKeys_40c6b0(s32, s32, s32, s32, s32);
void InsectRecPushBreedEntry_3cedf0(void *, Rec *);
s32 Rand_133710(void);
void InsectRollStatGain_3d11e0(Unit *, s32, s32);
u8 *ItemDefGetInsectData_40e0b0(Info *);
void InsectItemAddPersonalityMaybe_3d18f0(Unit *, s32);
void InsectItemCheckBecomeAdult_3cf880(Unit *);
void ItemConsume_3d41b0(Key *, s32, s32);
}
extern s32 D_00465D80[];
extern s32 D_004838E8;
extern Game *D_004838EC;

extern "C" s32 InsectApplyItem_3cf310(void *self, Key *key, Unit *a, Unit *b)
{
    Unit *pair[2];
    Unit **pp;
    Rec rec;
    Date dates[2];
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
    if (InsectItemUsable_3cf910() == 0) {
        return 0;
    }
    aDead = a->GetHp() <= 0;
    bDead = 0;
    if (b != 0) {
        bDead = b->GetHp() <= 0;
    }
    if (ItemIsKindDId515_3d4570(key) != 0) {
        InsectBreedRecReset_3d2730(&rec);
        rec.a = a->h4;
        rec.b = b->h4;
        rec.c = 2;
        rec.xC = 0;
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
        IterInit_370170(it, l);
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
            rec.val = e->val;
            break;
        }
        if (!found) {
            p = &dates[0];
            if (dates[0].d != dates[1].d && dates[0].d < dates[1].d) {
                p = &dates[1];
            }
            if (dates[0].c == 0x7DF || dates[1].c == 0x7DF) {
                rec.val = 0x424A;
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
                    rec.val = *r;
                }
            }
        }
        InsectRecPushBreedEntry_3cedf0(self, &rec);
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
        if (ItemIsInsectFood_3d45b0(key) == 0) {
            return 0;
        }
        l = D_004838EC->lists->l0c;
        if (l != 0) {
            l += 0x88;
        }
        IterInit_370170(it2, l);
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
    InsectItemCheckBecomeAdult_3cf880(a);
    InsectItemCheckBecomeAdult_3cf880(b);
    a->Set16c(D_00465D80[0]);
    ItemConsume_3d41b0(key, 1, 0);
    return 1;
}
