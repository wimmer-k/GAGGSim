#include "DetectorConstruction.hh"

using namespace std;

DetectorConstruction::DetectorConstruction(){
}

DetectorConstruction::~DetectorConstruction(){
}

void DetectorConstruction::DefineMaterials(){
  G4NistManager* NistManager = G4NistManager::Instance();
  // elements and materials
  G4double density;

  //air
  density = 1.290*mg/cm3;
  G4Element* O  = NistManager->FindOrBuildElement("O");
  G4Element* N  = NistManager->FindOrBuildElement("N");
  fAir = new G4Material("Air", density, 2);
  fAir->AddElement(N, 0.7);
  fAir->AddElement(O, 0.3);
  density = 1.225e-7*mg/cm3; 
  G4double pressure    = 1.e-7*bar;
  G4double temperature = STP_Temperature + 20*kelvin;
  fVacuum = new G4Material("Vacuum", density, 1,kStateGas, temperature, pressure);
  fVacuum->AddMaterial(fAir, 1.); 

  //Scintillator
  //hardcoded GAGG
  density = 6.63 *g/cm3;
  G4Element* Gd = NistManager->FindOrBuildElement("Gd");
  G4Element* Ga = NistManager->FindOrBuildElement("Ga");
  G4Element* Al = NistManager->FindOrBuildElement("Al");
  fScint = new G4Material("Scint", density, 4);
  fScint->AddElement(Gd, 0.15);
  fScint->AddElement(Al, 0.1);
  fScint->AddElement(Ga, 0.15);
  fScint->AddElement(O, 0.6);

  //Glass: SiO2 + B2O3
  density=2.23*g/cm3;
  G4Element* Si = NistManager->FindOrBuildElement("Si");
  G4Element* B = NistManager->FindOrBuildElement("B");
  fGlass = new G4Material("Glass", density,3);
  fGlass->AddElement(Si,27.7*perCent);
  fGlass->AddElement(O,63.9*perCent);
  fGlass->AddElement(B,8.31*perCent);

  density = 26.982*g/cm3;
  fCathode = new G4Material("Cathode",density,1);
  fCathode->AddElement(Al,1);

  DefineMaterialProperties();
  fScint->SetMaterialPropertiesTable(fScintTable);
  fScint->GetIonisation()->SetBirksConstant(fset->ScintBirksConstant());

  fGlass->SetMaterialPropertiesTable(fGlassTable);
  fAir->SetMaterialPropertiesTable(fAirTable);
  fVacuum->SetMaterialPropertiesTable(fAirTable);


  fCathodeSurf = new G4OpticalSurface("CathodeSurf",glisur,polished,dielectric_metal);
  fCathodeSurf->SetMaterialPropertiesTable(fCathodeTable);
}
void DetectorConstruction::DefineMaterialProperties(){
  fScintTable = new G4MaterialPropertiesTable();
    
  ifstream scintlightyield;
  scintlightyield.open(fset->ScintLightYieldFile());
  if(!scintlightyield.is_open())
    cout << "error" << endl;
  G4int Nscintlightyield = 0;
  scintlightyield >> Nscintlightyield;
  scintlightyield.ignore(1000,'\n');
  scintlightyield.ignore(1000,'\n');
  G4double scintenergies[MAXENTRIES];
  G4double scintyields[MAXENTRIES];
  for(int i=0;i<Nscintlightyield;i++){
    scintlightyield >> scintenergies[i] >> scintyields[i];
    scintenergies[i]*=eV;
    scintlightyield.ignore(1000,'\n');
  }
  fScintTable->AddProperty("FASTCOMPONENT",scintenergies,scintyields,Nscintlightyield);

  ifstream scintrefraction;
  scintrefraction.open(fset->ScintRefractionFile());
  if(!scintrefraction.is_open())
    cout << "error" << endl;
  G4int Nscintrefraction = 0;
  scintrefraction >> Nscintrefraction;
  scintrefraction.ignore(1000,'\n');
  scintrefraction.ignore(1000,'\n');
  G4double scintRindex[MAXENTRIES];
  G4double scintabslength[MAXENTRIES];
  for(int i=0;i<Nscintrefraction;i++){
    scintrefraction >> scintenergies[i] >> scintRindex[i] >> scintabslength[i];
    scintenergies[i]*=eV;
    scintabslength[i]*=cm;
    scintrefraction.ignore(1000,'\n');
  }
  fScintTable->AddProperty("RINDEX",scintenergies, scintRindex,Nscintrefraction);
  fScintTable->AddProperty("ABSLENGTH",scintenergies,scintabslength,Nscintrefraction);
  
  fScintTable->AddConstProperty("SCINTILLATIONYIELD",fset->ScintLightYield()/keV); 
  fScintTable->AddConstProperty("RESOLUTIONSCALE",fset->ScintResolutionScale());
  if(fset->ScintFastTimeConstant()>0)
    fScintTable->AddConstProperty("FASTTIMECONSTANT",fset->ScintFastTimeConstant()*ns);
  if(fset->ScintSlowTimeConstant()>0)
    fScintTable->AddConstProperty("SLOWTIMECONSTANT",fset->ScintSlowTimeConstant()*ns); 
  if(fset->ScintFastScintillatorRiseTime()>0)
  fScintTable->AddConstProperty("FASTSCINTILLATIONRISETIME",fset->ScintFastScintillatorRiseTime()*ns);
  fScintTable->AddConstProperty("YIELDRATIO",fset->ScintYieldRatio());


  fGlassTable = new G4MaterialPropertiesTable();
  ifstream glassrefraction;
  glassrefraction.open(fset->GlassRefractionFile());
  if(!glassrefraction.is_open())
    cout << "error" << endl;
  G4int Nglassrefraction = 0;
  glassrefraction >> Nglassrefraction;
  glassrefraction.ignore(1000,'\n');
  glassrefraction.ignore(1000,'\n');
  G4double glassenergies[MAXENTRIES];
  G4double glassRindex[MAXENTRIES];
  G4double glassabslength[MAXENTRIES];
  for(int i=0;i<Nglassrefraction;i++){
    glassrefraction >> glassenergies[i] >> glassRindex[i] >> glassabslength[i];
    glassenergies[i]*=eV;
    glassabslength[i]*=cm;
    glassrefraction.ignore(1000,'\n');
  }
  fGlassTable->AddProperty("RINDEX",glassenergies, glassRindex,Nglassrefraction);
  fGlassTable->AddProperty("ABSLENGTH",glassenergies,glassabslength,Nglassrefraction);

  fAirTable = new G4MaterialPropertiesTable();
  ifstream airrefraction;
  airrefraction.open(fset->AirRefractionFile());
  if(!airrefraction.is_open())
    cout << "error" << endl;
  G4int Nairrefraction = 0;
  airrefraction >> Nairrefraction;
  airrefraction.ignore(1000,'\n');
  airrefraction.ignore(1000,'\n');
  G4double airenergies[MAXENTRIES];
  G4double airRindex[MAXENTRIES];
  for(int i=0;i<Nairrefraction;i++){
    airrefraction >> airenergies[i] >> airRindex[i];
    airenergies[i]*=eV;
    airrefraction.ignore(1000,'\n');
  }
  fAirTable->AddProperty("RINDEX",airenergies, airRindex,Nairrefraction);


  fCathodeTable = new G4MaterialPropertiesTable();
  ifstream cathoderefraction;
  cathoderefraction.open(fset->CathodeRefractionFile());
  if(!cathoderefraction.is_open())
    cout << "error" << endl;
  G4int Ncathoderefraction = 0;
  cathoderefraction >> Ncathoderefraction;
  cathoderefraction.ignore(1000,'\n');
  cathoderefraction.ignore(1000,'\n');
  G4double cathodeenergies[MAXENTRIES];
  G4double cathodeRindexRe[MAXENTRIES];
  G4double cathodeRindexIm[MAXENTRIES];
  G4double cathodeEfficiency[MAXENTRIES];
  for(int i=0;i<Ncathoderefraction;i++){
    cathoderefraction >> cathodeenergies[i] >> cathodeRindexRe[i] >> cathodeRindexIm[i] >> cathodeEfficiency[i];
    cathodeenergies[i]*=eV;
    cathoderefraction.ignore(1000,'\n');
  }
  
  fCathodeTable->AddProperty("EFFICIENCY",cathodeenergies, cathodeEfficiency,Ncathoderefraction);
  fCathodeTable->AddProperty("REALRINDEX",cathodeenergies, cathodeRindexRe,Ncathoderefraction);
  fCathodeTable->AddProperty("IMAGINARYRINDEX",cathodeenergies, cathodeRindexIm,Ncathoderefraction);
  
}

