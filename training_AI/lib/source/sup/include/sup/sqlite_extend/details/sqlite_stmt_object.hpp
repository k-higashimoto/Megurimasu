/**
* @file sqlite_stmt_object.hpp
* @brief SQliteStmtObjectの定義ファイル
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
	* @brief sqlite3_stmtの終了処理自動化クラス
	*/
	class SQliteStmtObject final
	{
		SQliteStmtObject() = delete;
		SQliteStmtObject(const SQliteStmtObject&) = delete;
		SQliteStmtObject& operator=(const SQliteStmtObject&) = delete;

	public:
		/**
		* @brief コンストラクタ
		* @param stmt ステートメントオブジェクト
		*/
		SQliteStmtObject(sqlite3_stmt* stmt)noexcept;

		/**
		* @brief ムーブコンストラクタ
		*/
		SQliteStmtObject(SQliteStmtObject&&)noexcept;

		/**
		* @brief デストラクタ
		*/
		~SQliteStmtObject()noexcept;

		/**
		* @breif ムーブ代入演算子のオーバーロード
		*/
		SQliteStmtObject& operator=(SQliteStmtObject&&)noexcept;

	private:
		sqlite3_stmt* stmt; //!< ステートメントオブジェクト

	public:
		/**
		* @brief sqlite3_stmtを取得する
		* @return sqlite3_stmt
		*/
		operator sqlite3_stmt*()const noexcept;

		/**
		* @brief 値の書き換え手段を提供
		* @return stmtのダブルポインタ
		*/
		sqlite3_stmt** operator&()noexcept;

		/**
		* @brief 保持するステートメントオブジェクトを破棄する
		*/
		void Finalize()noexcept;
	};
}
}
}


#endif