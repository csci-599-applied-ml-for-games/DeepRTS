//
// Created by Per-Arne on 23.02.2017.
//

#ifndef WARC2SIM_GAME_H
#define WARC2SIM_GAME_H

#include <memory>
#include <map>
#include <unordered_map>
#include <iostream>


#include "player/Player.h"
#include "environment/Tilemap.h"
#include "action/BaseAction.h"
#include "logging/LogGame.h"
#include <chrono>


class Game {

    /// List of Game instances
    static std::unordered_map<int, Game *> games;

    /// Game Clock
    std::chrono::high_resolution_clock::time_point now;
    std::chrono::high_resolution_clock::time_point _update_next;
    std::chrono::high_resolution_clock::time_point _render_next;
    std::chrono::high_resolution_clock::time_point _stats_next;

    std::chrono::nanoseconds _update_interval;
    std::chrono::nanoseconds _render_interval;

    uint32_t _update_delta = 0;
    uint32_t _render_delta = 0;

    /// Game Tilemap
    Tilemap map;

    /// Spawn a player
    void spawnPlayer(Player & player);

    /// Initialize the game clock timers
    void timerInit();


    bool running;

	int state_environment_idx;
	int state_unit_player_idx;
	int state_unit_health_idx;
	int state_unit_type_idx;
    std::vector<std::vector<float>> state;



public:
    // Retrieve game via Game ID
    static Game * getGame(uint8_t id);

    /// Game Constructor
    Game();

    ////////////////////////////////////////////////////
    ///
    /// Properties
    ///
    ////////////////////////////////////////////////////

    /// Game State Manager
    StateManager stateManager;

    /// List of Players inside the game session
    std::vector<Player> players;

    /// List of Units inside the game session
    std::vector<Unit> units;

    /// Game Identification
    uint8_t id;

    /// Game Episode Ticks
    uint64_t ticks = 0;

    /// Game Episode
    uint16_t episode = 1;

    /// Bool that determine print of FPS and UPS in console
    bool consoleCaptionEnabled = true;

    /// Game Max FPS
	uint32_t max_fps;

    /// Game Max UPS
	uint32_t max_ups;

    /// Game Current FPS
    uint32_t currentFPS = 0;

    /// Game Current UPS
    uint32_t currentUPS = 0;


    /// Game terminal flag
    bool terminal;


    ////////////////////////////////////////////////////
    ///
    /// Getters
    ///
    ////////////////////////////////////////////////////

    /// Get the Game Tilemap
    Tilemap & getMap();

    // Get the Game state matrix
    std::vector<std::vector<float>> getState();

    /// Get a Unit via index
    Unit &getUnit(uint16_t idx);

    uint32_t getMaxFPS() const;

    uint32_t getMaxUPS() const;

    uint32_t getFPS() const;

    uint32_t getUPS() const;

    uint64_t getGameDuration() const;

    uint64_t getTicks() const ;

    size_t getWidth() const;

    size_t getHeight() const;

    uint16_t getEpisode() const;

    uint8_t getId() const;

    ////////////////////////////////////////////////////
    ///
    /// Setters
    ///
    ////////////////////////////////////////////////////

    /// Set the Game FPS
    void setMaxFPS(uint32_t fps_);

    /// Set the Game UPS
    void setMaxUPS(uint32_t ups_);


    ////////////////////////////////////////////////////
    ///
    /// Engine Functions
    ///
    ////////////////////////////////////////////////////

    // Add a player to the game
    Player *addPlayer();

    /// Game Tick Function
    void tick();

    /// Game Update Function
    void update();

    /// Game Render Function
    void render();

    /// Game
    virtual void _render();

    /// Print the Game Statistics
    void caption();

    // Enables the running flag and updates the clock
    void start();

    // Disables the running flag
    void stop();

    // Resets the game
    void reset();

    // Returns true if the game is in an terminal state
    bool isTerminal();

};


#endif //WARC2SIM_GAME_H
