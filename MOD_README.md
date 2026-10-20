# Pikmin first person + co-op mod

This branch adds two optional mods to the Pikmin decomp. Each one only compiles in when you ask for it, and a normal build still produces the original game.

| Build option | What you get |
|---|---|
| `--mod-first-person` | A first-person camera from Olimar's eyes |
| `--mod-coop` | A second player on controller 2, with split screen |
| both | Co-op where each player can play in first person on their half of the screen |

**Status: untested prototype.** The code passes a compiler type check, but it has not been built with the real GameCube compiler or played yet. Expect to tune it.

## Build it

You need your own copy of Pikmin (USA Rev 1, game ID `GPIE01`). This repo contains no game files.

1. Install Python 3 and [ninja](https://github.com/ninja-build/ninja/releases) (`pip install ninja`).
2. In Dolphin, right-click Pikmin and choose Properties, then Filesystem. Right-click the disc and choose **Extract System Data**. Copy the extracted `sys/main.dol` to `orig/GPIE01_01/sys/main.dol` in this repo.
3. Configure with the mods you want:
   ```
   python configure.py --mod-first-person --mod-coop
   ```
4. Run `ninja`. The modded game code is written to `build/GPIE01_01/main.dol`.
5. In the same Filesystem view, right-click the disc and choose **Extract Entire Disc** into a new folder. Replace `sys/main.dol` in that folder with your built one.
6. Rebuild that folder into a disc image (`.iso`), for example with GCRebuilder or `wit`. A disc image works with Dolphin NetPlay, which needs the game in Dolphin's game list.

## Controls

### First person (each player has their own)

| Input | Action |
|---|---|
| D-pad Up | Turn first person on or off (on by default) |
| Main stick | Walk and strafe relative to where you look |
| C-stick | Look around |
| Z + C-stick | Move the swarm (what the C-stick normally does) |
| L | Snap the view to the way Olimar faces |
| A / B / whistle | As normal; the cursor sits on the ground where you look |

### Co-op

| Input | Action |
|---|---|
| Controller 2 | Player 2's Olimar, with the same controls as player 1 |
| D-pad Right (player 1) | Switch between split screen (on by default) and one shared camera that keeps both players in frame |

In split screen, player 1 is on the top half and player 2 is on the bottom. Cutscenes play full screen.

- Player 2 wears a green-tinted suit and has their own health bar, marked "2P". It sits in their half of the screen, or in the bottom-right corner on the shared camera.
- The HUD's squad count covers both players' Pikmin, and so do the day-end results. Pikmin following either player are safe at sunset.
- If player 2 goes down, they drop their Pikmin and fall over, then get back up in front of the ship at full health. Only player 1 going down ends the day, as in the original game.

## Play online with Dolphin NetPlay

The mod needs no netcode. Dolphin NetPlay runs the same game on both computers and shares controller inputs, so a friend's controller becomes controller 2 in your game.

Both players need:
- the same Dolphin version,
- the same modded disc image (send your friend the build instructions, or your patch, so they make the same image from their own copy of the game),
- the image added to Dolphin's game list.

Then:
1. **Host:** Tools, then Start NetPlay. On the Host tab, set Connection Type to **Traversal Server** (no port forwarding needed), pick the modded Pikmin, and click **Host**. Copy the **Host Code** shown and send it to your friend.
2. **Friend:** Tools, then Start NetPlay. On the Connect tab, choose Traversal Server, paste the Host Code, and click **Connect**.
3. **Host:** click **Assign Controller Ports**. Put yourself on GC port 1 and your friend on GC port 2.
4. Check that the game shows as matching for both of you, then click **Start**.

Tips:
- Split screen draws the world twice per frame. If it runs slowly, the host can raise the CPU clock override (Config, Advanced). It is a NetPlay sync setting, so it applies to both players.
- Use the host's save. NetPlay copies the host's memory card to the friend for the session.
- If the game desyncs, both players restart NetPlay from the same save.

## Known gaps

- Untested: the tint on player 2 assumes the game applies a material's colour when it draws the model. If the two Olimars still look identical, that assumption was wrong.
- First person needs tuning in play. Turn and look direction, eye height and look speed are set in `include/Mod/FirstPerson.h` (`YawSpeed`, `PitchSpeed`, `EyeHeight`).
- In first person, your own antenna light is switched off so it doesn't cover the view. In split screen, the other player won't see it either while you're in first person.
- Player 2 uses Olimar's model (Louie only exists from Pikmin 2), tinted.

Mod code lives in `include/Mod/` and in `#if MOD_FIRSTPERSON` / `#if MOD_COOP` blocks in `src/plugPikiNakata/pcamcamera.cpp`, `pcamcameramanager.cpp`, `src/plugPikiKando/navi.cpp`, `naviMgr.cpp`, `gameCoreSection.cpp` and `src/plugPikiColin/newPikiGame.cpp`.
