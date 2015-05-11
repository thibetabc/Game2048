#ifndef __H_GAMEDEFINE_H__
#define __H_GAMEDEFINE_H__

#include "KDetectMemoryLeak.h"

#define GAME_2048 0  //2048游戏
#define GAME_CANDYCRUSH 1 //三消游戏
#define GAME_NAME GAME_CANDYCRUSH
//2048_define
#define TTF_RES_PATH "fonts/Marker Felt.ttf"
#define TTF_FONT_SIZE 40
#define GAME_TILED_WIDTH 64
#define GAME_TILED_HEIGHT 64
#define GAME_TILED_BOARD 4
#define GAME_COLS 4 //宽
#define GAME_ROWS 4 //高
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
// 定义屏幕宽高，这与所做的图片有关
#define GAME_SCREEN_WIDTH 480  
#define GAME_SCREEN_HEIGHT 800 

// 定义每个精灵大小与边框大小
#define SPRITE_WIDTH 48  
#define BOADER_WIDTH 2  

// 分数存储
#define userDefault UserDefault::getInstance()

// 音乐音效
#define SOUND_KEY "sound_key"
#define MUSIC_KEY "music_key"

// 音乐音效
#define MUSIC_FILE "CandyCrush/music_mainScene.mp3"


// 游戏精灵行数和列数  
#define ROWS 8  
#define COLS 8  

//最少有3个相同的才消除
#define MIN_EQUAL 3
// 精灵的显示模式，Hor 横向消除一行，Ver纵向消除一列  
enum DisplayMode{
	DISPLAY_MODE_NORMAL = 0,
	DISPLAY_MODE_HORIZONTAL,
	DISPLAY_MODE_VERTICAL,
};
// 精灵种类总数  
#define TOTAL_SPRITE 6  

// 普通的精灵  
static const char *spriteNormal[TOTAL_SPRITE] = {
	"icon1.png",
	"icon2.png",
	"icon3.png",
	"icon4.png",
	"icon5.png",
	"icon6.png"
};
// 垂直
static const char *sprVertical[TOTAL_SPRITE] = {
	"icon1_z.png",
	"icon2_z.png",
	"icon3_z.png",
	"icon4_z.png",
	"icon5_z.png",
	"icon6_z.png"
};

// 水平
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