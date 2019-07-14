/**
* @file sqlite_error.hpp
* @brief SQliteError定義ファイル
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
	* @brief SQliteLib全体で使用するSQlite操作関連のエラー取得用クラス
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
		* @brief コンストラクタ
		* @param access エラー元となったデータベース
		* @param msg メッセージ内容
		*/
		SQliteError(sqlite3* access, const char* msg)noexcept;

	private:
		int errcode; //!< エラーコード
		int extend_errcode; //!< 拡張エラーコード
		std::string msg; //!< エラーメッセージ
		std::wstring wmsg; //!< エラーメッセージ

	public:
		/**
		* @brief エラーコード取得
		* @return エラーコード
		*/
		int GetErrorCode()const noexcept;

		/**
		* @brief 拡張エラーコード取得
		* @return エラーコード
		*/
		int GetExtendErrorCode()const noexcept;

		/**
		* @brief エラーメッセージを受け取る
		* @return エラーメッセージ
		*/
		const char* GetErrorMsg()const noexcept;

		/**
		* @brief エラーメッセージを受け取る
		* @return エラーメッセージ
		*/
		const wchar_t* GetErrorMsgW()const noexcept;

		/**
		* @brief エラーメッセージを受け取る
		* @return エラーメッセージ
		*/
		operator const char*()const noexcept;

		/**
		* @brief エラーメッセージを受け取る
		* @return エラーメッセージ
		*/
		operator const wchar_t*()const noexcept;
	};
}
}

#endif
