fvMesh& mesh = solidRegions[i];
solidThermo& thermo = thermos[i];
dimensionedScalar& porosity = fporositys[i];
volScalarField& heatTransfer = heatTransfers[i];
volScalarField& kka = kkas[i];
volScalarField& Hlose = Hloses[i];
tmp<volScalarField> trho = thermo.rho();

const volScalarField& rho = trho();


tmp<volScalarField> tcp = thermo.Cp();
const volScalarField& cp = tcp();

tmp<volSymmTensorField> taniAlpha;
if (!thermo.isotropic())
{
    volSymmTensorField& aniAlpha = aniAlphas[i];
    tmp<volVectorField> tkappaByCp = thermo.Kappa()/cp;
    const coordinateSystem& coodSys = coordinates[i];

    aniAlpha.primitiveFieldRef() =
        coodSys.R().transformVector(tkappaByCp());
    aniAlpha.correctBoundaryConditions();

    taniAlpha = tmp<volSymmTensorField>
    (
        new volSymmTensorField(aniAlpha)
    );
}


volScalarField& h = thermo.he();

const volScalarField& betav = betavSolid[i];

fv::options& fvOptions = solidHeatSources[i];
