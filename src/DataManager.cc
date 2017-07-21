#include "DataManager.hh"

using namespace std;
using namespace CLHEP;

DataManager::DataManager(){
  cout << "bla" << endl;
}
DataManager::DataManager(const char* filename, int nevents){
  fnevents = nevents;
  ffile = new TFile(filename,"RECREATE");
  ffile->cd();
  ftree = new TTree("str","simulation data");
  ftree->Branch("esim",&fesim,"esim/D");
  ftree->Branch("edep",&fedep,"edep/D");
  ftree->Branch("npho",&fnpho,"npho/I");
  ftree->BranchRef();
}
DataManager::~DataManager(){
  this->Close();
  delete ftree;
  delete ffile;
}
void DataManager::SetEsim(double e){
  fesim = e;
}
void DataManager::FillTree(double en, int npho){
  fedep = en;
  fnpho = npho;
  ftree->Fill();
  fesim = 0;
}
void DataManager::Clear(const Option_t*){
  fesim = 0;
  fedep = 0;
  fnpho = 0;
}
void DataManager::Close(){
  ffile->cd();
  ftree->Write();
  ffile->Close();
}



