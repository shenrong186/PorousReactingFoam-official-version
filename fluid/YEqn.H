//   Info<< "YEqn:" << endl;
tmp<fv::convectionScheme<scalar>> mvConvection
(
    fv::convectionScheme<scalar>::New
    (
        mesh,
        fields,
        phi,
        mesh.divScheme("div(phi,Yi)")
    )
);
//     Info<< "Debug1" << endl;
{
    reaction.correct();
    dQ = reaction.Qdot();
    label inertIndex = -1;
    volScalarField Yt(0.0*Y[0]);
//     Info<< "Debug2" << endl;
    forAll(Y, i)
    {
 //    Info<< "Debug3" << endl;
        if (Y[i].name() != inertSpecie)
        {
            volScalarField& Yi = Y[i];
 //    Info<< "Debug4" << endl;
            fvScalarMatrix YiEqn
            (
                fvm::ddt(rho, Yi)
              + mvConvection->fvmDiv(phi, Yi)
              - fvm::laplacian(turb.muEff(), Yi)
             ==
                reaction.R(Yi)
              + fvOptions(rho, Yi)
            );
  //   Info<< "Debug5" << endl;
            YiEqn.relax();
  //   Info<< "Debug6" << endl;
            fvOptions.constrain(YiEqn);
  //   Info<< "Debug7" << endl;
            YiEqn.solve(mesh.solver("Yi"));
 //    Info<< "Debug8" << endl;
            fvOptions.correct(Yi);
  //   Info<< "Debug9" << endl;
            Yi.max(0.0);
            Yt += Yi;
  //  Info<< "Debug10" << endl;
        }
        else
        {
            inertIndex = i;
        }
    }

    Y[inertIndex] = scalar(1) - Yt;
    Y[inertIndex].max(0.0);
}

  //  Info<< "YEqnEnd:" << endl;
