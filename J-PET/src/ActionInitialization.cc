/// \file ActionInitialization.cc
/// \brief Implementation of the ActionInitialization class

#include "ActionInitialization.hh"
#include "PrimaryGeneratorAction.hh"
#include "EventAction.hh"

#include "RunAction.hh"
#include "StackingAction.hh"
#include "SteppingAction.hh"

//! Class constructor
ActionInitialization::ActionInitialization() :
  G4VUserActionInitialization()
{;}

//! Class destructor
ActionInitialization::~ActionInitialization()
{;}

void ActionInitialization::Build() const
{
    // Add your actions
    //

    // Add the primary generator (mandatory)
    SetUserAction(new PrimaryGeneratorAction());


    //Add a properly initialized instance of RunAction
    // Important to initialize to have output
    RunAction* theRunAction = new RunAction();
    SetUserAction(theRunAction);


    // Add a properly initialized instance of EventAction
    SetUserAction(new EventAction());

    //Add a properly initialized instance of SteppingAction
    SetUserAction(new StackingAction(theRunAction));

    //Add a properly initialized instance of SteppingAction
    SetUserAction(new SteppingAction(theRunAction));

}

void ActionInitialization::BuildForMaster() const
{
  // By default, don't do anything. Required only for
  // specific MT applications
}
