#include "EventAction.hh"
#include "RunAction.hh"

#include "G4Event.hh"

EventAction::EventAction(RunAction*) {}

EventAction::~EventAction() {}

void EventAction::BeginOfEventAction(const G4Event*) {}

void EventAction::EndOfEventAction(const G4Event*) {}
