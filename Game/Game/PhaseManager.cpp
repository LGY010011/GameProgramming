/*
// PhaseManager.cpp
#include "Game.h"

void PhaseManager::AddPhase(GamePhase phase, PhaseInterface* phaseInstance) {
    phases[phase] = phaseInstance;
}

void PhaseManager::SetPhase(GamePhase phase) {
    auto it = phases.find(phase);
    if (it != phases.end()) {
        currentPhase = it->second;
    }
}

void PhaseManager::HandleEvents() {
    if (currentPhase) {
        currentPhase->HandleEvents();
    }
}

void PhaseManager::Update() {
    if (currentPhase) {
        currentPhase->Update();
    }
}

void PhaseManager::Render() {
    if (currentPhase) {
        currentPhase->Render();
    }
}
*/