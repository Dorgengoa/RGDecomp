# Retail .reginfo register masks, pinned for the link (scripts/link.py).
#
# mwcc objects carry no .reginfo, so the image's masks are the OR of the
# GNU-as parts' masks only.  Once the last ASSEMBLY user of a register is
# converted to C, that bit drops out and the ELF differs in .reginfo alone
# (s65m: RevelationBoardDraw_349e70 was the last asm user of $f18/$f19 -> cprmask[1]
# 0xfff3ffff vs retail 0xffffffff).  This file is assembled together with
# main_data and uses every register retail marks: gprmask 0xf7fffffe (all
# but $zero and $k1), cprmask[1] 0xffffffff.  gasfixup.py then removes the
# .reginfo_pin section, so no bytes reach the image; only the masks remain.
	.section .reginfo_pin, "", @progbits
	.set noat
	.set noreorder
	addu $1, $1, $1
	addu $2, $2, $2
	addu $3, $3, $3
	addu $4, $4, $4
	addu $5, $5, $5
	addu $6, $6, $6
	addu $7, $7, $7
	addu $8, $8, $8
	addu $9, $9, $9
	addu $10, $10, $10
	addu $11, $11, $11
	addu $12, $12, $12
	addu $13, $13, $13
	addu $14, $14, $14
	addu $15, $15, $15
	addu $16, $16, $16
	addu $17, $17, $17
	addu $18, $18, $18
	addu $19, $19, $19
	addu $20, $20, $20
	addu $21, $21, $21
	addu $22, $22, $22
	addu $23, $23, $23
	addu $24, $24, $24
	addu $25, $25, $25
	addu $26, $26, $26
	addu $28, $28, $28
	addu $29, $29, $29
	addu $30, $30, $30
	addu $31, $31, $31
	mov.s $f0, $f0
	mov.s $f1, $f1
	mov.s $f2, $f2
	mov.s $f3, $f3
	mov.s $f4, $f4
	mov.s $f5, $f5
	mov.s $f6, $f6
	mov.s $f7, $f7
	mov.s $f8, $f8
	mov.s $f9, $f9
	mov.s $f10, $f10
	mov.s $f11, $f11
	mov.s $f12, $f12
	mov.s $f13, $f13
	mov.s $f14, $f14
	mov.s $f15, $f15
	mov.s $f16, $f16
	mov.s $f17, $f17
	mov.s $f18, $f18
	mov.s $f19, $f19
	mov.s $f20, $f20
	mov.s $f21, $f21
	mov.s $f22, $f22
	mov.s $f23, $f23
	mov.s $f24, $f24
	mov.s $f25, $f25
	mov.s $f26, $f26
	mov.s $f27, $f27
	mov.s $f28, $f28
	mov.s $f29, $f29
	mov.s $f30, $f30
	mov.s $f31, $f31
	.set at
	.set reorder
