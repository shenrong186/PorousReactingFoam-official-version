//kkD

volScalarField cal_kkD
(
    const dimensionedScalar L,
    const dimensionedScalar CDm,
    const volVectorField U,
    const volScalarField alpha,
    const volScalarField rho
)
{
    volScalarField kkD
    (
        rho*0.5*CDm*mag(U)*L/alpha+1
    );
    return kkD;
}
