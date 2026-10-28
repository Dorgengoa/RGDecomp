/* rgp:protos */
#define RGP_SELF_NameTableRegisterImArchive_1594d0 1
#include "port/game_protos.h"
#line 1
#pragma opt_propagation off
#include "types.h"

typedef struct Node Node;
struct Node {
    s16 h0;
    u8 pad2[0x46];
    s64 d48;
    u8 pad50[0x14];
    Node *next;
};

typedef struct {
    u8 pad0[8];
    Node *head;
    u8 padC[4];
} Slot;

typedef struct {
    u8 pad0[0xC];
    s32 wC;
    u8 pad10[0xC];
    Slot *slots;
    u8 pad20[0x1A8];
    Node **pool;
    u8 pad1CC[4];
    s32 npool;
} Self;

typedef struct {
    u8 b0;
    u8 pad1[0x1F];
    s32 w20;
    s32 w24;
    s32 w28;
    s32 w2C;
    s16 h30;
    u8 pad32[2];
    s32 w34;
    s64 d38;
} Entry;

typedef struct {
    u8 pad0[0x20];
    s32 w20;
    u8 pad24[0xC];
} E30;

typedef struct {
    u8 pad0[4];
    u32 n4;
    u32 n8;
    u8 padC[4];
    Entry e[1];
} Hdr;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern s32 memcmp(const void *, const void *, u32);
extern u8 D_00458B18[];
extern u8 D_00458B20[];
extern u8 D_00458B30[];

s32 NameTableRegisterImArchive_1594d0(Self *self, Hdr *hdr, s32 base, s32 flag, s32 *map) {
    s32 maxv;
    s32 isX;
    Node *r;
    Node *p;
    s32 i;
    s32 grp;
    Slot *sl;
    Node *prev;
    s32 isHash;
    s32 cur;
    s32 alt;
    s32 cnt;
    s32 last;
    u8 *data;
    u32 n;
    s32 h;
    Entry *e;
    E30 *e1;
    u32 k;
    s32 idx;

    if (hdr != 0) goto body;
    return 0;
body:
    isX = 0;
    if (memcmp(hdr, D_00458B20, 2) != 0) {
        return 0;
    }
    if (memcmp(hdr, D_00458B30, 3) == 0) {
        isX = 1;
    }
    alt = 0;
    if (memcmp(hdr, D_00458B18, 3) == 0) {
        alt = 1;
    }
    if (map != 0) {
        i = 0;
        do {
            map[i] = -1;
            map[i + 32] = 0;
            i++;
        } while (i < 32);
    }
    cur = base;
    cnt = 0;
    maxv = cur;
    if (alt == 0) {
        e1 = (E30 *)((u8 *)hdr + 0x10);
        for (k = 0; k < hdr->n4; k++) {
            r = ((Node *)Tim2RegisterPicture_159940(self, cur, e1, (u8 *)hdr + e1->w20, (long long)(isX), 0));
            if (r != 0 && cur < self->wC - 1 && TexGroupCalcFreeVram_159e90(self, cur) < 0) {
                cur++;
                cnt++;
                r->h0 = cur;
            }
            if (r != 0) {
                if (maxv < r->h0) {
                    maxv = r->h0;
                }
            }
            e1++;
        }
        if (map != 0) {
            map[0] = base;
            map[32] = cnt + 1;
        }
    } else {
        Im3SortByPriority_158e20(hdr);
        e = (Entry *)((u8 *)hdr + 0x10);
        grp = 0;
        n = 0;
        last = *(s32 *)((u8 *)hdr + 0x3C);
        for (; n < hdr->n8; n++, e++) {
            data = (u8 *)hdr + e->w24;
            isHash = e->b0 == 0x23;
            if (isHash) {
                if (base >= 0 && flag != 0) {
                    TexAnimeCfgParse_162780(self, data, ((volatile Entry *)e)->w34, flag, 0);
                }
                continue;
            }
            if (last != e->w2C) {
                last = e->w2C;
                grp++;
            }
            idx = cnt + (cur + grp);
            if (map != 0) {
                if (map[e->w2C] < 0) {
                    map[e->w2C] = idx;
                    map[e->w2C + 32] = 1;
                }
            }
            r = ((Node *)Tim2RegisterPicture_159940(self, idx, e, data, (long long)(e->w28), e->h30));
            if (r != 0) {
                r->d48 = e->d38;
            }
            if (r != 0 && idx < self->wC - 1 && TexGroupCalcFreeVram_159e90(self, idx) < 0) {
                if (map != 0) {
                    if (map[e->w2C] >= 0) {
                        map[e->w2C + 32]++;
                    }
                }
                cnt++;
                sl = &self->slots[r->h0];
                prev = 0;
                for (p = sl->head; p != 0; p = p->next) {
                    if (p == r) {
                        if (prev == 0) {
                            sl->head = p->next;
                        } else {
                            prev->next = p->next;
                        }
                    }
                    prev = p;
                }
                h = (s16)(r->h0 + 1);
                r->h0 = r->h0 + 1;
                if (h < self->wC) {
                    sl = &self->slots[h];
                    r->next = 0;
                    if (sl->head == 0) {
                        sl->head = r;
                    } else {
                        p = sl->head;
                        for (; p != 0; p = p->next) {
                            if (p->next == 0) {
                                p->next = r;
                                break;
                            }
                        }
                    }
                } else {
                    if (self->npool > 0) {
                        self->npool--;
                        self->pool[self->npool] = r;
                    }
                    r = 0;
                }
            }
            if (r != 0) {
                if (maxv < r->h0) {
                    maxv = r->h0;
                }
            }
        }
    }
    return maxv - cur;
}
