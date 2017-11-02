/// \file PrimaryGeneratorAction.hh
/// \brief Implementation of the PrimaryGeneratorAction class

#include "PrimaryGeneratorAction.hh"
#include "G4ParticleDefinition.hh"
#include "G4RandomDirection.hh"
#include <G4ParticleTable.hh>
#include <G4SystemOfUnits.hh>
#include <G4ParticleGun.hh>
#include <Randomize.hh>
#include <G4Event.hh>



PrimaryGeneratorAction::PrimaryGeneratorAction() :
  G4VUserPrimaryGeneratorAction()
{
// Set the basic properties of particles to be produced.
// number of particles

G4int n_particle = 1;

fGun = new G4ParticleGun(n_particle);

// Set the particle
G4ParticleDefinition* myParticle = G4ParticleTable::GetParticleTable()->FindParticle("gamma");

fGun->SetParticleDefinition(myParticle);

// Set particle's energy
fGun->SetParticleEnergy(511*keV);

// Set particle position & direction
fGun->SetParticlePosition(G4ThreeVector(0,0,0));
fGun->SetParticleMomentumDirection(G4RandomDirection());


}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
delete fGun;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
// set the vertex properties of the particle
//Bakc-to-Back 2-gamma in fixed angular region


G4ThreeVector dir(1.,1.,1.);

G4double Phi = 2*3.1414*G4UniformRand();
//G4double cosTheta = -1. + 2. * G4UniformRand();
G4double cosTheta = -1. + 2. * G4UniformRand();
G4double sinTheta = sqrt(1. - cosTheta *cosTheta);

G4double xMom0 = sinTheta * cos(Phi);
G4double yMom0 = sinTheta * sin(Phi);
G4double zMom0 = cosTheta;


for(int i=0; i<1; i++)    //increase loop on i for two
    {
        if(i==0)
        {


//Set vertex position
            fGun->SetParticlePosition(G4ThreeVector(0.*cm,0.*cm,0.*cm));

            dir.setX(xMom0);
            dir.setY(yMom0);
            dir.setZ(zMom0);

//Set vertex momentum direction

            fGun->SetParticleMomentumDirection(dir);

// Intentiate first event
            fGun->GeneratePrimaryVertex(anEvent);


        }
        if(i==1)
        {
//Set vertex position
            fGun->SetParticlePosition(G4ThreeVector(0.*cm,0.*cm,0.*cm));

            dir.setX(-1*xMom0);
            dir.setY(-1*yMom0);
            dir.setZ(-1*zMom0);
//Set vertex momentum direction
            fGun->SetParticleMomentumDirection(dir);
// Intentiate second event
            fGun->GeneratePrimaryVertex(anEvent);

        }
    }

}
