#include "test.h"
 one_line_type tanh_vec[] = {
{64, 0,123,__LINE__, 0xbfeaad4c, 0x6d28dcaf, 0xbff33333, 0x33333333},			/* -0.83365=f(-1.20000)*/
{64, 0,123,__LINE__, 0xbfea941a, 0x22a3e4a9, 0xbff30a3d, 0x70a3d70a},			/* -0.83057=f(-1.19000)*/
{64, 0,123,__LINE__, 0xbfea7a7b, 0xcd09aecf, 0xbff2e147, 0xae147ae1},			/* -0.82745=f(-1.18000)*/
{60, 0,123,__LINE__, 0xbfea6070, 0x07d3d0d8, 0xbff2b851, 0xeb851eb8},			/* -0.82427=f(-1.17000)*/
{63, 0,123,__LINE__, 0xbfea45f5, 0x6de12a6b, 0xbff28f5c, 0x28f5c28f},			/* -0.82103=f(-1.16000)*/
{64, 0,123,__LINE__, 0xbfea2b0a, 0x99a1b256, 0xbff26666, 0x66666666},			/* -0.81775=f(-1.15000)*/
{64, 0,123,__LINE__, 0xbfea0fae, 0x254400cf, 0xbff23d70, 0xa3d70a3d},			/* -0.81441=f(-1.14000)*/
{64, 0,123,__LINE__, 0xbfe9f3de, 0xaae49d27, 0xbff2147a, 0xe147ae14},			/* -0.81101=f(-1.13000)*/
{64, 0,123,__LINE__, 0xbfe9d79a, 0xc4bf14e4, 0xbff1eb85, 0x1eb851eb},			/* -0.80756=f(-1.12000)*/
{64, 0,123,__LINE__, 0xbfe9bae1, 0x0d60e1cc, 0xbff1c28f, 0x5c28f5c2},			/* -0.80406=f(-1.11000)*/
{64, 0,123,__LINE__, 0xbfe99db0, 0x1fde2404, 0xbff19999, 0x99999999},			/* -0.80049=f(-1.10000)*/
{63, 0,123,__LINE__, 0xbfe98006, 0x98083507, 0xbff170a3, 0xd70a3d70},			/* -0.79687=f(-1.09000)*/
{64, 0,123,__LINE__, 0xbfe961e3, 0x12a61778, 0xbff147ae, 0x147ae147},			/* -0.79319=f(-1.08000)*/
{64, 0,123,__LINE__, 0xbfe94344, 0x2daec7a4, 0xbff11eb8, 0x51eb851e},			/* -0.78946=f(-1.07000)*/
{64, 0,123,__LINE__, 0xbfe92428, 0x88856fa2, 0xbff0f5c2, 0x8f5c28f5},			/* -0.78566=f(-1.06000)*/
{64, 0,123,__LINE__, 0xbfe9048e, 0xc437818f, 0xbff0cccc, 0xcccccccc},			/* -0.78180=f(-1.05000)*/
{64, 0,123,__LINE__, 0xbfe8e475, 0x83bcb9ca, 0xbff0a3d7, 0x0a3d70a3},			/* -0.77788=f(-1.04000)*/
{64, 0,123,__LINE__, 0xbfe8c3db, 0x6c390a32, 0xbff07ae1, 0x47ae147a},			/* -0.77390=f(-1.03000)*/
{64, 0,123,__LINE__, 0xbfe8a2bf, 0x25406ee4, 0xbff051eb, 0x851eb851},			/* -0.76986=f(-1.02000)*/
{63, 0,123,__LINE__, 0xbfe8811f, 0x591cac08, 0xbff028f5, 0xc28f5c28},			/* -0.76576=f(-1.01000)*/
{64, 0,123,__LINE__, 0xbfe85efa, 0xb514f394, 0xbfefffff, 0xfffffffe},			/* -0.76159=f(-0.01000)*/
{64, 0,123,__LINE__, 0xbfe83c4f, 0xe9b770e0, 0xbfefae14, 0x7ae147ac},			/* -0.75736=f(-0.99000)*/
{63, 0,123,__LINE__, 0xbfe8191d, 0xab24b746, 0xbfef5c28, 0xf5c28f5a},			/* -0.75306=f(-0.98000)*/
{64, 0,123,__LINE__, 0xbfe7f562, 0xb15d0fce, 0xbfef0a3d, 0x70a3d708},			/* -0.74870=f(-0.97000)*/
{64, 0,123,__LINE__, 0xbfe7d11d, 0xb88fa124, 0xbfeeb851, 0xeb851eb6},			/* -0.74427=f(-0.96000)*/
{64, 0,123,__LINE__, 0xbfe7ac4d, 0x816b6c0b, 0xbfee6666, 0x66666664},			/* -0.73978=f(-0.95000)*/
{63, 0,123,__LINE__, 0xbfe786f0, 0xd1721548, 0xbfee147a, 0xe147ae12},			/* -0.73522=f(-0.94000)*/
{64, 0,123,__LINE__, 0xbfe76106, 0x734c7526, 0xbfedc28f, 0x5c28f5c0},			/* -0.73059=f(-0.93000)*/
{64, 0,123,__LINE__, 0xbfe73a8d, 0x3720e34a, 0xbfed70a3, 0xd70a3d6e},			/* -0.72589=f(-0.92000)*/
{64, 0,123,__LINE__, 0xbfe71383, 0xf2eb34bd, 0xbfed1eb8, 0x51eb851c},			/* -0.72113=f(-0.91000)*/
{64, 0,123,__LINE__, 0xbfe6ebe9, 0x82d6605b, 0xbfeccccc, 0xccccccca},			/* -0.71629=f(-0.90000)*/
{61, 0,123,__LINE__, 0xbfe6c3bc, 0xc997bd23, 0xbfec7ae1, 0x47ae1478},			/* -0.71139=f(-0.89000)*/
{64, 0,123,__LINE__, 0xbfe69afc, 0xb0cbcc26, 0xbfec28f5, 0xc28f5c26},			/* -0.70641=f(-0.88000)*/
{64, 0,123,__LINE__, 0xbfe671a8, 0x29547ec2, 0xbfebd70a, 0x3d70a3d4},			/* -0.70137=f(-0.87000)*/
{62, 0,123,__LINE__, 0xbfe647be, 0x2bb8e865, 0xbfeb851e, 0xb851eb82},			/* -0.69625=f(-0.86000)*/
{64, 0,123,__LINE__, 0xbfe61d3d, 0xb88649b0, 0xbfeb3333, 0x33333330},			/* -0.69106=f(-0.85000)*/
{63, 0,123,__LINE__, 0xbfe5f225, 0xd8b26165, 0xbfeae147, 0xae147ade},			/* -0.68580=f(-0.84000)*/
{63, 0,123,__LINE__, 0xbfe5c675, 0x9dfeee35, 0xbfea8f5c, 0x28f5c28c},			/* -0.68047=f(-0.83000)*/
{64, 0,123,__LINE__, 0xbfe59a2c, 0x235e4ad2, 0xbfea3d70, 0xa3d70a3a},			/* -0.67506=f(-0.82000)*/
{62, 0,123,__LINE__, 0xbfe56d48, 0x8d590c72, 0xbfe9eb85, 0x1eb851e8},			/* -0.66959=f(-0.81000)*/
{63, 0,123,__LINE__, 0xbfe53fca, 0x0a748a3e, 0xbfe99999, 0x99999996},			/* -0.66403=f(-0.80000)*/
{64, 0,123,__LINE__, 0xbfe511af, 0xd39a32b6, 0xbfe947ae, 0x147ae144},			/* -0.65840=f(-0.79000)*/
{64, 0,123,__LINE__, 0xbfe4e2f9, 0x2c7f9282, 0xbfe8f5c2, 0x8f5c28f2},			/* -0.65270=f(-0.78000)*/
{62, 0,123,__LINE__, 0xbfe4b3a5, 0x640eeeb6, 0xbfe8a3d7, 0x0a3d70a0},			/* -0.64692=f(-0.77000)*/
{62, 0,123,__LINE__, 0xbfe483b3, 0xd4d052ee, 0xbfe851eb, 0x851eb84e},			/* -0.64107=f(-0.76000)*/
{64, 0,123,__LINE__, 0xbfe45323, 0xe552f226, 0xbfe7ffff, 0xfffffffc},			/* -0.63514=f(-0.75000)*/
{64, 0,123,__LINE__, 0xbfe421f5, 0x0896b7b0, 0xbfe7ae14, 0x7ae147aa},			/* -0.62914=f(-0.74000)*/
{64, 0,123,__LINE__, 0xbfe3f026, 0xbe75e420, 0xbfe75c28, 0xf5c28f58},			/* -0.62306=f(-0.73000)*/
{63, 0,123,__LINE__, 0xbfe3bdb8, 0x940e909b, 0xbfe70a3d, 0x70a3d706},			/* -0.61690=f(-0.72000)*/
{64, 0,123,__LINE__, 0xbfe38aaa, 0x242bf149, 0xbfe6b851, 0xeb851eb4},			/* -0.61067=f(-0.71000)*/
{64, 0,123,__LINE__, 0xbfe356fb, 0x17af2e8e, 0xbfe66666, 0x66666662},			/* -0.60436=f(-0.70000)*/
{63, 0,123,__LINE__, 0xbfe322ab, 0x25f7aadc, 0xbfe6147a, 0xe147ae10},			/* -0.59798=f(-0.69000)*/
{63, 0,123,__LINE__, 0xbfe2edba, 0x154a89f9, 0xbfe5c28f, 0x5c28f5be},			/* -0.59151=f(-0.68000)*/
{64, 0,123,__LINE__, 0xbfe2b827, 0xbb394cea, 0xbfe570a3, 0xd70a3d6c},			/* -0.58497=f(-0.67000)*/
{64, 0,123,__LINE__, 0xbfe281f3, 0xfd0754b6, 0xbfe51eb8, 0x51eb851a},			/* -0.57836=f(-0.66000)*/
{62, 0,123,__LINE__, 0xbfe24b1e, 0xd00e1cb8, 0xbfe4cccc, 0xccccccc8},			/* -0.57166=f(-0.65000)*/
{64, 0,123,__LINE__, 0xbfe213a8, 0x3a1ffc62, 0xbfe47ae1, 0x47ae1476},			/* -0.56489=f(-0.64000)*/
{63, 0,123,__LINE__, 0xbfe1db90, 0x51e93ee4, 0xbfe428f5, 0xc28f5c24},			/* -0.55805=f(-0.63000)*/
{62, 0,123,__LINE__, 0xbfe1a2d7, 0x3f4f5e90, 0xbfe3d70a, 0x3d70a3d2},			/* -0.55112=f(-0.62000)*/
{61, 0,123,__LINE__, 0xbfe1697d, 0x3bce3092, 0xbfe3851e, 0xb851eb80},			/* -0.54412=f(-0.61000)*/
{63, 0,123,__LINE__, 0xbfe12f82, 0x92d2ccf8, 0xbfe33333, 0x3333332e},			/* -0.53704=f(-0.60000)*/
{62, 0,123,__LINE__, 0xbfe0f4e7, 0xa213fe44, 0xbfe2e147, 0xae147adc},			/* -0.52989=f(-0.59000)*/
{64, 0,123,__LINE__, 0xbfe0b9ac, 0xd9e8032a, 0xbfe28f5c, 0x28f5c28a},			/* -0.52266=f(-0.58000)*/
{64, 0,123,__LINE__, 0xbfe07dd2, 0xbd976c80, 0xbfe23d70, 0xa3d70a38},			/* -0.51535=f(-0.57000)*/
{57, 0,123,__LINE__, 0xbfe04159, 0xe3ace13f, 0xbfe1eb85, 0x1eb851e6},			/* -0.50797=f(-0.56000)*/
{54, 0,123,__LINE__, 0xbfe00442, 0xf64191fe, 0xbfe19999, 0x99999994},			/* -0.50052=f(-0.55000)*/
{64, 0,123,__LINE__, 0xbfdf8d1d, 0x668c4a9c, 0xbfe147ae, 0x147ae142},			/* -0.49298=f(-0.54000)*/
{64, 0,123,__LINE__, 0xbfdf107b, 0xd98fcce8, 0xbfe0f5c2, 0x8f5c28f0},			/* -0.48538=f(-0.53000)*/
{64, 0,123,__LINE__, 0xbfde92a3, 0x1263fffb, 0xbfe0a3d7, 0x0a3d709e},			/* -0.47770=f(-0.52000)*/
{64, 0,123,__LINE__, 0xbfde1395, 0x0715184e, 0xbfe051eb, 0x851eb84c},			/* -0.46994=f(-0.51000)*/
{64, 0,123,__LINE__, 0xbfdd9353, 0xd7568aea, 0xbfdfffff, 0xfffffff4},			/* -0.46211=f(-0.50000)*/
{64, 0,123,__LINE__, 0xbfdd11e1, 0xcceb44fe, 0xbfdf5c28, 0xf5c28f50},			/* -0.45421=f(-0.49000)*/
{64, 0,123,__LINE__, 0xbfdc8f41, 0x5c04518a, 0xbfdeb851, 0xeb851eac},			/* -0.44624=f(-0.48000)*/
{64, 0,123,__LINE__, 0xbfdc0b75, 0x239586a4, 0xbfde147a, 0xe147ae08},			/* -0.43819=f(-0.47000)*/
{64, 0,123,__LINE__, 0xbfdb867f, 0xed9fd638, 0xbfdd70a3, 0xd70a3d64},			/* -0.43008=f(-0.46000)*/
{64, 0,123,__LINE__, 0xbfdb0064, 0xaf70e0b0, 0xbfdccccc, 0xccccccc0},			/* -0.42189=f(-0.45000)*/
{64, 0,123,__LINE__, 0xbfda7926, 0x89d76b00, 0xbfdc28f5, 0xc28f5c1c},			/* -0.41364=f(-0.44000)*/
{64, 0,123,__LINE__, 0xbfd9f0c8, 0xc94c5cc2, 0xbfdb851e, 0xb851eb78},			/* -0.40532=f(-0.43000)*/
{64, 0,123,__LINE__, 0xbfd9674e, 0xe60feeea, 0xbfdae147, 0xae147ad4},			/* -0.39693=f(-0.42000)*/
{64, 0,123,__LINE__, 0xbfd8dcbc, 0x843ab76e, 0xbfda3d70, 0xa3d70a30},			/* -0.38847=f(-0.41000)*/
{64, 0,123,__LINE__, 0xbfd85115, 0x73c242ca, 0xbfd99999, 0x9999998c},			/* -0.37994=f(-0.40000)*/
{64, 0,123,__LINE__, 0xbfd7c45d, 0xb070f0ee, 0xbfd8f5c2, 0x8f5c28e8},			/* -0.37136=f(-0.39000)*/
{64, 0,123,__LINE__, 0xbfd73699, 0x61d0d031, 0xbfd851eb, 0x851eb844},			/* -0.36270=f(-0.38000)*/
{64, 0,123,__LINE__, 0xbfd6a7cc, 0xdb093664, 0xbfd7ae14, 0x7ae147a0},			/* -0.35399=f(-0.37000)*/
{64, 0,123,__LINE__, 0xbfd617fc, 0x9aaeddca, 0xbfd70a3d, 0x70a3d6fc},			/* -0.34521=f(-0.36000)*/
{64, 0,123,__LINE__, 0xbfd5872d, 0x4a8651c9, 0xbfd66666, 0x66666658},			/* -0.33637=f(-0.35000)*/
{64, 0,123,__LINE__, 0xbfd4f563, 0xbf387d9c, 0xbfd5c28f, 0x5c28f5b4},			/* -0.32747=f(-0.34000)*/
{64, 0,123,__LINE__, 0xbfd462a4, 0xf7f935d1, 0xbfd51eb8, 0x51eb8510},			/* -0.31852=f(-0.33000)*/
{64, 0,123,__LINE__, 0xbfd3cef6, 0x1e1f9c83, 0xbfd47ae1, 0x47ae146c},			/* -0.30950=f(-0.32000)*/
{64, 0,123,__LINE__, 0xbfd33a5c, 0x84b04735, 0xbfd3d70a, 0x3d70a3c8},			/* -0.30043=f(-0.31000)*/
{64, 0,123,__LINE__, 0xbfd2a4dd, 0xa7d914ec, 0xbfd33333, 0x33333324},			/* -0.29131=f(-0.30000)*/
{64, 0,123,__LINE__, 0xbfd20e7f, 0x2c5eaa96, 0xbfd28f5c, 0x28f5c280},			/* -0.28213=f(-0.29000)*/
{64, 0,123,__LINE__, 0xbfd17746, 0xdefb93d0, 0xbfd1eb85, 0x1eb851dc},			/* -0.27290=f(-0.28000)*/
{64, 0,123,__LINE__, 0xbfd0df3a, 0xb3b10e2e, 0xbfd147ae, 0x147ae138},			/* -0.26362=f(-0.27000)*/
{64, 0,123,__LINE__, 0xbfd04660, 0xc5098d45, 0xbfd0a3d7, 0x0a3d7094},			/* -0.25429=f(-0.26000)*/
{64, 0,123,__LINE__, 0xbfcf597e, 0xa69a1c68, 0xbfcfffff, 0xffffffe0},			/* -0.24491=f(-0.25000)*/
{64, 0,123,__LINE__, 0xbfce24b9, 0x874eb37a, 0xbfceb851, 0xeb851e98},			/* -0.23549=f(-0.24000)*/
{64, 0,123,__LINE__, 0xbfccee7f, 0x3e80b94e, 0xbfcd70a3, 0xd70a3d50},			/* -0.22602=f(-0.23000)*/
{64, 0,123,__LINE__, 0xbfcbb6dd, 0x248d8d37, 0xbfcc28f5, 0xc28f5c08},			/* -0.21651=f(-0.22000)*/
{64, 0,123,__LINE__, 0xbfca7de0, 0xd5da50b4, 0xbfcae147, 0xae147ac0},			/* -0.20696=f(-0.21000)*/
{64, 0,123,__LINE__, 0xbfc94398, 0x30b3a570, 0xbfc99999, 0x99999978},			/* -0.19737=f(-0.20000)*/
{64, 0,123,__LINE__, 0xbfc80811, 0x531380b4, 0xbfc851eb, 0x851eb830},			/* -0.18774=f(-0.19000)*/
{64, 0,123,__LINE__, 0xbfc6cb5a, 0x984db955, 0xbfc70a3d, 0x70a3d6e8},			/* -0.17808=f(-0.18000)*/
{64, 0,123,__LINE__, 0xbfc58d82, 0x96a4059b, 0xbfc5c28f, 0x5c28f5a0},			/* -0.16838=f(-0.17000)*/
{64, 0,123,__LINE__, 0xbfc44e98, 0x1cc22f53, 0xbfc47ae1, 0x47ae1458},			/* -0.15864=f(-0.16000)*/
{64, 0,123,__LINE__, 0xbfc30eaa, 0x2f235432, 0xbfc33333, 0x33333310},			/* -0.14888=f(-0.15000)*/
{64, 0,123,__LINE__, 0xbfc1cdc8, 0x0561186b, 0xbfc1eb85, 0x1eb851c8},			/* -0.13909=f(-0.14000)*/
{64, 0,123,__LINE__, 0xbfc08c01, 0x076dc0aa, 0xbfc0a3d7, 0x0a3d7080},			/* -0.12927=f(-0.13000)*/
{64, 0,123,__LINE__, 0xbfbe92c9, 0x95746e8e, 0xbfbeb851, 0xeb851e71},			/* -0.11942=f(-0.12000)*/
{64, 0,123,__LINE__, 0xbfbc0c06, 0x1e921d60, 0xbfbc28f5, 0xc28f5be2},			/* -0.10955=f(-0.11000)*/
{64, 0,123,__LINE__, 0xbfb983d7, 0x795f40f4, 0xbfb99999, 0x99999953},			/* -0.09966=f(-0.00100)*/
{64, 0,123,__LINE__, 0xbfb6fa5d, 0xbe0ceab2, 0xbfb70a3d, 0x70a3d6c4},			/* -0.08975=f(-0.09000)*/
{64, 0,123,__LINE__, 0xbfb46fb9, 0x47945c79, 0xbfb47ae1, 0x47ae1435},			/* -0.07982=f(-0.08000)*/
{64, 0,123,__LINE__, 0xbfb1e40a, 0xad5c640a, 0xbfb1eb85, 0x1eb851a6},			/* -0.06988=f(-0.07000)*/
{64, 0,123,__LINE__, 0xbfaeaee5, 0x7989b65b, 0xbfaeb851, 0xeb851e2d},			/* -0.05992=f(-0.06000)*/
{64, 0,123,__LINE__, 0xbfa99424, 0xe535f66d, 0xbfa99999, 0x9999990e},			/* -0.04995=f(-0.05000)*/
{64, 0,123,__LINE__, 0xbfa47815, 0xe8f28682, 0xbfa47ae1, 0x47ae13ef},			/* -0.03997=f(-0.04000)*/
{64, 0,123,__LINE__, 0xbf9eb5f6, 0x2856ff57, 0xbf9eb851, 0xeb851da0},			/* -0.02999=f(-0.03000)*/
{64, 0,123,__LINE__, 0xbf947a2e, 0x5a063e00, 0xbf947ae1, 0x47ae1362},			/* -0.01999=f(-0.02000)*/
{64, 0,123,__LINE__, 0xbf847ab4, 0x8ae4572c, 0xbf847ae1, 0x47ae1249},			/* -0.00999=f(-0.00010)*/
{64, 0,123,__LINE__, 0x3cd19000, 0x00000000, 0x3cd19000, 0x00000000},			/* 9.74915e-16=f(9.74915e-16)*/
{64, 0,123,__LINE__, 0x3f847ab4, 0x8ae45b90, 0x3f847ae1, 0x47ae16ad},			/* 0.00999=f(0.01000)*/
{64, 0,123,__LINE__, 0x3f947a2e, 0x5a064032, 0x3f947ae1, 0x47ae1594},			/* 0.01999=f(0.02000)*/
{64, 0,123,__LINE__, 0x3f9eb5f6, 0x28570189, 0x3f9eb851, 0xeb851fd2},			/* 0.02999=f(0.03000)*/
{64, 0,123,__LINE__, 0x3fa47815, 0xe8f2879b, 0x3fa47ae1, 0x47ae1508},			/* 0.03997=f(0.04000)*/
{64, 0,123,__LINE__, 0x3fa99424, 0xe535f785, 0x3fa99999, 0x99999a27},			/* 0.04995=f(0.05000)*/
{64, 0,123,__LINE__, 0x3faeaee5, 0x7989b773, 0x3faeb851, 0xeb851f46},			/* 0.05992=f(0.06000)*/
{64, 0,123,__LINE__, 0x3fb1e40a, 0xad5c6495, 0x3fb1eb85, 0x1eb85232},			/* 0.06988=f(0.07000)*/
{64, 0,123,__LINE__, 0x3fb46fb9, 0x47945d05, 0x3fb47ae1, 0x47ae14c1},			/* 0.07982=f(0.08000)*/
{64, 0,123,__LINE__, 0x3fb6fa5d, 0xbe0ceb3c, 0x3fb70a3d, 0x70a3d750},			/* 0.08975=f(0.09000)*/
{64, 0,123,__LINE__, 0x3fb983d7, 0x795f417f, 0x3fb99999, 0x999999df},			/* 0.09966=f(0.10000)*/
{64, 0,123,__LINE__, 0x3fbc0c06, 0x1e921deb, 0x3fbc28f5, 0xc28f5c6e},			/* 0.10955=f(0.11000)*/
{64, 0,123,__LINE__, 0x3fbe92c9, 0x95746f18, 0x3fbeb851, 0xeb851efd},			/* 0.11942=f(0.12000)*/
{64, 0,123,__LINE__, 0x3fc08c01, 0x076dc0ee, 0x3fc0a3d7, 0x0a3d70c6},			/* 0.12927=f(0.13000)*/
{64, 0,123,__LINE__, 0x3fc1cdc8, 0x056118b0, 0x3fc1eb85, 0x1eb8520e},			/* 0.13909=f(0.14000)*/
{64, 0,123,__LINE__, 0x3fc30eaa, 0x2f235477, 0x3fc33333, 0x33333356},			/* 0.14888=f(0.15000)*/
{64, 0,123,__LINE__, 0x3fc44e98, 0x1cc22f98, 0x3fc47ae1, 0x47ae149e},			/* 0.15864=f(0.16000)*/
{64, 0,123,__LINE__, 0x3fc58d82, 0x96a405df, 0x3fc5c28f, 0x5c28f5e6},			/* 0.16838=f(0.17000)*/
{64, 0,123,__LINE__, 0x3fc6cb5a, 0x984db998, 0x3fc70a3d, 0x70a3d72e},			/* 0.17808=f(0.18000)*/
{64, 0,123,__LINE__, 0x3fc80811, 0x531380f8, 0x3fc851eb, 0x851eb876},			/* 0.18774=f(0.19000)*/
{64, 0,123,__LINE__, 0x3fc94398, 0x30b3a5b3, 0x3fc99999, 0x999999be},			/* 0.19737=f(0.20000)*/
{64, 0,123,__LINE__, 0x3fca7de0, 0xd5da50f7, 0x3fcae147, 0xae147b06},			/* 0.20696=f(0.21000)*/
{64, 0,123,__LINE__, 0x3fcbb6dd, 0x248d8d7a, 0x3fcc28f5, 0xc28f5c4e},			/* 0.21651=f(0.22000)*/
{64, 0,123,__LINE__, 0x3fccee7f, 0x3e80b991, 0x3fcd70a3, 0xd70a3d96},			/* 0.22602=f(0.23000)*/
{64, 0,123,__LINE__, 0x3fce24b9, 0x874eb3bc, 0x3fceb851, 0xeb851ede},			/* 0.23549=f(0.24000)*/
{64, 0,123,__LINE__, 0x3fcf597e, 0xa69a1caa, 0x3fd00000, 0x00000013},			/* 0.24491=f(0.25000)*/
{64, 0,123,__LINE__, 0x3fd04660, 0xc5098d66, 0x3fd0a3d7, 0x0a3d70b7},			/* 0.25429=f(0.26000)*/
{64, 0,123,__LINE__, 0x3fd0df3a, 0xb3b10e4e, 0x3fd147ae, 0x147ae15b},			/* 0.26362=f(0.27000)*/
{64, 0,123,__LINE__, 0x3fd17746, 0xdefb93f0, 0x3fd1eb85, 0x1eb851ff},			/* 0.27290=f(0.28000)*/
{64, 0,123,__LINE__, 0x3fd20e7f, 0x2c5eaab6, 0x3fd28f5c, 0x28f5c2a3},			/* 0.28213=f(0.29000)*/
{64, 0,123,__LINE__, 0x3fd2a4dd, 0xa7d9150c, 0x3fd33333, 0x33333347},			/* 0.29131=f(0.30000)*/
{64, 0,123,__LINE__, 0x3fd33a5c, 0x84b04755, 0x3fd3d70a, 0x3d70a3eb},			/* 0.30043=f(0.31000)*/
{64, 0,123,__LINE__, 0x3fd3cef6, 0x1e1f9ca2, 0x3fd47ae1, 0x47ae148f},			/* 0.30950=f(0.32000)*/
{64, 0,123,__LINE__, 0x3fd462a4, 0xf7f935f1, 0x3fd51eb8, 0x51eb8533},			/* 0.31852=f(0.33000)*/
{64, 0,123,__LINE__, 0x3fd4f563, 0xbf387dbb, 0x3fd5c28f, 0x5c28f5d7},			/* 0.32747=f(0.34000)*/
{64, 0,123,__LINE__, 0x3fd5872d, 0x4a8651e8, 0x3fd66666, 0x6666667b},			/* 0.33637=f(0.35000)*/
{64, 0,123,__LINE__, 0x3fd617fc, 0x9aaedde9, 0x3fd70a3d, 0x70a3d71f},			/* 0.34521=f(0.36000)*/
{64, 0,123,__LINE__, 0x3fd6a7cc, 0xdb093683, 0x3fd7ae14, 0x7ae147c3},			/* 0.35399=f(0.37000)*/
{64, 0,123,__LINE__, 0x3fd73699, 0x61d0d04f, 0x3fd851eb, 0x851eb867},			/* 0.36270=f(0.38000)*/
{64, 0,123,__LINE__, 0x3fd7c45d, 0xb070f10c, 0x3fd8f5c2, 0x8f5c290b},			/* 0.37136=f(0.39000)*/
{64, 0,123,__LINE__, 0x3fd85115, 0x73c242e8, 0x3fd99999, 0x999999af},			/* 0.37994=f(0.40000)*/
{64, 0,123,__LINE__, 0x3fd8dcbc, 0x843ab78b, 0x3fda3d70, 0xa3d70a53},			/* 0.38847=f(0.41000)*/
{64, 0,123,__LINE__, 0x3fd9674e, 0xe60fef07, 0x3fdae147, 0xae147af7},			/* 0.39693=f(0.42000)*/
{64, 0,123,__LINE__, 0x3fd9f0c8, 0xc94c5cdf, 0x3fdb851e, 0xb851eb9b},			/* 0.40532=f(0.43000)*/
{64, 0,123,__LINE__, 0x3fda7926, 0x89d76b1d, 0x3fdc28f5, 0xc28f5c3f},			/* 0.41364=f(0.44000)*/
{64, 0,123,__LINE__, 0x3fdb0064, 0xaf70e0cd, 0x3fdccccc, 0xcccccce3},			/* 0.42189=f(0.45000)*/
{64, 0,123,__LINE__, 0x3fdb867f, 0xed9fd654, 0x3fdd70a3, 0xd70a3d87},			/* 0.43008=f(0.46000)*/
{64, 0,123,__LINE__, 0x3fdc0b75, 0x239586c0, 0x3fde147a, 0xe147ae2b},			/* 0.43819=f(0.47000)*/
{64, 0,123,__LINE__, 0x3fdc8f41, 0x5c0451a6, 0x3fdeb851, 0xeb851ecf},			/* 0.44624=f(0.48000)*/
{64, 0,123,__LINE__, 0x3fdd11e1, 0xcceb451a, 0x3fdf5c28, 0xf5c28f73},			/* 0.45421=f(0.49000)*/
{64, 0,123,__LINE__, 0x3fdd9353, 0xd7568b05, 0x3fe00000, 0x0000000b},			/* 0.46211=f(0.50000)*/
{64, 0,123,__LINE__, 0x3fde1395, 0x07151869, 0x3fe051eb, 0x851eb85d},			/* 0.46994=f(0.51000)*/
{64, 0,123,__LINE__, 0x3fde92a3, 0x12640015, 0x3fe0a3d7, 0x0a3d70af},			/* 0.47770=f(0.52000)*/
{64, 0,123,__LINE__, 0x3fdf107b, 0xd98fcd02, 0x3fe0f5c2, 0x8f5c2901},			/* 0.48538=f(0.53000)*/
{64, 0,123,__LINE__, 0x3fdf8d1d, 0x668c4ab6, 0x3fe147ae, 0x147ae153},			/* 0.49298=f(0.54000)*/
{64, 0,123,__LINE__, 0x3fe00442, 0xf641920c, 0x3fe19999, 0x999999a5},			/* 0.50052=f(0.55000)*/
{64, 0,123,__LINE__, 0x3fe04159, 0xe3ace14c, 0x3fe1eb85, 0x1eb851f7},			/* 0.50797=f(0.56000)*/
{64, 0,123,__LINE__, 0x3fe07dd2, 0xbd976c8c, 0x3fe23d70, 0xa3d70a49},			/* 0.51535=f(0.57000)*/
{64, 0,123,__LINE__, 0x3fe0b9ac, 0xd9e80336, 0x3fe28f5c, 0x28f5c29b},			/* 0.52266=f(0.58000)*/
{62, 0,123,__LINE__, 0x3fe0f4e7, 0xa213fe51, 0x3fe2e147, 0xae147aed},			/* 0.52989=f(0.59000)*/
{64, 0,123,__LINE__, 0x3fe12f82, 0x92d2cd04, 0x3fe33333, 0x3333333f},			/* 0.53704=f(0.60000)*/
{64, 0,123,__LINE__, 0x3fe1697d, 0x3bce30a0, 0x3fe3851e, 0xb851eb91},			/* 0.54412=f(0.61000)*/
{64, 0,123,__LINE__, 0x3fe1a2d7, 0x3f4f5e9e, 0x3fe3d70a, 0x3d70a3e3},			/* 0.55112=f(0.62000)*/
{64, 0,123,__LINE__, 0x3fe1db90, 0x51e93ef0, 0x3fe428f5, 0xc28f5c35},			/* 0.55805=f(0.63000)*/
{62, 0,123,__LINE__, 0x3fe213a8, 0x3a1ffc6d, 0x3fe47ae1, 0x47ae1487},			/* 0.56489=f(0.64000)*/
{64, 0,123,__LINE__, 0x3fe24b1e, 0xd00e1cc4, 0x3fe4cccc, 0xccccccd9},			/* 0.57166=f(0.65000)*/
{64, 0,123,__LINE__, 0x3fe281f3, 0xfd0754c1, 0x3fe51eb8, 0x51eb852b},			/* 0.57836=f(0.66000)*/
{62, 0,123,__LINE__, 0x3fe2b827, 0xbb394cf6, 0x3fe570a3, 0xd70a3d7d},			/* 0.58497=f(0.67000)*/
{64, 0,123,__LINE__, 0x3fe2edba, 0x154a8a04, 0x3fe5c28f, 0x5c28f5cf},			/* 0.59151=f(0.68000)*/
{64, 0,123,__LINE__, 0x3fe322ab, 0x25f7aae8, 0x3fe6147a, 0xe147ae21},			/* 0.59798=f(0.69000)*/
{64, 0,123,__LINE__, 0x3fe356fb, 0x17af2e99, 0x3fe66666, 0x66666673},			/* 0.60436=f(0.70000)*/
{64, 0,123,__LINE__, 0x3fe38aaa, 0x242bf154, 0x3fe6b851, 0xeb851ec5},			/* 0.61067=f(0.71000)*/
{63, 0,123,__LINE__, 0x3fe3bdb8, 0x940e90a5, 0x3fe70a3d, 0x70a3d717},			/* 0.61690=f(0.72000)*/
{64, 0,123,__LINE__, 0x3fe3f026, 0xbe75e42a, 0x3fe75c28, 0xf5c28f69},			/* 0.62306=f(0.73000)*/
{64, 0,123,__LINE__, 0x3fe421f5, 0x0896b7ba, 0x3fe7ae14, 0x7ae147bb},			/* 0.62914=f(0.74000)*/
{64, 0,123,__LINE__, 0x3fe45323, 0xe552f230, 0x3fe80000, 0x0000000d},			/* 0.63514=f(0.75000)*/
{60, 0,123,__LINE__, 0x3fe483b3, 0xd4d052f8, 0x3fe851eb, 0x851eb85f},			/* 0.64107=f(0.76000)*/
{57, 0,123,__LINE__, 0x3fe4b3a5, 0x640eeec0, 0x3fe8a3d7, 0x0a3d70b1},			/* 0.64692=f(0.77000)*/
{64, 0,123,__LINE__, 0x3fe4e2f9, 0x2c7f928c, 0x3fe8f5c2, 0x8f5c2903},			/* 0.65270=f(0.78000)*/
{64, 0,123,__LINE__, 0x3fe511af, 0xd39a32c0, 0x3fe947ae, 0x147ae155},			/* 0.65840=f(0.79000)*/
{64, 0,123,__LINE__, 0x3fe53fca, 0x0a748a48, 0x3fe99999, 0x999999a7},			/* 0.66403=f(0.80000)*/
{64, 0,123,__LINE__, 0x3fe56d48, 0x8d590c7a, 0x3fe9eb85, 0x1eb851f9},			/* 0.66959=f(0.81000)*/
{64, 0,123,__LINE__, 0x3fe59a2c, 0x235e4ada, 0x3fea3d70, 0xa3d70a4b},			/* 0.67506=f(0.82000)*/
{64, 0,123,__LINE__, 0x3fe5c675, 0x9dfeee3e, 0x3fea8f5c, 0x28f5c29d},			/* 0.68047=f(0.83000)*/
{64, 0,123,__LINE__, 0x3fe5f225, 0xd8b2616e, 0x3feae147, 0xae147aef},			/* 0.68580=f(0.84000)*/
{60, 0,123,__LINE__, 0x3fe61d3d, 0xb88649b7, 0x3feb3333, 0x33333341},			/* 0.69106=f(0.85000)*/
{64, 0,123,__LINE__, 0x3fe647be, 0x2bb8e86e, 0x3feb851e, 0xb851eb93},			/* 0.69625=f(0.86000)*/
{64, 0,123,__LINE__, 0x3fe671a8, 0x29547eca, 0x3febd70a, 0x3d70a3e5},			/* 0.70137=f(0.87000)*/
{64, 0,123,__LINE__, 0x3fe69afc, 0xb0cbcc2e, 0x3fec28f5, 0xc28f5c37},			/* 0.70641=f(0.88000)*/
{61, 0,123,__LINE__, 0x3fe6c3bc, 0xc997bd2b, 0x3fec7ae1, 0x47ae1489},			/* 0.71139=f(0.89000)*/
{64, 0,123,__LINE__, 0x3fe6ebe9, 0x82d66063, 0x3feccccc, 0xccccccdb},			/* 0.71629=f(0.90000)*/
{64, 0,123,__LINE__, 0x3fe71383, 0xf2eb34c6, 0x3fed1eb8, 0x51eb852d},			/* 0.72113=f(0.91000)*/
{64, 0,123,__LINE__, 0x3fe73a8d, 0x3720e353, 0x3fed70a3, 0xd70a3d7f},			/* 0.72589=f(0.92000)*/
{62, 0,123,__LINE__, 0x3fe76106, 0x734c752e, 0x3fedc28f, 0x5c28f5d1},			/* 0.73059=f(0.93000)*/
{64, 0,123,__LINE__, 0x3fe786f0, 0xd1721552, 0x3fee147a, 0xe147ae23},			/* 0.73522=f(0.94000)*/
{64, 0,123,__LINE__, 0x3fe7ac4d, 0x816b6c14, 0x3fee6666, 0x66666675},			/* 0.73978=f(0.95000)*/
{64, 0,123,__LINE__, 0x3fe7d11d, 0xb88fa12c, 0x3feeb851, 0xeb851ec7},			/* 0.74427=f(0.96000)*/
{64, 0,123,__LINE__, 0x3fe7f562, 0xb15d0fd6, 0x3fef0a3d, 0x70a3d719},			/* 0.74870=f(0.97000)*/
{64, 0,123,__LINE__, 0x3fe8191d, 0xab24b74e, 0x3fef5c28, 0xf5c28f6b},			/* 0.75306=f(0.98000)*/
{64, 0,123,__LINE__, 0x3fe83c4f, 0xe9b770e8, 0x3fefae14, 0x7ae147bd},			/* 0.75736=f(0.99000)*/
{64, 0,123,__LINE__, 0x3fe85efa, 0xb514f39a, 0x3ff00000, 0x00000007},			/* 0.76159=f(1.00000)*/
{59, 0,123,__LINE__, 0x3fe8811f, 0x591cac0f, 0x3ff028f5, 0xc28f5c30},			/* 0.76576=f(1.01000)*/
{64, 0,123,__LINE__, 0x3fe8a2bf, 0x25406eea, 0x3ff051eb, 0x851eb859},			/* 0.76986=f(1.02000)*/
{63, 0,123,__LINE__, 0x3fe8c3db, 0x6c390a38, 0x3ff07ae1, 0x47ae1482},			/* 0.77390=f(1.03000)*/
{64, 0,123,__LINE__, 0x3fe8e475, 0x83bcb9d0, 0x3ff0a3d7, 0x0a3d70ab},			/* 0.77788=f(1.04000)*/
{64, 0,123,__LINE__, 0x3fe9048e, 0xc4378195, 0x3ff0cccc, 0xccccccd4},			/* 0.78180=f(1.05000)*/
{64, 0,123,__LINE__, 0x3fe92428, 0x88856fa8, 0x3ff0f5c2, 0x8f5c28fd},			/* 0.78566=f(1.06000)*/
{64, 0,123,__LINE__, 0x3fe94344, 0x2daec7aa, 0x3ff11eb8, 0x51eb8526},			/* 0.78946=f(1.07000)*/
{64, 0,123,__LINE__, 0x3fe961e3, 0x12a6177e, 0x3ff147ae, 0x147ae14f},			/* 0.79319=f(1.08000)*/
{64, 0,123,__LINE__, 0x3fe98006, 0x9808350c, 0x3ff170a3, 0xd70a3d78},			/* 0.79687=f(1.09000)*/
{64, 0,123,__LINE__, 0x3fe99db0, 0x1fde240a, 0x3ff19999, 0x999999a1},			/* 0.80049=f(1.10000)*/
{62, 0,123,__LINE__, 0x3fe9bae1, 0x0d60e1d2, 0x3ff1c28f, 0x5c28f5ca},			/* 0.80406=f(1.11000)*/
{63, 0,123,__LINE__, 0x3fe9d79a, 0xc4bf14eb, 0x3ff1eb85, 0x1eb851f3},			/* 0.80756=f(1.12000)*/
{64, 0,123,__LINE__, 0x3fe9f3de, 0xaae49d2d, 0x3ff2147a, 0xe147ae1c},			/* 0.81101=f(1.13000)*/
{64, 0,123,__LINE__, 0x3fea0fae, 0x254400d5, 0x3ff23d70, 0xa3d70a45},			/* 0.81441=f(1.14000)*/
{64, 0,123,__LINE__, 0x3fea2b0a, 0x99a1b25c, 0x3ff26666, 0x6666666e},			/* 0.81775=f(1.15000)*/
{64, 0,123,__LINE__, 0x3fea45f5, 0x6de12a70, 0x3ff28f5c, 0x28f5c297},			/* 0.82103=f(1.16000)*/
{64, 0,123,__LINE__, 0x3fea6070, 0x07d3d0dd, 0x3ff2b851, 0xeb851ec0},			/* 0.82427=f(1.17000)*/
{64, 0,123,__LINE__, 0x3fea7a7b, 0xcd09aed4, 0x3ff2e147, 0xae147ae9},			/* 0.82745=f(1.18000)*/
{64, 0,123,__LINE__, 0x3fea941a, 0x22a3e4ae, 0x3ff30a3d, 0x70a3d712},			/* 0.83057=f(1.19000)*/
{64, 0,123,__LINE__, 0xbfeffff1, 0x5f81f9ab, 0xc01921fb, 0x54442d18},			/* -0.99999=f(-6.28318)*/
{64, 0,123,__LINE__, 0xbfeffead, 0x8c8b7e1e, 0xc012d97c, 0x7f3321d2},			/* -0.99983=f(-4.71238)*/
{64, 0,123,__LINE__, 0xbfefe175, 0xfa292810, 0xc00921fb, 0x54442d18},			/* -0.99627=f(-3.14159)*/
{62, 0,123,__LINE__, 0xbfed594f, 0xdae482ba, 0xbff921fb, 0x54442d18},			/* -0.91715=f(-1.57079)*/
{64, 0,123,__LINE__, 0x80000000, 0x00000000, 0x00000000, 0x00000000},			/* 0.00000=f(0.00000)*/
{62, 0,123,__LINE__, 0x3fed594f, 0xdae482ba, 0x3ff921fb, 0x54442d18},			/* 0.91715=f(1.57079)*/
{64, 0,123,__LINE__, 0x3fefe175, 0xfa292810, 0x400921fb, 0x54442d18},			/* 0.99627=f(3.14159)*/
{64, 0,123,__LINE__, 0x3feffead, 0x8c8b7e1e, 0x4012d97c, 0x7f3321d2},			/* 0.99983=f(4.71238)*/
{64, 0,123,__LINE__, 0xbff00000, 0x00000000, 0xc03e0000, 0x00000000},			/* -1.00000=f(-30.0000)*/
{64, 0,123,__LINE__, 0xbff00000, 0x00000000, 0xc03c4ccc, 0xcccccccd},			/* -1.00000=f(-28.3000)*/
{64, 0,123,__LINE__, 0xbff00000, 0x00000000, 0xc03a9999, 0x9999999a},			/* -1.00000=f(-26.6000)*/
{64, 0,123,__LINE__, 0xbff00000, 0x00000000, 0xc038e666, 0x66666667},			/* -1.00000=f(-24.9000)*/
{64, 0,123,__LINE__, 0xbff00000, 0x00000000, 0xc0373333, 0x33333334},			/* -1.00000=f(-23.2000)*/
{64, 0,123,__LINE__, 0xbff00000, 0x00000000, 0xc0358000, 0x00000001},			/* -1.00000=f(-21.5000)*/
{64, 0,123,__LINE__, 0xbff00000, 0x00000000, 0xc033cccc, 0xccccccce},			/* -1.00000=f(-19.8000)*/
{64, 0,123,__LINE__, 0xbfefffff, 0xfffffffd, 0xc0321999, 0x9999999b},			/* -0.01000=f(-18.1000)*/
{64, 0,123,__LINE__, 0xbfefffff, 0xffffff99, 0xc0306666, 0x66666668},			/* -0.01000=f(-16.4000)*/
{64, 0,123,__LINE__, 0xbfefffff, 0xfffff400, 0xc02d6666, 0x6666666a},			/* -0.01000=f(-14.7000)*/
{64, 0,123,__LINE__, 0xbfefffff, 0xfffe987b, 0xc02a0000, 0x00000004},			/* -0.01000=f(-13.0000)*/
{64, 0,123,__LINE__, 0xbfefffff, 0xffd5eb4d, 0xc0269999, 0x9999999e},			/* -0.01000=f(-11.3000)*/
{64, 0,123,__LINE__, 0xbfefffff, 0xfb1315c8, 0xc0233333, 0x33333338},			/* -0.99999=f(-9.60000)*/
{64, 0,123,__LINE__, 0xbfefffff, 0x6c69d310, 0xc01f9999, 0x999999a3},			/* -0.99999=f(-7.90000)*/
{64, 0,123,__LINE__, 0xbfefffee, 0xb9b79e83, 0xc018cccc, 0xccccccd6},			/* -0.99999=f(-6.20000)*/
{64, 0,123,__LINE__, 0xbfeffdfa, 0x72153984, 0xc0120000, 0x00000009},			/* -0.99975=f(-4.50000)*/
{64, 0,123,__LINE__, 0xbfefc3a3, 0x2d87c373, 0xc0066666, 0x66666678},			/* -0.99263=f(-2.80000)*/
{64, 0,123,__LINE__, 0xbfe99db0, 0x1fde241f, 0xbff19999, 0x999999bd},			/* -0.80049=f(-1.10000)*/
{62, 0,123,__LINE__, 0x3fe12f82, 0x92d2ccc9, 0x3fe33333, 0x333332ec},			/* 0.53704=f(0.60000)*/
{64, 0,123,__LINE__, 0x3fef5cf3, 0x1e1c8100, 0x40026666, 0x66666654},			/* 0.98009=f(2.30000)*/
{64, 0,123,__LINE__, 0x3feffa81, 0x708a0b42, 0x400fffff, 0xffffffee},			/* 0.99932=f(4.00000)*/
{64, 0,123,__LINE__, 0x3fefffd1, 0x0b130302, 0x4016cccc, 0xccccccc4},			/* 0.99997=f(5.70000)*/
{64, 0,123,__LINE__, 0x3feffffe, 0x6ed16c4d, 0x401d9999, 0x99999991},			/* 0.99999=f(7.40000)*/
{64, 0,123,__LINE__, 0x3fefffff, 0xf29c7a5a, 0x40223333, 0x3333332f},			/* 0.99999=f(9.10000)*/
{64, 0,123,__LINE__, 0x3fefffff, 0xff8d9cc5, 0x40259999, 0x99999995},			/* 0.01000=f(10.8000)*/
{64, 0,123,__LINE__, 0x3fefffff, 0xfffc2eb9, 0x4028ffff, 0xfffffffb},			/* 0.01000=f(12.5000)*/
{64, 0,123,__LINE__, 0x3fefffff, 0xffffdf63, 0x402c6666, 0x66666661},			/* 0.01000=f(14.2000)*/
{64, 0,123,__LINE__, 0x3fefffff, 0xfffffee9, 0x402fcccc, 0xccccccc7},			/* 0.01000=f(15.9000)*/
{64, 0,123,__LINE__, 0x3fefffff, 0xfffffff7, 0x40319999, 0x99999997},			/* 0.01000=f(17.6000)*/
{64, 0,123,__LINE__, 0x3ff00000, 0x00000000, 0x40334ccc, 0xccccccca},			/* 1.00000=f(19.3000)*/
{64, 0,123,__LINE__, 0x3ff00000, 0x00000000, 0x4034ffff, 0xfffffffd},			/* 1.00000=f(21.0000)*/
{64, 0,123,__LINE__, 0x3ff00000, 0x00000000, 0x4036b333, 0x33333330},			/* 1.00000=f(22.7000)*/
{64, 0,123,__LINE__, 0x3ff00000, 0x00000000, 0x40386666, 0x66666663},			/* 1.00000=f(24.4000)*/
{64, 0,123,__LINE__, 0x3ff00000, 0x00000000, 0x403a1999, 0x99999996},			/* 1.00000=f(26.1000)*/
{64, 0,123,__LINE__, 0x3ff00000, 0x00000000, 0x403bcccc, 0xccccccc9},			/* 1.00000=f(27.8000)*/
{64, 0,123,__LINE__, 0x3ff00000, 0x00000000, 0x403d7fff, 0xfffffffc},			/* 1.00000=f(29.5000)*/
0,};
test_tanh(m)   {run_vector_1(m,tanh_vec,(char *)(tanh),"tanh","dd");   }	
