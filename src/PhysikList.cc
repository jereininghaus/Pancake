#include "PhysikList.hh"
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

PhysikList::PhysikList() : G4VModularPhysicsList() {
    // Standard EM Physik hinzufügen
    RegisterPhysics(new G4EmStandardPhysics());

    // Optische Physik hinzufügen
    RegisterPhysics(new G4OpticalPhysics());
}

PhysikList::~PhysikList() {}

void PhysikList::ConstructParticle() {

    //Basispartikle
    G4Gamma::GammaDefinition();
    G4Electron::ElectronDefinition();
    G4Positron::PositronDefinition();
    G4Proton::ProtonDefinition();
    G4GenericIon::GenericIonDefinition();  // Für Ionen


    AddTransportation();
    G4PhysicsListHelper* ph = G4PhysicsListHelper::GetPhysicsListHelper();

    auto particleIterator=GetParticleIterator();
    particleIterator->reset();
    while ((*particleIterator)()) {
        G4ParticleDefinition* particle = particleIterator->value();
        G4String particleName = particle->GetParticleName();

        if (particleName == "gamma") {
            // Photonenprozesse
            ph->RegisterProcess(new G4PhotoElectricEffect, particle);
            ph->RegisterProcess(new G4ComptonScattering, particle);
            ph->RegisterProcess(new G4GammaConversion, particle);
        }
        // Weitere Prozesse für andere Partikel
    }
}

void PhysikList::ConstructProcess() {
    G4VModularPhysicsList::ConstructProcess();
}
