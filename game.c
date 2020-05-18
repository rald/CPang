#include "common.h"
#include "player.h"
#include "bubble.h"
#include "harpoon.h"

int main() {

	bool quit=false;

	glImage playerImage;
	glImage bubbleImages[4];
	glImage harpoonImages[2];

	GLuint playerTexture;
	GLuint bubbleTextures[4];
	GLuint harpoonTextures[2];

	glScreenInit(SCREEN_WIDTH,SCREEN_HEIGHT);
	glfwSetWindowTitle(GAME_TITLE);
	glfwSwapInterval(1);

	playerTexture=glLoadSprite(
			"images/player.tga",
			&playerImage,
			16,32,
			GL_NEAREST);

	bubbleTextures[0]=glLoadSprite(
			"images/bubble8x8.tga",
			&bubbleImages[0],
			8,8,
			GL_NEAREST);

	bubbleTextures[1]=glLoadSprite(
			"images/bubble16x16.tga",
			&bubbleImages[1],
			16,16,
			GL_NEAREST);

	bubbleTextures[2]=glLoadSprite(
			"images/bubble32x32.tga",
			&bubbleImages[2],
			32,32,
			GL_NEAREST);

	bubbleTextures[3]=glLoadSprite(
			"images/bubble64x64.tga",
			&bubbleImages[3],
			64,64,
			GL_NEAREST);

	harpoonTextures[0]=glLoadSprite(
			"images/spear.tga",
			&harpoonImages[0],
			16,16,
			GL_NEAREST);

	harpoonTextures[1]=glLoadSprite(
			"images/rope.tga",
			&harpoonImages[1],
			16,16,
			GL_NEAREST);

	Player *player=Player_New(
			playerImage,
			(SCREEN_WIDTH-playerImage.width)/2,
			SCREEN_HEIGHT-playerImage.height,
			4);

	Bubble *bubble=Bubble_New(
			bubbleImages,
			(SCREEN_WIDTH-bubbleImages[3].width)/2,
			0,
			3,
			2,1);

	Harpoon *harpoon=NULL;

	while(!quit) {

    glClearColor( 0xCA/255.0f, 0xDC/255.0f, 0x9F/255.0f, 0xFF/255.0f );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

		Bubble_Update(bubble);
		Player_Update(player);

		if(player->state==PLAYER_STATE_FIRING) {
			if(!harpoon) {
				harpoon=Harpoon_New(
						harpoonImages,
						(player->image.width-harpoonImages[0].width)/2+player->x,
						(player->image.height)+player->y,
						4);
			}
		}

		if(harpoon) {
			Harpoon_Update(harpoon);
			if(harpoon->y<=0) {
				player->canFire=true;
				Harpoon_Delete(&harpoon);
			}
		}

		Bubble_Draw(bubble);	
		Player_Draw(player);			

		if(harpoon) Harpoon_Draw(harpoon);

		float TimeStart=glfwGetTime();
		while((glfwGetTime()-TimeStart)<(1.0/100.0)){};
	
		glfwSwapBuffers();
	
		quit=glfwGetKey(GLFW_KEY_ESC) | !glfwGetWindowParam(GLFW_OPENED);
	}
	
	if(harpoon) Harpoon_Delete(&harpoon);
	Bubble_Delete(&bubble);
	Player_Delete(&player);

	glDeleteTextures(1,&playerTexture);
	glDeleteTextures(4,&bubbleTextures[0]);
	glDeleteTextures(2,&harpoonTextures[0]);

	glfwTerminate();

	return 0;
}
