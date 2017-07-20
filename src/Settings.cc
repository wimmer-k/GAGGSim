#include "Settings.hh"

using namespace std;

Settings::Settings(){
  cout << "not filename " << endl;
}
Settings::Settings(const char* filename){
  SetFile( filename );
  ReadSettings();
  if(fVerboseLevel>1)
    PrintSettings();
}
Settings::~Settings(){
  cout << "destructor" << endl;
}
void Settings::ReadSettings(){

  TEnv *set = new TEnv(fInputFile.data()); 
  fVerboseLevel = set->GetValue("VerboseLevel",0);
  fDrawOptical = set->GetValue("DrawOptical",0);

  fGammaEnergy = set->GetValue("Gamma.Energy",1000.);
  fGammaWhite[0] = set->GetValue("Gamma.White.From",-1.0);
  fGammaWhite[1] = set->GetValue("Gamma.White.To",-1.0);
  fGammaLevelFile = set->GetValue("Gamma.Level.File","nofile");
  fGammaDirection = set->GetValue("Gamma.Direction",0);
  fGammaTheta = set->GetValue("Gamma.Direction.Theta",0.);
  fGammaPhi = set->GetValue("Gamma.Direction.Phi",0.);
  
  fPosX = set->GetValue("Source.Position.X",0.0);
  fPosY = set->GetValue("Source.Position.Y",0.0);
  fPosZ = set->GetValue("Source.Position.Z",0.0);

  fScintPosX = set->GetValue("Scint.Position.X",0.0);
  fScintPosY = set->GetValue("Scint.Position.Y",0.0);
  fScintPosZ = set->GetValue("Scint.Position.Z",0.0);

  fScintZ = set->GetValue("Scint.Depth",51.0);
  fScintY = set->GetValue("Scint.Height",82.5);
  fScintX = set->GetValue("Scint.Width",82.5);

  fPMTZ = set->GetValue("PMT.Depth",151.0);
  fPMTY = set->GetValue("PMT.Height",82.5);
  fPMTX = set->GetValue("PMT.Width",82.5);
  fPMTwt = set->GetValue("PMT.Thick",1.);

  fGlassRefractionFile = set->GetValue("Glass.Refraction.File","nofile");
  fAirRefractionFile = set->GetValue("Air.Refraction.File","nofile");

  fCathodeZ = set->GetValue("Cathode.Depth",1.0);

  
  fScintProperties = set->GetValue("Scint.Properties","nofile");
  if(fScintProperties.compare("nofile"))
    set = new TEnv(fScintProperties.c_str());
  
  fScintLightYieldFile = set->GetValue("Scint.LightYield.File","nofile");
  fScintRefractionFile = set->GetValue("Scint.Refraction.File","nofile");
  fScintLightYield = set->GetValue("Scint.LightYield",12.8);
  fScintResolutionScale = set->GetValue("Scint.ResolutionScale",1.0);
  fScintFastTimeConstant = set->GetValue("Scint.FastTimeConstant",1.8);
  fScintSlowTimeConstant = set->GetValue("Scint.SlowTimeConstant",14.2);
  fScintFastScintillatorRiseTime = set->GetValue("Scint.FastScintillatorRiseTime",0.7);
  fScintYieldRatio = set->GetValue("Scint.YieldRatio",1.0);
  fScintBirksConstant = set->GetValue("Scint.BirksConstant",0.0159);



}
void Settings::PrintSettings(){
 cout << "VerboseLevel\t" << fVerboseLevel << endl;
 cout << "DrawOptical\t" << fDrawOptical << endl;
 
 cout << "Gamma.Energy\t" << fGammaEnergy << endl;
 cout << "Gamma.Energy.White.0\t" << fGammaWhite[0] << endl;
 cout << "Gamma.Energy.White.1\t" << fGammaWhite[1] << endl;
 cout << "Gamma.Level.File\t" << fGammaLevelFile << endl;
 cout << "Gamma.Direction\t" << fGammaDirection << endl;
 cout << "Gamma.Direction.Theta\t" << fGammaTheta << endl;
 cout << "Gamma.Direction.Phi\t" << fGammaPhi << endl;
 
 cout << "Source.Position.X\t" << fPosX << endl; 
 cout << "Source.Position.Y\t" << fPosY << endl; 
 cout << "Source.Position.Z\t" << fPosZ << endl; 

 cout << "Scint.Position.X\t" << fScintPosX << endl; 
 cout << "Scint.Position.Y\t" << fScintPosY << endl; 
 cout << "Scint.Position.Y\t" << fScintPosY << endl; 

 cout << "Scint.Depth\t"  << fScintZ << endl;
 cout << "Scint.Height\t" << fScintY << endl;
 cout << "Scint.Width\t"  << fScintX << endl;

 if(fScintProperties.compare("nofile"))
   cout << "Scint.Properties\t"  << fScintProperties << endl;
 
 cout << "Scint.LightYield.File\t" << fScintLightYieldFile << endl;
 cout << "Scint.Refraction.File\t" << fScintRefractionFile << endl;
 cout << "Scint.LightYield\t"  << fScintLightYield << endl;
 cout << "Scint.ResolutionScale\t"  << fScintResolutionScale << endl;
 cout << "Scint.FastTimeConstant\t"  << fScintFastTimeConstant << endl;
 cout << "Scint.SlowTimeConstant\t"  << fScintSlowTimeConstant << endl;
 cout << "Scint.FastScintillatorRiseTime\t"  << fScintFastScintillatorRiseTime << endl;
 cout << "Scint.YieldRatio\t"  << fScintYieldRatio << endl;
 cout << "Scint.BirksConstant\t"  << fScintBirksConstant << endl;
 
 cout << "Glass.Refraction.File\t" << fGlassRefractionFile << endl;
 cout << "Air.Refraction.File\t" << fAirRefractionFile << endl;

 cout << "PMT.Depth\t"  << fPMTZ << endl;
 cout << "PMT.Height\t" << fPMTY << endl;
 cout << "PMT.Width\t"  << fPMTX << endl;
 cout << "PMT.Thick\t"  << fPMTwt << endl;

 cout << "Cathode.Depth\t" << fCathodeZ << endl;
 
}
