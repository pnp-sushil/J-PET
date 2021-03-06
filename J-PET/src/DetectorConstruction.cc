// \file DetectorConstruction.cc
/// \brief Implementation of the DetectorConstruction class
#include "DetectorConstruction.hh"

#include "G4RotationMatrix.hh"
#include "G4LogicalVolume.hh"
#include "G4VisAttributes.hh"
#include "G4SystemOfUnits.hh"

#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include "G4Transform3D.hh"
#include "G4UnitsTable.hh"
#include "G4Material.hh"
#include "G4Colour.hh"
#include "G4Box.hh"


#include "G4MultiFunctionalDetector.hh"
#include <G4VSensitiveDetector.hh>
#include <G4SDManager.hh>
#include "SensitiveSD.hh"

#include <sstream>





DetectorConstruction::DetectorConstruction() :
    G4VUserDetectorConstruction()
{;}

DetectorConstruction::~DetectorConstruction()
{;}


G4VPhysicalVolume* DetectorConstruction::Construct()
{

    G4bool checkOverlaps = true;
    static const double Pi = 3.14159265358979323846;

    G4NistManager* nist = G4NistManager::Instance();

// Define material for world , J-PET FRAME , Scintillator ----
    G4Material* World_material = nist->FindOrBuildMaterial("G4_AIR");
    G4Material* Frame_material = nist->FindOrBuildMaterial("G4_AIR");
    G4Material* Cryst_material = nist->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE");


// J-PET characteristics--------------------------------------
    G4double World_sizeX,  World_sizeY,  World_sizeZ;
    World_sizeX = World_sizeY = World_sizeZ = 85.*cm;

    G4Box* solidWorld            = new G4Box("World",World_sizeX, World_sizeY, World_sizeZ);
    G4LogicalVolume  *logicWorld = new G4LogicalVolume(solidWorld, World_material, "World");
                                    //solid ptr, material, its Name
    G4VPhysicalVolume* physWorld = new G4PVPlacement(0,G4ThreeVector(),logicWorld,"World",0,false,0,checkOverlaps);
                                   //no rotation, at(0,0,0), logical_vol, Name, mother_vol,boolean_ope,copy,overlap check

    G4VisAttributes* WorVisAtt= new G4VisAttributes(G4Colour(0.,1.,0.));
    WorVisAtt->SetForceWireframe(true);

    //--------------------- World encapsulates -----------------------------

    G4double Frame_sizeX,  Frame_sizeY,  Frame_sizeZ;
    Frame_sizeX = Frame_sizeY = Frame_sizeZ =70.*cm;

    G4Box*   Frame              = new G4Box("Frame_Al", Frame_sizeX, Frame_sizeY, Frame_sizeZ);

    G4LogicalVolume* logicFrame = new G4LogicalVolume(Frame, Frame_material, "Frame_Al");

    new G4PVPlacement(0, G4ThreeVector(), logicFrame, "Frame_Al", logicWorld, false, 0, checkOverlaps);
    //no rotation, at(0,0,0), logical_vol, Name, mother_vol,boolean_ope,copy,overlap check

    G4VisAttributes* EnvVisAtt= new G4VisAttributes(G4Colour(1.,0.,0.));
    EnvVisAtt->SetForceWireframe(true);
    logicFrame->SetVisAttributes(EnvVisAtt);



    G4double Cryst_sizeX = 1.9*cm,
             Cryst_sizeY = 0.7*cm,
             Cryst_sizeZ = 50.*cm;


    G4int    Nsegments[3]= {48,48,96};

    G4double Radius, Phi;
    G4int    ScintId=0;

    G4Box* Crystal               = new G4Box("Scintillator",Cryst_sizeX/2, Cryst_sizeY/2, Cryst_sizeZ/2);
        G4LogicalVolume* logicCrystal= new G4LogicalVolume(Crystal, Cryst_material, "Scintillator");

    for(int i=0 ; i<193; i++)
    {
        //Layer1
        if(i < 48)
        {
            Phi = i*2*Pi/Nsegments[0];
            Radius = 42.5*cm;
        }
        //Layer2
        if(i > 47 && i < 96)
        {
            Phi = i*2*Pi/Nsegments[1]+0.06544985;
            Radius = 46.75*cm;
         }
         //Layer3
        if(i > 95 )
        {
            Phi = i*2*Pi/Nsegments[2]+0.032724923;
            Radius = 57.50*cm;
        }




        G4RotationMatrix rot = G4RotationMatrix();

        rot.rotateZ(Phi);

        G4ThreeVector loc = G4ThreeVector(Radius*(cos(Phi)),Radius*(sin(Phi)),0.0);

        G4Transform3D transform(rot,loc);

        ScintId = i+1;

        new G4PVPlacement(transform,logicCrystal, "Scintillator", logicFrame, false, ScintId, checkOverlaps);


    }

    return physWorld;
}


// Implement the following for sensitive detector
void DetectorConstruction::ConstructSDandField()
{
 G4SDManager* sdManager = G4SDManager::GetSDMpointer();
 sdManager->SetVerboseLevel(2);

 SensitiveSD* myDetector = new SensitiveSD("Scintillator");
 SetSensitiveDetector("Scintillator", myDetector);
 sdManager->AddNewDetector(myDetector);
}
