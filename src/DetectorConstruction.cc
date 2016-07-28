#include "DetectorConstruction.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"

DetectorConstruction::DetectorConstruction() {}

DetectorConstruction::~DetectorConstruction() {}

// Mandatory implementation of Construct() method
G4VPhysicalVolume *DetectorConstruction::Construct() {
	DefineMaterials();
	return ConstructDetector();
}

void DetectorConstruction::DefineMaterials() {
	G4String name;
	G4double density;
	G4double z, a;

	// Liquid Argon
	density = 1.390*g/cm3;
	a = 39.95*g/mole;
	G4Material *lAr = new G4Material(name = "liquidArgon", z = 18., a, density);

	// Vacuum standard definition
	density = universe_mean_density;
	G4Material *vacuum = new G4Material(name = "Vacuum", z = 1., a = 1.01*g/mole, density);

	// Display list of defined materials
	G4cout << G4endl << *(G4Material::GetMaterialTable()) << G4endl;

	// Default materials in setup
	LiquidArgonMaterial = lAr;
	VacuumMaterial = vacuum;
}

G4VPhysicalVolume *DetectorConstruction::ConstructDetector() {
	// WORLD volume
	WorldSizeX = 100*cm;
	WorldSizeY = 100*cm;
	WorldSizeZ = 100*cm;
	solidWorld = new G4Box("World", WorldSizeX/2, WorldSizeY/2, WorldSizeZ/2);
	logicWorld = new G4LogicalVolume(solidWorld, VacuumMaterial, "World");
	physiWorld = new G4PVPlacement(0, G4ThreeVector(), "World", logicWorld, NULL, false, 0);

	// Liquid Argon target volume
	TargetSizeX = 20*cm;
	TargetSizeY = 20*cm;
	TargetSizeZ = 20*cm;
	solidTarget = new G4Box("Target", TargetSizeX/2, TargetSizeY/2, TargetSizeZ/2);
	logicTarget = new G4LogicalVolume(solidTarget, LiquidArgonMaterial, "Target");
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
