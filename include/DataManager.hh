#ifndef DataManager_h
#define DataManager_h 1

#include "G4UnitsTable.hh"
#include "globals.hh"

class DataManager;

#include <TROOT.h>
#include <TObject.h>
#include <TFile.h>
#include <TTree.h>


class DataManager{
public:
  DataManager();
  DataManager(const char* filename, int nevents);
  ~DataManager();
  void Init(const char* filename);
  void SetEsim(double e);
  void FillTree(double en, int npho=0);
  void Clear(const Option_t* option="");
  void Close();
  int GetNevents(){return fnevents;};

private:
  int fnevents;
  double fesim;
  double fedep;
  int    fnpho;
  TTree* ftree;
  TFile* ffile;
};

#endif

