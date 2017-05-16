#include "arch.h"
#include "ecp_MF254E.h"

/* MF254 NUMS Curve - EDWARDS */

/* Montgomery-Friendly NUMS curves http://eprint.iacr.org/2014/130 */

/* p=k.2^n-1 where n is multiple of BASEBITS - but k can be adjusted. */
/* Here p=2^240(2^14-127)-1 = 2^232(2^22-256.127)-1 where 8*29=232 and (2^22-256.127)=0x3F8100 */
/* or = 2^224(2^30-65536.127)-1 where 4*56=224 and (2^30-65536.127) = 0x3F810000 */

#if CHUNK==32
const int CURVE_A_MF254E= -1;
const BIG_256 CURVE_Order_MF254E= {0x46E98C7,0x179E9FF6,0x158BEC3A,0xA60D917,0x1FFFFEB9,0x1FFFFFFF,0x1FFFFFFF,0x1FFFFFFF,0xFE03F};
const BIG_256 CURVE_B_MF254E= {0x367B};
const BIG_256 CURVE_Gx_MF254E= {0x1};
const BIG_256 CURVE_Gy_MF254E= {0xF2701E5,0x29687ED,0xC84861F,0x535081C,0x3F4E363,0x6A811B,0xCD65474,0x121AD498,0x19F0E6};
#endif


#if CHUNK==64
const int CURVE_A_MF254E= -1;
const BIG_256 CURVE_Order_MF254E= {0xF3D3FEC46E98C7,0x306C8BD62FB0EA,0xFFFFFFFFFFEB95,0xFFFFFFFFFFFFFF,0xFE03FFF};
const BIG_256 CURVE_B_MF254E= {0x367B};
const BIG_256 CURVE_Gx_MF254E= {0x1};
const BIG_256 CURVE_Gy_MF254E= {0x52D0FDAF2701E5,0x9A840E3212187C,0xD502363F4E3632,0xD6A4C335951D00,0x19F0E690};
#endif
