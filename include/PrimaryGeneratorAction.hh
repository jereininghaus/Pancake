#ifndef PrimaryGeneratorAction_hh
#define PrimaryGeneratorAction_hh

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"


namespace B1 {
class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction {
public:
    PrimaryGeneratorAction();
    virtual ~PrimaryGeneratorAction();

    virtual void GeneratePrimaries(G4Event* event) override;

    const G4ParticleGun* GetParticleGun() const;

private:
    G4ParticleGun* fParticleGun;
    G4double pi = 3.1415926;
    G4double twopi = 2 * pi;
};

}
#endif
