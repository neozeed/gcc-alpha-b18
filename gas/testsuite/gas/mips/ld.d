#objdump: -dr --prefix-addresses
#name: MIPS ld

# Test the ld macro.

.*: +file format .*mips.*

Disassembly of section .text:
0+0000 <[^>]*> lw	\$a0,0\(\$zero\)
0+0004 <[^>]*> lw	\$a1,4\(\$zero\)
0+0008 <[^>]*> lw	\$a0,1\(\$zero\)
0+000c <[^>]*> lw	\$a1,5\(\$zero\)
0+0010 <[^>]*> lui	\$at,0x1
0+0014 <[^>]*> lw	\$a0,-32768\(\$at\)
0+0018 <[^>]*> lw	\$a1,-32764\(\$at\)
0+001c <[^>]*> lw	\$a0,-32768\(\$zero\)
0+0020 <[^>]*> lw	\$a1,-32764\(\$zero\)
0+0024 <[^>]*> lui	\$at,0x1
0+0028 <[^>]*> lw	\$a0,0\(\$at\)
0+002c <[^>]*> lw	\$a1,4\(\$at\)
0+0030 <[^>]*> lui	\$at,0x2
0+0034 <[^>]*> lw	\$a0,-23131\(\$at\)
0+0038 <[^>]*> lw	\$a1,-23127\(\$at\)
0+003c <[^>]*> nop
0+0040 <[^>]*> lw	\$a0,0\(\$a1\)
0+0044 <[^>]*> lw	\$a1,4\(\$a1\)
0+0048 <[^>]*> nop
0+004c <[^>]*> lw	\$a0,1\(\$a1\)
0+0050 <[^>]*> lw	\$a1,5\(\$a1\)
0+0054 <[^>]*> lui	\$at,0x1
0+0058 <[^>]*> addu	\$at,\$a1,\$at
0+005c <[^>]*> lw	\$a0,-32768\(\$at\)
0+0060 <[^>]*> lw	\$a1,-32764\(\$at\)
0+0064 <[^>]*> nop
0+0068 <[^>]*> lw	\$a0,-32768\(\$a1\)
0+006c <[^>]*> lw	\$a1,-32764\(\$a1\)
0+0070 <[^>]*> lui	\$at,0x1
0+0074 <[^>]*> addu	\$at,\$a1,\$at
0+0078 <[^>]*> lw	\$a0,0\(\$at\)
0+007c <[^>]*> lw	\$a1,4\(\$at\)
0+0080 <[^>]*> lui	\$at,0x2
0+0084 <[^>]*> addu	\$at,\$a1,\$at
0+0088 <[^>]*> lw	\$a0,-23131\(\$at\)
0+008c <[^>]*> lw	\$a1,-23127\(\$at\)
0+0090 <[^>]*> lui	\$at,0x0
[ 	]*90: [A-Z0-9_]*HI[A-Z0-9_]*	.data.*
0+0094 <[^>]*> lw	\$a0,[-0-9]+\(\$at\)
[ 	]*94: [A-Z0-9_]*LO[A-Z0-9_]*	.data.*
0+0098 <[^>]*> lw	\$a1,[-0-9]+\(\$at\)
[ 	]*98: [A-Z0-9_]*LO[A-Z0-9_]*	.data.*
0+009c <[^>]*> lui	\$at,0x0
[ 	]*9c: [A-Z0-9_]*HI[A-Z0-9_]*	big_external_data_label
0+00a0 <[^>]*> lw	\$a0,0\(\$at\)
[ 	]*a0: [A-Z0-9_]*LO[A-Z0-9_]*	big_external_data_label
0+00a4 <[^>]*> lw	\$a1,[-0-9]+\(\$at\)
[ 	]*a4: [A-Z0-9_]*LO[A-Z0-9_]*	big_external_data_label
0+00a8 <[^>]*> lw	\$a0,0\(\$gp\)
[ 	]*a8: [A-Z0-9_]*GPREL[A-Z0-9_]*	small_external_data_label
0+00ac <[^>]*> lw	\$a1,[-0-9]+\(\$gp\)
[ 	]*ac: [A-Z0-9_]*GPREL[A-Z0-9_]*	small_external_data_label
0+00b0 <[^>]*> lui	\$at,0x0
[ 	]*b0: [A-Z0-9_]*HI[A-Z0-9_]*	big_external_common
0+00b4 <[^>]*> lw	\$a0,0\(\$at\)
[ 	]*b4: [A-Z0-9_]*LO[A-Z0-9_]*	big_external_common
0+00b8 <[^>]*> lw	\$a1,[-0-9]+\(\$at\)
[ 	]*b8: [A-Z0-9_]*LO[A-Z0-9_]*	big_external_common
0+00bc <[^>]*> lw	\$a0,0\(\$gp\)
[ 	]*bc: [A-Z0-9_]*GPREL[A-Z0-9_]*	small_external_common
0+00c0 <[^>]*> lw	\$a1,[-0-9]+\(\$gp\)
[ 	]*c0: [A-Z0-9_]*GPREL[A-Z0-9_]*	small_external_common
0+00c4 <[^>]*> lui	\$at,0x0
[ 	]*c4: [A-Z0-9_]*HI[A-Z0-9_]*	.bss.*
0+00c8 <[^>]*> lw	\$a0,[-0-9]+\(\$at\)
[ 	]*c8: [A-Z0-9_]*LO[A-Z0-9_]*	.bss.*
0+00cc <[^>]*> lw	\$a1,[-0-9]+\(\$at\)
[ 	]*cc: [A-Z0-9_]*LO[A-Z0-9_]*	.bss.*
0+00d0 <[^>]*> lw	\$a0,[-0-9]+\(\$gp\)
[ 	]*d0: [A-Z0-9_]*GPREL[A-Z0-9_]*	.sbss.*
0+00d4 <[^>]*> lw	\$a1,[-0-9]+\(\$gp\)
[ 	]*d4: [A-Z0-9_]*GPREL[A-Z0-9_]*	.sbss.*
0+00d8 <[^>]*> lui	\$at,0x0
[ 	]*d8: [A-Z0-9_]*HI[A-Z0-9_]*	.data.*
0+00dc <[^>]*> lw	\$a0,[-0-9]+\(\$at\)
[ 	]*dc: [A-Z0-9_]*LO[A-Z0-9_]*	.data.*
0+00e0 <[^>]*> lw	\$a1,[-0-9]+\(\$at\)
[ 	]*e0: [A-Z0-9_]*LO[A-Z0-9_]*	.data.*
0+00e4 <[^>]*> lui	\$at,0x0
[ 	]*e4: [A-Z0-9_]*HI[A-Z0-9_]*	big_external_data_label
0+00e8 <[^>]*> lw	\$a0,[-0-9]+\(\$at\)
[ 	]*e8: [A-Z0-9_]*LO[A-Z0-9_]*	big_external_data_label
0+00ec <[^>]*> lw	\$a1,[-0-9]+\(\$at\)
[ 	]*ec: [A-Z0-9_]*LO[A-Z0-9_]*	big_external_data_label
0+00f0 <[^>]*> lw	\$a0,1\(\$gp\)
[ 	]*f0: [A-Z0-9_]*GPREL[A-Z0-9_]*	small_external_data_label
0+00f4 <[^>]*> lw	\$a1,5\(\$gp\)
[ 	]*f4: [A-Z0-9_]*GPREL[A-Z0-9_]*	small_external_data_label
0+00f8 <[^>]*> lui	\$at,0x0
[ 	]*f8: [A-Z0-9_]*HI[A-Z0-9_]*	big_external_common
0+00fc <[^>]*> lw	\$a0,[-0-9]+\(\$at\)
[ 	]*fc: [A-Z0-9_]*LO[A-Z0-9_]*	big_external_common
0+0100 <[^>]*> lw	\$a1,[-0-9]+\(\$at\)
[ 	]*100: [A-Z0-9_]*LO[A-Z0-9_]*	big_external_common
0+0104 <[^>]*> lw	\$a0,1\(\$gp\)
[ 	]*104: [A-Z0-9_]*GPREL[A-Z0-9_]*	small_external_common
0+0108 <[^>]*> lw	\$a1,5\(\$gp\)
[ 	]*108: [A-Z0-9_]*GPREL[A-Z0-9_]*	small_external_common
0+010c <[^>]*> lui	\$at,0x0
[ 	]*10c: [A-Z0-9_]*HI[A-Z0-9_]*	.bss.*
0+0110 <[^>]*> lw	\$a0,[-0-9]+\(\$at\)
[ 	]*110: [A-Z0-9_]*LO[A-Z0-9_]*	.bss.*
0+0114 <[^>]*> lw	\$a1,[-0-9]+\(\$at\)
[ 	]*114: [A-Z0-9_]*LO[A-Z0-9_]*	.bss.*
0+0118 <[^>]*> lw	\$a0,[-0-9]+\(\$gp\)
[ 	]*118: [A-Z0-9_]*GPREL[A-Z0-9_]*	.sbss.*
0+011c <[^>]*> lw	\$a1,[-0-9]+\(\$gp\)
[ 	]*11c: [A-Z0-9_]*GPREL[A-Z0-9_]*	.sbss.*
0+0120 <[^>]*> lui	\$at,[-0-9x]+
[ 	]*120: [A-Z0-9_]*HI[A-Z0-9_]*	.data.*
0+0124 <[^>]*> lw	\$a0,[-0-9]+\(\$at\)
[ 	]*124: [A-Z0-9_]*LO[A-Z0-9_]*	.data.*
0+0128 <[^>]*> lw	\$a1,[-0-9]+\(\$at\)
[ 	]*128: [A-Z0-9_]*LO[A-Z0-9_]*	.data.*
0+012c <[^>]*> lui	\$at,[-0-9x]+
[ 	]*12c: [A-Z0-9_]*HI[A-Z0-9_]*	big_external_data_label
0+0130 <[^>]*> lw	\$a0,[-0-9]+\(\$at\)
[ 	]*130: [A-Z0-9_]*LO[A-Z0-9_]*	big_external_data_label
0+0134 <[^>]*> lw	\$a1,[-0-9]+\(\$at\)
[ 	]*134: [A-Z0-9_]*LO[A-Z0-9_]*	big_external_data_label
0+0138 <[^>]*> lui	\$at,[-0-9x]+
[ 	]*138: [A-Z0-9_]*HI[A-Z0-9_]*	small_external_data_label
0+013c <[^>]*> lw	\$a0,[-0-9]+\(\$at\)
[ 	]*13c: [A-Z0-9_]*LO[A-Z0-9_]*	small_external_data_label
0+0140 <[^>]*> lw	\$a1,[-0-9]+\(\$at\)
[ 	]*140: [A-Z0-9_]*LO[A-Z0-9_]*	small_external_data_label
0+0144 <[^>]*> lui	\$at,[-0-9x]+
[ 	]*144: [A-Z0-9_]*HI[A-Z0-9_]*	big_external_common
0+0148 <[^>]*> lw	\$a0,[-0-9]+\(\$at\)
[ 	]*148: [A-Z0-9_]*LO[A-Z0-9_]*	big_external_common
0+014c <[^>]*> lw	\$a1,[-0-9]+\(\$at\)
[ 	]*14c: [A-Z0-9_]*LO[A-Z0-9_]*	big_external_common
0+0150 <[^>]*> lui	\$at,[-0-9x]+
[ 	]*150: [A-Z0-9_]*HI[A-Z0-9_]*	small_external_common
0+0154 <[^>]*> lw	\$a0,[-0-9]+\(\$at\)
[ 	]*154: [A-Z0-9_]*LO[A-Z0-9_]*	small_external_common
0+0158 <[^>]*> lw	\$a1,[-0-9]+\(\$at\)
[ 	]*158: [A-Z0-9_]*LO[A-Z0-9_]*	small_external_common
0+015c <[^>]*> lui	\$at,[-0-9x]+
[ 	]*15c: [A-Z0-9_]*HI[A-Z0-9_]*	.bss.*
0+0160 <[^>]*> lw	\$a0,[-0-9]+\(\$at\)
[ 	]*160: [A-Z0-9_]*LO[A-Z0-9_]*	.bss.*
0+0164 <[^>]*> lw	\$a1,[-0-9]+\(\$at\)
[ 	]*164: [A-Z0-9_]*LO[A-Z0-9_]*	.bss.*
0+0168 <[^>]*> lui	\$at,[-0-9x]+
[ 	]*168: [A-Z0-9_]*HI[A-Z0-9_]*	.sbss.*
0+016c <[^>]*> lw	\$a0,[-0-9]+\(\$at\)
[ 	]*16c: [A-Z0-9_]*LO[A-Z0-9_]*	.sbss.*
0+0170 <[^>]*> lw	\$a1,[-0-9]+\(\$at\)
[ 	]*170: [A-Z0-9_]*LO[A-Z0-9_]*	.sbss.*
0+0174 <[^>]*> lui	\$at,0x0
[ 	]*174: [A-Z0-9_]*HI[A-Z0-9_]*	.data.*
0+0178 <[^>]*> lw	\$a0,[-0-9]+\(\$at\)
[ 	]*178: [A-Z0-9_]*LO[A-Z0-9_]*	.data.*
0+017c <[^>]*> lw	\$a1,[-0-9]+\(\$at\)
[ 	]*17c: [A-Z0-9_]*LO[A-Z0-9_]*	.data.*
0+0180 <[^>]*> lui	\$at,0x0
[ 	]*180: [A-Z0-9_]*HI[A-Z0-9_]*	big_external_data_label
0+0184 <[^>]*> lw	\$a0,[-0-9]+\(\$at\)
[ 	]*184: [A-Z0-9_]*LO[A-Z0-9_]*	big_external_data_label
0+0188 <[^>]*> lw	\$a1,[-0-9]+\(\$at\)
[ 	]*188: [A-Z0-9_]*LO[A-Z0-9_]*	big_external_data_label
0+018c <[^>]*> lui	\$at,0x0
[ 	]*18c: [A-Z0-9_]*HI[A-Z0-9_]*	small_external_data_label
0+0190 <[^>]*> lw	\$a0,[-0-9]+\(\$at\)
[ 	]*190: [A-Z0-9_]*LO[A-Z0-9_]*	small_external_data_label
0+0194 <[^>]*> lw	\$a1,[-0-9]+\(\$at\)
[ 	]*194: [A-Z0-9_]*LO[A-Z0-9_]*	small_external_data_label
0+0198 <[^>]*> lui	\$at,0x0
[ 	]*198: [A-Z0-9_]*HI[A-Z0-9_]*	big_external_common
0+019c <[^>]*> lw	\$a0,[-0-9]+\(\$at\)
[ 	]*19c: [A-Z0-9_]*LO[A-Z0-9_]*	big_external_common
0+01a0 <[^>]*> lw	\$a1,[-0-9]+\(\$at\)
[ 	]*1a0: [A-Z0-9_]*LO[A-Z0-9_]*	big_external_common
0+01a4 <[^>]*> lui	\$at,0x0
[ 	]*1a4: [A-Z0-9_]*HI[A-Z0-9_]*	small_external_common
0+01a8 <[^>]*> lw	\$a0,[-0-9]+\(\$at\)
[ 	]*1a8: [A-Z0-9_]*LO[A-Z0-9_]*	small_external_common
0+01ac <[^>]*> lw	\$a1,[-0-9]+\(\$at\)
[ 	]*1ac: [A-Z0-9_]*LO[A-Z0-9_]*	small_external_common
0+01b0 <[^>]*> lui	\$at,0x0
[ 	]*1b0: [A-Z0-9_]*HI[A-Z0-9_]*	.bss.*
0+01b4 <[^>]*> lw	\$a0,[-0-9]+\(\$at\)
[ 	]*1b4: [A-Z0-9_]*LO[A-Z0-9_]*	.bss.*
0+01b8 <[^>]*> lw	\$a1,[-0-9]+\(\$at\)
[ 	]*1b8: [A-Z0-9_]*LO[A-Z0-9_]*	.bss.*
0+01bc <[^>]*> lui	\$at,0x0
[ 	]*1bc: [A-Z0-9_]*HI[A-Z0-9_]*	.sbss.*
0+01c0 <[^>]*> lw	\$a0,[-0-9]+\(\$at\)
[ 	]*1c0: [A-Z0-9_]*LO[A-Z0-9_]*	.sbss.*
0+01c4 <[^>]*> lw	\$a1,[-0-9]+\(\$at\)
[ 	]*1c4: [A-Z0-9_]*LO[A-Z0-9_]*	.sbss.*
0+01c8 <[^>]*> lui	\$at,[-0-9x]+
[ 	]*1c8: [A-Z0-9_]*HI[A-Z0-9_]*	.data.*
0+01cc <[^>]*> lw	\$a0,[-0-9]+\(\$at\)
[ 	]*1cc: [A-Z0-9_]*LO[A-Z0-9_]*	.data.*
0+01d0 <[^>]*> lw	\$a1,[-0-9]+\(\$at\)
[ 	]*1d0: [A-Z0-9_]*LO[A-Z0-9_]*	.data.*
0+01d4 <[^>]*> lui	\$at,[-0-9x]+
[ 	]*1d4: [A-Z0-9_]*HI[A-Z0-9_]*	big_external_data_label
0+01d8 <[^>]*> lw	\$a0,0\(\$at\)
[ 	]*1d8: [A-Z0-9_]*LO[A-Z0-9_]*	big_external_data_label
0+01dc <[^>]*> lw	\$a1,[-0-9]+\(\$at\)
[ 	]*1dc: [A-Z0-9_]*LO[A-Z0-9_]*	big_external_data_label
0+01e0 <[^>]*> lui	\$at,[-0-9x]+
[ 	]*1e0: [A-Z0-9_]*HI[A-Z0-9_]*	small_external_data_label
0+01e4 <[^>]*> lw	\$a0,0\(\$at\)
[ 	]*1e4: [A-Z0-9_]*LO[A-Z0-9_]*	small_external_data_label
0+01e8 <[^>]*> lw	\$a1,[-0-9]+\(\$at\)
[ 	]*1e8: [A-Z0-9_]*LO[A-Z0-9_]*	small_external_data_label
0+01ec <[^>]*> lui	\$at,[-0-9x]+
[ 	]*1ec: [A-Z0-9_]*HI[A-Z0-9_]*	big_external_common
0+01f0 <[^>]*> lw	\$a0,0\(\$at\)
[ 	]*1f0: [A-Z0-9_]*LO[A-Z0-9_]*	big_external_common
0+01f4 <[^>]*> lw	\$a1,[-0-9]+\(\$at\)
[ 	]*1f4: [A-Z0-9_]*LO[A-Z0-9_]*	big_external_common
0+01f8 <[^>]*> lui	\$at,[-0-9x]+
[ 	]*1f8: [A-Z0-9_]*HI[A-Z0-9_]*	small_external_common
0+01fc <[^>]*> lw	\$a0,0\(\$at\)
[ 	]*1fc: [A-Z0-9_]*LO[A-Z0-9_]*	small_external_common
0+0200 <[^>]*> lw	\$a1,[-0-9]+\(\$at\)
[ 	]*200: [A-Z0-9_]*LO[A-Z0-9_]*	small_external_common
0+0204 <[^>]*> lui	\$at,[-0-9x]+
[ 	]*204: [A-Z0-9_]*HI[A-Z0-9_]*	.bss.*
0+0208 <[^>]*> lw	\$a0,[-0-9]+\(\$at\)
[ 	]*208: [A-Z0-9_]*LO[A-Z0-9_]*	.bss.*
0+020c <[^>]*> lw	\$a1,[-0-9]+\(\$at\)
[ 	]*20c: [A-Z0-9_]*LO[A-Z0-9_]*	.bss.*
0+0210 <[^>]*> lui	\$at,[-0-9x]+
[ 	]*210: [A-Z0-9_]*HI[A-Z0-9_]*	.sbss.*
0+0214 <[^>]*> lw	\$a0,[-0-9]+\(\$at\)
[ 	]*214: [A-Z0-9_]*LO[A-Z0-9_]*	.sbss.*
0+0218 <[^>]*> lw	\$a1,[-0-9]+\(\$at\)
[ 	]*218: [A-Z0-9_]*LO[A-Z0-9_]*	.sbss.*
0+021c <[^>]*> lui	\$at,[-0-9x]+
[ 	]*21c: [A-Z0-9_]*HI[A-Z0-9_]*	.data.*
0+0220 <[^>]*> lw	\$a0,[-0-9]+\(\$at\)
[ 	]*220: [A-Z0-9_]*LO[A-Z0-9_]*	.data.*
0+0224 <[^>]*> lw	\$a1,[-0-9]+\(\$at\)
[ 	]*224: [A-Z0-9_]*LO[A-Z0-9_]*	.data.*
0+0228 <[^>]*> lui	\$at,[-0-9x]+
[ 	]*228: [A-Z0-9_]*HI[A-Z0-9_]*	big_external_data_label
0+022c <[^>]*> lw	\$a0,[-0-9]+\(\$at\)
[ 	]*22c: [A-Z0-9_]*LO[A-Z0-9_]*	big_external_data_label
0+0230 <[^>]*> lw	\$a1,[-0-9]+\(\$at\)
[ 	]*230: [A-Z0-9_]*LO[A-Z0-9_]*	big_external_data_label
0+0234 <[^>]*> lui	\$at,[-0-9x]+
[ 	]*234: [A-Z0-9_]*HI[A-Z0-9_]*	small_external_data_label
0+0238 <[^>]*> lw	\$a0,[-0-9]+\(\$at\)
[ 	]*238: [A-Z0-9_]*LO[A-Z0-9_]*	small_external_data_label
0+023c <[^>]*> lw	\$a1,[-0-9]+\(\$at\)
[ 	]*23c: [A-Z0-9_]*LO[A-Z0-9_]*	small_external_data_label
0+0240 <[^>]*> lui	\$at,[-0-9x]+
[ 	]*240: [A-Z0-9_]*HI[A-Z0-9_]*	big_external_common
0+0244 <[^>]*> lw	\$a0,[-0-9]+\(\$at\)
[ 	]*244: [A-Z0-9_]*LO[A-Z0-9_]*	big_external_common
0+0248 <[^>]*> lw	\$a1,[-0-9]+\(\$at\)
[ 	]*248: [A-Z0-9_]*LO[A-Z0-9_]*	big_external_common
0+024c <[^>]*> lui	\$at,[-0-9x]+
[ 	]*24c: [A-Z0-9_]*HI[A-Z0-9_]*	small_external_common
0+0250 <[^>]*> lw	\$a0,[-0-9]+\(\$at\)
[ 	]*250: [A-Z0-9_]*LO[A-Z0-9_]*	small_external_common
0+0254 <[^>]*> lw	\$a1,[-0-9]+\(\$at\)
[ 	]*254: [A-Z0-9_]*LO[A-Z0-9_]*	small_external_common
0+0258 <[^>]*> lui	\$at,[-0-9x]+
[ 	]*258: [A-Z0-9_]*HI[A-Z0-9_]*	.bss.*
0+025c <[^>]*> lw	\$a0,[-0-9]+\(\$at\)
[ 	]*25c: [A-Z0-9_]*LO[A-Z0-9_]*	.bss.*
0+0260 <[^>]*> lw	\$a1,[-0-9]+\(\$at\)
[ 	]*260: [A-Z0-9_]*LO[A-Z0-9_]*	.bss.*
0+0264 <[^>]*> lui	\$at,[-0-9x]+
[ 	]*264: [A-Z0-9_]*HI[A-Z0-9_]*	.sbss.*
0+0268 <[^>]*> lw	\$a0,[-0-9]+\(\$at\)
[ 	]*268: [A-Z0-9_]*LO[A-Z0-9_]*	.sbss.*
0+026c <[^>]*> lw	\$a1,[-0-9]+\(\$at\)
[ 	]*26c: [A-Z0-9_]*LO[A-Z0-9_]*	.sbss.*
0+0270 <[^>]*> lui	\$at,0x0
[ 	]*270: [A-Z0-9_]*HI[A-Z0-9_]*	.data.*
0+0274 <[^>]*> addu	\$at,\$a1,\$at
0+0278 <[^>]*> lw	\$a0,[-0-9]+\(\$at\)
[ 	]*278: [A-Z0-9_]*LO[A-Z0-9_]*	.data.*
0+027c <[^>]*> lw	\$a1,[-0-9]+\(\$at\)
[ 	]*27c: [A-Z0-9_]*LO[A-Z0-9_]*	.data.*
0+0280 <[^>]*> lui	\$at,0x0
[ 	]*280: [A-Z0-9_]*HI[A-Z0-9_]*	big_external_data_label
0+0284 <[^>]*> addu	\$at,\$a1,\$at
0+0288 <[^>]*> lw	\$a0,0\(\$at\)
[ 	]*288: [A-Z0-9_]*LO[A-Z0-9_]*	big_external_data_label
0+028c <[^>]*> lw	\$a1,[-0-9]+\(\$at\)
[ 	]*28c: [A-Z0-9_]*LO[A-Z0-9_]*	big_external_data_label
0+0290 <[^>]*> nop
0+0294 <[^>]*> addu	\$at,\$a1,\$gp
0+0298 <[^>]*> lw	\$a0,0\(\$at\)
[ 	]*298: [A-Z0-9_]*GPREL[A-Z0-9_]*	small_external_data_label
0+029c <[^>]*> lw	\$a1,[-0-9]+\(\$at\)
[ 	]*29c: [A-Z0-9_]*GPREL[A-Z0-9_]*	small_external_data_label
0+02a0 <[^>]*> lui	\$at,0x0
[ 	]*2a0: [A-Z0-9_]*HI[A-Z0-9_]*	big_external_common
0+02a4 <[^>]*> addu	\$at,\$a1,\$at
0+02a8 <[^>]*> lw	\$a0,0\(\$at\)
[ 	]*2a8: [A-Z0-9_]*LO[A-Z0-9_]*	big_external_common
0+02ac <[^>]*> lw	\$a1,[-0-9]+\(\$at\)
[ 	]*2ac: [A-Z0-9_]*LO[A-Z0-9_]*	big_external_common
0+02b0 <[^>]*> nop
0+02b4 <[^>]*> addu	\$at,\$a1,\$gp
0+02b8 <[^>]*> lw	\$a0,0\(\$at\)
[ 	]*2b8: [A-Z0-9_]*GPREL[A-Z0-9_]*	small_external_common
0+02bc <[^>]*> lw	\$a1,[-0-9]+\(\$at\)
[ 	]*2bc: [A-Z0-9_]*GPREL[A-Z0-9_]*	small_external_common
0+02c0 <[^>]*> lui	\$at,0x0
[ 	]*2c0: [A-Z0-9_]*HI[A-Z0-9_]*	.bss.*
0+02c4 <[^>]*> addu	\$at,\$a1,\$at
0+02c8 <[^>]*> lw	\$a0,[-0-9]+\(\$at\)
[ 	]*2c8: [A-Z0-9_]*LO[A-Z0-9_]*	.bss.*
0+02cc <[^>]*> lw	\$a1,[-0-9]+\(\$at\)
[ 	]*2cc: [A-Z0-9_]*LO[A-Z0-9_]*	.bss.*
0+02d0 <[^>]*> nop
0+02d4 <[^>]*> addu	\$at,\$a1,\$gp
0+02d8 <[^>]*> lw	\$a0,[-0-9]+\(\$at\)
[ 	]*2d8: [A-Z0-9_]*GPREL[A-Z0-9_]*	.sbss.*
0+02dc <[^>]*> lw	\$a1,[-0-9]+\(\$at\)
[ 	]*2dc: [A-Z0-9_]*GPREL[A-Z0-9_]*	.sbss.*
0+02e0 <[^>]*> lui	\$at,0x0
[ 	]*2e0: [A-Z0-9_]*HI[A-Z0-9_]*	.data.*
0+02e4 <[^>]*> addu	\$at,\$a1,\$at
0+02e8 <[^>]*> lw	\$a0,[-0-9]+\(\$at\)
[ 	]*2e8: [A-Z0-9_]*LO[A-Z0-9_]*	.data.*
0+02ec <[^>]*> lw	\$a1,[-0-9]+\(\$at\)
[ 	]*2ec: [A-Z0-9_]*LO[A-Z0-9_]*	.data.*
0+02f0 <[^>]*> lui	\$at,0x0
[ 	]*2f0: [A-Z0-9_]*HI[A-Z0-9_]*	big_external_data_label
0+02f4 <[^>]*> addu	\$at,\$a1,\$at
0+02f8 <[^>]*> lw	\$a0,[-0-9]+\(\$at\)
[ 	]*2f8: [A-Z0-9_]*LO[A-Z0-9_]*	big_external_data_label
0+02fc <[^>]*> lw	\$a1,[-0-9]+\(\$at\)
[ 	]*2fc: [A-Z0-9_]*LO[A-Z0-9_]*	big_external_data_label
0+0300 <[^>]*> nop
0+0304 <[^>]*> addu	\$at,\$a1,\$gp
0+0308 <[^>]*> lw	\$a0,1\(\$at\)
[ 	]*308: [A-Z0-9_]*GPREL[A-Z0-9_]*	small_external_data_label
0+030c <[^>]*> lw	\$a1,5\(\$at\)
[ 	]*30c: [A-Z0-9_]*GPREL[A-Z0-9_]*	small_external_data_label
0+0310 <[^>]*> lui	\$at,0x0
[ 	]*310: [A-Z0-9_]*HI[A-Z0-9_]*	big_external_common
0+0314 <[^>]*> addu	\$at,\$a1,\$at
0+0318 <[^>]*> lw	\$a0,[-0-9]+\(\$at\)
[ 	]*318: [A-Z0-9_]*LO[A-Z0-9_]*	big_external_common
0+031c <[^>]*> lw	\$a1,[-0-9]+\(\$at\)
[ 	]*31c: [A-Z0-9_]*LO[A-Z0-9_]*	big_external_common
0+0320 <[^>]*> nop
0+0324 <[^>]*> addu	\$at,\$a1,\$gp
0+0328 <[^>]*> lw	\$a0,1\(\$at\)
[ 	]*328: [A-Z0-9_]*GPREL[A-Z0-9_]*	small_external_common
0+032c <[^>]*> lw	\$a1,5\(\$at\)
[ 	]*32c: [A-Z0-9_]*GPREL[A-Z0-9_]*	small_external_common
0+0330 <[^>]*> lui	\$at,0x0
[ 	]*330: [A-Z0-9_]*HI[A-Z0-9_]*	.bss.*
0+0334 <[^>]*> addu	\$at,\$a1,\$at
0+0338 <[^>]*> lw	\$a0,[-0-9]+\(\$at\)
[ 	]*338: [A-Z0-9_]*LO[A-Z0-9_]*	.bss.*
0+033c <[^>]*> lw	\$a1,[-0-9]+\(\$at\)
[ 	]*33c: [A-Z0-9_]*LO[A-Z0-9_]*	.bss.*
0+0340 <[^>]*> nop
0+0344 <[^>]*> addu	\$at,\$a1,\$gp
0+0348 <[^>]*> lw	\$a0,[-0-9]+\(\$at\)
[ 	]*348: [A-Z0-9_]*GPREL[A-Z0-9_]*	.sbss.*
0+034c <[^>]*> lw	\$a1,[-0-9]+\(\$at\)
[ 	]*34c: [A-Z0-9_]*GPREL[A-Z0-9_]*	.sbss.*
0+0350 <[^>]*> lui	\$at,[-0-9x]+
[ 	]*350: [A-Z0-9_]*HI[A-Z0-9_]*	.data.*
0+0354 <[^>]*> addu	\$at,\$a1,\$at
0+0358 <[^>]*> lw	\$a0,[-0-9]+\(\$at\)
[ 	]*358: [A-Z0-9_]*LO[A-Z0-9_]*	.data.*
0+035c <[^>]*> lw	\$a1,[-0-9]+\(\$at\)
[ 	]*35c: [A-Z0-9_]*LO[A-Z0-9_]*	.data.*
0+0360 <[^>]*> lui	\$at,[-0-9x]+
[ 	]*360: [A-Z0-9_]*HI[A-Z0-9_]*	big_external_data_label
0+0364 <[^>]*> addu	\$at,\$a1,\$at
0+0368 <[^>]*> lw	\$a0,[-0-9]+\(\$at\)
[ 	]*368: [A-Z0-9_]*LO[A-Z0-9_]*	big_external_data_label
0+036c <[^>]*> lw	\$a1,[-0-9]+\(\$at\)
[ 	]*36c: [A-Z0-9_]*LO[A-Z0-9_]*	big_external_data_label
0+0370 <[^>]*> lui	\$at,[-0-9x]+
[ 	]*370: [A-Z0-9_]*HI[A-Z0-9_]*	small_external_data_label
0+0374 <[^>]*> addu	\$at,\$a1,\$at
0+0378 <[^>]*> lw	\$a0,[-0-9]+\(\$at\)
[ 	]*378: [A-Z0-9_]*LO[A-Z0-9_]*	small_external_data_label
0+037c <[^>]*> lw	\$a1,[-0-9]+\(\$at\)
[ 	]*37c: [A-Z0-9_]*LO[A-Z0-9_]*	small_external_data_label
0+0380 <[^>]*> lui	\$at,[-0-9x]+
[ 	]*380: [A-Z0-9_]*HI[A-Z0-9_]*	big_external_common
0+0384 <[^>]*> addu	\$at,\$a1,\$at
0+0388 <[^>]*> lw	\$a0,[-0-9]+\(\$at\)
[ 	]*388: [A-Z0-9_]*LO[A-Z0-9_]*	big_external_common
0+038c <[^>]*> lw	\$a1,[-0-9]+\(\$at\)
[ 	]*38c: [A-Z0-9_]*LO[A-Z0-9_]*	big_external_common
0+0390 <[^>]*> lui	\$at,[-0-9x]+
[ 	]*390: [A-Z0-9_]*HI[A-Z0-9_]*	small_external_common
0+0394 <[^>]*> addu	\$at,\$a1,\$at
0+0398 <[^>]*> lw	\$a0,[-0-9]+\(\$at\)
[ 	]*398: [A-Z0-9_]*LO[A-Z0-9_]*	small_external_common
0+039c <[^>]*> lw	\$a1,[-0-9]+\(\$at\)
[ 	]*39c: [A-Z0-9_]*LO[A-Z0-9_]*	small_external_common
0+03a0 <[^>]*> lui	\$at,[-0-9x]+
[ 	]*3a0: [A-Z0-9_]*HI[A-Z0-9_]*	.bss.*
0+03a4 <[^>]*> addu	\$at,\$a1,\$at
0+03a8 <[^>]*> lw	\$a0,[-0-9]+\(\$at\)
[ 	]*3a8: [A-Z0-9_]*LO[A-Z0-9_]*	.bss.*
0+03ac <[^>]*> lw	\$a1,[-0-9]+\(\$at\)
[ 	]*3ac: [A-Z0-9_]*LO[A-Z0-9_]*	.bss.*
0+03b0 <[^>]*> lui	\$at,[-0-9x]+
[ 	]*3b0: [A-Z0-9_]*HI[A-Z0-9_]*	.sbss.*
0+03b4 <[^>]*> addu	\$at,\$a1,\$at
0+03b8 <[^>]*> lw	\$a0,[-0-9]+\(\$at\)
[ 	]*3b8: [A-Z0-9_]*LO[A-Z0-9_]*	.sbss.*
0+03bc <[^>]*> lw	\$a1,[-0-9]+\(\$at\)
[ 	]*3bc: [A-Z0-9_]*LO[A-Z0-9_]*	.sbss.*
0+03c0 <[^>]*> lui	\$at,0x0
[ 	]*3c0: [A-Z0-9_]*HI[A-Z0-9_]*	.data.*
0+03c4 <[^>]*> addu	\$at,\$a1,\$at
0+03c8 <[^>]*> lw	\$a0,[-0-9]+\(\$at\)
[ 	]*3c8: [A-Z0-9_]*LO[A-Z0-9_]*	.data.*
0+03cc <[^>]*> lw	\$a1,[-0-9]+\(\$at\)
[ 	]*3cc: [A-Z0-9_]*LO[A-Z0-9_]*	.data.*
0+03d0 <[^>]*> lui	\$at,0x0
[ 	]*3d0: [A-Z0-9_]*HI[A-Z0-9_]*	big_external_data_label
0+03d4 <[^>]*> addu	\$at,\$a1,\$at
0+03d8 <[^>]*> lw	\$a0,[-0-9]+\(\$at\)
[ 	]*3d8: [A-Z0-9_]*LO[A-Z0-9_]*	big_external_data_label
0+03dc <[^>]*> lw	\$a1,[-0-9]+\(\$at\)
[ 	]*3dc: [A-Z0-9_]*LO[A-Z0-9_]*	big_external_data_label
0+03e0 <[^>]*> lui	\$at,0x0
[ 	]*3e0: [A-Z0-9_]*HI[A-Z0-9_]*	small_external_data_label
0+03e4 <[^>]*> addu	\$at,\$a1,\$at
0+03e8 <[^>]*> lw	\$a0,[-0-9]+\(\$at\)
[ 	]*3e8: [A-Z0-9_]*LO[A-Z0-9_]*	small_external_data_label
0+03ec <[^>]*> lw	\$a1,[-0-9]+\(\$at\)
[ 	]*3ec: [A-Z0-9_]*LO[A-Z0-9_]*	small_external_data_label
0+03f0 <[^>]*> lui	\$at,0x0
[ 	]*3f0: [A-Z0-9_]*HI[A-Z0-9_]*	big_external_common
0+03f4 <[^>]*> addu	\$at,\$a1,\$at
0+03f8 <[^>]*> lw	\$a0,[-0-9]+\(\$at\)
[ 	]*3f8: [A-Z0-9_]*LO[A-Z0-9_]*	big_external_common
0+03fc <[^>]*> lw	\$a1,[-0-9]+\(\$at\)
[ 	]*3fc: [A-Z0-9_]*LO[A-Z0-9_]*	big_external_common
0+0400 <[^>]*> lui	\$at,0x0
[ 	]*400: [A-Z0-9_]*HI[A-Z0-9_]*	small_external_common
0+0404 <[^>]*> addu	\$at,\$a1,\$at
0+0408 <[^>]*> lw	\$a0,[-0-9]+\(\$at\)
[ 	]*408: [A-Z0-9_]*LO[A-Z0-9_]*	small_external_common
0+040c <[^>]*> lw	\$a1,[-0-9]+\(\$at\)
[ 	]*40c: [A-Z0-9_]*LO[A-Z0-9_]*	small_external_common
0+0410 <[^>]*> lui	\$at,0x0
[ 	]*410: [A-Z0-9_]*HI[A-Z0-9_]*	.bss.*
0+0414 <[^>]*> addu	\$at,\$a1,\$at
0+0418 <[^>]*> lw	\$a0,[-0-9]+\(\$at\)
[ 	]*418: [A-Z0-9_]*LO[A-Z0-9_]*	.bss.*
0+041c <[^>]*> lw	\$a1,[-0-9]+\(\$at\)
[ 	]*41c: [A-Z0-9_]*LO[A-Z0-9_]*	.bss.*
0+0420 <[^>]*> lui	\$at,0x0
[ 	]*420: [A-Z0-9_]*HI[A-Z0-9_]*	.sbss.*
0+0424 <[^>]*> addu	\$at,\$a1,\$at
0+0428 <[^>]*> lw	\$a0,[-0-9]+\(\$at\)
[ 	]*428: [A-Z0-9_]*LO[A-Z0-9_]*	.sbss.*
0+042c <[^>]*> lw	\$a1,[-0-9]+\(\$at\)
[ 	]*42c: [A-Z0-9_]*LO[A-Z0-9_]*	.sbss.*
0+0430 <[^>]*> lui	\$at,[-0-9x]+
[ 	]*430: [A-Z0-9_]*HI[A-Z0-9_]*	.data.*
0+0434 <[^>]*> addu	\$at,\$a1,\$at
0+0438 <[^>]*> lw	\$a0,[-0-9]+\(\$at\)
[ 	]*438: [A-Z0-9_]*LO[A-Z0-9_]*	.data.*
0+043c <[^>]*> lw	\$a1,[-0-9]+\(\$at\)
[ 	]*43c: [A-Z0-9_]*LO[A-Z0-9_]*	.data.*
0+0440 <[^>]*> lui	\$at,[-0-9x]+
[ 	]*440: [A-Z0-9_]*HI[A-Z0-9_]*	big_external_data_label
0+0444 <[^>]*> addu	\$at,\$a1,\$at
0+0448 <[^>]*> lw	\$a0,0\(\$at\)
[ 	]*448: [A-Z0-9_]*LO[A-Z0-9_]*	big_external_data_label
0+044c <[^>]*> lw	\$a1,[-0-9]+\(\$at\)
[ 	]*44c: [A-Z0-9_]*LO[A-Z0-9_]*	big_external_data_label
0+0450 <[^>]*> lui	\$at,[-0-9x]+
[ 	]*450: [A-Z0-9_]*HI[A-Z0-9_]*	small_external_data_label
0+0454 <[^>]*> addu	\$at,\$a1,\$at
0+0458 <[^>]*> lw	\$a0,0\(\$at\)
[ 	]*458: [A-Z0-9_]*LO[A-Z0-9_]*	small_external_data_label
0+045c <[^>]*> lw	\$a1,[-0-9]+\(\$at\)
[ 	]*45c: [A-Z0-9_]*LO[A-Z0-9_]*	small_external_data_label
0+0460 <[^>]*> lui	\$at,[-0-9x]+
[ 	]*460: [A-Z0-9_]*HI[A-Z0-9_]*	big_external_common
0+0464 <[^>]*> addu	\$at,\$a1,\$at
0+0468 <[^>]*> lw	\$a0,0\(\$at\)
[ 	]*468: [A-Z0-9_]*LO[A-Z0-9_]*	big_external_common
0+046c <[^>]*> lw	\$a1,[-0-9]+\(\$at\)
[ 	]*46c: [A-Z0-9_]*LO[A-Z0-9_]*	big_external_common
0+0470 <[^>]*> lui	\$at,[-0-9x]+
[ 	]*470: [A-Z0-9_]*HI[A-Z0-9_]*	small_external_common
0+0474 <[^>]*> addu	\$at,\$a1,\$at
0+0478 <[^>]*> lw	\$a0,0\(\$at\)
[ 	]*478: [A-Z0-9_]*LO[A-Z0-9_]*	small_external_common
0+047c <[^>]*> lw	\$a1,[-0-9]+\(\$at\)
[ 	]*47c: [A-Z0-9_]*LO[A-Z0-9_]*	small_external_common
0+0480 <[^>]*> lui	\$at,[-0-9x]+
[ 	]*480: [A-Z0-9_]*HI[A-Z0-9_]*	.bss.*
0+0484 <[^>]*> addu	\$at,\$a1,\$at
0+0488 <[^>]*> lw	\$a0,[-0-9]+\(\$at\)
[ 	]*488: [A-Z0-9_]*LO[A-Z0-9_]*	.bss.*
0+048c <[^>]*> lw	\$a1,[-0-9]+\(\$at\)
[ 	]*48c: [A-Z0-9_]*LO[A-Z0-9_]*	.bss.*
0+0490 <[^>]*> lui	\$at,[-0-9x]+
[ 	]*490: [A-Z0-9_]*HI[A-Z0-9_]*	.sbss.*
0+0494 <[^>]*> addu	\$at,\$a1,\$at
0+0498 <[^>]*> lw	\$a0,[-0-9]+\(\$at\)
[ 	]*498: [A-Z0-9_]*LO[A-Z0-9_]*	.sbss.*
0+049c <[^>]*> lw	\$a1,[-0-9]+\(\$at\)
[ 	]*49c: [A-Z0-9_]*LO[A-Z0-9_]*	.sbss.*
0+04a0 <[^>]*> lui	\$at,[-0-9x]+
[ 	]*4a0: [A-Z0-9_]*HI[A-Z0-9_]*	.data.*
0+04a4 <[^>]*> addu	\$at,\$a1,\$at
0+04a8 <[^>]*> lw	\$a0,[-0-9]+\(\$at\)
[ 	]*4a8: [A-Z0-9_]*LO[A-Z0-9_]*	.data.*
0+04ac <[^>]*> lw	\$a1,[-0-9]+\(\$at\)
[ 	]*4ac: [A-Z0-9_]*LO[A-Z0-9_]*	.data.*
0+04b0 <[^>]*> lui	\$at,[-0-9x]+
[ 	]*4b0: [A-Z0-9_]*HI[A-Z0-9_]*	big_external_data_label
0+04b4 <[^>]*> addu	\$at,\$a1,\$at
0+04b8 <[^>]*> lw	\$a0,[-0-9]+\(\$at\)
[ 	]*4b8: [A-Z0-9_]*LO[A-Z0-9_]*	big_external_data_label
0+04bc <[^>]*> lw	\$a1,[-0-9]+\(\$at\)
[ 	]*4bc: [A-Z0-9_]*LO[A-Z0-9_]*	big_external_data_label
0+04c0 <[^>]*> lui	\$at,[-0-9x]+
[ 	]*4c0: [A-Z0-9_]*HI[A-Z0-9_]*	small_external_data_label
0+04c4 <[^>]*> addu	\$at,\$a1,\$at
0+04c8 <[^>]*> lw	\$a0,[-0-9]+\(\$at\)
[ 	]*4c8: [A-Z0-9_]*LO[A-Z0-9_]*	small_external_data_label
0+04cc <[^>]*> lw	\$a1,[-0-9]+\(\$at\)
[ 	]*4cc: [A-Z0-9_]*LO[A-Z0-9_]*	small_external_data_label
0+04d0 <[^>]*> lui	\$at,[-0-9x]+
[ 	]*4d0: [A-Z0-9_]*HI[A-Z0-9_]*	big_external_common
0+04d4 <[^>]*> addu	\$at,\$a1,\$at
0+04d8 <[^>]*> lw	\$a0,[-0-9]+\(\$at\)
[ 	]*4d8: [A-Z0-9_]*LO[A-Z0-9_]*	big_external_common
0+04dc <[^>]*> lw	\$a1,[-0-9]+\(\$at\)
[ 	]*4dc: [A-Z0-9_]*LO[A-Z0-9_]*	big_external_common
0+04e0 <[^>]*> lui	\$at,[-0-9x]+
[ 	]*4e0: [A-Z0-9_]*HI[A-Z0-9_]*	small_external_common
0+04e4 <[^>]*> addu	\$at,\$a1,\$at
0+04e8 <[^>]*> lw	\$a0,[-0-9]+\(\$at\)
[ 	]*4e8: [A-Z0-9_]*LO[A-Z0-9_]*	small_external_common
0+04ec <[^>]*> lw	\$a1,[-0-9]+\(\$at\)
[ 	]*4ec: [A-Z0-9_]*LO[A-Z0-9_]*	small_external_common
0+04f0 <[^>]*> lui	\$at,[-0-9x]+
[ 	]*4f0: [A-Z0-9_]*HI[A-Z0-9_]*	.bss.*
0+04f4 <[^>]*> addu	\$at,\$a1,\$at
0+04f8 <[^>]*> lw	\$a0,[-0-9]+\(\$at\)
[ 	]*4f8: [A-Z0-9_]*LO[A-Z0-9_]*	.bss.*
0+04fc <[^>]*> lw	\$a1,[-0-9]+\(\$at\)
[ 	]*4fc: [A-Z0-9_]*LO[A-Z0-9_]*	.bss.*
0+0500 <[^>]*> lui	\$at,[-0-9x]+
[ 	]*500: [A-Z0-9_]*HI[A-Z0-9_]*	.sbss.*
0+0504 <[^>]*> addu	\$at,\$a1,\$at
0+0508 <[^>]*> lw	\$a0,[-0-9]+\(\$at\)
[ 	]*508: [A-Z0-9_]*LO[A-Z0-9_]*	.sbss.*
0+050c <[^>]*> lw	\$a1,[-0-9]+\(\$at\)
[ 	]*50c: [A-Z0-9_]*LO[A-Z0-9_]*	.sbss.*
0+0510 <[^>]*> lwc1	\$f[45],0\(\$zero\)
0+0514 <[^>]*> lwc1	\$f[45],4\(\$zero\)
0+0518 <[^>]*> lwc1	\$f[45],1\(\$zero\)
0+051c <[^>]*> lwc1	\$f[45],5\(\$zero\)
0+0520 <[^>]*> lui	\$at,0x1
0+0524 <[^>]*> lwc1	\$f[45],-32768\(\$at\)
0+0528 <[^>]*> lwc1	\$f[45],-32764\(\$at\)
0+052c <[^>]*> lwc1	\$f[45],-32768\(\$zero\)
0+0530 <[^>]*> lwc1	\$f[45],-32764\(\$zero\)
0+0534 <[^>]*> lwc1	\$f[45],0\(\$a1\)
0+0538 <[^>]*> lwc1	\$f[45],4\(\$a1\)
0+053c <[^>]*> lwc1	\$f[45],1\(\$a1\)
0+0540 <[^>]*> lwc1	\$f[45],5\(\$a1\)
0+0544 <[^>]*> lui	\$at,0x1
0+0548 <[^>]*> addu	\$at,\$a1,\$at
0+054c <[^>]*> lwc1	\$f[45],-32768\(\$at\)
0+0550 <[^>]*> lwc1	\$f[45],-32764\(\$at\)
0+0554 <[^>]*> lwc1	\$f[45],-32768\(\$a1\)
0+0558 <[^>]*> lwc1	\$f[45],-32764\(\$a1\)
0+055c <[^>]*> lui	\$at,[-0-9x]+
[ 	]*55c: [A-Z0-9_]*HI[A-Z0-9_]*	small_external_common
0+0560 <[^>]*> addu	\$at,\$a1,\$at
0+0564 <[^>]*> lwc1	\$f[45],[-0-9]+\(\$at\)
[ 	]*564: [A-Z0-9_]*LO[A-Z0-9_]*	small_external_common
0+0568 <[^>]*> lwc1	\$f[45],[-0-9]+\(\$at\)
[ 	]*568: [A-Z0-9_]*LO[A-Z0-9_]*	small_external_common
0+056c <[^>]*> nop
0+0570 <[^>]*> swc1	\$f[45],0\(\$zero\)
0+0574 <[^>]*> swc1	\$f[45],4\(\$zero\)
0+0578 <[^>]*> swc1	\$f[45],1\(\$zero\)
0+057c <[^>]*> swc1	\$f[45],5\(\$zero\)
0+0580 <[^>]*> lui	\$at,0x1
0+0584 <[^>]*> swc1	\$f[45],-32768\(\$at\)
0+0588 <[^>]*> swc1	\$f[45],-32764\(\$at\)
0+058c <[^>]*> swc1	\$f[45],-32768\(\$zero\)
0+0590 <[^>]*> swc1	\$f[45],-32764\(\$zero\)
0+0594 <[^>]*> swc1	\$f[45],0\(\$a1\)
0+0598 <[^>]*> swc1	\$f[45],4\(\$a1\)
0+059c <[^>]*> swc1	\$f[45],1\(\$a1\)
0+05a0 <[^>]*> swc1	\$f[45],5\(\$a1\)
0+05a4 <[^>]*> lui	\$at,0x1
0+05a8 <[^>]*> addu	\$at,\$a1,\$at
0+05ac <[^>]*> swc1	\$f[45],-32768\(\$at\)
0+05b0 <[^>]*> swc1	\$f[45],-32764\(\$at\)
0+05b4 <[^>]*> swc1	\$f[45],-32768\(\$a1\)
0+05b8 <[^>]*> swc1	\$f[45],-32764\(\$a1\)
0+05bc <[^>]*> lui	\$at,[-0-9x]+
[ 	]*5bc: [A-Z0-9_]*HI[A-Z0-9_]*	big_external_common
0+05c0 <[^>]*> addu	\$at,\$a1,\$at
0+05c4 <[^>]*> swc1	\$f[45],[-0-9]+\(\$at\)
[ 	]*5c4: [A-Z0-9_]*LO[A-Z0-9_]*	big_external_common
0+05c8 <[^>]*> swc1	\$f[45],[-0-9]+\(\$at\)
[ 	]*5c8: [A-Z0-9_]*LO[A-Z0-9_]*	big_external_common
0+05cc <[^>]*> sw	\$a0,0\(\$zero\)
0+05d0 <[^>]*> sw	\$a1,4\(\$zero\)
0+05d4 <[^>]*> lui	\$a0,[-0-9x]+
[ 	]*5d4: [A-Z0-9_]*HI[A-Z0-9_]*	.bss.*
0+05d8 <[^>]*> daddu	\$a0,\$a0,\$a1
0+05dc <[^>]*> ld	\$a0,[-0-9]+\(\$a0\)
[ 	]*5dc: [A-Z0-9_]*LO[A-Z0-9_]*	.bss.*
0+05e0 <[^>]*> lui	\$at,[-0-9x]+
[ 	]*5e0: [A-Z0-9_]*HI[A-Z0-9_]*	.sbss.*
0+05e4 <[^>]*> daddu	\$at,\$at,\$a1
0+05e8 <[^>]*> sd	\$a0,[-0-9]+\(\$at\)
[ 	]*5e8: [A-Z0-9_]*LO[A-Z0-9_]*	.sbss.*
0+05ec <[^>]*> nop
