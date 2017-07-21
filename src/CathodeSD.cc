/***********************************************************************
 *
 *    sensitive detector for detector read-out of the scintillator
 *
 ***********************************************************************/

#include "CathodeSD.hh"

using namespace std;
CathodeSD::CathodeSD(G4String iname)
  : G4VSensitiveDetector(iname)
{
  collectionName.insert(iname);
}

CathodeSD::~CathodeSD(){;}

void CathodeSD::Initialize(G4HCofThisEvent* evnt){
  
  //cout << __PRETTY_FUNCTION__ << "\t" << SensitiveDetectorName <<"\t";
  static G4int HCID;
  HCID = G4SDManager::GetSDMpointer()->GetCollectionID(SensitiveDetectorName);
  //cout << "HCID " << HCID << endl;
  CathodehitsCollection = new CathodeHitsCollection(SensitiveDetectorName,SensitiveDetectorName);

  evnt->AddHitsCollection(HCID, CathodehitsCollection);
  //cout << "added " << endl;
}
G4bool CathodeSD::ProcessHits(G4Step* aStep, G4TouchableHistory*){
  if(aStep->GetTrack()->GetDefinition() != G4OpticalPhoton::OpticalPhotonDefinition())
    return false;
  return false;
}
G4bool CathodeSD::ProcessSteps(const G4Step* aStep, G4TouchableHistory*){
  //cout << __PRETTY_FUNCTION__ << endl;

  G4SDManager* SDman = G4SDManager::GetSDMpointer();
  //cout << aStep->GetTrack()->GetDefinition()->GetParticleName() << endl;
  if(aStep->GetTrack()->GetDefinition() != G4OpticalPhoton::OpticalPhotonDefinition())
    return false;

  //cout << "checking collection id entries " <<CathodehitsCollection->entries() << endl;
  int CollectionID = SDman->GetCollectionID(CathodehitsCollection);
  //cout << "collection id " << CollectionID << endl;
  
  CathodeHit* newHit = NULL;
  G4int n=CathodehitsCollection->entries();
  
  for(int i=0;i<n;i++){
    //cout << "(*CathodehitsCollection)[i]->GetID() " << (*CathodehitsCollection)[i]->GetID() << endl;
    if((*CathodehitsCollection)[i]->GetID()==CollectionID){
      //cout << "already hit " << endl;
      newHit = (*CathodehitsCollection)[i];
      break;
    }
  }
  if(newHit==NULL){
    newHit = new CathodeHit();
    CathodehitsCollection->insert(newHit);
    newHit->SetID(CollectionID);
  }
  newHit->AddPhoton();
  //cout << newHit->GetPhotonCount() << endl;

  
  return true;
}

void CathodeSD::EndOfEvent(G4HCofThisEvent*)
{;}







