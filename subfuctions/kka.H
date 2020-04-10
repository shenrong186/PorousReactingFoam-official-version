//kka

volScalarField cal_kka
(
    const dimensionedScalar dm,
    const dimensionedScalar porosity,
    const dimensionedScalar c_rad,
    const dimensionedScalar Crad,
    const volScalarField Ts,
    const volScalarField kappa
)
{
    volScalarField kka
    (
        16*c_rad*Crad*Ts*Ts*Ts/3/((3/dm)*(1-porosity))/kappa+(1-porosity)
    );
    return kka;
}
