if (finalIter)
{
    mesh.data::add("finalIteration", true);
}

if (frozenFlow)
{
    #include "EEqn.H"
}

else
{
    if (oCorr == 0)
    {
//     Info<< "rhoEqn:" << endl;
        #include "rhoEqn.H"
    }

    #include "UEqn.H"
//     Info<< "UEqn:" << endl;
    #include "YEqn.H"
 //    Info<< "YEqn:" << endl;
    #include "EEqn.H"
 //    Info<< "EEqn:" << endl;

    // --- PISO loop
    for (int corr=0; corr<nCorr; corr++)
    {
        #include "pEqn.H"
    }

    turb.correct();

    rho = thermo.rho();
}

if (finalIter)
{
    mesh.data::remove("finalIteration");
}
