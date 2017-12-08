
/*
#!/usr/bin/env python
from .. import exceptions as exc
from ..traitlets import Float, Int, Instance, AfgenTrait
from ..decorators import prepare_rates, prepare_states
from ..base_classes import ParamTemplate, StatesTemplate, RatesTemplate, SimulationObject

from .nutrients import NPK_Translocation
from .nutrients import NPK_Demand_Uptake



class NPK_Crop_Dynamics(SimulationObject):
    """Implementation of overall NPK crop dynamics.

    NPK_Crop_Dynamics implements the overall logic of N/P/K book-keeping within the
    crop.

    **Simulation parameters**

    ===========  ================================================ =======  ======================
     Name         Description                                      Type     Unit
    ===========  ================================================ =======  ======================
    DVSNPK_STOP   DVS above which no crop N-P-K uptake occurs      SCr       -

    NMAXLV_TB      Maximum N concentration in leaves as            TCr     kg N kg-1 dry biomass
                   function of dvs
    PMAXLV_TB      As for P                                        TCr     kg P kg-1 dry biomass
    KMAXLV_TB      As for K                                        TCr     kg K kg-1 dry biomass

    NMAXRT_FR      Maximum N concentration in roots as fraction    SCr     -
                   of maximum N concentration in leaves
    PMAXRT_FR      As for P                                        SCr     -
    KMAXRT_FR      As for K                                        SCr     -

    NMAXST_FR      Maximum N concentration in stems as fraction    SCr     -
                   of maximum N concentration in leaves
    KMAXST_FR      As for K                                        SCr     -
    PMAXST_FR      As for P                                        SCr     -

    NRESIDLV       Residual N fraction in leaves                   SCr     kg N kg-1 dry biomass
    PRESIDLV       Residual P fraction in leaves                   SCr     kg P kg-1 dry biomass
    KRESIDLV       Residual K fraction in leaves                   SCr     kg K kg-1 dry biomass

    NRESIDRT       Residual N fraction in roots                    SCr     kg N kg-1 dry biomass
    PRESIDRT       Residual P fraction in roots                    SCr     kg P kg-1 dry biomass
    KRESIDRT       Residual K fraction in roots                    SCr     kg K kg-1 dry biomass

    NRESIDST       Residual N fraction in stems                    SCr     kg N kg-1 dry biomass
    PRESIDST       Residual P fraction in stems                    SCr     kg P kg-1 dry biomass
    KRESIDST       Residual K fraction in stems                    SCr     kg K kg-1 dry biomass
    ===========  ================================================ =======  ======================

    **State variables**

    =======  ================================================= ==== ============
     Name     Description                                      Pbl      Unit
    =======  ================================================= ==== ============
    ANLV     Actual N amount in living leaves                   Y   |kg N ha-1|
    APLV     Actual P amount in living leaves                   Y   |kg P ha-1|
    AKLV     Actual K amount in living leaves                   Y   |kg K ha-1|

    ANST     Actual N amount in living stems                    Y   |kg N ha-1|
    APST     Actual P amount in living stems                    Y   |kg P ha-1|
    AKST     Actual K amount in living stems                    Y   |kg K ha-1|

    ANSO     Actual N amount in living storage organs           Y   |kg N ha-1|
    APSO     Actual P amount in living storage organs           Y   |kg P ha-1|
    AKSO     Actual K amount in living storage organs           Y   |kg K ha-1|

    ANRT     Actual N amount in living roots                    Y   |kg N ha-1|
    APRT     Actual P amount in living roots                    Y   |kg P ha-1|
    AKRT     Actual K amount in living roots                    Y   |kg K ha-1|

    NUPTAKE_T    total absorbed N amount                        N   |kg N ha-1|
    PUPTAKE_T    total absorbed P amount                        N   |kg P ha-1|
    KUPTAKE_T    total absorbed K amount                        N   |kg K ha-1|
    NFIX_T   total biological fixated N amount                  N   |kg N ha-1|
    =======  ================================================= ==== ============

    **Rate variables**

    =======  ================================================= ==== ============
     Name     Description                                      Pbl      Unit
    =======  ================================================= ==== ============
    RNLV     Weight increase (N) in leaves                      N   |kg ha-1 d-1|
    RPLV     Weight increase (P) in leaves                      N   |kg ha-1 d-1|
    RKLV     Weight increase (K) in leaves                      N   |kg ha-1 d-1|

    RNST     Weight increase (N) in stems                       N   |kg ha-1 d-1|
    RPST     Weight increase (P) in stems                       N   |kg ha-1 d-1|
    RKST     Weight increase (K) in stems                       N   |kg ha-1 d-1|

    RNRT     Weight increase (N) in roots                       N   |kg ha-1 d-1|
    RPRT     Weight increase (P) in roots                       N   |kg ha-1 d-1|
    RKRT     Weight increase (K) in roots                       N   |kg ha-1 d-1|

    RNSO     Weight increase (N) in storage organs              N   |kg ha-1 d-1|
    RPSO     Weight increase (P) in storage organs              N   |kg ha-1 d-1|
    RKSO     Weight increase (K) in storage organs              N   |kg ha-1 d-1|

    RNDLV    Rate of N loss in leaves                           N   |kg ha-1 d-1|
    RPDLV    as for P                                           N   |kg ha-1 d-1|
    RKDLV    as for K                                           N   |kg ha-1 d-1|

    RNDST    Rate of N loss in roots                            N   |kg ha-1 d-1|
    RPDST    as for P                                           N   |kg ha-1 d-1|
    RKDST    as for K                                           N   |kg ha-1 d-1|

    RNDRT    Rate of N loss in stems                            N   |kg ha-1 d-1|
    RPDRT    as for P                                           N   |kg ha-1 d-1|
    RKDRT    as for K                                           N   |kg ha-1 d-1|

    RNLOSS   N loss due to senescence                           N   |kg ha-1 d-1|
    RPLOSS   P loss due to senescence                           N   |kg ha-1 d-1|
    RKLOSS   K loss due to senescence                           N   |kg ha-1 d-1|
    =======  ================================================= ==== ============

    **Signals send or handled**

    None

    **External dependencies**

    =======  =================================== ====================  ============
     Name     Description                         Provided by            Unit
    =======  =================================== ====================  ============
    DVS      Crop development stage              DVS_Phenology           -
    WLV      Dry weight of living leaves         WOFOST_Leaf_Dynamics  |kg ha-1|
    WRT      Dry weight of living roots          WOFOST_Root_Dynamics  |kg ha-1|
    WST      Dry weight of living stems          WOFOST_Stem_Dynamics  |kg ha-1|
    DRLV     Death rate of leaves                WOFOST_Leaf_Dynamics  |kg ha-1 d-|
    DRRT     Death rate of roots                 WOFOST_Root_Dynamics  |kg ha-1 d-|
    DRST     Death rate of stems                 WOFOST_Stem_Dynamics  |kg ha-1 d-|
    =======  =================================== ====================  ============
    """

    translocation = Instance(SimulationObject)
    demand_uptake = Instance(SimulationObject)

    ANLVI = Float(-99.)  # initial soil N amount in leaves
    ANSTI = Float(-99.)  # initial soil N amount in stems
    ANRTI = Float(-99.)  # initial soil N amount in roots
    ANSOI = Float(-99.)  # initial soil N amount in storage organs

    APLVI = Float(-99.)  # initial soil P amount in leaves
    APSTI = Float(-99.)  # initial soil P amount in stems
    APRTI = Float(-99.)  # initial soil P amount in roots
    APSOI = Float(-99.)  # initial soil P amount in storage organs

    AKLVI = Float(-99.)  # initial soil K amount in leaves
    AKSTI = Float(-99.)  # initial soil K amount in stems
    AKRTI = Float(-99.)  # initial soil K amount in roots
    AKSOI = Float(-99.)  # initial soil K amount in storage organs

    class Parameters(ParamTemplate):
        DVSNPK_STOP = Float(-99.)
        NMAXLV_TB = AfgenTrait()
        PMAXLV_TB = AfgenTrait()
        KMAXLV_TB = AfgenTrait()
        NMAXST_FR = Float(-99.)
        NMAXRT_FR = Float(-99.)
        PMAXST_FR = Float(-99.)
        PMAXRT_FR = Float(-99.)
        KMAXST_FR = Float(-99.)
        KMAXRT_FR = Float(-99.)
        NRESIDLV = Float(-99.)  # residual N fraction in leaves [kg N kg-1 dry biomass]
        NRESIDST = Float(-99.)  # residual N fraction in stems [kg N kg-1 dry biomass]
        NRESIDRT = Float(-99.)  # residual N fraction in roots [kg N kg-1 dry biomass]
        PRESIDLV = Float(-99.)  # residual P fraction in leaves [kg P kg-1 dry biomass]
        PRESIDST = Float(-99.)  # residual P fraction in stems [kg P kg-1 dry biomass]
        PRESIDRT = Float(-99.)  # residual P fraction in roots [kg P kg-1 dry biomass]
        KRESIDLV = Float(-99.)  # residual K fraction in leaves [kg K kg-1 dry biomass]
        KRESIDST = Float(-99.)  # residual K fraction in stems [kg K kg-1 dry biomass]
        KRESIDRT = Float(-99.)  # residual K fraction in roots [kg K kg-1 dry biomass]

    class StateVariables(StatesTemplate):
        ANLV = Float(-99.) # N amount in leaves [kg N ha-1]
        APLV = Float(-99.) # P amount in leaves [kg P ]
        AKLV = Float(-99.) # K amount in leaves [kg K ]

        ANST = Float(-99.) # N amount in stems [kg N ]
        APST = Float(-99.) # P amount in stems [kg P ]
        AKST = Float(-99.) # K amount in stems [kg K ]

        ANSO = Float(-99.) # N amount in storage organs [kg N ]
        APSO = Float(-99.) # P amount in storage organs [kg P ]
        AKSO = Float(-99.) # K amount in storage organs [kg K ]

        ANRT = Float(-99.) # N amount in roots [kg N ]
        APRT = Float(-99.) # P amount in roots [kg P ]
        AKRT = Float(-99.) # K amount in roots [kg K ]

        NUPTAKE_T = Float(-99.) # total absorbed N amount [kg N ]
        PUPTAKE_T = Float(-99.) # total absorbed P amount [kg P ]
        KUPTAKE_T = Float(-99.) # total absorbed K amount [kg K ]
        NFIX_T = Float(-99.) # total biological fixated N amount [kg N ]

        NLOSSES_T = Float(-99.)
        PLOSSES_T = Float(-99.)
        KLOSSES_T = Float(-99.)

    class RateVariables(RatesTemplate):
        RNLV = Float(-99.)  # Net rates of NPK in different plant organs
        RPLV = Float(-99.)
        RKLV = Float(-99.)

        RNST = Float(-99.)
        RPST = Float(-99.)
        RKST = Float(-99.)

        RNRT = Float(-99.)
        RPRT = Float(-99.)
        RKRT = Float(-99.)

        RNSO = Float(-99.)
        RPSO = Float(-99.)
        RKSO = Float(-99.)

        RNDLV = Float(-99.)  # N loss rate leaves [kg ha-1 d-1]
        RNDST = Float(-99.)  # N loss rate stems  [kg ha-1 d-1]
        RNDRT = Float(-99.)  # N loss rate roots  [kg ha-1 d-1]

        RPDLV = Float(-99.)  # P loss rate leaves [kg ha-1 d-1]
        RPDST = Float(-99.)  # P loss rate stems  [kg ha-1 d-1]
        RPDRT = Float(-99.)  # P loss rate roots  [kg ha-1 d-1]

        RKDLV = Float(-99.)  # K loss rate leaves [kg ha-1 d-1]
        RKDST = Float(-99.)  # K loss rate stems  [kg ha-1 d-1]
        RKDRT = Float(-99.)  # K loss rate roots  [kg ha-1 d-1]

        RNLOSS = Float(-99.)
        RPLOSS = Float(-99.)
        RKLOSS = Float(-99.)

using namespace std;
*/


