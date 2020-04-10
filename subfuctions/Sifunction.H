//Si function

volVectorField cal_Siv
(
    const volScalarField K1,
    const volScalarField K2,
    const volScalarField mu,
    const volScalarField rho,
    const volVectorField U
)
{
    volScalarField f1
    (
    mu/K1
    );
    volScalarField f2
    (
    rho/K2
    );
    volVectorField Si
    (
        f1*U+f2*mag(U)*U
    );
    return Si;
}

volVectorField cal_Sic
(
    const volScalarField K1,
    const volScalarField K2,
    const volVectorField U
)
{
    volVectorField Si
    (
        K1*U+K2*mag(U)*U
    );
    return Si;
}
