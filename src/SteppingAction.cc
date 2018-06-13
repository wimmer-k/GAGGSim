#include "SteppingAction.hh"
SteppingAction::SteppingAction(DataManager* data) : fOneStepPrimaries(false){
  // store the pointer to the data class locally, in order to be able to acess all information later
  fdata = data;
  fExpectedNextStatus = Undefined;
}
SteppingAction::~SteppingAction() {}

void SteppingAction::UserSteppingAction(const G4Step * theStep){
  //cout << __PRETTY_FUNCTION__ << endl;
  G4Track* theTrack = theStep->GetTrack();

  if ( theTrack->GetCurrentStepNumber() == 1 ) fExpectedNextStatus = Undefined;
 
  G4StepPoint* thePrePoint = theStep->GetPreStepPoint();
  G4VPhysicalVolume* thePrePV = thePrePoint->GetPhysicalVolume();

  G4StepPoint* thePostPoint = theStep->GetPostStepPoint();
  G4VPhysicalVolume* thePostPV = thePostPoint->GetPhysicalVolume();

  G4OpBoundaryProcessStatus boundaryStatus=Undefined;
  static G4ThreadLocal G4OpBoundaryProcess* boundary=NULL;

  //find the boundary process only once
  if(!boundary){
    G4ProcessManager* pm
      = theStep->GetTrack()->GetDefinition()->GetProcessManager();
    G4int nprocesses = pm->GetProcessListLength();
    G4ProcessVector* pv = pm->GetProcessList();
    G4int i;
    for( i=0;i<nprocesses;i++){
      if((*pv)[i]->GetProcessName()=="OpBoundary"){
        boundary = (G4OpBoundaryProcess*)(*pv)[i];
	//cout << "found boundary " << endl;
	//cout << "thePrePV->GetName() " << thePrePV->GetName() << ", thePostPV->GetName() " << thePostPV->GetName() << endl;
        break;
      }
    }
  }
  G4ParticleDefinition* particleType = theTrack->GetDefinition();
  // if(theTrack->GetParentID()>=0){
  //   cout << "ParentID " << theTrack->GetParentID();
  //   cout << ", particleType " << particleType->GetParticleName();
  //   cout << ", step process " << thePostPoint->GetProcessDefinedStep()->GetProcessName();
  //   if(thePostPoint->GetPhysicalVolume())
  //     cout << ", step volume " << thePostPoint->GetPhysicalVolume()->GetName();
  //   else
  //     cout << ", step volume out o world";
  //   if(theTrack->GetParentID()>0)
  //     cout << ", track process " << theTrack->GetCreatorProcess()->GetProcessName() << endl;
  //   else
  //     cout << endl;
  // }
  if(theTrack->GetParentID()==0){
    //This is a primary track 
    if(fOneStepPrimaries&&thePrePV->GetName()=="scint")
      theTrack->SetTrackStatus(fStopAndKill);
  }

  if(!thePostPV){//out of world
    fExpectedNextStatus=Undefined;
    return;
  }
  if(!boundary)
    return;
  if(particleType==G4OpticalPhoton::OpticalPhotonDefinition()){
    //Optical photon only
    boundaryStatus=boundary->GetStatus();

    //Check to see if the partcile was actually at a boundary
    //Otherwise the boundary status may not be valid
    //Prior to Geant4.6.0-p1 this would not have been enough to check
    if(thePostPoint->GetStepStatus()==fGeomBoundary){
      if(fExpectedNextStatus==StepTooSmall){
        if(boundaryStatus!=StepTooSmall){
          G4ExceptionDescription ed;
          ed << "SteppingAction::UserSteppingAction(): "
                << "No reallocation step after reflection!"
                << G4endl;
          G4Exception("SteppingAction::UserSteppingAction()", "Expl01",
          FatalException,ed,
          "Something is wrong with the surface normal or geometry");
        }
      }
      fExpectedNextStatus=Undefined;
      //cout << "boundaryStatus " << boundaryStatus <<endl;
      switch(boundaryStatus){
      case Absorption:
        break;
      case Detection:{
	//Note, this assumes that the volume causing detection is the photocathode because it is the only one with non-zero efficiency
	//Triger sensitive detector manually since photon is
	//absorbed but status was Detection
	G4SDManager* SDman = G4SDManager::GetSDMpointer();
	CathodeSD* cathode = (CathodeSD*)SDman->FindSensitiveDetector("cathode");
	//cout << "detection " << endl;
	if(cathode)
	  cathode->ProcessSteps(theStep,NULL);
	break;
      }
      case FresnelReflection:
	fdata->AddReflection();
	break;
      case LambertianReflection:
	fdata->AddReflection();
	break;
      case LobeReflection:
	fdata->AddReflection();
	break;
      case SpikeReflection:
	fdata->AddReflection();
	break;
      case TotalInternalReflection:
	fdata->AddReflection();
	break;
      case Undefined:
      case FresnelRefraction:
      case StepTooSmall:
      case SameMaterial:
      case NotAtBoundary:
      case NoRINDEX:
	//cout << "no refractive index! " << endl;
	break;
      case BackScattering:
	fExpectedNextStatus=StepTooSmall;
	break;
      default:
        break;
      }
    }
  }
}
/*
0	Undefined 	
1	FresnelRefraction 	
2	FresnelReflection 	
3	TotalInternalReflection 	
4	LambertianReflection 	
5	LobeReflection 	
6	SpikeReflection 	
7	BackScattering 	
8	Absorption 	
9	Detection 	
10	NotAtBoundary 	
11	SameMaterial 	
12	StepTooSmall 	
13	NoRINDEX 
*/