#include <math.h>
#include <vector>
#include "wofost.h"
#include "wofostUtil.h"
#include <string.h>
#include <iostream>

void WofostModel::npk_crop_dynamics_initialize() {

   // self.ANLVI = WLV * AFGEN(NMAXLV_TB, DVS);
   // self.ANSTI = WST * AFGEN(NMAXLV_TB, DVS) * NMAXST_FR;
   // self.ANRTI = WRT * AFGEN(NMAXLV_TB, DVS) * NMAXRT_FR;
   // self.ANSOI = 0.;

   crop.state.ANLV = crop.WLV * AFGEN(crop.par.NMAXLV_TB, crop.DVS);
   crop.state.ANST = crop.WST * AFGEN(crop.par.NMAXLV_TB, crop.DVS) * crop.par.NMAXST_FR;
   crop.state.ANRT = crop.WRT * AFGEN(crop.par.NMAXLV_TB, crop.DVS) * crop.par.NMAXRT_FR;
   crop.state.ANSO = 0.;

   // self.APLVI = WLV * AFGEN(PMAXLV_TB, DVS);
   // self.APSTI = WST * AFGEN(PMAXLV_TB, DVS) * PMAXST_FR;
    //self.APRTI = WRT * AFGEN(PMAXLV_TB, DVS) * PMAXRT_FR;
   // self.APSOI = 0.;
   crop.state.APLV = crop.WLV * AFGEN(crop.par.PMAXLV_TB, crop.DVS);
   crop.state.APST = crop.WST * AFGEN(crop.par.PMAXLV_TB, crop.DVS) * crop.par.PMAXST_FR;
   crop.state.APRT = crop.WRT * AFGEN(crop.par.PMAXLV_TB, crop.DVS) * crop.par.PMAXRT_FR;
   crop.state.APSO = 0.;

    //self.AKLVI = WLV * AFGEN(KMAXLV_TB, DVS);
   // self.AKSTI = WST * AFGEN(KMAXLV_TB, DVS) * KMAXST_FR;
   // self.AKRTI = WRT * AFGEN(KMAXLV_TB, DVS) * KMAXRT_FR;
   // self.AKSOI = 0.;
   crop.state.AKLV = crop.WLV * AFGEN(crop.par.KMAXLV_TB, crop.DVS);
   crop.state.AKST = crop.WST * AFGEN(crop.par.KMAXLV_TB, crop.DVS) * crop.par.KMAXRT_FR;
   crop.state.AKRT = crop.WRT * AFGEN(crop.par.KMAXLV_TB, crop.DVS) * crop.par.KMAXRT_FR;
   crop.state.AKSO = 0.;

   crop.var.NUPTAKE_T = 0;
   crop.var.PUPTAKE_T = 0;
   crop.var.KUPTAKE_T = 0;
   crop.var.NFIX_T = 0;
   crop.var.NLOSSES_T = 0;
   crop.var.PLOSSES_T = 0;
   crop.var.KLOSSES_T = 0;

   // NUPTAKE_T = 0;
//	PUPTAKE_T = 0.;
//	KUPTAKE_T = 0.;
//	NFIX_T = 0.;
  //  NLOSSES_T = 0;
//	PLOSSES_T = 0.;
// KLOSSES_T = 0.;

}


