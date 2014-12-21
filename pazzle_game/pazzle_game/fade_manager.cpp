#include"fade_manager.h"

using namespace logic;

bool fade_updater::update()
{
	//���`
	if (updater.next([&](int frame, int now, value_type end) -> value_type
	{
		auto a =  ( (ty == in ? now : frame_ - now) / (double) frame) * 255;
		return a;
	}) == boost::none)
	{
		//�t�F�[�h�C���A�A�E�g���I�������true
		return true;
	}
	else
	{
		//�I����Ă��Ȃ���΍X�V
		double n = updater.get_now().get();
		SetDrawBright((int) n, (int) n, (int) n);
		return false;
	}
}