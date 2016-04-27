//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
/// \file electromagnetic/TestEm5/src/StackingAction.cc
/// \brief Implementation of the StackingAction class
//
// $Id: StackingAction.cc 88674 2015-03-05 08:29:46Z gcosmo $
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "StackingAction.hh"

#include "HistoManager.hh"

#include "G4Track.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

StackingAction::StackingAction()
 : G4UserStackingAction()
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

StackingAction::~StackingAction()
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "G4ParticleTypes.hh"

#include "G4VProcess.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"

G4ClassificationOfNewTrack
StackingAction::ClassifyNewTrack(const G4Track* track)
{

	G4ParticleDefinition* particle =track->GetDefinition();
	G4double energy = track->GetKineticEnergy();
	G4double shield = 1. *keV;

	//判断粒子是否为gamma光子且来自于放射性衰变产生的
	//如果是，保存gamma离散谱，作为初始gamma源。
	const G4VProcess* creatorProcess = track->GetCreatorProcess();
	if(creatorProcess)
	{
	if(creatorProcess->GetProcessName() == "RadioactiveDecay" && particle == G4Gamma::Gamma() )
	{
			G4AnalysisManager::Instance()->FillH1(1,energy/MeV);
	}
	}
	if(track->GetTrackID() == 1 && particle == G4Gamma::Gamma())
	{
			G4AnalysisManager::Instance()->FillH1(1,energy/MeV);
	}

 return fUrgent; 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
