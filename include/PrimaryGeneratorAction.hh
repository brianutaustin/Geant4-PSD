#ifndef PrimaryGeneratorAction_h
#define PrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "DetectorConstruction.hh"
#include "G4Event.hh"
#include "G4ParticleTable.hh"

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction {
public:
	PrimaryGeneratorAction(DetectorConstruction*);
	~PrimaryGeneratorAction();

public:
	void GeneratePrimaries(G4Event*);

private:
	DetectorConstruction *Detector;
	G4ParticleGun *particleGun;
};

#endif
