#pragma once
#include<utility>
#include"translater.h"
#include"Position.h"

namespace GameObject
{
	enum DIR
	{
		UP		= 0x1,
		RIGHT	= 0x2,
		DOWN	= 0x4,
		LEFT	= 0x8,
	};
	enum BLOCK_TYPE
	{
		BLANK,
		WALL,
		BLOCK,
	};
	class block
	{
		//�����������
		int connect_dir_ = 0;
		//�u���b�N��������܂ł̃t���[����
		int erase_frame = 0xffff;
		BLOCK_TYPE mytype_ = BLANK;
		bool is_new_;
		util::translater<double> block_control;
	public:
		block() : connect_dir_(0), mytype_(BLANK), is_new_(false) {};
		explicit block(int dir) : connect_dir_(dir), mytype_(dir != 0 ? BLOCK : BLANK), is_new_(true) {}
		explicit block(BLOCK_TYPE type, const util::pos<int>& pos_) : mytype_(type),  is_new_(type != WALL ? false : true) {}
		block(block&& object)
		{
			*this = std::move(object);
		}
		//0 = Right 1 = Left
		void rota(int dir);
		//update my type
		block& operator=(BLOCK_TYPE type)
		{
			if (type != BLOCK) mytype_ = type;
			return *this;
		}

		block& operator=(block&& object)
		{
			mytype_ = object.mytype_;
			connect_dir_ = object.connect_dir_;
			object.mytype_ = BLANK;
			object.connect_dir_ = 0;
			erase_frame = object.erase_frame;
			is_new_ = object.is_new_;

			return *this;
		}
		void set_eraseframe(int value){ erase_frame = value; }
		int get_eraseframe() const { return erase_frame; }
		//���̃u���b�N���V�������ǂ���
		bool is_new() const { return is_new_; }
		//���̃u���b�N��new�t���O��|��
		void set_old()  { is_new_ = false; }
		//���������ʂ�0�ȉ��̏ꍇ��false
		bool decrement_eraseframe() { return (--erase_frame) >= 1; }
		//�u���b�N������
		bool erase() 
		{ 
			if (mytype_ != BLANK)
			{
				if (mytype_ == BLOCK)
					mytype_ = BLANK;
				connect_dir_ = 0;
				erase_frame = 0xffff;
				return true;
			}
			else
				return false;
		}
		bool operator==(BLOCK_TYPE type) const { return mytype_ == type; }
		bool operator&(int dir) const { return (connect_dir_ & dir) != 0; }
		BLOCK_TYPE get_block_type() const { return  mytype_; }
		int get_connect_dir() const { return connect_dir_; }
		void set_connect_dir(int dir){ connect_dir_ = dir; mytype_ = dir != 0 ? BLOCK : BLANK; }
		//�u���b�N�𐶐����� 3������4�����̐����m�����w��ł���
		static block block_new(int ThreeLineProb, int FourlineProb);
		//�����w��Ő���
		static block block_new(int dir);
	};
}