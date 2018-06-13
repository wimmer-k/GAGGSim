#ifndef DataManager_h
#define DataManager_h 1

#include "G4UnitsTable.hh"
#include "globals.hh"

class DataManager;

#include <TROOT.h>
#include <TObject.h>
#include <TFile.h>
#include <TTree.h>
#include <TVector3.h>


class DataManager{
public:
  DataManager();
  DataManager(const char* filename, int nevents, int vlevel);
  ~DataManager();
  void Init(const char* filename);
  void SetEsim(double e){fesim = e;};
  void SetFirstHit(double e, TVector3 p){ffire = e; ffirp = p;};
  void SetMaxHit(double e, TVector3 p){fmaxe = e; fmaxp = p;};
  void SetAverageHit(double e, TVector3 p){favee = e; favep = p;};
  void AddCreatedPhoton(){fcpho++;};
  void AddReflection(){frefl++;};
  void FillTree(double en, int npho=0);
  void Print(const Option_t* option="");
  void Clear(const Option_t* option="");
  void Close();
  int GetNevents(){return fnevents;};

private:
  int fnevents;
  double fesim;
  double fedep;
  int    fnpho;

  int       fcpho;
  ULong64_t frefl;

  double ffire;
  double fmaxe;
  double favee;
  TVector3 ffirp;
  TVector3 fmaxp;
  TVector3 favep;
  
  TTree* ftree;
  TFile* ffile;
  int fvlevel;
};

#endif

