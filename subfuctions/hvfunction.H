//hv

volScalarField cal_hv
(
    const dimensionedScalar dm,
    const volScalarField Nu,
    const volScalarField kappa
)
{
    volScalarField hv
    (
        kappa*Nu/dm/dm
    );
    return hv;
}
