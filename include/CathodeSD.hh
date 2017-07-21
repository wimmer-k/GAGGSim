/***********************************************************************
 *
 *    sensitive detector for detector read-out of GAGG
 *
 ***********************************************************************/

#ifndef CathodeSD_h
#define CathodeSD_h 1

#include "G4VSensitiveDetector.hh"

#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"
#include "G4UnitsTable.hh"
#include "G4VProcess.hh"
#include "G4ParticleTypes.hh"
#include "G4ParticleDefinition.hh"

#include <string>
#include <iostream>
#include <iomanip>

#include "DetectorConstruction.hh"
#include "CathodeHit.hh"

class G4Step;
class G4HCofThisEvent;

class CathodeSD : public G4VSensitiveDetector
{

public:
  CathodeSD(G4String);
  ~CathodeSD();
  
  void Initialize(G4HCofThisEvent*);
  G4bool ProcessHits(G4Step*, G4TouchableHistory*);
  G4bool ProcessSteps(const G4Step* aStep, G4TouchableHistory*);
  void EndOfEvent(G4HCofThisEvent*);
  
private:
  CathodeHitsCollection* CathodehitsCollection;
  G4String name;
};

#endif

