#ifndef PhysicsList_h
#define PhysicsList_h 1

#include "G4VModularPhysicsList.hh"
#include "G4ProcessManager.hh"
#include "G4ParticleTypes.hh"

class PhysicsList : public G4VModularPhysicsList {
public:
	PhysicsList();
	virtual ~PhysicsList();
};

#endif
