#ifndef EventAction_h
#define EventAction_h 1

#include "G4UserEventAction.hh"

class RunAction;

class EventAction : public G4UserEventAction {
public:
	EventAction(RunAction*);
   ~EventAction();

   void BeginOfEventAction(const G4Event*);
   void EndOfEventAction(const G4Event*);
};

#endif
