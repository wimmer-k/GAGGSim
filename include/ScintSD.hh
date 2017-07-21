/***********************************************************************
 *
 *    sensitive detector for detector read-out of GAGG
 *
 ***********************************************************************/

#ifndef ScintSD_h
#define ScintSD_h 1

#include "G4VSensitiveDetector.hh"

#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"
#include "G4UnitsTable.hh"
#include "G4VProcess.hh"

#include <string>
#include <iostream>
#include <iomanip>

#include "DetectorConstruction.hh"
#include "ScintHit.hh"

class G4Step;
class G4HCofThisEvent;

class ScintSD : public G4VSensitiveDetector
{

public:
  ScintSD(G4String);
  ~ScintSD();
  
  void Initialize(G4HCofThisEvent*);
  G4bool ProcessHits(G4Step*, G4TouchableHistory*);
  void EndOfEvent(G4HCofThisEvent*);
  
private:
  ScintHitsCollection* ScinthitsCollection;
  G4String name;
};

#endif

