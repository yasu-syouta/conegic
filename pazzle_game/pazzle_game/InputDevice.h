#pragma once
#include<array>
#include<vector>
#include"DxLibControl.h"

/*
	Controler�N���X�ɑΉ������N���X�̍���
		1.int operator[]�œ����̃o�b�t�@��ǂݍ��߂�(�ǂݍ��ݐ�p)
		2.update()�֐�������
		3.Key�񋓑̂������Œ�`����A�\���L�[���܂ރ{�^����\���v�f���񋓂���Ă���
			(��: enum Key{ DOWN, LEFT, RIGHT, UP, B1, B2... }�Ƃ����񋓑̂��`����i�v�f���͎��R�j)
	�ÓI���Ԃł̑Ή��Ȃ̂ŁA�L�[�𖈃t���[����ʏo�͂���@�\��������A���v���C��ǂݍ���œ��͂�����Ȃǂ����R�ɂł���
*/
/*
namespace input
{
	template<class Control_T = DxLibControl>
	class Controler
	{
		Control_T control;
	public:
		typedef enum Control_T::Key Key;
		void update()
		{
			control.update();
		}
		bool is_PushedButton(Key keycode){ return control[keycode] == 1; }
		int is_PushedButton_frames(Key keycode){ return control[keycode]; }
	};
	
	template<class Controler_T>
	class Controler_Manager
	{
		std::vector<Controler_T> controlers;
		Controler_Manager() = default;
		Controler_Manager(const Controler_Manager&) = delete;
		Controler_Manager& operator=(const Controler_Manager&) = delete;
	public:
		static Controler_Manager* get_Instance()
		{
			static Controler_Manager obj;
			return &obj;
		}
		Controler_T& getControl(int n) { return controlers[n]; }
	};

}
*/