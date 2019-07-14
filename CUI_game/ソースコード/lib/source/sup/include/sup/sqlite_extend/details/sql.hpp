/**
* @file sql.hpp
* brief sql��`�t�@�C��
*/

#ifndef SUP_LIB_SQLITE_EXTEND_SQL_HPP
#define SUP_LIB_SQLITE_EXTEND_SQL_HPP

#include<string>

namespace sup
{
inline namespace sqlite
{
namespace details
{
	/**
	* @class Sql
	* @brief �����^�Ɋ֌W�Ȃ�Sql����������悤�ɂ���N���X
	*/
	class Sql final
	{
	public:
		Sql() = default;
		Sql(const Sql&) = default;
		Sql(Sql&&) = default;
		~Sql() = default;
		Sql& operator=(const Sql&) = default;
		Sql& operator=(Sql&&) = default;

	public:
		/**
		* @brief �R���X�g���N�^
		* @param sql ��
		*/
		Sql(const char* sql);

		/**
		* @brief �R���X�g���N�^
		* @param sql��
		*/
		Sql(const wchar_t *sql);
	
	public:
		std::string sql; //!< �}���`�o�C�g��sql��
		std::wstring wsql; //!< ���C�h������sql��

	public:
		/**
		* @brief sql����j������
		*/
		void SqlClear()noexcept;

		/**
		* @brief sql����ۑ�����
		* @return �ۑ�����sql��
		*/
		std::string SaveSql(const char* sql);
		std::wstring SaveSql(const wchar_t* sql);

		/**
		* @brief sql����ێ����邩�m�F����
		* @return true�Ŗ��ێ� false�ŕێ�
		*/
		bool Empty()const noexcept;

		/**
		* @breif sql�����擾����
		*/
		operator const char*()noexcept;
		operator const wchar_t*()noexcept;
		operator const void*()noexcept;
	};
}
}
}


#endif