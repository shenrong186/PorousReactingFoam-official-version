    fvMesh& mesh = fluidRegions[i];
    volVectorField& Si = SiFluid[i];
    dimensionedScalar& porosity = fporositys[i];
    volScalarField& heatTransfer = heatTransfers[i];
    volScalarField& kkD = kkDs[i];
    combustionModels::rhoCombustionModel& reaction = reactionFluid[i];
    rhoReactionThermo& thermo = reaction.thermo();
    basicMultiComponentMixture& composition = reactionFluid[i].thermo().composition();	
    PtrList<volScalarField>& Y = composition.Y(); 
    thermo.validate(args.executable(), "h", "e");

    volScalarField& rho = rhoFluid[i];

    volVectorField& U = UFluid[i];
    surfaceScalarField& phi = phiFluid[i];


    compressible::turbulenceModel& turb = turbulence[i];
    volScalarField& K = KFluid[i];
    volScalarField& dpdt = dpdtFluid[i];
    volScalarField& dQ = dQFluid[i];



    volScalarField& p = thermo.p();
    const volScalarField& psi = thermo.psi();

    volScalarField& p_rgh = p_rghFluid[i];

    const dimensionedVector& g = gFluid[i];
    const volScalarField& gh = ghFluid[i];
    const surfaceScalarField& ghf = ghfFluid[i];

    radiation::radiationModel& rad = radiation[i];

    IOMRFZoneList& MRF = MRFfluid[i];
    fv::options& fvOptions = fluidFvOptions[i];
    multivariateSurfaceInterpolationScheme<scalar>::fieldTable fields = fieldsFluid[i];
    
    const dimensionedScalar initialMass
    (
        "initialMass",
        dimMass,
        initialMassFluid[i]
    );

    const bool frozenFlow = frozenFlowFluid[i];

    const word inertSpecie(thermo.lookup("inertSpecie"));




 //   solidThermo& thermoSolidtemp = thermos[0];
 //   volScalarField& heatTransfer = heatTransfers[0];
 //   volScalarField& NuFluid = NuFluids[0];
 //   volScalarField& htransferFluid=htransferFluids[0];
//        Info<< "turbt = " << turbt.mu()<<  nl << endl;
//tmp<volScalarField>  alp= turbt.mu();
//DimensionedField alpv= alp().internalField();
  //   volScalarField& REnumber = REnumbers[0];
//Info<< "turbt = " << alp().internalField()[1]<<  nl << endl;
    //   Info<< "Umax= " << max(mag(U)).value() <<  nl << endl;

/*REnumber=thermo.rho()*mag(U)*dm/turb.mu();

NuFluid=c_Nu*pow(REnumber,m_Nu);
htransferFluid=NuFluid*thermo.kappa()/lm/lm;
volScalarField& TFluid = thermo.T();
volScalarField& TSolid = thermoSolidtemp.T();
volScalarField& Hlose = Hloses[0];
volScalarField& T_en = T_ens[0];
heatTransfer=htransferFluid*dimensionfix*(TFluid-TSolid);


//heatTransfer= c_rad*AoV*(TFluid*TFluid*TFluid*TFluid-TSolid*TSolid*TSolid*TSolid)+h_const*AoV*(TFluid-TSolid);

//Hlose=h_lose*AoV_lose*(TSolid-T_en);
//Hlose[500]=0.8*c_rad*AoV*(TSolid[500]*TSolid[500]*TSolid[500]*TSolid[500]-T_en*T_en*T_en*T_en);
*/
