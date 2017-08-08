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
  fScintCollID = -1;
  fCathodeCollID = -1;
}
EventAction::~EventAction(){
}
void EventAction::BeginOfEventAction(const G4Event*){
  //cout << __PRETTY_FUNCTION__  << endl;
  G4SDManager* SDman = G4SDManager::GetSDMpointer();
  if(fScintCollID<0)
    fScintCollID=SDman->GetCollectionID("scint");
  if(fCathodeCollID<0)
    fCathodeCollID=SDman->GetCollectionID("cathode");
  //cout << "collection ids: scint " << fScintCollID <<", cathode " << fCathodeCollID << endl;

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


  ScintHitsCollection* scintHC = NULL;
  CathodeHitsCollection* cathodeHC = NULL;

  // get the hits collection (HC) of the current event
  G4HCofThisEvent * HCE = evt->GetHCofThisEvent();
  //Get the hit collections
  if(HCE){
    if(fScintCollID>=0)
      scintHC = (ScintHitsCollection*)(HCE->GetHC(fScintCollID));
    if(fCathodeCollID>=0)
      cathodeHC = (CathodeHitsCollection*)(HCE->GetHC(fCathodeCollID));
  }
  // temporary storage for the deposited energy, and number of photons
  G4double en = 0;
  G4double firsten = 0;
  G4double maxen = 0;
  G4double averageen = 0;
  TVector3 firstpos(sqrt(-1),sqrt(-1),sqrt(-1));
  TVector3 maxpos(sqrt(-1),sqrt(-1),sqrt(-1));
  TVector3 averagepos(0,0,0);
  
  G4int npho = 0;
  
  //Hits in scintillator
  if(scintHC){
    
    // loop over all the hits in this crystal
    for(int j=0;j<scintHC->entries();j++){
      //cout << (*scintHC)[j]->GetEdep()*MeV << "\t"<< (*scintHC)[j]->GetEdep()*keV << "\t"<< (*scintHC)[j]->GetEdep() << endl;
      //(*scintHC)[j]->Print();
      double edep = (*scintHC)[j]->GetEdep()*1000;
      en += edep;
      averagepos += TVector3((*scintHC)[j]->GetPos().x(),(*scintHC)[j]->GetPos().y(),(*scintHC)[j]->GetPos().z());
      if((*scintHC)[j]->GetTrackID() == 1){//first hit
	firstpos.SetXYZ((*scintHC)[j]->GetPos().x(),(*scintHC)[j]->GetPos().y(),(*scintHC)[j]->GetPos().z());
	firsten = edep;
      }
      if(edep>maxen){//highest hit
	maxpos.SetXYZ((*scintHC)[j]->GetPos().x(),(*scintHC)[j]->GetPos().y(),(*scintHC)[j]->GetPos().z());
	maxen = edep;
      }
      
    }//loop over all hits
    //calculate average position
    averagepos *= 1./scintHC->entries();
    averageen = en/scintHC->entries();
  }
  
  //hits in cathode
  if(cathodeHC){
    if(cathodeHC->entries()>1){
      cout << "cathodeHC->entries() " << cathodeHC->entries() << endl;
      cout << "should be only one for one cathode!" << endl;
    }
    for(int j=0;j<cathodeHC->entries();j++){
      npho += (*cathodeHC)[j]->GetPhotonCount();
      //thresholds
    }
  }

  fdata->SetMaxHit(maxen,maxpos);
  fdata->SetFirstHit(firsten,firstpos);
  fdata->SetAverageHit(averageen,averagepos);
  // fill the tree in the datamanager object, this saves the event to the ouput file
  fdata->FillTree(en,npho);


  //status output:
  // get current event number
  G4int event_id = evt->GetEventID();
  //cout << " ^^^^ " << event_id << endl;
  // output every 100 events
  if(event_id%100 ==0){ 
    cout << event_id <<"/"<<fdata->GetNevents() << " done..." << endl;
  }
  

  //cout << __PRETTY_FUNCTION__  << endl;
}
