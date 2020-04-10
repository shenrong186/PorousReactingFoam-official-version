// Initialise fluid field pointer lists
PtrList<combustionModels::rhoCombustionModel> reactionFluid(fluidRegions.size());
PtrList<volScalarField> rhoFluid(fluidRegions.size());
PtrList<volVectorField> UFluid(fluidRegions.size());

PtrList<volVectorField> SiFluid(fluidRegions.size());
PtrList<volScalarField> heatTransfers(fluidRegions.size());
PtrList<volScalarField> REnumbers(fluidRegions.size());


PtrList<surfaceScalarField> phiFluid(fluidRegions.size());
PtrList<uniformDimensionedVectorField> gFluid(fluidRegions.size());
PtrList<uniformDimensionedScalarField> hRefFluid(fluidRegions.size());


PtrList<volScalarField> K1Fluid(fluidRegions.size());
PtrList<volScalarField> K2Fluid(fluidRegions.size());
PtrList<volScalarField> NuFluids(fluidRegions.size());
PtrList<volScalarField> htransferFluids(fluidRegions.size());
PtrList<volScalarField> kkDs(fluidRegions.size());


PtrList<IOdictionary>fops(fluidRegions.size());
PtrList<dimensionedScalar>fporositys(fluidRegions.size());
PtrList<dimensionedScalar>fdms(fluidRegions.size());
PtrList<dimensionedScalar>fc_Nus(fluidRegions.size());
PtrList<dimensionedScalar>fm_Nus(fluidRegions.size());
PtrList<dimensionedScalar>fLs(fluidRegions.size());
PtrList<dimensionedScalar>fCDms(fluidRegions.size());
PtrList<scalar>Simodes(fluidRegions.size());



PtrList<volScalarField> ghFluid(fluidRegions.size());
PtrList<surfaceScalarField> ghfFluid(fluidRegions.size());
PtrList<compressible::turbulenceModel> turbulence(fluidRegions.size());
PtrList<volScalarField> p_rghFluid(fluidRegions.size());
PtrList<radiation::radiationModel> radiation(fluidRegions.size());
PtrList<volScalarField> KFluid(fluidRegions.size());
PtrList<volScalarField> dpdtFluid(fluidRegions.size());
PtrList<volScalarField> dQFluid(fluidRegions.size());

List<scalar> initialMassFluid(fluidRegions.size());
List<bool> frozenFlowFluid(fluidRegions.size(), false);

PtrList<IOMRFZoneList> MRFfluid(fluidRegions.size());
PtrList<fv::options> fluidFvOptions(fluidRegions.size());
PtrList<multivariateSurfaceInterpolationScheme<scalar>::fieldTable> fieldsFluid(fluidRegions.size());


