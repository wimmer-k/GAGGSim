#ifndef StackingAction_H
#define StackingAction_H 1
#include <string>
#include <iostream>
#include <iomanip>

#include "globals.hh"
#include "G4UserStackingAction.hh"
#include "G4Track.hh"
#include "G4ProcessManager.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"

#include "DataManager.hh"

using namespace std;

class StackingAction : public G4UserStackingAction{
public:
  
  StackingAction(DataManager* data);
  virtual ~StackingAction();
 
  G4ClassificationOfNewTrack ClassifyNewTrack(const G4Track* aTrack);
  void NewStage();
  void PrepareNewEvent();
  
private:
  DataManager* fdata;
};

#endif
