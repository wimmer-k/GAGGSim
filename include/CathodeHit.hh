/*************************************************************************
 *
 *    Cathode hit 
 * 
 *************************************************************************/

#ifndef CathodeHit_h
#define CathodeHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "G4Track.hh"
#include "G4Types.hh"
#include "G4String.hh"
#include "G4UnitsTable.hh"
#include "G4VVisManager.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"

class CathodeHit;

typedef G4THitsCollection<CathodeHit> CathodeHitsCollection;

extern G4Allocator<CathodeHit> CathodeHitAllocator;


class CathodeHit : public G4VHit
{
public:

  CathodeHit();
  ~CathodeHit();
  CathodeHit(const CathodeHit&);
  const CathodeHit& operator=(const CathodeHit&);
  int operator==(const CathodeHit&) const;

  inline void* operator new(size_t);
  inline void  operator delete(void*);

  void Draw();
  void Print();
  void SetID(G4int seg_id) {ID = seg_id;};
  G4int GetID()      { return ID; };

  // void SetPos(G4ThreeVector xyz){ pos = xyz; };
  // G4ThreeVector GetPos()      { return pos; };
  /*
  void SetTrackID(G4int ttrack){ trackID = ttrack; };
  void SetParentID(G4int par){ parentID = par; };
  void SetEdep(G4double de){ edep = de; };
  void SetPosInDet(G4ThreeVector xyz){ posindet = xyz; };
  void SetTrack(G4Track* Track){ track.CopyTrackInfo(*Track); };
  void SetProcName(G4String pname){ procName = pname; };
  void SetStep(G4int Step){ step = Step; };
  void SetVolume(G4String Vol){ vol = Vol; };
  //void SetID(G4int seg_id) {ID = seg_id;};
      
  G4int GetTrackID()          { return trackID; };
  G4int GetParentID()         { return parentID; };
  G4double GetEdep()          { return edep; };      
  G4ThreeVector GetPosInDet() { return posindet; };
  G4Track* GetTrack()         { return &track; };
  G4String GetProcName()      { return procName; };
  G4int GetStep()             { return  step; };
  G4String GetVolume()        { return vol; };
  //G4int GetID()      { return ID; };
  */
  inline void AddPhoton(){fnphotons++;}
  inline G4int GetPhotonCount(){return fnphotons;}


private:
  G4int fnphotons;
  //G4ThreeVector pos;
  G4int         ID;
  /*
  G4int         trackID;
  G4int         parentID;
  G4double      edep;
  G4ThreeVector posindet;
  G4Track       track;
  G4String      procName;
  G4int         step;
  G4String      vol;
  */
};

inline void* CathodeHit::operator new(size_t)
{
  void *aHit;
  aHit = (void *) CathodeHitAllocator.MallocSingle();
  return aHit;
}

inline void CathodeHit::operator delete(void *aHit)
{
  CathodeHitAllocator.FreeSingle((CathodeHit*) aHit);
}

#endif


