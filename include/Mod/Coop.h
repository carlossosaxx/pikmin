#ifndef _MOD_COOP_H
#define _MOD_COOP_H

#include "types.h"

/**
 * @brief Two-player co-op mod. Only compiled in with `configure.py --mod-coop`,
 * so the default build still matches the original game.
 *
 * Player 2 is a second Olimar on controller port 2, built on the 2-player code the
 * original game left unfinished (see GenObjectNavi and flowCont.mIsVersusMode).
 * Versus mode stays off, so both players' Pikmin are on the same side.
 *
 * Split screen is on by default: player 1 on the top half, player 2 on the bottom, each
 * with their own camera. Player 1 presses D-pad Right to switch to one shared camera that
 * keeps both players in frame (D-pad Down is taken by the original game).
 *
 * If player 2 goes down they drop their Pikmin and get back up at the ship a moment later;
 * only player 1 going down ends the day, as in the original. Player 2 is tinted green and
 * has their own health bar on screen.
 *
 * Online play needs no code: two Dolphin users running this same build over
 * Dolphin NetPlay each drive one controller port.
 */
#ifndef MOD_COOP
#define MOD_COOP 0
#endif

#if MOD_COOP

class Camera;
class Controller;
class Graphics;
class Navi;
class PcamCamera;

namespace ModCoop {

static const int NaviCount       = 2;
static const f32 SpawnSideOffset = 40.0f; // how far beside player 1 player 2 starts each day

// Player 2's tint (out of 255 per channel), a green-ish suit so the two Olimars look different.
static const int Player2TintR = 150;
static const int Player2TintG = 255;
static const int Player2TintB = 150;

extern Navi* sPlayer2;
extern Camera* sCamera2;     // player 2's own game camera, used in split screen
extern PcamCamera* sPcam2;   // drives sCamera2, following player 2
extern bool sSplitScreen;    // players chose split screen (vs one shared camera)
extern bool sIsSplitFrame;   // this frame is being drawn split (false during cutscenes)

// Puts player 2 on the ground beside player 1, facing the same way.
void placePlayer2BesidePlayer1(Navi* player1);

// After being downed: back on their feet at the ship (or beside player 1), at full health.
void respawnPlayer2();

// Player 2's health bar, in their half of the screen (or a corner when sharing a camera).
void drawPlayer2Hud(Graphics& gfx);

// Multiplies player 2's model colours by a tint so the two Olimars can be told apart.
// Call with apply = true before drawing player 2, then false to put the colours back.
void tintPlayer2(Navi* navi, bool apply);

// Per-frame: reads the split-screen toggle and points player 2's controls at the right camera.
void update(Controller& player1Controller, Camera* sharedCamera);

} // namespace ModCoop

#endif

#endif
