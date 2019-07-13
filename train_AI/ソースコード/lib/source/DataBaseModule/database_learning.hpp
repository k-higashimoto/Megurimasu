/**
* @file database_learning.hpp
* @brief DataBaseLearning�錾�t�@�C��
*/

#pragma once
#include<vector>
#include<map>
#include<boost/python.hpp>
#include"base.hpp"

namespace database
{	
	/**
	* @class DataBaseLearning
	* @brief �w�K�p�N���X
	*/
	class DataBaseLearning final
	{
	private:
		InitData init_data;					//!< �����f�[�^
		TermData term_data;					//!< �I���f�[�^ 
		std::vector<TurnData> turn_data;	//!< �w�K�f�[�^

	public:
		/**
		* @brief �����f�[�^���Z�b�g����
		*/
		void SetInit(const boost::python::dict& dict)noexcept;

		/**
		* @brief �����f�[�^���Z�b�g����
		*/
		void SetTerm(const boost::python::dict& dict)noexcept;

		/**
		* @brief �^�[���f�[�^��~����
		* @param turn �^�[���f�[�^
		*/
		void PushTurn(const boost::python::dict& dict)noexcept;

		/**
		* @brief �^�[���f�[�^�����o��
		*/
		void PopTurn()noexcept;

		/**
		* @brief �^�[���f�[�^��j������
		*/
		void ClearTurn()noexcept;

		/**
		* @brief �w�K�f�[�^��ۑ�����
		* @return true�Ő��� false���s
		*/
		bool Save()noexcept;
	};
}