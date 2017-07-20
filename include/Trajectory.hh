#ifndef Trajectory_h
#define Trajectory_h 1

#include "G4Trajectory.hh"
#include "G4Allocator.hh"
#include "G4ios.hh"
#include "globals.hh"
#include "G4ParticleDefinition.hh"
#include "G4TrajectoryPoint.hh"
#include "G4Track.hh"
#include "G4Step.hh"

class G4Polyline;                   // Forward declaration.

class Trajectory : public G4Trajectory{
public:
  
  Trajectory();
  Trajectory(const G4Track* aTrack);
  Trajectory(Trajectory &);
  virtual ~Trajectory();
  
  void DrawATrajectory() const;
  
  inline void* operator new(size_t);
  inline void  operator delete(void*);
  
 private:
  
  G4ParticleDefinition* fParticleDefinition;
};

extern G4ThreadLocal G4Allocator<Trajectory>* TrajectoryAllocator;

inline void* Trajectory::operator new(size_t){
  if(!TrajectoryAllocator)
    TrajectoryAllocator = new G4Allocator<Trajectory>;
  return (void*)TrajectoryAllocator->MallocSingle();
}

inline void Trajectory::operator delete(void* aTrajectory){
  TrajectoryAllocator->FreeSingle((Trajectory*)aTrajectory);
}

#endif
