#include "radMessenger.hh"

#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithABool.hh"

#include "radDetectorConstruction.hh"
#include "radEventAction.hh"
#include "radPrimaryGeneratorAction.hh"
#include "radSteppingAction.hh"

#include "G4UImanager.hh"
#include "G4RunManager.hh"

#include <iostream>

radMessenger::radMessenger(){
    /*  Initialize all the things it talks to to NULL */

    fDetCon       = NULL;
    fEvAct        = NULL;
    fPriGen       = NULL;
    fStepAct      = NULL;

    nrDetCmd = new G4UIcmdWithAnInteger("/rad/det/setNrRadialDetectors",this);
    nrDetCmd->SetGuidance("Set number of detectors in radial direction");
    nrDetCmd->SetParameterName("nrDet", false);

    gunEnergyCmd = new G4UIcmdWithADoubleAndUnit("/rad/gun/setGunEnergy",this);
    gunEnergyCmd->SetParameterName("gunEnergy", false);

    tgtMatCmd = new G4UIcmdWithAString("/rad/det/setTargetMaterial",this);
    tgtMatCmd->SetParameterName("tgtMat", false);

}

radMessenger::~radMessenger(){
  delete nrDetCmd;
  delete gunEnergyCmd;
  delete tgtMatCmd;
}


void radMessenger::SetNewValue(G4UIcommand* cmd, G4String newValue){

  if( cmd == nrDetCmd ){
    G4int val = nrDetCmd->GetNewIntValue(newValue);
    fDetCon -> SetNrDetectors( val );
  }else if( cmd == gunEnergyCmd ){
    G4double val = gunEnergyCmd->GetNewDoubleValue(newValue);
    fPriGen->SetGunEnergy( val );
  }else if( cmd == tgtMatCmd ){
    fDetCon->SetTargetMaterial( newValue );
  }else{
    G4cerr << __PRETTY_FUNCTION__
	   <<" what command are you talking about? "<<cmd<<" "<<newValue<<G4endl;
    exit(3);
  }

}