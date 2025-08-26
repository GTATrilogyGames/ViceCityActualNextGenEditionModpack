#include <consts.h>

#define PED_HASHES_MIN_INDEX	0
#define PED_HASHES_MAX_INDEX	81



int peds_hashes[82];		/*rebusx: чтобы случайно выбирать педов (заказчиков)*/
void init_ped_hashes()
{
	peds_hashes[0] = MODEL_F_M_BUSINESS_01;
	peds_hashes[1] = MODEL_F_M_BUSINESS_02;
	peds_hashes[2] = MODEL_F_M_CHINATOWN;
	peds_hashes[3] = MODEL_F_M_PBUSINESS;
	peds_hashes[4] = MODEL_F_M_PJERSEY_01;
	peds_hashes[5] = MODEL_F_M_PJERSEY_02;
	peds_hashes[6] = MODEL_F_M_PLATIN_01;
	peds_hashes[7] = MODEL_F_M_PMANHAT_01;
	peds_hashes[8] = MODEL_F_M_PMANHAT_02;
	peds_hashes[9] = MODEL_F_M_PORIENT_01;
	peds_hashes[10] = MODEL_F_M_PRICH_01;
	peds_hashes[11] = MODEL_F_O_BINCO;
	peds_hashes[12] = MODEL_F_O_PEASTEURO_01;
	peds_hashes[13] = MODEL_F_O_PEASTEURO_02;
	peds_hashes[14] = MODEL_F_O_PJERSEY_01;
	peds_hashes[15] = MODEL_F_Y_BUSINESS_01;
	peds_hashes[16] = MODEL_F_Y_CDRESS_01;
	peds_hashes[17] = MODEL_F_Y_DOCTOR_01;
	peds_hashes[18] = MODEL_F_Y_FF_CLUCK_R;
	peds_hashes[19] = MODEL_F_Y_FF_RSCAFE;
	peds_hashes[20] = MODEL_F_Y_GYMGAL_01;
	peds_hashes[21] = MODEL_F_Y_HOOKER_01;
	peds_hashes[22] = MODEL_F_Y_HOOKER_03;
	peds_hashes[23] = MODEL_F_Y_NURSE;
	peds_hashes[24] = MODEL_F_Y_PBRONX_01;
	peds_hashes[25] = MODEL_F_Y_PEASTEURO_01;
	peds_hashes[26] = MODEL_F_Y_PHARBRON_01;
	peds_hashes[27] = MODEL_F_Y_PMANHAT_01;
	peds_hashes[28] = MODEL_F_Y_PMANHAT_03;
	peds_hashes[29] = MODEL_F_Y_PRICH_01;
	peds_hashes[30] = MODEL_F_Y_SHOP_03;
	peds_hashes[31] = MODEL_F_Y_SHOPPER_05;
	peds_hashes[32] = MODEL_IG_TUNA;
	peds_hashes[33] = MODEL_IG_VINNY_SPAZ;
	peds_hashes[34] = MODEL_M_M_ALCOHOLIC;
	peds_hashes[35] = MODEL_M_M_ARMOURED;
	peds_hashes[36] = MODEL_M_M_BUSINESS_02;
	peds_hashes[37] = MODEL_M_M_BUSINESS_03;
	peds_hashes[38] = MODEL_M_M_CHINATOWN_01;
	peds_hashes[39] = MODEL_M_M_CRACKHEAD;
	peds_hashes[40] = MODEL_M_M_DOCTOR_01;
	peds_hashes[41] = MODEL_M_M_EECOOK;
	peds_hashes[42] = MODEL_M_M_ENFORCER;
	peds_hashes[43] = MODEL_M_M_FACTORY_01;
	peds_hashes[44] = MODEL_M_M_FATMOB_01;
	peds_hashes[45] = MODEL_M_M_FEDCO;
	peds_hashes[46] = MODEL_M_M_GAYMID;
	peds_hashes[47] = MODEL_M_M_GENBUM_01;
	peds_hashes[48] = MODEL_M_M_GRU2_HI_01;
	peds_hashes[49] = MODEL_M_M_GRU2_HI_02;
	peds_hashes[50] = MODEL_M_M_GRU2_LO_02;
	peds_hashes[51] = MODEL_M_M_HPORTER_01;
	peds_hashes[52] = MODEL_M_M_LAWYER_02;
	peds_hashes[53] = MODEL_M_M_PBUSINESS_01;
	peds_hashes[54] = MODEL_M_M_PEASTEURO_01;
	peds_hashes[55] = MODEL_M_M_PHARBRON_01;
	peds_hashes[56] = MODEL_M_M_PILOT;
	peds_hashes[57] = MODEL_M_M_PINDUS_01;
	peds_hashes[58] = MODEL_M_M_PITALIAN_01;
	peds_hashes[59] = MODEL_M_M_PITALIAN_02;
	peds_hashes[60] = MODEL_M_M_PLATIN_01;
	peds_hashes[61] = MODEL_M_M_PLATIN_02;
	peds_hashes[62] = MODEL_M_M_PMANHAT_02;
	peds_hashes[63] = MODEL_M_M_SELLER_01;
	peds_hashes[64] = MODEL_M_M_SWEEPER;
	peds_hashes[65] = MODEL_M_M_TRAMPBLACK;
	peds_hashes[66] = MODEL_M_O_MPMOBBOSS;
	peds_hashes[67] = MODEL_M_Y_BOHOGUY_01;
	peds_hashes[68] = MODEL_M_Y_DEALER;
	peds_hashes[69] = MODEL_M_Y_DORK_02;
	peds_hashes[70] = MODEL_M_Y_DOWNTOWN_01;
	peds_hashes[71] = MODEL_M_Y_DOWNTOWN_02;
	peds_hashes[72] = MODEL_M_Y_DRUG_01;
	peds_hashes[73] = MODEL_M_Y_FRENCHTOM;
	peds_hashes[74] = MODEL_M_Y_GAFR_LO_02;
	peds_hashes[75] = MODEL_M_Y_GALB_LO_02;
	peds_hashes[76] = MODEL_M_Y_GALB_LO_03;
	peds_hashes[77] = MODEL_M_Y_GENSTREET_16;
	peds_hashes[78] = MODEL_M_Y_GYMGUY_01;
	peds_hashes[79] = MODEL_M_Y_HASID_01;
	peds_hashes[80] = MODEL_M_Y_MODO;
	peds_hashes[81] = MODEL_M_Y_PHARLEM_01;
}
