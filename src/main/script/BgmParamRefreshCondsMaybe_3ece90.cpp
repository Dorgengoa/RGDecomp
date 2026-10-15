#include "types.h"
#undef NULL
#define NULL 0

typedef struct { u8 d[0x38]; } E3ec;
typedef struct { s32 a; s32 b; E3ec e[64]; s32 pad[2]; } S3ec;
typedef struct { s32 a; s32 b; } It3ec;

extern "C" {
s32 VariantIsZero_36ed10(s32);
void VariantInit_36ff00(void *);
u8 *IterNext_370040(It3ec *);
void IterInit_370170(It3ec *, u8 *);
s32 ScriptExecOpStream_3dffa0(S3ec *, s16, s32, s32);
void VariantPoolReset_3e01f0(S3ec *);
}

static inline u8 *getObj(u8 *b, s32 k)
{
    if (k < 0) {
        return NULL;
    }
    if (k < 2) {
        return *(u8 **)(b + 0x50) + k * 0x2F8;
    }
    return NULL;
}

static inline u8 *getObj2(u8 *p, s32 k)
{
    u8 *b = *(u8 **)(p + 0x34);
    if (k >= 0) {
        if (k >= 2) {
            return NULL;
        }
        return *(u8 **)(b + 0x50) + k * 0x2F8;
    }
    return NULL;
}

static inline u8 *getObj3(u8 *b, s32 k)
{
    if (k >= 0 && k < 2) {
        return *(u8 **)(b + 0x50) + k * 0x2F8;
    }
    return NULL;
}

extern "C" s32 BgmParamRefreshCondsMaybe_3ece90(u8 *arg0, s32 arg1)
{
    It3ec it;
    S3ec s2;
    S3ec s1;

    s32 i;
    u8 *p;
    u8 *ent;
    u8 *obj;
    u8 *e;
    E3ec *pe;
    s32 r;
    s16 k;
    u8 *q;

    if (*(u8 **)(arg0 + 8) == NULL) {
        return 0;
    }
    for (i = 0; i < 2; i++) {
        p = *(u8 **)(arg0 + 8);
        ent = *(u8 **)(p + 0xC) + i * 0x1C;
        if (ent == NULL) {
            continue;
        }
        if (*(s16 **)ent == NULL) {
            continue;
        }
        if (arg1 >= 0 && **(s16 **)ent != arg1) {
            continue;
        }
        obj = getObj2(p, *(s16 *)(ent + 8));
        if (obj == NULL) {
            continue;
        }
        if (obj != NULL) {
            obj += 0x88;
        }
        IterInit_370170(&it, obj);
        while (e = IterNext_370040(&it), e != NULL) {
            *(s32 *)(e + 0x18) = 0;
            if (*(s16 *)(e + 4) > 0 && *(s32 *)(e + 8) != 0) {
                pe = s2.e;
                do {
                    VariantInit_36ff00(pe);
                    pe++;
                } while (pe < &s2.e[64]);
                VariantPoolReset_3e01f0(&s2);
                r = ScriptExecOpStream_3dffa0(&s2, *(s16 *)(e + 4), *(s32 *)(e + 8), 0);
                if (r == 0 || VariantIsZero_36ed10(r) != 0) {
                    continue;
                }
            }
            if (*(s16 *)(e + 0xC) > 0 && *(s32 *)(e + 0x10) != 0) {
                pe = s1.e;
                do {
                    VariantInit_36ff00(pe);
                    pe++;
                } while (pe < &s1.e[64]);
                VariantPoolReset_3e01f0(&s1);
                r = ScriptExecOpStream_3dffa0(&s1, *(s16 *)(e + 0xC), *(s32 *)(e + 0x10), 0);
                if (r == 0 || VariantIsZero_36ed10(r) != 0) {
                    continue;
                }
            }
            *(s32 *)(e + 0x18) = 2;
        }
    }
    return 1;
}
