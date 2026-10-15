#include "types.h"

typedef struct Key { s16 key; u8 m2; u8 m3; } Key;
typedef struct Ent { s16 m0; s16 m2; s16 m4; u8 b0 : 1; u8 pad : 7; u8 pad7; } Ent;
typedef struct Slot { s16 a; s16 b; f32 f; } Slot;
typedef struct Obj {
    s16 n;
    Key keys[16];
    s16 m42;
    u8 m44;
    u8 pad45;
    Ent ents[64];
    Slot slots[16];
} Obj;
typedef struct Fl { u8 pad0[0x24C]; u8 b0 : 1; u8 b1 : 1; u8 b2 : 1; u8 b3 : 1; u8 b4 : 1; } Fl;
typedef struct Hdr { u8 pad0[0x2C]; s16 m2C; } Hdr;
class VT {
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
    virtual u8 *v70(s16);
};

typedef struct Mid { u8 pad0[0x14]; VT *m14; } Mid;
typedef struct Own { u8 pad0[0x48]; Mid *m48; } Own;
typedef struct G { u8 pad0[8]; Own *m8; Hdr *mC; u8 pad10[0x10]; Fl *m20; } G;

extern "C" {
void CharaEventLogCompact_3a65e0(Obj *);
void CharaEventLogEntryReset_3a6bf0(Ent *);
extern G *D_004837BC;

s32 CharaEventLogRecord_3a62f0(Obj *o, s32 key, s32 a, s32 b, s32 c)
{
    Own *own;
    Key *p;
    Ent *e;
    Ent *base;
    Slot *q;
    u8 *r;
    s32 idx;
    s32 i;
    s32 ok;

    if (a < 0 || c <= 0) return 0;
    if (o->m44 & 1) return 0;
    if (D_004837BC->m20->b4) return 1;
    own = D_004837BC->m8;
    if (D_004837BC->mC->m2C != 1) return 0;
    idx = -1;
    p = o->keys;
    for (i = 0; i < o->n; i++, p++) {
        if (p->key == key) {
            idx = i;
            break;
        }
    }
    if (idx < 0) return 0;
    if (b != -1 && b != -2) {
        for (i = 0; i < 16; i++) {
            q = &o->slots[i];
            if (q->a == a && q->b == b && !(q->f <= 0.0f)) return 1;
        }
    }
    if (b == 0x83) {
        if (p->m3 > 0) return 1;
        p->m3++;
    } else if (b == 1 || b == 0x84) {
        p->m3++;
    }
    p->m2++;
    if (o->m42 > 0) {
        for (e = &o->ents[o->m42 - 1]; e >= o->ents; e--) {
            if (!e->b0) break;
            o->m42--;
        }
    }
    if (o->m42 >= 0x40) CharaEventLogCompact_3a65e0(o);
    if (o->m42 >= 0x40) return 0;
    e = &o->ents[++o->m42 - 1];
    CharaEventLogEntryReset_3a6bf0(e);
    e->m0 = a;
    e->m2 = b;
    e->m4 = c;
    e->b0 = 0;
    ok = 0;
    r = own->m48->m14->v70((s16)b);
    if (r != 0) ok = r[2] & 1;
    if (ok == 0) goto done;
    for (i = 0; i < 16; i++) {
        q = &o->slots[i];
        if (q->a < 0) {
            q->a = a;
            q->b = b;
            q->f = 300.0f;
            break;
        }
    }
done:
    return 1;
}
}
