#include "DetectorConstruction.hh"

#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"
#include "G4NistManager.hh"
#include "G4MaterialPropertiesTable.hh"

DetectorConstruction::DetectorConstruction() {}

DetectorConstruction::~DetectorConstruction() {}

// Mandatory implementation of Construct() method
G4VPhysicalVolume *DetectorConstruction::Construct() {
	DefineMaterials();
	G4cout << "------------------------" << G4endl;
	//ConstructScintillator();
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

void DetectorConstruction::ConstructScintillator() {
	const G4int NUMENTRIES = 9;
  G4double Scnt_PP[NUMENTRIES] = { 6.6*eV, 6.7*eV, 6.8*eV, 6.9*eV, 7.0*eV, 7.1*eV, 7.2*eV, 7.3*eV, 7.4*eV };
  G4double Scnt_FAST[NUMENTRIES] = { 0.000134, 0.004432, 0.053991, 0.241971, 0.398942, 0.000134, 0.004432, 0.053991, 0.241971 };
  G4double Scnt_SLOW[NUMENTRIES] = { 0.000010, 0.000020, 0.000030, 0.004000, 0.008000, 0.005000, 0.020000, 0.001000, 0.000010 };

  G4MaterialPropertiesTable *Scnt_MPT = new G4MaterialPropertiesTable();
  Scnt_MPT->AddProperty("FASTCOMPONENT", Scnt_PP, Scnt_FAST, NUMENTRIES);
  Scnt_MPT->AddProperty("SLOWCOMPONENT", Scnt_PP, Scnt_SLOW, NUMENTRIES);
  Scnt_MPT->AddConstProperty("SCINTILLATIONYIELD", 5000./MeV);
  Scnt_MPT->AddConstProperty("RESOLUTIONSCALE", 2.0);
  Scnt_MPT->AddConstProperty("FASTTIMECONSTANT",  1.*ns);
  Scnt_MPT->AddConstProperty("SLOWTIMECONSTANT", 10.*ns);
  Scnt_MPT->AddConstProperty("YIELDRATIO", 0.8);
  Scnt->SetMaterialPropertiesTable(Scnt_MPT);
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
	logicTarget = new G4LogicalVolume(solidTarget, Scnt, "Target");
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
