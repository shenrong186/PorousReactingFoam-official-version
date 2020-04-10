//Nu number function

volScalarField cal_Nu
(
    const dimensionedScalar C,
    const dimensionedScalar m,
    const volScalarField Re
)
{
    volScalarField Nu
    (
        C*pow(Re,m)
    );
    return Nu;
}
