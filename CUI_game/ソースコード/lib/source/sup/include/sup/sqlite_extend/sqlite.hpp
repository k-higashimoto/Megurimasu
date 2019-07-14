/**
* @file sqlite.hpp
* @brief SQliteクラス定義ファイル
*/

#ifndef SUP_LIB_SQLITE_EXTEND_SQLITE_HPP
#define SUP_LIB_SQLITE_EXTEND_SQLITE_HPP

#include<memory>
#include<string>
#include<sup/sqlite_extend/sqlite3.hpp>
#include<sup/sqlite_extend/details/sqlite_object.hpp>

namespace sup
{
inline namespace sqlite
{
	/**
	* @class SQlite
	* @brief SQliteLibの起点クラス データベースへのアクセスを管理する
	*/
	class SQlite final
	{
	public:
		class SQliteStmt;

	private:
		SQlite(const SQlite&) = delete;
		SQlite& operator=(const SQlite&) = delete;

	public:
		/**
		* @brief コンストラクタ
		*/
		SQlite()noexcept;

		/**
		* @brief コンストラクタ
		* @param データベース名
		*/
		SQlite(const char* name);

		/**
		* @brief コンストラクタ
		* @param データベース名
		*/
		SQlite(const wchar_t* name);

		/**
		* @brief ムーブコンストラクタ
		*/
		SQlite(SQlite&&)noexcept;

		/**
		* @brief デストラクタ
		*/
		~SQlite()noexcept;

		/**
		* @biref ムーブ代入演算子
		*/
		SQlite& operator=(SQlite&&)noexcept;

	private:
		std::shared_ptr<sup::sqlite::details::SQliteObject> db; //!< データベースアクセスオブジェクト
	
	public:
		/**
		* @brief データベースをオープンする
		* @param name データベース名
		*/
		void Open(const char* name);

		/**
		* @brief データベースをオープンする
		* @param name データベース名
		*/
		void Open(const wchar_t* name);

		/**
		* @brief データベースを閉じる
		*/
		void Close()noexcept;

		/**
		* @brief データベースをオープン中か
		* @return trueオープン falseクローズ
		*/
		operator bool()const noexcept;
	};
}
}

#endif