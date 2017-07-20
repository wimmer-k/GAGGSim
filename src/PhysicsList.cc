#include "PhysicsList.hh"

#include "G4OpticalPhysics.hh"
#include "G4OpticalProcessIndex.hh"
#include "G4SystemOfUnits.hh"

PhysicsList::PhysicsList():  G4VModularPhysicsList(){
  defaultCutValue = 1.0*mm;
  SetVerboseLevel(0);
  
  RegisterPhysics( new Physics("physics") );
  // Optical Physics
  G4OpticalPhysics* opticalPhysics = new G4OpticalPhysics();
  RegisterPhysics( opticalPhysics );

  opticalPhysics->SetWLSTimeProfile("delta");

  opticalPhysics->SetScintillationYieldFactor(1.0);
  opticalPhysics->SetScintillationExcitationRatio(0.0);

  opticalPhysics->SetMaxNumPhotonsPerStep(100);
  opticalPhysics->SetMaxBetaChangePerStep(10.0);

  opticalPhysics->SetTrackSecondariesFirst(kCerenkov,true);
  opticalPhysics->SetTrackSecondariesFirst(kScintillation,true);
  
}

PhysicsList::~PhysicsList(){}

void PhysicsList::SetCuts(){
  //G4VUserPhysicsList::SetCutsWithDefault method sets 
  //the default cut value for all particle types 
  SetCutsWithDefault();
     
  if (verboseLevel>0) DumpCutValuesTable();
}


Physics::Physics(const G4String& name) :  G4VPhysicsConstructor(name) {
  fDecayProcess = NULL;
  fPhotoEffect = NULL;
  fComptonEffect = NULL;
  fPairProduction = NULL;
  fElectronMultipleScattering = NULL;
  fElectronIonisation = NULL; 
  fElectronBremsStrahlung = NULL;
  fPositronMultipleScattering = NULL;
  fPositronIonisation = NULL; 
  fPositronBremsStrahlung = NULL;
  fAnnihilation = NULL;
}

Physics::~Physics() {
  fDecayProcess = NULL;
  fPhotoEffect = NULL;
  fComptonEffect = NULL;
  fPairProduction = NULL;
  fElectronMultipleScattering = NULL;
  fElectronIonisation = NULL; 
  fElectronBremsStrahlung = NULL;
  fPositronMultipleScattering = NULL;
  fPositronIonisation = NULL; 
  fPositronBremsStrahlung = NULL;
  fAnnihilation = NULL;
}
void Physics::ConstructParticle()
{
  // pseudo-particles
  G4Geantino::GeantinoDefinition();
  G4ChargedGeantino::ChargedGeantinoDefinition();
  G4GenericIon::GenericIonDefinition();
  // gamma
  G4Gamma::GammaDefinition();
  // electron
  G4Electron::ElectronDefinition();
  G4Positron::PositronDefinition();
  G4NeutrinoE::NeutrinoEDefinition();
  G4AntiNeutrinoE::AntiNeutrinoEDefinition();

}
void Physics::ConstructProcess()
{
  fDecayProcess = new G4Decay();

  // Add Decay Process
  aParticleIterator->reset();
  while( (*aParticleIterator)() ){
    G4ParticleDefinition* particle = aParticleIterator->value();
    G4ProcessManager* pmanager = particle->GetProcessManager();
    if (fDecayProcess->IsApplicable(*particle)) {
      pmanager ->AddProcess(fDecayProcess);
      // set ordering for PostStepDoIt and AtRestDoIt
      pmanager ->SetProcessOrdering(fDecayProcess, idxPostStep);
      pmanager ->SetProcessOrdering(fDecayProcess, idxAtRest);
    }
  }
  fPhotoEffect = new G4PhotoElectricEffect();
  fComptonEffect = new G4ComptonScattering();
  fPairProduction = new G4GammaConversion();
 
    // Electron physics
  fElectronMultipleScattering = new G4eMultipleScattering();
  fElectronIonisation = new G4eIonisation();
  fElectronBremsStrahlung = new G4eBremsstrahlung();
 
    //Positron physics
  fPositronMultipleScattering = new G4eMultipleScattering();
  fPositronIonisation = new G4eIonisation();
  fPositronBremsStrahlung = new G4eBremsstrahlung();
  fAnnihilation = new G4eplusAnnihilation();

  G4ProcessManager* pManager = 0;

  // Gamma Physics
  pManager = G4Gamma::Gamma()->GetProcessManager();
  pManager->AddDiscreteProcess(fPhotoEffect);
  pManager->AddDiscreteProcess(fComptonEffect);
  pManager->AddDiscreteProcess(fPairProduction);

  // Electron Physics
  pManager = G4Electron::Electron()->GetProcessManager();
  pManager->AddProcess(fElectronMultipleScattering, -1, 1, 1);
  pManager->AddProcess(fElectronIonisation,         -1, 2, 2);
  pManager->AddProcess(fElectronBremsStrahlung,     -1, 3, 3);  

  //Positron Physics
  pManager = G4Positron::Positron()->GetProcessManager(); 
  pManager->AddProcess(fPositronMultipleScattering, -1, 1, 1);
  pManager->AddProcess(fPositronIonisation,         -1, 2, 2);
  pManager->AddProcess(fPositronBremsStrahlung,     -1, 3, 3);  
  pManager->AddProcess(fAnnihilation,                0,-1, 4);  

}
