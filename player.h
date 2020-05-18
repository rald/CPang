#ifndef PLAYER_H
#define PLAYER_H

#include "common.h"

typedef struct Player Player;
typedef enum PlayerState PlayerState;

enum PlayerState {
	PLAYER_STATE_IDLE=0,
	PLAYER_STATE_WALKING,
	PLAYER_STATE_JUMPING
};

struct Player {
	glImage image;
	double x,y;
	double speed;
	double dx,dy;
	double g;
	double jumpHeight;
	bool canJump;
	PlayerState state;
};

Player *Player_New(glImage image,double x,double y,double speed);
void Player_Delete(Player *player);
void Player_Draw(Player *player);
void Player_Update(Player *player);
void Player_UpdateIdle(Player *player);
void Player_UpdateWalking(Player *player);
void Player_UpdateJumping(Player *player);

#endif
