#include "game.hpp"

void game::UpdatePlayer(Player& player, std::vector<EnvItem>& envItems, float delta)
{
	if (IsKeyDown(KEY_LEFT)) {
		player.position.x -= PLAYER_HOR_SPD * delta;
	}

	if (IsKeyDown(KEY_RIGHT)) {
		player.position.x += PLAYER_HOR_SPD * delta;
	}

	if (IsKeyDown(KEY_SPACE) && player.canJump) {
		player.speed = -PLAYER_JUMP_SPD;
		player.canJump = false;
	}

	bool hitObstacle = false;
	for (int i = 0; i < envItems.size(); i++)
	{
		auto& ei = envItems.at(i);
		auto p = player.position;
		if (ei.blocking &&
			ei.rect.x <= p.x &&
			ei.rect.x + ei.rect.width >= p.x &&
			ei.rect.y >= p.y &&
			ei.rect.y <= p.y + player.speed * delta)
		{
			hitObstacle = true;
			player.speed = 0.0f;
			p.y = ei.rect.y;
			break;
		}
	}

	if (!hitObstacle)
	{
		player.position.y += player.speed * delta;
		player.speed += G * delta;
		player.canJump = false;
	}
	else
		player.canJump = true;
}