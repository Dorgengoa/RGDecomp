/* rgp:protos */
#include "port/game_protos.h"
#line 1
/* rg:datareloc */
/* Generated: do not edit. */
#include "types.h"
extern void MpegParseCopyrightExt_110248(void);
extern void MpegParsePicDisplayExt_1102e0(void);
extern void MpegParsePictureCodingExt_10fbf0(void);
extern void MpegParseQuantMatrixExt_10fae8(void);
extern void MpegParseSeqDisplayExt_1101b8(void);
/*rgp*/
extern void MpegParseSequenceExt_10f9a8(void);
/*rgp*/
extern void func_0010FDD8(void);
extern void func_0010FDE8(void);
u32 D_004563B8[14] __attribute__((section(".data$rg004563B8"), aligned(8))) = {
    (u32)&MpegParseUnknownExt_10fbe0, (u32)&MpegParseSequenceExt_10f9a8, (u32)&MpegParseSeqDisplayExt_1101b8, (u32)&MpegParseQuantMatrixExt_10fae8, (u32)&MpegParseCopyrightExt_110248, (u32)&MpegParseSeqScalableExt_10fbd0, (u32)&MpegParseUnknownExt_10fbe0, (u32)&MpegParsePicDisplayExt_1102e0, (u32)&MpegParsePictureCodingExt_10fbf0, (u32)&func_0010FDD8, (u32)&func_0010FDE8, @X@004563E4@, @X@004563E8@, @X@004563EC@
};
typedef char data2c_sizecheck_004563B8[(sizeof(D_004563B8) == 56) ? 1 : -1];
