#include "test.h"
 one_line_type j1_vec[] = {
{64, 0,123,__LINE__, 0xbfdfe3f7, 0xc98d2cad, 0xbff33333, 0x33333333},			/* -0.49828=f(-1.20000)*/
{64, 0,123,__LINE__, 0xbfdfb9be, 0x60162ce1, 0xbff30a3d, 0x70a3d70a},			/* -0.49571=f(-1.19000)*/
{62, 0,123,__LINE__, 0xbfdf8eec, 0x64ca92ed, 0xbff2e147, 0xae147ae1},			/* -0.49309=f(-1.18000)*/
{64, 0,123,__LINE__, 0xbfdf6382, 0x95db2d21, 0xbff2b851, 0xeb851eb8},			/* -0.49044=f(-1.17000)*/
{64, 0,123,__LINE__, 0xbfdf3781, 0xb4ad13e2, 0xbff28f5c, 0x28f5c28f},			/* -0.48776=f(-1.16000)*/
{64, 0,123,__LINE__, 0xbfdf0aea, 0x85d5bf16, 0xbff26666, 0x66666666},			/* -0.48504=f(-1.15000)*/
{63, 0,123,__LINE__, 0xbfdeddbd, 0xd1170952, 0xbff23d70, 0xa3d70a3d},			/* -0.48228=f(-1.14000)*/
{63, 0,123,__LINE__, 0xbfdeaffc, 0x615b2106, 0xbff2147a, 0xe147ae14},			/* -0.47949=f(-1.13000)*/
{63, 0,123,__LINE__, 0xbfde81a7, 0x04b0679a, 0xbff1eb85, 0x1eb851eb},			/* -0.47666=f(-1.12000)*/
{64, 0,123,__LINE__, 0xbfde52be, 0x8c453eac, 0xbff1c28f, 0x5c28f5c2},			/* -0.47380=f(-1.11000)*/
{64, 0,123,__LINE__, 0xbfde2343, 0xcc63c37b, 0xbff19999, 0x99999999},			/* -0.47090=f(-1.10000)*/
{63, 0,123,__LINE__, 0xbfddf337, 0x9c6d7898, 0xbff170a3, 0xd70a3d70},			/* -0.46796=f(-1.09000)*/
{64, 0,123,__LINE__, 0xbfddc29a, 0xd6d6ddf8, 0xbff147ae, 0x147ae147},			/* -0.46500=f(-1.08000)*/
{64, 0,123,__LINE__, 0xbfdd916e, 0x5922f77c, 0xbff11eb8, 0x51eb851e},			/* -0.46200=f(-1.07000)*/
{64, 0,123,__LINE__, 0xbfdd5fb3, 0x03dec20f, 0xbff0f5c2, 0x8f5c28f5},			/* -0.45896=f(-1.06000)*/
{64, 0,123,__LINE__, 0xbfdd2d69, 0xba9c976a, 0xbff0cccc, 0xcccccccc},			/* -0.45589=f(-1.05000)*/
{64, 0,123,__LINE__, 0xbfdcfa93, 0x63ef809a, 0xbff0a3d7, 0x0a3d70a3},			/* -0.45279=f(-1.04000)*/
{61, 0,123,__LINE__, 0xbfdcc730, 0xe966776b, 0xbff07ae1, 0x47ae147a},			/* -0.44965=f(-1.03000)*/
{64, 0,123,__LINE__, 0xbfdc9343, 0x378796ca, 0xbff051eb, 0x851eb851},			/* -0.44648=f(-1.02000)*/
{63, 0,123,__LINE__, 0xbfdc5ecb, 0x3dcb3a36, 0xbff028f5, 0xc28f5c28},			/* -0.44328=f(-1.01000)*/
{63, 0,123,__LINE__, 0xbfdc29c9, 0xee970c6b, 0xbfefffff, 0xfffffffe},			/* -0.44005=f(-0.01000)*/
{64, 0,123,__LINE__, 0xbfdbf440, 0x3f39054b, 0xbfefae14, 0x7ae147ac},			/* -0.43678=f(-0.99000)*/
{64, 0,123,__LINE__, 0xbfdbbe2f, 0x27e2573a, 0xbfef5c28, 0xf5c28f5a},			/* -0.43348=f(-0.98000)*/
{61, 0,123,__LINE__, 0xbfdb8797, 0xa3a24bfc, 0xbfef0a3d, 0x70a3d708},			/* -0.43015=f(-0.97000)*/
{64, 0,123,__LINE__, 0xbfdb507a, 0xb061112a, 0xbfeeb851, 0xeb851eb6},			/* -0.42678=f(-0.96000)*/
{64, 0,123,__LINE__, 0xbfdb18d9, 0x4eda7472, 0xbfee6666, 0x66666664},			/* -0.42339=f(-0.95000)*/
{64, 0,123,__LINE__, 0xbfdae0b4, 0x82988faf, 0xbfee147a, 0xe147ae12},			/* -0.41996=f(-0.94000)*/
{62, 0,123,__LINE__, 0xbfdaa80d, 0x51ee64f6, 0xbfedc28f, 0x5c28f5c0},			/* -0.41650=f(-0.93000)*/
{62, 0,123,__LINE__, 0xbfda6ee4, 0xc5f26abe, 0xbfed70a3, 0xd70a3d6e},			/* -0.41301=f(-0.92000)*/
{64, 0,123,__LINE__, 0xbfda353b, 0xea790847, 0xbfed1eb8, 0x51eb851c},			/* -0.40949=f(-0.91000)*/
{64, 0,123,__LINE__, 0xbfd9fb13, 0xce0f024b, 0xbfeccccc, 0xccccccca},			/* -0.40594=f(-0.90000)*/
{64, 0,123,__LINE__, 0xbfd9c06d, 0x81f3d82b, 0xbfec7ae1, 0x47ae1478},			/* -0.40236=f(-0.89000)*/
{64, 0,123,__LINE__, 0xbfd9854a, 0x1a1411af, 0xbfec28f5, 0xc28f5c26},			/* -0.39876=f(-0.88000)*/
{63, 0,123,__LINE__, 0xbfd949aa, 0xad037d84, 0xbfebd70a, 0x3d70a3d4},			/* -0.39512=f(-0.87000)*/
{60, 0,123,__LINE__, 0xbfd90d90, 0x53f76088, 0xbfeb851e, 0xb851eb82},			/* -0.39145=f(-0.86000)*/
{62, 0,123,__LINE__, 0xbfd8d0fc, 0x2ac09606, 0xbfeb3333, 0x33333330},			/* -0.38775=f(-0.85000)*/
{63, 0,123,__LINE__, 0xbfd893ef, 0x4fc5a123, 0xbfeae147, 0xae147ade},			/* -0.38402=f(-0.84000)*/
{64, 0,123,__LINE__, 0xbfd8566a, 0xe3fcaf6b, 0xbfea8f5c, 0x28f5c28c},			/* -0.38027=f(-0.83000)*/
{63, 0,123,__LINE__, 0xbfd81870, 0x0ae58cce, 0xbfea3d70, 0xa3d70a3a},			/* -0.37649=f(-0.82000)*/
{64, 0,123,__LINE__, 0xbfd7d9ff, 0xea83890c, 0xbfe9eb85, 0x1eb851e8},			/* -0.37268=f(-0.81000)*/
{64, 0,123,__LINE__, 0xbfd79b1b, 0xab574eca, 0xbfe99999, 0x99999996},			/* -0.36884=f(-0.80000)*/
{64, 0,123,__LINE__, 0xbfd75bc4, 0x7858ac6c, 0xbfe947ae, 0x147ae144},			/* -0.36497=f(-0.79000)*/
{62, 0,123,__LINE__, 0xbfd71bfb, 0x7ef04ed6, 0xbfe8f5c2, 0x8f5c28f2},			/* -0.36108=f(-0.78000)*/
{62, 0,123,__LINE__, 0xbfd6dbc1, 0xeef16e2a, 0xbfe8a3d7, 0x0a3d70a0},			/* -0.35716=f(-0.77000)*/
{64, 0,123,__LINE__, 0xbfd69b18, 0xfa936cd0, 0xbfe851eb, 0x851eb84e},			/* -0.35321=f(-0.76000)*/
{64, 0,123,__LINE__, 0xbfd65a01, 0xd66b68b9, 0xbfe7ffff, 0xfffffffc},			/* -0.34924=f(-0.75000)*/
{61, 0,123,__LINE__, 0xbfd6187d, 0xb965bf24, 0xbfe7ae14, 0x7ae147aa},			/* -0.34524=f(-0.74000)*/
{64, 0,123,__LINE__, 0xbfd5d68d, 0xdcbf82f6, 0xbfe75c28, 0xf5c28f58},			/* -0.34122=f(-0.73000)*/
{64, 0,123,__LINE__, 0xbfd59433, 0x7bffe5ea, 0xbfe70a3d, 0x70a3d706},			/* -0.33717=f(-0.72000)*/
{64, 0,123,__LINE__, 0xbfd5516f, 0xd4f19487, 0xbfe6b851, 0xeb851eb4},			/* -0.33309=f(-0.71000)*/
{62, 0,123,__LINE__, 0xbfd50e44, 0x279c0541, 0xbfe66666, 0x66666662},			/* -0.32899=f(-0.70000)*/
{64, 0,123,__LINE__, 0xbfd4cab1, 0xb63cbabe, 0xbfe6147a, 0xe147ae10},			/* -0.32487=f(-0.69000)*/
{64, 0,123,__LINE__, 0xbfd486b9, 0xc540796d, 0xbfe5c28f, 0x5c28f5be},			/* -0.32072=f(-0.68000)*/
{64, 0,123,__LINE__, 0xbfd4425d, 0x9b3c70b3, 0xbfe570a3, 0xd70a3d6c},			/* -0.31655=f(-0.67000)*/
{62, 0,123,__LINE__, 0xbfd3fd9e, 0x80e757a9, 0xbfe51eb8, 0x51eb851a},			/* -0.31235=f(-0.66000)*/
{64, 0,123,__LINE__, 0xbfd3b87d, 0xc1127db7, 0xbfe4cccc, 0xccccccc8},			/* -0.30813=f(-0.65000)*/
{64, 0,123,__LINE__, 0xbfd372fc, 0xa8a2cf16, 0xbfe47ae1, 0x47ae1476},			/* -0.30389=f(-0.64000)*/
{64, 0,123,__LINE__, 0xbfd32d1c, 0x8689cd80, 0xbfe428f5, 0xc28f5c24},			/* -0.29962=f(-0.63000)*/
{63, 0,123,__LINE__, 0xbfd2e6de, 0xabbe7d19, 0xbfe3d70a, 0x3d70a3d2},			/* -0.29534=f(-0.62000)*/
{63, 0,123,__LINE__, 0xbfd2a044, 0x6b3645c9, 0xbfe3851e, 0xb851eb80},			/* -0.29103=f(-0.61000)*/
{64, 0,123,__LINE__, 0xbfd2594f, 0x19ddc92b, 0xbfe33333, 0x3333332e},			/* -0.28670=f(-0.60000)*/
{64, 0,123,__LINE__, 0xbfd21200, 0x0e91ad45, 0xbfe2e147, 0xae147adc},			/* -0.28234=f(-0.59000)*/
{64, 0,123,__LINE__, 0xbfd1ca58, 0xa2175c15, 0xbfe28f5c, 0x28f5c28a},			/* -0.27797=f(-0.58000)*/
{64, 0,123,__LINE__, 0xbfd1825a, 0x2f15b843, 0xbfe23d70, 0xa3d70a38},			/* -0.27358=f(-0.57000)*/
{64, 0,123,__LINE__, 0xbfd13a06, 0x120dc6fe, 0xbfe1eb85, 0x1eb851e6},			/* -0.26916=f(-0.56000)*/
{64, 0,123,__LINE__, 0xbfd0f15d, 0xa9534f4f, 0xbfe19999, 0x99999994},			/* -0.26473=f(-0.55000)*/
{64, 0,123,__LINE__, 0xbfd0a862, 0x55056ee9, 0xbfe147ae, 0x147ae142},			/* -0.26027=f(-0.54000)*/
{64, 0,123,__LINE__, 0xbfd05f15, 0x770724c1, 0xbfe0f5c2, 0x8f5c28f0},			/* -0.25580=f(-0.53000)*/
{64, 0,123,__LINE__, 0xbfd01578, 0x72f7d185, 0xbfe0a3d7, 0x0a3d709e},			/* -0.25131=f(-0.52000)*/
{64, 0,123,__LINE__, 0xbfcf9719, 0x5c575c35, 0xbfe051eb, 0x851eb84c},			/* -0.24679=f(-0.51000)*/
{64, 0,123,__LINE__, 0xbfcf02a7, 0x1f4870cc, 0xbfdfffff, 0xfffffff4},			/* -0.24226=f(-0.50000)*/
{63, 0,123,__LINE__, 0xbfce6d9d, 0x00112cd6, 0xbfdf5c28, 0xf5c28f50},			/* -0.23772=f(-0.49000)*/
{64, 0,123,__LINE__, 0xbfcdd7fd, 0xd33be007, 0xbfdeb851, 0xeb851eac},			/* -0.23315=f(-0.48000)*/
{64, 0,123,__LINE__, 0xbfcd41cc, 0x707f7ea2, 0xbfde147a, 0xe147ae08},			/* -0.22857=f(-0.47000)*/
{64, 0,123,__LINE__, 0xbfccab0b, 0xb2b0302a, 0xbfdd70a3, 0xd70a3d64},			/* -0.22396=f(-0.46000)*/
{64, 0,123,__LINE__, 0xbfcc13be, 0x77afcc47, 0xbfdccccc, 0xccccccc0},			/* -0.21935=f(-0.45000)*/
{64, 0,123,__LINE__, 0xbfcb7be7, 0xa05e461e, 0xbfdc28f5, 0xc28f5c1c},			/* -0.21471=f(-0.44000)*/
{64, 0,123,__LINE__, 0xbfcae38a, 0x108a068f, 0xbfdb851e, 0xb851eb78},			/* -0.21006=f(-0.43000)*/
{64, 0,123,__LINE__, 0xbfca4aa8, 0xaee035a2, 0xbfdae147, 0xae147ad4},			/* -0.20540=f(-0.42000)*/
{64, 0,123,__LINE__, 0xbfc9b146, 0x64dcf383, 0xbfda3d70, 0xa3d70a30},			/* -0.20072=f(-0.41000)*/
{64, 0,123,__LINE__, 0xbfc91766, 0x1ebb816a, 0xbfd99999, 0x9999998c},			/* -0.19602=f(-0.40000)*/
{63, 0,123,__LINE__, 0xbfc87d0a, 0xcb665abf, 0xbfd8f5c2, 0x8f5c28e8},			/* -0.19131=f(-0.39000)*/
{61, 0,123,__LINE__, 0xbfc7e237, 0x5c673edc, 0xbfd851eb, 0x851eb844},			/* -0.18659=f(-0.38000)*/
{63, 0,123,__LINE__, 0xbfc746ee, 0xc5d72bd8, 0xbfd7ae14, 0x7ae147a0},			/* -0.18185=f(-0.37000)*/
{63, 0,123,__LINE__, 0xbfc6ab33, 0xfe4e4a90, 0xbfd70a3d, 0x70a3d6fc},			/* -0.17709=f(-0.36000)*/
{63, 0,123,__LINE__, 0xbfc60f09, 0xfed3cc72, 0xbfd66666, 0x66666658},			/* -0.17233=f(-0.35000)*/
{64, 0,123,__LINE__, 0xbfc57273, 0xc2cdbb4f, 0xbfd5c28f, 0x5c28f5b4},			/* -0.16755=f(-0.34000)*/
{62, 0,123,__LINE__, 0xbfc4d574, 0x47f0bb91, 0xbfd51eb8, 0x51eb8510},			/* -0.16276=f(-0.33000)*/
{62, 0,123,__LINE__, 0xbfc4380e, 0x8e2fc149, 0xbfd47ae1, 0x47ae146c},			/* -0.15796=f(-0.32000)*/
{64, 0,123,__LINE__, 0xbfc39a45, 0x97abb851, 0xbfd3d70a, 0x3d70a3c8},			/* -0.15314=f(-0.31000)*/
{64, 0,123,__LINE__, 0xbfc2fc1c, 0x68a31ff4, 0xbfd33333, 0x33333324},			/* -0.14831=f(-0.30000)*/
{64, 0,123,__LINE__, 0xbfc25d96, 0x07619a7a, 0xbfd28f5c, 0x28f5c280},			/* -0.14348=f(-0.29000)*/
{64, 0,123,__LINE__, 0xbfc1beb5, 0x7c2f70f1, 0xbfd1eb85, 0x1eb851dc},			/* -0.13863=f(-0.28000)*/
{64, 0,123,__LINE__, 0xbfc11f7d, 0xd1410b8e, 0xbfd147ae, 0x147ae138},			/* -0.13377=f(-0.27000)*/
{63, 0,123,__LINE__, 0xbfc07ff2, 0x12a65f0c, 0xbfd0a3d7, 0x0a3d7094},			/* -0.12890=f(-0.26000)*/
{64, 0,123,__LINE__, 0xbfbfc02a, 0x9c749eca, 0xbfcfffff, 0xffffffe0},			/* -0.12402=f(-0.25000)*/
{64, 0,123,__LINE__, 0xbfbe7fd5, 0x27241087, 0xbfceb851, 0xeb851e98},			/* -0.11913=f(-0.24000)*/
{64, 0,123,__LINE__, 0xbfbd3ee9, 0xe7d8971c, 0xbfcd70a3, 0xd70a3d50},			/* -0.11424=f(-0.23000)*/
{64, 0,123,__LINE__, 0xbfbbfd6f, 0x04416cce, 0xbfcc28f5, 0xc28f5c08},			/* -0.10933=f(-0.22000)*/
{64, 0,123,__LINE__, 0xbfbabb6a, 0xa51dfa12, 0xbfcae147, 0xae147ac0},			/* -0.10442=f(-0.21000)*/
{64, 0,123,__LINE__, 0xbfb978e2, 0xf61c3bb4, 0xbfc99999, 0x99999978},			/* -0.09950=f(-0.20000)*/
{62, 0,123,__LINE__, 0xbfb835de, 0x25b71825, 0xbfc851eb, 0x851eb830},			/* -0.09457=f(-0.19000)*/
{62, 0,123,__LINE__, 0xbfb6f262, 0x6514a4ce, 0xbfc70a3d, 0x70a3d6e8},			/* -0.08963=f(-0.18000)*/
{64, 0,123,__LINE__, 0xbfb5ae75, 0xe7e45bff, 0xbfc5c28f, 0x5c28f5a0},			/* -0.08469=f(-0.17000)*/
{63, 0,123,__LINE__, 0xbfb46a1e, 0xe43d4469, 0xbfc47ae1, 0x47ae1458},			/* -0.07974=f(-0.16000)*/
{64, 0,123,__LINE__, 0xbfb32563, 0x927c0aba, 0xbfc33333, 0x33333310},			/* -0.07478=f(-0.15000)*/
{64, 0,123,__LINE__, 0xbfb1e04a, 0x2d210e45, 0xbfc1eb85, 0x1eb851c8},			/* -0.06982=f(-0.14000)*/
{64, 0,123,__LINE__, 0xbfb09ad8, 0xf0ae6157, 0xbfc0a3d7, 0x0a3d7080},			/* -0.06486=f(-0.13000)*/
{64, 0,123,__LINE__, 0xbfaeaa2c, 0x370b7c26, 0xbfbeb851, 0xeb851e71},			/* -0.05989=f(-0.12000)*/
{62, 0,123,__LINE__, 0xbfac1e0f, 0xdb8ce112, 0xbfbc28f5, 0xc28f5be2},			/* -0.05491=f(-0.11000)*/
{64, 0,123,__LINE__, 0xbfa99169, 0x52566db6, 0xbfb99999, 0x99999953},			/* -0.04993=f(-0.00100)*/
{64, 0,123,__LINE__, 0xbfa70445, 0x21d0304a, 0xbfb70a3d, 0x70a3d6c4},			/* -0.04495=f(-0.09000)*/
{64, 0,123,__LINE__, 0xbfa476af, 0xd31065de, 0xbfb47ae1, 0x47ae1435},			/* -0.03996=f(-0.08000)*/
{64, 0,123,__LINE__, 0xbfa1e8b5, 0xf19707ed, 0xbfb1eb85, 0x1eb851a6},			/* -0.03497=f(-0.07000)*/
{64, 0,123,__LINE__, 0xbf9eb4c8, 0x16129820, 0xbfaeb851, 0xeb851e2d},			/* -0.02998=f(-0.06000)*/
{64, 0,123,__LINE__, 0xbf99978d, 0x5dda2ed1, 0xbfa99999, 0x9999990e},			/* -0.02499=f(-0.05000)*/
{60, 0,123,__LINE__, 0xbf9479d4, 0xdcc8ce88, 0xbfa47ae1, 0x47ae13ef},			/* -0.01999=f(-0.04000)*/
{64, 0,123,__LINE__, 0xbf8eb76f, 0x6fa2c211, 0xbf9eb851, 0xeb851da0},			/* -0.01499=f(-0.03000)*/
{64, 0,123,__LINE__, 0xbf847a9e, 0x2c18dd61, 0xbf947ae1, 0x47ae1362},			/* -0.00999=f(-0.02000)*/
{64, 0,123,__LINE__, 0xbf747ad0, 0x80bb0662, 0xbf847ae1, 0x47ae1249},			/* -0.00499=f(-0.00010)*/
{64, 0,123,__LINE__, 0x3cc19000, 0x00000000, 0x3cd19000, 0x00000000},			/* 4.87457e-16=f(9.74915e-16)*/
{64, 0,123,__LINE__, 0x3f747ad0, 0x80bb0ac6, 0x3f847ae1, 0x47ae16ad},			/* 0.00499=f(0.01000)*/
{61, 0,123,__LINE__, 0x3f847a9e, 0x2c18df94, 0x3f947ae1, 0x47ae1594},			/* 0.00999=f(0.02000)*/
{64, 0,123,__LINE__, 0x3f8eb76f, 0x6fa2c443, 0x3f9eb851, 0xeb851fd2},			/* 0.01499=f(0.03000)*/
{63, 0,123,__LINE__, 0x3f9479d4, 0xdcc8cfa0, 0x3fa47ae1, 0x47ae1508},			/* 0.01999=f(0.04000)*/
{64, 0,123,__LINE__, 0x3f99978d, 0x5dda2fe9, 0x3fa99999, 0x99999a27},			/* 0.02499=f(0.05000)*/
{64, 0,123,__LINE__, 0x3f9eb4c8, 0x16129939, 0x3faeb851, 0xeb851f46},			/* 0.02998=f(0.06000)*/
{64, 0,123,__LINE__, 0x3fa1e8b5, 0xf1970879, 0x3fb1eb85, 0x1eb85232},			/* 0.03497=f(0.07000)*/
{64, 0,123,__LINE__, 0x3fa476af, 0xd310666a, 0x3fb47ae1, 0x47ae14c1},			/* 0.03996=f(0.08000)*/
{63, 0,123,__LINE__, 0x3fa70445, 0x21d030d6, 0x3fb70a3d, 0x70a3d750},			/* 0.04495=f(0.09000)*/
{64, 0,123,__LINE__, 0x3fa99169, 0x52566e42, 0x3fb99999, 0x999999df},			/* 0.04993=f(0.10000)*/
{64, 0,123,__LINE__, 0x3fac1e0f, 0xdb8ce19c, 0x3fbc28f5, 0xc28f5c6e},			/* 0.05491=f(0.11000)*/
{64, 0,123,__LINE__, 0x3faeaa2c, 0x370b7cb1, 0x3fbeb851, 0xeb851efd},			/* 0.05989=f(0.12000)*/
{63, 0,123,__LINE__, 0x3fb09ad8, 0xf0ae619d, 0x3fc0a3d7, 0x0a3d70c6},			/* 0.06486=f(0.13000)*/
{63, 0,123,__LINE__, 0x3fb1e04a, 0x2d210e8b, 0x3fc1eb85, 0x1eb8520e},			/* 0.06982=f(0.14000)*/
{55, 0,123,__LINE__, 0x3fb32563, 0x927c0b00, 0x3fc33333, 0x33333356},			/* 0.07478=f(0.15000)*/
{62, 0,123,__LINE__, 0x3fb46a1e, 0xe43d44ae, 0x3fc47ae1, 0x47ae149e},			/* 0.07974=f(0.16000)*/
{63, 0,123,__LINE__, 0x3fb5ae75, 0xe7e45c44, 0x3fc5c28f, 0x5c28f5e6},			/* 0.08469=f(0.17000)*/
{63, 0,123,__LINE__, 0x3fb6f262, 0x6514a513, 0x3fc70a3d, 0x70a3d72e},			/* 0.08963=f(0.18000)*/
{63, 0,123,__LINE__, 0x3fb835de, 0x25b7186a, 0x3fc851eb, 0x851eb876},			/* 0.09457=f(0.19000)*/
{64, 0,123,__LINE__, 0x3fb978e2, 0xf61c3bf9, 0x3fc99999, 0x999999be},			/* 0.09950=f(0.20000)*/
{64, 0,123,__LINE__, 0x3fbabb6a, 0xa51dfa57, 0x3fcae147, 0xae147b06},			/* 0.10442=f(0.21000)*/
{63, 0,123,__LINE__, 0x3fbbfd6f, 0x04416d13, 0x3fcc28f5, 0xc28f5c4e},			/* 0.10933=f(0.22000)*/
{64, 0,123,__LINE__, 0x3fbd3ee9, 0xe7d89761, 0x3fcd70a3, 0xd70a3d96},			/* 0.11424=f(0.23000)*/
{64, 0,123,__LINE__, 0x3fbe7fd5, 0x272410cc, 0x3fceb851, 0xeb851ede},			/* 0.11913=f(0.24000)*/
{64, 0,123,__LINE__, 0x3fbfc02a, 0x9c749f0e, 0x3fd00000, 0x00000013},			/* 0.12402=f(0.25000)*/
{64, 0,123,__LINE__, 0x3fc07ff2, 0x12a65f2e, 0x3fd0a3d7, 0x0a3d70b7},			/* 0.12890=f(0.26000)*/
{63, 0,123,__LINE__, 0x3fc11f7d, 0xd1410bb0, 0x3fd147ae, 0x147ae15b},			/* 0.13377=f(0.27000)*/
{63, 0,123,__LINE__, 0x3fc1beb5, 0x7c2f7113, 0x3fd1eb85, 0x1eb851ff},			/* 0.13863=f(0.28000)*/
{61, 0,123,__LINE__, 0x3fc25d96, 0x07619a9c, 0x3fd28f5c, 0x28f5c2a3},			/* 0.14348=f(0.29000)*/
{64, 0,123,__LINE__, 0x3fc2fc1c, 0x68a32015, 0x3fd33333, 0x33333347},			/* 0.14831=f(0.30000)*/
{64, 0,123,__LINE__, 0x3fc39a45, 0x97abb873, 0x3fd3d70a, 0x3d70a3eb},			/* 0.15314=f(0.31000)*/
{61, 0,123,__LINE__, 0x3fc4380e, 0x8e2fc16c, 0x3fd47ae1, 0x47ae148f},			/* 0.15796=f(0.32000)*/
{61, 0,123,__LINE__, 0x3fc4d574, 0x47f0bbb4, 0x3fd51eb8, 0x51eb8533},			/* 0.16276=f(0.33000)*/
{64, 0,123,__LINE__, 0x3fc57273, 0xc2cdbb70, 0x3fd5c28f, 0x5c28f5d7},			/* 0.16755=f(0.34000)*/
{63, 0,123,__LINE__, 0x3fc60f09, 0xfed3cc95, 0x3fd66666, 0x6666667b},			/* 0.17233=f(0.35000)*/
{64, 0,123,__LINE__, 0x3fc6ab33, 0xfe4e4ab2, 0x3fd70a3d, 0x70a3d71f},			/* 0.17709=f(0.36000)*/
{64, 0,123,__LINE__, 0x3fc746ee, 0xc5d72bf9, 0x3fd7ae14, 0x7ae147c3},			/* 0.18185=f(0.37000)*/
{62, 0,123,__LINE__, 0x3fc7e237, 0x5c673efe, 0x3fd851eb, 0x851eb867},			/* 0.18659=f(0.38000)*/
{64, 0,123,__LINE__, 0x3fc87d0a, 0xcb665ae0, 0x3fd8f5c2, 0x8f5c290b},			/* 0.19131=f(0.39000)*/
{64, 0,123,__LINE__, 0x3fc91766, 0x1ebb818c, 0x3fd99999, 0x999999af},			/* 0.19602=f(0.40000)*/
{64, 0,123,__LINE__, 0x3fc9b146, 0x64dcf3a5, 0x3fda3d70, 0xa3d70a53},			/* 0.20072=f(0.41000)*/
{64, 0,123,__LINE__, 0x3fca4aa8, 0xaee035c2, 0x3fdae147, 0xae147af7},			/* 0.20540=f(0.42000)*/
{64, 0,123,__LINE__, 0x3fcae38a, 0x108a06af, 0x3fdb851e, 0xb851eb9b},			/* 0.21006=f(0.43000)*/
{64, 0,123,__LINE__, 0x3fcb7be7, 0xa05e463e, 0x3fdc28f5, 0xc28f5c3f},			/* 0.21471=f(0.44000)*/
{64, 0,123,__LINE__, 0x3fcc13be, 0x77afcc68, 0x3fdccccc, 0xcccccce3},			/* 0.21935=f(0.45000)*/
{64, 0,123,__LINE__, 0x3fccab0b, 0xb2b0304a, 0x3fdd70a3, 0xd70a3d87},			/* 0.22396=f(0.46000)*/
{64, 0,123,__LINE__, 0x3fcd41cc, 0x707f7ec2, 0x3fde147a, 0xe147ae2b},			/* 0.22857=f(0.47000)*/
{63, 0,123,__LINE__, 0x3fcdd7fd, 0xd33be029, 0x3fdeb851, 0xeb851ecf},			/* 0.23315=f(0.48000)*/
{64, 0,123,__LINE__, 0x3fce6d9d, 0x00112cf6, 0x3fdf5c28, 0xf5c28f73},			/* 0.23772=f(0.49000)*/
{64, 0,123,__LINE__, 0x3fcf02a7, 0x1f4870ea, 0x3fe00000, 0x0000000b},			/* 0.24226=f(0.50000)*/
{64, 0,123,__LINE__, 0x3fcf9719, 0x5c575c53, 0x3fe051eb, 0x851eb85d},			/* 0.24679=f(0.51000)*/
{64, 0,123,__LINE__, 0x3fd01578, 0x72f7d194, 0x3fe0a3d7, 0x0a3d70af},			/* 0.25131=f(0.52000)*/
{64, 0,123,__LINE__, 0x3fd05f15, 0x770724d1, 0x3fe0f5c2, 0x8f5c2901},			/* 0.25580=f(0.53000)*/
{64, 0,123,__LINE__, 0x3fd0a862, 0x55056ef8, 0x3fe147ae, 0x147ae153},			/* 0.26027=f(0.54000)*/
{64, 0,123,__LINE__, 0x3fd0f15d, 0xa9534f5e, 0x3fe19999, 0x999999a5},			/* 0.26473=f(0.55000)*/
{64, 0,123,__LINE__, 0x3fd13a06, 0x120dc70d, 0x3fe1eb85, 0x1eb851f7},			/* 0.26916=f(0.56000)*/
{62, 0,123,__LINE__, 0x3fd1825a, 0x2f15b852, 0x3fe23d70, 0xa3d70a49},			/* 0.27358=f(0.57000)*/
{63, 0,123,__LINE__, 0x3fd1ca58, 0xa2175c24, 0x3fe28f5c, 0x28f5c29b},			/* 0.27797=f(0.58000)*/
{64, 0,123,__LINE__, 0x3fd21200, 0x0e91ad54, 0x3fe2e147, 0xae147aed},			/* 0.28234=f(0.59000)*/
{64, 0,123,__LINE__, 0x3fd2594f, 0x19ddc93a, 0x3fe33333, 0x3333333f},			/* 0.28670=f(0.60000)*/
{63, 0,123,__LINE__, 0x3fd2a044, 0x6b3645d6, 0x3fe3851e, 0xb851eb91},			/* 0.29103=f(0.61000)*/
{60, 0,123,__LINE__, 0x3fd2e6de, 0xabbe7d27, 0x3fe3d70a, 0x3d70a3e3},			/* 0.29534=f(0.62000)*/
{64, 0,123,__LINE__, 0x3fd32d1c, 0x8689cd8e, 0x3fe428f5, 0xc28f5c35},			/* 0.29962=f(0.63000)*/
{63, 0,123,__LINE__, 0x3fd372fc, 0xa8a2cf24, 0x3fe47ae1, 0x47ae1487},			/* 0.30389=f(0.64000)*/
{62, 0,123,__LINE__, 0x3fd3b87d, 0xc1127dc6, 0x3fe4cccc, 0xccccccd9},			/* 0.30813=f(0.65000)*/
{63, 0,123,__LINE__, 0x3fd3fd9e, 0x80e757b8, 0x3fe51eb8, 0x51eb852b},			/* 0.31235=f(0.66000)*/
{62, 0,123,__LINE__, 0x3fd4425d, 0x9b3c70c1, 0x3fe570a3, 0xd70a3d7d},			/* 0.31655=f(0.67000)*/
{61, 0,123,__LINE__, 0x3fd486b9, 0xc540797b, 0x3fe5c28f, 0x5c28f5cf},			/* 0.32072=f(0.68000)*/
{64, 0,123,__LINE__, 0x3fd4cab1, 0xb63cbacc, 0x3fe6147a, 0xe147ae21},			/* 0.32487=f(0.69000)*/
{63, 0,123,__LINE__, 0x3fd50e44, 0x279c0551, 0x3fe66666, 0x66666673},			/* 0.32899=f(0.70000)*/
{64, 0,123,__LINE__, 0x3fd5516f, 0xd4f19495, 0x3fe6b851, 0xeb851ec5},			/* 0.33309=f(0.71000)*/
{64, 0,123,__LINE__, 0x3fd59433, 0x7bffe5f8, 0x3fe70a3d, 0x70a3d717},			/* 0.33717=f(0.72000)*/
{63, 0,123,__LINE__, 0x3fd5d68d, 0xdcbf8304, 0x3fe75c28, 0xf5c28f69},			/* 0.34122=f(0.73000)*/
{64, 0,123,__LINE__, 0x3fd6187d, 0xb965bf31, 0x3fe7ae14, 0x7ae147bb},			/* 0.34524=f(0.74000)*/
{64, 0,123,__LINE__, 0x3fd65a01, 0xd66b68c7, 0x3fe80000, 0x0000000d},			/* 0.34924=f(0.75000)*/
{64, 0,123,__LINE__, 0x3fd69b18, 0xfa936cdd, 0x3fe851eb, 0x851eb85f},			/* 0.35321=f(0.76000)*/
{64, 0,123,__LINE__, 0x3fd6dbc1, 0xeef16e37, 0x3fe8a3d7, 0x0a3d70b1},			/* 0.35716=f(0.77000)*/
{64, 0,123,__LINE__, 0x3fd71bfb, 0x7ef04ee3, 0x3fe8f5c2, 0x8f5c2903},			/* 0.36108=f(0.78000)*/
{62, 0,123,__LINE__, 0x3fd75bc4, 0x7858ac79, 0x3fe947ae, 0x147ae155},			/* 0.36497=f(0.79000)*/
{64, 0,123,__LINE__, 0x3fd79b1b, 0xab574ed7, 0x3fe99999, 0x999999a7},			/* 0.36884=f(0.80000)*/
{62, 0,123,__LINE__, 0x3fd7d9ff, 0xea838919, 0x3fe9eb85, 0x1eb851f9},			/* 0.37268=f(0.81000)*/
{61, 0,123,__LINE__, 0x3fd81870, 0x0ae58cdb, 0x3fea3d70, 0xa3d70a4b},			/* 0.37649=f(0.82000)*/
{64, 0,123,__LINE__, 0x3fd8566a, 0xe3fcaf78, 0x3fea8f5c, 0x28f5c29d},			/* 0.38027=f(0.83000)*/
{63, 0,123,__LINE__, 0x3fd893ef, 0x4fc5a12f, 0x3feae147, 0xae147aef},			/* 0.38402=f(0.84000)*/
{64, 0,123,__LINE__, 0x3fd8d0fc, 0x2ac09612, 0x3feb3333, 0x33333341},			/* 0.38775=f(0.85000)*/
{64, 0,123,__LINE__, 0x3fd90d90, 0x53f76094, 0x3feb851e, 0xb851eb93},			/* 0.39145=f(0.86000)*/
{62, 0,123,__LINE__, 0x3fd949aa, 0xad037d91, 0x3febd70a, 0x3d70a3e5},			/* 0.39512=f(0.87000)*/
{61, 0,123,__LINE__, 0x3fd9854a, 0x1a1411bb, 0x3fec28f5, 0xc28f5c37},			/* 0.39876=f(0.88000)*/
{64, 0,123,__LINE__, 0x3fd9c06d, 0x81f3d837, 0x3fec7ae1, 0x47ae1489},			/* 0.40236=f(0.89000)*/
{64, 0,123,__LINE__, 0x3fd9fb13, 0xce0f0257, 0x3feccccc, 0xccccccdb},			/* 0.40594=f(0.90000)*/
{64, 0,123,__LINE__, 0x3fda353b, 0xea790853, 0x3fed1eb8, 0x51eb852d},			/* 0.40949=f(0.91000)*/
{64, 0,123,__LINE__, 0x3fda6ee4, 0xc5f26ac9, 0x3fed70a3, 0xd70a3d7f},			/* 0.41301=f(0.92000)*/
{64, 0,123,__LINE__, 0x3fdaa80d, 0x51ee6500, 0x3fedc28f, 0x5c28f5d1},			/* 0.41650=f(0.93000)*/
{63, 0,123,__LINE__, 0x3fdae0b4, 0x82988fbb, 0x3fee147a, 0xe147ae23},			/* 0.41996=f(0.94000)*/
{62, 0,123,__LINE__, 0x3fdb18d9, 0x4eda747e, 0x3fee6666, 0x66666675},			/* 0.42339=f(0.95000)*/
{62, 0,123,__LINE__, 0x3fdb507a, 0xb0611136, 0x3feeb851, 0xeb851ec7},			/* 0.42678=f(0.96000)*/
{64, 0,123,__LINE__, 0x3fdb8797, 0xa3a24c08, 0x3fef0a3d, 0x70a3d719},			/* 0.43015=f(0.97000)*/
{62, 0,123,__LINE__, 0x3fdbbe2f, 0x27e25746, 0x3fef5c28, 0xf5c28f6b},			/* 0.43348=f(0.98000)*/
{62, 0,123,__LINE__, 0x3fdbf440, 0x3f390555, 0x3fefae14, 0x7ae147bd},			/* 0.43678=f(0.99000)*/
{64, 0,123,__LINE__, 0x3fdc29c9, 0xee970c75, 0x3ff00000, 0x00000007},			/* 0.44005=f(1.00000)*/
{62, 0,123,__LINE__, 0x3fdc5ecb, 0x3dcb3a42, 0x3ff028f5, 0xc28f5c30},			/* 0.44328=f(1.01000)*/
{63, 0,123,__LINE__, 0x3fdc9343, 0x378796d5, 0x3ff051eb, 0x851eb859},			/* 0.44648=f(1.02000)*/
{64, 0,123,__LINE__, 0x3fdcc730, 0xe9667776, 0x3ff07ae1, 0x47ae1482},			/* 0.44965=f(1.03000)*/
{63, 0,123,__LINE__, 0x3fdcfa93, 0x63ef80a4, 0x3ff0a3d7, 0x0a3d70ab},			/* 0.45279=f(1.04000)*/
{64, 0,123,__LINE__, 0x3fdd2d69, 0xba9c9775, 0x3ff0cccc, 0xccccccd4},			/* 0.45589=f(1.05000)*/
{64, 0,123,__LINE__, 0x3fdd5fb3, 0x03dec21a, 0x3ff0f5c2, 0x8f5c28fd},			/* 0.45896=f(1.06000)*/
{64, 0,123,__LINE__, 0x3fdd916e, 0x5922f785, 0x3ff11eb8, 0x51eb8526},			/* 0.46200=f(1.07000)*/
{64, 0,123,__LINE__, 0x3fddc29a, 0xd6d6de01, 0x3ff147ae, 0x147ae14f},			/* 0.46500=f(1.08000)*/
{62, 0,123,__LINE__, 0x3fddf337, 0x9c6d78a1, 0x3ff170a3, 0xd70a3d78},			/* 0.46796=f(1.09000)*/
{64, 0,123,__LINE__, 0x3fde2343, 0xcc63c385, 0x3ff19999, 0x999999a1},			/* 0.47090=f(1.10000)*/
{64, 0,123,__LINE__, 0x3fde52be, 0x8c453eb5, 0x3ff1c28f, 0x5c28f5ca},			/* 0.47380=f(1.11000)*/
{61, 0,123,__LINE__, 0x3fde81a7, 0x04b067a4, 0x3ff1eb85, 0x1eb851f3},			/* 0.47666=f(1.12000)*/
{63, 0,123,__LINE__, 0x3fdeaffc, 0x615b210e, 0x3ff2147a, 0xe147ae1c},			/* 0.47949=f(1.13000)*/
{61, 0,123,__LINE__, 0x3fdeddbd, 0xd117095b, 0x3ff23d70, 0xa3d70a45},			/* 0.48228=f(1.14000)*/
{63, 0,123,__LINE__, 0x3fdf0aea, 0x85d5bf1e, 0x3ff26666, 0x6666666e},			/* 0.48504=f(1.15000)*/
{61, 0,123,__LINE__, 0x3fdf3781, 0xb4ad13ec, 0x3ff28f5c, 0x28f5c297},			/* 0.48776=f(1.16000)*/
{64, 0,123,__LINE__, 0x3fdf6382, 0x95db2d2a, 0x3ff2b851, 0xeb851ec0},			/* 0.49044=f(1.17000)*/
{63, 0,123,__LINE__, 0x3fdf8eec, 0x64ca92f6, 0x3ff2e147, 0xae147ae9},			/* 0.49309=f(1.18000)*/
{63, 0,123,__LINE__, 0x3fdfb9be, 0x60162ceb, 0x3ff30a3d, 0x70a3d712},			/* 0.49571=f(1.19000)*/
{54, 0,123,__LINE__, 0xbfd23723, 0x45b96613, 0xc00921fb, 0x54442d18},			/* -0.28461=f(-3.14159)*/
{58, 0,123,__LINE__, 0xbfe2236c, 0x458df176, 0xbff921fb, 0x54442d18},			/* -0.56682=f(-1.57079)*/
{64, 0,123,__LINE__, 0x00000000, 0x00000000, 0x00000000, 0x00000000},			/* 0.00000=f(0.00000)*/
{62, 0,123,__LINE__, 0x3fe2236c, 0x458df176, 0x3ff921fb, 0x54442d18},			/* 0.56682=f(1.57079)*/
{61, 0,123,__LINE__, 0x3fd23723, 0x45b96613, 0x400921fb, 0x54442d18},			/* 0.28461=f(3.14159)*/
{58, 0,123,__LINE__, 0xbfd206ae, 0xe4af911e, 0x4012d97c, 0x7f3321d2},			/* -0.28165=f(4.71238)*/
{64, 0,123,__LINE__, 0x3fbe6678, 0x3a4dbbb0, 0xc03e0000, 0x00000000},			/* 0.11875=f(-30.0000)*/
{58, 0,123,__LINE__, 0xbfba145c, 0x2bf5d6a7, 0xc03c4ccc, 0xcccccccd},			/* -0.10187=f(-28.3000)*/
{64, 0,123,__LINE__, 0xbfb965bd, 0xda59f829, 0xc03a9999, 0x9999999a},			/* -0.09920=f(-26.6000)*/
{64, 0,123,__LINE__, 0x3fc142f3, 0x9995533a, 0xc038e666, 0x66666667},			/* 0.13485=f(-24.9000)*/
{64, 0,123,__LINE__, 0x3fb20dc7, 0xda3ce59d, 0xc0373333, 0x33333334},			/* 0.07052=f(-23.2000)*/
{64, 0,123,__LINE__, 0xbfc4f91a, 0xe3f53776, 0xc0358000, 0x00000001},			/* -0.16385=f(-21.5000)*/
{64, 0,123,__LINE__, 0xbfa0cd5b, 0xcd3ea881, 0xc033cccc, 0xccccccce},			/* -0.03281=f(-19.8000)*/
{64, 0,123,__LINE__, 0x3fc7fb17, 0x3dcfcf2e, 0xc0321999, 0x9999999b},			/* 0.18735=f(-18.1000)*/
{64, 0,123,__LINE__, 0xbf8c74d0, 0x79162d3e, 0xc0306666, 0x66666668},			/* -0.01389=f(-16.4000)*/
{64, 0,123,__LINE__, 0xbfca24e7, 0xd2d25d15, 0xc02d6666, 0x6666666a},			/* -0.20425=f(-14.7000)*/
{62, 0,123,__LINE__, 0x3fb2005d, 0x262e73c0, 0xc02a0000, 0x00000004},			/* 0.07031=f(-13.0000)*/
{62, 0,123,__LINE__, 0x3fcb6cb5, 0x6d484cf6, 0xc0269999, 0x9999999e},			/* 0.21425=f(-11.3000)*/
{63, 0,123,__LINE__, 0xbfc1dbf2, 0xf3b411d1, 0xc0233333, 0x33333338},			/* -0.13952=f(-9.60000)*/

{57, 0,123,__LINE__, 0x3fcdd035, 0xc7235639, 0xc018cccc, 0xccccccd6},			/* 0.23291=f(-6.20000)*/
{52, 0,123,__LINE__, 0x3fcd9363, 0x634158b5, 0xc0120000, 0x00000009},			/* 0.23106=f(-4.50000)*/
{57, 0,123,__LINE__, 0xbfda38ad, 0x22065bec, 0xc0066666, 0x66666678},			/* -0.40970=f(-2.80000)*/
{60, 0,123,__LINE__, 0xbfde2343, 0xcc63c3a5, 0xbff19999, 0x999999bd},			/* -0.47090=f(-1.10000)*/
{61, 0,123,__LINE__, 0x3fd2594f, 0x19ddc8f2, 0x3fe33333, 0x333332ec},			/* 0.28670=f(0.60000)*/
{63, 0,123,__LINE__, 0x3fe146a2, 0xc2f16a4e, 0x40026666, 0x66666654},			/* 0.53987=f(2.30000)*/
{58, 0,123,__LINE__, 0xbfb0e837, 0x2dfae9d8, 0x400fffff, 0xffffffee},			/* -0.06604=f(4.00000)*/
{59, 0,123,__LINE__, 0xbfd4bed5, 0xe968696f, 0x4016cccc, 0xccccccc4},			/* -0.32414=f(5.70000)*/
{54, 0,123,__LINE__, 0x3fbc1063, 0xe5380213, 0x401d9999, 0x99999991},			/* 0.10962=f(7.40000)*/
{59, 0,123,__LINE__, 0x3fcdc04a, 0x68314a0d, 0x40223333, 0x3333332f},			/* 0.23243=f(9.10000)*/
{54, 0,123,__LINE__, 0xbfc23283, 0x9cb6bbfa, 0x40259999, 0x99999995},			/* -0.14216=f(10.8000)*/
{59, 0,123,__LINE__, 0xbfc52e92, 0xc46b4553, 0x4028ffff, 0xfffffffb},			/* -0.16548=f(12.5000)*/
{62, 0,123,__LINE__, 0x3fc4d06d, 0xb4af245c, 0x402c6666, 0x66666661},			/* 0.16261=f(14.2000)*/
{59, 0,123,__LINE__, 0x3fbba7b7, 0x3ee07310, 0x402fcccc, 0xccccccc7},			/* 0.10802=f(15.9000)*/
{62, 0,123,__LINE__, 0xbfc60238, 0x43170350, 0x40319999, 0x99999997},			/* -0.17194=f(17.6000)*/
{64, 0,123,__LINE__, 0xbfacdf50, 0xf93779aa, 0x40334ccc, 0xccccccca},			/* -0.05639=f(19.3000)*/
{62, 0,123,__LINE__, 0x3fc5e744, 0xe39a0de4, 0x4034ffff, 0xfffffffd},			/* 0.17112=f(21.0000)*/
{62, 0,123,__LINE__, 0xbfc4a256, 0xe7770b60, 0x40386666, 0x66666663},			/* -0.16120=f(24.4000)*/
{59, 0,123,__LINE__, 0x3f9f302d, 0x6b54eb93, 0x403a1999, 0x99999996},			/* 0.03045=f(26.1000)*/
{62, 0,123,__LINE__, 0x3fc25cf8, 0x6ae10498, 0x403bcccc, 0xccccccc9},			/* 0.14346=f(27.8000)*/
{64, 0,123,__LINE__, 0xbfb07640, 0x70ecf703, 0x403d7fff, 0xfffffffc},			/* -0.06430=f(29.5000)*/
0,};
test_j1(m)   {run_vector_1(m,j1_vec,(char *)(j1),"j1","dd");   }	
