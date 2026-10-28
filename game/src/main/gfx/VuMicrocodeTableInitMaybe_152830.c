/* rgp:protos */
#define RGP_SELF_VuMicrocodeTableInitMaybe_152830 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Table initialiser: p is a pair of [4][12][4] pointer tables (0x000 and
   0x300).  Plane stride is 12*4*4 = 0xC0, row stride 0x10.
   The three trailing loops copy plane 0 onto planes 1, 2 and 3 and then patch
   a handful of entries; the loads and stores share one address, which is what
   `p->a[n][k][m] = p->a[0][k][m];` gives. */

typedef struct {
    void *a[4][12][4];
    void *b[4][12][4];
} Tbl;

extern void *D_00449DD0[];
extern u8 D_00436CA0[];
extern u8 D_00436CB0[];
extern u8 D_00436FB0[];
extern u8 D_004371D0[];
extern u8 D_00438520[];
extern u8 D_00438540[];
extern u8 D_0043E960[];
extern u8 D_0043E980[];
extern u8 D_0043EA30[];
extern u8 D_0043EBE0[];
extern u8 D_0043ECD0[];
extern u8 D_0043EF20[];
extern u8 D_0043F100[];
extern u8 D_0043F450[];
extern u8 D_0043F590[];
extern u8 D_0043F820[];
extern u8 D_0043F9C0[];
extern u8 D_00440970[];
extern u8 D_00441660[];
extern u8 D_004425F0[];
extern u8 D_00443050[];
extern u8 D_004441A0[];
extern u8 D_004443B0[];
extern u8 D_004452A0[];
extern u8 D_00449DF0[];
extern u8 D_00449E10[];
extern u8 D_00449E30[];
extern u8 D_00449E50[];
extern u8 D_00449E70[];
extern u8 D_00449E90[];
extern u8 D_00449EB0[];
extern u8 D_00449ED0[];
extern s32 D_0047DEC0;
extern s32 D_0047DED0;

Tbl *VuMicrocodeTableInitMaybe_152830(Tbl *p)
{
    s32 c1;
    s32 c2;
    s32 c3;
    s32 c4;
    s32 i;
    s32 j;
    s32 k;
    s32 m;

    for (i = 0; i < 8; i++) {
        D_00449DD0[i] = D_00436CA0;
    }
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 12; j++) {
            for (k = 0; k < 4; k++) {
                p->a[i][j][k] = D_00436CA0;
            }
            for (k = 0; k < 4; k++) {
                p->b[i][j][k] = D_00449DD0;
            }
        }
    }

    p->a[0][0][0] = D_00436CB0;
    p->a[0][0][1] = D_0043E980;
    p->a[0][0][2] = D_004371D0;
    p->a[0][1][0] = D_00441660;
    p->a[0][1][1] = D_00436CA0;
    p->a[0][1][2] = D_00436CA0;
    p->a[0][2][0] = D_00436CB0;
    p->a[0][2][1] = D_0043EA30;
    p->a[0][2][2] = D_004371D0;
    p->a[0][3][0] = D_00436CB0;
    p->a[0][3][1] = D_0043EBE0;
    p->a[0][3][2] = D_004371D0;
    p->a[0][4][0] = D_004425F0;
    p->a[0][4][1] = D_00436CA0;
    p->a[0][4][2] = D_00436CA0;
    p->a[0][5][0] = D_0043F820;
    p->a[0][5][1] = D_00436CA0;
    p->a[0][5][2] = D_0043F9C0;
    p->a[0][6][0] = D_00436FB0;
    p->a[0][6][1] = D_0043ECD0;
    p->a[0][6][2] = D_00438520;
    p->a[0][7][0] = D_00436CB0;
    p->a[0][7][1] = D_0043EF20;
    p->a[0][7][2] = D_004371D0;
    p->a[0][8][0] = D_00436FB0;
    p->a[0][8][1] = D_0043E960;
    p->a[0][8][2] = D_00438540;
    p->a[0][9][0] = D_00436CB0;
    p->a[0][9][1] = D_0043F100;
    p->a[0][9][2] = D_004371D0;
    p->a[0][10][0] = D_00440970;
    p->a[0][10][1] = D_0043F450;
    p->a[0][10][2] = D_00443050;
    p->a[0][11][0] = D_00436CB0;
    p->a[0][11][1] = D_0043F590;
    p->a[0][11][2] = D_00438520;

    p->b[0][0][0] = &D_0047DEC0;
    p->b[0][0][1] = D_00449DF0;
    p->b[0][0][2] = D_00449E30;
    p->b[0][1][0] = &D_0047DED0;
    p->b[0][1][1] = D_00449DD0;
    p->b[0][1][2] = D_00449E50;
    p->b[0][2][0] = &D_0047DEC0;
    p->b[0][2][1] = D_00449DF0;
    p->b[0][2][2] = D_00449E30;
    p->b[0][3][0] = &D_0047DEC0;
    p->b[0][3][1] = D_00449DF0;
    p->b[0][3][2] = D_00449E30;
    p->b[0][4][0] = &D_0047DED0;
    p->b[0][4][1] = D_00449DD0;
    p->b[0][4][2] = D_00449E90;
    p->b[0][5][0] = D_00449DD0;
    p->b[0][5][1] = D_00449DD0;
    p->b[0][5][2] = D_00449DD0;
    p->b[0][6][0] = &D_0047DEC0;
    p->b[0][6][1] = D_00449DF0;
    p->b[0][6][2] = D_00449EB0;
    p->b[0][7][0] = &D_0047DEC0;
    p->b[0][7][1] = D_00449DF0;
    p->b[0][7][2] = D_00449E30;
    p->b[0][8][0] = &D_0047DEC0;
    p->b[0][8][1] = D_00449DF0;
    p->b[0][8][2] = D_00449ED0;
    p->b[0][9][0] = &D_0047DEC0;
    p->b[0][9][1] = D_00449DF0;
    p->b[0][9][2] = D_00449E30;
    p->b[0][10][0] = &D_0047DEC0;
    p->b[0][10][1] = D_00449E10;
    p->b[0][10][2] = D_00449DD0;
    p->b[0][11][0] = &D_0047DEC0;
    p->b[0][11][1] = D_00449DD0;
    p->b[0][11][2] = D_00449E70;

    for (j = 0; j < 12; j++) {
        for (m = 0; m < 4; m++) {
            p->a[1][j][m] = p->a[0][j][m];
        }
        for (m = 0; m < 4; m++) {
            p->b[1][j][m] = p->b[0][j][m];
        }
    }
    p->a[1][0][0] = D_004441A0;
    p->a[1][0][2] = D_004443B0;
    p->a[1][2][0] = D_004441A0;
    p->a[1][2][2] = D_004443B0;

    for (c1 = 0; c1 < 12; c1++) {
        for (c2 = 0; c2 < 4; c2++) {
            p->a[2][c1][c2] = p->a[0][c1][c2];
        }
        for (c2 = 0; c2 < 4; c2++) {
            p->b[2][c1][c2] = p->b[0][c1][c2];
        }
    }
    p->a[2][0][0] = D_004441A0;
    p->a[2][0][2] = D_004452A0;
    p->a[2][2][0] = D_004441A0;
    p->a[2][2][2] = D_004452A0;

    for (c3 = 0; c3 < 12; c3++) {
        for (c4 = 0; c4 < 4; c4++) {
            p->a[3][c3][c4] = p->a[0][c3][c4];
        }
        for (c4 = 0; c4 < 4; c4++) {
            p->b[3][c3][c4] = p->b[0][c3][c4];
        }
    }
    return p;
}
