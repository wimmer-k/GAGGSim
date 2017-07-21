#ifndef DetectorConstruction_H
#define DetectorConstruction_H 1
class G4LogicalVolume;
class G4VPhysicalVolume;

#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4SDManager.hh"
#include "G4Material.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Cons.hh"
#include "G4Polycone.hh"
#include "G4UnionSolid.hh"
#include "G4SubtractionSolid.hh"
#include "G4LogicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4PVPlacement.hh"
#include "G4UIcommand.hh"
#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"
#include "G4LogicalSkinSurface.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4OpticalSurface.hh"

#include "ScintSD.hh"
#include "CathodeSD.hh"
#include "Settings.hh"

#include <iostream>
#include <fstream>
#include <string.h>
#include <iomanip>
#include <string>
#include <vector>
#include <stdlib.h>

#include "defines.h"

using namespace std;

class DetectorConstruction : public G4VUserDetectorConstruction{
public:

  DetectorConstruction();
  DetectorConstruction(Settings* set){
    fset= set;
  };
  ~DetectorConstruction();
  void DefineMaterials();
  void DefineMaterialProperties();
  G4VPhysicalVolume* Construct();

private:
  Settings* fset;

  G4Material* fAir;
  G4Material* fVacuum;
  G4Material* fGlass;
  G4Material* fCathode;
  G4Material* fScint;
  G4OpticalSurface* fCathodeSurf;
  
  G4MaterialPropertiesTable* fScintTable;
  G4MaterialPropertiesTable* fCathodeTable;
  G4MaterialPropertiesTable* fGlassTable;
  G4MaterialPropertiesTable* fAirTable;
  
  
};

#endif

