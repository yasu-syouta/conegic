#include"coursor.h"

using namespace GameObject;

//auto input_dev = input::Controler_Manager<input::Controler<input::DxLibControl>>::get_Instance();

cursor::cursor(field* target) : target_(target), mode(SOLO),
pos(target->get_size().x / 2, target->get_size().y / 2),
size(1, 1)
{}

void cursor::move(M_DIR dir)
{
	switch (dir)
	{
	case UP:
		pos.y = pos.y - 1 < 1 ? pos.y : pos.y - 1;
		break;
	case DOWN:
		pos.y = pos.y + size.y + 1 >= target_->get_size().y ? pos.y : pos.y + 1;
		break;
	case LEFT:
		pos.x = pos.x - 1 < 1 ? pos.x : pos.x - 1;
		break;
	case RIGHT:
		pos.x = pos.x + size.x + 1 >= target_->get_size().x ? pos.x : pos.x + 1;
		break;
	}
}

//�ύX�����ꍇ��true��Ԃ�
bool cursor::set_mode(MODE mode)
{
	switch (mode)
	{
	case SOLO:
		size.x = 1;
		size.y = 1;
		break;
	case SWAP1:
		size.x = 2;
		size.y = 1;
		break;
	case SWAP2:
		size.x = 1;
		size.y = 2;
		break;
	case ROTA:
		size.x = 2;
		size.y = 2;
		break;
	default:
		size.x = 1;
		size.y = 1;
		break;
	}
	this->mode = mode;
	//�͂ݏo����߂�
	if (pos.x + size.x >= target_->get_size().x)
		pos.x = target_->get_size().x - 3;
	if (pos.y + size.y >= target_->get_size().y)
		pos.y = target_->get_size().y - 3;
	return true;
}

bool cursor::rotation(M_DIR dir)
{
	for (int i = pos.y; i < pos.y + size.y; ++i)
	{
		for (int j = pos.x; j < pos.x + size.x; ++j)
		{
			if (dir == RIGHT)
			{
				target_->get_block(j, i).rota(0);
			}
			else if ( dir == LEFT )
			{
				target_->get_block(j, i).rota(1);
			}
			else
			{
				return false;
			}
		}
	}
	return true;
}

bool cursor::swap(M_DIR dir)
{
	switch (mode)
	{
	case SOLO:
		target_->reset_eraseframe(pos.x, pos.y);
		if (dir == RIGHT)
			target_->get_block(pos.x, pos.y).rota(0);
		else
			target_->get_block(pos.x, pos.y).rota(1);
		return true;
	case SWAP1:
	case SWAP2:
		target_->block_swap(pos.x, pos.y, pos.x + size.x - 1, pos.y + size.y - 1);
		return true;
	case ROTA:
		{
				 /*
					�J�[�\���̎w���Ă���ꏊ��
					AB
					CD
					�Ƃ���
				 */
				 //A��tmp�Ƀ��[�u
				 block tmp = std::move(target_->get_block(pos.x, pos.y));
				 if (dir == LEFT)
				 {
					 //A��B�����ւ�
					 target_->block_swap(pos.x, pos.y, pos.x + 1, pos.y);
					 //B��D�����ւ�
					 target_->block_swap(pos.x + 1, pos.y, pos.x + 1, pos.y + 1);
					 //D��C�����ւ�
					 target_->block_swap(pos.x + 1, pos.y + 1, pos.x, pos.y + 1);
					 //C��tmp���Z�b�g
					 target_->set_block(pos.x, pos.y + 1, std::move(tmp));
				 }
				 else if (dir == RIGHT)
				 {
					 //A��C�����ւ�
					 target_->block_swap(pos.x, pos.y, pos.x, pos.y + 1);
					 //C��D�����ւ�
					 target_->block_swap(pos.x, pos.y + 1, pos.x + 1, pos.y + 1);
					 //D��B�����ւ�
					 target_->block_swap(pos.x + 1, pos.y + 1, pos.x + 1, pos.y);
					 //B��tmp���Z�b�g
					 target_->set_block(pos.x + 1, pos.y , std::move(tmp));
				 }
				 else
				 {
					 return false;
				 }
		}
	}
	return true;
}