#ifndef _MOD_FIRSTPERSON_H
#define _MOD_FIRSTPERSON_H

#include "types.h"

/**
 * @brief First-person camera mod. Only compiled in with `configure.py --mod-first-person`,
 * so the default build still matches the original game.
 *
 * Controls while first person is on (each player toggles their own with D-pad Up):
 *  - Main stick: walk / strafe relative to where you are looking.
 *  - C-stick: look around (yaw and pitch).
 *  - Hold Z + C-stick: move the swarm, as the C-stick normally does.
 *  - L: snap the view to where Olimar is facing.
 *  - The cursor sits on the ground where you are looking, so throws and whistles go there.
 */
#ifndef MOD_FIRSTPERSON
#define MOD_FIRSTPERSON 0
#endif

#if MOD_FIRSTPERSON

class Controller;
class Creature;
class PcamCamera;

namespace ModFP {

// Tunables. Units are game units (Olimar's collision size is 20) and radians.
static const f32 EyeHeight     = 28.0f; // eye height above Olimar's feet
static const f32 EyeForward    = 6.0f;  // push the eye slightly in front of the helmet
static const f32 LookDistance  = 100.0f;
static const f32 YawSpeed      = 2.6f; // radians per second at full C-stick
static const f32 PitchSpeed    = 1.8f;
static const f32 MinPitch      = -1.35f; // about 77 degrees down
static const f32 MaxPitch      = 1.0f;   // about 57 degrees up
static const f32 Fov           = 70.0f;
static const f32 NearClip      = 8.0f; // the game normally uses 100, which would cut off everything near your face
static const f32 MinCursorDist = 30.0f;
static const f32 StickDeadZone = 0.1f;
static const int MaxViews      = 2; // one per player

/**
 * @brief One player's first-person view.
 */
struct View {
	bool mEnabled;  // player has first person switched on
	bool mIsActive; // first person drove this camera this frame (false during cutscenes etc.)
	f32 mYaw;       // look direction around Y, same convention as Creature::mFaceDirection
	f32 mPitch;     // positive looks up
};

extern View sViews[MaxViews];
extern View* sRenderView; // the view being drawn right now (split screen draws each in turn)

// The view a game camera drives: player 1's camera, or player 2's in co-op split screen.
View& getView(PcamCamera* camera);

// The active first-person view looking out of this navi's eyes, or nullptr.
View* getActiveViewFor(Creature* navi);

// Reads the toggle and the C-stick look input. Called by each camera once per frame.
void updateLook(View& view, Controller& controller, f32 frameTime);

// True when the C-stick should be read as look input instead of moving the swarm.
bool cStickIsLook(Controller& controller);

// True when any view being drawn is first person, so the near clip plane must come in.
bool needsNearClip();

} // namespace ModFP

#endif

#endif
