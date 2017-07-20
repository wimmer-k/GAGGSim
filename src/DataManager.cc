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
  ftree->Branch("edet",&fedet,"edet/D");
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
void DataManager::FillTree(double en){
  fedet = en;
  ftree->Fill();
  fesim = 0;
}
void DataManager::Clear(const Option_t*){
  fesim = 0;
  fedet = 0;
}
void DataManager::Close(){
  ffile->cd();
  ftree->Write();
  ffile->Close();
}



