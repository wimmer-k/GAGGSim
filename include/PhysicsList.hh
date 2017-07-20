#ifndef PhysicsList_h
#define PhysicsList_h 1

#include "G4VModularPhysicsList.hh"
#include "globals.hh"

#include "G4VPhysicsConstructor.hh"

#include "G4ios.hh"
#include "G4Decay.hh"
#include "G4PhotoElectricEffect.hh"
#include "G4ComptonScattering.hh"
#include "G4GammaConversion.hh"
#include "G4eMultipleScattering.hh"
#include "G4eIonisation.hh"
#include "G4eBremsstrahlung.hh"
#include "G4eplusAnnihilation.hh"

#include "G4ParticleDefinition.hh"
#include "G4ProcessManager.hh"
#include "G4ParticleTable.hh"
#include "G4Geantino.hh"
#include "G4ChargedGeantino.hh"
#include "G4GenericIon.hh"
#include "G4Gamma.hh"
#include "G4Electron.hh"
#include "G4Positron.hh"
#include "G4NeutrinoE.hh"
#include "G4AntiNeutrinoE.hh"

class PhysicsList: public G4VModularPhysicsList{
public:
  PhysicsList();
  virtual ~PhysicsList();
  virtual void SetCuts();
};


class Physics: public G4VPhysicsConstructor{
public:
  Physics(const G4String& name = "physics");
    virtual ~Physics();

    virtual void ConstructParticle();
    virtual void ConstructProcess();
  
  protected:
    G4Decay* fDecayProcess;
   // Gamma physics
    G4PhotoElectricEffect* fPhotoEffect;
    G4ComptonScattering* fComptonEffect;
    G4GammaConversion* fPairProduction;
 
    // Electron physics
    G4eMultipleScattering* fElectronMultipleScattering;
    G4eIonisation* fElectronIonisation;
    G4eBremsstrahlung* fElectronBremsStrahlung;
 
    //Positron physics
    G4eMultipleScattering* fPositronMultipleScattering;
    G4eIonisation* fPositronIonisation;
    G4eBremsstrahlung* fPositronBremsStrahlung;
    G4eplusAnnihilation* fAnnihilation;

};
#endif

 
