#include "SensitiveSD.hh"

#include <G4SDManager.hh>
#include <G4SystemOfUnits.hh>
#include "SensitiveHit.hh"

#include "G4String.hh"


SensitiveSD::SensitiveSD(G4String name) :
    G4VSensitiveDetector(name)
{
    collectionName.insert("energy_time");
}

G4bool SensitiveSD::ProcessHits(G4Step* aStep, G4TouchableHistory* /*ROhist*/)
{

    SensitiveHit* hit = new SensitiveHit();

    // Set the variables for the hits..

   // G4StepPoint * preStepPoint  = aStep->GetPreStepPoint();
    G4StepPoint * postStepPoint = aStep->GetPostStepPoint();
    G4Track * theTrack = aStep->GetTrack();

    G4TouchableHandle touch1 = postStepPoint->GetTouchableHandle();
    G4int         copynumber = touch1->GetCopyNumber();
    G4int              ParID = aStep->GetTrack()->GetParentID();
    G4int             StepID = theTrack->GetCurrentStepNumber();

    G4double            eDep = aStep->GetTotalEnergyDeposit();
    G4double            time = aStep->GetPostStepPoint()->GetGlobalTime();
    G4ThreeVector   position = aStep->GetPostStepPoint()->GetPosition();

    G4String            name  = aStep->GetTrack()->GetDynamicParticle()->GetDefinition()->GetParticleName();



    // Fill in the hit properties
    hit->SetTime(time);
    hit->SetDeltaEnergy(eDep);
    hit->SetPosition(position);
    hit->SetNbCopy(copynumber);

    hit->SetParID(ParID);
    hit->SetStepID(StepID);
    hit->SetParName(name);


    // Add the hit to the collection
    fHitsCollection->insert(hit);

    return true;
}

void SensitiveSD::Initialize(G4HCofThisEvent* hcof)
{

    fHitsCollection = new SensitiveHitsCollection(SensitiveDetectorName, collectionName[0]);

    if (fHitsCollectionId < 0)
    {
        fHitsCollectionId = G4SDManager::GetSDMpointer()->GetCollectionID(GetName() + "/" + collectionName[0]);
    }
    hcof->AddHitsCollection(fHitsCollectionId, fHitsCollection);

}
