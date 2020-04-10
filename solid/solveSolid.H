if (finalIter)
{
    mesh.data::add("finalIteration", true);
}
Info<< "Solid" << endl;
{
    for (int nonOrth=0; nonOrth<=nNonOrthCorr; nonOrth++)
    {
        fvScalarMatrix hEqn
        (
            fvm::ddt(betav*rho*(1-porosity), h)
          - (
               thermo.isotropic()
             ? fvm::laplacian(betav*kka*thermo.alpha(), h, "laplacian(alpha,h)")
             : fvm::laplacian(betav*taniAlpha(), h, "laplacian(alpha,h)")
            )
          ==
            fvOptions(rho, h)
          + heatTransfer
         - Hlose
        );

        hEqn.relax();

        fvOptions.constrain(hEqn);

        hEqn.solve(mesh.solver(h.select(finalIter)));

        fvOptions.correct(h);
    }
}

thermo.correct();

Info<< "Min/max T:" << min(thermo.T()).value() << ' '
    << max(thermo.T()).value() << endl;

if (finalIter)
{
    mesh.data::remove("finalIteration");
}