G4VPhysicalVolume* DetectorConstruction::Construct(){

  DefineMaterials();

#ifdef G4VIS_USE
  // usefull colors
  G4VisAttributes* HallVisAtt = new G4VisAttributes(false,G4Colour(0.,1.,0.));
  G4VisAttributes* detectorVisAtt = new G4VisAttributes(true,G4Colour(0.89,0.45,0.13));
  G4VisAttributes* pmtVisAtt      = new G4VisAttributes(true,G4Colour(0.49,0.85,0.13));
  G4VisAttributes* cathodeVisAtt  = new G4VisAttributes(true,G4Colour(0.49,0.45,0.63));
#endif

  //------------------------------ experimental hall (world volume)
  G4double expHall_x = 3.0*m;
  G4double expHall_y = 3.0*m;
  G4double expHall_z = 3.0*m;
  G4Box* experimentalHall_box = new G4Box("expHall_box",expHall_x,expHall_y,expHall_z);
  G4LogicalVolume *experimentalHall_log = new G4LogicalVolume(experimentalHall_box,fVacuum,"expHall_log",0,0,0);
#ifdef G4VIS_USE
  experimentalHall_log->SetVisAttributes(HallVisAtt);
#endif
  G4VPhysicalVolume *experimentalHall_phys = new G4PVPlacement(0,G4ThreeVector(),experimentalHall_log,"expHall",0,false,0);


  //Scintillator scint detector
  //G4Box for the scint, and sensitive detectors
  G4Box* detector_box= new G4Box("detector_box",fset->ScintHeight()*mm/2,fset->ScintWidth()*mm/2,fset->ScintDepth()*mm/2);
  G4LogicalVolume* detector_log = new G4LogicalVolume(detector_box, fScint,"detector_log");
#ifdef G4VIS_USE
  detector_log->SetVisAttributes(detectorVisAtt);
#endif      
  G4VPhysicalVolume* detector_phys = new G4PVPlacement(NULL,G4ThreeVector(fset->ScintPositionX(),fset->ScintPositionY(),fset->ScintPositionZ()),detector_log,"detector_phys",experimentalHall_log,false,0);

  //PMT
  G4Box* pmt_box1= new G4Box("pmt_box1",fset->PMTHeight()*mm/2+fset->PMTThick(),fset->PMTWidth()*mm/2+fset->PMTThick(),fset->PMTDepth()*mm/2);
  G4Box* pmt_box2= new G4Box("pmt_box2",fset->PMTHeight()*mm/2,fset->PMTWidth()*mm/2,fset->PMTDepth()*mm/2);
  G4SubtractionSolid* pmt_box = new G4SubtractionSolid("pmt_box",pmt_box1,pmt_box2);
  G4LogicalVolume* pmt_log = new G4LogicalVolume(pmt_box, fGlass,"pmt_log");
#ifdef G4VIS_USE
  pmt_log->SetVisAttributes(pmtVisAtt);
#endif
  G4VPhysicalVolume* pmt_phys = new G4PVPlacement(NULL,G4ThreeVector(fset->ScintPositionX(),fset->ScintPositionY(),fset->ScintPositionZ()-fset->PMTDepth()*mm/2-fset->ScintDepth()*mm/2),pmt_log,"pmt_phys",experimentalHall_log,false,0);

  //PhotoCathode
  G4Box* cathode_box= new G4Box("cathode_box",fset->PMTHeight()*mm/2,fset->PMTWidth()*mm/2,fset->CathodeDepth()*mm/2);
  G4LogicalVolume* cathode_log = new G4LogicalVolume(cathode_box, fCathode,"cathode_log");
#ifdef G4VIS_USE
  cathode_log->SetVisAttributes(cathodeVisAtt);
#endif
  G4VPhysicalVolume* cathode_phys = new G4PVPlacement(NULL,G4ThreeVector(fset->ScintPositionX(),fset->ScintPositionY(),fset->ScintPositionZ()-fset->CathodeDepth()*mm/2-fset->ScintDepth()*mm/2),cathode_log,"cathode_phys",experimentalHall_log,false,0);


  new G4LogicalSkinSurface("cathode_surface",cathode_log,fCathodeSurf);

  
  //manager for sensistive detectors
  G4SDManager* SDman = G4SDManager::GetSDMpointer();

  
  // -----creating sensisitve detectors and adding them to the sensitive detector manager
  ScintSD* sensitive_scint = new ScintSD("scint");
  SDman->AddNewDetector(sensitive_scint);
  detector_log->SetSensitiveDetector(sensitive_scint);

  CathodeSD* sensitive_cathode = new CathodeSD("cathode");
  SDman->AddNewDetector(sensitive_cathode);
  cathode_log->SetSensitiveDetector(sensitive_cathode);

  return experimentalHall_phys;
}

