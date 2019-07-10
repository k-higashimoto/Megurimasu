/**
* @file SQliteObject.hpp
* @brief SQliteObject定義ファイル
*/

#ifndef SUP_LIB_SQLITE_EXTEND_SQLITEOBJECT_HPP
#define SUP_LIB_SQLITE_EXTEND_SQLITEOBJECT_HPP

#include"../sqlite3.hpp"

namespace sup
{
inline namespace sqlite
{
namespace details
{
	/**
	* @class SQliteObject
	* @brief SQliteのオープン・クローズを管理する
	* @note
	*   shared_ptrの使用前提となるためアクセス先が異なるという問題を引き起こしうる
	*	open closeを実装は行わない
	*	そのためアクセス処理に関してはコンストラクタ・デストラクタを使用すること
	*/
    class SQliteObject final
	{
	private:
		SQliteObject() = delete;
		SQliteObject(const SQliteObject&) = delete;
		SQliteObject(SQliteObject&&) = delete;
		SQliteObject& operator=(const SQliteObject&) = delete;
		SQliteObject& operator=(SQliteObject&&) = delete;

	public:
        /**
        * @brief コンストラクタ
        * @param name データベース名
		* @except オープン失敗時例外送出
        */
        SQliteObject(const char* name);

        /**
        * @brief コンストラクタ
        * @param name データベース名
		* @except オープン失敗時例外送出
        */
        SQliteObject(const wchar_t* name);

        /**
        * @brief デストラクタ
        */
		~SQliteObject()noexcept;

	private:
		sqlite3* db; //!< データベースアクセスオブジェクト

	public:
        /**
		* @brief データベースアクセスオブジェクトを取得する
		* @return データベースアクセスオブジェクト
		*/
		operator sqlite3*()const noexcept;
	};
}
}
}

#endif