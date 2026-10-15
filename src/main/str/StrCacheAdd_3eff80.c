#include "types.h"

typedef struct {
    s16 unk0;
    s16 unk2;
    s32 unk4;
    char *str;
} Rec;

typedef struct {
    u8 pad0[0x2C];
    s32 heap;
    Rec *tbl;
} S1;

extern void MemStackHeapFree_14dcb0(s32, char *);
extern char *MemStackHeapAllocFront_14dd10(s32, u32);
extern void StrCacheEntryReset_3f4040(Rec *);
extern void *memcpy(void *, const void *, s32);
extern char *strcpy(char *, const char *);
extern s32 strlen(const char *);
extern s32 D_004644F0[];

char *StrCacheAdd_3eff80(S1 *obj, s16 a, s32 b, s32 c, char *s)
{
    s32 n;
    s32 idx;
    s32 i;
    u32 len;
    u32 rem;
    u32 w1;
    char *p;
    char *result;
    Rec *r;

    if (obj->heap == 0 || obj->tbl == NULL || s == NULL) {
        return NULL;
    }
    idx = -1;
    n = D_004644F0[0];
    for (i = 0; i < n; i++) {
        if (obj->tbl[i].str == NULL) {
            idx = i;
            break;
        }
    }
    if (idx < 0) {
        MemStackHeapFree_14dcb0(obj->heap, obj->tbl[0].str);
        for (i = 1; i < n; i++) {
            {
                Rec *q = &obj->tbl[i];
                memcpy(q - 1, q, 0xC);
            }
        }
        idx = n - 1;
        StrCacheEntryReset_3f4040(&obj->tbl[idx]);
    }
    result = NULL;
    len = strlen(s) + 1;
    rem = len & 0xF;
    n = len >> 4;
    w1 = n + 1;
    while (idx >= 0) {
        p = MemStackHeapAllocFront_14dd10(obj->heap, rem ? w1 : n);
        if (p != NULL) {
            strcpy(p, s);
            result = p;
            r = &obj->tbl[idx];
            r->unk0 = a;
            r->unk4 = b;
            r->unk2 = c;
            r->str = p;
            break;
        }
        MemStackHeapFree_14dcb0(obj->heap, obj->tbl[0].str);
        {
            s32 j;
            for (j = 1; j < idx; j++) {
                Rec *q = &obj->tbl[j];
                memcpy(q - 1, q, 0xC);
            }
        }
        idx--;
        StrCacheEntryReset_3f4040(&obj->tbl[idx]);
    }
    return result;
}
