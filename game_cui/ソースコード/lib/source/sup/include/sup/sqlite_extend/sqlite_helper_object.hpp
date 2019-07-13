/**
* @file sqlite_helper_object.hpp
* @brief SQliteで使用する指示オブジェクトの定義ファイル
*/

#ifndef SUP_LIB_SQLITE_EXTEND_SQLITE_HELPER_OBJECT_HPP
#define SUP_LIB_SQLITE_EXTEND_SQLITE_HELPER_OBJECT_HPP

#include<string>
#include<vector>
#include<sup/sqlite_extend/sqlite3.hpp>

namespace sup
{
inline namespace sqlite
{
	/**
	* @struct Run
	* @brief sqlの実行を指示する
	*/
	struct Run
	{
		Run(bool reset = false) : reset(reset) {};
		bool reset;
	};

	/**
	* @struct ColumnRun
	* @brief ColumnStepの実行を指示する
	*/
	struct ColumnRun
	{
	};

	/**
	* @struct Pos
	* @brief 位置の指定に使用する
	*/
	struct Pos
	{
		Pos(int pos = 0) : pos(pos) {};
		int pos;
	};

	/**
	* @struct BindBlob
	* @brief Blobの値のバインド指示
	*/
	struct BindBlob
	{
		BindBlob(const void* value, int num, void(*option)(void*) = SQLITE_TRANSIENT) : value(value), num(num), option(option) {};
		const void* value;
		int num;
		void(*option)(void*);
	};

	/**
	* @struct BindDouble
	* @brief Doubleの値のバインド指示用
	*/
	struct BindDouble
	{
		BindDouble(double value) : value(value) {};
		double value;
	};

	/**
	* @struct BindInt
	* @brief Intの値のバインド指示用
	*/
	struct BindInt
	{
		BindInt(int value) : value(value) {};
		int value;
	};

	/**
	* @struct BindInt64
	* @brief Int64の値のバインド指示用
	*/
	struct BindInt64
	{
		BindInt64(sqlite3_int64 value) : value(value) {};
		sqlite3_int64 value;
	};

	/**
	* @struct BindNull
	* @brief Nullの値のバインド指示用
	*/
	struct BindNull
	{
	};

	/**
	* @struct BindText
	* @brief Textの値のバインド指示用
	*/
	struct BindText
	{
		BindText(const char* value, int num = -1, void(*option)(void*) = SQLITE_TRANSIENT) : value(value), num(num), option(option) {};
		const char* value;
		int num;
		void(*option)(void*);
	};

	/**
	* @struct BindText16
	* @brief Text16の値のバインド指示用
	*/
	struct BindText16
	{
		BindText16(const void* value, int num = -1, void(*option)(void*) = SQLITE_TRANSIENT) : value(value), num(num), option(option) {};
		const void* value;
		int num;
		void(*option)(void*);
	};

	/**
	* @struct BindValue
	* @brief Valueの値のバインド指示用
	*/
	struct BindValue
	{
		BindValue(const sqlite3_value* value) : value(value) {};
		const sqlite3_value* value;
	};

	/**
	* @struct ZeroBlob
	* @brief ZeroBlobの値のバインド指示用
	*/
	struct BindZeroBlob
	{
		BindZeroBlob(int num) : num(num) {};
		int num;
	};

	/**
	* @struct ColumnBlob
	* @brief Blobの値の取得指示用
	*/
	struct ColumnBlob
	{
		std::vector<char> value;
		int size;
	};

	/**
	* @struct ColumnBytes
	* @brief Bytesの値の取得指示用
	*/
	struct ColumnBytes
	{
		int size;
	};

	/**
	* @struct ColumnBytes16
	* @brief Bytes16の値の取得指示用
	*/
	struct ColumnBytes16
	{
		int size;
	};
	
	/**
	* @struct ColumnDouble
	* @brief Doubleの値の取得指示用
	*/
	struct ColumnDouble
	{
		double value;
	};

	/**
	* @struct ColumnInt
	* @brief Intの値の取得指示用
	*/
	struct ColumnInt
	{
		int value;
	};

	/**
	* @struct ColumnInt64
	* @brief Int64の値の取得指示用
	*/
	struct ColumnInt64
	{
		sqlite3_int64 value;
	};

	/**
	* @struct ColumnText
	* @brief Textの値の取得指示用
	*/
	struct ColumnText
	{
		std::string value;
		int size;
	};

	/**
	* @struct ColumnText16
	* @brief Text16の値の取得指示用
	*/
	struct ColumnText16
	{
		std::wstring value;
		int size;
	};

	/**
	* @struct ColumnType
	* @brief Typeの値の取得指示用
	*/
	struct ColumnType
	{
		int value;
	};

	/**
	* @struct ColumnValue
	* @brief Valueの値の取得指示用
	*/
	struct ColumnValue
	{
		sqlite3_value* value;
	};
}
}

#endif
