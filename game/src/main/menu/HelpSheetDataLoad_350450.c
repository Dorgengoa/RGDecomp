/* rgp:protos */
#define RGP_SELF_HelpSheetDataLoad_350450 1
#include "port/game_protos.h"
#line 1




#include "types.h"
#pragma opt_loop_invariants off




typedef struct ScriptVm { u8 raw[0xED0]; } ScriptVm;
typedef struct B40 { s8 b[0x40]; } B40;
typedef struct B20 { s8 b[0x20]; } B20;
typedef struct B10 { s8 b[0x10]; } B10;
typedef struct Rec { s16 f00; s16 f02; s16 f04; s16 extra6; s16 extra8; B40 f06; B20 f46; B10 f66; } Rec;

extern u8 D_00453BB0[];

extern Rec *D_00482E9C;
extern s32  D_00482E94;
extern s32  D_00482E98;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void HelpSheetDataLoad_350450(s32 a, s32 b)
{
    ScriptVm vm __attribute__((aligned(16)));
    s32      i;
    s32      j;
    u8      *off;

    D_00482E94 = 0;
D_00482E9C=0;
    TextReaderCtor_15f140(&vm);
    BuildKeywordHashTable_15f270(&vm, D_00453BB0);
    TextReaderOpen_15f1b0(&vm, a, b);
    TextReaderParseAll_15f3f0(&vm);

    for (i = 0; i < D_00482E98 - 1; i++) {
        off = (u8 *)(i * sizeof(Rec));
        for (j = i + 1; j < D_00482E98; j++) {
            Rec *pb = &D_00482E9C[j];
            Rec *pa = (Rec *)(off + (s32)D_00482E9C);
            Rec *pw;

            if ((*pa).f02 > (*pb).f02) {
                Rec tmp __attribute__((aligned(16)));

                tmp = *pa;
                pw = (Rec *)((u32)j * sizeof(Rec));
                (*pa).f00 = (*pb).f00;
                (*pa).f02 = (*pb).f02;
                (*pa).f04 = (*pb).f04;
                (*pa).extra6=(*pb).extra6;
(*pa).extra8=(*pb).extra8;
(*pa).f06 = (*pb).f06;
                (*pa).f46 = (*pb).f46;
                (*pa).f66 = (*pb).f66;
                pw = (Rec *)((u8 *)D_00482E9C + (s32)pw);
                pw->f00 = tmp.f00;
                pw->f02 = tmp.f02;
                pw->f04 = tmp.f04;
                pw->extra6=tmp.extra6;
pw->extra8=tmp.extra8;
pw->f06 = tmp.f06;
                pw->f46 = tmp.f46;
                pw->f66 = tmp.f66;
            }
        }
    }
}
