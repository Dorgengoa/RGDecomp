#include "types.h"

typedef struct Ent {
    s32 m0;
    char *m4;
    struct Ent *m8;
} Ent;

extern char D_004610B8[];
extern char D_004610C0[];
extern char D_004610C8[];

void MemStackAlign64_14d8e0(s32);
u32 strlen(const char *);
char *MemStackPeekQw_14d9d0(s32, s32);
void MemStackAllocQw_14d950(s32, s32);
s32 Sprintf_1343b8(char *, const char *, ...);
char *strcat(char *, const char *);
char *strcpy(char *, const char *);
s32 atoi(const char *);
Ent *MemStackAllocAligned64_14da10(s32, s32);

char *MsgTableParseText_28aab0(s32 ctx, char *p, s32 len)
{
    char c4BC[2];
    char c4B8[2];
    char c4B4[2];
    char c4B0[3];
    char s490[0x20];
    char s470[0x20];
    char s80[0x3F0];
    char *z;
    u32 n;
    s32 cnt;
    char *r;
    char *end;
    Ent *prev;
    Ent *e;
    s32 base;
    s32 c;

    if (ctx == 0 || p == 0) {
        return 0;
    }
    MemStackAlign64_14d8e0(ctx);
    cnt = (strlen(D_004610B8) >> 4) + 1;
    if ((r = MemStackPeekQw_14d9d0(ctx, cnt)) == 0) {
        return 0;
    }
    MemStackAllocQw_14d950(ctx, cnt);
    Sprintf_1343b8(r, D_004610B8);
    end = p + len;
    prev = 0;
    base = 0;
    while (p < end) {
        if (*p == '@') {
        if (p[1] == 'I') {
            s490[0] = 0;
            p += 8;
            while ((c = *p) >= '0' && c <= '9') {
                z = c4BC; n = 2; if (z != 0) { do { *z = 0; n--; z++; } while (n != 0); }
                c4BC[0] = *p;
                strcat(s490, c4BC);
                p++;
            }
            base = atoi(s490);
        } else {
            e = MemStackAllocAligned64_14da10(ctx, 1);
            e->m0 = 0;
            e->m4 = 0;
            e->m8 = 0;
            if (prev != 0) {
                prev->m8 = e;
            }
            p++;
            strcpy(s470, D_004610C0);
            while ((c = *p) >= '0' && c <= '9') {
                z = c4B8; n = 2; if (z != 0) { do { *z = 0; n--; z++; } while (n != 0); }
                c4B8[0] = *p;
                strcat(s470, c4B8);
                p++;
            }
            e->m0 = base + atoi(s470);
            strcpy(s80, D_004610C0);
            while (*p != '\n') {
                p++;
            }
            p++;
            for (; p < end; p++) {
                c = *p;
                if (!(c & 0x80) && c == '\r') {
                    p++;
                }
                c = *p;
                if (c == '/' && p[1] == '/') {
                    while (*p != '\n') {
                        p++;
                    }
                    continue;
                }
                if (!(c & 0x80) || (c >= 0xA0 && c < 0xE0)) {
                    if (c == '\n' && p[1] == '@') {
                        break;
                    }
                    z = c4B4; n = 2; if (z != 0) { do { *z = 0; n--; z++; } while (n != 0); }
                    c4B4[0] = *p;
                    strcat(s80, c4B4);
                } else {
                    z = c4B0; n = 3; if (z != 0) { do { *z = 0; n--; z++; } while (n != 0); }
                    c4B0[0] = p[0];
                    c4B0[1] = p[1];
                    strcat(s80, c4B0);
                    p++;
                }
            }
            MemStackAlign64_14d8e0(ctx);
            e->m4 = MemStackPeekQw_14d9d0(ctx, (strlen(s80) >> 4) + 1);
            if (e->m4 != 0) {
                MemStackAllocQw_14d950(ctx, (strlen(s80) >> 4) + 1);
                Sprintf_1343b8(e->m4, D_004610C8, s80);
            }
            prev = e;
        }
        } else {
            p++;
        }
    }
    return r;
}
