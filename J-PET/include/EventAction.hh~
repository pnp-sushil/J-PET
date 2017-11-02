/// \file EventAction.hh
/// \brief Definition of the EventAction class

#ifndef EVENTACTION_HH
#define EVENTACTION_HH

#include <G4UserEventAction.hh>
#include <globals.hh>

/// Event action class
/// Provides access to the G4Event* information at the begin and 
/// at the end of each event

class EventAction : public G4UserEventAction
{
public:
  ///constructor
  EventAction();

  ///destructor
  ~EventAction();

  ///User actions to be performed at the beginning of each event
  void BeginOfEventAction(const G4Event* anEvent) override;

  ///User actions to be performed at the end of each event
  void EndOfEventAction(const G4Event* anEvent) override;
  
  private:
  //Numberical IDs for hit collection (-1 means unknown yet)
   G4int fScintillatorId{ -1 }; // for customed sensitive detector.
};

#endif
