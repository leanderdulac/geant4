// This code implementation is the intellectual property of
// the GEANT4 collaboration.
//
// By copying, distributing or modifying the Program (or any work
// based on the Program) you indicate your acceptance of this statement,
// and all its terms.
//
// $Id: G4EnergyLossMessenger.cc,v 1.2.6.1 1999/12/07 20:50:56 gunter Exp $
// GEANT4 tag $Name: geant4-01-00 $
//
// 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#include "G4EnergyLossMessenger.hh"

#include "G4eEnergyLoss.hh"
#include "G4hEnergyLoss.hh"
#include "G4eEnergyLossPlus.hh"
#include "G4hEnergyLossPlus.hh"

#include "G4UIcommand.hh"
#include "G4UIparameter.hh"
#include "G4UIcmdWithABool.hh"

#ifdef WIN32
#  include <Strstrea.h>
#else
#  include <strstream.h>
#endif

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

G4EnergyLossMessenger::G4EnergyLossMessenger()
{       
  RndmStepCmd = new G4UIcmdWithABool("/process/eLoss/rndmStep",this);
  RndmStepCmd->SetGuidance("Randomize the proposed step for eLoss.");
  RndmStepCmd->SetParameterName("choice",true);
  RndmStepCmd->SetDefaultValue(false);
  RndmStepCmd->AvailableForStates(Idle);
  
  EnlossFlucCmd = new G4UIcmdWithABool("/process/eLoss/fluct",this);
  EnlossFlucCmd->SetGuidance("Switch on/off the energy loss fluctuation.");
  EnlossFlucCmd->SetParameterName("choice",true);
  EnlossFlucCmd->SetDefaultValue(true);
  EnlossFlucCmd->AvailableForStates(Idle);

  StepFuncCmd = new G4UIcommand("/process/eLoss/StepFunction",this);
  StepFuncCmd->SetGuidance("Set the energy loss step limitation parameters.");
  StepFuncCmd->SetGuidance("  dRoverR   : max Range variation per step");
  StepFuncCmd->SetGuidance("  finalRange: range for final step");
  G4UIparameter* dRoverRPrm = new G4UIparameter("dRoverR",'d',false);
  dRoverRPrm->SetGuidance("max Range variation per step (fractional number)");
  dRoverRPrm->SetParameterRange("dRoverR>0. && dRoverR<=1.");
  StepFuncCmd->SetParameter(dRoverRPrm);
  G4UIparameter* finalRangePrm = new G4UIparameter("finalRange",'d',false);
  finalRangePrm->SetGuidance("range for final step");
  finalRangePrm->SetParameterRange("finalRange>0.");
  StepFuncCmd->SetParameter(finalRangePrm);
  G4UIparameter* unitPrm = new G4UIparameter("unit",'s',true);
  unitPrm->SetGuidance("unit of finalRange");
  unitPrm->SetDefaultValue("mm");
  G4String unitCandidates = G4UIcommand::UnitsList(G4UIcommand::CategoryOf("mm"));
  unitPrm->SetParameterCandidates(unitCandidates);
  StepFuncCmd->SetParameter(unitPrm);
  StepFuncCmd->AvailableForStates(Idle);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

G4EnergyLossMessenger::~G4EnergyLossMessenger()
{
  delete RndmStepCmd;
  delete EnlossFlucCmd;
  delete StepFuncCmd;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void G4EnergyLossMessenger::SetNewValue(G4UIcommand* command,G4String newValue)
{ 
  if (command == RndmStepCmd)
   { G4eEnergyLoss::SetRndmStep(RndmStepCmd->GetNewBoolValue(newValue));
     G4hEnergyLoss::SetRndmStep(RndmStepCmd->GetNewBoolValue(newValue));
     G4eEnergyLossPlus::SetRndmStep(RndmStepCmd->GetNewBoolValue(newValue));
     G4hEnergyLossPlus::SetRndmStep(RndmStepCmd->GetNewBoolValue(newValue));
   }
   
  if (command == EnlossFlucCmd)
   { G4eEnergyLoss::SetEnlossFluc(EnlossFlucCmd->GetNewBoolValue(newValue));
     G4hEnergyLoss::SetEnlossFluc(EnlossFlucCmd->GetNewBoolValue(newValue));
     G4eEnergyLossPlus::SetEnlossFluc(EnlossFlucCmd->GetNewBoolValue(newValue));
     G4hEnergyLossPlus::SetEnlossFluc(EnlossFlucCmd->GetNewBoolValue(newValue)); 
   }

  if (command == StepFuncCmd)
   {
     G4double v1,v2;
     char unts[30];
     const char* t = newValue;
     istrstream is((char*)t);
     is >> v1 >> v2 >> unts;
     G4String unt = unts;
     v2 *= G4UIcommand::ValueOf(unt);
     G4eEnergyLoss::SetStepFunction(v1,v2);
     G4hEnergyLoss::SetStepFunction(v1,v2);
     G4eEnergyLossPlus::SetStepFunction(v1,v2);
     G4hEnergyLossPlus::SetStepFunction(v1,v2);    
   }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....