void WofostModel::npk_crop_dynamics_rates() {

    npk_demand_uptake_rates();
	  npk_translocation_rates();

    // Compute loss of NPK due to death of plant material
    //DRLV = death rate leaves [kg dry matter ha-1 d-1]
    //DRST = death rate stems [kg dry matter ha-1 d-1]
    //DRRT = death rate roots [kg dry matter ha-1 d-1]

  double RNDLV = crop.par.NRESIDLV * crop.DRLV;
	double RNDST = crop.par.NRESIDST * crop.DRST;
	double RNDRT = crop.par.NRESIDRT * crop.DRRT;

	double RPDLV = crop.par.PRESIDLV * crop.DRLV;
	double RPDST = crop.par.PRESIDST * crop.DRST;
	double RPDRT = crop.par.PRESIDRT * crop.DRRT;

	double RKDLV = crop.par.KRESIDLV * crop.DRLV;
	double RKDST = crop.par.KRESIDST * crop.DRST;
	double RKDRT = crop.par.KRESIDRT * crop.DRRT;

   // N rates in leaves, stems, root and storage organs computed as
   // uptake - translocation - death.
   // except for storage organs which only take up as a result of translocation.
	crop.rate.RNLV = crop.rate.RNULV - crop.rate.RNTLV - RNDLV;
	crop.rate.RNST = crop.rate.RNUST - crop.rate.RNTST - RNDST;
	crop.rate.RNRT = crop.rate.RNURT - crop.rate.RNTRT - RNDRT;
	crop.rate.RNSO = crop.rate.RNUSO;

   // P rates in leaves, stems, root and storage organs
	crop.rate.RPLV = crop.rate.RPULV - crop.rate.RPTLV - RPDLV;
	crop.rate.RPST = crop.rate.RPUST - crop.rate.RPTST - RPDST;
	crop.rate.RPRT = crop.rate.RPURT - crop.rate.RPTRT - RPDRT;
	crop.rate.RPSO = crop.rate.RPUSO;

   // K rates in leaves, stems, root and storage organs
	crop.rate.RKLV = crop.rate.RKULV - crop.rate.RKTLV - RKDLV;
	crop.rate.RKST = crop.rate.RKUST - crop.rate.RKTST - RKDST;
	crop.rate.RKRT = crop.rate.RKURT - crop.rate.RKTRT - RKDRT;
	crop.rate.RKSO = crop.rate.RKUSO;

	crop.rate.RNLOSS = RNDLV + RNDST + RNDRT;
	crop.rate.RPLOSS = RPDLV + RPDST + RPDRT;
	crop.rate.RKLOSS = RKDLV + RKDST + RKDRT;

/*
   self._check_N_balance(day)
   self._check_P_balance(day)
   self._check_K_balance(day)
*/
}

