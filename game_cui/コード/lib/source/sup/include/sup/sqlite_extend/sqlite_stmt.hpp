/**
* @file sqlite_stmt.hpp
* @brief SQliteStmt定義ファイル
*/

#ifndef SUP_LIB_SQLITE_EXTEND_SQLITE_STMT_HPP
#define SUP_LIB_SQLITE_EXTEND_SQLITE_STMT_HPP

#include<vector>
#include<string>
#include"sqlite.hpp"
#include"sqlite_helper_object.hpp"
#include"details/sql.hpp"
#include"details/sqlite_object.hpp"
#include"details/sqlite_stmt_object.hpp"

namespace sup
{	
inline namespace sqlite
{
	/**
	* @class SQliteSQliteStmt
	* @brief SQL文の操作をラップする
	*/
    class SQlite::SQliteStmt final
	{
	private:
		struct BindPos 
		{
			BindPos(int pos = 1) : pos(pos) {};
			BindPos(const Pos& pos) : pos(pos.pos) {};
			int pos; 
		};

		struct ColumnPos 
		{ 
			ColumnPos(int pos = 0) : pos(pos) {};
			ColumnPos(const Pos& pos) : pos(pos.pos) {};
			int pos;
		};

    private:
        SQliteStmt(const SQliteStmt&) = delete;
        SQliteStmt& operator=(const SQliteStmt&) = delete;

	public: 
        /**
        * @brief コンストラクタ
        * @param sqlite データベースのアクセス権を持つSQliteクラス
        */
		SQliteStmt(SQlite* sqlite)noexcept;

        /**
        * @brief 疑似コピーコンストラクタ
        */
        SQliteStmt(SQliteStmt*);

        /**
        * @brief ムーブコンストラクタ
        */
        SQliteStmt(SQliteStmt&&)noexcept;

        /**
        * @brief デストラクタ
        */
        ~SQliteStmt()noexcept;

        /**
        * @brief 疑似コピー代入演算子
        */
        SQliteStmt& operator=(SQliteStmt*);

        /**
        * @brief ムーブ代入演算子
        */
        SQliteStmt& operator=(SQliteStmt&&);

	private:
		std::shared_ptr<sup::sqlite::details::SQliteObject> db; //!< 使用するデータベースアクセスオブジェクト
		sup::sqlite::details::SQliteStmtObject stmt; //!< ステートメントオブジェクト
		sup::sqlite::details::Sql sql; //保持するsql文
        BindPos bind_pos; //!< 次のバインド位置情報
        ColumnPos column_pos; //!< 次に取得するカラム位置情報

	private:
		/**
		* @breif エラーを取得して例外を投げる
		* @param msg メッセージ
		* @except SQliteError
		*/
		[[noreturn]] void ThrowErrorObject(const char* msg)const;

		/**
		* @brief 保持するsql文をコンパイルする
		*/
		void HasSqlCompile();

		/**
		* @brief 位置情報をリセットする
		*/
		void ResetPos()noexcept;

	public:
        /**
        * @brief ステートメントをコンパイル
        * @param sql sql文(マルチバイト)
		* @except コンパイル失敗時SQliteError
        */
        void Prepare(const char* sql);

        /**
        * @brief ステートメントをコンパイル
        * @param sql sql文(ワイド文字)
		* @except コンパイル失敗時SQliteError
        */
        void Prepare(const wchar_t* sql);

        /**
        * @brief sqlを実行する
		* @except 実行失敗時SQliteError
		* @attention
		*	バインド位置とカラム位置はリセットされる
        */
		void Step();

		/**
		* @brief カラム取得用のsqlを実行する
		* @return trueでSQLITE_ROWが返った falseでそうでない
		* @except 実行失敗時SQliteError
		*/
		bool ColumnStep();

        /**
        * @brief sqlを再利用可能にする
		* @except リセット失敗時SQliteError
        */
		void Reset();

        /**
        * @brief Stepを呼び出しResetを呼び出す
		* @except 失敗時SQliteError
        */
		void StepAndReset();

		/**
		* @brief sql文のコンパイルを易化する
		* @except 実行失敗時SQliteError
		*/
		SQliteStmt& operator<<(const char* sql);
		SQliteStmt& operator<<(const wchar_t* sql);

		/**
		* @brief sql文を実行する
		* @return sqlite3_stepの返した値
		* @except 実行失敗時SQliteError
		*/
		void operator<<(const Run& run);

		/**
		* @brief カラム取得用のsqlを実行する
		* @return trueでSQLITE_ROWが返った falseでそうでない
		* @except 実行失敗時SQliteError
		* @attention
		*	バインド位置とカラム位置はリセットされる
		*/
		bool operator<<(const ColumnRun& run);

        /**
        * @brief Bind処理を行う
        * @param バインド内容
        * @return SQliteStmt
		* @except 実行失敗時SQliteError
        * @attention
        *   呼び出されるたびに内部で位置をずらす処理を行う
        *   Posを渡すとBind位置を指定の位置に変更する
        */
        SQliteStmt& operator<<(const Pos& pos)noexcept;
        SQliteStmt& operator<<(const BindBlob& value);
		SQliteStmt& operator<<(const BindDouble& value);
		SQliteStmt& operator<<(const BindInt& value);
		SQliteStmt& operator<<(const BindInt64& value);
		SQliteStmt& operator<<(const BindNull& value);
		SQliteStmt& operator<<(const BindText& value);
		SQliteStmt& operator<<(const BindText16& value);
		SQliteStmt& operator<<(const BindValue& value);
        SQliteStmt& operator<<(const BindZeroBlob& value);

        /**
        * @brief カラムを取得する
        * @param 取得内容を受け取る変数
        * @return SQliteStmt
		* @except stlの例外が返る可能性あり
        * @attention
        *   呼び出されるたびに内部で位置をずらす処理を行う
        *   Posを渡すと位置を指定の位置に変更する
        */
        SQliteStmt& operator>>(const Pos& pos)noexcept;
        SQliteStmt& operator>>(ColumnBlob& value);
        SQliteStmt& operator>>(ColumnBytes& value)noexcept;
        SQliteStmt& operator>>(ColumnBytes16& value)noexcept;
        SQliteStmt& operator>>(ColumnDouble& value)noexcept;
        SQliteStmt& operator>>(ColumnInt& value)noexcept;
        SQliteStmt& operator>>(ColumnInt64& value)noexcept;
        SQliteStmt& operator>>(ColumnText& value);
        SQliteStmt& operator>>(ColumnText16& value);
        SQliteStmt& operator>>(ColumnType& value)noexcept;
        SQliteStmt& operator>>(ColumnValue& value)noexcept;
    };
}
}

#endif