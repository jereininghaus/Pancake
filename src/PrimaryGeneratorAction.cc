#include "PrimaryGeneratorAction.hh"

#include "G4MuonMinus.hh"
#include "G4MuonPlus.hh"
#include "G4OpticalPhoton.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleGun.hh"
#include "Randomize.hh"
//#include "TRandom3.h"

namespace B1 {
PrimaryGeneratorAction::PrimaryGeneratorAction() {
    fParticleGun = new G4ParticleGun(1);


// Einfache Implementierung einer cos² Intensitätsverteilung
    double F = G4UniformRand();  // Random number
//    double theta = acos(pow(1 - F, 1.0 / 3.0));  // Inverse CDF für Cos^2 Verteilung

    G4double theta=pi*G4UniformRand() ;
    G4double phi=twopi*G4UniformRand();

    G4double x_dir=sin(theta)*cos(phi);
    G4double y_dir=sin(theta)*sin(phi);
    G4double z_dir=-cos(theta);

    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0, 0, -1)); // Direction of Particle
}

PrimaryGeneratorAction::~PrimaryGeneratorAction() {
    delete fParticleGun;
   
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* event) {
    //ratio mu+/mu-: 1.27
    double charge_ratio=1.27;
    G4ParticleDefinition* particleDefinition;
    if (G4UniformRand() < 1.0 / (1.0 + charge_ratio)) {
        particleDefinition = G4MuonPlus::MuonPlusDefinition();
    } else {
        particleDefinition = G4MuonMinus::MuonMinusDefinition();
    }
//    G4ParticleDefinition* particleDefinition2 = G4OpticalPhoton::OpticalPhotonDefinition();
    fParticleGun->SetParticleDefinition(particleDefinition);

    //Set particle Energy random between 2-10GeV
    double energy = 2; //2 + 8 * G4UniformRand();
    fParticleGun->SetParticleEnergy(energy * GeV);

    //Set random position
    G4double sizeX = 20.0 * m;
    G4double sizeY = 20.0 * m;
    G4double height = 2.5 * m;

    G4double posX = -0.5 * sizeX + G4UniformRand() * sizeX; // Zufällige X Position
    G4double posY = -0.5 * sizeY + G4UniformRand() * sizeY; // Zufällige Y Position

    fParticleGun->SetParticlePosition(G4ThreeVector(0 * cm, 0 * cm, height)); // Startposition oberhalb des Detektors
    fParticleGun->GeneratePrimaryVertex(event);
}

const G4ParticleGun* PrimaryGeneratorAction::GetParticleGun() const {
    return fParticleGun;
}
}
