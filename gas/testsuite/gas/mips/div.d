#objdump: -dr --prefix-addresses
#name: MIPS div

# Test the div macro.

.*: +file format .*mips.*

Disassembly of section .text:
0+0000 <[^>]*> div	\$zero,\$a0,\$a1
0+0004 <[^>]*> div	\$zero,\$a0,\$a1
0+0008 <[^>]*> bnez	\$a1,0+0014 <foo\+14>
0+000c <[^>]*> nop
0+0010 <[^>]*> break	0x7
0+0014 <[^>]*> li	\$at,-1
0+0018 <[^>]*> bne	\$a1,\$at,0+002c <foo\+2c>
0+001c <[^>]*> lui	\$at,0x8000
0+0020 <[^>]*> bne	\$a0,\$at,0+002c <foo\+2c>
0+0024 <[^>]*> nop
0+0028 <[^>]*> break	0x6
0+002c <[^>]*> mflo	\$a0
	...
0+0038 <[^>]*> div	\$zero,\$a1,\$a2
0+003c <[^>]*> bnez	\$a2,0+0048 <foo\+48>
0+0040 <[^>]*> nop
0+0044 <[^>]*> break	0x7
0+0048 <[^>]*> li	\$at,-1
0+004c <[^>]*> bne	\$a2,\$at,0+0060 <foo\+60>
0+0050 <[^>]*> lui	\$at,0x8000
0+0054 <[^>]*> bne	\$a1,\$at,0+0060 <foo\+60>
0+0058 <[^>]*> nop
0+005c <[^>]*> break	0x6
0+0060 <[^>]*> mflo	\$a0
0+0064 <[^>]*> move	\$a0,\$a0
0+0068 <[^>]*> move	\$a0,\$a1
0+006c <[^>]*> neg	\$a0,\$a0
0+0070 <[^>]*> neg	\$a0,\$a1
0+0074 <[^>]*> li	\$at,2
0+0078 <[^>]*> div	\$zero,\$a0,\$at
0+007c <[^>]*> mflo	\$a0
0+0080 <[^>]*> li	\$at,2
0+0084 <[^>]*> nop
0+0088 <[^>]*> div	\$zero,\$a1,\$at
0+008c <[^>]*> mflo	\$a0
0+0090 <[^>]*> li	\$at,0x8000
0+0094 <[^>]*> nop
0+0098 <[^>]*> div	\$zero,\$a0,\$at
0+009c <[^>]*> mflo	\$a0
0+00a0 <[^>]*> li	\$at,0x8000
0+00a4 <[^>]*> nop
0+00a8 <[^>]*> div	\$zero,\$a1,\$at
0+00ac <[^>]*> mflo	\$a0
0+00b0 <[^>]*> li	\$at,-32768
0+00b4 <[^>]*> nop
0+00b8 <[^>]*> div	\$zero,\$a0,\$at
0+00bc <[^>]*> mflo	\$a0
0+00c0 <[^>]*> li	\$at,-32768
0+00c4 <[^>]*> nop
0+00c8 <[^>]*> div	\$zero,\$a1,\$at
0+00cc <[^>]*> mflo	\$a0
0+00d0 <[^>]*> lui	\$at,0x1
0+00d4 <[^>]*> nop
0+00d8 <[^>]*> div	\$zero,\$a0,\$at
0+00dc <[^>]*> mflo	\$a0
0+00e0 <[^>]*> lui	\$at,0x1
0+00e4 <[^>]*> nop
0+00e8 <[^>]*> div	\$zero,\$a1,\$at
0+00ec <[^>]*> mflo	\$a0
0+00f0 <[^>]*> lui	\$at,0x1
0+00f4 <[^>]*> ori	\$at,\$at,0xa5a5
0+00f8 <[^>]*> div	\$zero,\$a0,\$at
0+00fc <[^>]*> mflo	\$a0
0+0100 <[^>]*> lui	\$at,0x1
0+0104 <[^>]*> ori	\$at,\$at,0xa5a5
0+0108 <[^>]*> div	\$zero,\$a1,\$at
0+010c <[^>]*> mflo	\$a0
	...
0+0118 <[^>]*> divu	\$zero,\$a0,\$a1
0+011c <[^>]*> divu	\$zero,\$a0,\$a1
0+0120 <[^>]*> bnez	\$a1,0+012c <foo\+12c>
0+0124 <[^>]*> nop
0+0128 <[^>]*> break	0x7
0+012c <[^>]*> mflo	\$a0
	...
0+0138 <[^>]*> divu	\$zero,\$a1,\$a2
0+013c <[^>]*> bnez	\$a2,0+0148 <foo\+148>
0+0140 <[^>]*> nop
0+0144 <[^>]*> break	0x7
0+0148 <[^>]*> mflo	\$a0
0+014c <[^>]*> move	\$a0,\$a0
0+0150 <[^>]*> nop
0+0154 <[^>]*> div	\$zero,\$a1,\$a2
0+0158 <[^>]*> bnez	\$a2,0+0164 <foo\+164>
0+015c <[^>]*> nop
0+0160 <[^>]*> break	0x7
0+0164 <[^>]*> li	\$at,-1
0+0168 <[^>]*> bne	\$a2,\$at,0+017c <foo\+17c>
0+016c <[^>]*> lui	\$at,0x8000
0+0170 <[^>]*> bne	\$a1,\$at,0+017c <foo\+17c>
0+0174 <[^>]*> nop
0+0178 <[^>]*> break	0x6
0+017c <[^>]*> mfhi	\$a0
0+0180 <[^>]*> li	\$at,2
0+0184 <[^>]*> nop
0+0188 <[^>]*> divu	\$zero,\$a1,\$at
0+018c <[^>]*> mfhi	\$a0
	...
0+0198 <[^>]*> ddiv	\$zero,\$a1,\$a2
0+019c <[^>]*> bnez	\$a2,0+01a8 <foo\+1a8>
0+01a0 <[^>]*> nop
0+01a4 <[^>]*> break	0x7
0+01a8 <[^>]*> daddiu	\$at,\$zero,-1
0+01ac <[^>]*> bne	\$a2,\$at,0+01c4 <foo\+1c4>
0+01b0 <[^>]*> daddiu	\$at,\$zero,1
0+01b4 <[^>]*> dsll32	\$at,\$at,0x1f
0+01b8 <[^>]*> bne	\$a1,\$at,0+01c4 <foo\+1c4>
0+01bc <[^>]*> nop
0+01c0 <[^>]*> break	0x6
0+01c4 <[^>]*> mflo	\$a0
0+01c8 <[^>]*> li	\$at,2
0+01cc <[^>]*> nop
0+01d0 <[^>]*> ddivu	\$zero,\$a1,\$at
0+01d4 <[^>]*> mflo	\$a0
0+01d8 <[^>]*> li	\$at,0x8000
0+01dc <[^>]*> nop
0+01e0 <[^>]*> ddiv	\$zero,\$a1,\$at
0+01e4 <[^>]*> mfhi	\$a0
0+01e8 <[^>]*> li	\$at,-32768
0+01ec <[^>]*> nop
0+01f0 <[^>]*> ddivu	\$zero,\$a1,\$at
0+01f4 <[^>]*> mfhi	\$a0
	...
