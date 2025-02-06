
// Construction of Bathtub with scintillator Panels
//
/// \file DetectorConstruction.cc
/// \brief Implementation of the B1::DetectorConstruction class

#include "DetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4SubtractionSolid.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4ThreeVector.hh"
#include "G4UnionSolid.hh"

//#include "SimpleScorer.hh"
#include "G4SDManager.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4ParticleTable.hh"
#include "G4UserLimits.hh"

#include "G4Material.hh"
#include "G4MaterialPropertiesTable.hh"
#include "G4OpticalSurface.hh"
#include "G4LogicalBorderSurface.hh"

namespace B1
{

DetectorConstruction::DetectorConstruction()
{ConstructMaterials();
}

DetectorConstruction::~DetectorConstruction()
{}

void DetectorConstruction::ConstructMaterials() {
//    G4Material* lxenon = CreateLiquidXenon();
    fStainlessSteel = CreateStainlessSteel();
    G4OpticalSurface* mirrorSurface = CreateMirrorSurface();
    // Hier könnten Sie die Oberfläche den Grenzflächen zuweisen
}

G4Material* DetectorConstruction::CreateLiquidXenon() {
    G4double density = 3.02 * g/cm3;  // Dichte von flüssigem Xenon
    G4double atomicNumber = 54.0;
    G4double atomicMass = 131.29 * g/mole;
    
    G4Material* liquidXenon = new G4Material("LiquidXenon", atomicNumber, atomicMass, density);

    // Definieren der optischen Eigenschaften
    std::vector<G4double> photonEnergy = {7.0*eV, 7.07*eV, 7.14*eV};
    std::vector<G4double> scintillationYield = {0.1, 1.0, 0.1};  // Beispielwerte
    std::vector<G4double> refractiveIndices={1.59, 1.57, 1.54};
    std::vector<G4double> absorptionLengths={35.*cm, 35.*cm, 35.*cm};

    std::vector<G4double> scint_e = { 0.*MeV, 10.*MeV };
    std::vector<G4double> scint_default = { 0., 120000.};
    std::vector<G4double> scint_alpha = { 0., 132000.};
    std::vector<G4double> scint_ion = { 0., 24000.};


    G4MaterialPropertiesTable* mptXenon = new G4MaterialPropertiesTable();

// Hope to help
    const G4int nEntries = 5;
    G4double energy[nEntries] = {1.0 * MeV, 10.0 * MeV, 100.0 * MeV, 1.0 * GeV, 10.0 * GeV}; // Example photon energies
    G4double scintYield[nEntries] = {500.0, 450.0, 400.0, 350.0, 300.0}; // Example scintillation yields (photons/MeV)
    mptXenon->AddProperty("SCINTILLATIONYIELD", energy, scintYield, nEntries,true);

    mptXenon->AddProperty("SCINTILLATIONCOMPONENT1", photonEnergy, scintillationYield);
    mptXenon->AddProperty("SCINTILLATIONCOMPONENT2", photonEnergy, scintillationYield);
    mptXenon->AddProperty("RINDEX", photonEnergy, refractiveIndices);
    mptXenon->AddProperty("ABSLENGTH", photonEnergy, absorptionLengths);

//Included from DMX
    mptXenon->AddProperty("ELECTRONSCINTILLATIONYIELD", scint_e, scint_default); // include QE 20%
    mptXenon->AddConstProperty("ELECTRONSCINTILLATIONYIELD1", 0.);
    mptXenon->AddConstProperty("ELECTRONSCINTILLATIONYIELD2", 1.);


    mptXenon->AddProperty("ALPHASCINTILLATIONYIELD", scint_e, scint_alpha); // include QE 20%
    mptXenon->AddConstProperty("ALPHASCINTILLATIONYIELD1", 1.);
    mptXenon->AddConstProperty("ALPHASCINTILLATIONYIELD2", 0.);

    mptXenon->AddProperty("IONSCINTILLATIONYIELD", scint_e, scint_ion); // include QE 20%
    mptXenon->AddConstProperty("IONSCINTILLATIONYIELD1", 1.);
    mptXenon->AddConstProperty("IONSCINTILLATIONYIELD2", 0.);

    mptXenon->AddConstProperty("RESOLUTIONSCALE",1.0);
    mptXenon->AddConstProperty("SCINTILLATIONTIMECONSTANT1",20.*ns);
    mptXenon->AddConstProperty("SCINTILLATIONTIMECONSTANT2",45.*ns);



    liquidXenon->SetMaterialPropertiesTable(mptXenon);

    return liquidXenon;

}

G4Material* DetectorConstruction::CreateGasXenon() {
    G4Element* elementXe = new G4Element( "Xenon", "Xe", 54., 131.29*g/mole );
    G4Material* GXe = new G4Material
     ("GXe", 0.005887*g/cm3, 1, kStateGas, 173.15*kelvin, 1.5*atmosphere );
    GXe->AddElement( elementXe, 1);

    std::vector<G4double> GXe_PP = { 7.0*eV, 7.07*eV, 7.14*eV };
  std::vector<G4double> GXe_SCINT = { 0.1, 1.0, 0.1 };
  std::vector<G4double> GXe_RIND  = { 1.00, 1.00, 1.00 };
  std::vector<G4double> GXe_ABSL  = { 100*m, 100*m, 100*m}; //atten length
  std::vector<G4double> GXe_scint_e = { 0.*MeV, 10.*MeV };
  std::vector<G4double> GXe_scint_default = { 0., 120000.};
  std::vector<G4double> GXe_scint_alpha = { 0., 132000.};
  std::vector<G4double> GXe_scint_ion = { 0., 24000.};
  std::vector<G4double> LXe_scint_e = { 0.*MeV, 10.*MeV };
  std::vector<G4double> LXe_scint_ion = { 0., 24000.};
  G4MaterialPropertiesTable *GXe_mt = new G4MaterialPropertiesTable();
  GXe_mt->AddProperty("SCINTILLATIONCOMPONENT1", GXe_PP, GXe_SCINT);
  GXe_mt->AddProperty("SCINTILLATIONCOMPONENT2", GXe_PP, GXe_SCINT);
  GXe_mt->AddProperty("RINDEX",        GXe_PP, GXe_RIND);
  GXe_mt->AddProperty("ABSLENGTH",     GXe_PP, GXe_ABSL);
  GXe_mt->AddConstProperty("SCINTILLATIONYIELD",12000./MeV); // include QE 20%

  GXe_mt->AddProperty("ELECTRONSCINTILLATIONYIELD", GXe_scint_e, GXe_scint_default); // include QE 20%
  GXe_mt->AddConstProperty("ELECTRONSCINTILLATIONYIELD1", 0.);
  GXe_mt->AddConstProperty("ELECTRONSCINTILLATIONYIELD2", 1.);

  GXe_mt->AddProperty("ALPHASCINTILLATIONYIELD", GXe_scint_e, GXe_scint_alpha); // include QE 20%
  GXe_mt->AddConstProperty("ALPHASCINTILLATIONYIELD1", 1.);
  GXe_mt->AddConstProperty("ALPHASCINTILLATIONYIELD2", 0.);

  GXe_mt->AddProperty("IONSCINTILLATIONYIELD", LXe_scint_e, LXe_scint_ion); // include QE 20%
  GXe_mt->AddConstProperty("IONSCINTILLATIONYIELD1", 1.);
  GXe_mt->AddConstProperty("IONSCINTILLATIONYIELD2", 0.);

  GXe_mt->AddConstProperty("RESOLUTIONSCALE",1.0);
  GXe_mt->AddConstProperty("SCINTILLATIONTIMECONSTANT1",20.*ns);
  GXe_mt->AddConstProperty("SCINTILLATIONTIMECONSTANT2",45.*ns);
  GXe->SetMaterialPropertiesTable(GXe_mt);

return GXe;
}


G4Material* DetectorConstruction::CreateStainlessSteel() {
    G4NistManager* nistManager = G4NistManager::Instance();
    G4Material* stainlessSteel = nistManager->FindOrBuildMaterial("G4_STAINLESS-STEEL");

    // Optional: Definieren Sie eine optische Oberfläche für Edelstahl
    G4OpticalSurface* reflectiveSurface = new G4OpticalSurface("StainlessSteelSurface");
    reflectiveSurface->SetType(dielectric_metal);
    reflectiveSurface->SetFinish(ground);
    reflectiveSurface->SetModel(unified);  // Glisur model for polished surfaces

    G4double reflectivity[] = {0.8, 0.8, 0.8};  // 80% Reflexion
    G4double energy[] = {7.0*eV, 7.07*eV,7.14*eV};  // Beispielenergie

    G4MaterialPropertiesTable* mptReflective = new G4MaterialPropertiesTable();
    mptReflective->AddProperty("REFLECTIVITY", energy, reflectivity, 1);
    reflectiveSurface->SetMaterialPropertiesTable(mptReflective);

    return stainlessSteel;
}
 
G4Material* DetectorConstruction::CreateTeflon() {
    G4NistManager* nistManager = G4NistManager::Instance();
    G4Material* teflon = nistManager->FindOrBuildMaterial("G4_TEFLON");

    G4OpticalSurface* reflectiveSurface = new G4OpticalSurface("TeflonSurface");
    reflectiveSurface->SetType(dielectric_dielectric);
    reflectiveSurface->SetFinish(ground);
    reflectiveSurface->SetModel(unified);

    // Energiewerte und Reflexionswerte für Photonen
    G4double photonEnergies[] = {7.0*eV, 7.07*eV, 7.14*eV};
    G4double reflectivity[] = {0.99, 0.99, 0.99};  // Hohe Reflexion für Teflon

    G4MaterialPropertiesTable* mptReflective = new G4MaterialPropertiesTable();
    mptReflective->AddProperty("REFLECTIVITY", photonEnergies, reflectivity, 3);
    reflectiveSurface->SetMaterialPropertiesTable(mptReflective);

    return teflon;
}




G4OpticalSurface* DetectorConstruction::CreateMirrorSurface() {
    G4OpticalSurface* surface = new G4OpticalSurface("MirrorSurface");
    surface->SetType(dielectric_metal);
    surface->SetFinish(polished);
    surface->SetModel(glisur);
    return surface;
}

G4VPhysicalVolume* DetectorConstruction::Construct() {
    // Erhalten Sie den NIST Material Manager
    G4NistManager* nist = G4NistManager::Instance();

    // define Material
//    G4Material* air = nist->FindOrBuildMaterial("G4_Xe");
    G4Material* air = CreateGasXenon();
//    G4Material* steel = nist->FindOrBuildMaterial("G4_STAINLESS-STEEL");
    G4Material* steel = CreateStainlessSteel();
    G4Material* nai = nist->FindOrBuildMaterial("G4_SODIUM_IODIDE");
    G4Material* blackPlastic = nist->FindOrBuildMaterial("G4_POLYETHYLENE");
    G4Material* lxenon = CreateLiquidXenon();
    G4Material* teflon = CreateTeflon();

// Optische Eigenschaften für schwarzes Plastik
    G4double energy[] = {2.0*eV, 3.0*eV};  // Energie der Photonen
    G4double absorption[] = {0.1*mm, 0.1*mm};  // Sehr kurze Absorptionslänge

    G4MaterialPropertiesTable* mpt = new G4MaterialPropertiesTable();
    mpt->AddProperty("ABSLENGTH", energy, absorption, 2);
    blackPlastic->SetMaterialPropertiesTable(mpt);
//    G4Element* elementXe = new G4Element( "Xenon", "Xe", 54., 131.29*g/mole );
//    G4Material* LXe = new G4Material
//     ("LXe", 3.02*g/cm3, 1, kStateLiquid, 173.15*kelvin, 1.3*atmosphere );
//    LXe->AddElement( elementXe, 1);



    // World
    G4double world_sizeXY = 22 * m;
    G4double world_sizeZ = 6 * m;
    G4Box* solidWorld = new G4Box("solidWorld", 0.5 * world_sizeXY, 0.5 * world_sizeXY, 0.5 * world_sizeZ);
    G4LogicalVolume* logicWorld = new G4LogicalVolume(solidWorld, air, "logicWorld");
    G4VPhysicalVolume* physWorld = new G4PVPlacement(0, G4ThreeVector(), logicWorld, "physWorld", 0, false, 0, true);
    logicWorld -> SetVisAttributes (G4VisAttributes::GetInvisible());

    // flat Cylinder of liquid Xenon
    G4double radius = 0.75 * m;
    G4double height = 0.05 * m;
    G4double teflonThickness= 5 * cm;
    G4Tubs* solidXenonCylinder = new G4Tubs("solidXenonCylinder", 0, radius - teflonThickness, height/2, 0, 360 * deg);
    G4LogicalVolume* logicXenonCylinder = new G4LogicalVolume(solidXenonCylinder, lxenon, "Xenon");
    //color Xenon blue
    G4VisAttributes* xenonVisAtt = new G4VisAttributes(G4Colour(0.0, 0.0, 1.0)); // Blau
    xenonVisAtt->SetVisibility(true);
    logicXenonCylinder->SetVisAttributes(xenonVisAtt);

    //TeflonRing
    G4double teflonheight = 10 * cm;
    G4Tubs* solidTeflonRing = new G4Tubs("solidTeflonRing", radius - teflonThickness, radius, teflonheight, 0, 360 * deg);
    G4LogicalVolume* logicTeflonRing = new G4LogicalVolume(solidTeflonRing, teflon, "TeflonRing");
    //color Teflon white
    G4VisAttributes* teflonVisAtt = new G4VisAttributes(G4Colour(1.0, 1.0, 1.0)); // white
    teflonVisAtt->SetVisibility(true);
    logicXenonCylinder->SetVisAttributes(teflonVisAtt);


   // Bathtub
    G4double steelThickness = 5 * mm;
    G4double steelheight = 0.2 *m;
    G4Tubs* solidSteelOuter = new G4Tubs("solidSteelOuter", radius, radius + steelThickness, 0.5 * steelheight + steelThickness, 0, 360 * deg);
    G4Tubs* solidSteelBottom = new G4Tubs("solidSteelBottom", 0, radius + steelThickness, steelThickness, 0, 360 * deg);
    G4ThreeVector posBottom(0, 0, 0 * m - 0.5 * steelheight - 0.5 * steelThickness);

    G4UnionSolid* solidSteelBathtub = new G4UnionSolid("solidSteelBathtub", solidSteelOuter, solidSteelBottom, 0, posBottom);
    G4LogicalVolume* Bathtub = new G4LogicalVolume(solidSteelBathtub, steel, "Bathtub");

    // Absorber behind Scorer
    G4double absWidth = 60 * cm;
    G4double absHeight = 1 * mm;
    G4Box* solidAbsorber = new G4Box("solidAbsorber", 0.5 * absWidth, 0.5 * absWidth, 0.5 * absHeight);
    G4LogicalVolume* logicAbsorber = new G4LogicalVolume(solidAbsorber, blackPlastic, "logicAbsorber");

    //Top Dome
    G4double domeradius = 1 * m;
    G4double domethickness = 5 * cm;
    G4Sphere* solidtopDome = new G4Sphere("solidtopDome", domeradius, domeradius + domethickness, 0, 360 * deg, 0, 90 * deg);
    G4LogicalVolume* logictopDome = new G4LogicalVolume(solidtopDome, steel, "topDome");

    // Rectangle1
    G4double rectWidth1 = 0.1 * m;
    G4double rectHeight1 = 0.25 * m;
    G4double rectThickness1 = 19 * mm;
    G4Box* solidRectangle1 = new G4Box("solidRectangle1", 0.5 * rectWidth1, 0.5 * rectHeight1, 0.5 * rectThickness1);
    G4LogicalVolume* logicRectangle1 = new G4LogicalVolume(solidRectangle1, nai, "logicRectangle1");

    // Rectangle2
    G4double rectWidth2 = 0.1 * m;
    G4double rectHeight2 = 0.1 * m;
    G4double rectThickness2 = 25 * mm;
    G4Box* solidRectangle2 = new G4Box("solidRectangle2", 0.5 * rectWidth2, 0.5 * rectHeight2, 0.5 * rectThickness2);
    G4LogicalVolume* logicRectangle2 = new G4LogicalVolume(solidRectangle2, nai, "logicRectangle2");

    //color Rectangel white
    G4VisAttributes* rectangleVisAtt = new G4VisAttributes(G4Colour(1.0, 1.0, 1.0)); // Weiß
    rectangleVisAtt->SetVisibility(true);
    logicRectangle1->SetVisAttributes(rectangleVisAtt);
    logicRectangle2->SetVisAttributes(rectangleVisAtt);

    // Placing
    G4VPhysicalVolume* physXenonCylinder = new G4PVPlacement(0, G4ThreeVector(0, 0, 0), logicXenonCylinder, "physXenonCylinder", logicWorld, false, 0, true);
    G4VPhysicalVolume* physTeflonRing = new G4PVPlacement(0, G4ThreeVector(0, 0, 0.5 *teflonheight), logicTeflonRing, "physTeflonRing", logicWorld, false, 0, true);
    G4VPhysicalVolume* physBathtub=new G4PVPlacement(0, G4ThreeVector(0, 0, 0.5 * steelheight - steelThickness -  height), Bathtub, "physBathtub", logicWorld, false, 0, true);
    G4VPhysicalVolume* phystopDome = new G4PVPlacement(0, G4ThreeVector(0,0,0), logictopDome, "phystopDome", logicWorld, false, 0, true);
    G4VPhysicalVolume* physAbsorber = new G4PVPlacement(0, G4ThreeVector(0,0,51 * cm), logicAbsorber, "physAbsorber", logicWorld, false, 0, true);
    new G4PVPlacement(0, G4ThreeVector(0, 75 * mm,-0.56 * m), logicRectangle1, "physRectangle1", logicWorld, false, 0, true);
    new G4PVPlacement(0, G4ThreeVector(0, 0,-0.56 * m - 0.717 * m), logicRectangle2, "physRectangle2", logicWorld, false, 1, true);

    //Making and Placing of Wires in Air
    G4double wireRadius = 0.15 * mm;
    G4double wireLength = 1.5 * m;
    G4Tubs* solidWire = new G4Tubs("SolidWire", 0., wireRadius, wireLength/2, 0., 360.*deg);
    G4LogicalVolume* logicWire = new G4LogicalVolume(solidWire, steel, "LogicWire"); 
    G4RotationMatrix* rotm = new G4RotationMatrix();
    rotm->rotateY(90.*deg);  // Turns wires 90deg around xAxis

    G4double wireSpacing = 1.0 * cm;  // Abstand zwischen den Drähten
    G4double initialPositionY = -radius;  // Position 5 mm über dem Zylinder 
    G4int numberOfWires = 150;  // Anzahl der Drähte, passen Sie dies an Ihre Bedürfnisse an

    for (int i = 0; i < numberOfWires; ++i) {
      G4double posY = initialPositionY + i * wireSpacing;
      G4ThreeVector wirePosition(0, posY, height/2 + 5 * mm);  // Positionierung entlang der y-Achse
      new G4PVPlacement(rotm, wirePosition, logicWire, "WirePhysical", logicWorld, false, i, false);
    }

    //and in Xenon
    for (int i = 0; i < numberOfWires; ++i) {
      G4double posY = initialPositionY + 5 * mm + i * wireSpacing;
      G4ThreeVector wirePosition(0, posY, height/2 - 5 * mm);  // Positionierung entlang der y-Achse
      new G4PVPlacement(rotm, wirePosition, logicWire, "WirePhysical", logicWorld, false, i, false);
    }




  // Definition der spiegelnden Oberfläche
    //G4OpticalSurface* mirrorSurface = CreateMirrorSurface();
    //new G4LogicalBorderSurface("MirrorSurface", physWorld, physBathtub, mirrorSurface);

    return physWorld;}

}
