#pragma once
#include<boost/optional.hpp>

namespace util
{
	template<class Value_Type>
	class translater
	{
		//���݂̒l
		boost::optional<Value_Type> now;
		//�����l
		boost::optional<Value_Type> start_;
		//�I���l
		boost::optional<Value_Type> end_;
		//���݂̃t���[����
		int now_time = 0;
		//����t���[����
		int frame_ = 0;

	public:
		using optional_value_type = boost::optional<Value_Type>;
		translater() = default;
		translater(Value_Type&& start, Value_Type&& end, int frame) : start_(std::move(start)), end_(std::move(end)), frame_(frame) {}
		template<class Callable>
		optional_value_type& next(Callable f)
		{
			if (++now_time <= frame_)
				now = f(frame_, now_time, *end_);
			return now;
		}
		bool is_end() const { return now_time > frame_; }
		optional_value_type& get_now() { return now; }

	};
}