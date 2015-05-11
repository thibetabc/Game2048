#ifndef __H_GAMEDEFINE_H__
#define __H_GAMEDEFINE_H__

#include "KDetectMemoryLeak.h"

#define GAME_2048 0  //2048��Ϸ
#define GAME_CANDYCRUSH 1 //������Ϸ
#define GAME_NAME GAME_CANDYCRUSH
//2048_define
#define TTF_RES_PATH "fonts/Marker Felt.ttf"
#define TTF_FONT_SIZE 40
#define GAME_TILED_WIDTH 64
#define GAME_TILED_HEIGHT 64
#define GAME_TILED_BOARD 4
#define GAME_COLS 4 //��
#define GAME_ROWS 4 //��
#define AUDIO_PLAY_PATH "audio/play.wav"
#define AUDIO_MOVE_PATH "audio/move.wav"
#define AUDIO_DEFAULT "isPlayAudio"

enum class MOVE_DIR
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
};
#if(GAME_NAME == GAME_2048)
#define GAME_WIDTH 320
#define GAME_HEIGHT 480
#elif(GAME_NAME == GAME_CANDYCRUSH)

//http://blog.csdn.net/lttree/article/details/43079653
// ������Ļ��ߣ�����������ͼƬ�й�
#define GAME_SCREEN_WIDTH 480  
#define GAME_SCREEN_HEIGHT 800 

// ����ÿ�������С��߿��С
#define SPRITE_WIDTH 48  
#define BOADER_WIDTH 2  

// �����洢
#define userDefault UserDefault::getInstance()

// ������Ч
#define SOUND_KEY "sound_key"
#define MUSIC_KEY "music_key"

// ������Ч
#define MUSIC_FILE "CandyCrush/music_mainScene.mp3"


// ��Ϸ��������������  
#define ROWS 8  
#define COLS 8  

//������3����ͬ�Ĳ�����
#define MIN_EQUAL 3
// �������ʾģʽ��Hor ��������һ�У�Ver��������һ��  
enum DisplayMode{
	DISPLAY_MODE_NORMAL = 0,
	DISPLAY_MODE_HORIZONTAL,
	DISPLAY_MODE_VERTICAL,
};
// ������������  
#define TOTAL_SPRITE 6  

// ��ͨ�ľ���  
static const char *spriteNormal[TOTAL_SPRITE] = {
	"icon1.png",
	"icon2.png",
	"icon3.png",
	"icon4.png",
	"icon5.png",
	"icon6.png"
};
// ��ֱ
static const char *sprVertical[TOTAL_SPRITE] = {
	"icon1_z.png",
	"icon2_z.png",
	"icon3_z.png",
	"icon4_z.png",
	"icon5_z.png",
	"icon6_z.png"
};

// ˮƽ
static const char *sprHorizontal[TOTAL_SPRITE] = {
	"icon1_h.png",
	"icon2_h.png",
	"icon3_h.png",
	"icon4_h.png",
	"icon5_h.png",
	"icon6_h.png"
};

#endif


#endif