/*************************************************************************
 *
 *    Cathode hit
 * 
 *************************************************************************/

#include "CathodeHit.hh"

G4Allocator<CathodeHit> CathodeHitAllocator;

CathodeHit::CathodeHit()
  :fnphotons(0), ID(-1)//, pos(0)
{;}

CathodeHit::~CathodeHit() 
{;}

CathodeHit::CathodeHit(const CathodeHit& right)
  : G4VHit()
{
  fnphotons = right.fnphotons;
  ID          = right.ID;
  //pos         = right.pos;
  /*
  trackID     = right.trackID;
  parentID    = right.parentID;
  edep        = right.edep;
  posindet    = right.posindet;
  track.CopyTrackInfo(right.track);
  procName    = right.procName;
  step        = right.step;
  vol         = right.vol;
  */
}

const CathodeHit& CathodeHit::operator=(const CathodeHit& right)
{
  fnphotons = right.fnphotons;
  ID          = right.ID;
  //pos         = right.pos;
  /*
  trackID     = right.trackID;
  parentID    = right.parentID;
  edep        = right.edep;
  posindet    = right.posindet;
  track.CopyTrackInfo(right.track);
  procName    = right.procName;
  step        = right.step;
  vol         = right.vol;
  */
  return *this;
}

int CathodeHit::operator==(const CathodeHit&) const
{
  return 0;
}

void CathodeHit::Draw()
{
//  G4VVisManager* pVVisManager = G4VVisManager::GetConcreteInstance();
//
//  if(pVVisManager)
//  {
//    G4Circle circle(pos);
//    circle.SetScreenSize(0.04);
//    circle.SetFillStyle(G4Circle::filled);
//    G4Colour colour(1.,0.,0.);
//    G4VisAttributes attribs(colour);
//    circle.SetVisAttributes(attribs);
//    pVVisManager->Draw(circle);
//  }
}

void CathodeHit::Print()
{
  G4cout << " Cathode: " << G4endl;
  G4cout << "  number of phtotons: " << fnphotons << G4endl;
}




