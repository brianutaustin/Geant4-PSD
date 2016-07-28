#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4Material.hh"

#include "G4PVPlacement.hh"
#include "G4VisAttributes.hh"

// Derive the user-defined class from the G4VUserDetectorConstruction class
class DetectorConstruction : public G4VUserDetectorConstruction {
public:
	DetectorConstruction();
	virtual ~DetectorConstruction();

public:
	G4VPhysicalVolume *Construct();

private:
	G4VPhysicalVolume *ConstructDetector();
	void DefineMaterials();

	// Private members
		// Detector's volumes
		G4Box *solidWorld;
		G4LogicalVolume *logicWorld;
		G4VPhysicalVolume *physiWorld;

		G4Box *solidTarget;
		G4LogicalVolume *logicTarget;
		G4VPhysicalVolume *physiTarget;

		// Detector's volumes' sizes
		G4double WorldSizeX;
		G4double WorldSizeY;
		G4double WorldSizeZ;
		G4double TargetSizeX;
		G4double TargetSizeY;
		G4double TargetSizeZ;

	// Materials
	G4Material* C;
	G4Material* Pb;
	G4Material* Al;
	G4Material* Cu;
	G4Material* H2O;
	G4Material* Sci;
	G4Material* SiO2;
	G4Material* Air;
	G4Material* PbWO4;
	G4Material* lAr;
	G4Material* vac;
	G4Material* coldAr;
};

#endif
