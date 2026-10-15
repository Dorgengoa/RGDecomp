#include "types.h"

extern "C" {

typedef struct {
    s8 *key;
    s8 len;
    s8 *val;
} Tok;

typedef struct { Tok e[4]; } Tbl1;
typedef struct { Tok e[13]; } Tbl2;

typedef struct {
    s32 w0;
    s32 w4;
    s32 w8;
    struct { s16 id; s16 pad; } c[2];
    s32 w14[2];
    s32 w1C;
    s32 w20;
    s32 w24;
    s32 w28;
    s8 s2C[0x40];
    s8 s6C[0x40];
} Info;

typedef struct {
    u8 pad0[0xC];
    s8 *pC;
    s8 *p10;
} Rec;

class VA {
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
    virtual Rec *v70(s32);
};

class VB {
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
    virtual s8 *v4C(s8 *);
};

typedef struct {
    u8 pad0[8];
    VA *va;
} H40;

typedef struct {
    u8 pad0[0x40];
    H40 *p40;
} H;

typedef struct {
    u8 pad0[0x18];
    s32 w18;
} G;

G *GetGameData_1fede0(void);
H *GetWorldDataMgr_1fedf0(void);
void MsgIntToDigitText_28a660(s8 *, s8 *, u8);
VB *InvFindByUniqueId_3c85d0(s32, s32, s32, s32);
void *memset(void *, s32, u32);
s8 *strcpy(s8 *, const s8 *);
s32 strlen(const s8 *);
s32 strncmp(const s8 *, const s8 *, u32);
extern Tbl1 D_0044F8E0;
extern Tbl2 D_0044F910;

static inline void Copy(s8 *d, s8 *s) {
    if (s != 0) {
        strcpy(d, s);
    }
}

void MsgExpandTokens_28a250(s8 *out, s8 *fmt, Info *info, u8 flag) {
    Tbl1 t1;
    s8 nameA[2][0x60];
    s8 nameB[2][0x60];
    s8 name3[2][0x40];
    s8 buf990[0x40];
    Tbl2 t2;
    s8 src[0x400];
    s8 dst[0x400];
    s8 tmp[0x40];
    G *g;
    H *h;
    s32 i;
    s32 i2;
    s8 *a;
    s8 *b;
    Rec *r;
    s8 *c;
    VB *vb;
    s8 *str;
    s8 *s;
    s8 *d;
    s32 found;
    Tok *e;
    s8 *p;
    s32 n;
    s32 k;

    if (out == 0 || fmt == 0) {
        return;
    }
    {
        u32 *sp = (u32 *)&D_0044F8E0;
        u32 *dp = (u32 *)&t1;
        s32 n8 = 6;
        do {
            u32 w0 = sp[0];
            n8--;
            dp[0] = w0;
            dp[1] = sp[1];
            sp += 2;
            dp += 2;
        } while (n8 > 0);
    }
    t1.e[0].val = (s8 *)info->w0;
    t1.e[1].val = (s8 *)info->w4;
    t1.e[2].val = (s8 *)info->w8;
    g = GetGameData_1fede0();
    h = GetWorldDataMgr_1fedf0();
    for (i = 0; i < 2; i++) {
        a = nameA[i];
        b = nameB[i];
        a[0] = 0;
        b[0] = 0;
        if (h != 0) {
            r = h->p40->va->v70(info->c[i].id);
            if (r == 0) {
                continue;
            }
            if (r->pC != 0) {
                Copy(a, r->pC);
                Copy(b, r->p10);
            }
        }
    }
    for (i2 = 0; i2 < 2; i2++) {
        c = name3[i2];
        c[0] = 0;
        if (g != 0) {
            vb = InvFindByUniqueId_3c85d0(g->w18, info->w14[i2], -1, 0);
            if (vb == 0) {
                continue;
            }
            str = vb->v4C(buf990);
            if (str != 0) {
                strcpy(c, str);
            }
        }
    }
    {
        u32 *sp = (u32 *)&D_0044F910;
        u32 *dp = (u32 *)&t2;
        s32 n4 = 0x27;
        do {
            n4--;
            *dp = *sp;
            sp++;
            dp++;
        } while (n4 > 0);
    }
    t2.e[0].val = nameA[0];
    t2.e[1].val = nameA[1];
    t2.e[2].val = nameB[0];
    t2.e[3].val = nameB[1];
    t2.e[4].val = name3[0];
    t2.e[5].val = name3[1];
    t2.e[6].val = (s8 *)info->w1C;
    t2.e[7].val = (s8 *)info->w20;
    t2.e[8].val = (s8 *)info->w24;
    t2.e[9].val = (s8 *)info->w28;
    t2.e[10].val = info->s2C;
    t2.e[11].val = info->s6C;
    strcpy(src, fmt);
    memset(dst, 0, 0x400);
    s = src;
    d = dst;
    while (*s != 0) {
        found = 0;
        for (e = t1.e; e->key != 0; e++) {
            if (s[0] == e->key[0] && s[1] == e->key[1] && strncmp(s, *(s8 **)((u8 *)e + 0), e->len) == 0) {
                found = 1;
                MsgIntToDigitText_28a660(tmp, e->val, flag);
                p = tmp;
                n = strlen(p);
                for (k = 0; k < n; k++) {
                    *d++ = *p++;
                }
                s += e->len;
                break;
            }
        }
        if (found == 0) {
            for (e = t2.e; e->key != 0; e++) {
                if (s[0] == e->key[0] && s[1] == e->key[1] && strncmp(s, *(s8 **)((u8 *)e + 0), e->len) == 0) {
                    p = e->val;
                    found = 1;
                    if (p != 0) {
                        n = strlen(p);
                        for (k = 0; k < n; k++) {
                            *d++ = *p++;
                        }
                    }
                    s += e->len;
                    break;
                }
            }
        }
        if (found <= 0) {
            *d++ = *s++;
        }
    }
    strcpy(out, dst);
}

}
