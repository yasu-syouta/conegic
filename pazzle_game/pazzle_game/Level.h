#pragma once

#include"draw_system.h"
#include"field.h"

namespace level
{
	enum LEVEL_ID
	{
		TITLE,
		VSGAME,
		GAME_MAIN,
		EXIT,
	};

	enum ENGINE_MASSAGE
	{
		LEVEL_MSG_INIT,
		LEVEL_MSG_NORMAL,
		LEVEL_MSG_BACK,
		LEVEL_MSG_END,
		LEVEL_MSG_PAUSE,
	};

	class ILevel
	{
	public:
		//���s�@�߂�l�͍D���Ɍ��߂Ă悢
		virtual int execute(int Message) = 0;
		//������LEVEL_ID��Ԃ�
		virtual int get_myid() const = 0;
		//���������������Ă����true ���Ă��Ȃ����false
		virtual bool init(int Message) = 0;
		//�I���������������Ă����true ���Ă��Ȃ����false
		virtual bool end(int Message) = 0;
	};
}