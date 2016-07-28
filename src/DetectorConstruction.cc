#include "DetectorConstruction.hh"

#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"
#include "G4NistManager.hh"

DetectorConstruction::DetectorConstruction() {}

DetectorConstruction::~DetectorConstruction() {}

// Mandatory implementation of Construct() method
G4VPhysicalVolume *DetectorConstruction::Construct() {
	DefineMaterials();
	return ConstructDetector();
}

void DetectorConstruction::DefineMaterials() {
	G4NistManager* man = G4NistManager::Instance();
  man->SetVerbose(1);

  // define elements
  C  = man->FindOrBuildMaterial("C");
  Pb = man->FindOrBuildMaterial("Pb");

  // define pure NIST materials
  Al = man->FindOrBuildMaterial("G4_Al");
  Cu = man->FindOrBuildMaterial("G4_Cu");

  // define NIST materials
  H2O  = man->FindOrBuildMaterial("G4_WATER");
  Sci  = man->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE");
  SiO2 = man->FindOrBuildMaterial("G4_SILICON_DIOXIDE");
  Air  = man->FindOrBuildMaterial("G4_AIR");

  // HEP materials
  PbWO4  = man->FindOrBuildMaterial("G4_PbWO4");
  lAr    = man->FindOrBuildMaterial("G4_lAr");
  vac    = man->FindOrBuildMaterial("G4_Galactic");

  // define gas material at non STP conditions (T = 120K, P=0.5atm)
  coldAr = man->ConstructNewGasMaterial("ColdAr","G4_Ar",120.*kelvin,0.5*atmosphere);

  // print the table of materials
  G4cout << *(G4Material::GetMaterialTable()) << G4endl;
}

G4VPhysicalVolume *DetectorConstruction::ConstructDetector() {
	// WORLD volume
	WorldSizeX = 100*cm;
	WorldSizeY = 100*cm;
	WorldSizeZ = 100*cm;
	solidWorld = new G4Box("World", WorldSizeX/2, WorldSizeY/2, WorldSizeZ/2);
	logicWorld = new G4LogicalVolume(solidWorld, vac, "World");
	physiWorld = new G4PVPlacement(0, G4ThreeVector(), "World", logicWorld, NULL, false, 0);

	// Liquid Argon target volume
	TargetSizeX = 20*cm;
	TargetSizeY = 20*cm;
	TargetSizeZ = 20*cm;
	solidTarget = new G4Box("Target", TargetSizeX/2, TargetSizeY/2, TargetSizeZ/2);
	logicTarget = new G4LogicalVolume(solidTarget, PbWO4, "Target");
	physiTarget = new G4PVPlacement(0, G4ThreeVector(0, 0, 0), "Target", logicTarget, physiWorld, false, 0);

	// Visualization attributes

	G4VisAttributes *worldVisAtt = new G4VisAttributes(G4Colour());
	worldVisAtt->SetForceWireframe(true);
	worldVisAtt->SetVisibility(true);
	logicWorld->SetVisAttributes(worldVisAtt);

	G4VisAttributes *targetVisAtt = new G4VisAttributes(G4Colour(0., 1., 0.));
	targetVisAtt->SetForceSolid(false);
	targetVisAtt->SetVisibility(true);
	targetVisAtt->SetForceWireframe(true);
	logicTarget->SetVisAttributes(targetVisAtt);

	return physiWorld;
}
