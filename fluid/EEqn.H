{
    volScalarField& he = thermo.he();
//     Info<< "EEqn:" << endl;
    fvScalarMatrix EEqn
    (
        porosity*fvm::ddt(rho, he) + porosity*fvm::div(phi, he)
      + fvc::ddt(rho, K) + fvc::div(phi, K)
      + (
            he.name() == "e"
          ? fvc::div
            (
                fvc::absolute(phi/fvc::interpolate(porosity*rho), U),
                p,
                "div(phiv,p)"
            )
          : -dpdt
        )
      - porosity*fvm::laplacian(kkD*turb.alphaEff(), he)
     ==
        porosity*rho*(U&g)
      + rad.Sh(thermo,he)
      + porosity*reaction.Qdot()
      + fvOptions(rho, he)
      - heatTransfer
    );

    EEqn.relax();

    fvOptions.constrain(EEqn);

    EEqn.solve(mesh.solver(he.select(finalIter)));

    fvOptions.correct(he);

    thermo.correct();
    rad.correct();

    Info<< "Min/max T:" << min(thermo.T()).value() << ' '
        << max(thermo.T()).value() << endl;
//    Info<< "EEqnEnd:" << endl;
}
