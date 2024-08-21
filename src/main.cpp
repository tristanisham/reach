#include "raylib.h"
#include "raymath.h"
#include "game.hpp"
#include <vector>
#include <iostream>

constexpr auto WINDOW_TITLE = "Cope";

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);

    game::Player player{Vector2{400, 280}, 0, false};
     
    std::vector<game::EnvItem> envItems = {
        {{0, 0, 1000, 400}, false, LIGHTGRAY},
        {{0, 400, 1000, 200}, true, GRAY},
        {{300, 200, 400, 10}, true, GRAY},
        {{250, 300, 100, 10}, true, GRAY},
        {{650, 300, 100, 10}, true, GRAY}};

    Camera2D camera{};
    camera.target = player.position;
    camera.offset = Vector2{SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f};
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    // Store the camera update functions in a vector
    std::vector<game::CameraUpdater> cameraUpdaters = {
        game::UpdateCameraCenter,
        game::UpdateCameraCenterInsideMap,
        game::UpdateCameraCenterSmoothFollow,
        game::UpdateCameraEvenOutOnLanding,
        game::UpdateCameraPlayerBoundsPush};

    int cameraOption = 0;

    std::vector<std::string> cameraDescriptions = {
        "Follow player center",
        "Follow player center, but clamp to map edges",
        "Follow player center; smoothed",
        "Follow player center horizontally; update player center vertically after landing",
        "Player push camera on getting too close to screen edge"};

    SetTargetFPS(60);

    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) {
        // Update
        //----------------------------------------------------------------------------------
        float deltaTime = GetFrameTime();

        game::UpdatePlayer(player, envItems, deltaTime);

        camera.zoom += ((float)GetMouseWheelMove() * 0.05f);

        if (camera.zoom > 3.0f)
            camera.zoom = 3.0f;
        else if (camera.zoom < 0.25f)
            camera.zoom = 0.25f;

        if (IsKeyPressed(KEY_R)) {
            camera.zoom = 1.0f;
            player.position = Vector2{400, 280};
        }

        if (IsKeyPressed(KEY_C)) {
            cameraOption = (cameraOption + 1) % cameraUpdaters.size();
        }

        // Call update camera function by its pointer
        cameraUpdaters[cameraOption](camera, player, envItems, deltaTime, SCREEN_WIDTH, SCREEN_HEIGHT);
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(LIGHTGRAY);

        BeginMode2D(camera);

        for (int i = 0; i < envItems.size(); i++)
        {
            DrawRectangleRec(envItems[i].rect, envItems[i].color);
        }

        Rectangle playerRect = {player.position.x - 20, player.position.y - 40, 40.0f, 40.0f};
        DrawRectangleRec(playerRect, RED);

        DrawCircleV(player.position, 5.0f, GOLD);

        EndMode2D();

        DrawText("Controls:", 20, 20, 10, BLACK);
        DrawText("- Right/Left to move", 40, 40, 10, DARKGRAY);
        DrawText("- Space to jump", 40, 60, 10, DARKGRAY);
        DrawText("- Mouse Wheel to Zoom in-out, R to reset zoom", 40, 80, 10, DARKGRAY);
        DrawText("- C to change camera mode", 40, 100, 10, DARKGRAY);
        DrawText("- R to reset player position", 40, 120, 10, DARKGRAY);
        DrawText("Current camera mode:", 20, 140, 10, BLACK);
        DrawText(cameraDescriptions[cameraOption].c_str(), 40, 160, 10, DARKGRAY);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}