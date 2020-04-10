
    combustionModels::rhoCombustionModel& reactiontemp = reactionFluid[i];
    rhoReactionThermo& thermoFluidtemp = reactiontemp.thermo();
    solidThermo& thermoSolidtemp = thermos[i];
    volScalarField& heatTransfer = heatTransfers[i];
    volVectorField& Ut = UFluid[i];
    volScalarField& NuFluid = NuFluids[i];
    volScalarField& htransferFluid=htransferFluids[i];
    compressible::turbulenceModel& turbt = turbulence[i];
    volScalarField& REnumber = REnumbers[i];
    dimensionedScalar& dm = fdms[i];
    dimensionedScalar& c_Nu = fc_Nus[i];
    dimensionedScalar& m_Nu = fm_Nus[i];
    dimensionedScalar& L = fLs[i];
    dimensionedScalar& CDm = fCDms[i];
    dimensionedScalar& Crad = sCrads[i];
    dimensionedScalar& porosity = fporositys[i];
    scalar& Simode = Simodes[i];
    volScalarField& TFluid = thermoFluidtemp.T();
    volScalarField& TSolid = thermoSolidtemp.T();
    volScalarField& kka = kkas[i];
    volScalarField& kkD = kkDs[i];
    volVectorField& Si = SiFluid[i];
    volScalarField& K1 = K1Fluid[i];
    volScalarField& K2 = K2Fluid[i];
    volScalarField& T_en = T_ens[i];
    volScalarField& fix = fixs[i];
    volScalarField& Hlose = Hloses[i];