void WofostModel::npk_crop_dynamics_states() {

// N amount in leaves, stems, root and storage organs
    crop.state.ANLV += crop.rate.RNLV;
    crop.state.ANST += crop.rate.RNST;
    crop.state.ANRT += crop.rate.RNRT;
    crop.state.ANSO += crop.rate.RNSO;

// P amount in leaves, stems, root and storage organs
    crop.state.APLV += crop.rate.RPLV;
    crop.state.APST += crop.rate.RPST;
    crop.state.APRT += crop.rate.RPRT;
    crop.state.APSO += crop.rate.RPSO;

// K amount in leaves, stems, root and storage organs
    crop.state.AKLV += crop.rate.RKLV;
    crop.state.AKST += crop.rate.RKST;
    crop.state.AKRT += crop.rate.RKRT;
    crop.state.AKSO += crop.rate.RKSO;

    npk_translocation_states();
    npk_demand_uptake_states();

// total NPK uptake from soil
    crop.var.NUPTAKE_T += crop.rate.RNUPTAKE;
    crop.var.PUPTAKE_T += crop.rate.RPUPTAKE;
    crop.var.KUPTAKE_T += crop.rate.RKUPTAKE;
    crop.var.NFIX_T += crop.rate.RNFIX;

    crop.var.NLOSSES_T += crop.rate.RNLOSS;
    crop.var.PLOSSES_T += crop.rate.RPLOSS;
    crop.var.KLOSSES_T += crop.rate.RKLOSS;
}


