
#ifndef B1DetectorConstruction_h
#define B1DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "globals.hh"
#include "G4OpticalSurface.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;

/// Detector construction class to define materials and geometry.

namespace B1
{

class DetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    DetectorConstruction();
    ~DetectorConstruction();

    G4VPhysicalVolume* Construct();
    G4Material* CreateLiquidXenon();
    G4Material* CreateGasXenon();
    G4Material* CreateTeflon();
    void SetVisualAttributes();
    void ConstructMaterials();
    
    G4LogicalVolume* GetScoringVolume() const { return fScoringVolume; }

  protected:
    G4LogicalVolume* fScoringVolume = nullptr;

  private:
//    G4Material* CreateLiquidXenon();
    G4Material* CreateStainlessSteel();
    G4OpticalSurface* CreateMirrorSurface();

    G4Material* fLiquidXenon;
    G4Material* fStainlessSteel;
};

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
