/* rgp:protos */
#define RGP_SELF_DataTableCmdSubEntryDefine_422b60 1
#include "port/game_protos.h"
#line 1
#pragma opt_propagation off
#include "types.h"

typedef struct {
    s16 a;
    s16 b;
    s32 c;
    s32 d;
    s8 e;
    s8 f;
    u8 padE[2];
} Ent16;

typedef struct {
    u8 pad0[0x14];
    s32 cnt;
    Ent16 *ents;
    u8 pad1C[4];
} Sub32;

typedef struct {
    u8 pad0[0x14];
    s32 cnt;
    Sub32 *subs;
    u8 pad1C[4];
} Top32;

typedef struct {
    u8 pad0[0x7C];
    s16 n;
    u8 pad7E[0x8C - 0x7E];
    Top32 *tops;
    u8 pad90[0xBC - 0x90];
    s32 j;
    s32 k;
    u8 padC4[0xCC - 0xC4];
    s32 m;
} Mgr;

/*rgp*/
/*rgp*/
/*rgp*/
extern Mgr *D_004830F8;
extern s16 D_004830FC;

s32 DataTableCmdSubEntryDefine_422b60(s64 *arg0)
{
    Mgr *g;
    s32 idx;
    Top32 *t;
    Sub32 *s;
    Ent16 *e;
    s32 v;
    s32 m;
    s8 *str;
    s32 c;
    s32 d;

    g = D_004830F8;
    if (g->n <= 0) {
        return 1;
    }
    idx = D_004830FC - 1;
    if (idx >= g->n) {
        return 1;
    }
    t = &g->tops[idx];
    if (t->subs == NULL) {
        return 1;
    }
    if (t->cnt <= 0) {
        return 1;
    }
    if (g->j - 1 >= t->cnt) {
        return 1;
    }
    s = t->subs + g->j - 1;
    if (s->ents == NULL) {
        return 1;
    }
    if (s->cnt <= 0) {
        return 1;
    }
    if (g->k >= s->cnt) {
        return 1;
    }
    e = &s->ents[g->k];
    v = VariantGetInt_15f780((s32)arg0++);
    m = g->m;
    str = ((s8 *)SlotGetInt_15f720((s32)arg0++));
    c = VariantGetInt_15f780((s32)arg0++);
    d = VariantGetInt_15f780((s32)arg0++);
    if (m < 0 || m >= 0x30) {
        return 1;
    }
    if (str == NULL) {
        return 1;
    }
    if (*str == 0) {
        return 1;
    }
    e->a = v;
    e->b = m;
    e->c = DataTableStoreString_368ab0(g, str);
    e->e = c;
    e->f = d;
    e->d = 0;
    g->k++;
    g->m++;
    return 1;
}
