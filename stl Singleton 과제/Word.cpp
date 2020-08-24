#include "Word.h"

Word::Word()
{
	m_pos = { RandNum(5, 60), 1 };
}

void Word::SetMaterial(Material material)
{
	m_mat = material;
}

void Word::MoveDown()
{
	m_pos.y++;
}

bool Word::CheckTouchFloor()
{
	if (m_pos.y == 35)
		return true;
	return false;
}

void Word::Draw()
{
	m_draw.TextMiddle(m_pos.x, m_pos.y, m_mat.texture, m_mat.color);
}

void Word::Erase()
{
	m_draw.TextMiddle(m_pos.x, m_pos.y, "          ");
}

bool Word::SameWord(string word)
{
	if (m_mat.texture == word)
		return true;
	return false;
}

int Word::GetColor()
{
	return m_mat.color;
}

Word::~Word()
{

}