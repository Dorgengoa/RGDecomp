#pragma opt_propagation off
#pragma opt_loop_invariants off
#include "types.h"

extern "C" {

struct Vec4 { f32 x, y, z, w; };

struct Scene {
    u8 pad0[4];
    s16 h4;
    u8 pad6[4];
    s16 hA;
    s16 hC;
    u8 padE[2];
    s32 w10;
    u8 pad14[0x1C];
    s16 h30;
    s16 h32;
    u8 pad34[0x4CA0 - 0x34];
    s16 h4CA0;
};

struct Self {
    u8 pad0[0x18];
    Scene *scene;
};

struct Out {
    u8 pad0[0xD];
    s8 bD;
    s8 bE;
    s8 bF;
    s8 b10[6];
    s8 b16;
    s8 b17;
    u8 b18;
    u8 pad19;
    s16 h1A;
    s16 h1C;
    s16 h1E;
    u8 f0 : 1;
    u8 f1 : 1;
    u8 b21;
    u8 b22;
    u8 b23;
    s8 *w24;
};

class Ent {
public:
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual void d5();
    virtual void d6();
    virtual void d7();
    virtual void d8();
    virtual void d9();
    virtual void d10();
    virtual void d11();
    virtual void d12();
    virtual void d13();
    virtual void d14();
    virtual void d15();
    virtual void d16();
    virtual void d17();
    virtual void d18();
    virtual void d19();
    virtual void d20();
    virtual void d21();
    virtual void d22();
    virtual void d23();
    virtual void d24();
    virtual void d25();
    virtual void d26();
    virtual void d27();
    virtual void d28();
    virtual void d29();
    virtual void d30();
    virtual void d31();
    virtual void d32();
    virtual void d33();
    virtual void d34();
    virtual void d35();
    virtual void d36();
    virtual void d37();
    virtual void d38();
    virtual void d39();
    virtual void d40();
    virtual void d41();
    virtual void d42();
    virtual void d43();
    virtual void d44();
    virtual void d45();
    virtual void d46();
    virtual void d47();
    virtual void d48();
    virtual void d49();
    virtual void d50();
    virtual void d51();
    virtual void d52();
    virtual void d53();
    virtual void d54();
    virtual void d55();
    virtual void d56();
    virtual void d57();
    virtual void d58();
    virtual void d59();
    virtual void d60();
    virtual void d61();
    virtual void d62();
    virtual void d63();
    virtual void d64();
    virtual void d65();
    virtual void d66();
    virtual void d67();
    virtual s32 v118(struct Out *);
    virtual s8 v11C();
    virtual void d70();
    virtual void d71();
    virtual s8 v128();
    virtual void d73();
    virtual void d74();
    virtual void d75();
    virtual void d76();
    virtual void d77();
    virtual void d78();
    virtual void d79();
    virtual void d80();
    virtual void d81();
    virtual void d82();
    virtual s16 v154();
    virtual void d84();
    virtual void d85();
    virtual void d86();
    virtual void d87();
    virtual void d88();
    virtual void d89();
    virtual s16 v170();
    virtual void d91();
    virtual void d92();
    virtual s16 v17C();
    virtual void d94();
    virtual void d95();
    virtual s8 v188(s32);
    virtual void d97();
    virtual void d98();
    virtual void d99();
    virtual void d100();
    virtual s32 v19C();
    virtual s32 v1A0();
    virtual u8 v1A4();
    virtual void d104();
    virtual s32 v1AC();
    virtual void d106();
    virtual s32 v1B4();
    u8 pad4[0xC];
    s8 *p10;
};

struct Elem {
    u8 f0 : 1;
    u8 pad[11];
};

struct Tmp {
    u8 hdr[8];
    Elem arr[6];
};

s32 PartyAddMember_3c1430(Scene *, s32, s32);
s32 PartyMembersReset_3c31b0(Scene *);
void *InvGetCageItem_3c8040(Scene *, s32);
s32 PartySetLocationMaybe_3c9cd0(Scene *, s32, s32, s32, s32, s32, Vec4 *, f32 *, s32, s32, s32);
s32 PartySetAreaMaybe_3cab50(Scene *, s32, s32, s32);
f32 PartyGetSavedMemberRot_3caf70(Scene *, s32);
s32 PartyGetSavedMemberPos_3cafa0(Scene *, s32, Vec4 *);
Ent *InsectRecSlotGetItem_3cfb30(void *, s32);
s32 InsectRecSlotCountItems_3cfb80(void *);
s32 SaveDataDeserialize_3e5c30(Self *, s32, s32, Tmp *, s32, s32);
s32 ReqListResetWithFlagMaybe_3ee640(Tmp *, s32);
s32 ReqListResetMaybe_3ee6b0(Tmp *);
s32 ReqEntryInit_3ee700(Elem *);
extern const s32 D_00465D80[];

s32 SaveFileReadInsectList_3e45c0(Self *self, Out *out, s32 *count, s32 a3, s32 a4) {
    f32 fv[3];
    Vec4 vec[3];
    Tmp tmp;
    Scene *sc;
    s32 h4;
    s32 hA;
    s32 hC;
    s32 w10;
    s32 h30;
    s32 h32;
    s32 i;
    Elem *el;
    s32 big;
    s32 r;
    s32 d;
    s32 j;
    void *grp;
    void *g2;
    s32 n;
    s32 k;
    Ent *e;
    s32 m;
    u8 one;

    if (out == 0) {
        goto fail;
    }
    if (a3 == 0) {
        goto fail;
    }
    if (a4 <= 0) {
    fail:
        return 0;
    }
    {
        {
            sc = self->scene;
            i = 0;
            hA = sc->hA;
            h4 = sc->h4;
            hC = sc->hC;
            w10 = sc->w10;
            h30 = sc->h30;
            h32 = sc->h32;
            do {
                PartyGetSavedMemberPos_3cafa0(self->scene, i, &vec[i]);
                fv[i] = PartyGetSavedMemberRot_3caf70(self->scene, i);
                i++;
            } while (i < 3);
            el = tmp.arr;
            big = self->scene->h4CA0;
            do {
                ReqEntryInit_3ee700(el);
                el++;
            } while ((u32)el < (u32)&tmp.arr[6]);
            ReqListResetMaybe_3ee6b0(&tmp);
            ReqListResetWithFlagMaybe_3ee640(&tmp, 0);
            one = 1;
            *(u8 *)&tmp.arr[3] = (*(u8 *)&tmp.arr[3] & -2) | one;
            *(u8 *)&tmp.arr[5] = (*(u8 *)&tmp.arr[5] & -2) | one;
            r = SaveDataDeserialize_3e5c30(self, a3, a4, &tmp, -2, one);
            if (r <= 0) {
                return 0;
            }
            {
                PartyMembersReset_3c31b0(self->scene);
                PartyAddMember_3c1430(self->scene, 0, 0);
                PartySetAreaMaybe_3cab50(self->scene, h4, 1, 1);
                PartySetLocationMaybe_3c9cd0(self->scene, hA, hC, w10, h30, h32, vec, fv, 0, big, 1);
                *count = 0;
                d = D_00465D80[0];
                j = 0;
                do {
                    g2 = InvGetCageItem_3c8040(self->scene, j);
                    grp = g2;
                    if (g2 != 0) {
                        n = InsectRecSlotCountItems_3cfb80(g2);
                        for (k = 0; k < n; k++) {
                            e = InsectRecSlotGetItem_3cfb30(grp, k);
                            if (e == 0) {
                                continue;
                            }
                            e->v118(out);
                            out->bD = e->v11C();
                            out->bE = e->p10[3];
                            out->bF = e->v128();
                            m = 0;
                            do {
                                *(s8 *)((u8 *)out + m + 0x10) = e->v188(m);
                                m++;
                            } while (m < 6);
                            out->b16 = 2;
                            out->b17 = d;
                            out->b18 = e->v1A4();
                            out->h1A = e->v154();
                            out->h1C = e->v170();
                            out->h1E = e->v17C();
                            out->f0 = e->v19C();
                            out->f1 = e->v1A0();
                            out->b21 = 0;
                            out->b22 = 0;
                            out->b23 = j + 1;
                            out->w24 = e->p10;
                            if (out->b18 == 5) {
                                if (e->v1B4() >= e->v1AC()) {
                                    out->b18++;
                                }
                            }
                            out++;
                            (*count)++;
                        }
                    }
                    j++;
                } while (j < 3);
                return r;
            }
            return 0;
        }
    }
    return 0;
}

}
