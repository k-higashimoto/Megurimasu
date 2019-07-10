/**
* @file sqlite_helper_object.hpp
* @brief SQlite�Ŏg�p����w���I�u�W�F�N�g�̒�`�t�@�C��
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
	* @brief sql�̎��s���w������
	*/
	struct Run
	{
		Run(bool reset = false) : reset(reset) {};
		bool reset;
	};

	/**
	* @struct ColumnRun
	* @brief ColumnStep�̎��s���w������
	*/
	struct ColumnRun
	{
	};

	/**
	* @struct Pos
	* @brief �ʒu�̎w��Ɏg�p����
	*/
	struct Pos
	{
		Pos(int pos = 0) : pos(pos) {};
		int pos;
	};

	/**
	* @struct BindBlob
	* @brief Blob�̒l�̃o�C���h�w��
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
	* @brief Double�̒l�̃o�C���h�w���p
	*/
	struct BindDouble
	{
		BindDouble(double value) : value(value) {};
		double value;
	};

	/**
	* @struct BindInt
	* @brief Int�̒l�̃o�C���h�w���p
	*/
	struct BindInt
	{
		BindInt(int value) : value(value) {};
		int value;
	};

	/**
	* @struct BindInt64
	* @brief Int64�̒l�̃o�C���h�w���p
	*/
	struct BindInt64
	{
		BindInt64(sqlite3_int64 value) : value(value) {};
		sqlite3_int64 value;
	};

	/**
	* @struct BindNull
	* @brief Null�̒l�̃o�C���h�w���p
	*/
	struct BindNull
	{
	};

	/**
	* @struct BindText
	* @brief Text�̒l�̃o�C���h�w���p
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
	* @brief Text16�̒l�̃o�C���h�w���p
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
	* @brief Value�̒l�̃o�C���h�w���p
	*/
	struct BindValue
	{
		BindValue(const sqlite3_value* value) : value(value) {};
		const sqlite3_value* value;
	};

	/**
	* @struct ZeroBlob
	* @brief ZeroBlob�̒l�̃o�C���h�w���p
	*/
	struct BindZeroBlob
	{
		BindZeroBlob(int num) : num(num) {};
		int num;
	};

	/**
	* @struct ColumnBlob
	* @brief Blob�̒l�̎擾�w���p
	*/
	struct ColumnBlob
	{
		std::vector<char> value;
		int size;
	};

	/**
	* @struct ColumnBytes
	* @brief Bytes�̒l�̎擾�w���p
	*/
	struct ColumnBytes
	{
		int size;
	};

	/**
	* @struct ColumnBytes16
	* @brief Bytes16�̒l�̎擾�w���p
	*/
	struct ColumnBytes16
	{
		int size;
	};
	
	/**
	* @struct ColumnDouble
	* @brief Double�̒l�̎擾�w���p
	*/
	struct ColumnDouble
	{
		double value;
	};

	/**
	* @struct ColumnInt
	* @brief Int�̒l�̎擾�w���p
	*/
	struct ColumnInt
	{
		int value;
	};

	/**
	* @struct ColumnInt64
	* @brief Int64�̒l�̎擾�w���p
	*/
	struct ColumnInt64
	{
		sqlite3_int64 value;
	};

	/**
	* @struct ColumnText
	* @brief Text�̒l�̎擾�w���p
	*/
	struct ColumnText
	{
		std::string value;
		int size;
	};

	/**
	* @struct ColumnText16
	* @brief Text16�̒l�̎擾�w���p
	*/
	struct ColumnText16
	{
		std::wstring value;
		int size;
	};

	/**
	* @struct ColumnType
	* @brief Type�̒l�̎擾�w���p
	*/
	struct ColumnType
	{
		int value;
	};

	/**
	* @struct ColumnValue
	* @brief Value�̒l�̎擾�w���p
	*/
	struct ColumnValue
	{
		sqlite3_value* value;
	};
}
}

#endif
