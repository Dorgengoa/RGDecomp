#include "types.h"

extern s32 strncmp(const char *, const char *, u32);
extern char D_0045F828[];
extern char D_0045F830[];
extern char D_0045F838[];
extern char D_0045F840[];
extern char D_0045F848[];
extern char D_0045F850[];
extern char D_0045F858[];
extern char D_0045F860[];
extern char D_0045F868[];
extern char D_0045F870[];
extern char D_0045F878[];
extern char D_0045F880[];
extern char D_0045F888[];
extern char D_0045F890[];
extern char D_0045F898[];
extern char D_0045F8A0[];
extern char D_0045F8A8[];
extern char D_0045F8B0[];
extern char D_0045F8B8[];
extern char D_0045F8C0[];
extern char D_0045F8C8[];
extern char D_0045F8D0[];
extern char D_0045F8D8[];
extern char D_0045F8E0[];
extern char D_0045F8E8[];
extern char D_0045F8F0[];
extern char D_0045F8F8[];
extern char D_0045F900[];
extern char D_0045F908[];

s32 TextParseNumTag_275970(const char *s, s32 *out)
{
    s32 k;

    if (s == 0) {
        return 0;
    }
    k = 0;
    if (strncmp(s, D_0045F828, 2) == 0) {
        k = 1;
    } else if (strncmp(s, D_0045F830, 2) == 0) {
        k = 2;
    } else if (strncmp(s, D_0045F838, 2) == 0) {
        k = 3;
    } else if (strncmp(s, D_0045F840, 2) == 0) {
        k = 4;
    } else if (strncmp(s, D_0045F848, 2) == 0) {
        k = 5;
    } else if (strncmp(s, D_0045F850, 2) == 0) {
        k = 6;
    } else if (strncmp(s, D_0045F858, 2) == 0) {
        k = 7;
    } else if (strncmp(s, D_0045F860, 2) == 0) {
        k = 8;
    } else if (strncmp(s, D_0045F868, 2) == 0) {
        k = 9;
    } else if (strncmp(s, D_0045F870, 3) == 0) {
        k = 1;
    } else if (strncmp(s, D_0045F878, 3) == 0) {
        k = 2;
    } else if (strncmp(s, D_0045F880, 3) == 0) {
        k = 3;
    } else if (strncmp(s, D_0045F888, 3) == 0) {
        k = 4;
    } else if (strncmp(s, D_0045F890, 3) == 0) {
        k = 5;
    } else if (strncmp(s, D_0045F898, 3) == 0) {
        k = 6;
    } else if (strncmp(s, D_0045F8A0, 3) == 0) {
        k = 7;
    } else if (strncmp(s, D_0045F8A8, 3) == 0) {
        k = 8;
    } else if (strncmp(s, D_0045F8B0, 3) == 0) {
        k = 9;
    } else if (strncmp(s, D_0045F8B8, 3) == 0) {
        k = 10;
    } else if (strncmp(s, D_0045F8C0, 3) == 0) {
        k = 11;
    } else if (strncmp(s, D_0045F8C8, 3) == 0) {
        k = 12;
    } else if (strncmp(s, D_0045F8D0, 3) == 0) {
        k = 13;
    } else if (strncmp(s, D_0045F8D8, 3) == 0) {
        k = 14;
    } else if (strncmp(s, D_0045F8E0, 3) == 0) {
        k = 15;
    } else if (strncmp(s, D_0045F8E8, 3) == 0) {
        k = 16;
    } else if (strncmp(s, D_0045F8F0, 3) == 0) {
        k = 17;
    } else if (strncmp(s, D_0045F8F8, 3) == 0) {
        k = 18;
    } else if (strncmp(s, D_0045F900, 3) == 0) {
        k = 19;
    } else if (strncmp(s, D_0045F908, 3) == 0) {
        k = 20;
    }
    if (k != 0) {
        *out = k;
        return 1;
    }
    return 0;
}