/*
    def _check_N_balance(self, day):
        states = self.states

        NUPTAKE_T  = crop.NUPTAKE_T
        NFIX_T = crop.NFIX_T

        ANLVI  = self.ANLVI
        ANSTI  = self.ANSTI
        ANRTI  = self.ANRTI
        ANSOI  = self.ANSOI

        ANLV  = crop.ANLV
        ANST  = crop.ANST
        ANRT  = crop.ANRT
        ANSO  = crop.ANSO

        NLOSST = crop.NLOSSES_T

        checksum = abs(NUPTAKE_T + NFIX_T + (ANLVI + ANSTI + ANRTI + ANSOI) -
                       (ANLV + ANST + ANRT + ANSO + NLOSST))

        if abs(checksum) >= 1.:
            msg = "N flows not balanced on day %s\n" % day
            msg += "Checksum: %f, NUPTAKE_T: %f, NFIX_T: %f\n" % (checksum, NUPTAKE_T, NFIX_T)
            msg += "ANLVI: %f, ANSTI: %f, ANRTI: %f, ANSOI: %f\n"  %(ANLVI, ANSTI, ANRTI, ANSOI)
            msg += "ANLV: %f, ANST: %f, ANRT: %f, ANSO: %f\n" % (ANLV, ANST, ANRT, ANSO)
            msg += "NLOSST: %f\n" %(NLOSST)
            raise exc.NutrientBalanceError(msg)


    def _check_P_balance(self, day):
        states = self.states
        PUPTAKE_T = crop.PUPTAKE_T

        APLVI = self.APLVI
        APSTI = self.APSTI
        APRTI = self.APRTI
        APSOI = self.APSOI

        APLV = crop.APLV
        APST = crop.APST
        APRT = crop.APRT
        APSO = crop.APSO

        PLOSST = crop.PLOSSES_T

        checksum = abs(PUPTAKE_T + (APLVI + APSTI + APRTI + APSOI) -
                       (APLV + APST + APRT + APSO + PLOSST))

        if abs(checksum) >= 1.:
            msg = "P flows not balanced on day %s\n" % day
            msg += "Checksum: %f, PUPTAKE_T: %f\n" % (checksum, PUPTAKE_T)
            msg += "APLVI: %f, APSTI: %f, APRTI: %f, APSOI: %f\n" % (APLVI, APSTI, APRTI, APSOI)
            msg += "APLV: %f, APST: %f, APRT: %f, APSO: %f\n" % (APLV, APST, APRT, APSO)
            msg += "PLOSST: %f\n" %(PLOSST)
            raise exc.NutrientBalanceError(msg)

    def _check_K_balance(self, day):
        states = self.states
        KUPTAKE_T = crop.KUPTAKE_T

        AKLVI = self.AKLVI
        AKSTI = self.AKSTI
        AKRTI = self.AKRTI
        AKSOI = self.AKSOI

        AKLV = crop.AKLV
        AKST = crop.AKST
        AKRT = crop.AKRT
        AKSO = crop.AKSO

        KLOSST = crop.KLOSSES_T

        checksum = abs(KUPTAKE_T + (AKLVI + AKSTI + AKRTI + AKSOI) -
                       (AKLV + AKST + AKRT + AKSO + KLOSST))

        if abs(checksum) >= 1.:
            msg = "K flows not balanced on day %s\n" % day
            msg += "Checksum: %f, KUPTAKE_T: %f\n"  %(checksum, KUPTAKE_T)
            msg += "AKLVI: %f, AKSTI: %f, AKRTI: %f, AKSOI: %f\n" % (AKLVI, AKSTI, AKRTI, AKSOI)
            msg += "AKLV: %f, AKST: %f, AKRT: %f, AKSO: %f\n" % (AKLV, AKST, AKRT, AKSO)
            msg += "KLOSST: %f\n" %(KLOSST)
            raise exc.NutrientBalanceError(msg)
*/
