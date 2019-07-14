/**
* @file sqlite_stmt_object.hpp
* @brief SQliteStmtObject�̒�`�t�@�C��
*/

#ifndef SUP_LIB_SQLITE_EXTEND_STMT_OBJECT_HPP
#define SUP_LIB_SQLITE_EXTEND_STMT_OBJECT_HPP

#include"../sqlite3.hpp"

namespace sup
{
inline namespace sqlite
{
namespace details
{
	/**
	* @class SQliteStmtObject
	* @brief sqlite3_stmt�̏I�������������N���X
	*/
	class SQliteStmtObject final
	{
		SQliteStmtObject() = delete;
		SQliteStmtObject(const SQliteStmtObject&) = delete;
		SQliteStmtObject& operator=(const SQliteStmtObject&) = delete;

	public:
		/**
		* @brief �R���X�g���N�^
		* @param stmt �X�e�[�g�����g�I�u�W�F�N�g
		*/
		SQliteStmtObject(sqlite3_stmt* stmt)noexcept;

		/**
		* @brief ���[�u�R���X�g���N�^
		*/
		SQliteStmtObject(SQliteStmtObject&&)noexcept;

		/**
		* @brief �f�X�g���N�^
		*/
		~SQliteStmtObject()noexcept;

		/**
		* @breif ���[�u������Z�q�̃I�[�o�[���[�h
		*/
		SQliteStmtObject& operator=(SQliteStmtObject&&)noexcept;

	private:
		sqlite3_stmt* stmt; //!< �X�e�[�g�����g�I�u�W�F�N�g

	public:
		/**
		* @brief sqlite3_stmt���擾����
		* @return sqlite3_stmt
		*/
		operator sqlite3_stmt*()const noexcept;

		/**
		* @brief �l�̏���������i���
		* @return stmt�̃_�u���|�C���^
		*/
		sqlite3_stmt** operator&()noexcept;

		/**
		* @brief �ێ�����X�e�[�g�����g�I�u�W�F�N�g��j������
		*/
		void Finalize()noexcept;
	};
}
}
}


#endif