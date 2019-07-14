/**
* @file sqlite_error.hpp
* @brief SQliteError��`�t�@�C��
*/

#ifndef SUP_LIB_SQLITE_EXTEND_SQLITE_ERROR_HPP
#define SUP_LIB_SQLITE_EXTEND_SQLITE_ERROR_HPP

#include<string>
#include<exception>
#include"sqlite3.hpp"

namespace sup
{
inline namespace sqlite
{
	/**
	* @class SQliteError
	* @brief SQliteLib�S�̂Ŏg�p����SQlite����֘A�̃G���[�擾�p�N���X
	*/
	class SQliteError final :
		public std::exception
	{
	private:
		SQliteError() = delete;

	public:
		SQliteError(const SQliteError&) = default;
		SQliteError(SQliteError&&) = default;
		~SQliteError() = default;
		SQliteError& operator=(const SQliteError&) = default;
		SQliteError& operator=(SQliteError&&) = default;

	public:
		/**
		* @brief �R���X�g���N�^
		* @param access �G���[���ƂȂ����f�[�^�x�[�X
		* @param msg ���b�Z�[�W���e
		*/
		SQliteError(sqlite3* access, const char* msg)noexcept;

	private:
		int errcode; //!< �G���[�R�[�h
		int extend_errcode; //!< �g���G���[�R�[�h
		std::string msg; //!< �G���[���b�Z�[�W
		std::wstring wmsg; //!< �G���[���b�Z�[�W

	public:
		/**
		* @brief �G���[�R�[�h�擾
		* @return �G���[�R�[�h
		*/
		int GetErrorCode()const noexcept;

		/**
		* @brief �g���G���[�R�[�h�擾
		* @return �G���[�R�[�h
		*/
		int GetExtendErrorCode()const noexcept;

		/**
		* @brief �G���[���b�Z�[�W���󂯎��
		* @return �G���[���b�Z�[�W
		*/
		const char* GetErrorMsg()const noexcept;

		/**
		* @brief �G���[���b�Z�[�W���󂯎��
		* @return �G���[���b�Z�[�W
		*/
		const wchar_t* GetErrorMsgW()const noexcept;

		/**
		* @brief �G���[���b�Z�[�W���󂯎��
		* @return �G���[���b�Z�[�W
		*/
		operator const char*()const noexcept;

		/**
		* @brief �G���[���b�Z�[�W���󂯎��
		* @return �G���[���b�Z�[�W
		*/
		operator const wchar_t*()const noexcept;
	};
}
}

#endif
