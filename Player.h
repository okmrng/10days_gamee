#pragma once

#include <Vector2.h>
#include <Novice.h>

/// <summary>
/// ���@�N���X
/// </summary>
class Player
{
public:
	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	///  �X�V
	/// </summary>
	void Upadate(char* keys, char* preKeys);

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

private:
	// ���@���
	float radius_;     // ���a
	Vector2 pos_;      // ���W
	float velocity_;   // ���x
};

