#include "types.h"

class Sink {
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual s32 Load(s32, s32);
};

typedef struct Mgr {
    u8 pad0[0xC];
    Sink *s1;
    Sink *s2;
    Sink *s3;
    Sink *s4;
    u8 pad1C[4];
    Sink *s5;
    Sink *s6;
} Mgr;

typedef struct Ent {
    u8 flags;
    u8 pad1[3];
    s32 len;
    s32 ptr;
} Ent;

typedef struct Hdr {
    s32 x0;
    s32 x4;
    Ent ent[6];
} Hdr;

typedef struct Buf {
    u8 pad0[0x340];
    s64 x340;
    u8 pad348[8];
} Buf;

extern "C" {
s32 UnpackWordTriple_370d70(s32, s32, s32 *, s32 *, s32 *);
u8 SlotRecordValidate_3e52b0(Mgr *, s32, s32, s32, s32);
void SaveDataSetError_3e6340(Mgr *, s32, s32, s32);
void SaveDataClearError_3e6350(void);
void SlotRecordReset_3eeca0(Buf *);
void *memcpy(void *, const void *, u32);
extern s32 D_004658F0[];
extern s32 D_004658F8[];
}

extern "C" s32 SaveDataDeserialize_3e5c30(Mgr *self, s32 data, s32 size, Hdr *out) {
    s32 a3;
    s32 b3;
    s32 c3;
    s32 a2;
    s32 b2;
    s32 c2;
    Buf buf;
    s32 found;
    s32 flen;
    s32 total;
    s32 p;
    s32 rem;
    s32 n;
    s32 k;
    Ent *ent;
    s32 i;
    Sink *obj;
    s32 kind;
    s32 hit;
    s32 hlen;
    s32 q;
    s32 left;

    if (data == 0 || size <= 0 || out == 0) {
        return 0;
    }
    SaveDataClearError_3e6350();
    total = 0;
    if (size < D_004658F0[0] || D_004658F8[0] < size) {
        SaveDataSetError_3e6340(self, 2, size, 0);
        return 0;
    }
    if (SlotRecordValidate_3e52b0(self, data, size, 1, 1) == 0) {
        return 0;
    }
    buf.x340 = 0;
    SlotRecordReset_3eeca0(&buf);
    memcpy(&buf, (void *)data, 0x350);
    found = 0;
    flen = 0;
    out->x0 = D_004658F0[0];
    rem = size - D_004658F0[0];
    out->x4 = data;
    total += D_004658F0[0];
    p = data + D_004658F0[0];
    while (((found != 0) ^ 1) != 0) {
        a3 = 0;
        b3 = 0;
        c3 = 0;
        n = UnpackWordTriple_370d70(p, rem, &a3, &b3, &c3);
        if (n <= 0) {
            break;
        }
        if (a3 == 0) {
            if (rem < n + c3) {
                SaveDataSetError_3e6340(self, 3, flen, 0);
                return 0;
            }
            flen = c3;
            found = p + n;
        }
        k = n + c3;
        total += k;
        p += k;
        rem -= k;
    }
    if (found == 0) {
        SaveDataSetError_3e6340(self, 4, 0, 0);
        return 0;
    }
    ent = out->ent;
    for (i = 1; i <= 6; i++, ent++) {
        q = found;
        obj = 0;
        kind = -1;
        left = flen;
        switch (i) {
        case 1:
            obj = self->s1;
            kind = 1;
            break;
        case 2:
            obj = self->s2;
            kind = 2;
            break;
        case 3:
            obj = self->s3;
            kind = 3;
            break;
        case 4:
            obj = self->s4;
            kind = 8;
            break;
        case 5:
            obj = self->s5;
            kind = 0xE;
            break;
        case 6:
            obj = self->s6;
            kind = 0xF;
            break;
        }
        if (obj == 0) {
            break;
        }
        hit = 0;
        hlen = 0;
        while (((hit != 0) ^ 1) != 0) {
            a2 = 0;
            b2 = 0;
            c2 = 0;
            n = UnpackWordTriple_370d70(q, left, &a2, &b2, &c2);
            if (n <= 0) {
                break;
            }
            if (a2 == kind) {
                if (left < n + c2) {
                    SaveDataSetError_3e6340(self, 5, kind, hlen);
                    return 0;
                }
                hlen = c2;
                hit = q + n;
            }
            k = n + c2;
            if (!(ent->flags & 1)) {
                total += k;
            }
            q += k;
            ent->ptr = hit;
            ent->len = hlen;
            left -= k;
        }
        if (hit == 0) {
            SaveDataSetError_3e6340(self, 6, kind, 0);
            return 0;
        }
        if (ent->flags & 1) {
            total += obj->Load(hit, hlen);
        }
    }
    return total;
}
