/**
* @file sqlite_check.hpp
* @brief �G���[�̊ȈՃ`�F�b�N��i��錾����t�@�C�� 
*/

namespace sup
{
inline namespace sqlite
{
	/**
	* @brief SQlite�ł̏������������Ă��邩���m�F����
	* @param value sqlite�֐��̃��^�[���R�[�h
	* @return true�Ő��� false�Ŏ��s
	*/
	extern bool SQliteSucceed(int value)noexcept;

	/**
	* @brief SQlite�ł̏��������s���Ă��邩���m�F����
	* @param value sqlite�֐��̃��^�[���R�[�h
	* @return true�Ŏ��s false�Ő���
	*/
	extern bool SQliteFailed(int value)noexcept;
}
}