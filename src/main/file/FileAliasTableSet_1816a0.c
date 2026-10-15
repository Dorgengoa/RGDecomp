#include "types.h"

typedef struct {
    char *str;
    s32 len;
    char *next;
} Elem001816A0;

extern s32 memcmp(const void *, const void *, s32);
extern void *memcpy(void *, const void *, s32);
extern u8 D_0047E030;
extern u8 D_0047E031;
extern s32 D_00481214;
extern char D_0049B710[0x800];
extern Elem001816A0 D_0049BF10[0x20];

void FileAliasTableSet_1816a0(char *src, s32 size)
{
    u8 sep[2];
    s32 *lp;
    char *end;
    s32 i;
    s32 n;
    Elem001816A0 *e;

    if (src == NULL || size == 0) {
        s32 j;
        for (j = 0; j < 0x20; j++) {
            D_0049BF10[j].str = NULL;
        }
        D_00481214 = 0;
        return;
    }
    if (size < 0x801) {
        memcpy(D_0049B710, src, size);
        src = D_0049B710;
        i = 0;
        end = &D_0049B710[size];
        sep[0] = D_0047E030;
        sep[1] = D_0047E031;
        while ((u32)src < (u32)end) {
            e = &D_0049BF10[i];
            n = 0;
            e->str = src;
            lp = &e->len;
            *lp = 0;
            while ((u32)src < (u32)end) {
                if (*src == ';') {
                    e->len = n;
                    src++;
                    e->str[n] = 0;
                    n = 0;
                    e->next = src;
                }
                if (memcmp(src, &sep[0], 2) == 0) {
                    src += 2;
                    break;
                }
                if (memcmp(src, &sep[0], 1) == 0) {
                    src++;
                    break;
                }
                if (memcmp(src, &sep[1], 1) == 0) {
                    src++;
                    break;
                }
                if (*src == 0x5C) {
                    *src = 0x2F;
                }
                n++;
                src++;
            }
            if (*lp <= 0) {
                D_0049BF10[(u32)i].str = NULL;
                D_0049BF10[(u32)i].next = NULL;
            } else {
                i++;
                e->next[n] = 0;
                if (i >= 0x20) {
                    break;
                }
            }
        }
        D_00481214 = i;
    }
}
