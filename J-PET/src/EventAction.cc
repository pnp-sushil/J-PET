/// \file EventAction.cc
/// \brief Implementation of the EventAction class
#include "EventAction.hh"
#include <G4SDManager.hh>
#include <G4THitsMap.hh>
#include <G4SystemOfUnits.hh>
#include <G4Event.hh>
#include "SensitiveHit.hh"


#include "Analysis.hh"

using namespace std;

EventAction::EventAction() :
    G4UserEventAction()
{
    ;
}

EventAction::~EventAction()
{
    ;
}


void EventAction::BeginOfEventAction(const G4Event* anEvent)
{
    // Will be used later
}

void EventAction::EndOfEventAction(const G4Event* anEvent)
{

    G4SDManager* sdm = G4SDManager::GetSDMpointer();

// Intentiate the analysis manager
    G4AnalysisManager* analysis = G4AnalysisManager::Instance();

// Get the hit collection
    G4HCofThisEvent* hcofEvent = anEvent->GetHCofThisEvent();

// If there is no hit collection, there is nothing to be done
    if(!hcofEvent) return;

  //  G4int fScintillatorId;

    if(fScintillatorId<0)
    {
        fScintillatorId = sdm->GetCollectionID("Scintillator/energy_time");
        G4cout<< "Eventaction : Scintillator id is = "<<fScintillatorId<<G4endl;
    }



    SensitiveHitsCollection* hitsColl=0;

    if(hcofEvent) hitsColl = dynamic_cast<SensitiveHitsCollection*>(hcofEvent->GetHC(fScintillatorId));

    if(hitsColl)
    {
        int numberHits = hitsColl->entries();

     //   G4cout<<" Total  number of Hits are = "<<numberHits<<G4endl;

        for(int i1=0; i1<numberHits; i1++)
        {

            auto hit = (*hitsColl)[i1];
            analysis->FillNtupleDColumn(0,hit->GetDeltaEnergy() / keV);
            analysis->FillNtupleDColumn(1, hit->GetTime() / ns);
            G4ThreeVector position = hit->GetPosition();
            analysis->FillNtupleDColumn(2, position.getX() / cm);
            analysis->FillNtupleDColumn(3, position.getY() / cm);
            analysis->FillNtupleDColumn(4, position.getZ() / cm);
            analysis->FillNtupleIColumn(5,hit->GetNbCopy());
            analysis->FillNtupleIColumn(6,hit->GetParID());
            analysis->FillNtupleIColumn(7,hit->GetStepID());
            analysis->FillNtupleSColumn(8,hit->GetParName());
            analysis->AddNtupleRow();

        }
    }

}
