//Re number function

volScalarField cal_Re
(
    const dimensionedScalar dm,
    const volScalarField rho,
    const volVectorField U,
    const volScalarField mu
)
{
    volScalarField Re
    (
        dm*mag(U)*rho/mu
    );
    return Re;
}
