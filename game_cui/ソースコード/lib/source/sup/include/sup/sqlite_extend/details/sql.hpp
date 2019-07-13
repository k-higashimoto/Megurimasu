/**
* @file sql.hpp
* brief sql定義ファイル
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
	* @brief 文字型に関係なくSql文を扱えるようにするクラス
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
		* @brief コンストラクタ
		* @param sql 文
		*/
		Sql(const char* sql);

		/**
		* @brief コンストラクタ
		* @param sql文
		*/
		Sql(const wchar_t *sql);
	
	public:
		std::string sql; //!< マルチバイトのsql文
		std::wstring wsql; //!< ワイド文字のsql文

	public:
		/**
		* @brief sql文を破棄する
		*/
		void SqlClear()noexcept;

		/**
		* @brief sql文を保存する
		* @return 保存したsql文
		*/
		std::string SaveSql(const char* sql);
		std::wstring SaveSql(const wchar_t* sql);

		/**
		* @brief sql文を保持するか確認する
		* @return trueで未保持 falseで保持
		*/
		bool Empty()const noexcept;

		/**
		* @breif sql文を取得する
		*/
		operator const char*()noexcept;
		operator const wchar_t*()noexcept;
		operator const void*()noexcept;
	};
}
}
}


#endif