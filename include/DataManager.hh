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
  DataManager(const char* filename, int nevents);
  ~DataManager();
  void Init(const char* filename);
  void SetEsim(double e){fesim = e;};
  void SetFirstHit(double e, TVector3 p){ffire = e; ffirp = p;};
  void SetMaxHit(double e, TVector3 p){fmaxe = e; fmaxp = p;};
  void SetAverageHit(double e, TVector3 p){favee = e; favep = p;};
  void FillTree(double en, int npho=0);
  void Clear(const Option_t* option="");
  void Close();
  int GetNevents(){return fnevents;};

private:
  int fnevents;
  double fesim;
  double fedep;
  int    fnpho;

  double ffire;
  double fmaxe;
  double favee;
  TVector3 ffirp;
  TVector3 fmaxp;
  TVector3 favep;
  
  TTree* ftree;
  TFile* ffile;
};

#endif

