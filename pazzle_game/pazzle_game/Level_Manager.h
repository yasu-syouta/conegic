#pragma once
#include<list>
#include<unordered_map>
#include<memory>
#include"fade_manager.h"
#include"resource.h"

#include"Level.h"

namespace level
{
	using level_t = std::shared_ptr < ILevel > ;

	//�Q�[���̃V�[��(Level)�J�ڂ��Ǘ�����
	class Level_Manager
	{
		std::unordered_map<int, level_t> levels;
		std::list <level_t> level_stack;

		logic::fade_updater fade;
		res::resource_sh now_loading_gr;
		int next_id = 0;
		Level_Manager() = default;
		Level_Manager(const Level_Manager&) = delete;
		Level_Manager& operator=(const Level_Manager&) = delete;
		enum STATE{ INIT, EXE, END, END_BACK, NEXT } state = INIT;
		int frame = 0;
	public:
		static Level_Manager* get_Instance()
		{
			static Level_Manager obj;
			return &obj;
		}
		bool Initialize();
		//�t�F�[�h�A�E�g�̐ݒ�
		void set_fadeout(int frame);
		//�t�F�[�h�C���̐ݒ�
		void set_fadein(int frame);
		//�t�F�[�h�������I����Ă��邩
		inline bool fadeend() { return fade.is_end(); }

		int get_bright() { return fade.get_bright(); }
		//����Level�֑J��
		//�J�ڂ��������Ă����true
		bool set_next_level( int id);
		//����Level�֖߂�
		bool back_level();
		//Level��o�^
		bool regist_level(int id, level_t Level);
		//���s
		level_t execute();

		//�Q�[�����I������
		bool game_exit();

		int get_frame() const { return frame; }
	};
	template<class T>
	auto create_level() -> decltype(std::make_shared<T>()) { return std::make_shared<T>(); }
}