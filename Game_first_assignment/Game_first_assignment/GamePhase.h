#pragma once

// Game Phases
const int PHASE_INTRO = 0;
const int PHASE_STAGE = 1;
const int PHASE_ENDING = 2;


class PhaseInterface
{
public:
	PhaseInterface() {};

	virtual void HandleEvents() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void Reset() = 0;

};


extern int g_current_game_phase;
extern int g_prev_game_phase;