#include "PhysicsList.hh"

#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"
#include "G4StepLimiter.hh"
#include "G4UnitsTable.hh"

#include "G4EmStandardPhysics.hh"
#include "G4EmExtraPhysics.hh"
#include "G4DecayPhysics.hh"
#include "G4HadronElasticPhysicsXS.hh"
#include "G4IonBinaryCascadePhysics.hh"
#include "G4HadronInelasticQBBC.hh"
#include "G4NeutronTrackingCut.hh"

PhysicsList::PhysicsList() : G4VModularPhysicsList() {

  
}

PhysicsList::~PhysicsList() {}
