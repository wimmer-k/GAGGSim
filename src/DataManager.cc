#include "DataManager.hh"

using namespace std;
using namespace CLHEP;

DataManager::DataManager(){
}
DataManager::DataManager(const char* filename, int nevents, int vlevel){
  fnevents = nevents;
  fvlevel = vlevel;
  cout << "fvlevel " << fvlevel << endl;
  ffile = new TFile(filename,"RECREATE");
  ffile->cd();
  ftree = new TTree("str","simulation data");
  ftree->Branch("esim",&fesim,"esim/D");
  ftree->Branch("edep",&fedep,"edep/D");
  ftree->Branch("nphotons",&fnpho,"npho/I");
  
  ftree->Branch("ncreatedphotons",&fcpho,"cpho/I");
  ftree->Branch("nreflections",&frefl,"refl/l");

  ftree->Branch("efirst",  &ffire,"efir/D");
  ftree->Branch("emax",    &fmaxe,"emax/D");
  ftree->Branch("eaverage",&favee,"eave/D");
  
  ftree->Branch("pfirst",  &ffirp);
  ftree->Branch("pmax",    &fmaxp);
  ftree->Branch("paverage",&favep);

  ftree->BranchRef();
  Clear();
}
DataManager::~DataManager(){
  this->Close();
  delete ftree;
  delete ffile;
}
void DataManager::FillTree(double en, int npho){
  fedep = en;
  fnpho = npho;
  ftree->Fill();
  if(fvlevel>0)
    Print();
  Clear();
}
void DataManager::Print(const Option_t*){
  cout << "event with simulated energy " << fesim << ", deposited energy " << fedep << endl;
  cout << "number of photons created " << fcpho << ", detected photons " << fnpho << ", number of reflections " << frefl << endl;
  cout << "first energy deposition " << ffire << " at xyz = ("<<ffirp.X()<<", "<<ffirp.Y()<<", "<<ffirp.Z()<<")" << endl;
  cout << "maximum energy deposition " << fmaxe << " at xyz = ("<<fmaxp.X()<<", "<<fmaxp.Y()<<", "<<fmaxp.Z()<<")" << endl;
  cout << "average energy deposition " << favee << " at xyz = ("<<favep.X()<<", "<<favep.Y()<<", "<<favep.Z()<<")" << endl;
}
void DataManager::Clear(const Option_t*){
  fesim = 0;
  fedep = 0;
  fnpho = 0;
  fcpho = 0;
  frefl = 0;

  ffire = 0;
  fmaxe = 0;
  favee = 0;
     
  ffirp.SetXYZ(sqrt(-1),sqrt(-1),sqrt(-1));
  fmaxp.SetXYZ(sqrt(-1),sqrt(-1),sqrt(-1));
  favep.SetXYZ(sqrt(-1),sqrt(-1),sqrt(-1));
}
void DataManager::Close(){
  ffile->cd();
  ftree->Write();
  ffile->Close();
}



