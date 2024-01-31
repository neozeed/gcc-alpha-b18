#include "test.h"
 one_line_type ceilf_vec[] = {
{ 0, 0,123,__LINE__, 0xbff00000, 0x00000000, 0xbff33333, 0x33333333},			/* -1.00000=f(-1.20000)*/
{ 0, 0,123,__LINE__, 0xbff00000, 0x00000000, 0xbff30a3d, 0x70a3d70a},			/* -1.00000=f(-1.19000)*/
{ 0, 0,123,__LINE__, 0xbff00000, 0x00000000, 0xbff2e147, 0xae147ae1},			/* -1.00000=f(-1.18000)*/
{ 0, 0,123,__LINE__, 0xbff00000, 0x00000000, 0xbff2b851, 0xeb851eb8},			/* -1.00000=f(-1.17000)*/
{ 0, 0,123,__LINE__, 0xbff00000, 0x00000000, 0xbff28f5c, 0x28f5c28f},			/* -1.00000=f(-1.16000)*/
{ 0, 0,123,__LINE__, 0xbff00000, 0x00000000, 0xbff26666, 0x66666666},			/* -1.00000=f(-1.15000)*/
{ 0, 0,123,__LINE__, 0xbff00000, 0x00000000, 0xbff23d70, 0xa3d70a3d},			/* -1.00000=f(-1.14000)*/
{ 0, 0,123,__LINE__, 0xbff00000, 0x00000000, 0xbff2147a, 0xe147ae14},			/* -1.00000=f(-1.13000)*/
{ 0, 0,123,__LINE__, 0xbff00000, 0x00000000, 0xbff1eb85, 0x1eb851eb},			/* -1.00000=f(-1.12000)*/
{ 0, 0,123,__LINE__, 0xbff00000, 0x00000000, 0xbff1c28f, 0x5c28f5c2},			/* -1.00000=f(-1.11000)*/
{ 0, 0,123,__LINE__, 0xbff00000, 0x00000000, 0xbff19999, 0x99999999},			/* -1.00000=f(-1.10000)*/
{ 0, 0,123,__LINE__, 0xbff00000, 0x00000000, 0xbff170a3, 0xd70a3d70},			/* -1.00000=f(-1.09000)*/
{ 0, 0,123,__LINE__, 0xbff00000, 0x00000000, 0xbff147ae, 0x147ae147},			/* -1.00000=f(-1.08000)*/
{ 0, 0,123,__LINE__, 0xbff00000, 0x00000000, 0xbff11eb8, 0x51eb851e},			/* -1.00000=f(-1.07000)*/
{ 0, 0,123,__LINE__, 0xbff00000, 0x00000000, 0xbff0f5c2, 0x8f5c28f5},			/* -1.00000=f(-1.06000)*/
{ 0, 0,123,__LINE__, 0xbff00000, 0x00000000, 0xbff0cccc, 0xcccccccc},			/* -1.00000=f(-1.05000)*/
{ 0, 0,123,__LINE__, 0xbff00000, 0x00000000, 0xbff0a3d7, 0x0a3d70a3},			/* -1.00000=f(-1.04000)*/
{ 0, 0,123,__LINE__, 0xbff00000, 0x00000000, 0xbff07ae1, 0x47ae147a},			/* -1.00000=f(-1.03000)*/
{ 0, 0,123,__LINE__, 0xbff00000, 0x00000000, 0xbff051eb, 0x851eb851},			/* -1.00000=f(-1.02000)*/
{ 0, 0,123,__LINE__, 0xbff00000, 0x00000000, 0xbff028f5, 0xc28f5c28},			/* -1.00000=f(-1.01000)*/
{ 0, 0,123,__LINE__, 0xbff00000, 0x00000000, 0xbfefffff, 0xfffffffe},			/* -1.00000=f(-0.01000)*/
{64, 0,123,__LINE__, 0x00000000, 0x00000000, 0xbfefae14, 0x7ae147ac},			/* 0.00000=f(-0.99000)*/
{64, 0,123,__LINE__, 0x00000000, 0x00000000, 0xbfef5c28, 0xf5c28f5a},			/* 0.00000=f(-0.98000)*/
{64, 0,123,__LINE__, 0x00000000, 0x00000000, 0xbfef0a3d, 0x70a3d708},			/* 0.00000=f(-0.97000)*/
{64, 0,123,__LINE__, 0x00000000, 0x00000000, 0xbfeeb851, 0xeb851eb6},			/* 0.00000=f(-0.96000)*/
{64, 0,123,__LINE__, 0x00000000, 0x00000000, 0xbfee6666, 0x66666664},			/* 0.00000=f(-0.95000)*/
{64, 0,123,__LINE__, 0x00000000, 0x00000000, 0xbfee147a, 0xe147ae12},			/* 0.00000=f(-0.94000)*/
{64, 0,123,__LINE__, 0x00000000, 0x00000000, 0xbfedc28f, 0x5c28f5c0},			/* 0.00000=f(-0.93000)*/
{64, 0,123,__LINE__, 0x00000000, 0x00000000, 0xbfed70a3, 0xd70a3d6e},			/* 0.00000=f(-0.92000)*/
{64, 0,123,__LINE__, 0x00000000, 0x00000000, 0xbfed1eb8, 0x51eb851c},			/* 0.00000=f(-0.91000)*/
{64, 0,123,__LINE__, 0x00000000, 0x00000000, 0xbfeccccc, 0xccccccca},			/* 0.00000=f(-0.90000)*/
{64, 0,123,__LINE__, 0x00000000, 0x00000000, 0xbfec7ae1, 0x47ae1478},			/* 0.00000=f(-0.89000)*/
{64, 0,123,__LINE__, 0x00000000, 0x00000000, 0xbfec28f5, 0xc28f5c26},			/* 0.00000=f(-0.88000)*/
{64, 0,123,__LINE__, 0x00000000, 0x00000000, 0xbfebd70a, 0x3d70a3d4},			/* 0.00000=f(-0.87000)*/
{64, 0,123,__LINE__, 0x00000000, 0x00000000, 0xbfeb851e, 0xb851eb82},			/* 0.00000=f(-0.86000)*/
{64, 0,123,__LINE__, 0x00000000, 0x00000000, 0xbfeb3333, 0x33333330},			/* 0.00000=f(-0.85000)*/
{64, 0,123,__LINE__, 0x00000000, 0x00000000, 0xbfeae147, 0xae147ade},			/* 0.00000=f(-0.84000)*/
{64, 0,123,__LINE__, 0x00000000, 0x00000000, 0xbfea8f5c, 0x28f5c28c},			/* 0.00000=f(-0.83000)*/
{64, 0,123,__LINE__, 0x00000000, 0x00000000, 0xbfea3d70, 0xa3d70a3a},			/* 0.00000=f(-0.82000)*/
{64, 0,123,__LINE__, 0x00000000, 0x00000000, 0xbfe9eb85, 0x1eb851e8},			/* 0.00000=f(-0.81000)*/
{64, 0,123,__LINE__, 0x00000000, 0x00000000, 0xbfe99999, 0x99999996},			/* 0.00000=f(-0.80000)*/
{64, 0,123,__LINE__, 0x00000000, 0x00000000, 0xbfe947ae, 0x147ae144},			/* 0.00000=f(-0.79000)*/
{64, 0,123,__LINE__, 0x00000000, 0x00000000, 0xbfe8f5c2, 0x8f5c28f2},			/* 0.00000=f(-0.78000)*/
{64, 0,123,__LINE__, 0x00000000, 0x00000000, 0xbfe8a3d7, 0x0a3d70a0},			/* 0.00000=f(-0.77000)*/
{64, 0,123,__LINE__, 0x00000000, 0x00000000, 0xbfe851eb, 0x851eb84e},			/* 0.00000=f(-0.76000)*/
{64, 0,123,__LINE__, 0x00000000, 0x00000000, 0xbfe7ffff, 0xfffffffc},			/* 0.00000=f(-0.75000)*/
{64, 0,123,__LINE__, 0x00000000, 0x00000000, 0xbfe7ae14, 0x7ae147aa},			/* 0.00000=f(-0.74000)*/
{64, 0,123,__LINE__, 0x00000000, 0x00000000, 0xbfe75c28, 0xf5c28f58},			/* 0.00000=f(-0.73000)*/
{64, 0,123,__LINE__, 0x00000000, 0x00000000, 0xbfe70a3d, 0x70a3d706},			/* 0.00000=f(-0.72000)*/
{64, 0,123,__LINE__, 0x00000000, 0x00000000, 0xbfe6b851, 0xeb851eb4},			/* 0.00000=f(-0.71000)*/
{64, 0,123,__LINE__, 0x00000000, 0x00000000, 0xbfe66666, 0x66666662},			/* 0.00000=f(-0.70000)*/
{64, 0,123,__LINE__, 0x00000000, 0x00000000, 0xbfe6147a, 0xe147ae10},			/* 0.00000=f(-0.69000)*/
{64, 0,123,__LINE__, 0x00000000, 0x00000000, 0xbfe5c28f, 0x5c28f5be},			/* 0.00000=f(-0.68000)*/
{64, 0,123,__LINE__, 0x00000000, 0x00000000, 0xbfe570a3, 0xd70a3d6c},			/* 0.00000=f(-0.67000)*/
{64, 0,123,__LINE__, 0x00000000, 0x00000000, 0xbfe51eb8, 0x51eb851a},			/* 0.00000=f(-0.66000)*/
{64, 0,123,__LINE__, 0x00000000, 0x00000000, 0xbfe4cccc, 0xccccccc8},			/* 0.00000=f(-0.65000)*/
{64, 0,123,__LINE__, 0x00000000, 0x00000000, 0xbfe47ae1, 0x47ae1476},			/* 0.00000=f(-0.64000)*/
{64, 0,123,__LINE__, 0x00000000, 0x00000000, 0xbfe428f5, 0xc28f5c24},			/* 0.00000=f(-0.63000)*/
{64, 0,123,__LINE__, 0x00000000, 0x00000000, 0xbfe3d70a, 0x3d70a3d2},			/* 0.00000=f(-0.62000)*/
{64, 0,123,__LINE__, 0x00000000, 0x00000000, 0xbfe3851e, 0xb851eb80},			/* 0.00000=f(-0.61000)*/
{64, 0,123,__LINE__, 0x00000000, 0x00000000, 0xbfe33333, 0x3333332e},			/* 0.00000=f(-0.60000)*/
{64, 0,123,__LINE__, 0x00000000, 0x00000000, 0xbfe2e147, 0xae147adc},			/* 0.00000=f(-0.59000)*/
{64, 0,123,__LINE__, 0x00000000, 0x00000000, 0xbfe28f5c, 0x28f5c28a},			/* 0.00000=f(-0.58000)*/
{64, 0,123,__LINE__, 0x00000000, 0x00000000, 0xbfe23d70, 0xa3d70a38},			/* 0.00000=f(-0.57000)*/
{64, 0,123,__LINE__, 0x00000000, 0x00000000, 0xbfe1eb85, 0x1eb851e6},			/* 0.00000=f(-0.56000)*/
{64, 0,123,__LINE__, 0x00000000, 0x00000000, 0xbfe19999, 0x99999994},			/* 0.00000=f(-0.55000)*/
{64, 0,123,__LINE__, 0x00000000, 0x00000000, 0xbfe147ae, 0x147ae142},			/* 0.00000=f(-0.54000)*/
{64, 0,123,__LINE__, 0x00000000, 0x00000000, 0xbfe0f5c2, 0x8f5c28f0},			/* 0.00000=f(-0.53000)*/
{64, 0,123,__LINE__, 0x00000000, 0x00000000, 0xbfe0a3d7, 0x0a3d709e},			/* 0.00000=f(-0.52000)*/
{64, 0,123,__LINE__, 0x00000000, 0x00000000, 0xbfe051eb, 0x851eb84c},			/* 0.00000=f(-0.51000)*/
{64, 0,123,__LINE__, 0x00000000, 0x00000000, 0xbfdfffff, 0xfffffff4},			/* 0.00000=f(-0.50000)*/
{64, 0,123,__LINE__, 0x00000000, 0x00000000, 0xbfdf5c28, 0xf5c28f50},			/* 0.00000=f(-0.49000)*/
{64, 0,123,__LINE__, 0x00000000, 0x00000000, 0xbfdeb851, 0xeb851eac},			/* 0.00000=f(-0.48000)*/
{64, 0,123,__LINE__, 0x00000000, 0x00000000, 0xbfde147a, 0xe147ae08},			/* 0.00000=f(-0.47000)*/
{64, 0,123,__LINE__, 0x00000000, 0x00000000, 0xbfdd70a3, 0xd70a3d64},			/* 0.00000=f(-0.46000)*/
{64, 0,123,__LINE__, 0x00000000, 0x00000000, 0xbfdccccc, 0xccccccc0},			/* 0.00000=f(-0.45000)*/
{64, 0,123,__LINE__, 0x00000000, 0x00000000, 0xbfdc28f5, 0xc28f5c1c},			/* 0.00000=f(-0.44000)*/
{64, 0,123,__LINE__, 0x00000000, 0x00000000, 0xbfdb851e, 0xb851eb78},			/* 0.00000=f(-0.43000)*/
{64, 0,123,__LINE__, 0x00000000, 0x00000000, 0xbfdae147, 0xae147ad4},			/* 0.00000=f(-0.42000)*/
{64, 0,123,__LINE__, 0x00000000, 0x00000000, 0xbfda3d70, 0xa3d70a30},			/* 0.00000=f(-0.41000)*/
{64, 0,123,__LINE__, 0x00000000, 0x00000000, 0xbfd99999, 0x9999998c},			/* 0.00000=f(-0.40000)*/
{64, 0,123,__LINE__, 0x00000000, 0x00000000, 0xbfd8f5c2, 0x8f5c28e8},			/* 0.00000=f(-0.39000)*/
{64, 0,123,__LINE__, 0x00000000, 0x00000000, 0xbfd851eb, 0x851eb844},			/* 0.00000=f(-0.38000)*/
{64, 0,123,__LINE__, 0x00000000, 0x00000000, 0xbfd7ae14, 0x7ae147a0},			/* 0.00000=f(-0.37000)*/
{64, 0,123,__LINE__, 0x00000000, 0x00000000, 0xbfd70a3d, 0x70a3d6fc},			/* 0.00000=f(-0.36000)*/
{64, 0,123,__LINE__, 0x00000000, 0x00000000, 0xbfd66666, 0x66666658},			/* 0.00000=f(-0.35000)*/
{64, 0,123,__LINE__, 0x00000000, 0x00000000, 0xbfd5c28f, 0x5c28f5b4},			/* 0.00000=f(-0.34000)*/
{64, 0,123,__LINE__, 0x00000000, 0x00000000, 0xbfd51eb8, 0x51eb8510},			/* 0.00000=f(-0.33000)*/
{64, 0,123,__LINE__, 0x00000000, 0x00000000, 0xbfd47ae1, 0x47ae146c},			/* 0.00000=f(-0.32000)*/
{64, 0,123,__LINE__, 0x00000000, 0x00000000, 0xbfd3d70a, 0x3d70a3c8},			/* 0.00000=f(-0.31000)*/
{64, 0,123,__LINE__, 0x00000000, 0x00000000, 0xbfd33333, 0x33333324},			/* 0.00000=f(-0.30000)*/
{64, 0,123,__LINE__, 0x00000000, 0x00000000, 0xbfd28f5c, 0x28f5c280},			/* 0.00000=f(-0.29000)*/
{64, 0,123,__LINE__, 0x00000000, 0x00000000, 0xbfd1eb85, 0x1eb851dc},			/* 0.00000=f(-0.28000)*/
{64, 0,123,__LINE__, 0x00000000, 0x00000000, 0xbfd147ae, 0x147ae138},			/* 0.00000=f(-0.27000)*/
{64, 0,123,__LINE__, 0x00000000, 0x00000000, 0xbfd0a3d7, 0x0a3d7094},			/* 0.00000=f(-0.26000)*/
{64, 0,123,__LINE__, 0x00000000, 0x00000000, 0xbfcfffff, 0xffffffe0},			/* 0.00000=f(-0.25000)*/
{64, 0,123,__LINE__, 0x00000000, 0x00000000, 0xbfceb851, 0xeb851e98},			/* 0.00000=f(-0.24000)*/
{64, 0,123,__LINE__, 0x00000000, 0x00000000, 0xbfcd70a3, 0xd70a3d50},			/* 0.00000=f(-0.23000)*/
{64, 0,123,__LINE__, 0x00000000, 0x00000000, 0xbfcc28f5, 0xc28f5c08},			/* 0.00000=f(-0.22000)*/
{64, 0,123,__LINE__, 0x00000000, 0x00000000, 0xbfcae147, 0xae147ac0},			/* 0.00000=f(-0.21000)*/
{64, 0,123,__LINE__, 0x00000000, 0x00000000, 0xbfc99999, 0x99999978},			/* 0.00000=f(-0.20000)*/
{64, 0,123,__LINE__, 0x00000000, 0x00000000, 0xbfc851eb, 0x851eb830},			/* 0.00000=f(-0.19000)*/
{64, 0,123,__LINE__, 0x00000000, 0x00000000, 0xbfc70a3d, 0x70a3d6e8},			/* 0.00000=f(-0.18000)*/
{64, 0,123,__LINE__, 0x00000000, 0x00000000, 0xbfc5c28f, 0x5c28f5a0},			/* 0.00000=f(-0.17000)*/
{64, 0,123,__LINE__, 0x00000000, 0x00000000, 0xbfc47ae1, 0x47ae1458},			/* 0.00000=f(-0.16000)*/
{64, 0,123,__LINE__, 0x00000000, 0x00000000, 0xbfc33333, 0x33333310},			/* 0.00000=f(-0.15000)*/
{64, 0,123,__LINE__, 0x00000000, 0x00000000, 0xbfc1eb85, 0x1eb851c8},			/* 0.00000=f(-0.14000)*/
{64, 0,123,__LINE__, 0x00000000, 0x00000000, 0xbfc0a3d7, 0x0a3d7080},			/* 0.00000=f(-0.13000)*/
{64, 0,123,__LINE__, 0x00000000, 0x00000000, 0xbfbeb851, 0xeb851e71},			/* 0.00000=f(-0.12000)*/
{64, 0,123,__LINE__, 0x00000000, 0x00000000, 0xbfbc28f5, 0xc28f5be2},			/* 0.00000=f(-0.11000)*/
{64, 0,123,__LINE__, 0x00000000, 0x00000000, 0xbfb99999, 0x99999953},			/* 0.00000=f(-0.00100)*/
{64, 0,123,__LINE__, 0x00000000, 0x00000000, 0xbfb70a3d, 0x70a3d6c4},			/* 0.00000=f(-0.09000)*/
{64, 0,123,__LINE__, 0x00000000, 0x00000000, 0xbfb47ae1, 0x47ae1435},			/* 0.00000=f(-0.08000)*/
{64, 0,123,__LINE__, 0x00000000, 0x00000000, 0xbfb1eb85, 0x1eb851a6},			/* 0.00000=f(-0.07000)*/
{64, 0,123,__LINE__, 0x00000000, 0x00000000, 0xbfaeb851, 0xeb851e2d},			/* 0.00000=f(-0.06000)*/
{64, 0,123,__LINE__, 0x00000000, 0x00000000, 0xbfa99999, 0x9999990e},			/* 0.00000=f(-0.05000)*/
{64, 0,123,__LINE__, 0x00000000, 0x00000000, 0xbfa47ae1, 0x47ae13ef},			/* 0.00000=f(-0.04000)*/
{64, 0,123,__LINE__, 0x00000000, 0x00000000, 0xbf9eb851, 0xeb851da0},			/* 0.00000=f(-0.03000)*/
{64, 0,123,__LINE__, 0x00000000, 0x00000000, 0xbf947ae1, 0x47ae1362},			/* 0.00000=f(-0.02000)*/
{64, 0,123,__LINE__, 0x00000000, 0x00000000, 0xbf847ae1, 0x47ae1249},			/* 0.00000=f(-0.00010)*/
{ 2, 0,123,__LINE__, 0x3ff00000, 0x00000000, 0x3cd19000, 0x00000000},			/* 1.00000=f(9.74915e-16)*/
{12, 0,123,__LINE__, 0x3ff00000, 0x00000000, 0x3f847ae1, 0x47ae16ad},			/* 1.00000=f(0.01000)*/
{12, 0,123,__LINE__, 0x3ff00000, 0x00000000, 0x3f947ae1, 0x47ae1594},			/* 1.00000=f(0.02000)*/
{12, 0,123,__LINE__, 0x3ff00000, 0x00000000, 0x3f9eb851, 0xeb851fd2},			/* 1.00000=f(0.03000)*/
{12, 0,123,__LINE__, 0x3ff00000, 0x00000000, 0x3fa47ae1, 0x47ae1508},			/* 1.00000=f(0.04000)*/
{12, 0,123,__LINE__, 0x3ff00000, 0x00000000, 0x3fa99999, 0x99999a27},			/* 1.00000=f(0.05000)*/
{12, 0,123,__LINE__, 0x3ff00000, 0x00000000, 0x3faeb851, 0xeb851f46},			/* 1.00000=f(0.06000)*/
{12, 0,123,__LINE__, 0x3ff00000, 0x00000000, 0x3fb1eb85, 0x1eb85232},			/* 1.00000=f(0.07000)*/
{12, 0,123,__LINE__, 0x3ff00000, 0x00000000, 0x3fb47ae1, 0x47ae14c1},			/* 1.00000=f(0.08000)*/
{12, 0,123,__LINE__, 0x3ff00000, 0x00000000, 0x3fb70a3d, 0x70a3d750},			/* 1.00000=f(0.09000)*/
{12, 0,123,__LINE__, 0x3ff00000, 0x00000000, 0x3fb99999, 0x999999df},			/* 1.00000=f(0.10000)*/
{12, 0,123,__LINE__, 0x3ff00000, 0x00000000, 0x3fbc28f5, 0xc28f5c6e},			/* 1.00000=f(0.11000)*/
{12, 0,123,__LINE__, 0x3ff00000, 0x00000000, 0x3fbeb851, 0xeb851efd},			/* 1.00000=f(0.12000)*/
{12, 0,123,__LINE__, 0x3ff00000, 0x00000000, 0x3fc0a3d7, 0x0a3d70c6},			/* 1.00000=f(0.13000)*/
{12, 0,123,__LINE__, 0x3ff00000, 0x00000000, 0x3fc1eb85, 0x1eb8520e},			/* 1.00000=f(0.14000)*/
{12, 0,123,__LINE__, 0x3ff00000, 0x00000000, 0x3fc33333, 0x33333356},			/* 1.00000=f(0.15000)*/
{12, 0,123,__LINE__, 0x3ff00000, 0x00000000, 0x3fc47ae1, 0x47ae149e},			/* 1.00000=f(0.16000)*/
{12, 0,123,__LINE__, 0x3ff00000, 0x00000000, 0x3fc5c28f, 0x5c28f5e6},			/* 1.00000=f(0.17000)*/
{12, 0,123,__LINE__, 0x3ff00000, 0x00000000, 0x3fc70a3d, 0x70a3d72e},			/* 1.00000=f(0.18000)*/
{12, 0,123,__LINE__, 0x3ff00000, 0x00000000, 0x3fc851eb, 0x851eb876},			/* 1.00000=f(0.19000)*/
{12, 0,123,__LINE__, 0x3ff00000, 0x00000000, 0x3fc99999, 0x999999be},			/* 1.00000=f(0.20000)*/
{12, 0,123,__LINE__, 0x3ff00000, 0x00000000, 0x3fcae147, 0xae147b06},			/* 1.00000=f(0.21000)*/
{12, 0,123,__LINE__, 0x3ff00000, 0x00000000, 0x3fcc28f5, 0xc28f5c4e},			/* 1.00000=f(0.22000)*/
{12, 0,123,__LINE__, 0x3ff00000, 0x00000000, 0x3fcd70a3, 0xd70a3d96},			/* 1.00000=f(0.23000)*/
{12, 0,123,__LINE__, 0x3ff00000, 0x00000000, 0x3fceb851, 0xeb851ede},			/* 1.00000=f(0.24000)*/
{12, 0,123,__LINE__, 0x3ff00000, 0x00000000, 0x3fd00000, 0x00000013},			/* 1.00000=f(0.25000)*/
{12, 0,123,__LINE__, 0x3ff00000, 0x00000000, 0x3fd0a3d7, 0x0a3d70b7},			/* 1.00000=f(0.26000)*/
{12, 0,123,__LINE__, 0x3ff00000, 0x00000000, 0x3fd147ae, 0x147ae15b},			/* 1.00000=f(0.27000)*/
{12, 0,123,__LINE__, 0x3ff00000, 0x00000000, 0x3fd1eb85, 0x1eb851ff},			/* 1.00000=f(0.28000)*/
{12, 0,123,__LINE__, 0x3ff00000, 0x00000000, 0x3fd28f5c, 0x28f5c2a3},			/* 1.00000=f(0.29000)*/
{12, 0,123,__LINE__, 0x3ff00000, 0x00000000, 0x3fd33333, 0x33333347},			/* 1.00000=f(0.30000)*/
{12, 0,123,__LINE__, 0x3ff00000, 0x00000000, 0x3fd3d70a, 0x3d70a3eb},			/* 1.00000=f(0.31000)*/
{12, 0,123,__LINE__, 0x3ff00000, 0x00000000, 0x3fd47ae1, 0x47ae148f},			/* 1.00000=f(0.32000)*/
{12, 0,123,__LINE__, 0x3ff00000, 0x00000000, 0x3fd51eb8, 0x51eb8533},			/* 1.00000=f(0.33000)*/
{12, 0,123,__LINE__, 0x3ff00000, 0x00000000, 0x3fd5c28f, 0x5c28f5d7},			/* 1.00000=f(0.34000)*/
{12, 0,123,__LINE__, 0x3ff00000, 0x00000000, 0x3fd66666, 0x6666667b},			/* 1.00000=f(0.35000)*/
{12, 0,123,__LINE__, 0x3ff00000, 0x00000000, 0x3fd70a3d, 0x70a3d71f},			/* 1.00000=f(0.36000)*/
{12, 0,123,__LINE__, 0x3ff00000, 0x00000000, 0x3fd7ae14, 0x7ae147c3},			/* 1.00000=f(0.37000)*/
{12, 0,123,__LINE__, 0x3ff00000, 0x00000000, 0x3fd851eb, 0x851eb867},			/* 1.00000=f(0.38000)*/
{12, 0,123,__LINE__, 0x3ff00000, 0x00000000, 0x3fd8f5c2, 0x8f5c290b},			/* 1.00000=f(0.39000)*/
{12, 0,123,__LINE__, 0x3ff00000, 0x00000000, 0x3fd99999, 0x999999af},			/* 1.00000=f(0.40000)*/
{12, 0,123,__LINE__, 0x3ff00000, 0x00000000, 0x3fda3d70, 0xa3d70a53},			/* 1.00000=f(0.41000)*/
{12, 0,123,__LINE__, 0x3ff00000, 0x00000000, 0x3fdae147, 0xae147af7},			/* 1.00000=f(0.42000)*/
{12, 0,123,__LINE__, 0x3ff00000, 0x00000000, 0x3fdb851e, 0xb851eb9b},			/* 1.00000=f(0.43000)*/
{12, 0,123,__LINE__, 0x3ff00000, 0x00000000, 0x3fdc28f5, 0xc28f5c3f},			/* 1.00000=f(0.44000)*/
{12, 0,123,__LINE__, 0x3ff00000, 0x00000000, 0x3fdccccc, 0xcccccce3},			/* 1.00000=f(0.45000)*/
{12, 0,123,__LINE__, 0x3ff00000, 0x00000000, 0x3fdd70a3, 0xd70a3d87},			/* 1.00000=f(0.46000)*/
{12, 0,123,__LINE__, 0x3ff00000, 0x00000000, 0x3fde147a, 0xe147ae2b},			/* 1.00000=f(0.47000)*/
{12, 0,123,__LINE__, 0x3ff00000, 0x00000000, 0x3fdeb851, 0xeb851ecf},			/* 1.00000=f(0.48000)*/
{12, 0,123,__LINE__, 0x3ff00000, 0x00000000, 0x3fdf5c28, 0xf5c28f73},			/* 1.00000=f(0.49000)*/
{12, 0,123,__LINE__, 0x3ff00000, 0x00000000, 0x3fe00000, 0x0000000b},			/* 1.00000=f(0.50000)*/
{12, 0,123,__LINE__, 0x3ff00000, 0x00000000, 0x3fe051eb, 0x851eb85d},			/* 1.00000=f(0.51000)*/
{12, 0,123,__LINE__, 0x3ff00000, 0x00000000, 0x3fe0a3d7, 0x0a3d70af},			/* 1.00000=f(0.52000)*/
{12, 0,123,__LINE__, 0x3ff00000, 0x00000000, 0x3fe0f5c2, 0x8f5c2901},			/* 1.00000=f(0.53000)*/
{12, 0,123,__LINE__, 0x3ff00000, 0x00000000, 0x3fe147ae, 0x147ae153},			/* 1.00000=f(0.54000)*/
{12, 0,123,__LINE__, 0x3ff00000, 0x00000000, 0x3fe19999, 0x999999a5},			/* 1.00000=f(0.55000)*/
{12, 0,123,__LINE__, 0x3ff00000, 0x00000000, 0x3fe1eb85, 0x1eb851f7},			/* 1.00000=f(0.56000)*/
{12, 0,123,__LINE__, 0x3ff00000, 0x00000000, 0x3fe23d70, 0xa3d70a49},			/* 1.00000=f(0.57000)*/
{12, 0,123,__LINE__, 0x3ff00000, 0x00000000, 0x3fe28f5c, 0x28f5c29b},			/* 1.00000=f(0.58000)*/
{12, 0,123,__LINE__, 0x3ff00000, 0x00000000, 0x3fe2e147, 0xae147aed},			/* 1.00000=f(0.59000)*/
{12, 0,123,__LINE__, 0x3ff00000, 0x00000000, 0x3fe33333, 0x3333333f},			/* 1.00000=f(0.60000)*/
{12, 0,123,__LINE__, 0x3ff00000, 0x00000000, 0x3fe3851e, 0xb851eb91},			/* 1.00000=f(0.61000)*/
{12, 0,123,__LINE__, 0x3ff00000, 0x00000000, 0x3fe3d70a, 0x3d70a3e3},			/* 1.00000=f(0.62000)*/
{12, 0,123,__LINE__, 0x3ff00000, 0x00000000, 0x3fe428f5, 0xc28f5c35},			/* 1.00000=f(0.63000)*/
{12, 0,123,__LINE__, 0x3ff00000, 0x00000000, 0x3fe47ae1, 0x47ae1487},			/* 1.00000=f(0.64000)*/
{12, 0,123,__LINE__, 0x3ff00000, 0x00000000, 0x3fe4cccc, 0xccccccd9},			/* 1.00000=f(0.65000)*/
{12, 0,123,__LINE__, 0x3ff00000, 0x00000000, 0x3fe51eb8, 0x51eb852b},			/* 1.00000=f(0.66000)*/
{12, 0,123,__LINE__, 0x3ff00000, 0x00000000, 0x3fe570a3, 0xd70a3d7d},			/* 1.00000=f(0.67000)*/
{12, 0,123,__LINE__, 0x3ff00000, 0x00000000, 0x3fe5c28f, 0x5c28f5cf},			/* 1.00000=f(0.68000)*/
{12, 0,123,__LINE__, 0x3ff00000, 0x00000000, 0x3fe6147a, 0xe147ae21},			/* 1.00000=f(0.69000)*/
{12, 0,123,__LINE__, 0x3ff00000, 0x00000000, 0x3fe66666, 0x66666673},			/* 1.00000=f(0.70000)*/
{12, 0,123,__LINE__, 0x3ff00000, 0x00000000, 0x3fe6b851, 0xeb851ec5},			/* 1.00000=f(0.71000)*/
{12, 0,123,__LINE__, 0x3ff00000, 0x00000000, 0x3fe70a3d, 0x70a3d717},			/* 1.00000=f(0.72000)*/
{12, 0,123,__LINE__, 0x3ff00000, 0x00000000, 0x3fe75c28, 0xf5c28f69},			/* 1.00000=f(0.73000)*/
{12, 0,123,__LINE__, 0x3ff00000, 0x00000000, 0x3fe7ae14, 0x7ae147bb},			/* 1.00000=f(0.74000)*/
{12, 0,123,__LINE__, 0x3ff00000, 0x00000000, 0x3fe80000, 0x0000000d},			/* 1.00000=f(0.75000)*/
{12, 0,123,__LINE__, 0x3ff00000, 0x00000000, 0x3fe851eb, 0x851eb85f},			/* 1.00000=f(0.76000)*/
{12, 0,123,__LINE__, 0x3ff00000, 0x00000000, 0x3fe8a3d7, 0x0a3d70b1},			/* 1.00000=f(0.77000)*/
{12, 0,123,__LINE__, 0x3ff00000, 0x00000000, 0x3fe8f5c2, 0x8f5c2903},			/* 1.00000=f(0.78000)*/
{12, 0,123,__LINE__, 0x3ff00000, 0x00000000, 0x3fe947ae, 0x147ae155},			/* 1.00000=f(0.79000)*/
{12, 0,123,__LINE__, 0x3ff00000, 0x00000000, 0x3fe99999, 0x999999a7},			/* 1.00000=f(0.80000)*/
{12, 0,123,__LINE__, 0x3ff00000, 0x00000000, 0x3fe9eb85, 0x1eb851f9},			/* 1.00000=f(0.81000)*/
{12, 0,123,__LINE__, 0x3ff00000, 0x00000000, 0x3fea3d70, 0xa3d70a4b},			/* 1.00000=f(0.82000)*/
{12, 0,123,__LINE__, 0x3ff00000, 0x00000000, 0x3fea8f5c, 0x28f5c29d},			/* 1.00000=f(0.83000)*/
{12, 0,123,__LINE__, 0x3ff00000, 0x00000000, 0x3feae147, 0xae147aef},			/* 1.00000=f(0.84000)*/
{12, 0,123,__LINE__, 0x3ff00000, 0x00000000, 0x3feb3333, 0x33333341},			/* 1.00000=f(0.85000)*/
{12, 0,123,__LINE__, 0x3ff00000, 0x00000000, 0x3feb851e, 0xb851eb93},			/* 1.00000=f(0.86000)*/
{12, 0,123,__LINE__, 0x3ff00000, 0x00000000, 0x3febd70a, 0x3d70a3e5},			/* 1.00000=f(0.87000)*/
{12, 0,123,__LINE__, 0x3ff00000, 0x00000000, 0x3fec28f5, 0xc28f5c37},			/* 1.00000=f(0.88000)*/
{12, 0,123,__LINE__, 0x3ff00000, 0x00000000, 0x3fec7ae1, 0x47ae1489},			/* 1.00000=f(0.89000)*/
{12, 0,123,__LINE__, 0x3ff00000, 0x00000000, 0x3feccccc, 0xccccccdb},			/* 1.00000=f(0.90000)*/
{12, 0,123,__LINE__, 0x3ff00000, 0x00000000, 0x3fed1eb8, 0x51eb852d},			/* 1.00000=f(0.91000)*/
{12, 0,123,__LINE__, 0x3ff00000, 0x00000000, 0x3fed70a3, 0xd70a3d7f},			/* 1.00000=f(0.92000)*/
{12, 0,123,__LINE__, 0x3ff00000, 0x00000000, 0x3fedc28f, 0x5c28f5d1},			/* 1.00000=f(0.93000)*/
{12, 0,123,__LINE__, 0x3ff00000, 0x00000000, 0x3fee147a, 0xe147ae23},			/* 1.00000=f(0.94000)*/
{12, 0,123,__LINE__, 0x3ff00000, 0x00000000, 0x3fee6666, 0x66666675},			/* 1.00000=f(0.95000)*/
{12, 0,123,__LINE__, 0x3ff00000, 0x00000000, 0x3feeb851, 0xeb851ec7},			/* 1.00000=f(0.96000)*/
{12, 0,123,__LINE__, 0x3ff00000, 0x00000000, 0x3fef0a3d, 0x70a3d719},			/* 1.00000=f(0.97000)*/
{12, 0,123,__LINE__, 0x3ff00000, 0x00000000, 0x3fef5c28, 0xf5c28f6b},			/* 1.00000=f(0.98000)*/
{12, 0,123,__LINE__, 0x3ff00000, 0x00000000, 0x3fefae14, 0x7ae147bd},			/* 1.00000=f(0.99000)*/
{12, 0,123,__LINE__, 0x3ff00000, 0x00000000, 0x3ff00000, 0x00000007},			/* 1.00000=f(1.00000)*/
{ 1, 0,123,__LINE__, 0x40000000, 0x00000000, 0x3ff028f5, 0xc28f5c30},			/* 2.00000=f(1.01000)*/
{ 1, 0,123,__LINE__, 0x40000000, 0x00000000, 0x3ff051eb, 0x851eb859},			/* 2.00000=f(1.02000)*/
{ 1, 0,123,__LINE__, 0x40000000, 0x00000000, 0x3ff07ae1, 0x47ae1482},			/* 2.00000=f(1.03000)*/
{ 1, 0,123,__LINE__, 0x40000000, 0x00000000, 0x3ff0a3d7, 0x0a3d70ab},			/* 2.00000=f(1.04000)*/
{ 1, 0,123,__LINE__, 0x40000000, 0x00000000, 0x3ff0cccc, 0xccccccd4},			/* 2.00000=f(1.05000)*/
{ 1, 0,123,__LINE__, 0x40000000, 0x00000000, 0x3ff0f5c2, 0x8f5c28fd},			/* 2.00000=f(1.06000)*/
{ 1, 0,123,__LINE__, 0x40000000, 0x00000000, 0x3ff11eb8, 0x51eb8526},			/* 2.00000=f(1.07000)*/
{ 1, 0,123,__LINE__, 0x40000000, 0x00000000, 0x3ff147ae, 0x147ae14f},			/* 2.00000=f(1.08000)*/
{ 1, 0,123,__LINE__, 0x40000000, 0x00000000, 0x3ff170a3, 0xd70a3d78},			/* 2.00000=f(1.09000)*/
{ 1, 0,123,__LINE__, 0x40000000, 0x00000000, 0x3ff19999, 0x999999a1},			/* 2.00000=f(1.10000)*/
{ 1, 0,123,__LINE__, 0x40000000, 0x00000000, 0x3ff1c28f, 0x5c28f5ca},			/* 2.00000=f(1.11000)*/
{ 1, 0,123,__LINE__, 0x40000000, 0x00000000, 0x3ff1eb85, 0x1eb851f3},			/* 2.00000=f(1.12000)*/
{ 1, 0,123,__LINE__, 0x40000000, 0x00000000, 0x3ff2147a, 0xe147ae1c},			/* 2.00000=f(1.13000)*/
{ 1, 0,123,__LINE__, 0x40000000, 0x00000000, 0x3ff23d70, 0xa3d70a45},			/* 2.00000=f(1.14000)*/
{ 1, 0,123,__LINE__, 0x40000000, 0x00000000, 0x3ff26666, 0x6666666e},			/* 2.00000=f(1.15000)*/
{ 1, 0,123,__LINE__, 0x40000000, 0x00000000, 0x3ff28f5c, 0x28f5c297},			/* 2.00000=f(1.16000)*/
{ 1, 0,123,__LINE__, 0x40000000, 0x00000000, 0x3ff2b851, 0xeb851ec0},			/* 2.00000=f(1.17000)*/
{ 1, 0,123,__LINE__, 0x40000000, 0x00000000, 0x3ff2e147, 0xae147ae9},			/* 2.00000=f(1.18000)*/
{ 1, 0,123,__LINE__, 0x40000000, 0x00000000, 0x3ff30a3d, 0x70a3d712},			/* 2.00000=f(1.19000)*/
{15, 0,123,__LINE__, 0xc0180000, 0x00000000, 0xc01921fb, 0x54442d18},			/* -6.00000=f(-6.28318)*/
{14, 0,123,__LINE__, 0xc0100000, 0x00000000, 0xc012d97c, 0x7f3321d2},			/* -4.00000=f(-4.71238)*/
{15, 0,123,__LINE__, 0xc0080000, 0x00000000, 0xc00921fb, 0x54442d18},			/* -3.00000=f(-3.14159)*/
{ 0, 0,123,__LINE__, 0xbff00000, 0x00000000, 0xbff921fb, 0x54442d18},			/* -1.00000=f(-1.57079)*/
{64, 0,123,__LINE__, 0x00000000, 0x00000000, 0x00000000, 0x00000000},			/* 0.00000=f(0.00000)*/
{ 1, 0,123,__LINE__, 0x40000000, 0x00000000, 0x3ff921fb, 0x54442d18},			/* 2.00000=f(1.57079)*/
{11, 0,123,__LINE__, 0x40100000, 0x00000000, 0x400921fb, 0x54442d18},			/* 4.00000=f(3.14159)*/
{13, 0,123,__LINE__, 0x40140000, 0x00000000, 0x4012d97c, 0x7f3321d2},			/* 5.00000=f(4.71238)*/
{64, 0,123,__LINE__, 0xc03e0000, 0x00000000, 0xc03e0000, 0x00000000},			/* -30.0000=f(-30.0000)*/
{17, 0,123,__LINE__, 0xc03c0000, 0x00000000, 0xc03c4ccc, 0xcccccccd},			/* -28.0000=f(-28.3000)*/
{16, 0,123,__LINE__, 0xc03a0000, 0x00000000, 0xc03a9999, 0x9999999a},			/* -26.0000=f(-26.6000)*/
{16, 0,123,__LINE__, 0xc0380000, 0x00000000, 0xc038e666, 0x66666667},			/* -24.0000=f(-24.9000)*/
{18, 0,123,__LINE__, 0xc0370000, 0x00000000, 0xc0373333, 0x33333334},			/* -23.0000=f(-23.2000)*/
{16, 0,123,__LINE__, 0xc0350000, 0x00000000, 0xc0358000, 0x00000001},			/* -21.0000=f(-21.5000)*/
{16, 0,123,__LINE__, 0xc0330000, 0x00000000, 0xc033cccc, 0xccccccce},			/* -19.0000=f(-19.8000)*/
{19, 0,123,__LINE__, 0xc0320000, 0x00000000, 0xc0321999, 0x9999999b},			/* -18.0000=f(-18.1000)*/
{17, 0,123,__LINE__, 0xc0300000, 0x00000000, 0xc0306666, 0x66666668},			/* -16.0000=f(-16.4000)*/
{15, 0,123,__LINE__, 0xc02c0000, 0x00000000, 0xc02d6666, 0x6666666a},			/* -14.0000=f(-14.7000)*/
{64, 0,123,__LINE__, 0xc02a0000, 0x00000000, 0xc02a0000, 0x00000004},			/* -13.0000=f(-13.0000)*/
{16, 0,123,__LINE__, 0xc0260000, 0x00000000, 0xc0269999, 0x9999999e},			/* -11.0000=f(-11.3000)*/
{15, 0,123,__LINE__, 0xc0220000, 0x00000000, 0xc0233333, 0x33333338},			/* -9.00000=f(-9.60000)*/
{14, 0,123,__LINE__, 0xc01c0000, 0x00000000, 0xc01f9999, 0x999999a3},			/* -7.00000=f(-7.90000)*/
{16, 0,123,__LINE__, 0xc0180000, 0x00000000, 0xc018cccc, 0xccccccd6},			/* -6.00000=f(-6.20000)*/
{14, 0,123,__LINE__, 0xc0100000, 0x00000000, 0xc0120000, 0x00000009},			/* -4.00000=f(-4.50000)*/
{13, 0,123,__LINE__, 0xc0000000, 0x00000000, 0xc0066666, 0x66666678},			/* -2.00000=f(-2.80000)*/
{ 0, 0,123,__LINE__, 0xbff00000, 0x00000000, 0xbff19999, 0x999999bd},			/* -1.00000=f(-1.10000)*/
{12, 0,123,__LINE__, 0x3ff00000, 0x00000000, 0x3fe33333, 0x333332ec},			/* 1.00000=f(0.60000)*/
{12, 0,123,__LINE__, 0x40080000, 0x00000000, 0x40026666, 0x66666654},			/* 3.00000=f(2.30000)*/
{64, 0,123,__LINE__, 0x40100000, 0x00000000, 0x400fffff, 0xffffffee},			/* 4.00000=f(4.00000)*/
{12, 0,123,__LINE__, 0x40180000, 0x00000000, 0x4016cccc, 0xccccccc4},			/* 6.00000=f(5.70000)*/
{10, 0,123,__LINE__, 0x40200000, 0x00000000, 0x401d9999, 0x99999991},			/* 8.00000=f(7.40000)*/
{13, 0,123,__LINE__, 0x40240000, 0x00000000, 0x40223333, 0x3333332f},			/* 10.0000=f(9.10000)*/
{14, 0,123,__LINE__, 0x40260000, 0x00000000, 0x40259999, 0x99999995},			/* 11.0000=f(10.8000)*/
{14, 0,123,__LINE__, 0x402a0000, 0x00000000, 0x4028ffff, 0xfffffffb},			/* 13.0000=f(12.5000)*/
{14, 0,123,__LINE__, 0x402e0000, 0x00000000, 0x402c6666, 0x66666661},			/* 15.0000=f(14.2000)*/
{11, 0,123,__LINE__, 0x40300000, 0x00000000, 0x402fcccc, 0xccccccc7},			/* 16.0000=f(15.9000)*/
{14, 0,123,__LINE__, 0x40320000, 0x00000000, 0x40319999, 0x99999997},			/* 18.0000=f(17.6000)*/
{13, 0,123,__LINE__, 0x40340000, 0x00000000, 0x40334ccc, 0xccccccca},			/* 20.0000=f(19.3000)*/
{64, 0,123,__LINE__, 0x40350000, 0x00000000, 0x4034ffff, 0xfffffffd},			/* 21.0000=f(21.0000)*/
{15, 0,123,__LINE__, 0x40370000, 0x00000000, 0x4036b333, 0x33333330},			/* 23.0000=f(22.7000)*/
{15, 0,123,__LINE__, 0x40390000, 0x00000000, 0x40386666, 0x66666663},			/* 25.0000=f(24.4000)*/
{15, 0,123,__LINE__, 0x403b0000, 0x00000000, 0x403a1999, 0x99999996},			/* 27.0000=f(26.1000)*/
{13, 0,123,__LINE__, 0x403c0000, 0x00000000, 0x403bcccc, 0xccccccc9},			/* 28.0000=f(27.8000)*/
{14, 0,123,__LINE__, 0x403e0000, 0x00000000, 0x403d7fff, 0xfffffffc},			/* 30.0000=f(29.5000)*/
0,};
test_ceilf(m)   {run_vector_1(m,ceilf_vec,(char *)(ceilf),"ceilf","ff");   }	
