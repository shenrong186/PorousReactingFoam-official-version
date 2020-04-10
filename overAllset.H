//overAllset


                IOdictionary overAllOptions
                 (
                 IOobject
                 (
                 "overAllOptions",
                 runTime.constant(),
                 runTime,
                 IOobject::MUST_READ,
                 IOobject::NO_WRITE
                 )
                 );

dimensionedScalar c_rad
(
    "c_rad",
    overAllOptions.lookup("c_rad")
);
dimensionedScalar AoV_lose
(
    "AoV_lose",
    overAllOptions.lookup("AoV_lose")
);
