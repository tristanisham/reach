#pragma once
#include "raylib.h"
#include "raymath.h"
#include <functional>
#include <vector>

constexpr auto G = 400;
constexpr auto PLAYER_JUMP_SPD = 350.0f;
constexpr auto PLAYER_HOR_SPD = 200.0f;

constexpr auto SCREEN_WIDTH = 800;
constexpr auto SCREEN_HEIGHT = 450;

namespace game
{
    class Player
    {
    public:
        Vector2 position;
        float speed;
        bool canJump;

        Player(Vector2 pos, float speed, bool canJump)
            : position(pos), speed(speed), canJump(canJump) {};
    };

    struct EnvItem
    {
        Rectangle rect;
        bool blocking;
        Color color;
    };

    //----------------------------------------------------------------------------------
    // Module functions declaration
    //----------------------------------------------------------------------------------

    void UpdatePlayer(Player &player, std::vector<EnvItem> &envItems, float delta);
    void UpdateCameraCenter(Camera2D &camera, Player &player, std::vector<EnvItem> &envItems, float delta, int width, int height);
    void UpdateCameraCenterInsideMap(Camera2D &camera, Player &player, std::vector<EnvItem> &envItems, float delta, int width, int height);
    void UpdateCameraCenterSmoothFollow(Camera2D &camera, Player &player, std::vector<EnvItem> &envItems, float delta, int width, int height);
    void UpdateCameraEvenOutOnLanding(Camera2D &camera, Player &player, std::vector<EnvItem> &envItems, float delta, int width, int height);
    void UpdateCameraPlayerBoundsPush(Camera2D &camera, Player &player, std::vector<EnvItem> &envItems, float delta, int width, int height);

    // Define the function type
    using CameraUpdater = std::function<void(Camera2D &, Player &, std::vector<EnvItem> &, float, int, int)>;
}
