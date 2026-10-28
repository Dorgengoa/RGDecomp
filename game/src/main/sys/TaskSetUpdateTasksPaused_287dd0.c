/* rgp:protos */
#define RGP_SELF_TaskSetUpdateTasksPaused_287dd0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* A registration LIST: one call to TaskSetCharaTasksPaused_288130, then a `u8` flag built from
   the parameter and handed to TaskSetEnabled_27c2a0 with 51 string literals.  The
   strings are "Step Fade", "Step Factory", ... -- phase names.

   The flag is retail's `sltu $2,$0,$16 / xori $2,$2,1 / andi $16,$2,0xFF`,
   which is a u8 bool built from an INEQUALITY and negated in one expression,
   not the `x == 0` form (that emits xor/sltiu).  See
   memory/subsystem-decomp-track.md section 2.

   Every literal is declared as the external spimdisasm named it; a source
   string would take mwcc's own @N label and could never take the same
   relocation. */

/*rgp*/
/*rgp*/

extern char D_0045FED0[];
extern char D_0045FF78[];
extern char D_0045FF88[];
extern char D_0045FF98[];
extern char D_0045FFA8[];
extern char D_0045FFB8[];
extern char D_0045FFE0[];
extern char D_0045FFF0[];
extern char D_00460000[];
extern char D_00460010[];
extern char D_00460028[];
extern char D_00460038[];
extern char D_00460070[];
extern char D_004600D8[];
extern char D_00460130[];
extern char D_004601B8[];
extern char D_00460200[];
extern char D_00460210[];
extern char D_00460230[];
extern char D_00460250[];
extern char D_00460268[];
extern char D_00460280[];
extern char D_004602A0[];
extern char D_004602C0[];
extern char D_004602D8[];
extern char D_004602F8[];
extern char D_00460350[];
extern char D_00460368[];
extern char D_00460390[];
extern char D_004603B0[];
extern char D_004603D0[];
extern char D_004603F0[];
extern char D_00460408[];
extern char D_00460420[];
extern char D_00460430[];
extern char D_00460440[];
extern char D_00460450[];
extern char D_00460460[];
extern char D_00460478[];
extern char D_00460490[];
extern char D_004604B0[];
extern char D_004604F0[];
extern char D_00460500[];
extern char D_00460520[];
extern char D_00460558[];
extern char D_00460568[];
extern char D_00460578[];
extern char D_00460588[];
extern char D_00460598[];

void TaskSetUpdateTasksPaused_287dd0(s32 mode)
{
    u8 f;

    TaskSetCharaTasksPaused_288130(mode);
    f = !(mode != 0);
    TaskSetEnabled_27c2a0(f, D_00460588);
    TaskSetEnabled_27c2a0(f, D_0045FF88);
    TaskSetEnabled_27c2a0(f, D_0045FFA8);
    TaskSetEnabled_27c2a0(f, D_0045FFE0);
    TaskSetEnabled_27c2a0(f, D_0045FFF0);
    TaskSetEnabled_27c2a0(f, D_004602D8);
    TaskSetEnabled_27c2a0(f, D_0045FF78);
    TaskSetEnabled_27c2a0(f, D_0045FF98);
    TaskSetEnabled_27c2a0(f, D_0045FFB8);
    TaskSetEnabled_27c2a0(f, D_00460568);
    TaskSetEnabled_27c2a0(f, D_00460368);
    TaskSetEnabled_27c2a0(f, D_00460268);
    TaskSetEnabled_27c2a0(f, D_00460280);
    TaskSetEnabled_27c2a0(f, D_004602A0);
    TaskSetEnabled_27c2a0(f, D_00460028);
    TaskSetEnabled_27c2a0(f, D_004601B8);
    TaskSetEnabled_27c2a0(f, D_00460038);
    TaskSetEnabled_27c2a0(f, D_00460210);
    TaskSetEnabled_27c2a0(f, D_004600D8);
    TaskSetEnabled_27c2a0(f, D_00460200);
    TaskSetEnabled_27c2a0(f, D_004602C0);
    TaskSetEnabled_27c2a0(f, D_00460070);
    TaskSetEnabled_27c2a0(f, D_00460000);
    TaskSetEnabled_27c2a0(f, D_00460350);
    TaskSetEnabled_27c2a0(f, D_00460250);
    TaskSetEnabled_27c2a0(f, D_00460230);
    TaskSetEnabled_27c2a0(f, D_004602F8);
    TaskSetEnabled_27c2a0(f, D_0045FED0);
    TaskSetEnabled_27c2a0(f, D_00460130);
    TaskSetEnabled_27c2a0(f, D_00460368);
    TaskSetEnabled_27c2a0(f, D_0045FF88);
    TaskSetEnabled_27c2a0(f, D_00460010);
    TaskSetEnabled_27c2a0(f, D_00460578);
    TaskSetEnabled_27c2a0(f, D_00460408);
    TaskSetEnabled_27c2a0(f, D_00460390);
    TaskSetEnabled_27c2a0(f, D_00460430);
    TaskSetEnabled_27c2a0(f, D_00460420);
    TaskSetEnabled_27c2a0(f, D_00460440);
    TaskSetEnabled_27c2a0(f, D_00460558);
    TaskSetEnabled_27c2a0(f, D_004604F0);
    TaskSetEnabled_27c2a0(f, D_004603B0);
    TaskSetEnabled_27c2a0(f, D_004603D0);
    TaskSetEnabled_27c2a0(f, D_004603F0);
    TaskSetEnabled_27c2a0(f, D_00460500);
    TaskSetEnabled_27c2a0(f, D_00460460);
    TaskSetEnabled_27c2a0(f, D_00460478);
    TaskSetEnabled_27c2a0(f, D_00460490);
    TaskSetEnabled_27c2a0(f, D_004604B0);
    TaskSetEnabled_27c2a0(f, D_00460450);
    TaskSetEnabled_27c2a0(f, D_00460520);
    TaskSetEnabled_27c2a0(f, D_00460598);
}
