#pragma once
#include<vector>
#include<array>
#include"block.h"
#include"Position.h"
#include"resource.h"

namespace GameObject
{
	class field
	{
	public: enum ERASE_CHK
		{
			NOP,		//�܂��������ĂȂ�
			CHECKED,	//���׏I�����
			TMP,		//������������Ȃ�
			ERASE,		//�����̂��m��
			ERASING,	//������
			WALLCONNECT,//�ǂƐڑ����Ă��� 
			WALL_COOL_DOWN,	// �ǂ̃N�[���_�E����
		};
	private:
		//�u���b�N�f�[�^
		std::vector<block> data_;
		//�u���b�N�ɕt����ꂽ�t���O
		std::vector<ERASE_CHK> flags_;
		//�t���O�̃e���|����
		std::vector<ERASE_CHK> flags_tmp;

		util::pos<int> field_size_;

		std::array<res::resource_sh, 1> resdata;
		
		//���̃t���[���Ő������ꂽ�u���b�N�̐�
		int create_num = 0;
		//�X�R�A
		int score_ = 0;
		enum{ erase_min = 1 };

		//x,y ���ɒ��ׂ�u���b�N�̍��W
		//bef_pos ���݂̍��W(���̌Ăяo���łǂ̕�������Ă΂ꂽ���𓾂邽��
		//erase_num �������
		int block_erase_impl(int x, int y, int bef_pos, std::vector<ERASE_CHK>& flags , int erase_num = erase_min - 1);

		//�u���b�N��������܂ł̃t���[����
		int erase_frame = 150;
		//�u���b�N�̐���@�ċA�����p
		int fall_block(int x, int y, int n = 0);		

		//1�񂸂u���b�N�𐶐����� �����ł��Ȃ�(�t�B�[���h�����܂��Ă���)�ꍇ��0��Ԃ�
		inline int create_blocks();

		//�u���b�N���ǂɌq�����Ă��邩�ǂ������`�F�b�N����
		bool is_connected(const util::pos<int>& block_pos) const { return is_connected(block_pos.x, block_pos.y); };
		bool is_connected(int ax, int ay) const;

		//�w���̃u���b�N���d�͂ɂ��������ė��Ƃ�
		int fall_blocks(int x);

		//�u���b�N����
		int block_erase();
		//�u���b�N�̍X�V(�u���b�N��erase_frame�̍X�V)
		void block_update();
		//�u���b�N�̐ڑ��`�F�b�N
		void block_erase_check(bool erase_flag = true);

		//data_��flags�̃������ʒu���擾
		int get_memorypos(int x, int y) const { return y * field_size_.x + x; }

	public:
		//���̈ʒu�̃u���b�N�����Ȃ����Ă��邩
		std::vector<int> connectnum;

		using block_iterator = std::vector<block>::iterator;
		using flags_iterator = std::vector<ERASE_CHK>::iterator;

		field(int sizex, int sizey);
		void initialize();

		//�t�B�[���h�̃A�b�v�f�[�g
		void update();

		decltype(field_size_) get_size() const { return field_size_; }
		block& get_block(int x, int y) { return data_[ y * field_size_.x + x ]; }
		const block& get_block_const(int x, int y) const { return data_[y * field_size_.x + x]; }

		//�u���b�N���w��ʒu�ɒu������
		void set_block(int x, int y, block&& object)
		{
			data_[y * field_size_.x + x] = std::move(object);
		}
		//�u���b�N���w��ʒu�ɒu������ �������`�F�b�N����o�[�W����
		bool set_block_secure(int x, int y, block&& object)
		{
			if (x < 0 || x >= field_size_.x || y < 0 || y >= field_size_.y)
				return false;
			data_[y * field_size_.x + x] = std::move(object);
			return true;
		}
		//�t���O���Z�b�g(����p�ɒ���)
		void set_flag(int x, int y, ERASE_CHK flag)
		{
			flags_[y * field_size_.x + x] = flag;
		}
		//�w����W�̃u���b�N��eraseframe��������
		void reset_eraseframe(int x, int y)
		{
			data_[y * field_size_.x + x].set_eraseframe(erase_frame);
		}
		int get_eraseframe() const { return erase_frame; }

		//a��b�����ւ���
		void block_swap(int ax, int ay, int bx, int by);
		void block_swap(const util::pos<int>& a, const util::pos<int>& b){ block_swap(a.x, a.y, b.x, b.y); }

		int get_score() const { return score_; }
		int get_flag(int x, int y) const { return flags_ [ y * field_size_.x + x]; }
		block_iterator block_iterator_begin() { return data_.begin(); }
		block_iterator block_iterator_end() { return data_.end(); }
		
		flags_iterator flags_iterator_begin() { return flags_.begin(); }
		flags_iterator flags_iterator_end() { return flags_.end(); }

	};
}