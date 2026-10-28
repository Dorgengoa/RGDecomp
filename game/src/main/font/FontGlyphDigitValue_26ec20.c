/* rgp:protos */
#define RGP_SELF_FontGlyphDigitValue_26ec20 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
extern char D_0045F560[0x40];
extern char D_0045F568[0x40];
extern char D_0045F570[0x40];
extern char D_0045F578[0x40];
extern char D_0045F580[0x40];
extern char D_0045F588[0x40];
extern char D_0045F590[0x40];
extern char D_0045F598[0x40];
extern char D_0045F5A0[0x40];
extern char D_0045F5A8[0x40];

s32 FontGlyphDigitValue_26ec20(void *arg0, s32 arg1)
{
    if (arg1 == FontFindCode_26ee00(arg0, D_0045F560)) {
        return 1;
    }
    if (arg1 == FontFindCode_26ee00(arg0, D_0045F568)) {
        return 2;
    }
    if (arg1 == FontFindCode_26ee00(arg0, D_0045F570)) {
        return 3;
    }
    if (arg1 == FontFindCode_26ee00(arg0, D_0045F578)) {
        return 4;
    }
    if (arg1 == FontFindCode_26ee00(arg0, D_0045F580)) {
        return 5;
    }
    if (arg1 == FontFindCode_26ee00(arg0, D_0045F588)) {
        return 6;
    }
    if (arg1 == FontFindCode_26ee00(arg0, D_0045F590)) {
        return 7;
    }
    if (arg1 == FontFindCode_26ee00(arg0, D_0045F598)) {
        return 8;
    }
    if (arg1 == FontFindCode_26ee00(arg0, D_0045F5A0)) {
        return 9;
    }
    return -(arg1 != FontFindCode_26ee00(arg0, D_0045F5A8));
}
