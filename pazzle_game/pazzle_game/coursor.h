#pragma once
#include"InputDevice.h"
#include"field.h"
#include"Position.h"

namespace GameObject
{
	class cursor
	{
	public:
		//�J�[�\���̌`
		//SOLO 1*1�T�C�Y�@���̃}�X����]
		//SWAP1 2*1�T�C�Y�@���E�̃u���b�N�����ւ���
		//SWAP2 1*2�T�C�Y�@�㉺�̃u���b�N�����ւ���
		//ROTA 2*2�T�C�Y�@4�̃u���b�N����]�ړ�
		enum MODE{ SOLO, SWAP1, SWAP2, ROTA };
		//���̃N���X�Ŏg�������w��
		enum M_DIR{ UP, DOWN, LEFT, RIGHT };
	private:
		field* target_;
		MODE mode;
		util::pos<int> pos;
		util::pos<int> size;
	public:
		explicit cursor(field* target);
		void move(M_DIR dir);
		bool set_mode(MODE new_mode);
		MODE get_mode() const { return mode; }

		bool rotation(M_DIR dir);
		bool swap(M_DIR dir);


		util::pos<int> get_pos() const { return pos; }
		util::pos<int> get_size() const { return size; }
		RECT get_rect() const { return RECT{ pos.x, pos.y, pos.x + size.x, pos.y + size.y }; }
	};
}