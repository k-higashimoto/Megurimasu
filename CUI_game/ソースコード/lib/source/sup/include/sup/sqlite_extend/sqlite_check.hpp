/**
* @file sqlite_check.hpp
* @brief エラーの簡易チェック手段を宣言するファイル 
*/

namespace sup
{
inline namespace sqlite
{
	/**
	* @brief SQliteでの処理が成功しているかを確認する
	* @param value sqlite関数のリターンコード
	* @return trueで成功 falseで失敗
	*/
	extern bool SQliteSucceed(int value)noexcept;

	/**
	* @brief SQliteでの処理が失敗しているかを確認する
	* @param value sqlite関数のリターンコード
	* @return trueで失敗 falseで成功
	*/
	extern bool SQliteFailed(int value)noexcept;
}
}