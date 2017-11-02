/// \file PhysicsList.hh
/// \brief Implementation of the PhysicsList class (Mandatory)

#include "PhysicsList.hh"

// Include standard Electromagnetic
#include <G4EmStandardPhysics.hh>
// Include header for G4EmLivermorePhysics
#include <G4EmLivermorePhysics.hh>
//Include header for G4EmExtraPhysics
#include <G4EmExtraPhysics.hh>
// Set decay physics list
#include <G4DecayPhysics.hh>
// Needed to implement cuts
#include <G4ProductionCutsTable.hh>

#include  <G4EmLivermorePolarizedPhysics.hh>

#include <G4SystemOfUnits.hh>

#include <G4LowEPComptonModel.hh>


//++++++++++++++++++++++



PhysicsList::PhysicsList() :
    G4VModularPhysicsList()
{

    G4int verb = 1;
    SetVerboseLevel(verb);


    RegisterPhysics(new G4EmStandardPhysics());

    //  RegisterPhysics(new G4EmLivermorePhysics());
    //specialized low-energy Livermore database with polarization
    //  RegisterPhysics(new G4EmLivermorePolarizedPhysics());

    // RegisterPhysics(new G4EmExtraPhysics());


}

PhysicsList::~PhysicsList()
{
    ;
}


void PhysicsList::ConstructParticle()
{
    // Call parent method. Replace it, if required
    G4VModularPhysicsList::ConstructParticle();
}

void PhysicsList::ConstructProcess()
{
    // Call parent method. Replace it, if required
    G4VModularPhysicsList::ConstructProcess();
}

void PhysicsList::SetCuts()
{
    // The method SetCuts() is mandatory in the interface. Here, one just use
    // the default SetCuts() provided by the base class.
    // Call parent method. Replace it, if required
    G4VUserPhysicsList::SetCuts();
    SetCutValue(0.11*mm,"e-");

}
