#include "StackingAction.hh"
StackingAction::StackingAction(DataManager* data){
  // store the pointer to the data class locally, in order to be able to acess all information later
  fdata = data;
}
StackingAction::~StackingAction() {}
G4ClassificationOfNewTrack
StackingAction::ClassifyNewTrack(const G4Track * aTrack){

  // if(aTrack->GetParentID()>=0){
  //   cout << "ParentID " << aTrack->GetParentID();
  //   if(aTrack->GetVolume())
  //     cout << ", volume " << aTrack->GetVolume()->GetName();
  //   cout << ", particleType " << aTrack->GetDefinition()->GetParticleName();
  //   if(aTrack->GetParentID()>0)
  //     cout << ", track process " << aTrack->GetCreatorProcess()->GetProcessName() << endl;
  //   else
  //     cout << endl;
  // }
  //count scintillation photons
  if(aTrack->GetDefinition() == G4OpticalPhoton::OpticalPhotonDefinition()){ // particle is optical photon
    if(aTrack->GetParentID()>0 && aTrack->GetVolume()->GetName() == "detector_phys" && aTrack->GetCreatorProcess()->GetProcessName() == "Scintillation"){// particle is secondary, in the crystal, created by scintillator
      fdata->AddCreatedPhoton();
    }
  }
  return fUrgent;
}
void StackingAction::NewStage(){
}
void StackingAction::PrepareNewEvent(){
}
