#objdump: -dr --prefix-addresses --show-raw-insn
#name: ARM arm7t
#as: -marm7t -EL

# Test the halfword and signextend memory transfers:

.*: +file format .*arm.*little

Disassembly of section .text:
00000000 <[^>]*> e1d100b0 ?	ldrh	r0, \[r1\]
00000004 <[^>]*> e1f100b0 ?	ldrh	r0, \[r1\]!
00000008 <[^>]*> e19100b2 ?	ldrh	r0, \[r1, r2\]
0000000c <[^>]*> e1b100b2 ?	ldrh	r0, \[r1, r2\]!
00000010 <[^>]*> e1d100bc ?	ldrh	r0, \[r1, #c\]
00000014 <[^>]*> e1f100bc ?	ldrh	r0, \[r1, #c\]!
00000018 <[^>]*> e15100bc ?	ldrh	r0, \[r1, -#c\]
0000001c <[^>]*> e09100b2 ?	ldrh	r0, \[r1\], r2
00000020 <[^>]*> e3a00cff ?	mov	r0, #ff00
00000024 <[^>]*> e1df0bb4 ?	ldrh	r0, 000000e0 <\$\$lit_1>
00000028 <[^>]*> e1df0abc ?	ldrh	r0, 000000dc <.L2>
0000002c <[^>]*> e1c100b0 ?	strh	r0, \[r1\]
00000030 <[^>]*> e1e100b0 ?	strh	r0, \[r1\]!
00000034 <[^>]*> e18100b2 ?	strh	r0, \[r1, r2\]
00000038 <[^>]*> e1a100b2 ?	strh	r0, \[r1, r2\]!
0000003c <[^>]*> e1c100bc ?	strh	r0, \[r1, #c\]
00000040 <[^>]*> e1e100bc ?	strh	r0, \[r1, #c\]!
00000044 <[^>]*> e14100bc ?	strh	r0, \[r1, -#c\]
00000048 <[^>]*> e08100b2 ?	strh	r0, \[r1\], r2
0000004c <[^>]*> e1cf08b8 ?	strh	r0, 000000dc <.L2>
00000050 <[^>]*> e1d100d0 ?	ldrsb	r0, \[r1\]
00000054 <[^>]*> e1f100d0 ?	ldrsb	r0, \[r1\]!
00000058 <[^>]*> e19100d2 ?	ldrsb	r0, \[r1, r2\]
0000005c <[^>]*> e1b100d2 ?	ldrsb	r0, \[r1, r2\]!
00000060 <[^>]*> e1d100dc ?	ldrsb	r0, \[r1, #c\]
00000064 <[^>]*> e1f100dc ?	ldrsb	r0, \[r1, #c\]!
00000068 <[^>]*> e15100dc ?	ldrsb	r0, \[r1, -#c\]
0000006c <[^>]*> e09100d2 ?	ldrsb	r0, \[r1\], r2
00000070 <[^>]*> e3a000de ?	mov	r0, #de
00000074 <[^>]*> e1df06d0 ?	ldrsb	r0, 000000dc <.L2>
00000078 <[^>]*> e1d100f0 ?	ldrsh	r0, \[r1\]
0000007c <[^>]*> e1f100f0 ?	ldrsh	r0, \[r1\]!
00000080 <[^>]*> e19100f2 ?	ldrsh	r0, \[r1, r2\]
00000084 <[^>]*> e1b100f2 ?	ldrsh	r0, \[r1, r2\]!
00000088 <[^>]*> e1d100fc ?	ldrsh	r0, \[r1, #c\]
0000008c <[^>]*> e1f100fc ?	ldrsh	r0, \[r1, #c\]!
00000090 <[^>]*> e15100fc ?	ldrsh	r0, \[r1, -#c\]
00000094 <[^>]*> e09100f2 ?	ldrsh	r0, \[r1\], r2
00000098 <[^>]*> e3a00cff ?	mov	r0, #ff00
0000009c <[^>]*> e1df03fc ?	ldrsh	r0, 000000e0 <\$\$lit_1>
000000a0 <[^>]*> e1df03f4 ?	ldrsh	r0, 000000dc <.L2>
000000a4 <[^>]*> e19100b2 ?	ldrh	r0, \[r1, r2\]
000000a8 <[^>]*> 119100b2 ?	ldrneh	r0, \[r1, r2\]
000000ac <[^>]*> 819100b2 ?	ldrhih	r0, \[r1, r2\]
000000b0 <[^>]*> b19100b2 ?	ldrlth	r0, \[r1, r2\]
000000b4 <[^>]*> e19100f2 ?	ldrsh	r0, \[r1, r2\]
000000b8 <[^>]*> 119100f2 ?	ldrnesh	r0, \[r1, r2\]
000000bc <[^>]*> 819100f2 ?	ldrhish	r0, \[r1, r2\]
000000c0 <[^>]*> b19100f2 ?	ldrltsh	r0, \[r1, r2\]
000000c4 <[^>]*> e19100d2 ?	ldrsb	r0, \[r1, r2\]
000000c8 <[^>]*> 119100d2 ?	ldrnesb	r0, \[r1, r2\]
000000cc <[^>]*> 819100d2 ?	ldrhisb	r0, \[r1, r2\]
000000d0 <[^>]*> b19100d2 ?	ldrltsb	r0, \[r1, r2\]
000000d4 <[^>]*> e1df00f4 ?	ldrsh	r0, 000000e0 <\$\$lit_1>
000000d8 <[^>]*> e1df00f4 ?	ldrsh	r0, 000000e4 <\$\$lit_1\+4>
000000dc <[^>]*> 00000000 ?	andeq	r0, r0, r0
[		]*dc: 32	.LC0
000000e0 <[^>]*> 0000c0de ?	.*
000000e4 <[^>]*> 0000dead ?	.*
