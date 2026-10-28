/* rgp:protos */
#define RGP_SELF_TextParseWideNumTag_2756a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern s32 strncmp(const char *, const char *, u32);
extern char D_0045F788[];
extern char D_0045F790[];
extern char D_0045F798[];
extern char D_0045F7A0[];
extern char D_0045F7A8[];
extern char D_0045F7B0[];
extern char D_0045F7B8[];
extern char D_0045F7C0[];
extern char D_0045F7C8[];
extern char D_0045F7D0[];
extern char D_0045F7D8[];
extern char D_0045F7E0[];
extern char D_0045F7E8[];
extern char D_0045F7F0[];
extern char D_0045F7F8[];
extern char D_0045F800[];
extern char D_0045F808[];
extern char D_0045F810[];
extern char D_0045F818[];
extern char D_0045F820[];

s32 TextParseWideNumTag_2756a0(const char *s, s32 *out)
{
    s32 k;

    if (s == 0) {
        return 0;
    }
    k = 0;
    if (strncmp(s, D_0045F788, 3) == 0) {
        k = 1;
    } else if (strncmp(s, D_0045F790, 3) == 0) {
        k = 2;
    } else if (strncmp(s, D_0045F798, 3) == 0) {
        k = 3;
    } else if (strncmp(s, D_0045F7A0, 3) == 0) {
        k = 4;
    } else if (strncmp(s, D_0045F7A8, 3) == 0) {
        k = 5;
    } else if (strncmp(s, D_0045F7B0, 3) == 0) {
        k = 6;
    } else if (strncmp(s, D_0045F7B8, 3) == 0) {
        k = 7;
    } else if (strncmp(s, D_0045F7C0, 3) == 0) {
        k = 8;
    } else if (strncmp(s, D_0045F7C8, 3) == 0) {
        k = 9;
    } else if (strncmp(s, D_0045F7D0, 5) == 0) {
        k = 10;
    } else if (strncmp(s, D_0045F7D8, 5) == 0) {
        k = 11;
    } else if (strncmp(s, D_0045F7E0, 5) == 0) {
        k = 12;
    } else if (strncmp(s, D_0045F7E8, 5) == 0) {
        k = 13;
    } else if (strncmp(s, D_0045F7F0, 5) == 0) {
        k = 14;
    } else if (strncmp(s, D_0045F7F8, 5) == 0) {
        k = 15;
    } else if (strncmp(s, D_0045F800, 5) == 0) {
        k = 16;
    } else if (strncmp(s, D_0045F808, 5) == 0) {
        k = 17;
    } else if (strncmp(s, D_0045F810, 5) == 0) {
        k = 18;
    } else if (strncmp(s, D_0045F818, 5) == 0) {
        k = 19;
    } else if (strncmp(s, D_0045F820, 5) == 0) {
        k = 20;
    }
    if (k != 0) {
        *out = k;
        return 1;
    }
    return 0;
}
