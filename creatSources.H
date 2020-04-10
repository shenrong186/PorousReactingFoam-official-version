
    kkD=cal_kkD(L,CDm,Ut,turbt.alpha(),thermoFluidtemp.rho());
    REnumber=cal_Re(dm,thermoFluidtemp.rho(),Ut,turbt.mu());
    NuFluid=cal_Nu(c_Nu,m_Nu,REnumber);
    htransferFluid=cal_hv(dm,NuFluid,thermoFluidtemp.kappa());
    heatTransfer=cal_hcv(TFluid,TSolid,htransferFluid);
    kka=cal_kka(dm,porosity,c_rad,Crad,TSolid,thermoSolidtemp.kappa());
//---------------------------------------------------//
    if(Simode)
    {
    Si = cal_Siv(K1,K2,turbt.mu(),thermoFluidtemp.rho(),Ut);
    }
    else
    {
    Si = cal_Sic(K1,K2,Ut);
    }
//------------------------------------------------//
    Hlose=fix*c_rad*AoV_lose*(TSolid*TSolid*TSolid*TSolid-T_en*T_en*T_en*T_en);


