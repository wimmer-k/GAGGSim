#ifndef Settings_h
#define Settings_h 1

#include <iostream>
#include <fstream>
#include <string>

class Settings;
#include "TSystem.h"
#include "TEnv.h"
#include "TObject.h"
#include "TMath.h"
using namespace std;

#define deg2rad TMath::Pi()/180.;
#define rad2deg 180./TMath::Pi();


class Settings{
public:
  Settings();//default ctor
  Settings(const char*);
  ~Settings();

  void ReadSettings();
  void PrintSettings();
  void SetFile(const char* filename){fInputFile = filename;}
  const string InputFile(){return fInputFile;}

  int VLevel(){return fVerboseLevel;}
  int DrawOptical(){return fDrawOptical;}
  void SetVerboseLevel(int vlevel){fVerboseLevel = vlevel;}
  
  double GammaEnergy(){return fGammaEnergy;}
  double GammaWhite(int i){return fGammaWhite[i];}
  double GammaWhiteFrom(){return fGammaWhite[0];}
  double GammaWhiteTo(){return fGammaWhite[1];}
  const char* GammaLevelFile(){return fGammaLevelFile.c_str();}
  int GammaDirection(){return fGammaDirection;}
  double GammaDirectionTheta(){return fGammaTheta;}
  double GammaDirectionPhi(){return fGammaPhi;}

  double SourcePositionX(){return fPosX;} 
  double SourcePositionY(){return fPosY;} 
  double SourcePositionZ(){return fPosZ;} 

  double ScintPositionX(){return fScintPosX;} 
  double ScintPositionY(){return fScintPosY;} 
  double ScintPositionZ(){return fScintPosZ;} 

  double ScintDepth(){return  fScintZ;}
  double ScintHeight(){return fScintY;}
  double ScintWidth(){return  fScintX;}

  const char* ScintPropertiesFile(){return fScintProperties.c_str();}
  const char* ScintLightYieldFile(){return fScintLightYieldFile.c_str();}
  const char* ScintRefractionFile(){return fScintRefractionFile.c_str();}

  double ScintLightYield(){return fScintLightYield;}
  double ScintResolutionScale(){return fScintResolutionScale;}
  double ScintFastTimeConstant(){return fScintFastTimeConstant;}
  double ScintSlowTimeConstant(){return fScintSlowTimeConstant;}
  double ScintFastScintillatorRiseTime(){return fScintFastScintillatorRiseTime;}
  double ScintYieldRatio(){return fScintYieldRatio;}
  double ScintBirksConstant(){return fScintBirksConstant;}
  
  double PMTDepth(){return  fPMTZ;}
  double PMTHeight(){return fPMTY;}
  double PMTWidth(){return  fPMTX;}
  double PMTThick(){return  fPMTwt;}
  const char* GlassRefractionFile(){return fGlassRefractionFile.c_str();}
  const char* AirRefractionFile(){return fAirRefractionFile.c_str();}
  const char* CathodeRefractionFile(){return fCathodeRefractionFile.c_str();}

  double CathodeDepth(){return  fCathodeZ;}
  
protected:
  int fVerboseLevel;
  int fDrawOptical;

  string fInputFile;
  double fGammaEnergy;
  double fGammaWhite[2];
  string fGammaLevelFile;
  int fGammaDirection;
  double fGammaTheta;
  double fGammaPhi;
  double fPosX;
  double fPosY;
  double fPosZ;
  
  double fScintPosX;
  double fScintPosY;
  double fScintPosZ;
  double fScintZ;
  double fScintY;
  double fScintX;
  string fScintProperties;
  string fScintLightYieldFile;
  string fScintRefractionFile;
  double fScintLightYield;
  double fScintResolutionScale;
  double fScintFastTimeConstant;
  double fScintSlowTimeConstant;
  double fScintFastScintillatorRiseTime;
  double fScintYieldRatio;
  double fScintBirksConstant;

  double fPMTZ;
  double fPMTY;
  double fPMTX;
  double fPMTwt;
  string fGlassRefractionFile;
  string fAirRefractionFile;
  string fCathodeRefractionFile;

  double fCathodeZ;
};
#endif
