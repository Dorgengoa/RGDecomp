/* rgp:protos */
#define RGP_SELF_InsectCageParamsLoad_386810 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern void *memset(void *, s32, s32);
extern u8 D_0047FD00;
extern s32 D_004832B0;
extern s8 D_00483400;
/*rgp*/

void InsectCageParamsLoad_386810(s32 arg0, s32 arg1, s32 arg2)
{
    u8 sp30[0xED0] __attribute__((aligned(16)));
    s32 obj;

    obj = ((s32)ConstructNewArray_100710(((s32)MemStackNew_14e1b0(0x350, arg0)), (void *)MenuObjParamsCtor_388010, 0, 0x34, 0x10));
    D_004832B0 = obj;
    memset((void *)obj, 0, 0x340);
    D_00483400 = 0;
    TextReaderCtor_15f140(sp30);
    BuildKeywordHashTable_15f270(sp30, &D_0047FD00);
    TextReaderOpen_15f1b0(sp30, arg1, arg2);
    TextReaderParseAll_15f3f0(sp30);
}
