/***********************************************************************
 *
 *    sensitive detector for detector read-out of the scintillator
 *
 ***********************************************************************/

#include "ScintSD.hh"

using namespace std;
ScintSD::ScintSD(G4String iname)
  : G4VSensitiveDetector(iname)
{
  collectionName.insert(iname);
}

ScintSD::~ScintSD(){;}

void ScintSD::Initialize(G4HCofThisEvent* evnt){
  
  //cout << __PRETTY_FUNCTION__ << "\t" << SensitiveDetectorName <<"\t";
  static G4int HCID;
  HCID = G4SDManager::GetSDMpointer()->GetCollectionID(SensitiveDetectorName);
  //cout << "HCID " << HCID << endl;
  ScinthitsCollection = new ScintHitsCollection(SensitiveDetectorName,SensitiveDetectorName);

  evnt->AddHitsCollection(HCID, ScinthitsCollection);
  //cout << "added " << endl;
}

G4bool ScintSD::ProcessHits(G4Step* aStep, G4TouchableHistory*){
  //cout << __PRETTY_FUNCTION__ << endl;

  G4SDManager* SDman = G4SDManager::GetSDMpointer();


  G4double edep = aStep->GetTotalEnergyDeposit();
  //cout << "edep " << edep << endl;
  if(edep==0)
    return false;
  //cout << "edep " << edep << endl;
  ScintHit* newHit = new ScintHit();

  newHit->SetTrackID(aStep->GetTrack()->GetTrackID());
  newHit->SetParentID(aStep->GetTrack()->GetParentID());
  newHit->SetEdep(edep);

  G4StepPoint* stepPoint;
  if(aStep->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName()=="Transportation")
    stepPoint = aStep->GetPreStepPoint();
  else
    stepPoint = aStep->GetPostStepPoint();

  G4ThreeVector position = stepPoint->GetPosition();
  
  newHit->SetPos(position);
  
  G4TouchableHandle theTouchable = stepPoint->GetTouchableHandle();

  G4ThreeVector det_position = theTouchable->GetHistory()->GetTopTransform().TransformPoint(position);
  newHit->SetPosInDet(det_position);

  //check which HitCollectionID this is
  //cout << "checking collection id entries " <<ScinthitsCollection->entries() << endl;
  int CollectionID = SDman->GetCollectionID(ScinthitsCollection);
  //cout << "collection id " << CollectionID << endl;
  
  newHit->SetID(CollectionID);
 
  //cout<<"CollectionID = "<<CollectionID<<endl;


  newHit->SetTrack(aStep->GetTrack());
  newHit->SetProcName(aStep->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName());
  newHit->SetStep(aStep->GetTrack()->GetCurrentStepNumber());
  
  if( aStep->GetTrack()->GetNextVolume() != 0 ) 
    { 
      newHit->SetVolume(aStep->GetTrack()->GetVolume()->GetName());
    } 
  else 
    {
      newHit->SetVolume("OutOfWorld");
    }

  ScinthitsCollection->insert(newHit);
  

  return true;
}

void ScintSD::EndOfEvent(G4HCofThisEvent*)
{;}







