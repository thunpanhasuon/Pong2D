#include <raylib.h>
/* huzz is how many girl you got */
int rizzer_huzz = 0; 
int aislop_huzz = 0; 

class Baller {
public: 
	float xPosition, yPosition; 
	float xSpeed, ySpeed; 	
	int radius; 

	void letThemCook() {
		DrawCircle(xPosition, yPosition, radius, WHITE);
	}
	void noCapUpdate() {
		xPosition += xSpeed; 
		yPosition += ySpeed;

		if (yPosition + radius >= GetScreenHeight() || yPosition - radius <= 0) {
			ySpeed *= -1; 
		}

		if (xPosition + radius >= GetScreenWidth()) {
			rizzer_huzz++; 
			touchGrass();
		}
		if (xPosition - radius <= 0) {
			aislop_huzz++;
			touchGrass();
		}
	}
	
	void touchGrass() {
		xPosition = GetScreenWidth()/ 2; 
		yPosition = GetScreenHeight() /2 ;

		int randomize_wSpeed[2] = {-1, 1}; 

		xSpeed *= randomize_wSpeed[GetRandomValue(0, 1)];
		ySpeed *= randomize_wSpeed[GetRandomValue(0, 1)];

	}
};
class Brainroter {

protected: 
	void doomScrollLimit() {
		if (yPosition <= 0) {
			yPosition = 0;
		}
		if (yPosition + height >= GetScreenHeight()) {
			yPosition = GetScreenHeight() - height;
		}
	};
	
public:
	float xPosition, yPosition; 
	float width, height; 
	int speed; 

	void letThemCook() {
		DrawRectangle(xPosition, yPosition, width, height, WHITE);
	}
	void noCapUpdate() {
		if (IsKeyDown(KEY_UP)) {
			yPosition = yPosition - speed; 
		}
		if (IsKeyDown(KEY_DOWN)) {
			yPosition = yPosition + speed; 
		}
		doomScrollLimit(); 
	}
};
class InstagramBot: public Brainroter {
public: 
	void noCapUpdate(float ball_y) {
		if (yPosition + height / 2 > ball_y) {
			yPosition = yPosition - speed; 
		}
		if (yPosition + height / 2 < ball_y) {
			yPosition = yPosition + speed;
		}
		doomScrollLimit(); 

	}
};

Baller ball; 
Brainroter rizzler; 
InstagramBot aislop; 

int main() {
	
	const int scroll_portal_width = 1280; 
	const int scroll_protal_height = 720;  

	InitWindow(scroll_portal_width, scroll_protal_height, "2D Pong for genZer");
	SetTargetFPS(60);

	ball.xPosition = scroll_portal_width / 2.0f;
	ball.yPosition = scroll_protal_height / 2.0f;
	ball.xSpeed = 7.0f;
	ball.ySpeed = 7.0f;
	ball.radius = 10.0f; 

	rizzler.xPosition = 20;
	rizzler.yPosition = scroll_protal_height / 2.0f - 40.0f;
	rizzler.width = 15;
	rizzler.height = 150;
	rizzler.speed = 6;

	aislop.xPosition = scroll_portal_width - 35.0f;
	aislop.yPosition = scroll_protal_height / 2.0f - 40.0f;
	aislop.width = 15;
	aislop.height = 150;
	aislop.speed = 6;

	while(!WindowShouldClose()) {
		BeginDrawing(); 
		ClearBackground(BLACK);

		DrawLine(scroll_portal_width /2, 0, scroll_portal_width /2, scroll_protal_height, WHITE);
		ball.noCapUpdate();
		rizzler.noCapUpdate();
		aislop.noCapUpdate(ball.yPosition);

		bool noCapVibeCheck_for_Sigma = CheckCollisionCircleRec(Vector2{ball.xPosition, ball.yPosition}, ball.radius, 
						              Rectangle { rizzler.xPosition, rizzler.yPosition, rizzler.width, rizzler.height} );
		if (noCapVibeCheck_for_Sigma) {
			ball.xSpeed *= -1; 
		}

		bool noCapVibeCheck_for_AdrainEffoc67ahh24brianrot = CheckCollisionCircleRec(Vector2{ball.xPosition, ball.yPosition}, ball.radius, 
						              Rectangle { aislop.xPosition, aislop.yPosition, aislop.width, aislop.height} );

		if (noCapVibeCheck_for_AdrainEffoc67ahh24brianrot ) {
			ball.xSpeed *= -1; 
		}
		
		ball.letThemCook(); 
		rizzler.letThemCook(); 
		aislop.letThemCook();

                DrawText(TextFormat("%i ", rizzer_huzz), scroll_portal_width / 4 - 20, 20, 80, WHITE);
                DrawText(TextFormat("%i", aislop_huzz), 3 * scroll_portal_width / 4 - 20, 20, 80, WHITE);

		EndDrawing();
	}

	CloseWindow();
	return 0; 
}
