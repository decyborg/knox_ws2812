/** \addtogroup CPMU Clock, Reset and Power management unit  
 *  @{
 */
/**	
 *  @file cpmu.c
 *  
 * 	@brief Contains Clock and power management unit API routines for MagniV devices.
 * 	
 *	@author Manuel Rodriguez
 *  
 */
/*
 * History:
 * 
 * 		Rev 1.0 Initial Release
 * 		
 * */

#include "cpmu.h"
/** \addtogroup Core Core API functions  
 *  @{
 */
/** Initializes the Bus clock at the desired speed using the internal oscillator.
 * 
 * 	@param[in] BusClock Desired Bus Clock Frequency in hertz
 * 	
 * */
void clock_init(unsigned long BusClock){
	clock_dividers prescalers;
	prescalers = calc_prs(BusClock*2, FALSE, 0);
	set_clock(prescalers, FALSE);
}

/** Initializes the Bus clock at the desired speed using an external oscillator.
 * 
 * 	@param[in] BusClock Desired Bus Clock Frequency in hertz
 * 	@param[in] ExtFreq  Frequency of the external oscillator
 * */
void clock_init_ext(unsigned long BusClock, unsigned long ExtFreq){
	clock_dividers prescalers;
	prescalers = calc_prs(BusClock*2, TRUE, ExtFreq);
	set_clock(prescalers, TRUE);
}
/** @}*/

/** \addtogroup helper Helper functions  
 *  @{
 */
/** Calculate the prescaler values for the corresponding bus frequency.
 * 
 * @param[in] FPLL Desired PLL frequency (bus frequency * 2) in hertz
 * @param[in] ExtClock If an External oscillator is being used set this variable to TRUE (1) otherwise set to FALSE (0)
 * @param[in] ExtFreq  If an oscillator is being used pass the frequency of the oscillator, otherwise pass FALSE (0)
 * 
 * @return A structure with the values of the prescalers
 * 
 * */
clock_dividers calc_prs(unsigned long FPLL, unsigned char ExtClock, unsigned long ExtFreq){
	clock_dividers prs;
	unsigned long Fref;
	
	/* Check if an external oscillator is being used */
	if(ExtClock == TRUE){
		if(!(ExtFreq % IRC)){	/* Check if ExtFreq is an integer multiple of IRC */
			prs.refdiv = (ExtFreq / IRC) - 1;	/* Fref = Fosc / (REFDIV + 1) */
			Fref = IRC;
			prs.reffrq = SELECT_REF_RANGE(Fref);
		} else {
			unsigned char RefDiv;
			unsigned long search_Fref, min_error = 0;
			/* Look for best prescaler values */
			for(RefDiv = 0; RefDiv <= REFDIV_MAX; ++RefDiv){
				search_Fref = ExtFreq / (RefDiv + 1);
				prs = search_prs(search_Fref, FPLL);
				if(prs.error == 0){							/* Exact match found return values */
					prs.refdiv = RefDiv;
					prs.reffrq = SELECT_REF_RANGE(search_Fref);
					return prs;
				} else {
					if(min_error == 0){						/* First time it enters */
						min_error = prs.error;				/* Store values */
						prs.refdiv = RefDiv;
						prs.reffrq = SELECT_REF_RANGE(search_Fref);
					}
					if(prs.error < min_error){				/* A better value has been found */
						min_error = prs.error;				/* Store values */
						prs.refdiv = RefDiv;
						prs.reffrq = SELECT_REF_RANGE(search_Fref);
					}
				}
			}
			return prs;										/* Values for external oscillator have been found, return */
		}
		
	} else
		Fref = IRC;
	
	prs = search_prs(Fref, FPLL);
	prs.refdiv;
	prs.reffrq;
	
	return prs;
}

/** Searches through possible values to find the best match
 * 	
 * 	Searches for the values of POSTDIV and SYNDIV given a certain frequency reference, this function only writes
 * 	the following values on the clock_dividers structure:
 * 		postdiv, syndiv, vcofrq and error.		 
 * 
 * 	@param[in] Fref Reference frequency used to find the values
 * 	@param[in] FPLL Desired PLL frequency (bus frequency * 2) in hertz
 * 	
 * 	@return Structure with the found values and the error of the setup
 * */
clock_dividers search_prs(unsigned long Fref, unsigned long FPLL){
	
	unsigned long search_VCO, error;
    unsigned long min_error = 0;
	clock_dividers min_prs_values, prescalers;
	unsigned char PostDiv, SynDiv;
	
	/* Search for best prescaler values */
	for(SynDiv = 0; SynDiv <= SYNDIV_MAX; ++SynDiv){
		search_VCO = 2 * Fref * (SynDiv + 1);						/* Search through possible values of Fvco */
		if((search_VCO >= VCO_MIN) && (search_VCO <= VCO_MAX)){		/* If VCO is within range */
			for(PostDiv = 0; PostDiv <= POSTDIV_MAX; ++PostDiv){	/* Brute force through possible values of Postdiv for best match */
				error = (search_VCO / (PostDiv + 1));
				error = error - FPLL;
				if(error == 0){										/* Exact match, store values and return */
					prescalers.postdiv = PostDiv;
					prescalers.syndiv = SynDiv;
					prescalers.vcofrq = SELECT_VCO_RANGE(search_VCO);
					prescalers.error = error;
					return prescalers;
				} else {
					if(min_error == 0){								/* First time it enters the algorithm */
						min_error = error;
						prescalers.postdiv = PostDiv;						/* Store corresponding values */
						prescalers.syndiv = SynDiv;
						prescalers.vcofrq = SELECT_VCO_RANGE(search_VCO);
						prescalers.error = error;
					}
					if(error < min_error){									/* The minimum possible error will be stored */
						min_error = error;									/* Update minimum error */
						prescalers.postdiv = PostDiv;						/* Store corresponding values */
						prescalers.syndiv = SynDiv;
						prescalers.vcofrq = SELECT_VCO_RANGE(search_VCO);
						prescalers.error = error;
					}
				}
			}
		}
	}
	return prescalers;
}

/** Set the clock registers
 * 	
 * 	@param[in] ClockConfig Holds the prescaler values to configure the clock
 * 	@param[in] ExtClock If an External oscillator is being used set this variable to TRUE (1) otherwise set to FALSE (0)
 * */
void set_clock(clock_dividers ClockConfig, unsigned char ExtClock){
	tCPMU *pCPMU;
	pCPMU = (tCPMU*) CPMU_ADDR;
	
	if(ExtClock == TRUE){
		pCPMU->osc.bit.osce = 1;
		pCPMU->refdiv.bit.reffrq = ClockConfig.reffrq;
		pCPMU->refdiv.bit.refdiv = ClockConfig.refdiv;
		pCPMU->syndiv.bit.vcofrq = ClockConfig.vcofrq;
		pCPMU->syndiv.bit.syndiv = ClockConfig.syndiv;
		pCPMU->postdiv.bit.postdiv = ClockConfig.postdiv;
	} else {
		pCPMU->syndiv.bit.vcofrq = ClockConfig.vcofrq;
		pCPMU->syndiv.bit.syndiv = ClockConfig.syndiv;
		pCPMU->postdiv.bit.postdiv = ClockConfig.postdiv;
	}
	while(0 == pCPMU->iflg.bit.lockif){};
}
/** @}*/

/** @}*/
