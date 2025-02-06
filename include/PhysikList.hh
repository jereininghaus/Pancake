#ifndef PhysikList_h
#define PhysikList_h 1

#include "G4VModularPhysicsList.hh"
#include "G4EmStandardPhysics.hh"
#include "G4OpticalPhysics.hh"
#include "G4PhotoElectricEffect.hh"
#include "G4ComptonScattering.hh"
#include "G4GammaConversion.hh"
#include "G4VModularPhysicsList.hh"
#include "G4Gamma.hh"
#include "G4Electron.hh"
#include "G4Positron.hh"
#include "G4Proton.hh"
#include "G4GenericIon.hh"
#include "G4Transportation.hh"
#include "G4PhysicsListHelper.hh"
//#include "G4MultipleScattering.hh"
#include "G4hIonisation.hh"
#include "G4ionIonisation.hh"
#include "G4PhotoElectricEffect.hh"
#include "G4ComptonScattering.hh"
#include "G4GammaConversion.hh"
#include "G4Transportation.hh"


class PhysikList : public G4VModularPhysicsList {
public:
    PhysikList();
    virtual ~PhysikList();

    virtual void ConstructParticle();
    virtual void ConstructProcess();
};

#endif

