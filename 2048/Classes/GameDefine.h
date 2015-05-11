#ifndef __H_GAMEDEFINE_H__
#define __H_GAMEDEFINE_H__

#define GAME_WIDTH 320
#define GAME_HEIGHT 480
#define TTF_RES_PATH "fonts/Marker Felt.ttf"
#define TTF_FONT_SIZE 40
#define GAME_TILED_WIDTH 64
#define GAME_TILED_HEIGHT 64
#define GAME_TILED_BOARD 4
#define GAME_COLS 4 //¿í
#define GAME_ROWS 4 //¸ß
#define AUDIO_PLAY_PATH "audio/play.wav"
#define AUDIO_MOVE_PATH "audio/move.wav"
#define AUDIO_DEFAULT "isPlayAudio"

#define CL(__className__) [](){return __className__::create();}
enum class MOVE_DIR
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
};


#endif