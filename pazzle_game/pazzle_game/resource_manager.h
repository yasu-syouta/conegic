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
	//resource = リソース型 bool = リソースを消さずにキャッシュしておくかどうか
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
		//読み込みファイルとローダーを登録する
		//同じものが登録されていればそのリソースへの参照を返し、なければ新しく生成する
		resource_sh Regist(const char* filename, Loader file_loader, bool cache = false);
		//名前を指定してリソースを取得 存在しない場合はstd::runtime_errorを投げる
		resource_sh Get_RegistedResource(const char* resource_name) ;
		//リソースの明示的消去
		bool Unregist(const resource& resource_);
		static Resource_mng* get_Instance() 
		{
			static Resource_mng obj;
			return &obj;
		}

	};
}