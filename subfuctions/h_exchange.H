//heat exchande

volScalarField cal_hcv
(
    const volScalarField Tg,
    const volScalarField Ts,
    const volScalarField hv
)
{
    volScalarField hcv
    (
        (Tg-Ts)*hv
    );
    return hcv;
}
