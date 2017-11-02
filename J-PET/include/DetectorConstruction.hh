/// \file DetectorConstruction.hh
/// \brief Definition of the DetectorConstruction class (Mandatory)

#ifndef DETECTOR_CONSTRUCTION_HH
#define DETECTOR_CONSTRUCTION_HH

#include <G4VUserDetectorConstruction.hh>



/// Detector construction class to define materials (with their physical properties) and detector geometry.
class DetectorConstruction : public G4VUserDetectorConstruction
{
public:
  /// constructor
  DetectorConstruction();
  /// destructor
  virtual ~DetectorConstruction();

  // Defines the detector geometry and returns a pointer to the physical World Volume
  G4VPhysicalVolume* Construct() override;
  
  // Register some of the detector's volumes as "sensitive"

  // Add the following, if you have fields / sensitive detectors
  void ConstructSDandField() override;



};

#endif
