/*************************************************************************
 *
 *    Scintillator hit
 * 
 *************************************************************************/

#include "ScintHit.hh"

G4Allocator<ScintHit> HitAllocator;

ScintHit::ScintHit()
  :trackID(0), edep(0), pos(0), posindet(0)
{;}

ScintHit::~ScintHit() 
{;}

ScintHit::ScintHit(const ScintHit& right)
  : G4VHit()
{
  trackID     = right.trackID;
  parentID    = right.parentID;
  edep        = right.edep;
  pos         = right.pos;
  posindet    = right.posindet;
  track.CopyTrackInfo(right.track);
  procName    = right.procName;
  step        = right.step;
  vol         = right.vol;
  ID          = right.ID;
}

const ScintHit& ScintHit::operator=(const ScintHit& right)
{
  trackID     = right.trackID;
  parentID    = right.parentID;
  edep        = right.edep;
  pos         = right.pos;
  posindet    = right.posindet;
  track.CopyTrackInfo(right.track);
  procName    = right.procName;
  step        = right.step;
  vol         = right.vol;
  ID          = right.ID;
  return *this;
}

int ScintHit::operator==(const ScintHit&) const
{
  return 0;
}

void ScintHit::Draw()
{
  G4VVisManager* pVVisManager = G4VVisManager::GetConcreteInstance();

  if(pVVisManager)
  {
    G4Circle circle(pos);
    circle.SetScreenSize(0.04);
    circle.SetFillStyle(G4Circle::filled);
    G4Colour colour(1.,0.,0.);
    G4VisAttributes attribs(colour);
    circle.SetVisAttributes(attribs);
    pVVisManager->Draw(circle);
  }
}

void ScintHit::Print()
{
  G4cout << " Scint: " << G4endl;
  G4cout << "  trackID: " << trackID 
         << "  energy deposit: " << G4BestUnit(edep,"Energy")
	 << "  position: " << G4BestUnit(pos,"Length") << G4endl;
}




