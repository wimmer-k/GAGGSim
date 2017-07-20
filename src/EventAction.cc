/*************************************************************************
 * 
 *  fill histogramms at the end of an event
 * 
 *************************************************************************/

#include "EventAction.hh"

using namespace std;
using namespace CLHEP;

EventAction::EventAction(DataManager* data){
  // store the pointer to the data class locally, in order to be able to acess all information later
  fdata = data;
  fDrawOptical = -1;
}
EventAction::~EventAction(){
}
void EventAction::BeginOfEventAction(const G4Event*){
  //cout << __PRETTY_FUNCTION__  << endl;
}
void EventAction::EndOfEventAction(const G4Event* evt){
  //cout << __PRETTY_FUNCTION__  << endl;
  //draw trajectories
  G4TrajectoryContainer* trajectoryContainer = evt->GetTrajectoryContainer();
 
  G4int n_trajectories = 0;
  if(trajectoryContainer)
    n_trajectories = trajectoryContainer->entries();
  // extract the trajectories and draw them
  if(G4VVisManager::GetConcreteInstance()){
    for(G4int i=0; i<n_trajectories; i++){
      Trajectory* trj = (Trajectory*)((*(evt->GetTrajectoryContainer()))[i]);
      if(trj->GetParticleName()=="opticalphoton"){
  	if(fDrawOptical==-1)
  	  continue;
  	if(fDrawOptical==0)
  	  trj->DrawATrajectory();
  	else if(fDrawOptical> 0 && i%fDrawOptical==0)
  	  trj->DrawATrajectory();
      }
      else
  	trj->DrawATrajectory();
    }
  }


  
  // temporary storage for all the energies
  G4double en =0;
  
  // get the hits collection (HC) of the current event
  G4HCofThisEvent * HCE = evt->GetHCofThisEvent();

  // get all hits in this current crystal
  HitsCollection* collection = (HitsCollection*)(HCE->GetHC(0));
    
  // loop over all the hits in this crystal
  for(int j=0;j<collection->entries();j++){
    // add the energy to the energy of the current cyrstal (en[i]) and the total energy (etot)
    //cout << (*collection)[j]->GetEdep()*MeV << "\t"<< (*collection)[j]->GetEdep()*keV << "\t"<< (*collection)[j]->GetEdep() << endl;
    en += (*collection)[j]->GetEdep()*1000;
  }//loop over all hits


  // fill the tree in the datamanager object, this saves the event to the ouput file
  fdata->FillTree(en);


  //status output:
  // get current event number
  G4int event_id = evt->GetEventID();
  //cout << " ^^^^ " << event_id << endl;
  // output every 10000 events
  if(event_id%10000 ==0){ 
    cout << event_id <<"/"<<fdata->GetNevents() << " done..." << endl;
  }
  

  cout << __PRETTY_FUNCTION__  << endl;
}
