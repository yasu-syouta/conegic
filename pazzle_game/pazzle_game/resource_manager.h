#pragma once
#include"resource.h"
#include"IResourceControl.h"

#include<unordered_map>
#include<tuple>

const int RES_MAX = 200;


namespace res
{
	enum RES_ID
	{
		TITLE_LOGO,
		TITLE_TITLE,
		GAME_BLOCK,
		GAME_FIELD,
		GAME_BACKGROUND,
		RES_MAX_ = RES_MAX,
	};
	//resource = ���\�[�X�^ bool = ���\�[�X���������ɃL���b�V�����Ă������ǂ���
	using res_tuple = std::tuple<resource_sh, bool>;
	inline auto get_resource(res_tuple& tuple) -> decltype(std::get<0>(tuple)) { return std::get<0>(tuple); }
	inline auto get_cacheflag(res_tuple& tuple) -> decltype(std::get<1>(tuple)){ return std::get<1>(tuple); }

	class Resource_mng
	{
		std::unordered_map<std::string, res_tuple> res_map;

		Resource_mng() {};
		Resource_mng(const Resource_mng&) = delete;
		Resource_mng& operator=(const Resource_mng&) = delete;
	public:
		//�ǂݍ��݃t�@�C���ƃ��[�_�[��o�^����
		//�������̂��o�^����Ă���΂��̃��\�[�X�ւ̎Q�Ƃ�Ԃ��A�Ȃ���ΐV������������
		resource_sh Regist(const char* filename, Loader file_loader, bool cache = false);
		//���O���w�肵�ă��\�[�X���擾 ���݂��Ȃ��ꍇ��std::runtime_error�𓊂���
		resource_sh Get_RegistedResource(const char* resource_name) ;
		//���\�[�X�̖����I����
		bool Unregist(const resource& resource_);
		static Resource_mng* get_Instance() 
		{
			static Resource_mng obj;
			return &obj;
		}

	};
}