// Populate fluid field pointer lists
forAll(fluidRegions, i)
{
    Info<< "*** Reading fluid mesh thermophysical properties for region "
        << fluidRegions[i].name() << nl << endl;

    Info<< "    Creating combustion model\n" << endl;

    reactionFluid.set
    (
        i,
        combustionModels::rhoCombustionModel::New(fluidRegions[i]).ptr()
    );

    Info<< "    Adding to rhoFluid\n" << endl;
    rhoFluid.set
    (
        i,
        new volScalarField
        (
            IOobject
            (
                "rho",
                runTime.timeName(),
                fluidRegions[i],
                IOobject::NO_READ,
                IOobject::AUTO_WRITE
            ),
            reactionFluid[i].thermo().rho()
        )
    );
//--------------------------------------------------//
    Info<< "    Adding to opsFluid\n" << endl;
    fops.set
    (
        i,
        new IOdictionary
        (
            IOobject
            (
                 "Options",
                 runTime.constant(),
                 fluidRegions[i],
                 IOobject::MUST_READ,
                 IOobject::NO_WRITE
            )
        )
    );

    fporositys.set
    (
        i,
        new dimensionedScalar
        (
              "porosity",
               fops[i].lookup("porosity")
        )
    );
    fLs.set
    (
        i,
        new dimensionedScalar
        (
              "L",
               fops[i].lookup("L")
        )
    );
    fCDms.set
    (
        i,
        new dimensionedScalar
        (
              "CDm",
               fops[i].lookup("CDm")
        )
    );
    Simodes.set
    (
        i,
        new scalar
        (
        readScalar(fops[i].lookup("Simode"))
        )
    );
    fdms.set
    (
        i,
        new dimensionedScalar
        (
              "dm",
               fops[i].lookup("dm")
        )
    );
    fc_Nus.set
    (
        i,
        new dimensionedScalar
        (
              "c_Nu",
               fops[i].lookup("c_Nu")
        )
    );
    fm_Nus.set
    (
        i,
        new dimensionedScalar
        (
              "m_Nu",
               fops[i].lookup("m_Nu")
        )
    );
//--------------------------------------------------//
    Info<< "    Adding to UFluid\n" << endl;
    UFluid.set
    (
        i,
        new volVectorField
        (
            IOobject
            (
                "U",
                runTime.timeName(),
                fluidRegions[i],
                IOobject::MUST_READ,
                IOobject::AUTO_WRITE
            ),
            fluidRegions[i]
        )
    );

//---------------------------------------------------//
    Info<< "    Adding to phiFluid\n" << endl;
    phiFluid.set
    (
        i,
        new surfaceScalarField
        (
            IOobject
            (
                "phi",
                runTime.timeName(),
                fluidRegions[i],
                IOobject::READ_IF_PRESENT,
                IOobject::AUTO_WRITE
            ),
            linearInterpolate(rhoFluid[i]*UFluid[i])
                & fluidRegions[i].Sf()
        )
    );

    Info<< "    Adding to gFluid\n" << endl;
    gFluid.set
    (
        i,
        new uniformDimensionedVectorField
        (
            IOobject
            (
                "g",
                runTime.constant(),
                fluidRegions[i],
                IOobject::MUST_READ,
                IOobject::NO_WRITE
            )
        )
    );

//------------------------------------------------//
    Info<< "    Adding to REnumbers\n" << endl;
    REnumbers.set
    (
        i,
        new volScalarField
        (
            IOobject
            (
                "REnumber",
                runTime.timeName(),
                fluidRegions[i],
                IOobject::MUST_READ,
                IOobject::AUTO_WRITE
            ),
            fluidRegions[i]
        )
    );
    Info<< "    Adding to kkD\n" << endl;
    kkDs.set
    (
        i,
        new volScalarField
        (
            IOobject
            (
                "kkD",
                runTime.timeName(),
                fluidRegions[i],
                IOobject::MUST_READ,
                IOobject::AUTO_WRITE
            ),
            fluidRegions[i]
        )
    );
    Info<< "    Adding to NuFluids\n" << endl;
    NuFluids.set
    (
        i,
        new volScalarField
        (
            IOobject
            (
                "Nu",
                runTime.timeName(),
                fluidRegions[i],
                IOobject::MUST_READ,
                IOobject::AUTO_WRITE
            ),
            fluidRegions[i]
        )
    );
    Info<< "    Adding to htransferFluids\n" << endl;
    htransferFluids.set
    (
        i,
        new volScalarField
        (
            IOobject
            (
                "htransfer",
                runTime.timeName(),
                fluidRegions[i],
                IOobject::MUST_READ,
                IOobject::AUTO_WRITE
            ),
            fluidRegions[i]
        )
    );
//------------------------------------------------//
    Info<< "    Adding to heatTransfers\n" << endl;
    heatTransfers.set
    (
        i,
        new volScalarField
        (
            IOobject
            (
                "heatTransfer",
                runTime.timeName(),
                fluidRegions[i],
                IOobject::MUST_READ,
                IOobject::AUTO_WRITE
            ),
            fluidRegions[i]
        )
    );
    Info<< "    Adding to K1Fluid\n" << endl;
    K1Fluid.set
    (
        i,
        new volScalarField
        (
            IOobject
            (
                "K1",
                runTime.timeName(),
                fluidRegions[i],
                IOobject::MUST_READ,
                IOobject::AUTO_WRITE
            ),
            fluidRegions[i]
        )
    );
//------------------------------------------------//
    Info<< "    Adding to K2Fluid\n" << endl;
    K2Fluid.set
    (
        i,
        new volScalarField
        (
            IOobject
            (
                "K2",
                runTime.timeName(),
                fluidRegions[i],
                IOobject::MUST_READ,
                IOobject::AUTO_WRITE
            ),
            fluidRegions[i]
        )
    );
//------------------------------------------------//

//------------------------------------------------//

    Info<< "    Adding to SiFluid\n" << endl;
    SiFluid.set
    (
        i,
        new volVectorField
        (
            IOobject
            (
                "Si",
                runTime.timeName(),
                fluidRegions[i],
                IOobject::MUST_READ,
                IOobject::AUTO_WRITE
            ),
            fluidRegions[i]
        )
    );
//---------------------------------------------------//
//SiFluid[i] = -(UFluid[i]*uuuFluid[i]/aFluid[i]+C2Fluid[i]*0.5*fixUFluid[i]*rhoFluid[i]*magSqr(UFluid[i])*UFluid[i]);
//------------------------------------------------//
    Info<< "    Adding to hRefFluid\n" << endl;
    hRefFluid.set
    (
        i,
        new uniformDimensionedScalarField
        (
            IOobject
            (
                "hRef",
                runTime.constant(),
                fluidRegions[i],
                IOobject::READ_IF_PRESENT,
                IOobject::NO_WRITE
            ),
            dimensionedScalar("hRef", dimLength, 0)
        )
    );

    dimensionedScalar ghRef
    (
        mag(gFluid[i].value()) > SMALL
      ? gFluid[i]
          & (cmptMag(gFluid[i].value())/mag(gFluid[i].value()))*hRefFluid[i]
      : dimensionedScalar("ghRef", gFluid[i].dimensions()*dimLength, 0)
    );

    Info<< "    Adding to ghFluid\n" << endl;
    ghFluid.set
    (
        i,
        new volScalarField
        (
            "gh",
            (gFluid[i] & fluidRegions[i].C()) - ghRef
        )
    );

    Info<< "    Adding to ghfFluid\n" << endl;
    ghfFluid.set
    (
        i,
        new surfaceScalarField
        (
            "ghf",
            (gFluid[i] & fluidRegions[i].Cf()) - ghRef
        )
    );

    Info<< "    Adding to turbulence\n" << endl;
    turbulence.set
    (
        i,
        compressible::turbulenceModel::New
        (
            rhoFluid[i],
            UFluid[i],
            phiFluid[i],
            reactionFluid[i].thermo()
        ).ptr()
    );

// Set the turbulence into the reaction model
    reactionFluid[i].setTurbulence(turbulence[i]);


    p_rghFluid.set
    (
        i,
        new volScalarField
        (
            IOobject
            (
                "p_rgh",
                runTime.timeName(),
                fluidRegions[i],
                IOobject::MUST_READ,
                IOobject::AUTO_WRITE
            ),
            fluidRegions[i]
        )
    );

    // Force p_rgh to be consistent with p
    p_rghFluid[i] = reactionFluid[i].thermo().p() - rhoFluid[i]*ghFluid[i];

    fluidRegions[i].setFluxRequired(p_rghFluid[i].name());

    radiation.set
    (
        i,
        radiation::radiationModel::New(reactionFluid[i].thermo().T())
    );

    initialMassFluid[i] = fvc::domainIntegrate(rhoFluid[i]).value();

    Info<< "    Adding to KFluid\n" << endl;
    KFluid.set
    (
        i,
        new volScalarField
        (
            "K",
            0.5*magSqr(UFluid[i])
        )
    );

    Info<< "    Adding to dpdtFluid\n" << endl;
    dpdtFluid.set
    (
        i,
        new volScalarField
        (
            IOobject
            (
                "dpdt",
                runTime.timeName(),
                fluidRegions[i]
            ),
            fluidRegions[i],
            dimensionedScalar
            (
                "dpdt",
                reactionFluid[i].thermo().p().dimensions()/dimTime,
                0
            )
        )
    );

   Info<< "    Adding to dQ\n" << endl;
   dQFluid.set
   (
        i,
        new volScalarField
        (
            IOobject
            (
                "dQ",
                runTime.timeName(),
                fluidRegions[i],
                IOobject::NO_READ,
                IOobject::AUTO_WRITE
            ),
                fluidRegions[i],
                dimensionedScalar
            (
                "dQ",
                dimEnergy/dimVolume/dimTime,
                0
            )
        )
    );

    const dictionary& pimpleDict =
        fluidRegions[i].solutionDict().subDict("PIMPLE");
    pimpleDict.readIfPresent("frozenFlow", frozenFlowFluid[i]);

    Info<< "    Adding MRF\n" << endl;
    MRFfluid.set
    (
        i,
        new IOMRFZoneList(fluidRegions[i])
    );

    Info<< "    Adding fvOptions\n" << endl;
    fluidFvOptions.set
    (
        i,
        new fv::options(fluidRegions[i])
    );

    turbulence[i].validate();

    fieldsFluid.set
    	(
    	    i,
			new multivariateSurfaceInterpolationScheme<scalar>::fieldTable 
		);
		
    basicMultiComponentMixture& composition = reactionFluid[i].thermo().composition();	
	
	forAll(composition.Y(), j)
	{
		    fieldsFluid[i].add(composition.Y()[i]);
	}
		
    fieldsFluid[i].add(reactionFluid[i].thermo().he());
}
