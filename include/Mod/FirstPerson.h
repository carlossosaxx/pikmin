#ifndef _MOD_FIRSTPERSON_H
#define _MOD_FIRSTPERSON_H

#include "types.h"

/**
 * @brief First-person camera mod. Only compiled in with `configure.py --mod-first-person`,
 * so the default build still matches the original game.
 *
 * Controls while first person is on (toggle with D-pad Up):
 *  - Main stick: walk / strafe relative to where you are looking.
 *  - C-stick: look around (yaw and pitch).
 *  - Hold Z + C-stick: move the swarm, as the C-stick normally does.
 *  - The cursor sits on the ground where you are looking, so throws and whistles go there.
 */
#ifndef MOD_FIRSTPERSON
#define MOD_FIRSTPERSON 0
#endif

#if MOD_FIRSTPERSON

class Controller;

namespace ModFP {

// Tunables. Units are game units (Olimar's collision size is 20) and radians.
static const f32 EyeHeight      = 28.0f; // eye height above Olimar's feet
static const f32 EyeForward     = 6.0f;  // push the eye slightly in front of the helmet
static const f32 LookDistance   = 100.0f;
static const f32 YawSpeed       = 2.6f;  // radians per second at full C-stick
static const f32 PitchSpeed     = 1.8f;
static const f32 MinPitch       = -1.35f; // about 77 degrees down
static const f32 MaxPitch       = 1.0f;   // about 57 degrees up
static const f32 Fov            = 70.0f;
static const f32 MinCursorDist  = 30.0f;
static const f32 StickDeadZone  = 0.1f;

extern bool sEnabled;  // player has first person switched on
extern bool sIsActive; // first person drove the camera this frame (false during cutscenes etc.)
extern f32 sYaw;       // look direction around Y, same convention as Creature::mFaceDirection
extern f32 sPitch;     // positive looks up

// Reads the toggle and the C-stick look input. Called by the camera once per frame.
void updateLook(Controller& controller, f32 frameTime);

// True when the C-stick should be read as look input instead of moving the swarm.
bool cStickIsLook(Controller& controller);

} // namespace ModFP

#endif

#endif
