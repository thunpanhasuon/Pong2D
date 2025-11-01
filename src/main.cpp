#include <raylib.h>
#include <iostream>

int player_score = 0; 
int ai_score = 0; 

class Ball {
public: 
	float x, y; 
	float speed_x, speed_y;
	float radius; 

	void ResetBall() {
		x = GetScreenWidth() / 2; 
		y = GetScreenHeight() /2; 
		int random_speed[2] = {-1, 1}; 
		speed_x *= random_speed[GetRandomValue(0, 1)];
		speed_y *= random_speed[GetRandomValue(0, 1)];
		
	}
	void Draw() {
		DrawCircle(x, y, radius, YELLOW);
	}
	void Update() {
		x += speed_x; 
		y += speed_y; 

		if (y + radius >= GetScreenHeight() || y - radius <= 0) {
			speed_y *= -1; 
		}

		if (x + radius >= GetScreenWidth()) {
			player_score++; 
			ResetBall();
		}
		if ( x - radius <= 0 ) {
                        ai_score++;
			ResetBall();
		}
	}
};
class Paddle {
protected:
	void LimitMovement() {
		if (y <= 0) {
			y = 0; 
		}
		if (y + height >= GetScreenHeight()) {
			y = GetScreenHeight() - height;
		}

	}
public: 
	float x, y; 
	float width, height; 
	float speed; 

	void Draw() {
		DrawRectangle(x, y, width, height, WHITE);
	}
	void Update() {
		if (IsKeyDown(KEY_UP)) {
			y = y - speed; 
		}
		if (IsKeyDown(KEY_DOWN)) {
			y = y + speed; 
		}
		LimitMovement();
	}
	
};
class AiPaddle: public Paddle {

	public: 
	void Update(int ball_y) {

		if (y + height / 2 <= ball_y) {
			y = y + speed;
		}
		if (y + height /2 >= ball_y) {
			y = y - speed; 
		}
		LimitMovement();
	}
};

Ball ball; 
Paddle player; 
AiPaddle ai; 

int main() {
	const int window_width = 1280; 
	const int window_height = 800;

	InitWindow(window_width, window_height, "Pong 2D");

	SetTargetFPS(60);

	ball.x = window_width / 2; 
	ball.y = window_height /2; 
	ball.radius = 20; 
	ball.speed_x = 7; 
	ball.speed_y = 7; 

	player.x = 10; 
	player.y = window_height/2 - 60;
	player.width = 20;
	player.height = 150; 
	player.speed = 6; 

	ai.x = window_width - 40;
	ai.y = window_height / 2 - 60;
	ai.width = 20; 
	ai.height = 150;
	ai.speed = 6;

	while(!WindowShouldClose()) {
		BeginDrawing(); 
		ClearBackground(BLACK);
		/* update */
		ball.Update(); 
		player.Update();
		ai.Update(ball.y);
		/* physic */
		if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle {player.x, player.y, player.width, player.height})) {
			ball.speed_x *= -1;
		}
		if (CheckCollisionCircleRec(Vector2 {ball.x, ball.y}, ball.radius, Rectangle {ai.x, ai.y, ai.width, ai.height})) {
			ball.speed_x *= -1;
		}
		
		/* rendering */
		DrawLine(window_width /2, 0, window_width/2, window_height, WHITE);
		DrawCircle(window_width / 2, window_height / 2, 100, WHITE);
		ball.Draw(); 
		player.Draw();	
		ai.Draw();

		DrawText(TextFormat("%i ", player_score), window_width / 4 - 20, 20, 80, WHITE);
                DrawText(TextFormat("%i", ai_score), 3 * window_width / 4 - 20, 20, 80, WHITE);

		EndDrawing(); 
	}
	CloseWindow();

}
