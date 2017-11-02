#ifndef SENSITIVEHIT_HH
#define SENSITIVEHIT_HH

#include <G4VHit.hh>
#include <G4THitsMap.hh>
#include <G4ThreeVector.hh>

/**
  * Custom hit class used in task 4d.
  *
  * It holds infomation about energy deposits and position/time when
  * traversing a layer.
  */
class SensitiveHit : public G4VHit
{
public:
    // Memory allocation and de-allocation
    inline void* operator new(size_t);
    inline void  operator delete(void*);


 // Set the hit variables
    void SetDeltaEnergy(G4double deltaE) { fDeltaEnergy = deltaE; }
    void SetTime(G4double time) { fTime = time; }
    void SetPosition(G4ThreeVector pos) { fPosition = pos; }
    void SetNbCopy(G4int scint) {fscintID = scint;}
    void SetParID(G4int Parentid) {fParID = Parentid;}
    void SetStepID(G4int stepid) {fStepID = stepid;}
    void SetParName(G4String particle) {fParName = particle;}

  // Get the hit variables

    G4double GetDeltaEnergy() const { return fDeltaEnergy; }
    G4double GetTime() const { return fTime; }
    G4ThreeVector GetPosition() const { return fPosition; }
    G4int GetNbCopy() const { return fscintID;}
    G4int GetParID() const {return fParID;}
    G4int GetStepID() const {return fStepID;}
    G4String GetParName() const {return fParName;}

    // Declare the hit variables
private:
    G4double fDeltaEnergy;
    G4double fTime;
    G4ThreeVector fPosition;
    G4int fscintID;
    G4int fParID;
    G4int fStepID;
    G4String fParName;
};

using SensitiveHitsCollection = G4THitsCollection<SensitiveHit>;

extern G4ThreadLocal G4Allocator<SensitiveHit> *hitAllocator;

inline void* SensitiveHit::operator new(size_t)
{
  if (!hitAllocator)
  {
      hitAllocator = new G4Allocator<SensitiveHit>;
  }
  return hitAllocator->MallocSingle();
}

inline void SensitiveHit::operator delete(void *aHit)
{
    if (!hitAllocator)
    {
        hitAllocator = new G4Allocator<SensitiveHit>;
    }
    hitAllocator->FreeSingle((SensitiveHit*) aHit);
}

#endif
